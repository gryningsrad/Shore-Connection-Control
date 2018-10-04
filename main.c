/* Shore connection control

Author: Mikael Mattson
E-mail: mikael@mikaelmattsson.com

*/

#include "main.h"

// Constants / settings
int AUTO_SWITCHPOW_SHORE = 1; // Switch automatically to shore power if available READ FROM JUMPER?
int AUTO_SWITCHPOW_BATT = 0; // Switch automatically to shore power if available READ FROM JUMPER?

// Flags
int bShorePowerAvailable; 
int bBatteriesAvailable;
int intSwitch; // 0=off (never used), 1=batteries, 2=shore power
int intCurrMode; // stores current stable state of operating mode, 0 = battery, 1= shorepower
int intCurrStatus; // stores the whole status-byte (all inputpins)

// interrupt to check shorepower availability
ISR(INT0) {
     
}


// Blink-function for LEDS
void BlinkFunctionForLeds {
     if (blinkLEDBatt) {
          // Toggle LED-pin
          digitalWrite(LED_BATT_PIN, !digitalRead(LED_BATT_PIN));
     }
     
     if (blinkLEDShore) {
          digitalWrite(LED_SHORE_PIN, !digitalRead(LED_SHORE_PIN));
     }
     
}

// Poll of inputpins 23-28,1, PC0-PC6
ISR (// ON TIMER 800ms)
{
  int new_status = PORTC; // read whole byte
  _delay(300); // should take care of debouncing
  
  if (new_status != PORTC) { // if we still have bouncing than...
    _delay_ms(200); // ... add yet another 200 ms delay
  }
    
  // If original state is Batteries ON (assuming switch = battery)
  if (!(intCurrMode))
  {
    // what has changed ?
    select case (intCurrStatus ~ new_status) // what has changed ?
      case Input_ShoPowAvail: // shorepower has become available
        if (new_status ~ Input_ShoPowAvail) { // if Shorepower has become active
            statusLEDShorePow(2); // blink
          
        } else { // ShorePower has been turned off
            statusLEDShorePow(0): // off         
        }
        break;
    
      case Input_BattAvail: // has become available (used only when starting up boat?
          // DO NOTHING
          break;
    
      case Input_SwtBatt: // switch turned to Battery 
          // DO NOTHING
          break;
    
      case Input_SwtShoPow: // switch turned to ShorePower
          // TODO: check if shorepower is available
          // TODO: delay
          // TODO: change relays
          // TODO: change statusLED
          break;
    
  } else { // intCurrMode = 1 = Shorepower connected
    
    select case (intCurrStatus ~ new_status) // what has changed ?
      case Input_ShoPowAvail: // shorepower has become available
          // DO NOTHING
          break;
    
      case Input_BattAvail: // has become available (used only when starting up boat?
          statusLEDBattAvail(2); // Blink
    
      case Input_SwtBatt: // switch turned to Battery 
          // TODO: check if batterys is availbale
          // TODO: delay
          // TODO: change
          break;
    
      case Input_SwtShoPow: // switch turned to ShorePower
          // DO NOTHING    
          break;
    
  }
  
  
  // case battery off + shore poweroff:
  // TODO: activate battery relay only, blink statusLED
  
  
}

void loop()
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

// Operation of relayShorePower
void relayShorePow(int _status)
{
  // Set relay port to high
  
  // Set status LED to "on"
  statusLEDShorePow(1);
  statusLEDBatt(0);
}

// Operation of relayBattery
void relayBATT(int _status)
{
  // Set relay port to high
  digitalWrite(pinRelayBatt, HIGH);
  
  // Set status LED to "on"
  statusLEDBatt(1);
  statusLEDShorePow(0);
}

void statusLEDShorePow(int _status) // 0 = off, 1 = on, 2 = blink
{
  if (_status == 0) {
       digitalWrite(LED_SHORE_PIN, LOW);
  } else {
       digitalWrite(LED_SHORE_PIN, HIGH);
  }
     
  if (_status == 2) { // We want the LED to blink    
     blinkLEDShore = 1;
  } else {
     blinkLEDShore = 0;    
  }
}

void statusLEDBatt(int _status) // 0 = off, 1 = on, 2 = blink
{
  if (_status == 0) {
       digitalWrite(LED_BATT_PIN, LOW);
  } else {
       digitalWrite(LED_BATT_PIN, HIGH);
  }
     
  if (_status == 2) { // We want the LED to blink    
     blinkLEDBatt = 1;
  } else {
     blinkLEDBatt = 0;    
  }
  
}


