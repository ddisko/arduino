#include <Servo.h> //include servo library

 int redPin = 11; //pin our red LED is connected to
 int bluePin = 5; //pin our blue LED is connected to
 int greenPin = 9; //pin our green LED is connected to
 int buttonPin = 7; //pin our button is connected to
 int servoPin = 6; //pin our servo is connected to

 int ledState = LOW; //used to control red LED state, we're starting with it OFF
 byte brightness = 0; //starting LED brightness
 byte fadeIncrement = 1; //how much to change the brightness after each period
 int toggleState = LOW; //used to control the toggle state of our green LED, we're starting with it OFF
 int servoIncrement = 1; //how much to move the servo horn each period
 int servoPos = 0; //starting servo position

 Servo servo; //create a servo object
 
 unsigned long currentMillis = 0; //stores the current time

 unsigned long blinkPreviousMillis = 0; //stores last time red LED was blinked
 unsigned long fadePreviousMillis = 0; //stores last time blue LED was faded up
 unsigned long buttonPreviousMillis = 0; //stores the last time button read took place
 unsigned long servoPreviousMillis = 0; //stores the last time the servo horn moved

 const unsigned long blinkPeriod = 500; //interval to blink red LED in milliseconds
 const unsigned long fadePeriod = 10; //interval to fade blue LED in milliseconds
 const unsigned long buttonPeriod = 100; //interval to read the button
 const unsigned long servoPeriod = 15; //interval to move the servo horn

 void blinkLED() {
  /*if the difference between the current time and last time the LED blinked is greater than or equal to the blink period, we need to blink the LED*/
  if (currentMillis - blinkPreviousMillis >= blinkPeriod) {
   //record the current time the blink happens to blinkPreviousMillis
   blinkPreviousMillis = currentMillis;
   //if the LED is off (LOW) change the LED state to on (HIGH)
   if (ledState == LOW) {
    ledState = HIGH;
   }
   /*if the LED is on (HIGH), turn it off (LOW)*/
   else {
    ledState = LOW;
   }
   //output the state of the red LED
  digitalWrite(redPin, ledState);
  }
 }

 void fadeLED() {
  /*if the difference between the current time and last time the LED faded up is greater than or equal to the fade period, we need to increment the brightness of the LED*/
  if (currentMillis - fadePreviousMillis >= fadePeriod) {
   //record the current time the fade happens to fadePreviousMillis
   fadePreviousMillis = currentMillis;
   //output the brightness of the LED
   analogWrite(bluePin, brightness);
   //increase the brightness by 1 increment for the next period
   brightness += fadeIncrement;
   }
 }

 void toggleLED() {
  /*if the difference between the current time and last time the button was read is greater than or equal to the button period, we need to read the button*/
  if (currentMillis - buttonPreviousMillis >= buttonPeriod) {
   //record the current time the button read happens to buttonPreviousMillis
   buttonPreviousMillis = currentMillis;
   //if the button reads LOW, that means it has been pressed so light up the green LED
   if (digitalRead(buttonPin) == LOW) {
    toggleState = HIGH;
   }
   /*otherwise, keep the green LED off*/
   else {
    toggleState = LOW;
   }
  //output the state of the green LED
  digitalWrite(greenPin, toggleState);
  }
 }

 void servoSweep() {
  /*if the difference between the current time and last time the servo horn moved is greater than or equal to the servo period, we need to move the servo horn*/
  if (currentMillis - servoPreviousMillis >= servoPeriod) {
   //record the current time the servo horn movement happens to servoPreviousMillis
   servoPreviousMillis = currentMillis;
   //increment the servo position by 1
   servoPos += servoIncrement;
   /*if the servo position goes above 180, reverse the increment by turning it negative. If the servo position goes below 0 then reverse the neg increment to positive*/
   if ((servoPos > 180) || (servoPos < 0)) {
    servoIncrement = -servoIncrement;
   }
   //output the servo horn position
   servo.write(servoPos);
  }
 }

 void setup() {
  pinMode(redPin, OUTPUT); //set red LED pin as an output
  pinMode(bluePin, OUTPUT); //set blue LED pin as an output
  pinMode(greenPin, OUTPUT); //set green LED pin as an output
  pinMode(buttonPin, INPUT_PULLUP); //set button to an input using the internal pull-up resistor
  servo.attach(servoPin); //attach the servo
 }

 void loop() {
  //check millis for the current time
  currentMillis = millis();

  blinkLED(); //run the blinkLED function
  fadeLED(); //run the fadeLED function
  toggleLED(); //run the toggleLED function
  servoSweep(); //run the servoSweep function
 }
