define dso_local i32 @main(){
    %1 = alloca float
    store float 0x40163851E0000000, float* %1
    %2 = load float, float* %1
    %3 = fcmp ugt float %2, 1.000000e+00
    br i1 %3, label %4, label %5
; a > 1
4:
    ret i32 233
; else    
5:  
    ret i32 0
} 