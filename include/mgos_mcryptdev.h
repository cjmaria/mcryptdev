#ifndef CS_MOS_LIBS_MCRYPTDEV_SRC_MGOS_MCRYPTDEV_H_
#define CS_MOS_LIBS_MCRYPTDEV_SRC_MGOS_MCRYPTDEV_H_

#include <stdbool.h>
#include <stdlib.h>



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Function: encrypt
 * data:     Data to be encrypted
 * len:      Length of the data to be encrypted
 * key:      Symmetric key
 * out_len:  Pointer to output length variable
 * Returns:  Encrypted data or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer.
 */
void * encrypt(const void * data, size_t len, const void * key, size_t * out_len);

/**
 * Function: decrypt
 * data:     Data to be decrypted
 * len:      Length of the data to be decrypted
 * key:      Symmetric key
 * out_len:  Pointer to output length variable
 * Returns:  Decrypted data or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer.
 */
void * decrypt(const void * data, size_t len, const void * key, size_t * out_len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_MOS_LIBS_MCRYPTDEV_SRC_MGOS_MCRYPTDEV_H_ */
