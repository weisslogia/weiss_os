#include "types.h"
#include "gdt.h"

void printf(char* str) {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    static uint8_t x = 0, y = 0;
    for(int i = 0; str[i] != '\0'; ++i) {
        switch(str[i]) {
            case '\n':
                x = 0;
                y++;
                break;
            default: 
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
        }
        if(x >= 80) {
            x = 0;
            y++;
        }
        if(y >=25) {
            for(y = 0; y < 25; y++) {
                for(x = 0; x < 80; x++) {
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
                }
            }
            x=0;
            y=0;
        }
    }
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callContructors() {
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
    printf("Hello World from os");
    printf("\nHello World from os line 2");
    GlobalDescriptorTable gdt;
    while(1);
}

// VIDEO #5 URL https://www.youtube.com/watch?v=AgeX-U4dKSs&list=PLHh55M_Kq4OApWScZyPl5HhgsTJS9MZ6M&index=6