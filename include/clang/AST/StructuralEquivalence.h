//===-- StructuralEquivalence.h - Check for decls equivalence ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//  This file defines the StructuralEquivalence class which checks
//  for equivalence two declarations from different AST contexts
//
//  Main purpose is to check for equivalence before importing declarations
//  from one context to another
//
//  Also it is used for checking for ODR violations
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_CLANG_AST_STRUCTURALEQUIVALENCE_H
#define LLVM_CLANG_AST_STRUCTURALEQUIVALENCE_H

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/Optional.h"
#include "clang/AST/Type.h"
#include <deque>

namespace clang {

class ASTContext;
class Decl;
class RecordDecl;
class ClassTemplateDecl;
class TemplateParameterList;

class StructuralEquivalenceContext {
  /// \brief AST contexts for which we are checking structural equivalence.
  ASTContext &C1, &C2;

  /// \brief The set of "tentative" equivalences between two canonical
  /// declarations, mapping from a declaration in the first context to the
  /// declaration in the second context that we believe to be equivalent.
  llvm::DenseMap<Decl *, Decl *> TentativeEquivalences;

  /// \brief Queue of declarations in the first context whose equivalence
  /// with a declaration in the second context still needs to be verified.
  std::deque<Decl *> DeclsToCheck;

  /// \brief Declaration (from, to) pairs that are known not to be equivalent
  /// (which we have already complained about).
  llvm::DenseSet<std::pair<Decl *, Decl *> > &NonEquivalentDecls;

  /// \brief Whether we're being strict about the spelling of types when
  /// unifying two types.
  const bool StrictTypeSpelling;

  /// \brief Whether to complain about failures.
  const bool Complain;

  /// \brief \c true if the last diagnostic came from C2.
  bool LastDiagFromC2;

public:

  StructuralEquivalenceContext(ASTContext &C1, ASTContext &C2,
                               llvm::DenseSet<std::pair<Decl *, Decl *> > &NonEquivalentDecls,
                               bool StrictTypeSpelling = false,
                               bool Complain = true);

  /// \brief Determine whether the two declarations are structurally
  /// equivalent.
  bool IsStructurallyEquivalent(Decl *D1, Decl *D2);

  /// \brief Determine whether the two types are structurally equivalent.
  bool IsStructurallyEquivalent(QualType T1, QualType T2);

private:

  /// \brief Determine structural equivalence of two expressions.
  bool IsStructurallyEquivalentImpl(Expr *E1, Expr *E2);

  /// \brief Determine whether two identifiers are equivalent.
  bool IsStructurallyEquivalentImpl(const IdentifierInfo *Name1,
                                    const IdentifierInfo *Name2);

  /// \brief Determine whether two nested-name-specifiers are equivalent.
  bool IsStructurallyEquivalentImpl(NestedNameSpecifier *NNS1, NestedNameSpecifier *NNS2);

  /// \brief Determine whether two template arguments are equivalent.
  bool IsStructurallyEquivalentImpl(const TemplateArgument &Arg1,
                                    const TemplateArgument &Arg2);

  /// \brief Determine structural equivalence for the common part of array
  /// types.
  bool IsArrayStructurallyEquivalentImpl(const ArrayType *Array1,
                                         const ArrayType *Array2);

  /// \brief Determine structural equivalence of two types.
  bool IsStructurallyEquivalentImpl(QualType T1, QualType T2);

  /// \brief Determine structural equivalence of two fields.
  bool IsStructurallyEquivalentImpl(FieldDecl *Field1, FieldDecl *Field2);

  /// \brief Determine structural equivalence of two records.
  bool IsStructurallyEquivalentImpl(RecordDecl *D1, RecordDecl *D2);

  /// \brief Determine structural equivalence of two enums.
  bool IsStructurallyEquivalentImpl(EnumDecl *D1, EnumDecl *D2);

  bool IsStructurallyEquivalentImpl(TemplateParameterList *Params1,
                                    TemplateParameterList *Params2);

  bool IsStructurallyEquivalentImpl(TemplateTypeParmDecl *D1,
                                    TemplateTypeParmDecl *D2);

  bool IsStructurallyEquivalentImpl(NonTypeTemplateParmDecl *D1,
                                    NonTypeTemplateParmDecl *D2);

  bool IsStructurallyEquivalentImpl(TemplateTemplateParmDecl *D1,
                                    TemplateTemplateParmDecl *D2);

  bool IsStructurallyEquivalentImpl(ClassTemplateDecl *D1,
                                    ClassTemplateDecl *D2);

  /// \brief Determine structural equivalence of two declarations.
  bool IsStructurallyEquivalentImpl(Decl *D1, Decl *D2);

  DiagnosticBuilder Diag1(SourceLocation Loc, unsigned DiagID);

  DiagnosticBuilder Diag2(SourceLocation Loc, unsigned DiagID);

  /// \brief Finish checking all of the structural equivalences.
  ///
  /// \returns true if an error occurred, false otherwise.
  bool Finish();
};

/// \brief Find the index of the given anonymous struct/union within its
/// context.
///
/// \returns Returns the index of this anonymous struct/union in its context,
/// including the next assigned index (if none of them match). Returns an
/// empty option if the context is not a record, i.e.. if the anonymous
/// struct/union is at namespace or block scope.
Optional<unsigned> findAnonymousStructOrUnionIndex(RecordDecl *Anon);

} // end namespace clang

#endif
