//===--- MiscTidyModule.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "ConfusableIdentifierCheck.h"
#include "ConstCorrectnessCheck.h"
#include "DefinitionsInHeadersCheck.h"
#include "MisleadingBidirectional.h"
#include "MisleadingIdentifier.h"
#include "MisplacedConstCheck.h"
#include "NewDeleteOverloadsCheck.h"
#include "NoRecursionCheck.h"
#include "NonCopyableObjects.h"
#include "NonPrivateMemberVariablesInClassesCheck.h"
#include "PrzewozniczekAlwaysNameParametersCheck.h"
#include "PrzewozniczekAutoForbiddenCheck.h"
#include "PrzewozniczekDoNotThrowCheck.h"
#include "PrzewozniczekGotoForbiddenCheck.h"
#include "PrzewozniczekInitInConstructorCheck.h"
#include "PrzewozniczekMeaningfulNamesCheck.h"
#include "PrzewozniczekNoBreakContinueInLoopsCheck.h"
#include "PrzewozniczekNoGlobalVariablesCheck.h"
#include "PrzewozniczekNoMagicNumbersCheck.h"
#include "PrzewozniczekNonproceduralCodeCheck.h"
#include "PrzewozniczekOnlyPrivateFieldsCheck.h"
#include "PrzewozniczekPassObjectsByReferenceCheck.h"
#include "PrzewozniczekSmartPointersForbiddenCheck.h"
#include "RedundantExpressionCheck.h"
#include "StaticAssertCheck.h"
#include "ThrowByValueCatchByReferenceCheck.h"
#include "UnconventionalAssignOperatorCheck.h"
#include "UniqueptrResetReleaseCheck.h"
#include "UnusedAliasDeclsCheck.h"
#include "UnusedParametersCheck.h"
#include "UnusedUsingDeclsCheck.h"

namespace clang {
namespace tidy {
namespace misc {

class MiscModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<ConfusableIdentifierCheck>(
        "misc-confusable-identifiers");
    CheckFactories.registerCheck<ConstCorrectnessCheck>(
        "misc-const-correctness");
    CheckFactories.registerCheck<DefinitionsInHeadersCheck>(
        "misc-definitions-in-headers");
    CheckFactories.registerCheck<MisleadingBidirectionalCheck>(
        "misc-misleading-bidirectional");
    CheckFactories.registerCheck<MisleadingIdentifierCheck>(
        "misc-misleading-identifier");
    CheckFactories.registerCheck<MisplacedConstCheck>("misc-misplaced-const");
    CheckFactories.registerCheck<NewDeleteOverloadsCheck>(
        "misc-new-delete-overloads");
    CheckFactories.registerCheck<NoRecursionCheck>("misc-no-recursion");
    CheckFactories.registerCheck<NonCopyableObjectsCheck>(
        "misc-non-copyable-objects");
    CheckFactories.registerCheck<NonPrivateMemberVariablesInClassesCheck>(
        "misc-non-private-member-variables-in-classes");
    CheckFactories.registerCheck<PrzewozniczekAlwaysNameParametersCheck>(
        "misc-przewozniczek-always-name-parameters");
    CheckFactories.registerCheck<PrzewozniczekAutoForbiddenCheck>(
        "misc-przewozniczek-auto-forbidden");
    CheckFactories.registerCheck<PrzewozniczekDoNotThrowCheck>(
        "misc-przewozniczek-do-not-throw");
    CheckFactories.registerCheck<PrzewozniczekGotoForbiddenCheck>(
        "misc-przewozniczek-goto-forbidden");
    CheckFactories.registerCheck<PrzewozniczekInitInConstructorCheck>(
        "misc-przewozniczek-init-in-constructor");
    CheckFactories.registerCheck<PrzewozniczekMeaningfulNamesCheck>(
        "misc-przewozniczek-meaningful-names");
    CheckFactories.registerCheck<PrzewozniczekNoBreakContinueInLoopsCheck>(
        "misc-przewozniczek-no-break-continue-in-loops");
    CheckFactories.registerCheck<PrzewozniczekNoGlobalVariablesCheck>(
        "misc-przewozniczek-no-global-variables");
    CheckFactories.registerCheck<PrzewozniczekNoMagicNumbersCheck>(
        "misc-przewozniczek-no-magic-numbers");
    CheckFactories.registerCheck<PrzewozniczekNonproceduralCodeCheck>(
        "misc-przewozniczek-nonprocedural-code");
    CheckFactories.registerCheck<PrzewozniczekOnlyPrivateFieldsCheck>(
        "misc-przewozniczek-only-private-fields");
    CheckFactories.registerCheck<PrzewozniczekPassObjectsByReferenceCheck>(
        "misc-przewozniczek-pass-objects-by-reference");
    CheckFactories.registerCheck<PrzewozniczekSmartPointersForbiddenCheck>(
        "misc-przewozniczek-smart-pointers-forbidden");
    CheckFactories.registerCheck<RedundantExpressionCheck>(
        "misc-redundant-expression");
    CheckFactories.registerCheck<StaticAssertCheck>("misc-static-assert");
    CheckFactories.registerCheck<ThrowByValueCatchByReferenceCheck>(
        "misc-throw-by-value-catch-by-reference");
    CheckFactories.registerCheck<UnconventionalAssignOperatorCheck>(
        "misc-unconventional-assign-operator");
    CheckFactories.registerCheck<UniqueptrResetReleaseCheck>(
        "misc-uniqueptr-reset-release");
    CheckFactories.registerCheck<UnusedAliasDeclsCheck>(
        "misc-unused-alias-decls");
    CheckFactories.registerCheck<UnusedParametersCheck>(
        "misc-unused-parameters");
    CheckFactories.registerCheck<UnusedUsingDeclsCheck>(
        "misc-unused-using-decls");
  }
};

} // namespace misc

// Register the MiscTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<misc::MiscModule>
    X("misc-module", "Adds miscellaneous lint checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the MiscModule.
volatile int MiscModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
