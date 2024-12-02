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
int index;
int maxSongs = 1;
int val;
int songList = 1;
char mychar;
TMRpcm audio;
File root;
Bounce startStopButton = Bounce();
Bounce nextSongButton = Bounce();
char trackList[255][20];
int whichButtonPressed;

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
    audio.setVolume(3);
  } else {
    Serial.println("L’initialisation de la carte SD a échoué!");
    return;
  }
}

void printDirectory(File dir) {
  int i = 0;
  while (true)  // Boucle infinie pour lire tous les fichiers du répertoire
  {
    File entry = dir.openNextFile();  // Ouvre le prochain fichier dans le répertoire
    if (!entry)                       // Si le fichier n'existe pas, on sort de la boucle et on affiche le message "Completed reading files"
    {
      Serial.println("Completed reading files");
      break;
    }
    Serial.println(entry.name());        // Affiche le nom du fichier
    strcpy(trackList[i], entry.name());  // Copie le nom du fichier dans le array trackList
    i++;                                 // Incrémente le compteur de fichiers
  }
  maxSongs = i - 1;  // Détermine le nombre de fichiers dans le répertoire et -1 car le premier nom est system1
}

void loop() {
  val = analogRead(0);                // Lecture de la valeur du potentiomètre
  audio.setVolume(volumeLevel(val));  // Ajuste le volume selon la valeur du potentiomètre avec la valeur mapper entre 0 et 7
  startStopButton.update();
  nextSongButton.update();
  if (startStopButton.fell()) {  // Si le bouton de lecture est appuyé
    if (audio.isPlaying()) { // Si la musique joue, on arrête la lecture et si la musique est arrêtée, on démarre la lecture
      audio.stopPlayback();
    } else {
      audio.play(trackList[index]);
    }
    printSongList();
  } else if (nextSongButton.fell()) { // Si le bouton de chanson suivante est appuyé on incrémente l'index et si l'index est plus grand que le nombre de chansons, on revient à 1
    if (index < maxSongs) {
      index++;
    } else {
      index = 1;
    }
    audio.play(trackList[index]); 
    printSongList();
  }
}

int volumeLevel(int val) { 
  val = map(val, 0, 1023, 0, 7); // map la valeur du potentiomètre entre 0 et 7
  return val;
}

void printSongList()  // Affiche la liste des chansons avec la chanson en cours de lecture
{
  for(int songList = 1; songList <= maxSongs; songList++)  // Boucle pour afficher la liste des chansons
  {
    Serial.print(trackList[songList]);
    if (index == songList)  // Si la chanson en cours de lecture est égale à la chanson dans la boucle, on affiche "Playing"
    {
      if (audio.isPlaying()) {
        Serial.print("     /Playing/     ");
        printTrackNames();
      } else {
        Serial.print("     /Pause/     ");  // Sinon, on affiche "Pause"
        printTrackNames();
      }
    }
    Serial.println(""); 
  }
}

void printTrackNames(){ // Affiche le nom de la chanson en cours de lecture dependant de l'index

  switch(index){
    case 1:
      Serial.print("Lean Beef Patty - JPEGMAFIA x Danny Brown");
    break;
    case 2: 
      Serial.print("Steppa Pig - JPEGMAFIA x Danny Brown");
    break;
    case 3:
      Serial.print("SCARING THE HOES - JPEGMAFIA x Danny Brown");
    break;
    case 4:
      Serial.print("Garbage Pale Kids - JPEGMAFIA x Danny Brown");
    break;
    case 5: 
      Serial.print("Fentanyl Tester - JPEGMAFIA x Danny Brown");
    break;
    case 6:
      Serial.print("Burfict! - JPEGMAFIA x Danny Brown");
    break;
    case 7:
      Serial.print("Shut Yo Bitch Ass Up / Muddy Waters - JPEGMAFIA x Danny Brown");
    break;
    case 8: 
      Serial.print("Orange Juice Jones - JPEGMAFIA x Danny Brown");
    break;
    case 9:
      Serial.print("Kingdom Hearts Key - JPEGMAFIA x Danny Brown (ft.redveil)");
    break;
    case 10:
      Serial.print("God Loves You  - JPEGMAFIA x Danny Brown");
    break;
  }
}
