#ifndef CS_MOS_LIBS_MCRYPTDEV_SRC_MCRYPTDEV_H_
#define CS_MOS_LIBS_MCRYPTDEV_SRC_MCRYPTDEV_H_

#include <stdbool.h>
#include <stdlib.h>
#include "cryptoauthlib.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

bool mgos_mcryptdev_init(void);

int add(int a, int b);
uint8_t generateRandom32();
int generateRandom();
/*
class RandomGenerator{
public:
    RandomGenerator();
    ~RandomGenerator();
    void destroy();
    uint8_t random8();

private:
    uint8_t* uint8;
};
*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_MOS_LIBS_MCRYPTDEV_SRC_MCRYPTDEV_H_ */
