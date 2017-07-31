#define UV_Pin A0
void UV_start() {
    pinMode(UV_Pin, INPUT);
}
String UV_Get() {
  int uvLevel = analogRead(UV_Pin);
  //Serial.println("analog : "+(String)uvLevel);
  float outputVoltage = uvLevel*4.88281;
  //Serial.println((String)outputVoltage);
  if(outputVoltage > -1.0)
  {
    return "0";
  }
  else if(outputVoltage > 227.0)
  {
    return "1";
  }
  else if(outputVoltage > 318.0)
  {
    return "2";
  }
  else if(outputVoltage > 408.0)
  {
    return "3";
  }
  else if(outputVoltage > 503.0)
  {
    return "4";
  }
  else if(outputVoltage > 606.0)
  {
    return "5";
  }
  else if(outputVoltage > 696.0)
  {
    return "6";
  }
  else if(outputVoltage > 795.0)
  {
    return "7";
  }
  else if(outputVoltage > 881.0)
  {
    return "8";
  }
  else if(outputVoltage > 976.0)
  {
    return "9";
  }
  else if(outputVoltage > 1079.0)
  {
    return "10";
  }
  return "11";
}