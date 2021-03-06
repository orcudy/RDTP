//
//  header.cpp
//  reliable-data-protocol
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Header.hpp"
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

Header::Header(){
  syn = false;
  synack = false;
  fin = false;
  ackNum = -1;
  seqNum = -1;
  dataSize = -1;
  totalPackets = -1;
  memset(this->data, '\0', this->chunkSize);
  memset(this->filename, '\0', maxFilenameSize);

}

Header::Header(char * data){
  memcpy(this, data, sizeof(char) * sizeof(Header));
}

void Header::setData(char * adata) {
  memset(this->data, 0, 1000);
  memcpy(this->data, adata, strlen(adata));
}

char * Header::generateMessage(){
  char * msg = (char*)malloc(sizeof(char) * sizeof(Header));
  memcpy(msg, this, sizeof(char) * sizeof(Header));
  return msg;
}

void Header::description(){
  cout << "syn: " << syn << endl;
  cout << "synack: " << synack << endl;
  cout << "fin: " << fin << endl;
  cout << "ackNum: " << ackNum << endl;
  cout << "seqNum: " << seqNum << endl;
  cout << "dataSize: " << dataSize << endl;
  cout << "chunkSize: " << chunkSize << endl;
  printf("filename: %s\n", filename);
  cout << "totalPackets: " << totalPackets << endl;
  printf("data: %s\n", data);
}

