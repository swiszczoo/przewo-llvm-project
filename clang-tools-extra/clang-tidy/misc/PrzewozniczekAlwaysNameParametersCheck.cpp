//===--- PrzewozniczekAlwaysNameParametersCheck.cpp - clang-tidy ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekAlwaysNameParametersCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekAlwaysNameParametersCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxRecordDecl(forEach(cxxMethodDecl(isUserProvided(), hasAnyParameter(unless(hasAnyName()))).bind("method"))).bind("class"), this);
}

void PrzewozniczekAlwaysNameParametersCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedClass = Result.Nodes.getNodeAs<CXXRecordDecl>("class");
  const auto *MatchedMethod = Result.Nodes.getNodeAs<CXXMethodDecl>("method");

  diag(MatchedMethod->getLocation(), "Always name all method parameters! Method '%0' from class '%1' contains an unnamed parameter. [-20 points]")
    << MatchedMethod->getNameAsString()
    << MatchedClass->getNameAsString();
}

} // namespace misc
} // namespace tidy
} // namespace clang
