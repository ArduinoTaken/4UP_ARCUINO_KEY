#include "CmdAndFeedback.h"
/*
This code for Arduino board
LED pin:D13
KEY pin:D12
*/
String comdata="";
int led_pin = 13;
int key_pin = 12; //not 4up
//int key_pin = 2; //4up
int cmdCount = 0;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  //pinMode(key_pin, INPUT_PULLUP);
  digitalWrite(led_pin, LOW);
  cmdCount = sizeof(cmdFeedbackArr) /sizeof(cmdFeedbackArr[0]);
  delay(5);
  // Serial.println(cmdCount);
}

void loop()
{
  // put your main code here, to run repeatedly:
  receiveCom();
  checkButton();
  delay(10);
}

void receiveCom()
{
  comdata = "";
  while (Serial.available() > 0)
  {
    comdata += char(Serial.read());
    delay(2);
  }
  if (comdata != "")
  {
    respondAction();
  }
}

void respondAction()
{
  if (comdata != "")
    comdata.trim(); // 去除前后空格
  else
    return;
  if (comdata == "help")
  {
    delay(100);
    printCommandList();
    return;
  }
  else if (comdata == "set LED on")
    {
      digitalWrite(led_pin, HIGH);
      delay(10);
      Serial.println("OK*_*");
      return;
    }
  else if (comdata == "set LED off")
    {
      digitalWrite(led_pin, LOW);
      delay(10);
      Serial.println("OK*_*");
      return;
    }
  else if (comdata.startsWith("OP"))
    {
      delay(10);
      Serial.println("OK");
      return;
    }
  bool return_flag = false;
  for (int i = 0; i < cmdCount; i++)
  {
    int location = cmdFeedbackArr[i].indexOf(';');
    String cmd = cmdFeedbackArr[i].substring(0, location);
    if (comdata == cmd)
    {
      String feedback = cmdFeedbackArr[i].substring(location + 1, cmdFeedbackArr[i].length());
      delay(10);
      if (feedback != "")
        Serial.println(feedback);
      return_flag = true;
      break;
    }
  }
  //if (!return_flag)
  //  Serial.println("OK");
}

void checkButton()
{
  if (HIGH == digitalRead(key_pin))
  {
    while(HIGH == digitalRead(key_pin)){
      delay(5);
    }
    Serial.println("KEY PRESS");
  }
}

void printCommandList()
{
  for (int i = 0; i < cmdCount; i++)
  {
    Serial.println(cmdFeedbackArr[i]);
    delay(5);
  }
}
