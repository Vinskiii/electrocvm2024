

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

const byte SD_CS_PIN = 10;    // Carte SD (SS) sur la pin 10
const byte SD_MOSI_PIN = 11;  // Carte SD (MOSI) sur la pin 11
const byte SD_MISO_PIN = 12;  // Carte SD (MISO) sur la pin 12
const byte SD_CLK_PIN = 13;   // Carte SD (SCK) sur la pin 13
const byte STARTSTOP_PIN = 2;
const byte NEXTSONG_PIN = 3;
const byte SOUNDOUT_PIN = 9;

int positionDansDir;

TMRpcm musique;  //  Objet TMRpcm nommé "musique"

File root;


Bounce startStopButton = Bounce();
Bounce nextSongButton = Bounce();

// https://www.instructables.com/SD-Card-Module-With-Arduino-How-to-ReadWrite-Data/

void setup() {

  Serial.begin(115200);  //  initialisation du port série

  startStopButton.attach(STARTSTOP_PIN, INPUT_PULLUP);
  nextStopButton.attach(NEXTSONG_PIN, INPUT_PULLUP);
  
  startStopButton.interval(5);
  nextStopButton.interval(5);

  startStopButton.setPressedState(LOW); 
  nextStopButton.setPressedState(LOW); 


  //  initialisation de la carte SD
  if (SD.begin()) {
    Serial.println("La carte SD a été initialisée");
  } else {
    Serial.println("L’initialisation de la carte SD a échoué!");
    return;
  }

  root = SD.open("/")  //open in root
  printDirectory(root, 0);

  


}

void printDirectory(File dir, int numTabs) {

  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print("\t")
    }

    Serial.print(entry.name()) {
      if (entry.isDirectory()) {
        Serial.println("/");
        printDirectory(entry, numtabs + 1);
      } else {
        Serial.print("\t\t");
        Serial.println(entry.size(), DEC)
      }
    }
  }
}



void loop() {

  startStopButton.update();
  nextSongButton.update();

  if(startStopButton.pressed()){

    

  

    //en pause write le dir avec  > ou ||

  }
  
  if(nextSongButton.pressed()){

    file.openNextFile();

    File entry = dir.openNextFile();
    if (!entry) {
      file.rewindDirectory();
    }


  }
}
