#ifndef PERF_MONITOR_H
#define PERF_MONITOR_H

#include <stdint.h> //includes specific int sizes in this case "uint64 & uint32" more precision than just int or long

static inline uint32_t read_cycles_lo(void) { //inlines means pass the code to the caller without jumping and returnign reduces overhead
    uint32_t lo;
    
    // Read lower 32 bits
    asm volatile ("csrr %0, mcycle" : "=r"(lo)); //assmeble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)lo); //merges the two 32 bits into 64 bits
}

static inline uint32_t read_cycles_hi(void) { //inlines means pass the code to the caller without jumping and returnign reduces overhead
    uint32_t hi;
    
    // Read upper 32 bits  
    asm volatile ("csrr %0, mcycleh" : "=r"(hi)); //assemble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)hi); //merges the two 32 bits into 64 bits
}


static inline uint32_t read_instructions_lo(void) { //reads instructions, operates just as previous function
    uint32_t lo;
    
    // Read lower 32 bits
    asm volatile ("csrr %0, minstret" : "=r"(lo)); //asm allows to write CPU instructions in C
    

    // Combine into 64-bit value
    return ((uint32_t)lo);
}

static inline uint32_t read_instructions_hi(void) { //reads instructions, operates just as previous function
    uint32_t hi;
    
    // Read upper 32 bits
    asm volatile ("csrr %0, minstreth" : "=r"(hi));
    
    // Combine into 64-bit value
    return ((uint32_t)hi);
}

static inline uint32_t numberof_I_cachemiss_lo(void) {
    uint32_t lo;
    
    // Read lower 32 bits
    asm volatile ("csrr %0, mhpmcounter4" : "=r"(lo)); //assmeble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)lo); //merges the two 32 bits into 64 bits
}

static inline uint32_t numberof_I_cachemiss_hi(void) {
    uint32_t hi;

    // Read upper 32 bits  
    asm volatile ("csrr %0, mhpmcounter4h" : "=r"(hi)); //assemble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)hi); //merges the two 32 bits into 64 bits
}

static inline uint32_t numberof_D_cachemiss_lo(void) {
    uint32_t lo;
    
    // Read lower 32 bits
    asm volatile ("csrr %0, mhpmcounter5" : "=r"(lo)); //assmeble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)lo); //merges the two 32 bits into 64 bits
}

static inline uint32_t numberof_D_cachemiss_hi(void) {
    uint32_t hi;
    
    // Read upper 32 bits  
    asm volatile ("csrr %0, mhpmcounter5h" : "=r"(hi)); //assemble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)hi); //merges the two 32 bits into 64 bits
}

static inline uint32_t numberof_memoryinstructions_lo(void) {
    uint32_t lo;
    
    // Read lower 32 bits
    asm volatile ("csrr %0, mhpmcounter3" : "=r"(lo)); //assmeble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)lo); //merges the two 32 bits into 64 bits
}

static inline uint32_t numberof_memoryinstructions_hi(void) {
    uint32_t hi;
   
    // Read upper 32 bits  
    asm volatile ("csrr %0, mhpmcounter3h" : "=r"(hi)); //assemble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)hi);  //merges the two 32 bits into 64 bits
}

static inline uint32_t data_hazards_lo(void){
    uint32_t lo;

    asm volatile ("csrr %0, mhpmcounter8" : "=r"(lo)); //assmeble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)lo); //merges the two 32 bits into 64 bits
}

static inline uint32_t data_hazards_hi(void){
    uint32_t hi;

    // Read upper 32 bits  
    asm volatile ("csrr %0, mhpmcounter8h" : "=r"(hi)); //assemble instruction in pure C code

    // Combine into 64-bit value
    return ((uint32_t)hi); //merges the two 32 bits into 64 bits
}

static inline uint32_t ALU_stall_lo(void){
    uint32_t lo;

    asm volatile ("csrr %0, mhpmcounter9" : "=r"(lo)); //assmeble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)lo); //merges the two 32 bits into 64 bits
}

static inline uint32_t ALU_stall_hi(void){
    uint32_t hi;

    // Read upper 32 bits  
    asm volatile ("csrr %0, mhpmcounter9h" : "=r"(hi)); //assemble instruction in pure C code

    // Combine into 64-bit value
    return ((uint32_t)hi); //merges the two 32 bits into 64 bits
}

static inline uint32_t numberofstalls_I_lo(void) {
    uint32_t lo;
    
    // Read lower 32 bits
    asm volatile ("csrr %0, mhpmcounter6" : "=r"(lo)); //assmeble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)lo); //merges the two 32 bits into 64 bits
}

static inline uint32_t numberofstalls_D_lo(void) {
    uint32_t lo;
    
    // Read lower 32 bits
    asm volatile ("csrr %0, mhpmcounter7" : "=r"(lo)); //assmeble instruction in pure C code
    
    // Combine into 64-bit value
    return ((uint32_t)lo); //merges the two 32 bits into 64 bits
}

#endif // PERF_MONITOR_H

