/* Shore connection control

Author: Mikael Mattson
E-mail: mikael@mikaelmattsson.com



*/


// Constants / settings
int SP_ON_DELAY = 10; // seconds before Shorepower is deemed stable
int SWITCH_OFF = 0;
int SWTICH_BATTERIES = 1;
int SWITCH_SHOREPOW = 3;
bool AUTO_SWITCHPOW = true; // Switch automatically to shore power if available

// Flags
bool bShorePowerAvailable;
bool bBatteriesAvailable;
int intSwitch; // 0=off (never used), 1=batteries, 2=shore power
int intCurrMode; // stores current stable state of operating mode, b01 = batteries, b10 = shore power


// If shorepower-pin status changes
interruptShorePowerchange
{
  bool bNewStaus = [INPUTPIN OF SHOREPOWER SUPERVISION]
  if(bShorePowerAvailable) // ShorePower where connected erlier ==Z Shorepower is now lost
  {
     bShorePowerAvailable = false;
     RaiseAlarm(); // if alarm is set to sound, raise alarm
     SwitchToBatteries(); // Procedure to change to battery
     
  } else { // Shorepower was disconnected ==Z ShorePower now connected
  
    // ## Time loop, 10 seconds to see that shore power connection is stable. delay defined as a constatnt ##
    bShorePowerAvailale = true;
    led_on(ledShorePowerAvailable);
    
    // If selector is set to "Shore power" = then connect
    if (intSwitch = SWITCH_SHOREPOW && AUTO_SHOREPOW)
    {
      SwitchToShorePower();
    {
  }
}

// If selector button changes 
// 2-pins: b00 = off, b01 = batteries, b10 = shore power
interrupSelectorChange()
{
  // dependin on new value
  switch([SELECTOT_BITES_VALUE]
  case(b00) // off never used
  
  
  case(b10) // batteries
  
  
  case (b01) // shorepower
    
  
}

// Functino to switch from Shore Power to Batteries
SwitchToBatteries()
{
  relayBatt(on);
}

// Function to switch from Batteries to Shore Power
SwitchToShorePower()
{
  // Check to see if Shorepower is available
  if (bShorePower Available)
  {
    relaySHPO(true);
    delay(5); // 5 seconds
      if (bShorePowerAvailable) // if still OK
      {
        relayBATT(off);
      }
  }
}

// Control of relayShorePower
void relaySHPO()
{
  // Set relay port to high
  
  // Set status LED to "on"
  
}

// Control of relayBattery
void relayBATT()
{
  // Set relay port to high
  
  // Set status LED to "on"
  
}

