/*
 * game.h
 * CS11 Splendor
 */

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "termfuncs.h"
#include "card.h"
#include "player.h"
#include "vector.h"

using namespace std;

class Game {
public:
    //constructor
    Game(string filename, string play_nobles);
    ~Game();
    void read_data(string filename);
    void Drawtop3();
    void initialize_Gbank();

    //main gameplay
    void playGame();

    //utility functions
    string indexToColor(int index);
    bool game_exit = false;

private:

    //drawing functions
    bool is_winner();
    void returnGem(Player *playernum);
    void Q_p2(Player *playernum, istream &input);
    bool check_p2(string color);
    void Q_p3(Player *playernum, istream &input);
    bool check_p3p1(string color);
    bool check_p3(string color1,string color2, string color3);
    void Q_r(Player *playernum, istream &input);
    bool check_r(Player *playernum, string card_type , int index);
    void Q_b(Player *playernum, istream &input);
    bool check_b(string card_type, int index);
    bool can_afford(Player *playernum, Card *current_card);
    void Q_br(Player *playernum, istream &input);
    bool check_br(int index, Player *playernum);
    bool Query_helper(Player *playernum);
    void drawBoard();
    void drawNoble(int vpos, int hpos, Card *c);
    void drawPlayer(int vpos, int hpos, Player *p);
    void drawDeck(int vpos, int hpos, string type);
    void drawCard(int vpos, int hpos, Card *c);
    void drawGem(int vpos, int hpos, string color);
    void clearBoard();

    static const int BOARD_HEIGHT = 41;
    static const int BOARD_WIDTH = 120;
    static const int CARD_WIDTH = 13;
    static const int CARD_HEIGHT = 8;
    static const int CARD_ROWS = 3;
    static const int CARD_COLS = 4;
    static const int NUM_NOBLES = 3;
    static const int GEMS = 6;

    //nobles activated true/false
    bool play_nobles;

    //cards in play
    Card *grid[CARD_ROWS][CARD_COLS];
    Vector vendors;
    Vector transport;
    Vector mines;
    Player player_1;
    Player player_2;
    Vector nobles;
    int gem_bank[6];
    //display
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    string board_color[BOARD_HEIGHT][BOARD_WIDTH];

    //Gem colors in the game
    string colors[GEMS];
};

#endif
