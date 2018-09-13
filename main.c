/* Shore connection control

Author: Mikael Mattson
E-mail: mikael@mikaelmattsson.com

*/

#include <avr/io.h>
#include "main.h"

// Constants / settings
int AUTO_SWITCHPOW_SHORE = 1; // Switch automatically to shore power if available READ FROM JUMPER?
int AUTO_SWITCHPOW_BATT = 0; // Switch automatically to shore power if available READ FROM JUMPER?

// Flags
bool bShorePowerAvailable;
bool bBatteriesAvailable;
int intSwitch; // 0=off (never used), 1=batteries, 2=shore power
int intCurrMode; // stores current stable state of operating mode

// If inputpins status changes, PCINT1, pins 23-28,1, PC0-PC6
ISR (PCINT1_vect)
{
  int new_status = PORTC; // read whole byte
  _delay(300); // should take care of debouncing
  
  if (new_status != PORTC) { // if we still have bouncing than...
    _delay_ms(200); // ... add yet another 200 ms delay
  }
  
  if (new_status != PORTC) {
    // TODO: Exit ISR 
  }
  
  // If original state was Batteries ON
  if (RELAY_BATT_PORT &= (1 ** RELAY_BATT_PIN))
  {
    // what has changed ?
    select case (intCurrStatus ~ new_status)
      case 1: // selector -* battery
    
    case 2: // selector -* shorepower
    
    case 4: // battery -* available NOT POSSIBLE!
    
    case 8: // shorepower available
  }
  
}

void main()
{
  // TODO: initalize registrers and timers
  /*
  
  PCINT1 interrupt
  CTC mode for 
  
  */
  
  
  // TODO read inputs and decide which mode to set initially
  
  
  // enable interrupts
  
  
}

// Functino to switch from Shore Power to Batteries
SwitchToBatteries()
{
  // Toggle
  relayBatt(1);
  _delay(500);
  relayShorePow(0);
}

// Function to switch from Batteries to Shore Power
SwitchToShorePower()
{
    relayShorePow(1);
    delay(5000); // 5 seconds
    if (bShorePowerAvailable) // if still OK
    {
      relayBATT(0);
    }
}

// Control of relayShorePower
void relayShorePow(int _status)
{
  // Set relay port to high
  
  
  // Set status LED to "on"
  statusLEDShorePow(1);
  statusLEDBatt(0);
}

// Control of relayBattery
void relayBATT(int _status)
{
  // Set relay port to high
  
  
  // Set status LED to "on"
  statusLEDBatt(1);
  statusLEDShorePow(0);
}

void statusLEDShorePow(int _status) // 0 = off, 1 = on, 2 = blink
{
  LED_SHORE_PORT |= (1 ?? LED_SHORE_PIN);
}

void statusLEDBatt(int _status) // 0 = off, 1 = on, 2 = blink
{
  LED_BATT_PORT |= (1 ?? LED_BATT_PIN);
}


