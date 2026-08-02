volatile int counter = 0;

void main(void) {
    while (1) {
Preferences: Open User Settings        counter++; // We will watch this variable in the debugger
    }
}

// The reset handler is the very first code that runs when the chip powers on.
void Reset_Handler(void) {
    main();
}

// Cortex-M processors require a vector table at the start of memory.
// Entry 0: Initial Stack Pointer
// Entry 1: The Reset Handler address
__attribute__((section(".isr_vector")))
void (*const vector_table[])(void) = {
    (void (*)(void))0x20010000, // Fake Stack Pointer (Top of 64K RAM)
    Reset_Handler               // Reset Vector
};