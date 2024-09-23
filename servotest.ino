// servo driver test using pca9685 driver board

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Settings for servo swing range, needs to stay in safe zone 
// so not to stall servo at either end

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

// address of servo(s) 0 through 15
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  pwm.begin();

// regular servos run at ~60 Hz updates
  pwm.setPWMFreq(60);  
  yield();
}

// first number = servo location, second number = , third number = number of steps
void loop() {

    pwm.setPWM(0, 0, 125 );
	delay(500);
    pwm.setPWM(0, 0, 255 );
	delay(500);
    pwm.setPWM(0, 0, 450 );
	delay(500);
    pwm.setPWM(0, 0, 575 );
	delay(500);	

 
}