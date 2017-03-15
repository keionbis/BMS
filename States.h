#ifndef STATES_H
#define STATES_H

typedef enum BMS_States{
  Charging,
  Standby,
  PowerDown,
  Running
};

BMS_States BMS_state;

#endif
