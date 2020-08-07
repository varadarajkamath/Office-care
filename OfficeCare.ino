// DLITHE INTERNSHIP PROGRAM
// TINKERCAD CIRCUIT FOR OFFICE CARE SYSTEM USING IoT SOLUTIONS

#define sig1 2
#define sig2 4
#define grn 7
#define red 8
#define buzz 9
#include<Servo.h>
Servo glassdoor; //Glass door at the entrance
Servo sanitizer; //Sanitizer Dispenser machine
Servo passgate; //Passgate after applying sanitizer

long dur1, dis1;
long dur2, dis2;

void setup() 
{
  pinMode(grn,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(buzz,OUTPUT);
  glassdoor.attach(3);
  sanitizer.attach(5);
  passgate.attach(6);
  Serial.begin(9600);
}

void loop() 
{
  // Ultrasonic sensor used for controlling Glass Door 
 
  pinMode(sig1, OUTPUT);
  digitalWrite(sig1, LOW);
  delayMicroseconds(2);
  digitalWrite(sig1, HIGH);
  delayMicroseconds(3);
  digitalWrite(sig1, LOW);

  pinMode(sig1, INPUT);
  dur1 = pulseIn(sig1, HIGH);

  dis1 = dur1 / 29 / 2;     // In order to find distance of the incoming object,
                 // We need to calculate half of the distance travelled by the signal
                // Speed of sound is 29 ms per cm (340 m/s)
  delay(100);
  
  // Operation of the Glass Door
  
  if(dis1 <=120) // Incoming object at less than a certain distance is detected to avoid stray operation
  {
    glassdoor.write(90); // Door opens
    Serial.println("WELCOME TO OUR OFFICE");
  }
  else
  {
    glassdoor.write(0); // Door returns to original position
  }
  
  
  // Ultrasonic sensor used for Sanitizer dispenser
  
  pinMode(sig2, OUTPUT);
  digitalWrite(sig2, LOW);
  delayMicroseconds(2);
  digitalWrite(sig2, HIGH);
  delayMicroseconds(5);
  digitalWrite(sig2, LOW);

  pinMode(sig2, INPUT);
  dur2 = pulseIn(sig2, HIGH);

  dis2 = dur2 / 29 / 2;
  
  // Operation of the Sanitizer Dispenser
  
  sanitizer.write(0); // Initial position of the dispenser motor
  if(dis2 <= 50)
  {
    sanitizer.write(180); // One full rotation to dispense sanitizer
    Serial.println("PLEASE APPLY SANITIZER");
    delay(3000);
    sanitizer.write(0); // Back to original position
    delay(2000);
  }
  else
  {
    sanitizer.write(0);
    delay(10);
  }
  
  // Passgate control
  
  passgate.write(0); // Initial position of the passgate
  if(dis2 <=50)
  {
    delay(3000);
    passgate.write(90);
    Serial.println("PLEASE ENTER");
    
    digitalWrite(red,LOW); // RED LED is OFF
    digitalWrite(buzz,LOW); // BUZZER is OFF
    
    // GREEN LED blinks thrice to indicate the passgate opening
      digitalWrite(grn,HIGH); // Blink 1
      delay(1500);
      digitalWrite(grn,LOW);
      delay(1500);
      digitalWrite(grn,HIGH); // Blink 2
      delay(1500);
      digitalWrite(grn,LOW);
      delay(1500);
      digitalWrite(grn,HIGH); // Blink 3
      delay(1500);
      digitalWrite(grn,LOW);
      delay(1000);
    
      passgate.write(0);
      digitalWrite(grn,LOW);
      digitalWrite(red,HIGH); // RED LED turns ON
      digitalWrite(buzz,HIGH); // Long buzz to indicate the closure of the passgate
      Serial.println("GATE IS CLOSING!");
      delay(1000);
  }
}
