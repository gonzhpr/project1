#include <iostream>
#include "trade.h"
#include "commodity.h"

using namespace std;

void toBuy(int& ID, int& count) {
    cout << "请输入购买商品的编号:" << endl;
    cin >> ID;
    getchar();
    cout << "请输入购买商品的数量:" << endl;
    cin >> count;
    getchar();
}

void toSell(int& ID, int& count) {
    cout << "请输入卖出商品的编号:" << endl;
    cin >> ID;
    getchar();
    cout << "请输入卖出商品的数量:" << endl;
    cin >> count;
    getchar();
}

void operate() {
    printf("按任意键继续");
    getchar();
    system("cls");
}

void drawIndex() {
    system("cls");
    printf("\t--------------------------------------------------------------\n");
    printf("\t                        ****商品目录****                      \n");
    printf("\t--------------------------------------------------------------\n");
}

void drawLine() {
    printf("\t--------------------------------------------------------------\n");
}

void drawMainMenu() {
    printf("\t--------------------------------------------------------------\n");
    printf("\t                       欢迎使用销售系统                       \n");
    printf("\t--------------------------------------------------------------\n");
    printf("\t                       1-    购进商品                         \n");
    printf("\t                       2-    卖出商品                         \n");
    printf("\t                       3-    添加商品                         \n");
    printf("\t                       4-    查看商品信息                     \n");
    printf("\t                       5-    查看采购记录                     \n");
    printf("\t                       6-    查看销售记录                     \n");
    printf("\t                       7-    退出                             \n");
    printf("\t--------------------------------------------------------------\n");
}

int main()
{
    trade myTrade;
    if (!myTrade.init()) {
        myTrade = trade();
    }
    bool quitFlag = false;
    while (!quitFlag) {
        drawMainMenu();
        int selection;
        cin >> selection;
        getchar();
        int ID;
        int count;
        switch (selection) {
        case 1:
            drawIndex();
            myTrade.getIndex();
            drawLine();
            toBuy(ID, count);
            if (myTrade.buy(ID, count)) {
                system("cls");
                printf("操作成功,");
            }
            else {
                system("cls");
                printf("操作失败,");
            }
            operate();
            break;
        case 2:
            drawIndex();
            myTrade.getIndex();
            drawLine();
            toSell(ID, count);
            if (myTrade.sell(ID, count)) {
                system("cls");
                printf("操作成功,");
            }
            else {
                system("cls");
                printf("操作失败,");
            }
            operate();
            break;
        case 3:
            char name[30];
            float value;
            float cost;
            system("cls");
            cout << "请输入新品的名字" << endl;
            cin >> name;
            getchar();
            cout << "请输入购入价格" << endl;
            cin >> cost;
            getchar();
            cout << "请输入出售价格" << endl;
            cin >> value;
            getchar();
            myTrade.addNew(name, cost, value);
            system("cls");
            printf("操作成功");
            operate();
            break;
        case 4:
            drawIndex();
            myTrade.getIndex();
            drawLine();
            cout << "请输入商品编号" << endl;
            int index;
            cin >> index;
            getchar();
            system("cls");
            if (!myTrade.getInformation(index)) {
                cout << "无效商品编号" << endl;
            }
            else {
                cout << "商品存在" << endl;
            }
            operate();
            break;
        case 5:
            drawIndex();
            myTrade.getIndex();
            drawLine();
            system("cls");
            myTrade.getBuyRecord();
            operate();
            break;
        case 6:
            drawIndex();
            myTrade.getIndex();
            drawLine();
            system("cls");
            myTrade.getSellRecord();
            operate();
            break;
        case 7:
            quitFlag = true;
            break;
        }
    }
    myTrade.save();
    return 0;
}


