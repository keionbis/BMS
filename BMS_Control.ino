#include "Pins.h"
#include "States.h"

int Voltage1, Voltage2, Voltage3, Voltage4, Voltage5, Voltage6;

void setup() {
  Serial.begin(9600);
  pinMode (Main_Power, OUTPUT);
  digitalWrite(Main_Power,HIGH);
  pinMode(Voltade_Divider1, OUTPUT);
  pinMode(Voltade_Divider2, OUTPUT);
  pinMode(Voltade_Divider3, OUTPUT);
  pinMode(Voltade_Divider4, OUTPUT);
  pinMode(Voltade_Divider5, OUTPUT);

  pinMode(Cell_Drain1, OUTPUT);
  pinMode(Cell_Drain2, OUTPUT);
  pinMode(Cell_Drain3, OUTPUT);
  pinMode(Cell_Drain4, OUTPUT);
  pinMode(Cell_Drain5, OUTPUT);
  pinMode(Cell_Drain6, OUTPUT);

  pinMode(Motor_Power, OUTPUT);
  
  pinMode(Btn_LED, OUTPUT);

  digitalWrite(Voltade_Divider1, HIGH);
  digitalWrite(Voltade_Divider2, HIGH);
  digitalWrite(Voltade_Divider3, HIGH);
  digitalWrite(Voltade_Divider4, HIGH);
  digitalWrite(Voltade_Divider5, HIGH);
}
 
void loop() {
  
  if(analogRead(Input_Power)>500)
  {
    BMS_state = Charging;
  }
  
  switch(BMS_state)
  {
    case Charging:
      Process_Batt_Voltage();
      break;

      
    case Standby:
      digitalWrite(Btn_LED, HIGH);
      delay(1000);
      digitalWrite(Btn_LED, LOW);
      delay(1000);
      standby();
      break;

      
    case PowerDown:
      digitalWrite(Main_Power,LOW);
      break;

      
    case Running:
      digitalWrite(Motor_Power,HIGH);
      break;
  }
  Serial.println(BMS_state);

}


void Read_Batt_Voltages()
{
  Voltage1 = analogRead(Voltage_Check1);
  Voltage2 = analogRead(Voltage_Check2);
  Voltage3 = analogRead(Voltage_Check3);
  Voltage4 = analogRead(Voltage_Check4);
  Voltage5 = analogRead(Voltage_Check5);
  Voltage6 = analogRead(Voltage_Check6); 
}


void Process_Batt_Voltage()
{
  Read_Batt_Voltages();
  if(Voltage1 > Voltage_Threshold_batt1)
    {
      digitalWrite(Cell_Drain1, HIGH);
      Serial.println("Mosfet1: High");
    }
  else if(Voltage1 < Voltage_Threshold_batt1)
    {
      digitalWrite(Cell_Drain1, LOW);  
      Serial.println("Mosfet1: Low");
    }
  if(Voltage2 > Voltage_Threshold_batt2)
    {
      digitalWrite(Cell_Drain2, HIGH);
      Serial.println("Mosfet2: High");
    }
  else if(Voltage2 < Voltage_Threshold_batt2)
    {
      digitalWrite(Cell_Drain2, LOW);  
      Serial.println("Mosfet2: Low");
    }
  if(Voltage3 > Voltage_Threshold_batt3)
    {
      digitalWrite(Cell_Drain3, HIGH);
      Serial.println("Mosfet3: High");
    }
  else if(Voltage3 < Voltage_Threshold_batt3)
    {
      digitalWrite(Cell_Drain3, LOW);  
      Serial.println("Mosfet2: Low");
    }
  if(Voltage4 > Voltage_Threshold_batt4)
    {
      digitalWrite(Cell_Drain4, HIGH);
      Serial.println("Mosfet4: High");
    }
  else if(Voltage4 < Voltage_Threshold_batt4)
    {
      digitalWrite(Cell_Drain4, LOW);  
      Serial.println("Mosfet4: Low");
    }
  if(Voltage5 > Voltage_Threshold_batt5)
    {
      digitalWrite(Cell_Drain5, HIGH);
      Serial.println("Mosfet5: High");
    }
  else if(Voltage5 < Voltage_Threshold_batt5)
    {
      digitalWrite(Cell_Drain5, LOW);  
      Serial.println("Mosfet5: Low");
    }
  if(Voltage6 > Voltage_Threshold_batt6)
    {
      digitalWrite(Cell_Drain6, HIGH);
      Serial.println("Mosfet6: High");
    }
  else if(Voltage6 < Voltage_Threshold_batt6)
    {
      digitalWrite(Cell_Drain6, LOW);  
      Serial.println("Mosfet6: Low");
    }
  if (Voltage1 == Voltage_Threshold_batt1 && Voltage2 == Voltage_Threshold_batt2 && Voltage3 == Voltage_Threshold_batt3 && Voltage4 == Voltage_Threshold_batt4 && Voltage5 == Voltage_Threshold_batt5 && Voltage6 == Voltage_Threshold_batt6)
  {
     BMS_state = Standby;
  }
}



void standby()
{
  digitalWrite(Voltade_Divider1, LOW);
  digitalWrite(Voltade_Divider2, LOW);
  digitalWrite(Voltade_Divider3, LOW);
  digitalWrite(Voltade_Divider4, LOW);
  digitalWrite(Voltade_Divider5, LOW);
}

