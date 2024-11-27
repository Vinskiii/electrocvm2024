

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

int volume;

TMRpcm audio;  //  Objet TMRpcm nommé "musique"

File root;

char mychar;







// a faire 
 
int trackList[2][10] = {
  {file.position(1), SONG NAME TO PRINT}
  {SONG2 FILE TO READ, SONG2 NAME TO PRINT}
  {SONG3 FILE TO READ, SONG3 NAME TO PRINT}

  THEN AUDIO.PLAY(trackList[currentSong])


  print

}

// a faire 












currentSong = 1;

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

  volume = 0;

  if (SD.begin()) {
    Serial.println("La carte SD a été initialisée");

    root = SD.open("music"); 
    printDirectory(musique, 0);

  } else {
    Serial.println("L’initialisation de la carte SD a échoué!");
    return;
  }
}


void printDirectory(File dir, int numTabs) {

  while (true) {

    File entry = dir.openNextFile();

    if (!entry) {

      if (numTabs == 0)

        Serial.println("** Done **");

      return;
    }


    for (uint8_t i = 0; i < numTabs; i++)

      Serial.print('\t');

    Serial.println(entry.name());
  }
}


void loop (){
  if (startStopButton.fell){
    if(audio.isPlaying){
      audio.stopPlayback();
      Serial.println(file.name(currentSong));
      Serial.print(Pause);
    }
    else if{
      audio.play(currentSong);
      Serial.println(file.name(currentSong));
      Serial.print(Playing);
    }
  } else if(nextSongButton.fell()){
    if(currentSong < 11){
      audio.play(currentSong + 1)
      currentSong = currentSong + 1;
    }
    else if(currentSong < 11){
      currentSong = 1;
      audio.play(currentSong)
    }
  }    
}







 
