#include <stdio.h>


int main(){
    unsigned cycles_high, cycles_high1, cycles_low, cycles_low1;

    asm volatile ("CPUID\n\t"
    "RDTSC\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
    "%eax", "%ebx", "%ecx", "%edx");
    /***********************************/
    /*call the function to measure here*/
    /***********************************/
    asm volatile("RDTSCP\n\t"
    "mov %%edx, %0\n\t"
    "mov %%eax, %1\n\t"
    "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
    "%eax", "%ebx", "%ecx", "%edx");
    

    printf("ch  >>> %u\n", cycles_high);
    printf("cl  >>> %u\n", cycles_low);
    printf("ch1 >>> %u\n", cycles_high1);
    printf("cl1 >>> %u\n", cycles_low1);



    return 0;
}
