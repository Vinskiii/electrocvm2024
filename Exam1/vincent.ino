#include <Bounce2.h>

unsigned long TIME_NOW = 0 ;
unsigned long TIME_AFTERON = 0 ;
const int PERIODE = 1000;
const byte  LEDV_PIN = 7;
const byte  LEDJ_PIN = 8;
const byte  LEDR_PIN = 9;
const byte  LEDBLINK_PIN = 2;
const byte BOUTON_PIN = 12;
const byte LED_ARD = 13;
const byte INTERVALLE = 5;
int valPot = 0;
int valON_V = 101;
int valON_J = 501;
int valON_R = 901;
bool ledState = LOW;
Bounce bouton = Bounce();

void setup() {

  Serial.begin(9600);
  bouton.attach(BOUTON_PIN, INPUT_PULLUP);
  bouton.interval(INTERVALLE);
  digitalWrite(13,ledState);
  pinMode(13,OUTPUT); // LED ON ou OFF
  pinMode(LEDV_PIN,OUTPUT); // LED Verte
  pinMode(LEDJ_PIN,OUTPUT); // LED Jaune
  pinMode(LEDR_PIN,OUTPUT); // LED Rouge
  pinMode(LEDBLINK_PIN,OUTPUT); // LED BLINK BONUS

}

void loop() {
  
  bouton.update();
  valPot = analogRead(A5);
  TIME_NOW = millis(); //reset millis a 0
  Serial.println(valPot);

  if (bouton.fell() ) 
    {
      ledState = !ledState ;
      digitalWrite(13,ledState);
    }

 if( millis() < TIME_NOW + PERIODE) //Temps entre 0 et 1 secondes ON
    {
      digitalWrite(2,HIGH);
      TIME_AFTERON = millis();
    }

if(millis() < (TIME_AFTERON + PERIODE))
    {      
      digitalWrite(2, LOW);
    }
  
if (ledState == 0)
  {  
    if (valPot >= valON_V)
      {    
        digitalWrite(LEDV_PIN,HIGH);
      }
      else 
        {
          digitalWrite(LEDV_PIN,LOW);
        }

    if (valPot >= valON_J)
      {
        digitalWrite(LEDJ_PIN,HIGH);
      }
      else 
        {
          digitalWrite(LEDJ_PIN,LOW);
        }

    if (valPot >= valON_R)
      {
        digitalWrite(LEDR_PIN,HIGH);
      }
      else 
        {
          digitalWrite(LEDR_PIN,LOW);
        }
  }
}
