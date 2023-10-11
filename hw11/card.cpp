/*
* Author: Shahd Ahmed | sahmed18
 * Date: 4/21/2023 
 */
#include "card.h"

Card::Card() 
{
    //initialize each variable in card class
    prestige = 0;
    for (int i = 0; i < 5; i++) {
        price[i] = i;
    }
    discount = ""; 
}



int Card::getPrestige() 
{
    return prestige;
}


string Card:: getGemColor() 
{
    return discount; 
}

//return the price at the color index
int Card::getPrice(int index) 
{   
    return price[index];
}

//set the prestige value
void Card::setPrestige(int input_prestige) 
{
    this->prestige = input_prestige;
}


void Card::setGemColor(string input_discount) 
{
    this->discount = input_discount;
}


//set the array price of the card to the input array values
void Card::setPrice(int input_price[5]) 
{
    for (int i = 0; i < 5; i++) {
        this->price[i] = input_price[i];
    }
   
}

