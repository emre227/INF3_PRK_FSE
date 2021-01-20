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
	myTCPserver srv(2021,25);

	srv.run();
}




string myTCPserver::myResponse(string input){

	string response("unknown Command");

	bool success = false;
	int a,b;

	if(input.compare(0,7,"NEWBOX[")== 0){


		sscanf(input.c_str(),"NEWBOX[%d,%d]", &a, &b);

		Safe_ = new BlackBoxSafe(a,b);


		response = string("password set");
		//response = Safe_->readPwd();			//psw ausgabe

	}else if(input.compare(0,4,"PSW[") == 0){
		char pwd[32];
		sscanf(input.c_str(), "PSW[%s",pwd);


		response = Safe_->input(pwd);



	}else{

		response = string(" UNKNOWN COMMAND");
	}


	return response;
}










/*

//  hat schon mal funktioniert

string myTCPserver::myResponse(string input){
	string response("UNKNOWN Command");
	if(input.compare(0,3,"ABC") ==0 ){
			response = string ("..Die Katze lief im schnee.");

	};

	return response;

}


/*  Versuch Nummer zwei aus Praktikum 2



   string myTCPserver::myResponse(string input){


	string response("UNKNOWN Command");
	bool success = false;
	int a,b;


	if(input.compare(0,4,"PSW[") == 0 ){
		// password received

		char pwd[32];

		sscanf(input.c_str(), "PSW[%s]",pwd);

		pwd[input.size() - 5]= '\0';

		cout << "pwd receided :" << pwd << "'" << endl;

		success = rand()%2;


		if(success){
			response = string ("SUCCESS");

		}else{
			response = string("FAILED");

		}
	}else if(input.compare(0,7,"NEWBOX[")== 0){

		sscanf(input.c_str(),"NEWBOX[%d,%d]", &a, &b);

		response = string("OKAY");


	}else{
		response = string(" UNKNOWN COMMAND");

	}

	return response;

}


*/




