
#ifndef __WEISSOS__HARDWARECOMMUNICATION__PORT_H
#define __WEISSOS__HARDWARECOMMUNICATION__PORT_H

#include <common/types.h>

namespace weissos
{
    namespace hardwarecommunication
    {

        class Port
        {
            protected:
                Port(weissos::common::uint16_t portnumber);
                // FIXME: Must be virtual (currently isnt because the kernel has no memory management yet)
                ~Port();
                weissos::common::uint16_t portnumber;
        };

        
        class Port8Bit : public Port
        {
            public:
                Port8Bit(weissos::common::uint16_t portnumber);
                ~Port8Bit();

                virtual weissos::common::uint8_t Read();
                virtual void Write(weissos::common::uint8_t data);

            protected:
                static inline weissos::common::uint8_t Read8(weissos::common::uint16_t _port)
                {
                    weissos::common::uint8_t result;
                    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write8(weissos::common::uint16_t _port, weissos::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };



        class Port8BitSlow : public Port8Bit
        {
            public:
                Port8BitSlow(weissos::common::uint16_t portnumber);
                ~Port8BitSlow();

                virtual void Write(weissos::common::uint8_t data);
            protected:
                static inline void Write8Slow(weissos::common::uint16_t _port, weissos::common::uint8_t _data)
                {
                    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
                }

        };



        class Port16Bit : public Port
        {
            public:
                Port16Bit(weissos::common::uint16_t portnumber);
                ~Port16Bit();

                virtual weissos::common::uint16_t Read();
                virtual void Write(weissos::common::uint16_t data);

            protected:
                static inline weissos::common::uint16_t Read16(weissos::common::uint16_t _port)
                {
                    weissos::common::uint16_t result;
                    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write16(weissos::common::uint16_t _port, weissos::common::uint16_t _data)
                {
                    __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
                }
        };



        class Port32Bit : public Port
        {
            public:
                Port32Bit(weissos::common::uint16_t portnumber);
                ~Port32Bit();

                virtual weissos::common::uint32_t Read();
                virtual void Write(weissos::common::uint32_t data);

            protected:
                static inline weissos::common::uint32_t Read32(weissos::common::uint16_t _port)
                {
                    weissos::common::uint32_t result;
                    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
                    return result;
                }

                static inline void Write32(weissos::common::uint16_t _port, weissos::common::uint32_t _data)
                {
                    __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
                }
        };

    }
}


#endif