.global _start

.text


a:
    .string "aaa\n"
b:
    .string "bbb\n"
c:
    .string "ccc\n"
d:
    .string "ddd\n"
e:
    .string "eee\n"
f_:
    .string "fff\n"
g_:
    .string "ggg\n"
h:
    .string "hhh\n"

print:
    mov $0x1, %rax
    mov $0x1,%rdi
    mov $4,%rdx
    syscall
    ret

setup_f:

    push %rcx
    push %rbx
    push %rsi
    push %rdi
    push %rbp
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    mov %rsp, %r8

    mov %rax, %r12
    mov %rdx, %r11

    mov $13, %rax
    mov (%rsp,%rax,8), %r15
    inc %rax
    mov (%rsp,%rax,8), %r13
    inc %rax
    mov (%rsp,%rax,8), %r14

    push %r8
    mov $9, %rax
    mov $0, %rdi
    mov %r15, %rsi  #ssize function
    mov $3, %rdx
    mov $34, %r10
    mov $-1, %r8
    mov $0, %r9
    syscall
    add $0x100000, %rax
    pop %r8
    mov %rax, %rbp

    push %r8
    mov $9, %rax
    mov $0, %rdi
    mov $0x1000, %rsi  # arg size
    mov $3, %rdx
    mov $34, %r10
    mov $-1, %r8
    mov $0, %r9
    syscall
    pop %r8

    mov %rax,%rcx

    movl %r13d, %ebx
    addl %r13d, %r13d
    mov $0, %r10

_setup_f_cont:

    push (%r14,%r10,8)
    pop (%rcx,%r10,8)
    inc %r10
    cmpl %r13d, %r10d
    jne _setup_f_cont



    mov %rbp, %rsp

    mov %r12, %rax
    mov %r11, %rdx

    mov %rsp, %rbp
    sub $8, %rbp

    push %r8

    call _f
    ret

setup_g:

    push %rcx
    push %rbx
    push %rsi
    push %rdi
    push %rbp
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    mov %rsp, %r8

    mov %rax, %r12
    mov %rdx, %r11
    push %r8
    mov $9, %rax
    mov $0, %rdi
    mov $0x100000, %rsi  #ssize function
    mov $3, %rdx
    mov $34, %r10
    mov $-1, %r8
    mov $0, %r9
    syscall
    add $0x100000, %rax
    pop %r8

    mov %rax, %rsp

    mov %r12, %rax
    mov %r11, %rdx

    mov %rsp, %rbp
    sub $8, %rbp

    push %r8

    call _g
    ret


resume_:
    push %rcx
    push %rbx
    push %rsi
    push %rdi
    push %rbp
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    mov %rsp, %rbp
    mov %r8, %rsp
    mov %rbp, %r8

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %rbp
    pop %rdi
    pop %rsi
    pop %rbx
    pop %rcx

    mov %r8, (%rbp)

    ret


sus_:
    push %rcx
    push %rbx
    push %rsi
    push %rdi
    push %rbp
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    mov %rsp, %r8
    mov (%rbp), %rsp

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %rbp
    pop %rdi
    pop %rsi
    pop %rbx
    pop %rcx

    ret


_f:
    call sus_
    call f
    jmp _f

_g:
    call sus_
    call g
    jmp _g



g:
    lea b,%rsi
    call print
    call sus_

    call setup_f
    mov %r8, %r14

    mov %r14,%r8
    call resume_
    mov %r8, %r14

    lea c,%rsi
    call print

    call sus_

    lea h,%rsi
    call print

    mov %r14,%r8
    call resume_
    mov %r8, %r14

    call sus_


f:
    lea d,%rsi
    call print

    call sus_


    lea f_,%rsi
    call print
    call sus_



_start:
     mov $9, %rax
    mov $0, %rdi
    mov $0x1000, %rsi  # arg size
    mov $3, %rdx
    mov $34, %r10
    mov $-1, %r8
    mov $0, %r9
    syscall

    push $13234;
    push %rax
    push $11234
    call setup_f
    call resume_



exit:

    movq $60, %rax
    syscall
    ret



