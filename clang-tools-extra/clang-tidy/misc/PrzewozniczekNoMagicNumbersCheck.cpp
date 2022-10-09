//===--- PrzewozniczekNoMagicNumbersCheck.cpp - clang-tidy ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrzewozniczekNoMagicNumbersCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void PrzewozniczekNoMagicNumbersCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(integerLiteral().bind("int"), this);
  Finder->addMatcher(floatLiteral().bind("float"), this);
  Finder->addMatcher(stringLiteral().bind("string"), this);
}

void PrzewozniczekNoMagicNumbersCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedInt = Result.Nodes.getNodeAs<IntegerLiteral>("int");
  const auto *MatchedFloat = Result.Nodes.getNodeAs<FloatingLiteral>("float");
  const auto *MatchedString = Result.Nodes.getNodeAs<StringLiteral>("string");

  if (MatchedInt) {
    llvm::APInt val = MatchedInt->getValue();

    llvm::APInt zero(32, "0", 10);
    llvm::APInt one(32, "1", 10);
    llvm::APInt two(32, "2", 10);

    if (val.eq(zero) || val.eq(one) || val.eq(two)) {
      return;
    }

    if (MatchedInt->getBeginLoc().isMacroID() || MatchedInt->getEndLoc().isMacroID()) {
      return;
    }

    llvm::SmallString<64> str;
    val.toString(str, 10, true);
    diag(MatchedInt->getBeginLoc(), "You can only use 0, 1, 2 in your code! Move '%0' to a header file. [-8 points]")
      << str;

    return;
  }

  if (MatchedFloat) {
    llvm::APFloat val = MatchedFloat->getValue();

    llvm::APFloat zero{0.0};
    llvm::APFloat one{1.0};
    llvm::APFloat two{2.0};

    if (val.compare(zero) == llvm::APFloat::cmpEqual 
      || val.compare(one) == llvm::APFloat::cmpEqual 
      || val.compare(two) == llvm::APFloat::cmpEqual) {
      return;
    }

    if (MatchedFloat->getBeginLoc().isMacroID() || MatchedFloat->getEndLoc().isMacroID()) {
      return;
    }

    llvm::SmallString<64> str;
    val.toString(str);
    diag(MatchedFloat->getBeginLoc(), "You can only use 0, 1, 2 in your code! Move '%0' to a header file. [-8 points]")
      << str;

    return;
  }

  if (MatchedString) {
    if (MatchedString->getBeginLoc().isMacroID() || MatchedString->getEndLoc().isMacroID()) {
      return;
    }

    diag(MatchedString->getBeginLoc(), "Extract constant strings! Move '%0' to a header file. [-8 points]")
      << MatchedString->getString();
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
