#ifndef _DEBUGGER_HPP_
#define _DEBUGGER_HPP_

#include <cpustate.hpp>

namespace tasty_debug {

    class debugger_t {
        public:
            debugger_t();
            void uart_puts(const char * str); // send string to UART
            void endless() { while (1) uart_putc(uart_getc()); }
            ~debugger_t(){};
        private:
            tasty_kernel::cpustate_t registers;// for testing
            void uart_putc(unsigned char c); // send symbol to UART
            unsigned char uart_getc();       // get symbol from UART
    }; // class debugger_t

} // namespace tasty_debug

#endif // _DEBUGGER_HPP_
