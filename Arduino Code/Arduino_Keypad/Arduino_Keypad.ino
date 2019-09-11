#include <Keypad.h>

char* password = "1234"; //create a password
int passPosition = 0; //keypad position

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
  Serial.begin(9600);
}


void loop() {

  checkPassword();

  delay(100);

}


void checkPassword() {
  char whichKey = myKeypad.getKey(); //define which key is pressed with getKey

  if (whichKey == password [passPosition]) {
    Serial.println(whichKey);
    passPosition ++;
  }
  else if (whichKey != password [passPosition] && whichKey != NULL){
    passPosition = 0;
    Serial.println(whichKey);
  }
  
  if (passPosition == 4) {
    passPosition = 0;
    Serial.println("Password Matched");
    delay(1000);
  }
}
