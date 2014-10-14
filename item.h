#ifndef ITEM_H
#define ITEM_H

#include <iostream>

using namespace std;

class Item
{
private:
    int v_no;
    string v_id;
    string v_title;
    string v_url;

public:
    Item(int no, string id, string title, string url);
    int getNo();
    string getId();
    string getTitle();
    string getUrl();
};

#endif // ITEM_H
