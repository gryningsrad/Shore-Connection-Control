/* Shore connection control

Author: Mikael Mattson
E-mail: mikael@mikaelmattsson.com

*/

// Settings
int AUTO_SWITCHPOW_SHORE = 1; // Switch automatically to shore power if available READ FROM JUMPER?
int AUTO_SWITCHPOW_BATT = 0; // Switch automatically to shore power if available READ FROM JUMPER?
const int blinkInterval = 500; // how many milliseconds between blinks

// Other global variables
unsigned long startMillis;
unsigned long currentMillis;
const int LED_OFF = 0;
const int LED_ON = 1;
const int LED_BLINK = 2;

// Flags
int bBatteriesAvailable;
int intSwitch; // 0=off (never used), 1=batteries, 2=shore power
int intCurrMode; // stores current stable state of operating mode, 0 = battery, 1= shorepower

// Pins
const int pinRelayShorePower = 1;
const int pinRelayBattery = 2;
const int pinLedBattery = 3;
const int pinLedShore = 4;
const int pinSwitchShore = 5;
const int pinSwitchBattery = 6;
const int pinShoreAvailable = 7;

// If shore power connection availabilty changes
IR_ShoreChanged () // 
{
  // Combinations possible:
  // 1: Battery ON, Shorepower OFF, Shore Avail OFF -> ON
  // 2: Battery ON, Shorepower OFF, Shore Avail ON -> OFF
  // 3: Battery OFF, ShorePower ON, Shore Avail ON -> OFF
  // 
  // ShorePowerAvailable()
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
     
void setup() {
     
     Serial.begin(9600);
     
     // Get start time for our LED-blink-function
     startMillis = millis();
     
     // Pin setup
     pinMode(pinRelayShorePower, OUTPUT);
     pinMode(pinRelayBattery, OUTPUT);
     pinMode(pinLedBattery, OUTPUT);
     pinMode(pinLedShore, OUTPUT);
     
     pinMode(pinSwitchShore, INPUT);
     pinMode(pinSwitchBattery, INPUT);
     pinMode(pinShoreAvailable, INPUT);
     
     // initial setup of LEDs and relays.
     // Power to controller is from batteries so we assume that battery is on
     intCurrMode = 0; // 0 = battery
         
     digitalWrite(pinBatteryRelay, LOW); // relay is NC (battery normally connected if anything happens to controller
     digitalWrite(pinShoreRelay, LOW);
     
     statusLEDBatt(LED_ON); 
     statusLEDShore(LED_OFF);
     
     // check status of Shoreconnection
     if (ShorePowerAvailable())
     {
          statusLEDShore(LED_BLINK);
     }
     
     // check switch status, if put on "shore", delay then switch to shore
     intSwitch = GetSwitch();
     if (intSwitch == 1) { // Battery
          if (ShorePowerAvailable())
          {
               SwitchToShorePower(3000);   // 3000 ms delay
          }
     }
      
      // enable interrups, check of ShorePoweravailability
      attachInterrupt (digitalPinToInterrupt (pinShoreAvailable), IR_ShoreChanged, CHANGE);
     sei();
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
  
  // Blink function
  currentMillis = millis();
     
  if (currentMillis - startMillis >= blinkInterval) { // Times up!
      // Blink LEDs! 
      if (blinkLEDBatt) {
          // Toggle LED-pin
          digitalWrite(pinLedBattery, !digitalRead(pinLedBattery));
       }

       if (blinkLEDShore) {
          // Toggle LED-pin
          digitalWrite(pinLedShore, !digitalRead(pinLedShore));
       }
       startMillis = currentMillis;
       
      // Check switch input
      if (intSwitch != ReadSwitch()) {
        
      }
    
  } // millis-check
  
}

int ShorePowerAvailable() // returns 0 if not, 1 if available
{
     int _status = digitalRead(pinShoreAvailable);
     return _status;
}

// Function to switch from Shore Power to Batteries
void SwitchToBatteries()
{
  // Toggle
  relayBatt(1);
  
  _delay(500);
  relayShorePow(0);
}
  
int ReadSwitch()
  {
     
    
  }

// Function to switch from Batteries to Shore Power
void SwitchToShorePower(int _delay)
{
    relayShorePow(1);
    
    delay(_delay); // 5 seconds
    if (ShorePowerAvailable()) // if still OK
    {
      relayBATT(0); // Switch off batteries
    }
}

// Operation of relayShorePower
void relayShorePow(int _status)
{
  if (_status) { // = 1 = on
     // Set relay port to high
     digitalWrite(pinRelayShorePower, HIGH);
     // Set status LED to "on"
     statusLEDShorePow(LED_ON);
  } else { // = 0
     digitalWrite(pinRelayShorePower, LOW);
     // Set status LED to "on"
     statusLEDShorePow(LED_OFF);
  }
  
}

// Operation of relayBattery
void relayBATT(int _status)
{
     if (_status) { // = 1 = on
     // Set relay port to high
     digitalWrite(pinRelayBatt, HIGH);
     // Set status LED to "on"
     statusLEDBatt(LED_ON);
  } else { // = 0
     digitalWrite(pinRelayBatt, LOW);
     // Set status LED to "on"
     statusLEDBatt(LED_OFF);
  }
}

void statusLEDShorePow(int _status) // 0 = off, 1 = on, 2 = blink
{
  if (_status == LED_OFF) {
       digitalWrite(pinLedShore, LOW);
  } else {
       digitalWrite(pinLedShore, HIGH);
  }
     
  if (_status == LED_BLINK) { // We want the LED to blink    
     blinkLEDShore = 1;
  } else {
     blinkLEDShore = 0;    
  }
}

void statusLEDBatt(int _status) // 0 = off, 1 = on, 2 = blink
{
  if (_status == LED_OFF) {
       digitalWrite(pinLedBattery, LOW);
  } else {
       digitalWrite(pinLedBattery, HIGH);
  }
     
  if (_status == LED_BLINK) { // We want the LED to blink    
     blinkLEDBatt = 1;
  } else {
     blinkLEDBatt = 0;    
  }
  
}


