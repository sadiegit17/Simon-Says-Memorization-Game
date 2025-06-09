#include <Adafruit_CircuitPlayground.h>

//constants used
const int patternSize = 10; //a fixed 10 steps to the pattern
int pattern [patternSize]; //creates an array of either blue or orange for 10 steps
int playerIndex = 0; //tracks correct inputs, increases to next expected input after each button push, starts at step 0 and recognizes when step 10 is correct and completed
bool gameActive = false;// false: when pattern is displayed, true: when game has started (active mode)
unsigned long displayStartTime; //for large integers and avoids negatives, timestamps of the 10 second display period, found from arduino link below


//buttons
const int leftButtonPin = 4; //blue button
const int rightButtonPin = 5; //orange button


//sound frequencies when buttons are pushed
const int blueNote = 196; //G3 note
const int orangeNote = 659; //E5 note 


//declaration functions
void startNewGame();//new round of game, resets the random pattern, the user's progress, and whether the game is active or not
void showPattern(); //pattern is displayed on LEDs for 10 seconds based on randomly generated array, then game is active and prepared for player input
void checkPlayerInput(); //allows the proper LED and sound output based on which button was pressed
void validateInput(int inputColor); //checks parameter to see if player button choice is correct 


  void startNewGame() { //involved in setup
    for (int i = 0; i < patternSize; i++){ //loop that runs 10 times and i increases
      pattern[i] = random(0,2); //can either be assigned a 0/ blue or 1/ orange, max number is exclusive so <2, generates the numbers that randomSeed intitializes
    }
    playerIndex = 0; //resets to step 0
    gameActive = false; // pattern is shown, not in input mode yet
    displayStartTime = millis(); //tracks in milliseconds how long pattern is displayed, allows timely switch to player input mode
  }


  void showPattern() {
    CircuitPlayground.clearPixels();
    for(int i = 0; i < patternSize; i++) {
      int color = pattern[i];
    if (color == 0) { //compares if color is 0 or not, if the step color is blue then display blue on LED
      CircuitPlayground.setPixelColor(i, 0, 0, 255);
      } else {
      CircuitPlayground.setPixelColor(i, 255, 100, 0);
        }
      }
      delay(10000);
      CircuitPlayground.clearPixels();
      gameActive = true;
      Serial.println("Begin Pressing Buttons");
        }


  void checkPlayerInput(){ 
    if (digitalRead(leftButtonPin) == HIGH){ //high voltage is button pushed, used instead of ISR since button causes many steps which creates issues for simple interrupts 
       CircuitPlayground.playTone(blueNote, 200);
    for (int i = 0; i < 10; i++){
       CircuitPlayground.setPixelColor(i,0,0,255);
       }
      validateInput(0);
      delay(300);
      CircuitPlayground.clearPixels();
        }
    else if (digitalRead(rightButtonPin) == HIGH) {
      CircuitPlayground.playTone(orangeNote, 200);
    for(int i = 0; i < 10; i++){
       CircuitPlayground.setPixelColor(i,255,100,0);
        }
        validateInput(1);
        delay(300);
        CircuitPlayground.clearPixels();
          }
        }


  void validateInput(int inputColor) { //0=blue, 1=orange
    if(inputColor == pattern[playerIndex]){ //checks if player's button choice matches the color of the step in the pattern
      playerIndex++; //if a correct match then move to next step
    if(playerIndex >= patternSize) { //win condition
      Serial.println("Winner!!");
      CircuitPlayground.clearPixels();
      delay(1000);
      startNewGame();
        } 
  } else { //lose condition
      Serial.println("Game Over");
      CircuitPlayground.clearPixels();
      delay(1000);
      startNewGame();
        }
      }


//prepares game on both the program and the board
void setup(){
  Serial.begin(9600);
  CircuitPlayground.begin();

  pinMode(leftButtonPin, INPUT_PULLDOWN);
  pinMode(rightButtonPin, INPUT_PULLDOWN);

  randomSeed(analogRead(A0));// https://docs.arduino.cc/language-reference/en/functions/random-numbers/randomSeed/
  startNewGame(); // game reset and ready for player input, initializes gameplay before program begins looping
}


void loop (){
  if(!gameActive && millis() - displayStartTime < 10000){ //pattern is still being displayed AND 10 seconds has not passed yet
    showPattern();
    }
    else if (!gameActive) { //moment after pattern displayed
      CircuitPlayground.clearPixels();
      gameActive = true; //player can now input
      Serial.println("Start Game!");
      }
    else { //repeatedly checks the player input until game is over
      checkPlayerInput(); //player input takes you to validate input which take you to next step, winner, or game over
      }
  }
