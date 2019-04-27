#include <stdlib.h>
#include "mgos_config_wifi_sta_mcrypt_wrapper.h"
#include "mgos_config_wifi_sta_mcrypt.h"

struct MWC {
	void *obj;
};

mgos_config_wifi_sta_mcrypt *mgos_config_wifi_sta_mcrypt_create(char* _pass)
{
	mgos_config_wifi_sta_mcrypt *m;
	McryptWifiConfig *obj;

	m      = (typeof(m))malloc(sizeof(*m));
	obj    = new McryptWifiConfig(_pass);
	m->obj = obj;

	return m;
}

void mgos_config_wifi_sta_mcrypt_destroy(mgos_config_wifi_sta_mcrypt *m)
{
	if (m == NULL)
		return;
	delete static_cast<McryptWifiConfig *>(m->obj);
	free(m);
}

/*void mgos_config_wifi_sta_mcrypt_add(mgos_config_wifi_sta_mcrypt *m, int val)
{
	McryptWifiConfig *obj;

	if (m == NULL)
		return;

	obj = static_cast<McryptWifiConfig *>(m->obj);
	obj->add(val);
}*/

char* mgos_config_wifi_sta_mcrypt_getpass(mgos_config_wifi_sta_mcrypt *m)
{
	McryptWifiConfig *obj;

	if (m == NULL)
		return 0;

	obj = static_cast<McryptWifiConfig *>(m->obj);
	return obj->getPass();
}