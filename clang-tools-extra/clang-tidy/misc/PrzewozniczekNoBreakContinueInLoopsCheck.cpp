//===--- PrzewozniczekNoBreakContinueInLoopsCheck.cpp - clang-tidy --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekNoBreakContinueInLoopsCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekNoBreakContinueInLoopsCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(breakStmt(unless(hasParent(caseStmt()))).bind("break"), this);
  Finder->addMatcher(continueStmt().bind("continue"), this);
}

void PrzewozniczekNoBreakContinueInLoopsCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Context = Result.Context;
  const auto *MatchedBreak = Result.Nodes.getNodeAs<BreakStmt>("break");
  const auto *MatchedContinue = Result.Nodes.getNodeAs<ContinueStmt>("continue");

  if (MatchedBreak) {
    auto list = const_cast<clang::ASTContext*>(Context)->getParents(*MatchedBreak);

    while (!list.empty()) {
      auto node = *list.begin();

      if (node.get<CaseStmt>()) {
        return;
      }

      if (node.get<ForStmt>() || node.get<WhileStmt>() || node.get<DoStmt>()) {
        break;
      }

      list = const_cast<clang::ASTContext*>(Context)->getParents(node);
    }

    diag(MatchedBreak->getBeginLoc(), "Do not use break in loops! It breaks control flow. [-8 points or more]");
  } else if (MatchedContinue) {
    diag(MatchedContinue->getBeginLoc(), "Do not use continue! It breaks control flow. [-8 points or more]");
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
