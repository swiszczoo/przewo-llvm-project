//===--- PrzewozniczekMeaningfulNamesCheck.cpp - clang-tidy ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekMeaningfulNamesCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekMeaningfulNamesCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(varDecl(unless(hasParent(declStmt(hasParent(forStmt()))))).bind("var"), this);
  Finder->addMatcher(fieldDecl().bind("var"), this);
}

void PrzewozniczekMeaningfulNamesCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<NamedDecl>("var");

  if (!MatchedDecl->getIdentifier() || MatchedDecl->getName().size() > 1)
    return;

  if (MatchedDecl->getName().empty())
    return;

  if (MatchedDecl->getName()[0] == 'i' || MatchedDecl->getName()[0] == 'j')
    return;
  
  diag(MatchedDecl->getLocation(), "Use meaningful entity names! [-10 points]");
}

} // namespace misc
} // namespace tidy
} // namespace clang
