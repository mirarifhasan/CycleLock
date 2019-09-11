#include <SoftwareSerial.h>
#include <Keypad.h>
SoftwareSerial SIM900A(10, 11);

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


void setup()
{
  SIM900A.begin(9600);   // Setting the baud rate of GSM Module
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println ("SIM900A Ready");
  delay(100);
  Serial.println ("Type s to send message or r to receive message");
}


void loop()
{
  checkPassword();

  delay(100);
}


void checkPassword() {
  char whichKey = myKeypad.getKey(); //define which key is pressed with getKey

  if (whichKey == password [passPosition]) {
    Serial.println(whichKey);
    passPosition ++;
  }
  else if (whichKey != password [passPosition] && whichKey != NULL) {
    passPosition = 0;
    Serial.println(whichKey);
  }

  if (passPosition == 4) {
    passPosition = 0;
    Serial.println("Password Matched");
    delay(1000);
    SendMessage();
  }
}


void SendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+8801534312346\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("Good morning, Cycle unlocked.");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ->SMS Selesai dikirim");
}


void RecieveMessage()
{
  Serial.println ("SIM900A Membaca SMS");
  delay (1000);
  SIM900A.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  Serial.write ("Unread Message done");
}
