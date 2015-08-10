// RUN: %clang_cc1 -emit-pch -o %t.decayed.ast %S/Inputs/decayed.c
// RUN: %clang_cc1 -ast-merge %t.decayed.ast -fsyntax-only %s
