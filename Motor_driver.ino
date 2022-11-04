#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial myserial(A0, A1); // rx | tx
// TX from bluetooth module must connect to rx pin and vice versa

// Variable declarations
AF_DCMotor motor1(3);
AF_DCMotor motor2(4);
char msg;
int mySpeed = 150;
int mydelay = 10;
char gearMove[] = "udxm";


void setup() 
{
  // Setting up the serial connection
  Serial.begin(38400); // opens the serial port
  myserial.begin(9600); // this must be the baud rate of the module not the arduino 
  
	//Set initial speed of the motor & stop
	motor1.setSpeed(200);
  motor2.setSpeed(200);
	motor1.run(RELEASE);
	motor2.run(RELEASE);  
}

void loop() 
{
	uint8_t i;

  if(myserial.available()>0) { // this listens for a msg from the bluetooth module
    msg = myserial.read(); // reads the message
  }

  Serial.println(msg); // this is so that we see the message sent in the serial monitor  
  // Serial.println(mySpeed);
  
  if (msg == 'f') {   
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor1.setSpeed(mySpeed);
    motor2.setSpeed(mySpeed);
    delay(mydelay);
  } else if (msg == 'b') {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor1.setSpeed(mySpeed);
    motor2.setSpeed(mySpeed);
    delay(mydelay);    
  } else if (msg == 'l') {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor1.setSpeed(mySpeed);
    motor2.setSpeed(mySpeed);
    delay(mydelay);    
  } else if (msg == 'r') {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor1.setSpeed(mySpeed);
    motor2.setSpeed(mySpeed);
    delay(mydelay);    
  }else if (msg == 'a') {
    digitalWrite(13, HIGH);
  }else if (msg == 'b') {
    digitalWrite(13, LOW); 
  } else {
    motor1.run(RELEASE);
    motor2.run(RELEASE);    
  }

  for (int i=0; i<4; i++) {
      if (msg == gearMove[i]) {
        mySpeed = changeGear(msg, mySpeed);
        delay(100);
    }
  }



}

int changeGear(char x, int mySpeed){
  
    switch (x) {
    case 'u':
      if (mySpeed < 250){
        mySpeed = mySpeed + 50;
      } 
      break;
    case 'd':
      if (mySpeed > 150){
        mySpeed = mySpeed - 50;
      }
      break;
    case 'x':
      mySpeed = 150;
      break;
    case 'm':
      mySpeed = 250;
      break;
    default:
      mySpeed = mySpeed;
      break;
  }
  
  return mySpeed;
}
