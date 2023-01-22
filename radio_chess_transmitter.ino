#include "rfid.h"

bool pieceState = false;

struct rfidStatus  // to keep the details of each card in
{
  unsigned long ID = 0;
  int state = 0;
};

rfidStatus readers[NR_OF_READERS]; //create an array of currentRFID objects

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  init_rfid();
}

void loop() {
  bool checkState = false;

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++)
  {
    int rfid_removed[NR_OF_READERS];    //create an array to store values in

    rfid_removed[reader] = checkRFIDremoved(reader); // call the check RFID function and store returned value in the array

    if (rfid_removed[reader] != -1)   // if the above function doesn't have a card removed then it will return -1 and we won't do the rest
      {
        readerState[reader]= false;
        readers[reader].state = 0;
      }

    int rfid_added[NR_OF_READERS];  //create an array to store values in

    rfid_added[reader] = checkRFIDadded(reader); // call the check RFID function and store returned value in the array

    if (rfid_added[reader] != -1) // if the above function doesn't have a card added then it will return -1 and we won't do the rest
      {
        readerState[reader] = true;
        readers[reader].state = 1;
        readers[reader].ID = rfid_added[reader];
      }

    if (readerState[reader] != storedState[reader]){
      if (readerState[reader] == 1) {
        storedState[reader] = readerState[reader];
      } else {
        storedState[reader] = readerState[reader];
      }
    }

    if (storedState[reader] == true) {
      checkState = storedState[reader];
    }
  }

  if (checkState != pieceState){
    pieceState = checkState;
    Serial.println(pieceState);
  }

}
