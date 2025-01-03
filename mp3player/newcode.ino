

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

//songs
  song1 = file.position() ; 
  song2 = 
  song3 = 
  song4 = 
  song5 = 
  song6 = 
  song7 = 
  song8 = 
  song9 = 
  song10 =

currentSong = 1;




Bounce startStopButton = Bounce();
Bounce nextSongButton = Bounce();

// https://www.instructables.com/SD-Card-Module-With-Arduino-How-to-ReadWrite-Data/


// byte length = audio.listInfo(<Song Name>,<buffer[]>,<tagToRequest>);

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

    root = SD.open("/");  //open in root
    printDirectory(root, 0);

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


    //    if (entry.isDirectory()) {
    //
    //      Serial.println("/");
    //
    //      printDirectory(entry, numTabs + 1);
    //
    //    } else {
    //
    //      Serial.print("\t\t");
    //
    //      Serial.println(entry.size(), DEC);
    //
  }
  //    entry.close();
}





//}

void loop() {

  if (Serial.available()) {
    mychar = Serial.read();

    if (mychar == 'p') {  

      audio.play("test.wav");
      Serial.println("kglw baby");

    }

    else if (mychar == 's') {  

      if (audio.isPlaying() == 1) {

        Serial.println("is playing");


      } 
    }
    
    
    else if (mychar == 'd') {  

        audio.stopPlayback();
      
    } 
    
    else if (mychar == '=') {

      audio.volume(1);

      if (volume > 0 && volume < 7) {
        volume = volume + 1;

        Serial.println("Volume ");
        Serial.print(volume);
        Serial.print(" /7 ");
      }

    }

    else if (mychar == '-') {

      audio.volume(0);

      if (volume > 0 && volume < 7) {
        volume = volume - 1;

        Serial.println("Volume ");
        Serial.print(volume);
        Serial.print(" /7 ");
      }
    }
  }
    
    
    else if(nextSongButton.fell()){

    file.openNextFile();

    File entry = dir.openNextFile();
    if (!entry) {
      file.rewindDirectory(); 


}

void loop (){


  if (startStopButton.fell){
    
    if(audio.isPlaying){
      audio.stopPlayback();
    }
    else if{
      audio.play(currentSong);
    }


  }



  else if(nextSongButton.fell()){

    if(currentSong < 11){
      audio.play(currentSong + 1)
      currentSong = currentSong + 1;
    }
    else if(currentSong < 11){
      currentSong = 1;
      audio.play(currentSong)
    }
    


}

 
