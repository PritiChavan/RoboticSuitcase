const int  trigPin = 7;
const int echoPin = 8;
const int buzzPin=9;
long duration;
int distance;

void setup() 
{  
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin,OUTPUT); 
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}
 
void loop() 
{
      int dist;
       // Serial.println("loop");
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(2);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      dist=(duration/2)/29.412;
      //Serial.println(dist);
      if(dist<=100 && dist>=0)
      {
        digitalWrite(buzzPin,HIGH);
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        delay(100);
        digitalWrite(buzzPin,LOW);
      }
      else
      {
        digitalWrite(buzzPin,LOW);
      }
      
      Serial.println(dist);
      delay(1000);
       
}
