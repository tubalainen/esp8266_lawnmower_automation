# Automation of any lawn mower robot using an ESP8266 / NodeMCU / Wimos D1 Mini using Home Assistant

# What I want to achive
- Ground the boundry wire in case of thunder bold lightning
- Being able to disable the front lawn using relays and re-routing of the boundry wire
- Knowing when the lawn mower got stuck (did not come back to charge)
- Installing a "manual" button to control the front lawn zone

# Pre-req´s
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

# Features of this build includes
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

# The hardware used
The whole build is quite basic, I control two relays and uses to GPIOs for switch input.
-	ESP8266 with at least four GPIOs, I recommend a NodeMCU or a Wimos D1 (mini)
-	Relay board with at least two relays where the coil of the relays accept 3.3 V control
-	Switch filter - 2x 4k7 Resistor and 2x 20 – 100 nano farad capacitor to prevent “ghost switching”
-	DC-DC converter 32 VDC -> 12 VDC
-	DC-DC converter 12 VDC – 5VDC
-	Two 12 VDC car head light relays (alternating relays)
-	IP65 housing
-	Normal wall light switch (IP 44 or higher)
-	Rolling switch with arm
-	Cables of assorted sizes and water proofed connectors
-	Terminal screw block
-	PCB and headers
-	Solder, soldering iron
-	Heat shrink and a heater blower
-	Spare wood and screws to build the arm for the rolling switch
-	A day to spare for the build

# Shopping list (Sweden), lawicel.se and kjell.com
-	NodeMCU: https://www.lawicel-shop.se/catalog/product/view/id/5823/s/nodemcu-v3-with-esp-12e-ch340/
-	Relay board: https://www.lawicel-shop.se/relay-module-4-relays-5vdc
-	Components resistors: https://www.lawicel-shop.se/catalog/product/view/id/4005/s/resistor-4-70kohm-10-pack/
-	Components capacitors:  https://www.lawicel-shop.se/capacitor-100nf-10-pack
-	DC-DC converter 32 V – 12 V: https://www.lawicel-shop.se/catalog/product/view/id/4478/s/12v-2-2a-step-down-vr-d24v22f12/
-	DC-DC converter 12 V – 5 V: https://www.lawicel-shop.se/catalog/product/view/id/4469/s/5v-step-up-step-down-vr-s9v11f5/
-	Terminal screw block: https://www.kjell.com/se/sortiment/el-verktyg/elektronik/montering/luxorparts-skruvplint-5-mm-4-pol-10-pack-p90762

(Please note that all components above can be sourced from anywhere. Most components are priced except for the DC-DC converters…)

# The build
I source the power from the lawn mower, you do not have to do that, you can run a separate power to the micro controller and relays if you want. It would be preferred hence you could use one of the relays to turn on/off the power to lawn mower without losing power to your micro controller and relays. If you decide to source for example 12 VDC from another power source than the lawn mower charger then you can drop one DC-DC converter from the build.
The built is quite straight forward. Adding the filter for the two buttons and connect in/out of the DC-DC converters.

# The Arduino Code
I found this code on the Home Assistant homepage, credits to: XXXX
The code compiles great in Arduino IDE, it requires the ESP8266 setup as well as the MQTT libs installed.
Change the SSID, Password and MQTT details to fit your setup.

# Home Assistant
For more details around HASS, please visit: http://www.home-assistant.io/
In the repository above you will see some example code for Home Assistant.
Configuration.yaml 
MQTT server setup 
Timer 
Switches.yaml 
Sensors.yaml 
Automations.yaml 

