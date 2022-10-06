//===--- PrzewozniczekDoNotThrowCheck.cpp - clang-tidy --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekDoNotThrowCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekDoNotThrowCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxThrowExpr().bind("x"), this);
}

void PrzewozniczekDoNotThrowCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *SrcMan = Result.SourceManager;
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXThrowExpr>("x");
  const auto &Location = MatchedDecl->getBeginLoc();

  if (SrcMan->getFilename(Location).endswith(".cpp")) {
    diag(MatchedDecl->getBeginLoc(), "Do not throw exceptions! [-8 points]");
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
