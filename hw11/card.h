#ifndef _CARD_H
#define _CARD_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
using namespace std;

class Card
{
public:
    //constructor 
    Card();

    //getters
    int getPrestige();
    string getGemColor();
    int getPrice(int index);

    //setters
    void setPrestige(int input_prestige);
    void setGemColor(string input_discount);
    void setPrice(int input_price[5]);
    

private:
   int prestige;
   int price[5];
   string discount; 
 
};

#endif