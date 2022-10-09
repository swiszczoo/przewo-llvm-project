//===--- PrzewozniczekOnlyPrivateFieldsCheck.cpp - clang-tidy -------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekOnlyPrivateFieldsCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

AST_MATCHER(CXXRecordDecl, hasNonStaticNonImplicitMethod) {
  return hasMethod(unless(anyOf(isStaticStorageClass(), isImplicit())))
      .matches(Node, Finder, Builder);
}

void PrzewozniczekOnlyPrivateFieldsCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxRecordDecl(isClass(), hasNonStaticNonImplicitMethod(), forEach(fieldDecl(unless(isPublic())).bind("field"))).bind("class"), this);
}

void PrzewozniczekOnlyPrivateFieldsCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedClass = Result.Nodes.getNodeAs<CXXRecordDecl>("class");
  const auto *MatchedField = Result.Nodes.getNodeAs<FieldDecl>("field");

  diag(MatchedField->getLocation(), "All fields should be private, but the field '%0' in class '%1' is not! [-6 points]")
    << MatchedField->getNameAsString()
    << MatchedClass->getName();
}

} // namespace misc
} // namespace tidy
} // namespace clang
