.intel_syntax noprefix	

.fmtstr:
    .asciz "Result: 0x%016x\n"

.fmtstr_err:
    .asciz "usage: <prog> <fib(n)>\n"

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

        # -- handle base cases 
        cmp rax, 0x0                # fib(0) = 0
        je PRINT

        cmp rax, 0x1                # fib(1) = 1
        je PRINT

        cmp rax, 0x2                # fib(2) = 1
        je CASE2                    # jump to special case to set rax = 1

        mov rcx, rax                # rcx = rax (result from atoi)
        add rcx, 0x1                # add 1 so loop from <= n
        mov rdx, 0x3                # start fib(n) calcuation at n=3
        
        # -- compute fib(n)
        mov r8,  0x1                # f_0 = 1
        mov r9,  0x1                # f_1 = 1

LOOP_FIB:
        cmp rdx, rcx                # rcx contains n
        je PRINT
        
        add r8, r9
        mov rax, r8                 # rax = r8 + r9 (result = f_0 + f_1)

        mov r8, r9                  # r8  = r9      (f_0 = f_1)
        mov r9, rax                 # r9  = result  (f_1 = result)
        
        add rdx, 1
        jmp LOOP_FIB

CASE2:
        mov rax, 0x1                # rax = 1 ( for fib(2) )

PRINT:
        # -- print result 
        mov rdi, OFFSET .fmtstr     # rdi = arg1 -> format string
        mov rsi, rax                # rsi = arg2 -> result (rax)

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







