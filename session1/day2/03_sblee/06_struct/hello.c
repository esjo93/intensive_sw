// hello.c
#include <stdio.h>

void mem_inspection(unsigned char* p, int N) {
    for(int i=0;i<N;i++)
        printf("mem[%d] is 0x%02X at %p\n", i, *(p+i), p+i);
}
void main() {
    struct bits_8 {
        unsigned char b0 : 1;
        unsigned char b1 : 1;
        unsigned char b2 : 1;
        unsigned char b3 : 1;
        unsigned char b4 : 1;
        unsigned char b5 : 1;
        unsigned char b6 : 1;
        unsigned char b7 : 1;
    };
    struct ADC_CONFIG {
        unsigned char CNFG1;
        unsigned char CNFG2;
        unsigned short MODE;
    };
    union flag_16bits {
        unsigned char bytes[2];
        struct bits_8 b8[2];
        unsigned short bits16;
    };
    struct ADC_CONFIG adc1 = {0x01, 0x80, 0xF000};
    printf("CNFG1: 0x%02X\n", adc1.CNFG1);
    printf("CNFG2: 0x%02X\n", adc1.CNFG2);
    printf("MODE: 0x%04X\n", adc1.MODE);

    unsigned char* adc_p = (unsigned char*)&adc1;
    mem_inspection(adc_p, sizeof(adc1));

    *(adc_p+1) = 0x5A; // write CNFG2;
    printf("CNFG2: 0x%02X\n", adc1.CNFG2);

    struct bits_8 bytes;
    printf("struct bits_8 is allocated with %ld bytes\n", sizeof(bytes));

    unsigned char b8 = 0xB;
    //b8 = 0X80; // try to set MSB; --> overwrite all-->error
    b8 |= 0x80;
    printf("bytes: %02X\n", b8);

    union flag_16bits flag16;
    printf("flag16 is with %ld bytes\n", sizeof(flag16));

    flag16.bits16 = 0xF005;
    printf("flag16 is 0x%02X%02X\n", flag16.bytes[1], flag16.bytes[0]);
}

