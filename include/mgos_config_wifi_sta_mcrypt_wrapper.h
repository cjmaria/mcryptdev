#ifndef __MGOS_CONFIG_WIFI_STA_MCRYPT_WRAPPER_H__
#define __MGOS_CONFIG_WIFI_STA_MCRYPT_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

struct MWC;
typedef struct MWC mgos_config_wifi_sta_mcrypt;

mgos_config_wifi_sta_mcrypt *mgos_config_wifi_sta_mcrypt_create(char* _pass);
void mgos_config_wifi_sta_mcrypt_destroy(mgos_config_wifi_sta_mcrypt *m);

//void mgos_config_wifi_sta_mcrypt_add(mgos_config_wifi_sta_mcrypt *m, int val);
char* mgos_config_wifi_sta_mcrypt_getpass(mgos_config_wifi_sta_mcrypt *m);

#ifdef __cplusplus
}
#endif

#endif /* __MGOS_CONFIG_WIFI_STA_MCRYPT_WRAPPER_H__ */