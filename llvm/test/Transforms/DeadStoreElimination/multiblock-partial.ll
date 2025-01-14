; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -basic-aa -dse -S | FileCheck %s

target datalayout = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"

define void @second_store_smaller_1(ptr noalias %P, i1 %c) {
; CHECK-LABEL: @second_store_smaller_1(
; CHECK-NEXT:    store i32 0, ptr [[P:%.*]], align 4
; CHECK-NEXT:    br i1 [[C:%.*]], label [[BB1:%.*]], label [[BB2:%.*]]
; CHECK:       bb1:
; CHECK-NEXT:    br label [[BB3:%.*]]
; CHECK:       bb2:
; CHECK-NEXT:    br label [[BB3]]
; CHECK:       bb3:
; CHECK-NEXT:    ret void
;
  store i32 1, ptr %P
  br i1 %c, label %bb1, label %bb2
bb1:
  br label %bb3
bb2:
  br label %bb3
bb3:
  store i16 0, ptr %P
  ret void
}

define void @second_store_smaller_2(ptr noalias %P, i1 %c) {
; CHECK-LABEL: @second_store_smaller_2(
; CHECK-NEXT:    store i32 12345, ptr [[P:%.*]], align 4
; CHECK-NEXT:    br i1 [[C:%.*]], label [[BB1:%.*]], label [[BB2:%.*]]
; CHECK:       bb1:
; CHECK-NEXT:    br label [[BB3:%.*]]
; CHECK:       bb2:
; CHECK-NEXT:    br label [[BB3]]
; CHECK:       bb3:
; CHECK-NEXT:    ret void
;
  store i32 1, ptr %P
  br i1 %c, label %bb1, label %bb2
bb1:
  br label %bb3
bb2:
  br label %bb3
bb3:
  store i16 12345, ptr %P
  ret void
}

declare void @use(i16) readnone
declare void @use.i8(i8) readnone

define void @second_store_smaller_3(ptr noalias %P, i1 %c) {
; CHECK-LABEL: @second_store_smaller_3(
; CHECK-NEXT:    store i32 1, ptr [[P:%.*]], align 4
; CHECK-NEXT:    br i1 [[C:%.*]], label [[BB1:%.*]], label [[BB2:%.*]]
; CHECK:       bb1:
; CHECK-NEXT:    [[L1:%.*]] = load i16, ptr [[P]], align 2
; CHECK-NEXT:    call void @use(i16 [[L1]])
; CHECK-NEXT:    br label [[BB3:%.*]]
; CHECK:       bb2:
; CHECK-NEXT:    br label [[BB3]]
; CHECK:       bb3:
; CHECK-NEXT:    store i16 -31073, ptr [[P]], align 2
; CHECK-NEXT:    ret void
;
  store i32 1, ptr %P
  br i1 %c, label %bb1, label %bb2

bb1:
  %l1 = load i16, ptr %P
  call void @use(i16 %l1)
  br label %bb3
bb2:
  br label %bb3
bb3:
  store i16 -31073, ptr %P
  ret void
}

define void @second_store_smaller_4(ptr noalias %P, i1 %c) {
; CHECK-LABEL: @second_store_smaller_4(
; CHECK-NEXT:    store i32 1, ptr [[P:%.*]], align 4
; CHECK-NEXT:    br i1 [[C:%.*]], label [[BB1:%.*]], label [[BB2:%.*]]
; CHECK:       bb1:
; CHECK-NEXT:    [[L1:%.*]] = load i8, ptr [[P]], align 1
; CHECK-NEXT:    call void @use.i8(i8 [[L1]])
; CHECK-NEXT:    br label [[BB3:%.*]]
; CHECK:       bb2:
; CHECK-NEXT:    br label [[BB3]]
; CHECK:       bb3:
; CHECK-NEXT:    store i16 -31073, ptr [[P]], align 2
; CHECK-NEXT:    ret void
;
  store i32 1, ptr %P
  br i1 %c, label %bb1, label %bb2

bb1:
  %l1 = load i8, ptr %P
  call void @use.i8(i8 %l1)
  br label %bb3
bb2:
  br label %bb3
bb3:
  store i16 -31073, ptr %P
  ret void
}

define void @second_store_smaller_5(ptr noalias %P, i16 %x, i1 %c) {
; CHECK-LABEL: @second_store_smaller_5(
; CHECK-NEXT:    store i32 1, ptr [[P:%.*]], align 4
; CHECK-NEXT:    br i1 [[C:%.*]], label [[BB1:%.*]], label [[BB2:%.*]]
; CHECK:       bb1:
; CHECK-NEXT:    br label [[BB3:%.*]]
; CHECK:       bb2:
; CHECK-NEXT:    br label [[BB3]]
; CHECK:       bb3:
; CHECK-NEXT:    store i16 [[X:%.*]], ptr [[P]], align 2
; CHECK-NEXT:    ret void
;
  store i32 1, ptr %P
  br i1 %c, label %bb1, label %bb2
bb1:
  br label %bb3
bb2:
  br label %bb3
bb3:
  store i16 %x, ptr %P
  ret void
}

define void @second_store_bigger(ptr noalias %P, i1 %c) {
; CHECK-LABEL: @second_store_bigger(
; CHECK-NEXT:    br i1 [[C:%.*]], label [[BB1:%.*]], label [[BB2:%.*]]
; CHECK:       bb1:
; CHECK-NEXT:    br label [[BB3:%.*]]
; CHECK:       bb2:
; CHECK-NEXT:    br label [[BB3]]
; CHECK:       bb3:
; CHECK-NEXT:    store i64 0, ptr [[P:%.*]], align 8
; CHECK-NEXT:    ret void
;
  store i32 1, ptr %P
  br i1 %c, label %bb1, label %bb2
bb1:
  br label %bb3
bb2:
  br label %bb3
bb3:
  store i64 0, ptr %P
  ret void
}
