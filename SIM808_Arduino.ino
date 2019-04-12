#include <SoftwareSerial.h>
SoftwareSerial sim808(7,8);
//GPS-GSM
char phone_no[] = "9156659369"; // your phone no.
String data[5];
#define DEBUG true
String state,timegps,latitude,longitude;

//ULTRASONIC
const int  trigPin = 9;
const int echoPin = 10;
const int buzzPin=11;
long duration;
int distance;

String sendData (String command , const int timeout ,boolean debug)
{
  String response = "";
  sim808.println(command);
  long int time = millis();
  int i = 0;

  while ( (time+timeout ) > millis())
  {
    while (sim808.available())
    {
      char c = sim808.read();
      response +=c;
    }
  }
  if (debug) {
     Serial.print(response);
     }
     return response;
}

void setup()
{
      /*Serial.begin(9600);
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
      pinMode(buzzPin,OUTPUT); 
      pinMode(3,OUTPUT);
      pinMode(4,OUTPUT);
      pinMode(5,OUTPUT);
      pinMode(6,OUTPUT);*/
    
     sim808.begin(9600);
     Serial.begin(9600);
  
     delay(300);
     sim808.println("AT+CMGF=1");
     delay(1000);
  
     sim808.println("AT+CNMI=2,2,0,0,0");
     delay(1000);
  
     sim808.println("AT+CSMP=17,167,0,0");  // set this parameter if empty SMS received
     delay(100);
     sendData("AT+CGNSPWR=1",1000,DEBUG); 
     delay(50);
     sendData("AT+CGNSSEQ=RMC",1000,DEBUG);
     delay(150); 

}

void sendTabData(String command , const int timeout , boolean debug){

  sim808.println(command);
  long int time = millis();
  int i = 0;

  while((time+timeout) > millis()){
    while(sim808.available()){
      char c = sim808.read();
      if (c != ',') {
         data[i] +=c;
         delay(100);
      } else {
        i++;  
      }
      if (i == 5) {
        delay(100);
        goto exitL;
      }
    }
  }exitL:
  if (debug) {
    state = data[1];
    timegps = data[2];
    latitude = data[3];
    longitude =data[4];  
  }
}


void loop()
{
    char data;
    String inputString = "";         
    String incomingString ="";
    String Number="";

    Ultra();
    
    //MOTOR
    if(Serial.available() > 0)
    {
      //Serial.println(data);
      data =Serial.read();
      Serial.println(data);
      if(data == 'F')
      {
        //Serial.println(" Forward ");
        digitalWrite(3,HIGH);//forword
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(6,LOW);
        //Serial.print(data);
        delay(1000);
        //digitalWrite(3,LOW); 
        //digitalWrite(5,LOW);
      }
      else if(data == 'S')
      {
         //    Serial.println(" STOP ");
         digitalWrite(6,LOW);//stop
         digitalWrite(5,LOW);
         digitalWrite(4,LOW);
         digitalWrite(3,LOW);
         //Serial.print(data);
         delay(1000);
      }
      else if(data == 'L')
      {
        digitalWrite(6,HIGH);//left
        digitalWrite(5,LOW);
        digitalWrite(4,LOW);
        digitalWrite(3,HIGH);
        //Serial.print(data);
        delay(1000);
        digitalWrite(3,LOW); 
        digitalWrite(6,LOW);  
      }
      else if(data == 'R')
      {
         digitalWrite(6,LOW);//right
         digitalWrite(5,HIGH);
         digitalWrite(4,HIGH);
         digitalWrite(3,LOW);
         //Serial.print(data);  
         delay(1000);
         digitalWrite(5,LOW);         
         digitalWrite(4,LOW);  
      }
      digitalWrite(6,LOW);//stop
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,LOW);    
    }
    
    
    //GPS-GSM
    if (sim808.available()>0)
    {  
        incomingString=sim808.readString();
        Serial.println(incomingString);
        for(int i=9;i<22;i++)
        {
            Number += incomingString[i];
        }
        for(int i=51;i<55;i++)
        {
            inputString += incomingString[i];
        }
        Serial.println(Number);
        if((Number=="+919156659369"))
        {  
            sendTabData("AT+CGNSINF",1000,DEBUG);
            if (state !=0)
            {
                Serial.println("State  :"+state);
                Serial.println("Time  :"+timegps);
                Serial.println("Latitude  :"+latitude);
                Serial.println("Longitude  :"+longitude);
                sim808.println("AT+CMGF=1\r"); 
                delay(400);
           
                sim808.print("AT+CMGS=\"");
                sim808.print(phone_no);
                sim808.println("\"");
                
                delay(300);
            
                sim808.print("http://maps.google.com/maps?q=loc:");
                sim808.print(latitude);
                sim808.print(",");
                sim808.print (longitude);
                delay(200);
                sim808.println((char)26); // End AT command with a ^Z, ASCII code 26
                delay(200);
                Serial.println("Message send"); // End AT command with a ^Z, ASCII code 26
                
                sim808.println();
                delay(20000);
                sim808.flush();
                
              } 
              else 
              {  Serial.println("GPS Initialising...");              
              }
         }
 }
}

void Ultra()
{
      int dist;
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(2);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      dist=(duration/2)/29.1;
      //Serial.println(dist);
      if(dist<=10)
      {
        digitalWrite(buzzPin,HIGH);
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        delay(1000);        
       digitalWrite(buzzPin,LOW);
      }
      else
      {
        digitalWrite(buzzPin,LOW);
      }      
      //sSerial.println(dist);
      delay(1000);
}
