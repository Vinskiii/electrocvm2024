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
int maxSongs = 1;
int val;
char mychar;
TMRpcm audio;
File root;
Bounce startStopButton = Bounce();
Bounce nextSongButton = Bounce();
char trackList[255][20];

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
  int i = 0;
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      Serial.println("** Done **");
      break;
    }
    Serial.println(entry.name());
    strcpy(trackList[i], entry.name());
    i++;
  }
  maxSongs = i - 1;
}

void loop() {

  val = analogRead(0);
  audio.setVolume(volumeLevel(val));

  if (Serial.available()) {
    mychar = Serial.read();
    switch (mychar) {
      case 'p':
        if (audio.isPlaying()) {
          audio.stopPlayback();
        } else {
          audio.play(trackList[index]);
        }
        printSongList();
        break;
      case 'n':
        if (index < maxSongs) {
          index++;
          audio.play(trackList[index]);
        } else {
          index = 1;
        }
        printSongList();
        break;
      case 's':
        Serial.println("testing branch");
    }
  }
}
int volumeLevel(int val) {
  val = map(val, 0, 1023, 0, 7);
  return val;
}
void printSongList() {
  for (int songList = 1; songList <= maxSongs; songList++) {
    Serial.print(trackList[songList]);
    if (index == songList) {
      if (audio.isPlaying()) {
        Serial.print("     Playing");
      } else {
        Serial.print("     Pause");
      }
    }
    Serial.println("");
  }
}

