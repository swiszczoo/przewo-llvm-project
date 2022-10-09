//===--- PrzewozniczekGotoForbiddenCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekGotoForbiddenCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekGotoForbiddenCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(gotoStmt().bind("x"), this);
}

void PrzewozniczekGotoForbiddenCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<GotoStmt>("x");
  const auto &Location = MatchedDecl->getBeginLoc();

  diag(Location, "Goto is absolutely forbidden! [-100 points]");
}

} // namespace misc
} // namespace tidy
} // namespace clang
