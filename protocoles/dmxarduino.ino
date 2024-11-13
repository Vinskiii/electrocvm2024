#include <lib_dmx.h>




#define DMX512 (0)

const int ADRESSE_DEPART = 50;  // Pour canal DMX 10
const int NB_CANAUX = 512;
const int POT = A0;

const int RED = 50;
const int GRN = 51;
const int BLU = 52;
const int STR = 54;
const int FAN = 55;



void setup() {

  ArduinoDmx0.set_tx_address(ADRESSE_DEPART);
  ArduinoDmx0.set_tx_channels(NB_CANAUX);    
  ArduinoDmx0.init_tx(DMX512);               
}

void loop() {

  //ArduinoDmx0.TxBuffer[STR] = scale(analogRead(A0));

  ArduinoDmx0.TxBuffer[2] = 255;  // red
  ArduinoDmx0.TxBuffer[4] = 125;  // strobe
  
  //ArduinoDmx0.TxBuffer[GRN] = 0;  //GRN
  //ArduinoDmx0.TxBuffer[BLU] = 0;  //BLU
  //ArduinoDmx0.TxBuffer[STR] = 50;  //STROBE
  //ArduinoDmx0.TxBuffer[FAN] = 0;  //fan


}



int scale(int value) {
  value = map(value, 0, 1023, 0, 255);
  return value;
}
