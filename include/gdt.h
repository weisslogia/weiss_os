#ifndef __WEISSOS__GDT_H
#define __WEISSOS__GDT_H

#include <common/types.h>

namespace weissos
{
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    weissos::common::uint16_t limit_lo;
                    weissos::common::uint16_t base_lo;
                    weissos::common::uint8_t base_hi;
                    weissos::common::uint8_t type;
                    weissos::common::uint8_t limit_hi;
                    weissos::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(weissos::common::uint32_t base, weissos::common::uint32_t limit, weissos::common::uint8_t type);
                    weissos::common::uint32_t Base();
                    weissos::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            weissos::common::uint16_t CodeSegmentSelector();
            weissos::common::uint16_t DataSegmentSelector();
    };

}
    
#endif