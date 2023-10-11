
/* 
 * Author: Shahd Ahmed | sahmed18
 * Date: 4/21/2023 
 */
#include <iostream>
#include <fstream>
#include <string>
#include "player.h"
using namespace std;

    Player::Player()
    {
        //initializing discounts and gems in player's hand
        for (int i= 0; i < 5; i++) { 
            discount[i] = 0;
            gemcount[i] = 0;
        }

        gemcount[5] = 0;
        prestige = 0;
        //initialize reserved_Cards
        for (int i = 0; i < 3; i++) {
            reserved_cards.push_back(nullptr);
        }
    }


    int Player::totalPrestige()
    {
        return prestige;
    }


    int Player::getDiscount(int index)
    {
        return discount[index];
    }


    //return number of gems at a given index
    int Player::getGemCount(int index)
    {
        return gemcount[index];
    }


    //return the reserved card at the given index
    Card* Player::getReserve(int index)
    {
        if (reserved_cards.at(index) != nullptr) {
            Card *newcard =  reserved_cards.at(index);
            return newcard;
        }
        return nullptr;
    }


    int Player::getPrestige()
    {
        return prestige;
    }


    //increment gem count by 1
    void Player::setGemCountP3(int index_Gindex)
    {
        gemcount[index_Gindex] = gemcount[index_Gindex] + 1;
    }


    //increment gem count by 2
    void Player::setGemCountP2(int index_Gindex)
    {
        gemcount[index_Gindex] = gemcount[index_Gindex] + 2;
    }


    //add a card to reserve 
    void Player::setReservedcards(Card *card)
    {
        if (reserved_cards.at(0) == nullptr) {
            reserved_cards.insert(0 , card);
            reserved_cards.erase(1);
        }
        else if (reserved_cards.at(1) == nullptr) {
            reserved_cards.insert(1 , card);
            reserved_cards.erase(2);
        }
        else if (reserved_cards.at(2) == nullptr) {
            reserved_cards.insert(2 , card);
            reserved_cards.erase(3);
        }
    }


    //increment number of cards purchased
    void Player::setPurchased()
    {
        purchased_cards++;
    }


    void Player::takefromReserve(int index)
    {
        if (reserved_cards.at(index) != nullptr) {
            reserved_cards.erase(index);
            reserved_cards.push_back(nullptr);
        }
    }


    void Player::setDisocunt(int index)
    {
        discount[index]++;
    }


    //use from player's gems to pay for cards
    void Player::payGems(int index, int cost)
    {
        gemcount[index] = gemcount[index] - cost;
    }


    //increment the prestige when purchasing a card
    void Player::setPrestige (int card_prestige)
    {
        prestige = prestige + card_prestige;
    }


    //return the total number of gems
    int Player::getotalGems()
    {
        int count = gemcount[0]+gemcount[1]+gemcount[2]+gemcount[3]+gemcount[4]+gemcount[5];
        return count;
    }


    //return the number of purchased cards
    int Player::getPurchased()
    {
        return purchased_cards;
    }
