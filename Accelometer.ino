/*#include <SoftwareSerial.h>*/
#include <math.h>

/*#define BT_SERIAL_RX TX1
#define BT_SERIAL_TX RX0*/
/*SoftwareSerial BluetoothSerial(1,0); // rx,tx*/

const int x_out = A1; /* connect x_out of module to A1 */
const int y_out = A2; /* connect y_out of module to A2 */
const int z_out = A3; /* connect z_out of module to A3*/ 


float angle_x;
float angle_y;
float angle_z;
int x_adc_value, y_adc_value, z_adc_value; 
double x_g_value, y_g_value, z_g_value;
char ch[20],x_loc[5],y_loc[5];
double x_new=0,y_new=0;
double x_prev=0,y_prev=0;
void setup()
{
  Serial.begin(9600); 
  //BluetoothSerial.begin(9600);
       Acceleration();
         x_prev=x_g_value;
         //Serial.print(" X _prev = ");
         //Serial.print(x_prev);           
         y_prev=y_g_value;
         //Serial.print(" Y_prev = ");
        // Serial.println(y_prev);

}
void loop()
{
 
        Acceleration();
        x_new=x_g_value;
        //Serial.print(" X_new = ");
        //Serial.print(x_new);
        y_new=y_g_value;
        //Serial.print(" Y_new = ");
        //Serial.println(y_new);        
        double difference1_x=(x_new-x_prev);
        double difference2_y=abs(y_new-y_prev);
        //Serial.print("difference1_x=");
        //Serial.println(difference1_x);
        //Serial.print("difference2_y=");
        //Serial.println(difference2_y);
         if(difference2_y>0.04)
         {
          //Serial.println("A");
          Serial.println("F");
          }        
         else if(x_new >= (0.45) ) 
         {//Serial.println("B");
             Serial.println("L");
         }               
         else if(x_new <= (0.35) ) 
         {//Serial.println("B");
             Serial.println("R");
         }
         else{ Serial.println("S");}
          x_prev=x_new;
          y_prev=y_new;
          delay(2000);
}

void Acceleration()
{
        x_adc_value = analogRead(x_out); /* Digital value of voltage on x_out pin */ 
        y_adc_value = analogRead(y_out);  
        z_adc_value = analogRead(z_out); 
          
        x_g_value = ( ( ( (double)(x_adc_value * 5)/1024) - 1.65 ) / 0.330 ); /* Acceleration in x-direction*/ 
        y_g_value = ( ( ( (double)(y_adc_value * 5)/1024) - 1.65 ) / 0.330 );  
        z_g_value = ( ( ( (double)(z_adc_value * 5)/1024) - 1.80 ) / 0.330 );   
}
