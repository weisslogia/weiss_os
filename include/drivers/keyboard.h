
#ifndef __WEISSOS__DRIVERS__KEYBOARD_H
#define __WEISSOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace weissos
{
    namespace drivers
    {
    
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
        class KeyboardDriver : public weissos::hardwarecommunication::InterruptHandler, public Driver
        {
            weissos::hardwarecommunication::Port8Bit dataport;
            weissos::hardwarecommunication::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(weissos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual weissos::common::uint32_t HandleInterrupt(weissos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif