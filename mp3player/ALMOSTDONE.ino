#include <TMRpcm.h>
#include <pcmConfig.h>
#include <pcmRF.h>
#include <SD.h>



/*********************************************************************************************
 *  Lecteur de musique Arduino
 *  par Vincent Brochu
 * 
 *  Pour la conversion des fichiers audio en fichier .wav avec les paramètres suivants :
 *    bit resolution : 8 Bit
 *    sampling rate  : 32000 Hz
 *    audio channel  : mono
 *  
 *  Pour convertir gratuitement : https://audio.online-convert.com/convert-to-wav
 *
 ********************************************************************************************/

/*********************************************************************************************
 *  Connexions du circuit
 *  
 *  pin 2 : Bouton Lecture / Arrêt
 *  pin 3 : Bouton Chanson suivante
 *  pin 9 : Sortie Audio
 *  pin 10 : CS (SS sur la carte carte SD)
 *  pin 11 : MOSI (MOSI sur la carte SD)
 *  pin 12 : MISO (MISO sur la carte SD)
 *  pin 13 CLK (SCK sur la carte SD)
 *    par défaut, MOSI, MISO et CLK doivent être sur 11, 12, et 13 pour Arduino UNO.

 *********************************************************************************************/


#include <Bounce2.h>
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
#include <pcmConfig.h>
#include <pcmRF.h>


const byte SD_CS_PIN = 53;    // Carte SD (SS) sur la pin 10
const byte SD_MOSI_PIN = 51;  // Carte SD (MOSI) sur la pin 11
const byte SD_MISO_PIN = 50;  // Carte SD (MISO) sur la pin 12
const byte SD_CLK_PIN = 52;   // Carte SD (SCK) sur la pin 13
const byte STARTSTOP_PIN = 2;
const byte NEXTSONG_PIN = 3;
const byte SOUNDOUT_PIN = 5;

int positionCurrentSong = 1;
int volume;
int index;
int i = 0;

TMRpcm audio;

File root;

char mychar;


char trackList[10][20];


Bounce startStopButton = Bounce();
Bounce nextSongButton = Bounce();


void setup() {

  Serial.begin(115200);

  startStopButton.attach(STARTSTOP_PIN, INPUT_PULLUP);
  nextSongButton.attach(NEXTSONG_PIN, INPUT_PULLUP);

  startStopButton.interval(5);
  nextSongButton.interval(5);


  audio.speakerPin = 11;
  audio.setVolume(0);


  if (SD.begin()) {
    Serial.println("La carte SD a été initialisée");

    root = SD.open("/");
    printDirectory(root);
    index = 1;
    audio.setVolume(4);


  } else {
    Serial.println("L’initialisation de la carte SD a échoué!");
    return;
  }
}


void printDirectory(File dir) {

  while (true) {

    File entry = dir.openNextFile();

    if (!entry) {

      Serial.println("** Done **");

      return;
    }

    Serial.println(entry.name());

    strcpy(trackList[i], entry.name());

    i++;
  }
}


void loop() {

  if (Serial.available()) {
    mychar = Serial.read();

    if (mychar == 'p') {
      if (audio.isPlaying()) {

        Serial.println(index);
        Serial.println("Pause");
        audio.stopPlayback();

      } else {
        Serial.println(index);
        Serial.println("Playing");
        audio.play(trackList[index]);
      }
    }

    else if (mychar == 's') {

      Serial.println(trackList[index]);

    }

    else if (mychar == 'n') {

      if (index <= i) {

        index++;
        audio.play(trackList[index]);

      } else {
        index = 1;
      }
    }
  }
}
