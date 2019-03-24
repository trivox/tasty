#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <stdint.h>

// Memory-Mapped I/O output
static inline void addr_write(uint32_t reg, uint32_t data)
{
	*(volatile uint32_t*)reg = data;
}

// Memory-Mapped I/O input
static inline uint32_t addr_read(uint32_t reg)
{
	return *(volatile uint32_t*)reg;
}

// Loop <delay> times in a way that the compiler won't optimize away
static inline void hard_delay(int32_t count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}

#endif // _UTILITY_HPP_
