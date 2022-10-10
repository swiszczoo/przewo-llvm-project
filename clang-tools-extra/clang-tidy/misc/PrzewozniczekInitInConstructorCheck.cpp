//===--- PrzewozniczekInitInConstructorCheck.cpp - clang-tidy -------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekInitInConstructorCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekInitInConstructorCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxRecordDecl(isClass(), forEach(fieldDecl(hasInClassInitializer(anything())).bind("field"))).bind("class"), this);
}

void PrzewozniczekInitInConstructorCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedClass = Result.Nodes.getNodeAs<CXXRecordDecl>("class");
  const auto *MatchedField = Result.Nodes.getNodeAs<FieldDecl>("field");

  diag(MatchedField->getLocation(), "Do not initialize fields inside class definition! Move initialization of field '%0' from class '%1' to constructor. [-5 points]")
    << MatchedField->getNameAsString()
    << MatchedClass->getNameAsString();
}

} // namespace misc
} // namespace tidy
} // namespace clang
