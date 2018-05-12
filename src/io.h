#define cli asm("cli"::) // Clear interruptions
#define sti asm("sti"::) // Rearm the interruptions

// Write a byte on a port
#define outb(port, value)\
        asm volatile ("outb %%al, %%dx" :: "d" (port), "a" (value));

// Write a byte on a port and wait
#define outbp(port,value) \
	asm volatile ("outb %%al, %%dx; jmp 1f; 1:" :: "d" (port), "a" (value));

// Read a byte from a port
#define inb(port) ({    \
	unsigned char _v;       \
	asm volatile ("inb %%dx, %%al" : "=a" (_v) : "d" (port)); \
        _v;     \
})

