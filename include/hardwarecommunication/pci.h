
#ifndef __WEISSOS__HARDWARECOMMUNICATION__PCI_H
#define __WEISSOS__HARDWARECOMMUNICATION__PCI_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace weissos
{
    namespace hardwarecommunication
    {
        enum BaseAddressRegisterType {
            MemoryMapping = 0,
            InputOutput = 1
        };

        class BaseAddressRegister {
            public:
                bool prefetchable;
                weissos::common::uint8_t* address;
                weissos::common::uint32_t size;
                BaseAddressRegisterType type;
                // BaseAddressRegister();
                // ~BaseAddressRegister();
        };

        class PeripheralComponentInterconnectDeviceDescriptor {
            public:
                weissos::common::uint32_t portBase;
                weissos::common::uint32_t interrupt;
                
                weissos::common::uint16_t bus;
                weissos::common::uint16_t device;
                weissos::common::uint16_t function;

                weissos::common::uint16_t vendor_id;
                weissos::common::uint16_t device_id;

                weissos::common::uint8_t class_id;
                weissos::common::uint8_t subclass_id;
                weissos::common::uint8_t interface_id;
                
                weissos::common::uint16_t revision;
                PeripheralComponentInterconnectDeviceDescriptor();
                ~PeripheralComponentInterconnectDeviceDescriptor();
        };

        class PeripheralComponentInterconnectController {
            Port32Bit dataPort;
            Port32Bit commandPort;
            public:
                PeripheralComponentInterconnectController();
                ~PeripheralComponentInterconnectController();
                weissos::common::uint32_t Read(weissos::common::uint16_t bus, weissos::common::uint16_t device, weissos::common::uint16_t function, weissos::common::uint32_t registeroffset);
                void Write(weissos::common::uint16_t bus, weissos::common::uint16_t device, weissos::common::uint16_t function, weissos::common::uint32_t registeroffset, weissos::common::uint32_t value);
                bool DeviceHasFunctions(weissos::common::uint16_t bus, weissos::common::uint16_t device);
                void SelectDrivers(weissos::drivers::DriverManager* driverManager, weissos::hardwarecommunication::InterruptManager* interrupts);
                weissos::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, weissos::hardwarecommunication::InterruptManager* interrupts);
                PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(weissos::common::uint16_t bus, weissos::common::uint16_t device, weissos::common::uint16_t function);
                BaseAddressRegister GetBaseAddressRegister(weissos::common::uint16_t bus, weissos::common::uint16_t device, weissos::common::uint16_t function, weissos::common::uint16_t bar);
        };
    }
}

#endif