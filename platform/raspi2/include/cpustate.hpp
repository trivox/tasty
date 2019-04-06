#ifndef _ARM_CPUSTATE_HPP_
#define _ARM_CPUSTATE_HPP_

#include <stdint.h>

namespace tasty_kernel {

    class cpustate_t
    {
        public:
            inline void pull(); // save cpu state to this
            inline void push(); // load this state to cpu
        private:
            struct cpustate_raw; // platform dependent
    }; // class cpustate


    // platform-dependent components of cpustate.hpp
    struct cpustate_raw
    {
        uint32_t retreg;                 //  r0
        uint32_t r1;
        uint32_t r2;
        uint32_t r3;
        uint32_t r4;
        uint32_t r5;
        uint32_t r6;
        uint32_t r7;
        uint32_t r8;
        uint32_t r9;                     //  sb
        uint32_t r10;                    //  sl
        uint32_t fp;                     //  r11
        uint32_t r12;                    //  ip
        uint32_t sp;                     //  r13
        uint32_t lr;                     //  r14
        uint32_t pc;                     //  r15
        uint32_t psr;
    };

    // save cpu state to this
    inline void cpustate_t::pull()
    {
    }

    // load this state to cpu
    inline void cpustate_t::push()
    {
    }

} // namespace tasty_kernel

#endif // _ARM_CPUSTATE_HPP_
