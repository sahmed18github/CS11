/*
 * game.cpp
 * CS11 Splendor
 * Author: Shahd Ahmed | sahmed18
 * Date: 4/21/2023 
 */

#include "game.h"

//constructor
Game::Game(string filename, string play_nobles)
{
    //store gem colors for easy reference in drawing functions
    colors[0] = "white";
    colors[1] = "red";
    colors[2] = "pink";
    colors[3] = "blue";
    colors[4] = "green";
    colors[5] = "gold";

    //include nobles or not
    if (play_nobles == "true") {
        this->play_nobles = true;
    } else {
        this->play_nobles = false;
    }

    //initialize the board
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
    }
    read_data(filename);
    Drawtop3();
    initialize_Gbank();
}

 //draw top3 cards
void Game::Drawtop3() {
    //fill vendors
    for(int j = 0; j < CARD_COLS; j++ ){
        grid[0][j] = vendors.back();
        vendors.pop_back();
     
    }
    //fill trans
    for(int j = 0; j < CARD_COLS; j++ ){
        grid[1][j] = transport.back();
        transport.pop_back();
    }
    //fill mines
    for(int j = 0; j < CARD_COLS; j++ ){
        grid[2][j] = mines.back();
        mines.pop_back();
    }
}
//destructor
Game:: ~Game()
{
    if (!vendors.empty()) {
        for (int i=0; i < vendors.size(); i++) {
            delete vendors.at(i);
        }
    }
    if (!transport.empty()) {
        for(int i = 0; i < transport.size(); i++) {
            delete transport.at(i);
        }
    }
    if (!mines.empty()) {
        for (int i = 0; i < mines.size(); i++) {
            delete mines.at(i);
        }
    }
    for(int i = 0; i < CARD_ROWS; i++){
        for (int j = 0; j < CARD_COLS; j++) {
            delete grid[i][j];
        }
    }  
    for (int j = 0; j < 3; j++) {
        if (player_1.getReserve(j) != nullptr) {
            delete player_1.getReserve(j);
        }
        if (player_2.getReserve(j) != nullptr) {
            delete player_2.getReserve(j);
        }
    } 
}

void Game::read_data(string filename)
{
    char row;
    int prestige, white, red, pink, blue, green; 
    string discount;
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << "Failed to open deck file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string str;
    getline(infile, str);
    while(!infile.eof()){
        infile >> row >> prestige >> discount >> white >> red >> pink >> blue >> green; 
        //fill mines
        if (row == 'm') {
            Card *cmines = new Card; 
            cmines->setPrestige(prestige);
            cmines->setGemColor(discount);
            int temp_array[5];
            temp_array[0]=white;
            temp_array[1]=red;
            temp_array[2]=pink;
            temp_array[3]=blue;
            temp_array[4]=green;
            cmines->setPrice(temp_array);
            mines.push_back(cmines); 
        }
        //fill transports
        else if (row == 't') {
            Card *ctrans = new Card; 
            ctrans->setPrestige(prestige);
            ctrans->setGemColor(discount);
            int temp_array[5];
            temp_array[0]=white;
            temp_array[1]=red;
            temp_array[2]=pink;
            temp_array[3]=blue;
            temp_array[4]=green;
            ctrans->setPrice(temp_array);
            transport.push_back(ctrans); 
        }
        //fill vendors
        else if (row == 'v') {
            Card *cvendors = new Card; 
            cvendors->setPrestige(prestige);
            cvendors->setGemColor(discount);
            int temp_array[5];
            temp_array[0]=white;
            temp_array[1]=red;
            temp_array[2]=pink;
            temp_array[3]=blue;
            temp_array[4]=green;
            cvendors->setPrice(temp_array);
            vendors.push_back(cvendors); 
        }
    }
}

//return a filled gem bank
void Game::initialize_Gbank() 
{
    //set normal gems
    for (int i = 0; i < GEMS-1; i++) {
        gem_bank[i] = 4;
    }
    //set gold gems
    gem_bank[5] = 5;
}

//main game loop
void Game::playGame()
{
    bool game_over = false;
    bool player1_turn = true;

    while (!game_over) {
        //reset the screen
        clearBoard();
        screen_clear();
        screen_home();
        //draw the board
        drawBoard();
        
        
        while (player1_turn == true) {
           
            
            cout << "PLAYER 1, enter your next move: ";
            //prompt user for queries
            Query_helper(&player_1);
            if (game_exit) {
                return;
            }
             //check if a player has extra gems
            while (player_1.getotalGems() > 10) {
                clearBoard();
                screen_clear();
                screen_home();
                drawBoard();
                cout << "PLAYER 1, you have more than 10 gems! Name one gem you would like to return: ";
                returnGem(&player_1);
                
            }
          
            player1_turn = false;
        } 

        //change turns
        while (!player1_turn) {
            clearBoard();
            screen_clear();
            screen_home();
            drawBoard();
            cout << "PLAYER 2, enter your next move: ";
            Query_helper(&player_2);
            if (game_exit) {
                return;
            }
            //check if extra gems
            while (player_2.getotalGems() > 10) {
                clearBoard();
                screen_clear();
                screen_home();
                //draw the board
                drawBoard();
                cout << "PLAYER 2, you have more than 10 gems! Name one gem you would like to return: ";
                returnGem(&player_2);
            }
            //check if player is a winner
            if (is_winner()) {
                game_exit = true;
                return;
            }
            player1_turn = true;
            
        }       
    }
}

//return true if there is a winner or tie
bool Game::is_winner() {
    if (player_1.getPrestige() >= 15) {
       
            clearBoard();
            screen_clear();
            screen_home();
            drawBoard();   

        if (player_1.getPrestige() > player_2.getPrestige()) {
            cout << "Congratulations Player 1: YOU WIN!!!!" << endl;
            return true;
        }
        else if (player_1.getPrestige() < player_2.getPrestige()) {
            cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
            return true;
            
        }
        //if tie
        else if (player_1.getPrestige() == player_2.getPrestige()) {
            if (player_1.getPurchased() < player_2.getPurchased()) {
                cout << "Congratulations Player 1: YOU WIN!!!!" << endl;
                return true;
            }
            //check for number of purchased cards
            else if (player_1.getPurchased() > player_2.getPurchased()) {
                cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
                return true;
            }
            else {
                cout << "You losers tied - BORING!!!!" << endl;
                return true;
            }
        }
    }
    else if (player_2.getPrestige() >= 15) {
        clearBoard();
        screen_clear();
        screen_home();
        drawBoard();
        
        if (player_1.getPrestige() > player_2.getPrestige()) {
            cout << "Congratulations Player 1: YOU WIN!!!!" << endl;
            return true;
        }
        else if (player_1.getPrestige() < player_2.getPrestige()) {
            cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
            return true;
        }

        //if tie
        else if (player_1.getPrestige() == player_2.getPrestige()) {
            if (player_1.getPurchased() < player_2.getPurchased()) {
                cout << "Congratulations Player 1: YOU WIN!!!!" << endl;
                return true;
            }
            //check for number of purchased cards
            else if (player_1.getPurchased() > player_2.getPurchased()) {
                cout << "Congratulations Player 2: YOU WIN!!!!" << endl;
                return true;
            }
            else {
                cout << "You losers tied - BORING!!!!" << endl;
                return true;
            } 
        }
    }
    return false;
}


//check for extra gems and prompt for return gems
//checks for valid input
void Game:: returnGem(Player *playernum) 
{
    string color;
    string str;
    getline(cin, str);
    stringstream get_color(str);
    get_color >> color;
    for (int i = 0; i < 6; i++) {
        if (colors[i] == color) {
            if (playernum->getGemCount(i) != 0) 
            {
                //put them back in the bank
                gem_bank[i]++;
                //delete the gem from player's hand
                playernum->payGems(i, 1);
                return;
            }
        }
    }
    cout << "Invalid color. Name one gem you would like to return: ";
    returnGem(playernum);
}

//prompt user for valid queries and call the function
//associated with
bool Game::Query_helper(Player *playernum)
{
    string q;
    string str;
    getline(cin, str);
    stringstream input(str);
    input >> q;
    if (q == "p3") {
        Q_p3(playernum, input);
    }
    else if (q == "p2") {
        Q_p2(playernum, input);
    }
    else if (q == "r") {
        Q_r(playernum, input);
    }
    else if (q == "b") {
        Q_b(playernum, input);
    }
    else if (q == "br") {
        Q_br(playernum, input);
    }
    else if (q == "q") {
        game_exit = true;
        return true;
    }
    else {
        cout << "Invalid move - enter a valid move: ";
        return Query_helper(playernum);
    }
    return false;
}

//pick two
void Game::Q_p2(Player *playernum, istream &input) 
{

    string color;
    input >> color;

    if (!check_p2(color)) {
        Query_helper(playernum);
    }
    else {
        for (int i = 0; i < 5; i++) {  
            if (colors[i] == color) {
                gem_bank[i] =  gem_bank[i]-2;
                playernum->setGemCountP2(i);
                break;  
            }
        }
    }
}

//check for available gems and valid input color
bool Game::check_p2(string color) 
{
    for (int i = 0; i < 5; i++) {
        if (colors[i] == color) {
            if(gem_bank[i] == 4){
                return true;
            }
            else{
                cout << "Invalid move (unavailable gems) - enter a valid move: ";
                return false;
            }
        }
    } 
    cout << "Invalid move (invalid color) - enter a valid move: ";
    return false;    
}

//pick 3 colors
void Game::Q_p3(Player *playernum, istream &input) 
{
    string color1, color2, color3;
    input >> color1 >> color2 >> color3;
    //if not valid input, keep prompting for a query
    if (!check_p3(color1, color2, color3)) {
        Query_helper(playernum);
    }
    else {
        for (int i = 0; i < 5; i++) {
            if ((colors[i] == color1) || 
                (colors[i] == color2) || (colors[i] == color3)) {
                if (gem_bank[i] != 0) {
                    //take gems from gem_bank
                    gem_bank[i] =  gem_bank[i]-1;
                    //update player's gem
                    playernum->setGemCountP3(i);
                }
            }
        }
    }
}

//check valid inputs for pick 3 query
bool Game::check_p3(string color1,string color2, string color3)
{
    bool check1;
    bool check2;

    if ((check_p3p1(color1)) && (check_p3p1(color2)) && (check_p3p1(color3))) {
        check1 = true;
    }
    else {
        check1 = false;
    }
    //check for duplicate colors
    if ((color1 != color2) && (color1 != color2) 
        && (color2 != color3) && (color1 != color3)) {
        check2 = true;
    }
    else if(check1) {
        cout << "Invalid move (duplicate color) - enter a valid move: ";
        check2 = false;
    }
    if ((check1) && (check2)) {
        return true;
    }
    return false;
}

//check available gems and valid colors for p3 function
bool Game::check_p3p1(string color) 
{
  
    for (int i = 0; i < 5; i++) {
        if (colors[i] == color) {
            if (gem_bank[i] != 0) {
                return true;
            }
            else {
                cout << "Invalid move (unavailable gems) - enter a valid move: ";
                return false;
            }
        }      
    }
    cout << "Invalid move (invalid color) - enter a valid move: ";
    return false;
}


//reseve cards
void Game::Q_r(Player *playernum, istream &input)
{    
    string row;
    int index;
    input >> row >> index;
    if (!check_r(playernum, row,index)) {
        Query_helper(playernum);
    }
    else {
        //if the card type is mine
        if (row == "m") {
            //add it to player's reserve
            playernum->setReservedcards(grid[2][index-1]);
            //get rid of that card from the grid
            grid[2][index-1] = mines.back();
            mines.pop_back();
            //add gold gems to player's gems
            if (gem_bank[5] != 0) {
                gem_bank[5] =  gem_bank[5]-1;
                playernum->setGemCountP3(5);
            }
        }

        else if (row == "t") {
            playernum->setReservedcards(grid[1][index-1]);  
            grid[1][index-1] = transport.back();
          
            transport.pop_back();
            if (gem_bank[5] != 0) {
                gem_bank[5] =  gem_bank[5]-1;
                playernum->setGemCountP3(5);
            }
        }

        else if (row == "v") {
            playernum->setReservedcards(grid[0][index-1]);  
            grid[0][index-1] = vendors.back();
            vendors.pop_back();
            
            if (gem_bank[5] != 0) {
                gem_bank[5] =  gem_bank[5]-1;
                playernum->setGemCountP3(5);
            }
        }
    }
}


//check for valid move for reserve
bool Game::check_r(Player *playernum, string card_type ,int index)
{
    bool check1, check2, check3;
    //check card type
    if ((card_type != "m" )&& (card_type != "t" ) && (card_type != "v" )) {
        cout << "Invalid move (invalid card type) - enter a valid move: ";
        check1 = false;
    }
    else {
        check1 = true;
    }
    //check column number
    if ((check1) && ((index <= 0) || (index > 4))) {
        check2 = false;
        cout << "Invalid move (invalid card column) - enter a valid move: " ;
    }
    else{
        check2 = true;
    }
    //check if reserve is full
    if ((check2)&& ((playernum->getReserve(0) != nullptr) && 
        (playernum->getReserve(1) != nullptr) 
        && (playernum->getReserve(2) != nullptr))) {
        check3 = false;
        cout << "Invalid move (reserve is already full) - enter a valid move: " ;
    }
    else{
        check3 = true;
    }
    if (check1 && check2 && check3) {
        return true;
    }
    return false;
}


//buy cards
void Game::Q_b(Player *playernum, istream &input)
{
    string row;
    int index;
    input >> row >> index;
    if (!check_b(row, index)) {
        Query_helper(playernum);
    }

    if (row == "m")
    {
        Card *minesC = grid[2][index-1];
        if (!can_afford(playernum, minesC)) {
            Query_helper(playernum);
        }
        else{
        //handle dicount, gold, and normal gems
            for (int i = 0; i < 5; i++) {
                if (minesC->getPrice(i) != 0) {
                    int gems_paid = minesC->getPrice(i) - playernum->getDiscount(i);
                    int gold_paid =  gems_paid - playernum->getGemCount(i); 
                    //if normal gems aren't enough
                    if (gems_paid > playernum->getGemCount(i)) {
                    //put them back in deck
                        gem_bank[i] = gem_bank[i] + playernum->getGemCount(i);
                        //use all in normal gems
                        playernum->payGems(i, playernum->getGemCount(i));               
                        //use gold
                        playernum->payGems(5, gold_paid);
                        //reset gembank (gold)
                        gem_bank[5] = gem_bank[5] + gold_paid;
                    }
                    //if normal gems are sufficient
                    else if (gems_paid >= 0) {
                        gem_bank[i] = gem_bank[i] + gems_paid;
                        playernum->payGems(i, gems_paid);
                    } 
                }
            }
            //add prestige
            playernum->setPrestige(minesC->getPrestige());
            //add discount
            for (int i =0; i < 5; i++) {
                if (indexToColor(i) == minesC->getGemColor()) {
                    playernum->setDisocunt(i);
                    break;
                }
            }
            //get rid of the card on the grid
            grid[2][index-1] = mines.back();
            mines.pop_back();
            playernum->setPurchased();
            delete minesC;
        }
    }
    else if (row == "t") {
        Card *transportC = grid[1][index-1];
        if (!can_afford(playernum, transportC)) {
            Query_helper(playernum);
        }
        else{
            for (int i = 0; i < 5; i++) {
                if (transportC->getPrice(i) != 0) {
                    int gems_paid = transportC->getPrice(i) - playernum->getDiscount(i);
                    int gold_paid =  gems_paid - playernum->getGemCount(i);
                    //if normal gems aren't enough
                    if (gems_paid > playernum->getGemCount(i)) { 
                        //put them  back in deck
                        gem_bank[i] = gem_bank[i] + playernum->getGemCount(i);
                        //use all in normal gems
                        playernum->payGems(i, playernum->getGemCount(i));
                        //use gold
                        playernum->payGems(5, gold_paid);
                        //reset gembank (gold)
                        gem_bank[5] = gem_bank[5] + gold_paid;
                    }

                    else if (gems_paid >= 0) {
                        gem_bank[i] = gem_bank[i] + gems_paid;
                        playernum->payGems(i, gems_paid);
                    }
                }
            }
            //add prestige
            playernum->setPrestige(transportC->getPrestige());
            //add discount
            for(int i =0; i < 5; i++) {
                if(indexToColor(i) == transportC->getGemColor())
                {
                    playernum->setDisocunt(i);
                    break;
                }
            }
            grid[1][index-1] = transport.back();
            transport.pop_back();
            playernum->setPurchased();
            delete transportC;
        }
    }

    else if (row == "v") {
        Card *vendorsC = grid[0][index-1];
        if (!can_afford(playernum, vendorsC)) {
            Query_helper(playernum);
        }
        else {
        //deduce the gem count & discount --> player
            for (int i = 0; i < 5; i++) {
                if (vendorsC->getPrice(i) != 0) {
                    int gems_paid = vendorsC->getPrice(i) - playernum->getDiscount(i);
                    int gold_paid =  gems_paid - playernum->getGemCount(i);
                    if (gems_paid > playernum->getGemCount(i)) { //if normal gems aren't enough
                        //put them  back in deck
                        gem_bank[i] = gem_bank[i] + playernum->getGemCount(i);
                        //use all in normal gems
                        playernum->payGems(i, playernum->getGemCount(i));
                        //use gold
                        playernum->payGems(5, gold_paid);
                        //reset gembank (gold)
                        gem_bank[5] = gem_bank[5] + gold_paid;
                    }

                else if (gems_paid >= 0) {
                        gem_bank[i] = gem_bank[i] + gems_paid;
                        playernum->payGems(i, gems_paid);  
                    }
                }
            }
            //add prestige
            playernum->setPrestige(vendorsC->getPrestige());
            //add discount
            for (int i =0; i < 5; i++) {
                if (indexToColor(i) == vendorsC->getGemColor()) {
                    playernum->setDisocunt(i);
                    break;
                }
            }
            grid[0][index-1] = vendors.back();
            vendors.pop_back();
            playernum->setPurchased();  
            delete vendorsC; 
        }
    }
}

//check for valid input when players buy cards
bool Game::check_b(string card_type, int index)
{
    bool check1, check2;
    if ((card_type != "m" )&& (card_type != "t" ) && (card_type != "v" )) {
        cout << "Invalid move (invalid card type) - enter a valid move: ";
        check1 = false;
    }
    else {
        check1 = true;
    }

    if ((check1) && ((index <= 0) || (index > 4))) {
        cout << "Invalid move (invalid card column) - enter a valid move: " ;
        check2 = false;
    }
    else {
        check2 = true;
    }

    if (check1 && check2) {
        return true;
    }
    return false;
}
    
//check if players can afford a card
bool Game::can_afford(Player *playernum, Card *current_card)
{   
    bool check3;
    int gold_gems = playernum->getGemCount(5);
    int gems_W_discount; //gems added to discount

    for (int i = 0; i < 5; i++) {
        gems_W_discount = playernum->getDiscount(i) + playernum->getGemCount(i);
        if (current_card->getPrice(i) != 0) {
            //check if gems & discounts are enough
            if (gems_W_discount < current_card->getPrice(i)) {
                check3 = false;
            }
            else {
                check3 = true;
            }
            //check if a player can use gold gems to afford the card 
            if ((!check3) && (gold_gems < (current_card->getPrice(i) - gems_W_discount))) {
                cout << "Invalid move (cannot afford card) - enter a valid move: ";
                return false;
            }
            else if (check3) {
                continue;
            }
            else {
                //update gold_gems
                gold_gems = gold_gems - (current_card->getPrice(i) - gems_W_discount);
            }
        }
    }

    return true;
}


void Game::Q_br(Player *playernum, istream &input)
{

    int index;
    input >> index;
   
    if (!check_br(index, playernum)) {
        Query_helper(playernum);
    }
    else {
        Card *r_card = playernum->getReserve(index-1);
        if (!can_afford(playernum, r_card)) {
            Query_helper(playernum);
        }
        else {
            for (int i = 0; i < 5; i++) {
                if (r_card->getPrice(i) != 0) {
                    int gems_paid = r_card->getPrice(i) - playernum->getDiscount(i);
                    int gold_paid =  gems_paid - playernum->getGemCount(i);
                    //if normal gems aren't enough
                    if (gems_paid > playernum->getGemCount(i)) { 
                        //put them  back in deck
                        gem_bank[i] = gem_bank[i] + playernum->getGemCount(i);
                        //use all in normal gems
                        playernum->payGems(i, playernum->getGemCount(i));
                        
                        //use gold
                        playernum->payGems(5, gold_paid);
                        //reset gembank (gold)
                        gem_bank[5] = gem_bank[5] + gold_paid;
                    }

                    else if (gems_paid >= 0) {
                        gem_bank[i] = gem_bank[i] + gems_paid;
                        playernum->payGems(i, gems_paid); 
                    }
                }
            }

            playernum->setPrestige(r_card->getPrestige());
            //set discount
            for (int i =0; i < 5; i++) {
                if (indexToColor(i) == r_card->getGemColor()) {
                    playernum->setDisocunt(i);
                    break;
                }
            }
            playernum->takefromReserve(index-1);
            playernum->setPurchased();
            delete r_card;
        }  
       
    } 
}

bool Game::check_br(int index, Player *playernum)
{
    if ((index <= 0) || (index > 3)) {
        cout << "Invalid move (no card at that index) - enter a valid move: " ;
        return false;
    }
    else if (playernum->getReserve(index-1) == nullptr) {
        cout << "Invalid move (no card at that index) - enter a valid move: " ;
        return false;
    }
    return true;
}
   

//Get the gem color associated with the given index
string Game::indexToColor(int index)
{
    return colors[index];
}

//draw all of the elements onto the game board
void Game::drawBoard()
{
    int vpos = 0;
    int hpos = 1;

    //draw the card decks
    if (!vendors.empty()) {
        drawDeck(vpos, hpos, "Vendors");
    }
    vpos += CARD_HEIGHT + 1;
    if (!transport.empty()) {
        drawDeck(vpos, hpos, "Transport");
    }
    vpos += CARD_HEIGHT + 1;
    if (!mines.empty()) {
        drawDeck(vpos, hpos, "Mines");
    }

    //draw the in play cards
    vpos = 0;
    hpos = CARD_WIDTH + 2;
    for (int i = 0; i < CARD_ROWS; i++) {
        for (int j = 0; j < CARD_COLS; j++) {
            if (grid[i][j] != nullptr) {
                drawCard(vpos, hpos, grid[i][j]);
            }
            hpos += CARD_WIDTH + 1;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = CARD_WIDTH + 2;
    }

    //draw the gems
    int gemOffset = ((CARD_WIDTH + 1) * 5) + 3;
    vpos = 1;
    hpos = gemOffset;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            int index = (i * 2) + j;
            if (gem_bank[index] > 0) {
                board[vpos][hpos + 5] = gem_bank[index] + 48;
                board_color[vpos][hpos + 5] = indexToColor(index);
                drawGem(vpos + 1, hpos, indexToColor(index));
            }
            hpos += CARD_WIDTH;
        }
        vpos += CARD_HEIGHT + 1;
        hpos = gemOffset;
    }

    //draw players
   
    drawPlayer(vpos + 1, 1, &player_1);
    drawPlayer(vpos + 1, ((CARD_WIDTH + 1) * 4), &player_2);

    //draw nobles
  
    if (play_nobles) {
        hpos = ((CARD_WIDTH + 1) * 7) + 2;
        vpos = 2;
        for (int i = 0; i < NUM_NOBLES; i++) {
            if (nobles.at(i) != nullptr) {
                drawNoble(vpos, hpos, nobles.at(i));
            }
            vpos += CARD_HEIGHT + 1;
        }
    }
   

    //print out the finished board
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board_color[i][j] != "white") {
                screen_fg(board_color[i][j]);
            }
            cout << board[i][j];
            screen_fg("white");
        }
        cout << endl;
    }
    cout << endl;
}

//draws a noble at the specified position of the board
void Game::drawNoble(int vpos, int hpos, Card *c)
{
    string top = "|\\  /*\\  /|";
    string second = "| \\/   \\/ |";
    string blank = "N         N";
    string bottom = "~~~~~~~~~~~";

    //draw the basic card outline
    int length = top.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];

        for (int j = 2; j < 5; j++) {
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + 5][hpos + i] = bottom[i];
    }

    //draw the prices
    vpos += 2;
    for (int i = 0; i < GEMS - 1; i++) {
        int price = c->getPrice(i);
        if (price > 0) {
            board_color[vpos][hpos + 4] = indexToColor(i);
            board_color[vpos][hpos + 5] = indexToColor(i);
            board_color[vpos][hpos + 6] = indexToColor(i);
            board[vpos][hpos + 4] = '|';
            board[vpos][hpos + 5] = price + 48;
            board[vpos][hpos + 6] = '|';
            vpos++;
        }
    }
}

//draws a player at the specified position of the board
void Game::drawPlayer(int vpos, int hpos, Player *p)
{
    //player string
    string prestige = to_string(p->totalPrestige());
    string player_s;
    if (hpos < 10) {
        player_s = " PLAYER 1: " + prestige + " prestige point(s)";
    } else {
        player_s = " PLAYER 2: " + prestige + " prestige point(s)";
    }
    int length = player_s.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = player_s[i];
    }

    //bonus string
    vpos++;
    string bonus_s = "Discounts: ";
    length = bonus_s.length();
    for (int i = 0; i < GEMS - 1; i++) {
        int bonus = p->getDiscount(i);
        bonus_s += "|" + to_string(bonus) + "| ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
        if (bonus >= 10) {
            length += 1;
        }
    }
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = bonus_s[i];
    }

    //gem string
    vpos++;
    string gems_s = "     Gems: ";
    length = gems_s.length();
    int different_gems = GEMS;
    for (int i = 0; i < different_gems; i++) {
        int gems = p->getGemCount(i);
        gems_s += "(" + to_string(gems) + ") ";

        board_color[vpos][hpos + length] = indexToColor(i);
        board_color[vpos][hpos + length + 1] = indexToColor(i);
        board_color[vpos][hpos + length + 2] = indexToColor(i);

        length += 4;
    }
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = gems_s[i];
    }

    //reserve string
    vpos++;
    string reserve_s = " Reserved:";
    length = reserve_s.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = reserve_s[i];
    }

    hpos += reserve_s.length();
    for (int i = 0; i < 3; i++) {
        Card *c = p->getReserve(i);
        if (c == nullptr) {
            drawDeck(vpos, hpos, "");
        } else {
            drawCard(vpos, hpos, c);
        }
        hpos += CARD_WIDTH + 1;
    }
}

//draws a card deck at the specified position of the board
void Game::drawDeck(int vpos, int hpos, string type)
{
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = top[i];
        board[vpos + 1][hpos + i] = second[i];
        for (int j = 2; j < CARD_HEIGHT; j++) {
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    int start_pos = hpos + (blank.length() / 2) - (type.length() / 2);
    length = type.length();
    for (int i = 0; i < length; i++) {
        board[vpos + (CARD_HEIGHT / 2)][start_pos + i] = type[i];
    }
}

//draws a gem at the specified position of the board
void Game::drawGem(int vpos, int hpos, string color)
{
    string gem_image[6];
    gem_image[0] = "  _______  ";
    gem_image[1] = ".'_/_|_\\_'.";
    gem_image[2] = "\\`\\  |  /`/";
    gem_image[3] = " `\\  | //' ";
    gem_image[4] = "   `\\|/`   ";
    gem_image[5] = "     `     ";

    for (int i = 0; i < GEMS; i++) {
        int length = gem_image[i].length();
        for (int j = 0; j < length; j++) {
            board[vpos + i][hpos + j] = gem_image[i][j];
            board_color[vpos + i][hpos + j] = color;
        }
    }
}

//draws a card at the specified position of the board
void Game::drawCard(int vpos, int hpos, Card *c)
{
    string top = "  _________  ";
    string second = " /         \\ ";
    string blank = "|           |";
    string bottom = " \\_________/ ";

    //draw the basic card outline
    int length = top.length();
    for (int i = 0; i < length; i++) {
        board[vpos][hpos + i] = top[i];

        if (i == 8 || i == 9) {
            board_color[vpos + 1][hpos + i] = c->getGemColor();
        }
        board[vpos + 1][hpos + i] = second[i];

        for (int j = 2; j < CARD_HEIGHT; j++) {
            board[vpos + j][hpos + i] = blank[i];
        }
        board[vpos + CARD_HEIGHT][hpos + i] = bottom[i];
    }

    //draw the prestige number and gem
    board[vpos + 2][hpos + 3] = c->getPrestige() + 48;
    board_color[vpos + 2][hpos + 8] = c->getGemColor();
    board_color[vpos + 2][hpos + 9] = c->getGemColor();
    board[vpos + 2][hpos + 8] = '\\';
    board[vpos + 2][hpos + 9] = '/';
    board_color[vpos + 1][hpos + 8] = c->getGemColor();
    board_color[vpos + 1][hpos + 9] = c->getGemColor();
    board[vpos + 1][hpos + 8] = '_';
    board[vpos + 1][hpos + 9] = '_';

    //draw the prices
    vpos += 4;
    for (int i = 0; i < GEMS - 1; i++) {
        int price = c->getPrice(i);
        if (price > 0) {
            board_color[vpos][hpos + 2] = indexToColor(i);
            board_color[vpos][hpos + 3] = indexToColor(i);
            board_color[vpos][hpos + 4] = indexToColor(i);
            board[vpos][hpos + 2] = '(';
            board[vpos][hpos + 3] = price + 48;
            board[vpos][hpos + 4] = ')';
            vpos++;
        }
    }
}

//clear the board display
void Game::clearBoard()
{
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = ' ';
            board_color[i][j] = "white";
        }
    }
}
