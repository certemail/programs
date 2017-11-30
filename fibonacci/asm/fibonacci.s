.intel_syntax noprefix	

fmtstr:
    .asciz "Computing fib(%d)...\n"

.globl main
main:

    xor rbx, rbx
    mov rbx, [rsi + 8]          # rbx = &(argv+8)

    xor rax, rax
    mov al, BYTE PTR [rbx]      # al = argv[1]
    

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
