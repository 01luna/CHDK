#include "../generic/check_compat.c"

extern long *blob_chdk_core;
extern long blob_chdk_core_size;

int __attribute__((naked)) get_core_id() {
    asm volatile (
"    mrc     p15, #0, r0, c0, c0, #5\n"
"    ands    r0, #0xf\n"
"    bx      lr\n"
    );
}

void __attribute__((noreturn)) my_restart()
{
    int coreid = get_core_id();

    if (!coreid) {
        check_compat();

        long *dst = (long*)MEMISOSTART;
        const long *src = blob_chdk_core;
        long length = (blob_chdk_core_size + 3) >> 2;

        core_copy(src, dst, length);

        // GPIO base = 0xD2080000
        // 0xD20801E4   - SD led

        // light up green LED
        volatile int* p = (int*)0xD20801E4;
        *p = 0x24D0002;
    }

    asm volatile (
            "ldr    r2, =0xb5102101\n"  // First 2 instructions of function to call
            "ldr    r1, =0xe051e214\n"  // FW 1.20a
            "ldr    r0, [r1]\n"
            "cmp    r0, r2\n"           // instruction match?
            "beq    cont3\n"

            "movs   r0, %2\n"
            "bne    cont1\n"

            "ldr    r1, =0xe051e078\n"  // FW 1.10b
            "ldr    r0, [r1]\n"
            "cmp    r0, r2\n"           // instruction match?
            "beq    cont2\n"
            "ldr    r1, =0xe051e07c\n"  // FW 1.01a & 1.01b
        "cont2:\n"
            "orr    r1, #1\n"
            "movs   r0, #1\n"
            "blx    r1\n" // unblock core1

        "cont1:\n"
            "mov    r1, %1\n"
            "mov    r0, %0\n"
            "ldr    r2, =0xe042eb75\n" // address is OK for 101a
            "blx    r2\n"              // caching related routine called at fw startup
            "mov    r1, %1\n"
            "mov    r0, %0\n"
            "ldr    r2, =0xe042ec4d\n" // address is OK for 101a
            "blx    r2\n"              // caching related routine called at fw startup
            "mov    r0, %0\n"
            "add    r0, r0, #1\n"
            "bx     r0\n"

        "cont3:\n"          // 1.20a
            "movs   r0, %2\n"
            "bne    cont4\n"

            "orr    r1, #1\n"
            "movs   r0, #1\n"
            "blx    r1\n" // unblock core1

        "cont4:\n"          // 1.20a
            "mov    r1, %1\n"
            "mov    r0, %0\n"
            "ldr    r2, =0xe0425999\n" // address is OK for 120a
            "blx    r2\n"              // caching related routine called at fw startup
            "mov    r1, %1\n"
            "mov    r0, %0\n"
            "ldr    r2, =0xe0425a71\n" // address is OK for 120a
            "blx    r2\n"              // caching related routine called at fw startup
            "mov    r0, %0\n"
            "add    r0, r0, #1\n"
            "bx     r0\n"
            : : "r"(MEMISOSTART), "r"(((blob_chdk_core_size+3)>>2)<<2), "r"(coreid) : "memory","r0","r1","r2","r3"
    );
    while(1);
}
