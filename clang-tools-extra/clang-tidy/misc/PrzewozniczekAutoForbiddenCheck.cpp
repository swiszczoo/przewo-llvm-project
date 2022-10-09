//===--- PrzewozniczekAutoForbiddenCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekAutoForbiddenCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekAutoForbiddenCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(varDecl().bind("decl"), this);
}

void PrzewozniczekAutoForbiddenCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("decl");

  if (MatchedDecl->getType()->getTypeClass() == Type::Auto) {
    diag(MatchedDecl->getLocation(), "Do not use auto; type variable '%0' explicitly as '%1'! [-? points]")
      << MatchedDecl->getNameAsString()
      << MatchedDecl->getType().getAsString();
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
