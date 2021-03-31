#ifndef __PORT_H_
#define __PORT_H_

#include"types.h"

class Port {
protected:
    u16 portNo;

    Port(u16 portNo);

    ~Port();

};

class Port8Bit : public Port {
public:
    Port8Bit(u16 portNo);

    ~Port8Bit();

    void write(u8 data);

    u8 read();


};

class Port8BitSlow : public Port8Bit {
public:
    Port8BitSlow(u16 portNo);

    ~Port8BitSlow();

    void write(u8 data);

    u8 read();


};


class Port16Bit : public Port {
public:
    Port16Bit(u16 portNo);

    ~Port16Bit();

    void write(u16 data);

    u16 read();


};


class Port32Bit : public Port {
public:
    Port32Bit(u16 portNo);

    ~Port32Bit();

    void write(u32 data);

    u32 read();


};


#endif
