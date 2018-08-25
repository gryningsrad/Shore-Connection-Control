# ShoreConnectionControl
Automatic switching and control for transition between shore power and battery on a sailing yacht.
When on shore power the Main Switchboard (MSB) shall be fed trough a 12V-power supply instead of the batteries.
One power supply for the MSB, one separate for the refridator. 

Functions:
- Switch to select feeding of main switchboard from battery/batteries or powersupply (12V) fed from 230V shore connection
- Indication of which power source is available and which one is active
- Automatic switching between shore/battery depending on availability
- Option to enable/disable automativ switching

Inputs:
- Switch, "Shore power/batteries/auto"
- Enough?

Outputs:
- 1 relay, batterier to MSB
- 1 relay, batteries to Fridge
- 1 relay, power supply to MSB
- 1 relay, power supply to fridge
- LEDs indicating availablity and active source
