define dso_local i32 @main(){
    %1 = alloca i32, align 4    ; a
    %2 = alloca i32, align 4    ; i
    store i32 10, i32* %1, align 4
    store i32 0, i32* %2, align 4
    br label %3

3:  
    %4 = load i32, i32* %2, align 4 ; i
    %5 = icmp slt i32 %4, 10
    br i1 %5, label %6, label %11

; i < 10
6:  
    %7 = load i32, i32* %1, align 4 ; a
    %8 = load i32, i32* %2, align 4 ; i
    %9 = add nsw i32 %8, 1          ; i = i + 1
    %10 = add nsw i32 %7, %9        ; a = a + i
    store i32 %10, i32* %1, align 4
    store i32 %9, i32* %2, align 4
    br label %3

; i >= 10
11:    
    %12 = load i32, i32* %1, align 4 ; a
    ret i32 %12
}