Game Description: 

This game is inspired by the Simon Says electronic game. LEDs 0-9 will each have either an orange or blue color in the 0-9 order. This will happen for 10 seconds, then the LEDs will turn off. The user must use this time to memorize the pattern and once the period is over, the serial monitor will read “Begin Pressing Buttons”. Now, the user must use the right and left buttons to recreate the displayed pattern from the LED 0-9 order. The right button will be orange, and the left button will be blue. The corresponding orange or blue note and LED color will happen each time a button is pressed. If at any point the user messes up the pattern, the serial monitor will read off “Game Over” and the game is reset. If the user completes a pattern, the serial monitor will read “Winner!” and the user will be assigned a different randomly generated pattern.  


User Inputs/Outputs Definitions:

  Input: Right Button (digital pin D5)
    Sensors Used: CircuitPlayground.rightButton()
    Specific Range: digitalRead()
    Sensor Function/ Output: Selects [1] for orange LED and orange note
  Input: Left Button (digital pin D4)
    Sensors Used: CircuitPlayground.leftButton()
    Specfic Range: digitalRead()
    Sensor Function/ Output: Selects [0] for blue LED and blue note
  Input: LEDs (0-9)
    Sensors Used: CircuitPlayground.setPixelColor()
    Rnages: Orange- (255,100,0), Blue- (0,0,255)
    Sensor Function/ Output: Displays pattern, all blue, all orange
  Input: Speaker
    Sensors Used: CircuitPlayground.playTone()
    Ranges: E5/Orange- 659 Hz, G3/Blue- 196 Hz
    Sensor Function/ Output: Plays note (2ms) when button pressed
  Input: Timer
    Sensors Used: millis()
    Range: if(millis() - displaystartTime < 10000 ms)
    Sensor Function/ Output: 10 second timer for pattern to be displayed
  Input: Serial Monitor
    Sensors Used: Serial.println()
    Ranges: "Text"
    Sensor Function/ Output: "Game Over", "Winner!!", "Begin Pressing Buttons"
