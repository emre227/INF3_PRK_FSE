/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <sstream> 	//für stringstream
#include <math.h>
#include <fstream> 	// bibliothek um in dateien zu schreiben

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
	c.conn(host , 20233);

	int pl = 4;												//passwordlänge
	int al = 4;												//alphabetlänge
	string res("");											//string wo die antwort des server gespeichert wird
	cout << "asking server to create a password" << endl;
	res = askNewbox(&c,pl,al);								//ruft die funktion zum erstellen eines pws auf

	if(res.compare(0,11,"password set")){					//client bekommt die antwort vom server das ein pw erfolgreich erstellt wurde

	int counter;											//zählt die versuche das pw zu raten
	counter = guessPsw(&c,pl,al);

	cout << "guesed the password with " << counter << " tries" << endl;

	ofstream file("statistik.csv",ofstream::app);			//erzeugt die datei "statistik"


	//file << "Passwortlänge	Alphabetlänge	Versuche" << endl;   //erstmal auskommentiert, braucht man nur bei erstmaliger dateierzeugung
	file << pl << "	" << al << "	" << counter << "	" <<endl;



	file.close();											//schließt die datei

	}



	else{ // für den fall das der client das password nicht erzeugt hat
		
		cout << "fehler"<< endl;
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



int guessPsw(TCPclient *c, int pl, int al){						//int als rückgabe, wei die anzahl der versuche zurück gegeben werden
																//versucht das password über bruteforce zu erraten
	const string SYMBOLS = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";	//mögliches alphabet
	char symbArray[al];
	string pwdIdee,response;
	int m=0;
	int index;
	pwdIdee =string("");


	
	
	for(int i=0;i<al;i++){
		symbArray[i] = SYMBOLS.at(i);
	}
	
	//hier ist noch viel zu machen :D

	if(pl > 0){
		for(int i=0;i < pl;i++){
			pwdIdee += symbArray[0];
		}

		do{
			for(int i=0;i<pl;i++){
				if(i==0){
					pwdIdee.replace(i,1,1,symbArray[int(m % al)]);
				}else{
					index = (m / int(pow(float(al),float(i)))) % al;

					pwdIdee.replace(i,1,1,symbArray[index]);
				}
			}
			response = string();
			response = "PSW[";
			response += pwdIdee;
	
			cout << response << endl;
					
			c->sendData(response);
	
			response = c->receive(32);
			cout << response << endl;
			m++;

		}while(response.compare("ACCEPTED") != 0);


	return int(m + 1);





}

return -1;


}

