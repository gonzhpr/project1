#pragma once
class commodity {
private:
	int static kinds;
	int ID;
	int stock;
	float buyValue;
	float sellValue;
	char name[30];
public:
	commodity();
	commodity(char name[], float buyValue, float sellValue);
	commodity(int ID, char name[], float cost, float value, int stock);
	~commodity();
	int getID();
	int getStock();
	float getBuyValue();
	float getSellValue();
	char* getName();
	void UpdateStock(int n);
	static void setKinds(int k);
};