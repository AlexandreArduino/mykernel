#include "COM.h"

COM com;

void COM::init(uint16_t port)
{
    this->port = port;
    outb(this->port + 1, 0x00);    // Disable all interrupts
    outb(this->port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(this->port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(this->port + 1, 0x00);    //                  (hi byte)
    outb(this->port + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(this->port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(this->port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outb(this->port + 4, 0x1E);    // Set in loopback mode, test the serial chip
    outb(this->port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // inb(this->port) != 0xAE => todo if different while(1);
    if(inb(this->port) != 0xAE)
    {
        framebuffer.clear(COM_INIT_ERROR);
        while(1);
    }
    outb(this->port + 4, 0x0F);
}

int COM::received()
{
    return inb(this->port + 5) & 1;
}

char COM::read()
{
    while(!this->received());
    return inb(this->port);

}

int COM::isTransmitEmpty()
{
    return inb(this->port + 5) & 0x20;   
}

void COM::write(char c)
{
    while(!this->isTransmitEmpty());
    outb(this->port, c);
}

void COM::write(const char *str)
{
    while(*str)
    {
        this->write((char)*str);
        str++;
    }
}

void COM::writeln(const char *str)
{
    this->write(str);
    this->write('\n');
}

void COM::writeln(const char *str, size_t length)
{
    for(size_t i = 0; i < length; i++) this->write((char)str[i]);
    this->write('\n');
}