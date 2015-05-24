// RUN: %clang_cc1 -emit-pch -o %t.attributes_list1.ast %S/Inputs/attributes_list1.cpp
// RUN: %clang_cc1 -emit-pch -o %t.attributes_list2.ast %S/Inputs/attributes_list2.cpp
// RUN: not %clang_cc1 -ast-merge %t.attributes_list1.ast -ast-merge %t.attributes_list2.ast -fsyntax-only %s 2>&1 | FileCheck %s

// CHECK: attributes_list1.cpp:2:8: error: attribute 'pack' is missing
// CHECK: attributes_list2.cpp:1:8: note: attribute 'pack' here

// CHECK: attributes_list1.cpp:11:8: error: type 'X2' declared with incompatible 'pack' attribute value in different translation units (8 bits vs. 16 bits)
// CHECK: attributes_list2.cpp:7:8: note: attribute 'pack' here


// CHECK: 2 errors generated.
