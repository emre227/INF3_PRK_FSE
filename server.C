/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include <iostream>

#include "SIMPLESOCKET.H"
#include "TASK1.H"

using namespace std;
using namespace TASK1;


class myTCPserver : public TCPserver{

public :
	myTCPserver(int port, int maxDataSize) : TCPserver(port, maxDataSize){;}



protected:
	string myResponse(string input);
	BlackBoxSafe *Safe_;
};

// 2022 =  port number
int main(){
	srand(time(nullptr));
	myTCPserver srv(20233,25);

	srv.run();
}




string myTCPserver::myResponse(string input){

	string response("unknown command");    					//falls eine unbekannt eingabe vom client kommt


	int pl,al;												// pl= passwordlänge und alphabetlänge => wird vom client gesendet

	if(input.compare(0,7,"NEWBOX[")== 0){					//überprüft ob der client einen password erstellen will
															//input.compare guckt ob die ersten 7 Zeilen übereinstimmen

		sscanf(input.c_str(),"NEWBOX[%d,%d]", &pl, &al);	//scanned string und speichert die vom client gesendeten variablen

		Safe_ = new BlackBoxSafe(pl,al);					//erstellt objekt safe auf der halde ->password wird so erstellt


		response = string("password set");					//gibt dem client zurück das ein password erstellt wurde


	}else if(input.compare(0,4,"PSW[") == 0){				//prüft ob der befehl zum passwordeinlesen gesendet wurde
		char pwd[32];										//erstellt ein char wo das vom client gesendete password gesenet wird
		sscanf(input.c_str(), "PSW[%s",pwd);


		response = Safe_->input(pwd);						//gibt das password in die methode von safe
															//input() vergleicht das gesendete pw von dem vom server
															//input() hat als rückgabe einen string
															//entweder "accepted" oder "denied"
	}

	return response;										//ausgabe der antwort des servers, abhängig vom client befehl
}



