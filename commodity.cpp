#include "commodity.h"
#include <string.h>
int commodity::kinds = 0;

commodity::commodity() {
	kinds++;
}

commodity::commodity(char name[], float buyValue, float sellValue) {
	kinds++;
	ID = kinds;
	this->stock = 0;
	this->buyValue = buyValue;
	this->sellValue = sellValue;
	strcpy_s(this->name, name);
}

commodity::commodity(int id, char name[], float cost, float value, int stock) {
	//kinds++;
	this->ID = id;
	this->stock = stock;
	this->buyValue = cost;
	this->sellValue = value;
	strcpy_s(this->name, name);
}

commodity::~commodity() {
	//kinds--;
}

int commodity::getID() {
	return commodity::ID;
}

int commodity::getStock() {
	return commodity::stock;
}

float commodity::getBuyValue() {
	return commodity::buyValue;
}

float commodity::getSellValue() {
	return commodity::sellValue;
}

char* commodity::getName() {
	return commodity::name;
}

void commodity::UpdateStock(int n) {
	this->stock += n;
}

void commodity::setKinds(int k) {
	kinds = k;
}