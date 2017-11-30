.intel_syntax noprefix	

.fmtstr:
    .asciz "Result: 0x%016x\n"

.globl main
main:

        # get argv[1]
        mov rbx, rsi                # rbx = argv
        add rbx, 8
        mov rbx, [rbx]

        # convert to int
        mov rdi, rbx
        call atoi                   
    
        mov rcx, rax                # rcx = rax (result from atoi)

        add rcx, 0x1                # add 1 so loop from <= n

        mov rdx, 0x3                # rdx starts at 3
        
        # compute fibonacci
        mov r8,  0x1                # f_0 = 1
        mov r9,  0x1                # f_1 = 1

L1:
        cmp rdx, rcx
        je L2
        
        add r8, r9
        mov rax, r8                 # rax = r8 + r9 (result = f_0 + f_1)

        mov r8, r9                  # r8  = r9      (f_0 = f_1)
        mov r9, rax                 # r9  = result  (f_1 = result)
        
        add rdx, 1
        jmp L1
L2:
        # print result 
        mov rdi, OFFSET .fmtstr     # rdi = arg1 -> format string
        mov rsi, rax                # rsi = arg2 -> result (rax)

        xor rax, rax                # zero rax (no floating points passed)

        call printf
                
        ret 
