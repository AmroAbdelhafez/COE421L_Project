Memory Motion Game - Arduino & Java Implementation

Overview:

This project implements a sequence memory game using Arduino hardware and a Java controller. The game challenges players to repeat LED light sequences by pressing corresponding light sensors, with increasing difficulty each round.




Hardware Requirements:

- Arduino board (Uno, Mega, etc.)


- 4 LEDs (connected to pins 2-5)

- 4 Light sensors (connected to analog pins A0-A3)

- Buzzer (connected to pin 7)

- Push button (connected to pin 6)

- ZigBee module (optional, for wireless communication)





Software Requirements

- Arduino IDE

- Java Development Kit (JDK) 8+

- JSSC library (jssc-2.8.0.jar)





Installation

- Arduino Setup

- Connect all hardware components as specified in the code comments

- Upload the Arduino sketch to your board

- Note the serial port address (e.g., /dev/cu.usbserial-DN02MSGP)


Java Setup

- Add jssc-2.8.0.jar to your Java project's build path

- Update the serial port in MemoryMotionGame.java to match your Arduino




How to Play

- Run the Java program

- Press the physical button to start the game

- Watch the LED sequence carefully

- Repeat the sequence by covering the corresponding light sensors

- Successfully complete sequences to advance rounds

- The game ends if you make a mistake



Features

- 3-second countdown with audible buzzer before Round 1

- Progressive difficulty with longer sequences each round

- Visual feedback through LED lights

- Audible feedback via buzzer

- Console logging of game progress

- Error detection and game over state

Communication Protocol

- Arduino → Java Messages
    -  SYSTEM_READY: Initialization complete
    -  COUNTDOWN:X: Countdown timer (3, 2, 1)
    -  ROUND:X: New round started
    -  PRESSED:X: Sensor X was pressed
    -  GAME_OVER: Game ended
- Java → Arduino Messages
    -  (Not currently used in basic implementation)


Troubleshooting
- No communication:
-  Verify correct serial port and baud rate (9600)

- LEDs not lighting: Check wiring and pin assignments

- Sensors not responding: Adjust SENSOR_THRESHOLD value

- Buzzer issues: Verify connection to pin 7

Customization Options

- Change difficulty by modifying:

  - Sequence length increment in Arduino code

  - Time limits in validatePlayerInput()

- Adjust feedback:

  - Buzzer durations in startCountdown()

  - LED timing in playSequence()
