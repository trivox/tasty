#include <stddef.h>

#include <utility.hpp>
#include <debugger.hpp>

const char str[] = "Hello, kernel world!\n";

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    // Declare as unused
    (void) r0;
    (void) r1;
    (void) atags;

    tasty_debug::debugger_t deb;
    deb.uart_puts(str);
    deb.endless();
}

