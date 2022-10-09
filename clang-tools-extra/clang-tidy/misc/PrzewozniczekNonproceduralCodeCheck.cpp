//===--- PrzewozniczekNonproceduralCodeCheck.cpp - clang-tidy -------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekNonproceduralCodeCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#define MAX_FUNCTION_SIZE 60

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekNonproceduralCodeCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(compoundStmt(hasParent(functionDecl().bind("func"))).bind("body"), this);
}

void PrzewozniczekNonproceduralCodeCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FunctionDecl>("func");
  const auto *MatchedBody = Result.Nodes.getNodeAs<CompoundStmt>("body");
  const auto *SrcMgr = Result.SourceManager;

  const auto& StartLoc = MatchedBody->getBeginLoc();
  const auto& EndLoc = MatchedBody->getEndLoc();

  if (!SourceLocation::isPairOfFileLocations(StartLoc, EndLoc)) {
    return;
  }

  if (SrcMgr->getPresumedLineNumber(EndLoc) - SrcMgr->getPresumedLineNumber(StartLoc) > MAX_FUNCTION_SIZE) {
    diag(MatchedDecl->getLocation(), "Function '%0' is probably non-procedural, as it is longer than 60 lines! [-11 points]")
      << MatchedDecl->getNameAsString();
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
