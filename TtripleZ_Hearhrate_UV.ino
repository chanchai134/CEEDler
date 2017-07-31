#include <triplez_network.h>
#include <uv_lib.h>
#define stack 8
int counter = 0;
unsigned long wait_send[stack];
unsigned long curren_data;
String web_stat;
String HR = "";
void setup()
{
  //Serial.begin(9600);
  tripleZ_network_strat();
  UV_start();
  arrayInit();
  attachInterrupt(0, interrupt, RISING);//port2
}
void loop()
{
  //Serial.println("UV : "+UV_Get());
  /*if(HR != "")
  {
    Serial.println("HR : "+HR);
  }*/
  tripleZ_network_sendtext("ceedlerInUV", UV_Get());
  tripleZ_network_sendtext("ceedlerInHR", HR);
  delay(1000);
}
void interrupt()
{
      //Serial.println("Counter : "+(String)counter);
      wait_send[counter] = millis();
      if(counter < stack)
      {
        //Serial.println("now : "+(String)wait_send[counter]);
        /*if(counter > 0)
        {
          Serial.println("brfore :"+(String)wait_send[counter-1]);
          Serial.println("range: "+(String)(wait_send[counter]-wait_send[counter-1]));
        }
        */
        if(0 < counter  && counter <= stack-1 && (wait_send[counter]-wait_send[counter-1])>2400)
        {
          //Serial.println("error try again");
          counter = -1;
          delay(100);
        }
        if(counter == (stack-1))
        {
          HR = heartrate();
          counter = -1;
          delay(100);
        }
        counter+=1;
      }
}
void arrayInit()
{
  for(unsigned char i=0;i < stack;i ++)
  {
    wait_send[i]=0;
  }
}
String heartrate()
{
  int rate = (60000*(stack-2))/(wait_send[stack-1]-wait_send[1]);
  return (String)rate;
}
