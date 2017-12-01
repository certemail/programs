.intel_syntax noprefix	

.fmtstr:
    .asciz "Result: 0x%016llx %016llx\n"

.fmtstr_err:
    .asciz "usage: <prog> <fib(n)>\n\tn must be non-negative\n"

.globl main
main:
        # -- validate cmd line args
        cmp rdi, 0x2
        jne EXIT

        # -- get argv[1]
        mov rbx, rsi                # rbx = argv
        add rbx, 8                  # rbx = &(argv[1])
        mov rbx, [rbx]              # rbx = argv[1]

        # -- convert to int
        mov rdi, rbx
        call atoi                   

        # --validate non-negative
        cmp rax, 0x0
        jl EXIT

        # -- handle base cases 
        cmp rax, 0x0                # fib(0) = 0
        je PRINT

        cmp rax, 0x1                # fib(1) = 1
        je PRINT

        cmp rax, 0x2                # fib(2) = 1
        je CASE2                    # jump to special case to set rax = 1

        mov rcx, rax                # rcx = rax (result from atoi)
        add rcx, 0x1                # add 1 so loop from <= n
        mov r13, 0x3                # start fib(n) calcuation at n=3
        
        # -- compute fib(n)
        xor r14, r14                # f_0  ( r14:r8 )
        mov r8,  0x1                # f_0 = 1

        xor r15, r15                # f_1  ( r15:r9 )
        mov r9,  0x1                # f_1 = 1

LOOP_FIB:
        cmp r13, rcx                # rcx contains n; r13 is counter
        je PRINT
                                     
        add r8, r9                  # add low-order 64 bits
        adc r14, r15                # add high-order 64 bits w/ carry
                                    # result is now in: r14:r8
                                    
        mov rdx, r14                # rdx:rax = r14:r8 (result = f_0 + f_1)               
        mov rax, r8                 

        mov r14, r15                # r14:r8  = r15:r9 (f_0 = f_1)
        mov r8, r9                  
                         
        mov r15, rdx                # r15:r9  = result  (f_1 = result)
        mov r9,  rax
        
        add r13, 1
        jmp LOOP_FIB

CASE2:
        mov rax, 0x1                # rax = 1 ( for fib(2) )

PRINT:
        # -- print result 
        mov rdi, OFFSET .fmtstr     # rdi = arg1 -> format string
        mov rsi, rdx                # rsi = arg2 -> result (rax)
        mov rdx, rax
        xor rax, rax                # zero rax (no floating points passed)

        call printf
        xor rax, rax                # return 0
        ret

EXIT:
        # -- print error message                
        mov rdi, OFFSET .fmtstr_err
        xor rax, rax
        call printf

        xor rax, rax                # return 0
        ret 







