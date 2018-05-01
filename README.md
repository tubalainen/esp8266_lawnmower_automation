# Automation of any lawn mower robot using an ESP8266 / NodeMCU / Wimos D1 Mini using Home Assistant

Pre-req´s
This build is based around the home automation system Home Assistant and uses a ESP8266 micro controller to communicate with Home Assistant via wifi.
Further more you would also need a lawn mower shelter / house where you can install the system.
So the list of pre-req´s before you jump into the build. :)
- A robotic lawn mower (duuh!)
- Preferably a shelter/house for the mower
- Home Assistant installation (can be on a Raspberry Pi for instance)
- A working MQTT server/broker installed and configured with Home Assistant
- Some basic skills and know-how for Arduino IDE and programming of ESP8266 micro controllers
- A wifi network with coverage at the charging base
- Soldering iron and soldering skills
- The components, spare cables, connectors and other "nice to have" things from your workshop

Features of this build includes:
- Grounding of the boundary wire in case of thunder bolt lightning
- Disable from lawn in case of my kids playing there
- A lever switch to detect if the robot is charging
- A normal "button" to control if the front yard should be cut or not
- Automations in Home Assistant to:
   * Timer to alert if the robot has been running for more than two hours (stuck)
   * Automation to turn on a LED strip light if the robot is out working (cutting grass)
   * Automation to turn on a LED strip light if the robot is charging (at home)
   * Automation to turn on a LED strip light + send a notification that the timer has expired and that the robot is now stuck
   * Automation that engages the boundary wire switches and ground the wire if the risk of thunder bold lightning is greater than 70%

The hardware used:
The whole build is quite basic, I control two relays and uses to GPIOs for switch input.
-	ESP8266 with at least four GPIOs, I recommend a NodeMCU or a Wimos D1 (mini)
-	Relay board with at least two relays where the coil of the relays accept 3.3 V control
-	Switch filter - 2x 4k7 Resistor and 2x 20 – 40 nano farad capacitor to prevent “ghost switching”
-	DC-DC converter 32 VDC -> 12 VDC
-	DC-DC converter 12 VDC – 5VDC
-	Two 12 VDC car head light relays (alternating relays)
-	IP65 housing
-	Cables of assorted sizes and water proofed connectors
-	PCB and headers
-	Solder, soldering iron
-	Heat shrink and a heater blower
-	A day to spare for the build

The Arduino Code
I found this code on the Home Assistant homepage, credits to: XXXX
The code compiles great in Arduino IDE, it requires the ESP8266 setup as well as the MQTT libs installed.
Change the SSID, Password and MQTT details to fit your setup.

Home Assistant
For more details around HASS, please visit: http://www.home-assistant.io/
In the repository above you will see some example code for Home Assistant.
Configuration.yaml
MQTT
Timer
Switches.yaml
Sensors.yaml
Automations.yaml

