#include <Bounce2.h>

int period = 1000;
unsigned long time_now = 0;
int randomLoading ;
const byte DE6 = 6 ;
const byte DE16 = 16;
const byte NB_LEDS = 7;
const int LEDPIN[7] = {7,8,9,10,11,12,13};
const byte BOUTON_PIN = 2;
const byte SWITCH_PIN = 3;
const int INTERVALLE = 25;
Bounce bouton = Bounce();

const bool DE6_LEDS[DE6][NB_LEDS] =
{
  { 0 , 1 , 1 , 0 , 0 , 0 , 0 },  //  1
  { 1 , 1 , 0 , 1 , 1 , 0 , 1 },  //  2 
  { 1 , 1 , 1 , 1 , 0 , 0 , 1 },  //  3
  { 0 , 1 , 1 , 0 , 0 , 1 , 1 },  //  4
  { 1 , 0 , 1 , 1 , 0 , 1 , 1 },  //  5
  { 1 , 0 , 1 , 1 , 1 , 1 , 1 },  //  6

};
 
const bool DE16_LEDS[DE16][NB_LEDS] =
{
  { 0 , 1 , 1 , 0 , 0 , 0 , 0 },  //  1
  { 1 , 1 , 0 , 1 , 1 , 0 , 1 },  //  2 
  { 1 , 1 , 1 , 1 , 0 , 0 , 1 },  //  3
  { 0 , 1 , 1 , 0 , 0 , 1 , 1 },  //  4
  { 1 , 0 , 1 , 1 , 0 , 1 , 1 },  //  5
  { 1 , 0 , 1 , 1 , 1 , 1 , 1 },  //  6  
  { 1 , 1 , 1 , 0 , 0 , 0 , 0 },  //  7  
  { 1 , 1 , 1 , 1 , 1 , 1 , 1 },  //  8  
  { 1 , 1 , 1 , 0 , 0 , 1 , 1 },  //  9  
  { 1 , 0 , 1 , 1 , 1 , 1 , 1 },  //  A  
  { 0 , 0 , 1 , 1 , 1 , 1 , 1 },  //  B  
  { 1 , 0 , 0 , 1 , 1 , 1 , 1 },  //  C  
  { 0 , 0 , 1 , 1 , 1 , 0 , 1 },  //  D  
  { 1 , 0 , 0 , 1 , 1 , 1 , 1 },  //  E  
  { 1 , 0 , 0 , 0 , 1 , 1 , 1 },  //  F  
  

};




long randomNumber;


void setup() {


  Serial.begin(9600);
  randomSeed(analogRead(A0));
  bouton.attach(BOUTON_PIN, INPUT_PULLUP);
  bouton.interval(INTERVALLE);


  
  pinMode(3,INPUT); // pin switch
  pinMode(LEDPIN[0],OUTPUT); // led a
  pinMode(LEDPIN[1],OUTPUT); // led b
  pinMode(LEDPIN[2],OUTPUT); // led c
  pinMode(LEDPIN[3],OUTPUT); // led d
  pinMode(LEDPIN[4],OUTPUT); // led e
  pinMode(LEDPIN[5],OUTPUT); // led f
  pinMode(LEDPIN[6],OUTPUT); // led g
  
  

  
  

  

}

void loop() {

  bouton.update();

  
 
if (digitalRead(3) == 1)
  {
   randomNumber = random(6 + 1);
  }
if (digitalRead(3) == 0)
  {
    randomNumber = random(16 + 1);
  }  

  


  


if (bouton.fell())
  {
    
    time_now = millis();
      
    while(millis() < time_now + period) 
        {
          randomLoading = random(7 + 1);
          
          digitalWrite(LEDPIN[randomLoading], HIGH);
          
          delay(20);
          digitalWrite(LEDPIN[randomLoading], LOW);
          
         
          
        }
    
    

    
  

            
      if(digitalRead(3)== 1)
        {
           
        Serial.println(randomNumber);
            
        digitalWrite(LEDPIN[0], DE6_LEDS[(randomNumber - 1)][0]);    
        digitalWrite(LEDPIN[1], DE6_LEDS[(randomNumber - 1)][1]);
        digitalWrite(LEDPIN[2], DE6_LEDS[(randomNumber - 1)][2]);
        digitalWrite(LEDPIN[3], DE6_LEDS[(randomNumber - 1)][3]);
        digitalWrite(LEDPIN[4], DE6_LEDS[(randomNumber - 1)][4]);
        digitalWrite(LEDPIN[5], DE6_LEDS[(randomNumber - 1)][5]);
        digitalWrite(LEDPIN[6], DE6_LEDS[(randomNumber - 1)][6]);
        
        }

      else
        {
        
          
        Serial.println(randomNumber);
            
        digitalWrite(LEDPIN[0], DE16_LEDS[(randomNumber - 1)][0]);    
        digitalWrite(LEDPIN[1], DE16_LEDS[(randomNumber - 1)][1]);
        digitalWrite(LEDPIN[2], DE16_LEDS[(randomNumber - 1)][2]);
        digitalWrite(LEDPIN[3], DE16_LEDS[(randomNumber - 1)][3]);
        digitalWrite(LEDPIN[4], DE16_LEDS[(randomNumber - 1)][4]);
        digitalWrite(LEDPIN[5], DE16_LEDS[(randomNumber - 1)][5]);
        digitalWrite(LEDPIN[6], DE16_LEDS[(randomNumber - 1)][6]);
        }       
  
      
    
  }
 
}
