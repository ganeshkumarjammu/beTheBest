#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h> 
LiquidCrystal_I2C display(0x27, 16, 2);
Servo myservo ;

int trigPin1 = 8;
int echoPin1 = 9;
 
int trigPin2 = 10;
int echoPin2 = 11;

int currentPeople = 0;
int maxPeople = 5;
int prevCount = -1 ;
int comeIn = 0 ;
int goOut = 0 ;
int  initialDistanceIn = 20 ;
int  initialDistanceOut = 20 ;

void displayText(String txt){
  display.clear();
  display.setCursor(5,0);
  display.print("Welcome");
  display.setCursor(0,1);
  display.print("Visitors: "+txt); 
}
 
int distanceIn, distanceOut ;
 
int measureDistance(int trigPin, int echoPin){
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   int duration = pulseIn (echoPin, HIGH);
   return (duration/2) / 29.1;
}
  
void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT); // declare piezo as output  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT); 
//  initialDistanceIn = measureDistance(trigPin1, echoPin1);
//  initialDistanceOut = measureDistance(trigPin2, echoPin2);
   myservo.attach(5);  
   myservo.write(100); 
   myservo.write(0); 
   display.begin();
   display.backlight();
   display.setCursor (6,0);
   display.print("SOHAM");  
   display.setCursor (0,1);  
   display.print(" Visitors Counter ");  
   delay (1500);  
   display.clear(); 
}

 void loop(){ 
   delay(200);
  distanceIn = measureDistance(trigPin1, echoPin1);
  distanceOut = measureDistance(trigPin2, echoPin2); 
  Serial.println("distanceIn: ");
  Serial.println(distanceIn);
  Serial.print("distanceOut: ");
  Serial.println(distanceOut);
  Serial.println("goOut: && comeIn:  ");
  Serial.println(goOut);
  Serial.println(comeIn);
  if(distanceIn < initialDistanceIn){
    if (!(goOut||comeIn)){
      comeIn = 1; 
      myservo.write(180);
      delay(10);
    }
    else if (goOut){
      currentPeople-- ;
      goOut = 0 ;
      myservo.write(0);
      delay(200);
       }
    else {
      Serial.print("Bloacking In Sensor,Soham");
    }
  } 
  if(distanceOut < initialDistanceOut){
    if(!(comeIn )){ 
      goOut = 1;
      myservo.write(180);
      delay(500);
    }
    else if(comeIn){
      currentPeople++ ;
      comeIn = 0 ;
      myservo.write(0);
      delay(500);
    }
    else {
      Serial.print("Bloacking Out Sensor,Soham");
    }
  }
  Serial.println("People :");
  Serial.println(currentPeople);
  if ((currentPeople != prevCount) && (currentPeople >= 0 ) ){
  displayText(String(currentPeople));
  prevCount = currentPeople ;
  }
  else if(currentPeople < 0){
    currentPeople = 0 ;
  }
}  
