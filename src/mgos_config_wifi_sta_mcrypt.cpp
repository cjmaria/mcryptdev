#include "mgos_config_wifi_sta_mcrypt.h"

McryptWifiConfig::McryptWifiConfig(char* _pass)
{
	pass = _pass;
}

/*void McryptWifiConfig::add(int val)
{
	value += val;
}*/

char* McryptWifiConfig::getPass()
{
	return pass;
}