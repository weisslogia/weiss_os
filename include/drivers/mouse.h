
#ifndef __WEISSOS__DRIVERS__MOUSE_H
#define __WEISSOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace weissos
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(weissos::common::uint8_t button);
            virtual void OnMouseUp(weissos::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public weissos::hardwarecommunication::InterruptHandler, public Driver
        {
            weissos::hardwarecommunication::Port8Bit dataport;
            weissos::hardwarecommunication::Port8Bit commandport;
            weissos::common::uint8_t buffer[3];
            weissos::common::uint8_t offset;
            weissos::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(weissos::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual weissos::common::uint32_t HandleInterrupt(weissos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif