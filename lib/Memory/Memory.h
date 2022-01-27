#ifndef __TIMER_MEMORY__
#define __TIMER_MEMORY__

#include <Arduino.h>
#include <EEPROM.h>

#define WRITE_ADDR 0xA0 //?
#define READ_ADDR 0xA1  //?

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

class Memory
{
    u8 data, p;
    u16 writeAddr, readAddr;

public:
    void writeData(u8 data);
    void writeData(u8 data, u8 _addr);
    void writeData(u16 _addr, u16 len, u8 *_p);
    u8 readData(void);
    u8 readData(u16 _addr);
    void readData(u16 _addr, u16 len, u8 *_p);
};

#endif