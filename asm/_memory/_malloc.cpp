//
// Created by ash on 23.04.24.
//


extern "C" void *_map(void *__addr, unsigned long __len, int __prot, int __flags, int __fd, long __offset) {
    void *result;
    asm volatile (
            "movq $9, %%rax;"
            "movq %1, %%rdi;"
            "movq %2, %%rsi;"
            "movl %3, %%edx;"
            "movl %4, %%r10d;"
            "movl %5, %%r8d;"
            "movq %6, %%r9;"
            "syscall;"
            "movq %%rax, %0;"
            : "=r" (result)
            : "r"(__addr), "r" (__len), "r"(__prot), "r"(__flags), "r"(__fd), "r"(__offset)
            : "%rax", "%rcx", "%r11", "%rdi", "%rsi", "%rdx"
            );
    return result;
}

extern "C" void *__malloc(unsigned long __len) {
    const auto t=0x02 | 0x20;
    const void* y= (int*)nullptr+1-1;
    return _map(nullptr, __len, 0x1 | 0x2, 0x02 | 0x20, -1, 0);
}

extern "C" void* __mmm(unsigned long);

extern "C" void* call(){
    int a;
    return (int*)__malloc(1234)+1;
}