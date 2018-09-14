/* ##### main.h #####



*/

#IFNDEF main.h
#DEFINE main.h

#define intCurrMode 0         // 0=battery, 1=shorepower


// Output Pins
#define LED_BATT_PORT         PORTA
#define LED_BATT_PIN          3

#DEFINE LED_SHOPOW_PORT       PORTA
#DEFINE LED_SHOPOW_PIN        4

#DEFINE RELAY_BATT_PORT       PORTA
#DEFINE RELAY_BATT_PIN        5

#DEFINE RELAY_SHOPOW_PORT     PORTA
#DEFINE RELAY_SHOPOW_PIN      4

#DEFINE BUZZER_PORT           PORTA
#DEFINE BUZZER_PIN            7

// Input pins
#DEFINE SHOPOW_AVAIL_PORT       PORTA
#DEFINE SHOPOW_AVAIL_PIN        4

#DEFINE BATT_AVAIL_PORT       PORTA
#DEFINE BATT_AVAIL_PIN        5

#DEFINE SHOPOW_SELECT_PORT       PORTA
#DEFINE SHOPOW_SELECT_PIN        4

#DEFINE BATT_SELECT_PORT       PORTA
#DEFINE BATT_SELECT_PIN        5

// Delays and timers
#DEFINE TIME_DELAY_BATT2SHORE 500 // in ms
#DEFINE TIME_DELAY_SHORE2BATT 500 // in ms
#DEFINE ALARM_SUMMER_TIME     1200


// enum for the different input combinations
/*
          bit:  7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
ShoPow_Avail    x   x   x   x   x   x   x   1
Batt_Avail      x   x   x   x   x   x   1   x
SwtBatt         x   x   x   x   x   1   x   x
SwtShoPow       x   x   x   x   1   x   x   x
*/
enum Inputs {
        Input_ShoPowAvail = 1,
        Input_BattAvail = 2,
        Input_SwtBatt = 4,
        Input_SwtShoPow = 8
};


#ENDIF
