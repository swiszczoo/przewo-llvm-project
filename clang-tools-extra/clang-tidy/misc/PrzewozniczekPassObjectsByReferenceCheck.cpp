//===--- PrzewozniczekPassObjectsByReferenceCheck.cpp - clang-tidy --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekPassObjectsByReferenceCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekPassObjectsByReferenceCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(functionDecl(forEachDescendant(parmVarDecl(
    unless(
      anyOf(
        hasTypeLoc(referenceTypeLoc(typeLoc())), 
        hasTypeLoc(pointerTypeLoc(typeLoc()))
      )
    )
  ).bind("param")
  )).bind("function"), this);
}

void PrzewozniczekPassObjectsByReferenceCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedParam = Result.Nodes.getNodeAs<ParmVarDecl>("param");
  const auto *MatchedFunc = Result.Nodes.getNodeAs<FunctionDecl>("function");

  if (!MatchedParam->getType().isDestructedType()) {
    return;
  }

  std::string NameStr = MatchedParam->getName().lower();
  auto Name = StringRef(NameStr);
  
  if (Name.contains("copy") || Name.contains("clone") || Name.contains("move") || Name.contains("new")) {
    return;
  }

  diag(MatchedParam->getLocation(), 
    "Check if you accidentally pass parameter '%0' of type '%1' in function '%2' by copy. Suppress this warning by appending 'copy', 'clone', 'move' or 'new' to parameter name. [-8 points]")
    << MatchedParam->getName()
    << MatchedParam->getType().getAsString()
    << MatchedFunc->getName();
}

} // namespace misc
} // namespace tidy
} // namespace clang
