#define Servo_port 9
#include <Servo.h>
Servo certain;
boolean check = true;//can open
void certain_start()
{
    certain.attach(Servo_port);
}
void certain_change(String x)
{
    if(x == "on" && check)
    {
        certain.write(150);
        check = !check;
        //Serial.println("on");
    }
    else if(x == "off" && !check)
    {
        certain.write(30);
        check = !check;
        //Serial.println("on");
    }
}
