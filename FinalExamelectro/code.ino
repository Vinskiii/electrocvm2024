#include <Bounce2.h>

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const byte BOUTON_PIN = 2;

const int switchTime = 500;
const int endTime = 4000;

long time_now;
long startTime;
long stepsTime;
int started = 0;

int randomR;
int randomG;
int randomB;

Bounce bouton = Bounce();
const int INTERVALLE = 25;


void setup() {
  Serial.begin(38400);

  bouton.attach(BOUTON_PIN, INPUT_PULLUP);
  bouton.interval(INTERVALLE);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {

  bouton.update();

  time_now = millis();

  if (bouton.fell()) {
    startTime = time_now;               // etablir le temps de refenrece
    stepsTime = time_now + switchTime;  // etablir le temps de changement de couleur, ici a chaque 500ms
    started = 1;
  }

  if (time_now == stepsTime && started) {  // a chaque fois que le temps reel a compter 500ms et que le "timer" soit commencé

    randomR = random(1, 255);  // creer des varaibles des nombres aleatoire afin de pouvoir les print
    randomG = random(1, 255);
    randomB = random(1, 255);

    analogWrite(redPin, randomR);
    Serial.print("Red :");
    Serial.println(randomR);
    analogWrite(greenPin, randomG);
    Serial.print("Green :");
    Serial.println(randomG);
    analogWrite(bluePin, randomB);
    Serial.print("Blue :");
    Serial.println(randomB);

    stepsTime = time_now + switchTime;          // changer le temps des changements au temps actuel pour pouvoir continuer à ajouter 500ms
  } else if (time_now > startTime + endTime) {  // si 4000ms ce sont decouler depuis le press du bouton les leds se ferme et le "timer" arrete
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    started = 0;
  }
}
