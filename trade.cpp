#include "trade.h"
#include "commodity.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include <iostream>

#define CAP 5
#define TLEN 10
#define ALEN 30

using namespace std;

bool trade::getInformation(int index) {
	for (auto iter = dataList.begin(); iter != dataList.end(); iter++) {
		if (iter->getID() == index) {
			printf("��Ʒ��ţ�%d\n��Ʒ���ƣ�%s\n����۸�%f\n���ۼ۸�%f\nʣ�ࣺ%d\n",index,iter->getName(),iter->getBuyValue(),iter->getSellValue(),iter->getStock());
			return true;
		}
	}
	return false;
}

void trade::getIndex() {
	for (auto iter = dataList.begin(); iter != dataList.end(); iter++) {
		printf("\t ��Ʒ��ţ�%i ��Ʒ���ƣ�%s\n",iter->getID(),iter->getName());
	}
}

bool trade::init() {
	ifstream file("stock.txt");
	if (!file.fail()) {
		char titles[CAP][TLEN] = { "ID:","NAME:","COST:","VALUE:","STOCK:" };
		char saves[CAP][TLEN] = {};
		int tindex = 0;
		char buf[128];
		for (int i = 0; i < 3; i++) {
			file.getline(buf, 128);
		}
		while (!file.eof()) {
			char temp[TLEN] = "";
			for (int i = 0; i < TLEN && !file.eof(); i++) {
				file.get(temp[i]);
				if (strcmp(temp, titles[tindex]) == 0) {
					for (int j = 0; j < ALEN && !file.eof(); j++) {
						char c;
						file.get(c);
						if (c != '\t' && c != '\n') {
							saves[tindex][j] = c;
						}
						else if (c != '\n') {
							if (tindex > 4) {
								return false;
							}
							tindex++;
							break;
						}
						else {
							dataList.emplace_back(commodity(atoi(saves[0]),saves[1],atof(saves[2]),atof(saves[3]),atoi(saves[4])));
							tindex = 0;
							break;
						}
						if (j == TLEN - 1) {
							return false;
						}
					}
					break;
				}
				if (i == TLEN - 1) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

void trade::save() {
	ofstream file;
	file.open("stock.txt");
	if (!file.fail()) {

		file << "----------------------------------------\n";
		file << "            ****��Ʒ��Ϣ****            \n";
		file << "----------------------------------------\n";
		for (auto iter = dataList.begin(); iter != dataList.end(); iter++) {
			file << "ID:" << iter->getID()
				<< "\tNAME:" << iter->getName()
				<< "\tCOST:" << iter->getBuyValue()
				<< "\tVALUE:" << iter->getSellValue()
				<< "\tSTOCK" << iter->getStock() << endl;
		}
	}
	else {
		printf("��¼�ļ�����ʧ��");
	}
	file.close();
	file.open("sellRecord.txt");
	if (!file.fail()) {
		file << "----------------------------------------\n";
		file << "            ****������Ϣ****            \n";
		file << "----------------------------------------\n";
		for (auto iter = sellRecordList.begin(); iter != sellRecordList.end(); iter++) {
			file << "NAME:" << iter->name << "\tTIME:" << iter->sTime << "\tCOUNT:" << iter->count << endl;
		}
	}
	else {
		cout << "���ۼ�¼�ļ�����ʧ��" << endl;
	}
	file.close();
	file.open("buyRecord.txt");
	if (!file.fail()) {
		file << "----------------------------------------\n";
		file << "            ****������Ϣ****            \n";
		file << "----------------------------------------\n";
		for (auto iter = buyRecordList.begin(); iter != buyRecordList.end(); iter++) {
			file << "NAME:" << iter->name << "\tTIME:" << iter->sTime << "\tCOUNT:" << iter->count << endl;
		}
	}
	else {
		cout << "�����¼�ļ�����ʧ��" << endl;
	}
}

bool trade::buy(int ID, int count) {
	for (auto iter = dataList.begin(); iter != dataList.end(); iter++) {
		if (iter->getID() == ID) {
			iter->UpdateStock(count);
			time_t t = time(0);
			struct tm timeStruct;
			localtime_s(&timeStruct, &t);
			char temp[50];
			strftime(temp,sizeof(temp),"%Y�� %m�� %d�� %X %A ", &timeStruct);
			buyRecordList.push_back(record(iter->getName(), count, temp));
			return true;
		}
	}
	return false;
}

bool trade::sell(int ID, int count) {
	for (auto iter = dataList.begin(); iter != dataList.end(); iter++) {
		if (iter->getID() == ID && !(iter->getStock() + count < 0)) {
			iter->UpdateStock(-count);
			time_t t = time(0);
			struct tm timeStruct;
			localtime_s(&timeStruct, &t);
			char temp[50];
			strftime(temp, sizeof(temp), "%Y�� %m�� %d�� %X %A", &timeStruct);
			sellRecordList.push_back(record(iter->getName(), count, temp));
			return true;
		}
	}
	return false;
}

void trade::addNew(char name[], float buyValue, float sellValue) {
	trade::dataList.emplace_back(commodity(name,buyValue,sellValue));
}

void trade::getSellRecord() {
	for (auto iter = sellRecordList.begin(); iter != sellRecordList.end(); iter++) {
		printf("\t��Ʒ���ƣ�%s\n", iter->name);
		printf("\t�������ڣ�%s\n", iter->sTime);
		printf("\t����������%d\n", iter->count);
		printf("\t----------------------------------\n");
	}
}

void trade::getBuyRecord() {
	for (auto iter = buyRecordList.begin(); iter != buyRecordList.end(); iter++) {
		printf("\t��Ʒ���ƣ�%s\n", iter->name);
		printf("\t�������ڣ�%s\n", iter->sTime);
		printf("\t����������%d\n", iter->count);
		printf("\t----------------------------------\n");
	}
}