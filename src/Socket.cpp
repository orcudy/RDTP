//
//  Socket.cpp
//  rdt
//
//  Created by Chris Orcutt on 11/12/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Error.hpp"
#include "Socket.hpp"
#include <iostream>
#include <netdb.h>
#include <string.h>

using std::string;
using std::cout;
using std::endl;

Socket::Socket(string ip, int port, TransportLayer type){
  this->ip = ip;
  this->port = port;
  this->type = type;
}

void Socket::getAddressInfo(){
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  (this->type == UDP) ? (hints.ai_socktype = SOCK_DGRAM) : (hints.ai_socktype = SOCK_STREAM);
  hints.ai_flags = AI_PASSIVE;

  // empty string does not convert to NULL on call to string::c_str()
  char * ip;
  (this->ip.empty()) ? (ip = NULL) : (ip = (char *)this->ip.c_str());

  int retval = getaddrinfo(ip, std::to_string(this->port).c_str(), &hints, &res);
  if (retval) {
    cout << "Error setting up port: " << gai_strerror(retval) << endl;
    Error::exit(1);
  }

  this->destinationAddress = *(*res).ai_addr;
  this->destinationAddressLength = (*res).ai_addrlen;
}

void Socket::getDescriptor(){
  this->descriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (this->descriptor == -1) {
    cout << "Error setting up socket: " << strerror(errno) << endl;
    Error::exit(2);
  }
  freeaddrinfo(res);
}

void Socket::bind(){
  this->sourceAddress = this->destinationAddress;
  this->sourceAddressLength = this->destinationAddressLength;
  int retval = ::bind(this->descriptor, &this->sourceAddress, this->sourceAddressLength);
  if (retval == -1) {
    cout << "Error binding to port " << std::to_string(this->port) << ": " <<  strerror(errno) << endl;
    Error::exit(3);
  }
}
