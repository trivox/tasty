#include <debugger.hpp>

#include <stddef.h>

#include <utility.hpp>
#include <uart.hpp>

using namespace tasty_debug;

// private

debugger_t::debugger_t()
{
    // Disable UART0.
	addr_write(UART0_CR, 0x00000000);
	// Setup the GPIO pin 14 && 15.

	// Disable pull up/down for all GPIO pins & delay for 150 cycles.
	addr_write(GPPUD, 0x00000000);
	hard_delay(150);

	// Disable pull up/down for pin 14,15 & delay for 150 cycles.
	addr_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	hard_delay(150);

	// Write 0 to GPPUDCLK0 to make it take effect.
	addr_write(GPPUDCLK0, 0x00000000);

	// Clear pending interrupts.
	addr_write(UART0_ICR, 0x7FF);

	// Set integer & fractional part of baud rate.
	// Divider = UART_CLOCK/(16 * Baud)
	// Fraction part register = (Fractional part * 64) + 0.5
	// UART_CLOCK = 3000000; Baud = 115200.

	// Divider = 3000000 / (16 * 115200) = 1.627 = ~1.
	addr_write(UART0_IBRD, 1);
	// Fractional part register = (.627 * 64) + 0.5 = 40.6 = ~40.
	addr_write(UART0_FBRD, 40);

	// Enable FIFO & 8 bit data transmissio (1 stop bit, no parity).
	addr_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

	// Mask all interrupts.
	addr_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	                       (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

	// Enable UART0, receive & transfer part of UART.
	addr_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void debugger_t::uart_putc(unsigned char c)
{
    // Wait for UART to become ready to transmit.
	while ( addr_read(UART0_FR) & (1 << 5) ) { }
	addr_write(UART0_DR, c);
}

unsigned char debugger_t::uart_getc()
{
    // Wait for UART to have received something.
    while ( addr_read(UART0_FR) & (1 << 4) ) { }
    return addr_read(UART0_DR);
}

// public
void debugger_t::uart_puts(const char * str)
{
    for (size_t i = 0; str[i] != '\0'; i ++)
		uart_putc((unsigned char)str[i]);
}

