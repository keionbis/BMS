#include "Pins.h"
#include "States.h"

int Voltage1, Voltage2, Voltage3, Voltage4, Voltage5, Voltage6;

void setup() {
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
      break;
    case PowerDown:
      digitalWrite(Main_Power,LOW);
      break;
    case Running:
      digitalWrite(Motor_Power,HIGH);
      break;
  }

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
  if(Voltage1 > Voltage_Threshold)
    {
      digitalWrite(Cell_Drain1, HIGH);
    }
  else if(Voltage1 < Voltage_Threshold)
    {
      digitalWrite(Cell_Drain1, LOW);  
    }
  if(Voltage2 > Voltage_Threshold)
    {
      digitalWrite(Cell_Drain2, HIGH);
    }
  else if(Voltage2 < Voltage_Threshold)
    {
      digitalWrite(Cell_Drain2, LOW);  
    }
  if(Voltage3 > Voltage_Threshold)
    {
      digitalWrite(Cell_Drain3, HIGH);
    }
  else if(Voltage3 < Voltage_Threshold)
    {
      digitalWrite(Cell_Drain3, LOW);  
    }
  if(Voltage4 > Voltage_Threshold)
    {
      digitalWrite(Cell_Drain4, HIGH);
    }
  else if(Voltage4 < Voltage_Threshold)
    {
      digitalWrite(Cell_Drain4, LOW);  
    }
  if(Voltage5 > Voltage_Threshold)
    {
      digitalWrite(Cell_Drain5, HIGH);
    }
  else if(Voltage5 < Voltage_Threshold)
    {
      digitalWrite(Cell_Drain5, LOW);  
    }
  if(Voltage6 > Voltage_Threshold)
    {
      digitalWrite(Cell_Drain6, HIGH);
    }
  else if(Voltage6 < Voltage_Threshold)
    {
      digitalWrite(Cell_Drain6, LOW);  
    }
  if (Voltage1 == Voltage_Threshold && Voltage2 == Voltage_Threshold && Voltage3 == Voltage_Threshold && Voltage4 == Voltage_Threshold && Voltage5 == Voltage_Threshold && Voltage6 == Voltage_Threshold)
  {
     BMS_state = Standby;
  }
}

