; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt -dse %s -S | FileCheck %s

target datalayout = "e-m:o-p:32:32-Fi8-i64:64-a:0:32-n32-S128"

define void @widget(ptr %ptr) {
; CHECK-LABEL: @widget(
; CHECK-NEXT:  bb:
; CHECK-NEXT:    [[PTR1:%.*]] = getelementptr inbounds i8, ptr [[PTR:%.*]], i32 4
; CHECK-NEXT:    store atomic i32 0, ptr [[PTR1]] monotonic, align 4
; CHECK-NEXT:    store ptr null, ptr [[PTR]], align 4
; CHECK-NEXT:    ret void
;
bb:
  %ptr1 = getelementptr inbounds i8, ptr %ptr, i32 4
  store atomic i32 0, ptr %ptr1 monotonic, align 4
  store ptr null, ptr %ptr, align 4
  ret void
}
