#include "hal.h"
#include <stdint.h>
#include <string.h>
#include "simpleserial.h"

#define KEY_LENGTH 20

static const char master_key[KEY_LENGTH] = "REDACTED";

uint8_t authenticate(uint8_t* incoming_key, uint8_t len)
{
    
    volatile uint8_t acc = 0;
    uint8_t mismatch_flag = 0;
    
    trigger_high();
    
    for (uint8_t i = 0; i < KEY_LENGTH; i++) {
        uint8_t diff = incoming_key[i] ^ master_key[i];
        uint8_t is_match = (diff == 0);
        acc += is_match * (i * 7 + 3);      
        mismatch_flag |= diff;               
    }
    
    trigger_low();

    simpleserial_put('r',1,&mismatch_flag);
    
    return 0x00;
}

int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();
    simpleserial_init();
    
    simpleserial_addcmd('a', KEY_LENGTH, authenticate);

    while(1) {
        simpleserial_get();
    }
    return 0;
}

