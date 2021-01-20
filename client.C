/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <sstream> //für stringstream

#include "SIMPLESOCKET.H"

using namespace std;

string askNewbox(TCPclient *c, int pl, int al);
int guessPsw(TCPclient *c, int pl, int al);

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2021);

	int pl = 5;
	int al = 5;
	string res("");
	cout << "asking server to create a password" << endl;
	res =askNewbox(&c,pl,al);

	if(res.compare(0,11,"password set")){		//client bekommt die antwort vom server das ein pw erfolgreich erstellt wurde

	int counter;
	counter = guessPsw(c,pl,al);

	cout << "guesed the password with" << counter << " tries" << endl;
	}



	else{ // für den fall das der client das password nicht erzeugt hat
		return 0;

	}



	}



//soll dann server dazu bringen ein pw zu erstellen
string askNewbox(TCPclient *c, int pl, int al){    // pl-> password länge al-> alphabet länge(also wie viele versch. zeichen)

	stringstream s;
	s << "NEWBOX[" << pl << "," << al << "]";
	string msg = s.str();
	string res("");
	c->sendData(msg);
	res = c->receive(32);

	cout << res << endl;

	return res;

}



int guessPsw(TCPclient *c, int pl, int al){	//versucht das password über bruteforce zu erraten

	const string SYMBOLS = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";
	int pwArray[pl];

	//hier ist noch viel zu machen :D
	while(){



	}





}



}

