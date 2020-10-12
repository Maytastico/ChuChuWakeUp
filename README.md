# What is ChuChuWakeUp?

ChuChuWake is a application that is designed to work with a raspberry pi and an arduino. It shall be an application that achieves a pleasant awakening. The idea is that a led stripe will simulate a sunrise, but before the sun rises the raspberry pi will play natural noises like birdsongs, wave sounds, or wind noises. The application will be controlled by an Web-Application. It shall be able to set the color, an animation, a wake-up time, a preferred wake-up sound and when the waking up sequence stops. The communication between raspberry pi and arduino will be over the serial interface. The raspberry pi sends commands to the raspberry that will be interpreted by the arduino. The Web-App communicates over HTTP requests with the Python script which has the function to interpret the HTTP requests into Serial commands. However that is just one task that the python server has. It also controls the waking up sequence. A curl configuration will look whether the server is running or not. If it dies, curl will restart the application. So it plays the role of a watchdog to be sure that everything works.

# Serial Commands

There shall be several commands that control the LED-Stripe. One of them shall be setting a specific Color. 

<command> : says what the arduino shall do e.g setColor or playAnimation

<argument> : An argument can contain a number or a string e.g 255 or rainbow
							The program can process three arguments in total.

The Syntax will be:
` <command>(<arguments>)`

## Example Commands

This command command plays an specified animation during an specific time. 
Time will be counted in milliseconds.
Types:
	rainbow,
	sunrise,
	randomColorFade,

`playAnimation(<type>, <duration>)`

Fades the old color out and a new color in. The color is specified in the rgb format
`setColorFade(<red>,<green>,<blue>)`

Sets a specified color.
`setColor(<red>,<green>,<blue>)`

# Specification Raspberry

The Raspberry will contain the server that manages everything. There will be a flask application that handles the web application. Nevertheless there will be a database as well. It contains all the data for example the state of the arduinos, their brightness, their wake-up times, their program states or their current color.

# Topics

1. "Die Serielle Kommunikation und wie sie in diesem Projekt eingesetzt wird."
   1. Geschichte der Seriellen kommunikation
   2. Serielle kommunikation allgemein
   3. Wie der Arduino die Befehle interpretiert
2. "Wie die Website mit dem dem Back End kommuniziert"
   1. Aufbau der Webseite
   2. Das HTTP-Protokoll
   3. Sicherheitsmassnahmen
   4. Kommunikation in Action
3. "Was macht der Arduino"
   1. Was ist eine State Maschine
   2. Aufbau der Klassen
   3. Die loop Methode
   4. Wie werden die LED-Stripes animiert

# Goals

|      | Goals                                                        |
| :--- | ------------------------------------------------------------ |
| [x]  | Getting serial working                                       |
| [x]  | Getting the arduino to interpret the commands that were send over the serial interface |
| [x]  | Getting the arduino to execute the commands properly         |
| []   | Getting a sunrise animation to work |
| []   | Getting the raspberry to send serial commands over the serial interface |
| []   | Building a prototype for the web interface                   |
| []   | Coding the web interface                                     |
| []   | Building the back-end                                        |
| []   | Connecting the front-end with the back-end                   |
| []   | Finalizing the project                                       |
| []   | Presenting one of four topics regarding the project at the fifth verbal secondary school exam |
| []   | Writing a sunrise animation                                  |