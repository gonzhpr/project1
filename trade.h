#pragma once
#include <list>
#include "commodity.h"

using std::list;

class trade {
	struct record {
		char name[30];
		int count;
		char sTime[70];
		record(char* name, int count, char* time) {
			strcpy_s(this->name, name);
			this->count = count;
			strcpy_s(sTime, time);
		}
	};

private:
	list<commodity> dataList;
	list<record> sellRecordList;
	list<record> buyRecordList;

public:
	trade() {};
	~trade() {};
	bool getInformation(int index);
	void getIndex();
	bool init();
	void save();
	bool buy(int ID, int count);
	bool sell(int ID, int count);
	void addNew(char name[], float buyValue, float sellValue);
	void getSellRecord();
	void getBuyRecord();
};