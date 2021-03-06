.intel_syntax noprefix	

.fmtstr:
    .asciz "Result: 0x%016llX %016llX\n"

.fmtstr_err:
    .asciz "usage: <PROG> [FIB(N)]\n\tn must be non-negative (0-186)\n"

.fmtstr_prompt:
    .asciz "Please enter the desired Fibonacci Number (0-186): "

.fmtstr_input:
    .asciz "%s"

.globl main
main:
        push rbp
        mov rbp, rsp
        sub rsp, 0x10

        # -- check argc
        cmp rdi, 0x3
        jge ERROR

        cmp rdi, 0x2
        je L1

        # -- prompt user for input
        mov rdi, OFFSET .fmtstr_prompt
        xor rax, rax
        call printf

        # -- read in user input
        mov rdi, OFFSET .fmtstr_input
        lea rsi, [rbp-0x4]
        xor rax, rax
        call scanf

        # -- convert to int
        lea rdi, [rbp-0x4]          # rdi = &n
        jmp L2

L1:
        # -- get argv[1]
        mov rbx, rsi                # rbx = argv
        add rbx, 8                  # rbx = &(argv[1])
        mov rbx, [rbx]              # rax = argv[1]

        mov rdi, rbx                # rdi = argv[1]

L2:
        # -- convert to int
        call atoi

        # --validate non-negative
        cmp rax, 0x0
        jl ERROR

        cmp rax, 186                # max fib(n) to calculate
        jg ERROR

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
        
        # -- initialization 
        xor r14, r14                # f_0  ( r14:r8 )
        mov r8,  0x1                # f_0 = 1

        xor r15, r15                # f_1  ( r15:r9 )
        mov r9,  0x1                # f_1 = 1

LOOP_FIB:
        # -- compute fib(n)
        cmp r13, rcx                # rcx contains n; r13 is counter
        je PRINT
                                     
        add r8, r9                  # add low-order 64 bits
        adc r14, r15                # add high-order 64 bits w/ carry
                                    # result is now in: r14:r8
                                    
        mov rdx, r14                # rdx:rax = r14:r8  (result = f_0 + f_1)               
        mov rax, r8                 

        mov r14, r15                # r14:r8  = r15:r9  (f_0 = f_1)
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
        jmp EXIT

ERROR:
        # -- print error message                
        mov rdi, OFFSET .fmtstr_err
        xor rax, rax
        call printf

        xor rax, rax                
        jmp EXIT 

EXIT:
        mov rsp, rbp
        pop rbp
        xor rax, rax                # return 0
        ret
