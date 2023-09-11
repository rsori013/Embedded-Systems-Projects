# Introduction-To-Embedded-Systems

These are the labs and projects I completed during my CS120B class in Spring 2023. Throughout this course, I delved into the fundamentals of embedded systems, utilizing hardware components and implementing software logic to bring real-world applications to life. 

## Instructions

### Lab 1: Hex to Binary LED Converter
- **Description**: Convert a user-input hex value into its binary and decimal representations.
- **Instructions**:
  - Enter a hex value.
  - Watch the 8 LED lights displaying the binary representation of the input.
  - LEDs will reset and then demonstrate a shifting light pattern.
  - This cycle persists until a new hex input is given.

### Lab 2: LED Control with Buttons & Potentiometer
- **Exercise 1: Simple LED Control**
  - Press the first button to activate the 4 LEDs.
  - Press the second button to deactivate them.
- **Exercise 2: Incremental LED Control**
  - Use the first button to increment active LEDs in the sequence: 0, 1, 2, 3, 4, 3, 2, 1.
  - Use the second button for the reverse sequence.
- **Exercise 3: Potentiometer LED Mapper**
  - Rotate the potentiometer.
  - View the 4 LEDs as they display a binary representation (e.g., for value 4: off, off, on, off).

### Lab 3: Ambient Light Color LED Controller
- **Description**: Utilize a photoresistor and potentiometer to modulate an RGB LED's color based on ambient light.
- **Instructions**:
  - In dark conditions, the LED activates.
  - Rotate the potentiometer to toggle through 5 different colors.
  - Under light conditions, the LED deactivates.
  - Employ state machines for implementing control logic.

### Lab 4: Restroom Occupancy Indicator
- **Description**: Simulate restroom occupancy indicators using a photoresistor and button to control LEDs.
- **Instructions**:
  - The green LED indicates the restroom is unoccupied.
  - Upon detection of occupancy (either through darkness or button press), the white LED activates for 20 seconds.
  - Pressing the button during this period either extends the duration by another 20 seconds or deactivates the LED.
  - If 20 seconds pass without any detected activity, the LED deactivates.
  - Following manual deactivation, a 20-second cooldown period ensues where the system won't respond.

### Lab 5: Segment Display & Joystick Controller
- **Description**: Control the rate of number display on a seven-segment screen using a joystick.
- **Instructions**:
  - Push the joystick to initiate counting on the seven-segment display, looping from 0 to 9.
  - The default counting speed is one number per second.
  - Pushing the joystick up increases counting speed to one number every 0.5 seconds.
  - Pushing it down decelerates it to one number every 2 seconds.
  - Press the joystick during counting to pause at the current number. Another press resumes counting.

### Lab 6: Joystick-Driven State Machines with LED & Segment Display
- **Description**: Develop dual concurrent state machines to manipulate LEDs and a seven-segment display based on joystick actions and timings.
- **Instructions**:
  - Initially, the green LED blinks every 1000ms.
  - Pressing the joystick halts the green LED, turns on the white LED, and the seven-segment display starts a countdown from 9 to 0.
  - Any joystick motion during the countdown resets it to 9.
  - Once the countdown finishes, the green LED resumes its blinking, and the white LED deactivates. This status remains until the joystick is pressed again.

### Final Project: Interactive Music Box with LCD Interface
- **Description**: Create a music box with an LCD screen, speakers, joystick, and a potentiometer, permitting users to select and oversee song playback and adjust the LCD's brightness.
- **Instructions**:
  - **LCD Home Screen**: Options displayed include:
    - Song 1
    - Song 2
    - Song 3
    - Start
  - Use the joystick to navigate and select a song. A mark will indicate your choice.
  - Press "Start" to commence song playback.
  - During playback, the LCD will display:
    - The song number currently playing.
    - Pause and play options.
  - Music autoplays upon selection, but users can pause and restart it as needed.
  - Once a song ends, users can revisit the song selection screen to choose another track.
  - Rotate the potentiometer to regulate the LCD screen's brightness. 

## Videos
- **Lab 1:** [Link](https://www.youtube.com/watch?v=ZpnG9_CUoDk)
- **Lab 2:** [Link](https://youtu.be/0tPc3yZE8pM)
- **Lab 3:** No Video
- **Lab 4:** [Link](https://www.youtube.com/watch?v=YKX-MGzriQg)
- **Lab 5:** [Link](https://www.youtube.com/watch?v=SXXvCRA_VBo)
- **Lab 6:** [Link](https://www.youtube.com/watch?v=R-gUcM8tyt0)
- **Final Project:** [Link](https://www.youtube.com/watch?v=q-HWtbY07x0)
