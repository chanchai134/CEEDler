#include <triplez_network.h>
#include <lightAndSound_libV3.h>
#include <servotriplez_lib.h>
#define DURATION_LIGHT 30
#define DURATION_TV 30
int sound_Max;
int light_Max;
void setup() {
  //Serial.begin(9600);
  tripleZ_network_strat();
  lightAndSound_strat();
  certain_start();
}
void loop() {
  light_Max = tripleZ_network_readtext("ceedlerOutRangeLight").toInt();
  //Serial.println("Light Range : "+tripleZ_network_readtext("ceedlerOutRangeLight"));
  ///////////////////////////////////////////////////////////////////
  String light_stat = tripleZ_network_readtext("ceedlerOutLight");
  //Serial.println("Light Status : "+light_stat);
  if(light_stat == "increase" && light_Max == 0)
  {
    lightAndSound_increase(DURATION_LIGHT,255,"light");
  }
  else if(light_stat == "increase")
  {
    lightAndSound_increase(DURATION_LIGHT,light_Max,"light");
  }
  else if(light_stat == "decrease")
  {
    lightAndSound_decrease(DURATION_LIGHT,0,"light");
  }
  else if(light_stat == "on")
  {
    lightAndSound_on(light_Max,"light");
  }
  else if(light_stat == "off")
  {
    lightAndSound_off("light");
  }
  ///////////////////////////////////////////////////////////////////
  sound_Max = tripleZ_network_readtext("ceedlerOutRangeTV").toInt();
  //Serial.println("TV Level : "+tripleZ_network_readtext("ceedlerOutRangeTV"));
  ///////////////////////////////////////////////////////////////////
  String TV_stat = tripleZ_network_readtext("ceedlerOutTV");
  //Serial.println("TV Status : "+TV_stat);
  if(TV_stat == "increase")
  {
    lightAndSound_increase(DURATION_TV,sound_Max,"TV");
  }
  else if(TV_stat == "decrease")
  {
    lightAndSound_decrease(DURATION_TV,0,"TV");
  }
  else if(TV_stat == "on")
  {
    lightAndSound_on(sound_Max,"TV");
  }
  else if(TV_stat == "off")
  {
    lightAndSound_off("TV");
  }
  ///////////////////////////////////////////////////////////////////
  String certain_stat = tripleZ_network_readtext("ceedlerOutCT");
  //Serial.println("Certain : "+certain_stat);
  if(certain_stat == "on")
  {
    certain_change(certain_stat);
  }
  else if(certain_stat == "off")
  {
    certain_change(certain_stat);
  }
  ///////////////////////////////////////////////////////////////////
  delay(300);
}
