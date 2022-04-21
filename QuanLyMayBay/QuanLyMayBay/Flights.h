#pragma once

#include"DataConst.h"
#include<fstream>
#include"Day.h"
#include"Planes.h"


struct Flight {
	char idFlight[MAX_ID_FLIGHT+1];
	Date departure;
	char arrive[MAX_ARRIVE+1];
	char idPlane[MAX_ID_PLANE+1];
	/*
	* 0 huy chuyen
	* 1 con ve
	* 2 het ve
	* 3 hoan tat 
	*/
	int status; 

	//-----CHI SO PHU
	char** ticketList;
	int totalTicket;
	

};

struct FlightNode
{
	Flight info;
	FlightNode* next;
};
typedef FlightNode* PTR;


void initializeList(PTR& first)
{
	first = NULL;
}



PTR newNode(Flight& flight)
{
	PTR p = new FlightNode;
	p->info = flight;
	p->next = NULL;
	return p;
}

bool isEmpty(PTR& first)
{
	return(first == NULL ? true : false);
}

void insertAfter(PTR& first, Flight &flight)
{
	PTR temp = newNode(flight);
	if (first == NULL) {
		first = temp;
		first->next = NULL;
	}
	else
	{
		PTR p = first;
		while (p->next != NULL)
			p = p->next;
		p->next = temp;

	}
}

int size(PTR& first) {
	int cnt = 0;
	for (PTR k = first; k != NULL; k = k->next) {
		cnt++;
	}
	return cnt;
}



bool checkDupIDFlight(PTR& first, char id[MAX_ID_FLIGHT+1]) {
	for (PTR p = first; p != NULL; p = p->next) {
		if (strcmp(p->info.idFlight, id) == 0) {
			return true;
		}
	}
	return false;
}

PTR searchByIDFlight(PTR &first, char  id[MAX_ID_FLIGHT + 1])
{
	for (PTR p = first; p != NULL; p = p->next)
		if (strcmp(p->info.idFlight, id) == 0)
			return p;
	return NULL;
}

bool searchByIDPlane(PTR& first, char id[MAX_ID_PLANE + 1]) {
	for (PTR k = first; k != NULL; k = k->next) {
		if (strcmp(k->info.idPlane, id) == 0)
			return true;
	}
	return false;
}

int checkCancleFlight(PTR& first) {
	if (first->info.status == HAVE_TICKET || first->info.status == OUT_OF_TICKET) {
		first->info.status = CANCEL_TICKET;
		return 1;
	}
	return 0;
}


//-------------TICKET
void initTicketList(PlaneList& planeList, Flight& flight) {
	flight.status = HAVE_TICKET;
	flight.totalTicket = planeList.data[findPlane(planeList, flight.idPlane)]->seats;
	flight.ticketList = new char* [flight.totalTicket + 1];
	for (int i = 0; i < flight.totalTicket; i++) {
		flight.ticketList[i] = new char[MAX_ID_PASS];
		strcpy_s(flight.ticketList[i], 2, "0");
	}

}


void writeFileFlight(PTR& first) {
	ofstream out("FlightData.txt", ios::trunc,ios::binary);

	if (out.fail()) {
		cout << "Khong mo duoc file DSCB\n";
		return;
	}

	for (PTR k = first; k != NULL; k = k->next) {
		out.write(reinterpret_cast<char*>(&k->info), sizeof(Flight));
		for (int i = 0; i < k->info.totalTicket; i++) {
			out.write(reinterpret_cast<char*>(&k->info.ticketList[i]), sizeof(char[MAX_ID_FLIGHT + 1]));
		}
	}

	
	out.close();
}

void readFileFlight(PTR& first) {
	ifstream inp("FlightData.txt",ios::binary);
	
	if (inp.fail()) {
		cout << "Khong mo duoc file DSCB\n";
		return;
	}
	Flight flight;

	while(inp.read(reinterpret_cast<char*>(&flight), sizeof(flight))){
		flight.ticketList = new char* [flight.totalTicket + 1];
		for (int i = 0; i < flight.totalTicket; i++) {
			flight.ticketList[i] = new char[MAX_ID_FLIGHT + 1];
			inp.read(reinterpret_cast<char*>(&flight.ticketList[i]), sizeof(char[MAX_ID_FLIGHT + 1]));
		}
		
		insertAfter(first, flight);
	}
	inp.close();

}

void deleteList(PTR& first)
{
	PTR temp = first;
	while (temp != NULL) {
		PTR t = temp;
		temp = temp->next;
		delete t;
	}
}

