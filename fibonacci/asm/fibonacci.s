.intel_syntax noprefix	

.fmtstr:
    .asciz "Computing fib(%d)...\n"

.globl main
main:

        # get argv[1]
        #xor rbx, rbx
        #xor rax, rax

        #mov rbx, rsi
        #mov rbx, QWORD PTR [rbx]
        #add rbx, 0x8
        #mov rax, QWORD PTR [rbx]
        
        #------------------
        
        mov rcx, 0x7    # TODO -> rcx will contain user input [ fib(n) ]
        add rcx, 0x1    # add 1 so loop from <= n

        mov rdx, 0x3    # rdx starts at 3
        
        # compute fibonacci

        mov r8,  0x1    # f_0 = 1
        mov r9,  0x1    # f_1 = 1

L1:
        cmp rdx, rcx
        je L2
        
        add r8, r9
        mov rax, r8     # rax = r8 + r9  (result = f_0 + f_1)

        mov r8, r9      # r8  = r9      (f_0 = f_1)
        mov r9, rax     # r9  = result  (f_1 = result)
        
        add rdx, 1
        jmp L1
L2:
         
        ret



#main:
#    mov ecx, 99
#
#1:
#    mov rdi, OFFSET .bottles
#    mov esi, ecx
#    xor rax, rax
#    push rcx
#
#    call printf
#
#    pop rcx
#    loop 1b
#
#    ret
#
#.bottles:
#    .asciz "%d bottles of beer on the wall\n"
