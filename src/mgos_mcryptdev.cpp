#include "mgos_mcryptdev.h"

bool mgos_mcryptdev_init(void) {
    return true;
}

int add(int a, int b){
    return a + b;
}

// "Converting structs to objects"
// "https://github.com/cesanta/mjs"


uint8_t generateRandom32(){
    uint8_t* random_number = (uint8_t*) malloc(sizeof(uint8_t[32]));
    //*random_number = 32;
    //uint8_t* random_number = new uint8_t;
    //uint8_t random_number[32];
    atcab_init(&cfg_ateccx08a_i2c_default);
    atcab_random(random_number);
    //return (int) random_number;
    return *random_number;
}

int generateRandom(){
    return (int) generateRandom32();
    //return 255;
    //RandomGenerator rg;
    //return rg.random8();
}




