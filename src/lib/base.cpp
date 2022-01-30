#include "base.h"

// < 0 numbers are not supported yet 

char Library::conversion_output[256];

const char *String(uint64_t value, uint8_t base)
{
    switch(base)
    {
        case BINARY: return BinaryString(value);
        case DECIMAL: return DecimalString(value);
        case HEXADECIMAL: return HexadecimalString(value);
        default:
            log.log("base.String() => error base not supported ! => ");
            log.log(DecimalString(base));
            log.log("\n");
            return "";
    }
}

const char *DecimalString(uint64_t value)
{
    uint8_t size = 0;
    uint64_t sizeTest = value;
    while(sizeTest / DECIMAL > 0)
    {
        sizeTest /= 10;
        size++;   
    }
    uint8_t index = 0;
    while(value / DECIMAL > 0)
    {
        uint8_t remainder = value % DECIMAL;
        value /= DECIMAL;
        Library::conversion_output[size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % DECIMAL;
    Library::conversion_output[size - index] = remainder + '0';
    Library::conversion_output[size + 1] = 0;
    return Library::conversion_output;
}

const char *HexadecimalString(uint64_t value)
{
    uint64_t *ValuePtr = &value;
    uint8_t *ptr;
    uint8_t tmp;
    uint8_t size = 8 * 2 - 1;
    for(uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)ValuePtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        Library::conversion_output[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        Library::conversion_output[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    Library::conversion_output[size + 1] = 0;
    return Library::conversion_output;
}

const char *BinaryString(uint64_t value)
{
    uint8_t size = 0;
    uint64_t sizeTest = value;
    while(sizeTest / BINARY > 0)
    {
        sizeTest /= 10;
        size++;   
    }
    uint8_t index = 0;
    while(value / BINARY > 0)
    {
        uint8_t remainder = value % BINARY;
        value /= BINARY;
        Library::conversion_output[size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % BINARY;
    Library::conversion_output[size - index] = remainder + '0';
    Library::conversion_output[size + 1] = 0;
    return Library::conversion_output;
}

const char *FloatString(float value)
{
    return "Conversion not possible for now!";
}