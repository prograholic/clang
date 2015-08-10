// RUN: %clang_cc1 -emit-pch -o %t.string-literal.ast %S/Inputs/string-literal.c
// RUN: %clang_cc1 -ast-merge %t.string-literal.ast -fsyntax-only %s
