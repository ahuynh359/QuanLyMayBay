#pragma once;

#include"DataConst.h"


#include<iostream>
using namespace std;

struct Plane {
	char idPlane[MAX_ID];
	char type[MAX_TYPE];
	int seats; //So cho >= 20

};


struct PlaneList {
	int size = 0;
	Plane* data[MAX_PLANE];

};

//Ham tim may bay 
Plane* findPlane(PlaneList& list, char idPlane[MAX_ID]) {
	for (int i = 0; i < list.size; i++) {
		if (strcmp(list.data[i]->idPlane, idPlane) == 0)
			return list.data[i];
	}
	return NULL;
}

//Tra ve vi tri may bay
int getIndexPlane(PlaneList& list, char idPlane[MAX_ID]) {
	for (int i = 0; i < list.size; i++) {
		if (strcmp(list.data[i]->idPlane, idPlane) == 0) {
			return i;
		}
	}
	return -1;
}

//Remove may bay
int removePlane(PlaneList& list, int index) {
	if (index < 0 || index > list.size - 1)
		return 0;
	for (int i = index; i < list.size - 1; i++) {
		list.data[i] = list.data[i + 1];
	}
	list.size--;
	return 1;

}


void add(PlaneList& list) {
	Plane* plane = new Plane();
	cout << "Nhap so hieu MB:";
	cin >> plane->idPlane;
	cout << "Nhap loai may bay:";
	cin >> plane->type;
	while (plane->seats < 20) {
		cout << "Nhap so cho:";
		cin >> plane->seats;
	}
	list.data[(++list.size)] = plane;
}


