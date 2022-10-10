//===--- PrzewozniczekSmartPointersForbiddenCheck.cpp - clang-tidy --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekSmartPointersForbiddenCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekSmartPointersForbiddenCheck::registerMatchers(MatchFinder *Finder) {
  auto UniquePtrDecl = recordDecl(hasName("unique_ptr"), isInStdNamespace());
  auto UniquePtrType = qualType(hasDeclaration(UniquePtrDecl));
  auto SharedPtrDecl = recordDecl(hasName("shared_ptr"), isInStdNamespace());
  auto SharedPtrType = qualType(hasDeclaration(SharedPtrDecl));

  Finder->addMatcher(typeLoc(loc(qualType(UniquePtrType, unless(elaboratedType())))).bind("type"), this);
  Finder->addMatcher(usingDecl(hasAnyUsingShadowDecl(hasTargetDecl(namedDecl(hasName("unique_ptr"), isInStdNamespace())))).bind("type"),this);
  
  Finder->addMatcher(typeLoc(loc(qualType(SharedPtrType, unless(elaboratedType())))).bind("type"), this);
  Finder->addMatcher(usingDecl(hasAnyUsingShadowDecl(hasTargetDecl(namedDecl(hasName("shared_ptr"), isInStdNamespace())))).bind("type"),this);
}

void PrzewozniczekSmartPointersForbiddenCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedType = Result.Nodes.getNodeAs<TypeLoc>("type");
  const auto *MatchedUsing = Result.Nodes.getNodeAs<UsingDecl>("type");

  if (MatchedType) {
    diag(MatchedType->getBeginLoc(), "Do not use built-in smart pointers! If you want them, write their custom implementations. [-? points]");
  } else if (MatchedUsing) {
    diag(MatchedUsing->getBeginLoc(), "Do not use built-in smart pointers! If you want them, write their custom implementations. [-? points]");
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
