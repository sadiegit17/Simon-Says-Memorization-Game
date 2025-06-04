#include <Adafruit_CircuitPlayground.h>

//constants used
const int patternSize = 10; //a fixed 10 steps to the pattern
int pattern [patternSize]; //array of either blue or orange
int userIndex = 0; //tracks correct inputs, increases to next expected input after each button push
bool gameActive = false;// false: when pattern is displayed, true: when game has started (active mode)
unsigned long displayStartTime; //for large positive integers, timestamps of the 10 second display period

//sound frequencies when buttons are pushed
const int blueNote = 196; //G3 note
const int orangeNote = 659; //E5 note 

//buttons
const int leftButtonPin = 4; //blue button
const int rightButtonPin = 5; //orange button

//functions that are declared initially so that loop and setup can use then but they get defined later on
void startNewGame();//new round of game, resets the random pattern, the user's progress, and whether the game is active or not
void showPattern(); //lights up LED according to generated random pattern, based on array
void checkUserInput(); //allows the proper LED and sound output based on which button was pressed
void validateInput(int inputColor); //checks to see if player button choice is correct

//prepares game on both the program and the board
void setup(){
  Serial.begin(9600);
  CircuitPlayground.begin();

  pinMode(leftButtonPin, INPUT_PULLDOWN);
  pinMode(rightButtonPin, INPUT_PULLDOWN);

  randomSeed(analogRead(A0));//inspired by the arduino forum, this generates a new random pattern each time program is run
  startNewGame(); // game reset and ready for player input
}

void loop (){
  if(!gameActive && millis() - displayStartTime < 10000){ //pattern is still being displayed AND 10 seconds has not passed yet
    showPattern();
    }
    else if (!gameActive) {
      CircuitPlayground.clearPixels();
      gameActive = true; //player can now input
      Serial.println("Start Game!");
      }
    else { 
      checkUserInput();
      }
  }

//resets so that a new round of the game can begin
  void startNewGame() {
    for (int i = 0; i < patternSize; i++){
      pattern[i] = random(0,2); //can either be assigned a 0/ blue or 1/ orange, max is exclusive so <2
    }
    userIndex = 0; //resets to step 0
    gameActive = false; // pattern is shown, not in input mode yet
    displayStartTime = millis(); //tracks in milliseconds how long pattern is displayed
  }

//pattern is displayed on LEDs for 10 seconds based on randomly generated array, then game is active and prepared for player input
  void showPattern() {
    CircuitPlayground.clearPixels();
    for(int i = 0; i < patternSize; i++) {
      int color = pattern[i];
    if (color == 0) { //if the step color is blue then display blue on LED
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

//based on what button was pushed, will determine what color is displayed on LEDs and what note is played
  void checkUserInput(){ 
    if (digitalRead(leftButtonPin) == HIGH){
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

//checks if the button that was pushed is correct to the step in the random pattern array
  void validateInput(int inputColor) {
    if(inputColor == pattern[userIndex]){
      userIndex++;
    if(userIndex >= patternSize) {
      Serial.println("Winner!!");
      CircuitPlayground.clearPixels();
      delay(1000);
      startNewGame();
        } 
  } else {
      Serial.println("Game Over");
      CircuitPlayground.clearPixels();
      delay(1000);
      startNewGame();
        }
      }
      
    
