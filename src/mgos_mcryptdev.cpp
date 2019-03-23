#include "mgos_mcryptdev.h"

bool mgos_mcryptdev_init(void) {
    return true;
}

int add(int a, int b){
    return a + b;
}

// "Converting structs to objects"
// "https://github.com/cesanta/mjs"

struct uintLayers {
  int8_t i8;
  int16_t i16;
  uint8_t u8;
  uint16_t u16;
};

/*
static const struct mjs_c_struct_member mjsUintInterface[] = {
  {"i8", offsetof(struct uintLayers, i8), MJS_STRUCT_FIELD_TYPE_INT8, NULL},
  {"i16", offsetof(struct uintLayers, i16), MJS_STRUCT_FIELD_TYPE_INT16, NULL},
  {"u8", offsetof(struct uintLayers, u8), MJS_STRUCT_FIELD_TYPE_UINT8, NULL},
  {"u16", offsetof(struct uintLayers, u16), MJS_STRUCT_FIELD_TYPE_UINT16, NULL},
  {NULL, 0, MJS_STRUCT_FIELD_TYPE_INVALID, NULL},
};

const struct mjs_c_struct_member *getMjsUintInterface(void) {
  return mjsUintInterface;
};*/

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
/*

RandomGenerator::RandomGenerator(){
    uint8 = (uint8_t*) malloc(sizeof(uint8_t));
}*/
void RandomGenerator::destroy(){
    delete uint8;
}
/*
RandomGenerator::~RandomGenerator(){
    destroy();
}
*/
int RandomGenerator::random8(){
    atcab_init(&cfg_ateccx08a_i2c_default);
    atcab_random(uint8);
    return (int) *uint8;
}





