
#include "mgos_mcryptdev.h"
//#include "mgos_config_wifi_sta_mcrypt_wrapper.h"


#include <string.h>
#if defined(_MSC_VER) && _MSC_VER < 1600
typedef unsigned __int8 uint8_t;
typedef unsigned __int32 uint32_t;
#else
    #include <stdint.h>
#endif

#include <sys/types.h> /* This will likely define BYTE_ORDER */

#define LITTLE_ENDIAN   1234    /* least-significant byte first (vax, pc) */
#define BIG_ENDIAN  4321    /* most-significant byte first (IBM, net) */
#define PDP_ENDIAN  3412 

#define BYTE_ORDER    LITTLE_ENDIAN

#ifndef BYTE_ORDER
#ifdef __BYTE_ORDER
#if defined(__LITTLE_ENDIAN) && defined(__BIG_ENDIAN)
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN __LITTLE_ENDIAN
#endif
#ifndef BIG_ENDIAN
#define BIG_ENDIAN __BIG_ENDIAN
#endif
#if (__BYTE_ORDER == __LITTLE_ENDIAN)
#define BYTE_ORDER LITTLE_ENDIAN
#else
#define BYTE_ORDER BIG_ENDIAN
#endif
#endif
#endif
#endif

#define MX (((z >> 5) ^ (y << 2)) + ((y >> 3) ^ (z << 4))) ^ ((sum ^ y) + (key[(p & 3) ^ e] ^ z))
#define DELTA 0x9e3779b9

#define FIXED_KEY \
    size_t i;\
    uint8_t fixed_key[16];\
    memcpy(fixed_key, key, 16);\
    for (i = 0; (i < 16) && (fixed_key[i] != 0); ++i);\
    for (++i; i < 16; ++i) fixed_key[i] = 0;\


static uint32_t * xxtea_to_uint_array(const uint8_t * data, size_t len, int inc_len, size_t * out_len) {
    uint32_t *out;
#if !(defined(BYTE_ORDER) && (BYTE_ORDER == LITTLE_ENDIAN))
    size_t i;
#endif
    size_t n;

    n = (((len & 3) == 0) ? (len >> 2) : ((len >> 2) + 1));

    if (inc_len) {
        out = (uint32_t *)calloc(n + 1, sizeof(uint32_t));
        if (!out) return NULL;
        out[n] = (uint32_t)len;
        *out_len = n + 1;
    }
    else {
        out = (uint32_t *)calloc(n, sizeof(uint32_t));
        if (!out) return NULL;
        *out_len = n;
    }
#if defined(BYTE_ORDER) && (BYTE_ORDER == LITTLE_ENDIAN)
    memcpy(out, data, len);
#else
    for (i = 0; i < len; ++i) {
        out[i >> 2] |= (uint32_t)data[i] << ((i & 3) << 3);
    }
#endif

    return out;
}

static uint8_t * xxtea_to_ubyte_array(const uint32_t * data, size_t len, int inc_len, size_t * out_len) {
    uint8_t *out;
#if !(defined(BYTE_ORDER) && (BYTE_ORDER == LITTLE_ENDIAN))
    size_t i;
#endif
    size_t m, n;

    n = len << 2;

    if (inc_len) {
        m = data[len - 1];
        n -= 4;
        if ((m < n - 3) || (m > n)) return NULL;
        n = m;
    }

    out = (uint8_t *)malloc(n + 1);

#if defined(BYTE_ORDER) && (BYTE_ORDER == LITTLE_ENDIAN)
    memcpy(out, data, n);
#else
    for (i = 0; i < n; ++i) {
        out[i] = (uint8_t)(data[i >> 2] >> ((i & 3) << 3));
    }
#endif

    out[n] = '\0';
    *out_len = n;

    return out;
}

static uint32_t * xxtea_uint_encrypt(uint32_t * data, size_t len, uint32_t * key) {
    uint32_t n = (uint32_t)len - 1;
    uint32_t z = data[n], y, p, q = 6 + 52 / (n + 1), sum = 0, e;

    if (n < 1) return data;

    while (0 < q--) {
        sum += DELTA;
        e = sum >> 2 & 3;

        for (p = 0; p < n; p++) {
            y = data[p + 1];
            z = data[p] += MX;
        }

        y = data[0];
        z = data[n] += MX;
    }

    return data;
}

static uint32_t * xxtea_uint_decrypt(uint32_t * data, size_t len, uint32_t * key) {
    uint32_t n = (uint32_t)len - 1;
    uint32_t z, y = data[0], p, q = 6 + 52 / (n + 1), sum = q * DELTA, e;

    if (n < 1) return data;

    while (sum != 0) {
        e = sum >> 2 & 3;

        for (p = n; p > 0; p--) {
            z = data[p - 1];
            y = data[p] -= MX;
        }

        z = data[n];
        y = data[0] -= MX;
        sum -= DELTA;
    }

    return data;
}

static uint8_t * xxtea_ubyte_encrypt(const uint8_t * data, size_t len, const uint8_t * key, size_t * out_len) {
    uint8_t *out;
    uint32_t *data_array, *key_array;
    size_t data_len, key_len;

    if (!len) return NULL;

    data_array = xxtea_to_uint_array(data, len, 1, &data_len);
    if (!data_array) return NULL;

    key_array  = xxtea_to_uint_array(key, 16, 0, &key_len);
    if (!key_array) {
        free(data_array);
        return NULL;
    }

    out = xxtea_to_ubyte_array(xxtea_uint_encrypt(data_array, data_len, key_array), data_len, 0, out_len);

    free(data_array);
    free(key_array);

    return out;
}

static uint8_t * xxtea_ubyte_decrypt(const uint8_t * data, size_t len, const uint8_t * key, size_t * out_len) {
    uint8_t *out;
    uint32_t *data_array, *key_array;
    size_t data_len, key_len;

    if (!len) return NULL;

    data_array = xxtea_to_uint_array(data, len, 0, &data_len);
    if (!data_array) return NULL;

    key_array  = xxtea_to_uint_array(key, 16, 0, &key_len);
    if (!key_array) {
        free(data_array);
        return NULL;
    }

    out = xxtea_to_ubyte_array(xxtea_uint_decrypt(data_array, data_len, key_array), data_len, 1, out_len);

    free(data_array);
    free(key_array);

    return out;
}

// public functions

void * encrypt(const void * data, size_t len, size_t * out_len) {
    const char* device_key = "eOe+jn5rHZ2oNKIiY2I4mxZgsfucSJM97Rd/eFis9HU=";
    return xxtea_ubyte_encrypt((const uint8_t *)data, len, (const uint8_t *) device_key, out_len);
}

void * decrypt(const void * data, size_t len, size_t * out_len) {
    const char* device_key = "eOe+jn5rHZ2oNKIiY2I4mxZgsfucSJM97Rd/eFis9HU=";
    return xxtea_ubyte_decrypt((const uint8_t *)data, len, (const uint8_t *) device_key, out_len);
}

bool mgos_mcryptdev_init(void) {
    return true;
}


