#ifndef __MGOS_CONFIG_WIFI_STA_MCRYPT_H__
#define __MGOS_CONFIG_WIFI_STA_MCRYPT_H__

class McryptWifiConfig
{
	public:
		McryptWifiConfig(char* _pass);
		//void add(int val);
		char* getPass();

	private:
		//int value;
        char* pass;
};

#endif // __MGOS_CONFIG_WIFI_STA_MCRYPT_H__