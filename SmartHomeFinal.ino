//sHome by Nick Potiriadis

//Blinds Initialization
#include <Servo.h>
Servo myservo;
//Blinds Initialization

//OLED screen initialization
#include <Streaming.h>
#include <iomanip>
// -- OLED -------
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// OLED i2c
#define OLED_RESET -1
#define SDA D4; // Used by the default Wire constructor
// (called from Adafruit_SSD1306 default constructor)
#define SCL D3; // Need to overide defaults for
// **** original Wemos D1 board *****
#define OLED_SCREEN_I2C_ADDRESS 0x3C
Adafruit_SSD1306 display(OLED_RESET);
//OLED screen initialization

//Clock and button initialization
#include <DS1302.h>
#include <TM1638.h>
#define DS1302_SCLK_PIN D10 // Arduino pin for the Serial Clock
#define DS1302_IO_PIN D2 // Arduino pin for the Data I/O
#define DS1302_CE_PIN D4 // Arduino pin for the Chip Enable AKA rst
DS1302 rtc(DS1302_CE_PIN, DS1302_IO_PIN, DS1302_SCLK_PIN );
#define TM1638_DIO D11
#define TM1638_CLK D6
#define TM1638_STB D5
TM1638 module(TM1638_DIO, TM1638_CLK, TM1638_STB);
//Clock and button initialization

//Variables
byte buttons;//button number that has been pressed is stored here
String light; //the status of the light is stiored here
String blind;//the status of the blinds is stored here
//variables

void setup() {
  myservo.attach(D12);  // attaches the servo to D12

  //Starts OLED
  Serial.begin(115200);
  Serial << endl << "Hello World" << endl;
  // -- OLED --------------
  display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_I2C_ADDRESS);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  //starts OLED

  //sets port for led (ceiling light)
  pinMode (D9, OUTPUT);
  //sets port for led (ceiling light)

  //sets up clock display
  module.setupDisplay(true, 2); // active, brightness = 1
  //sets up clock display
}
void loop() {

  //draws s
  display.drawLine(0, 26, 10, 26, WHITE); //middle line
  display.drawLine(10, 20, 0, 26, WHITE); //first line
  display.drawLine(0, 32, 10, 26, WHITE); //second line
  //draws s

  //draws house
  display.drawLine(14, 32, 14, 25, WHITE); //base of house
  display.drawLine(24, 32, 24, 25, WHITE); //base of house
  display.drawLine(14, 25, 24, 25, WHITE); //base of house
  display.drawLine(14, 25, 19, 20, WHITE); //triangle
  display.drawLine(24, 25, 19, 20, WHITE); //triangle
  //draws house

  //prints out the statuses of the home equipment
  display.setCursor(0, 0);
  display << "The Light is " << light << endl;
  display << "The Blinds are " << blind << endl;
  //prints out the statuses of the home equipment

  display.display();


  //takes in which button was pressed and stores it in the buttons int variable
  buttons = module.getButtons(); // read which buttons are pressed
  //takes in which button was pressed and stores it in the buttons int variable


  //shows the time on the LEDs
  Time t = rtc.time();
  unsigned long a = (t.hr * (long)10000) + (t.min * (long)100) + t.sec;
  module.setDisplayToDecNumber( a, 4, false);
  //shows the time on the LEDs

  //if the button that was pressed was the first one, then the light will turn on and its status in the string variable light will change to on
  if (buttons == 1)
  { digitalWrite(D9, HIGH);
    light = "ON";
    display.clearDisplay();
  }
  //if the button that was pressed was the first one, then the light will turn on and its status in the string variable light will change to on

  //if the button that was pressed was the second one, then the light will turn off and its status in the string variable light will change to off
  if (buttons == 2)
  {
    digitalWrite(D9, LOW);
    light = "OFF";
    display.clearDisplay();
  }
  //if the button that was pressed was the second one, then the light will turn off and its status in the string variable light will change to off


  //if the button that was pressed was the third one, then the blinds will go up and its status in the string variable blind will change to up
  if (buttons == 4)
  {

    for (int cir = 0; cir <= 180; cir += 1) // goes from 0 degrees to 180 degrees
    { // in steps of 1 degree
      myservo.write(180);              // tell servo to go to position in variable 'pos'
      delay(1);                       // waits 15ms for the servo to reach the position
    }
    blind = "up";
    display.clearDisplay();
  }
  //if the button that was pressed was the third one, then the blinds will go up and its status in the string variable blind will change to up


  //if the button that was pressed was the fourth one, then the blinds will go down and its status in the string variable blind will change to down
  if (buttons == 8)
  {

    for (int cir = 180; cir >= 0; cir -= 1) // goes from 180 degrees to 0 degrees
    {
      myservo.write(0);              // tell servo to go to position in variable 'pos'
      delay(1);                       // waits 15ms for the servo to reach the position
    }
    blind = "down";
    display.clearDisplay();
    //if the button that was pressed was the fourth one, then the blinds will go down and its status in the string variable blind will change to down

  }




}










