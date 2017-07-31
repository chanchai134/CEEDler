#include <Wire.h>
#include <UnoWiFiDevEd.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
String tripleZ_network_Group = "chat";
CiaoData data;
void tripleZ_network_strat()
{
	Ciao.begin();
}
void tripleZ_network_sendtext(String topic, String text)
{
	data = Ciao.write(CONNECTOR, SERVER_ADDR, "/data/" + tripleZ_network_Group + "/" + topic + "/set/" + text);
	/*
	if (data.isEmpty())
	{
		Serial.println("Send Failed");
		Ciao.println("Write Failed");
	}
	else
	{
		Serial.println("Send Success");
	}
	*/
}
String tripleZ_network_readtext(String topic)
{
	data = Ciao.read(CONNECTOR, SERVER_ADDR, "/data/" + tripleZ_network_Group + "/" + topic);
	/*
	if (data.isEmpty())
	{
		return "Empty";
	}
	else
	{
		return String(data.get(2));
	}
	*/
	return String(data.get(2));
}