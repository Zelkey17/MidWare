//
// Created by ash on 29.04.24.
//
#pragma once
#include<vector>
#include <string>
#include<concepts>
#include<sstream>
#include<ranges>
#include <algorithm>


std::stringstream __start(const std::string& entry_name){
    std::stringstream ans;
    ans<<R"(
.text
.global _start
__not_implemented_msg:
    .string "not implemented\n"
__not_implemented:
    mov $1, %rax
    mov $2, %rdi
    mov $__not_implemented_msg, %rsi
    mov $16, %rdx
    syscall
exit:
    movq $60, %rax
    syscall
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

_start:
    mov $9, %rax
    mov $0, %rdi
    mov $0x1000, %rsi  # arg size
    mov $3, %rdx
    mov $34, %r10
    mov $-1, %r8
    mov $0, %r9
    syscall

    push %rax;
    push $0
    push $1123245
    call setup_)"+entry_name+R"(
    call resume_
    call exit
)";
    return ans;
}
