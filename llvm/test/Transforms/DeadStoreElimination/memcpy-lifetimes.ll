; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -basic-aa -dse -S | FileCheck %s
; RUN: opt < %s -aa-pipeline=basic-aa -passes=dse -S | FileCheck %s

target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"

%struct.Village = type { [4 x ptr], ptr, %struct.List, %struct.Hosp, i32, i64 }
%struct.List = type { ptr, ptr, ptr }
%struct.Patient = type { i32, i32, i32, ptr }
%struct.Hosp = type { i32, i32, i32, %struct.List, %struct.List, %struct.List, %struct.List }

declare ptr @alloc(ptr)

define ptr @alloc_tree() {
; CHECK-LABEL: @alloc_tree(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[FVAL:%.*]] = alloca [4 x ptr], align 16
; CHECK-NEXT:    call void @llvm.lifetime.start.p0(i64 32, ptr nonnull [[FVAL]])
; CHECK-NEXT:    [[CALL:%.*]] = tail call dereferenceable_or_null(192) ptr @malloc(i64 192)
; CHECK-NEXT:    [[CALL3:%.*]] = tail call ptr @alloc(ptr [[CALL]])
; CHECK-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds [4 x ptr], ptr [[FVAL]], i64 0, i64 3
; CHECK-NEXT:    store ptr [[CALL3]], ptr [[ARRAYIDX]], align 8
; CHECK-NEXT:    [[CALL3_1:%.*]] = tail call ptr @alloc(ptr [[CALL]])
; CHECK-NEXT:    [[ARRAYIDX_1:%.*]] = getelementptr inbounds [4 x ptr], ptr [[FVAL]], i64 0, i64 2
; CHECK-NEXT:    store ptr [[CALL3_1]], ptr [[ARRAYIDX_1]], align 16
; CHECK-NEXT:    [[CALL3_2:%.*]] = tail call ptr @alloc(ptr [[CALL]])
; CHECK-NEXT:    [[ARRAYIDX_2:%.*]] = getelementptr inbounds [4 x ptr], ptr [[FVAL]], i64 0, i64 1
; CHECK-NEXT:    store ptr [[CALL3_2]], ptr [[ARRAYIDX_2]], align 8
; CHECK-NEXT:    [[CALL3_3:%.*]] = tail call ptr @alloc(ptr [[CALL]])
; CHECK-NEXT:    store ptr [[CALL3_3]], ptr [[FVAL]], align 16
; CHECK-NEXT:    call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 8 dereferenceable(32) [[CALL]], ptr nonnull align 16 dereferenceable(32) [[FVAL]], i64 32, i1 false)
; CHECK-NEXT:    call void @llvm.lifetime.end.p0(i64 32, ptr nonnull [[FVAL]])
; CHECK-NEXT:    ret ptr [[CALL]]
;
entry:
  %fval = alloca [4 x ptr], align 16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %fval) #7
  %call = tail call dereferenceable_or_null(192) ptr @malloc(i64 192) #8
  %call3 = tail call ptr @alloc(ptr %call)
  %arrayidx = getelementptr inbounds [4 x ptr], ptr %fval, i64 0, i64 3
  store ptr %call3, ptr %arrayidx, align 8
  %call3.1 = tail call ptr @alloc(ptr %call)
  %arrayidx.1 = getelementptr inbounds [4 x ptr], ptr %fval, i64 0, i64 2
  store ptr %call3.1, ptr %arrayidx.1, align 16
  %call3.2 = tail call ptr @alloc(ptr %call)
  %arrayidx.2 = getelementptr inbounds [4 x ptr], ptr %fval, i64 0, i64 1
  store ptr %call3.2, ptr %arrayidx.2, align 8
  %call3.3 = tail call ptr @alloc(ptr %call)
  store ptr %call3.3, ptr %fval, align 16
  call void @llvm.memcpy.p0.p0.i64(ptr nonnull align 8 dereferenceable(32) %call, ptr nonnull align 16 dereferenceable(32) %fval, i64 32, i1 false)
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %fval) #7
  ret ptr %call
}

declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture)
declare noalias ptr @malloc(i64)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg)
