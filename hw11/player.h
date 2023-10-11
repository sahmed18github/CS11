#ifndef _PLAYER_H
#define _PLAYER_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
#include "card.h"
#include "vector.h"
using namespace std;

class Player{

public:
    Player();
    int totalPrestige();
    int getDiscount(int index);
    int getGemCount(int index);
    int getPrestige();
    Card *getReserve(int index);
    void setGemCountP2(int input_Gindex);
    void setGemCountP3(int input_Gindex);
    void setReservedcards(Card *card);
    void takefromReserve(int index);
    void setDisocunt(int index);
    void payGems(int index, int cost);
    void setPrestige(int card_prestige);
    int getotalGems();
    int getPurchased();
    void setPurchased();
   
private:
    int prestige;
    int discount[5];
    int gemcount[6];
    Vector reserved_cards;
    int purchased_cards;

};


#endif