// RUN: %clang_cc1 -emit-pch -o %t.init-list.ast %S/Inputs/init-list.cpp
// RUN: %clang_cc1 -ast-merge %t.init-list.ast -fsyntax-only %s
