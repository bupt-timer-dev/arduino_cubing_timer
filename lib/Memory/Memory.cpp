#include "Memory.h"
#include <Arduino.h>
#include <EEPROM.h>


/*
函数功能: (指定位置)写入(指定数量)的数据
函数参数:
    data:写入的字节数据
    _addr: 写数据的地址或从哪里开始写数据
    len : 写入多长的数据
    *p  : 存放数据的缓冲区
*/
void Memory::writeData(u8 data)
{
    EEPROM.write(writeAddr, data);
    writeAddr++;
    if (writeAddr == 512)
        writeAddr = 0;
}

void Memory::writeData(u8 data, u8 _addr)
{
    EEPROM.write(_addr, data);
}

void Memory::writeData(u16 _addr, u16 len, u8 *p)
{
    writeAddr = _addr;
    while (len--)
    {
        if (writeAddr == 512)
            writeAddr = 0;
        EEPROM.write(writeAddr, *p);
        writeAddr++, p++;
    }
}

/*
函数功能: (指定位置)读取(指定数量)的数据
函数参数:
    _addr: 从哪里开始读取数据
    len : 读取多长的数据
    *p  : 存放数据的缓冲区
*/
u8 Memory::readData()
{
    u8 data = EEPROM.read(readAddr);

    Serial.print(readAddr);
    Serial.print("\t");
    Serial.print(data, DEC);
    Serial.println();

    readAddr++;
    if (readAddr == 512)
        readAddr = 0;

    return data;
}

u8 Memory::readData(u16 _addr)
{
    readAddr = _addr;
    u8 data = EEPROM.read(readAddr);

    Serial.print(readAddr);
    Serial.print("\t");
    Serial.print(data, DEC);
    Serial.println();

    readAddr++;
    if (readAddr == 512)
        readAddr = 0;

    return data;
}

void Memory::readData(u16 _addr, u16 len, u8 *p)
{
    readAddr = _addr;
    
    while (len--)
    {
        if (readAddr == 512)
            readAddr = 0;

        u8 data = EEPROM.read(readAddr);
        *p = data;

        Serial.print(readAddr);
        Serial.print("\t");
        Serial.print(data, DEC);
        Serial.println();

        ++readAddr, ++p;
    }
}

