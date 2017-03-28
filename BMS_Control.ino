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
  

 
}
 
void loop() {

  if(analogRead(Input_Power)>500 && BMS_state = Standby )
  {
    BMS_state = Standby;
  }
  else if(analogRead(Input_Power)>500)
  {
    BMS_state = Charging;
  }
                                    //  else if(analogRead(Input_Power)<500 && BMS_state == Running)
                                    //  {
                                    //    BMS_state = Running;
                                    //  }
                                    //  else if(analogRead(Input_Power)<500 && BMS_state == Standby)
                                    //  {
                                    //    BMS_state = Standby;
                                    //  }

  if(((BMS_state == Running)||(BMS_state == Standby)||(BMS_state == PowerDown))&& digitalRead(Button == 1))
  {
    BMS_state = PowerDown;
  }

  if((BMS_state == Charging)&&(analogRead(Input_Power)<500))
  {
    BMS_state = PowerDown;
  }
  switch(BMS_state)
  {
    case Charging:
     digitalWrite(Voltade_Divider1, HIGH);
     digitalWrite(Voltade_Divider2, HIGH);
     digitalWrite(Voltade_Divider3, HIGH);
     digitalWrite(Voltade_Divider4, HIGH);
     digitalWrite(Voltade_Divider5, HIGH);
      Process_Batt_Voltage();
      break;

      
    case Standby:
      pinMode(Button, INPUT); // replacing voltageDivider 1 pin to be an input to check whether or not to turn the board off
      standby();
      break;

      
    case PowerDown:
      pinMode(Button, INPUT); // replacing voltageDivider 1 pin to be an input to check whether or not to turn the board off
      standby();
      digitalWrite(Main_Power,LOW);
      break;

      
    case Running:
      pinMode(Button, INPUT); // replacing voltageDivider 1 pin to be an input to check whether or not to turn the board off
      digitalWrite(Motor_Power,HIGH);
      DontDrainTooLow();
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

void DontDrainTooLow()
{
  if (Voltage1< Min_Voltage1&&Voltage2< Min_Voltage2&&Voltage3< Min_Voltage3&&Voltage4< Min_Voltage4&&Voltage5< Min_Voltage5&&Voltage6< Min_Voltage6)
  {
    BMS_state = PowerDown;
  }
}

