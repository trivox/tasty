#ifndef _UART_HPP_
#define _UART_HPP_

#include <stdint.h>

// The GPIO registers base address.
constexpr uint32_t GPIO_BASE = 0x3F200000; // for raspi2 & 3, 0x20200000 for raspi1

// The offsets for reach register.

// Controls actuation of pull up/down to ALL GPIO pins.
constexpr uint32_t GPPUD = (GPIO_BASE + 0x94);

// Controls actuation of pull up/down for specific GPIO pin.
constexpr uint32_t GPPUDCLK0 = (GPIO_BASE + 0x98);

// The base address for UART.
constexpr uint32_t UART0_BASE = 0x3F201000; // for raspi2 & 3, 0x20201000 for raspi1

// The offsets for reach register for the UART.
constexpr uint32_t UART0_DR     = (UART0_BASE + 0x00);
constexpr uint32_t UART0_RSRECR = (UART0_BASE + 0x04);
constexpr uint32_t UART0_FR     = (UART0_BASE + 0x18);
constexpr uint32_t UART0_ILPR   = (UART0_BASE + 0x20);
constexpr uint32_t UART0_IBRD   = (UART0_BASE + 0x24);
constexpr uint32_t UART0_FBRD   = (UART0_BASE + 0x28);
constexpr uint32_t UART0_LCRH   = (UART0_BASE + 0x2C);
constexpr uint32_t UART0_CR     = (UART0_BASE + 0x30);
constexpr uint32_t UART0_IFLS   = (UART0_BASE + 0x34);
constexpr uint32_t UART0_IMSC   = (UART0_BASE + 0x38);
constexpr uint32_t UART0_RIS    = (UART0_BASE + 0x3C);
constexpr uint32_t UART0_MIS    = (UART0_BASE + 0x40);
constexpr uint32_t UART0_ICR    = (UART0_BASE + 0x44);
constexpr uint32_t UART0_DMACR  = (UART0_BASE + 0x48);
constexpr uint32_t UART0_ITCR   = (UART0_BASE + 0x80);
constexpr uint32_t UART0_ITIP   = (UART0_BASE + 0x84);
constexpr uint32_t UART0_ITOP   = (UART0_BASE + 0x88);
constexpr uint32_t UART0_TDR    = (UART0_BASE + 0x8C);

#endif // _UART_HPP_
