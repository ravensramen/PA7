#include "header.h"

//Function Name: void display_menu()
//Description: Displays menu to console
//Parameters: n/a
//Output: Prints menu to console. 

void display_menu()
{
    printf("\nEnter the coresponding integer to make a choice: \n1. Play\n2. Rules\n3. Exit\n"); 
}

//Function Name: void display_rules(void)
//Description: Prints rules to console. 
//Parameters: n/a
//Output: Rules printed to console. 

void display_rules(void) {
    printf("\nHere are the rules of 5 Card Draw Poker:\n\n");
    printf("We will each be drawn a random hand of five cards.\n");
    printf("You will get the option to redraw any of your cards.\n");
    printf("After, we will both reveal our cards, whoever had the highest score wins!\n\n");
    printf("Without further ado, let's play!\n\n");
}

//Function Name: void deal(Hand* player, int current_player, int wDeck[][13], const char* wFace[], const char* wSuit[])
//Description: Deals top 10 cards of the randomly shuffled deck to the players
//Parameters: Player hand structs, current player indicator, shuffled deck array, face and suit string arrays
//Output: Assigns cards to players hands, prints to console

void deal(Hand* player, int current_player, int wDeck[][13], const char* wFace[], const char* wSuit[])
{
    int row = 0; // row number -> suit
    int column = 0; // column number -> face
    int card = 0; /* card counter */

    //prints player 1s cards to console
    if (current_player == 1)
        printf("\nHere are your cards: \n\n");

    //notes that the dealer received their cards
    if (current_player == 2)
        printf("\nThe dealer's cards (Player 2) are face down... how mysterious!\n\n");

    // deals 10 cards from top of the deck to the players
    for (card = 1; card <= 10; card++)
    {
        // loop through rows of wDeck corresponding to suit
        for (row = 0; row <= 3; row++)
        {
            // loop through columns of wDeck for current row corresponding to face
            for (column = 0; column <= 12; column++)
            {
                /* if slot contains current card, display card */

                if (wDeck[row][column] == card) {
                    // player 1 recieves these cards
                    if (card <= 5 && current_player == 1) { //only print player 1s cards to console
                        // set cards to hand array
                        player->hand_array[card - 1].face_index = column;
                        player->hand_array[card - 1].suit_index = row;

                        // display player 1's cards to console
                        printf("%5s of %-8s%c", wFace[column], wSuit[row], card % 2 == 0 ? '\n' : '\t');
                    }
                    // player 2 (dealer) recieves these cards
                    else if (card > 5 && current_player == 2)
                    {
                        // set cards to hand array
                        player->hand_array[card - 6].face_index = column;
                        player->hand_array[card - 6].suit_index = row;
                    }
                }
            }
        }
    }
}

//Function Name: void shuffle(int wDeck[][13])
//Description: Creates a randomly shuffled deck to be used in drawing.
//Parameters: Deck multidimensional array. 
//Output: A randomly shuffled deck. 

void shuffle(int wDeck[][13])
{
    int row = 0; /* row number */
    int column = 0; /*column number */
    int card = 0; /* card counter */
    /* for each of the 52 cards, choose slot of deck randomly */

    for (card = 1; card <= 52; card++)
    {
        /* choose new random location until unoccupied slot found */
        do
        {
            row = rand() % 4;
            column = rand() % 13;
        } while (wDeck[row][column] != 0);
        /* place card number in chosen slot of deck */
        wDeck[row][column] = card;
    }
}

//Function Name: void select_cards(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]) {
//Description: Prompts player which cards they want to redraw
//Parameters: Hand struct, selection struct, deck array, face and suit arrays
//Output: Marks cards to be redrawn

void select_cards(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]) {
    int option = 0, row = 0, col = 0; 

    int redraws = 0;
    Card current = { 0,0 }, selection = { 0,0 }; //stores face and suit of card selected to redraw

    printf("Now you can choose three cards to redraw, but be careful you cannot redraw greater than three!\n");
 

    for (int i = 0; i < 5 && redraws < 4; i++) //insures that redraw can't exceed 3
    {

        // current card in players hand
        current = player->hand_array[i]; 
        printf("\nDo you want to keep this card?: \n\n%5s of %-8s%c\nEnter '1' to keep, and '2' to redraw':\n1. y\n2. n\n", wFace[current.face_index], wSuit[current.suit_index], i % 2 == 0 ? '\n' : '\t');
        scanf("%d", &option);
        switch (option) {

        case 1: //keep card
            // matches the position of the orignial hand array
            selection_array->hand_array[i] = current;
            break;

        case 2: //mark face and suit to be redrawn in draw_cards function
            selection_array->hand_array[i].face_index = 0;
            selection_array->hand_array[i].suit_index = 0;
            redraws++; //increment redraws after each iteration
            if (redraws == 3) {
                printf("\nWoah... make sure not to redraw any more!\n"); //warns the player not to exceed 3 redraws
                
                system("pause");
            }
            break;
        }
    }
}

//Function Name: void draw_cards(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[])
//Description: Redraws player's selected cards (up to three)
//Parameters: Player hand struct, redraw selection struct, deck array, suit and face arrays. 
//Output: Updated player hand with redrawn cards.

void draw_cards(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[])
{
    Card selection = { 0,0 }, current = { 0,0 };
    printf("\nOkay! here is your final hand:\n\n");
    for (int i = 0; i < 5; i++)
    {
        selection = selection_array->hand_array[i];
        current = player->hand_array[i];
        // needs to be drawn from the deck of cards to keep

        if (selection.face_index == 0) //if cards was chosen to be redrawn
        {

            selection_array->hand_array[i].face_index = rand() % 13;
            selection_array->hand_array[i].suit_index = rand() % 4;

            selection = selection_array->hand_array[i];
            player->hand_array[i] = selection;

        }
        //prints new hand to console
        printf("%5s of %-8s%c", wFace[selection.face_index], wSuit[selection.suit_index], i % 2 == 0 ? '\n' : '\t');

    }
}

//Function Name: int determine_pair(Hand* player, Hand* selection_array)
//Description: Determines if hand contains a pair for scoring. 
//Parameters: Player hand struct, selection array struct (for iteration)
//Output: Determines in pair(s) were found. 

int determine_pair(Hand* player, Hand* selection_array) {
    int pair = 0;
    Card current = { 0,0 }, next = { 0,0 }; //stores face and suit of cards to compare
    for (int i = 0; i < 5; i++) { //card 1
        for (int j = i; j < 4; j++) { //card 2 to compare
            current = player->hand_array[i];
            next = player->hand_array[j + 1];

            if (current.face_index == next.face_index) { //if faces are equal (card pair)
                selection_array->hand_array[i] = current;
                selection_array->hand_array[j + 1] = next;

                pair++; //pair detected
            }
        }
    }
    if (pair >= 1) {
        if (pair == 1) {
            printf("One pair found!\n");
        }
        if (pair > 2) {
            pair == 2; //cannot exceed two pairs (insures that pairs are not counted multiple times)
            printf("Two pairs found!!\n");
        }
    }
    else {
        printf("No pairs detected\n");
    }
    return pair;
}

//Function Name: int determine_three(Hand* player, Hand* selection_array
//Description: Determines if three of a kind are in hand. 
//Parameters: Hand struct, selection struct. 
//Output: Determines if a three of a kind was found for scoring. 

int determine_three(Hand* player, Hand* selection_array) {
    int triple = 0;
    Card current = { 0,0 }, next = { 0,0 }, next2 = { 0,0 }; //stores face and suit of compared cards

    for (int i = 0; i < 5; i++) { //card 1
        for (int j = i; j < 4; j++) { //card 2
            for (int x = j; x < 3; x++) { //card 3
                current = player->hand_array[i];
                next = player->hand_array[j + 1];
                next2 = player->hand_array[x + 2];

                //if all face values ==
                if (current.face_index == next.face_index && current.face_index == next2.face_index) {
                    triple++;
                }
            }
        }
    }
    if (triple == 1) {
        printf("Triple found!\n");
    }
    else {
        printf("No triples found\n");
    }
    return triple;
}

//Function Name: int determine_four(Hand* player, Hand* selection_array)
//Description: Determines if hand contains four of a kind. 
//Parameters: Player hand struct, selection struct. 
//Output: Determines if four of a kind in hand for scoring. 

int determine_four(Hand* player, Hand* selection_array)
{
    int four = 0;
    Card current = { 0,0 }, next = { 0,0 }, next2 = { 0,0 }, next3 = { 0,0 }; //stores face and suit of cards

    for (int i = 0; i < 5; i++) { //card 1
        for (int j = i; j < 4; j++) { //card 2
            for (int x = j; x < 3; x++) //card 3
            {
                for (int q = x; q < 2; q++) //card 4
                {
                    current = player->hand_array[i];
                    next = player->hand_array[j + 1];
                    next2 = player->hand_array[x + 2];
                    next3 = player->hand_array[q + 3];
                    // detects if any 4 cards are alike

                    //if four of the same face values found
                    if (current.face_index == next.face_index && current.face_index == next2.face_index && current.face_index == next3.face_index)
                    {
                        four++;
                    }
                }
            }
        }
    }
    if (four > 1) {
        printf("Four of a kind found!\n");
    }
    else
        printf("Four of a kind not found\n");
    return four;
}

//Function Name: int determine_flush(Hand* player, Hand* selection_array)
//Description: Determines if player's hand contains a flush (a;; suits match)
//Parameters: Player hand struct, selection array. 
//Output: Returns a 1 if flush found, 0 if not (for scoring)

int determine_flush(Hand* player, Hand* selection_array)
{
    int flush = 0;
    Card current = { 0,0 }, next = { 0,0 }, next2 = { 0,0 }, next3 = { 0,0 }, next4 = { 0,0 }; //stores face and suit of each card

    //compares all 5 cards
    current = player->hand_array[0];
    next = player->hand_array[1];
    next2 = player->hand_array[2];
    next3 = player->hand_array[3];
    next4 = player->hand_array[4];
    // detects if all 5 cards are alike

    if (current.suit_index == next.suit_index && current.suit_index == next2.suit_index && current.suit_index == next3.suit_index && current.suit_index == next4.suit_index)
    {
        flush++;
    }
    if (flush > 1) {
        printf("Flush found!\n");
    }
    else
        printf("Flush not found\n");
    return flush;
}

//Function Name: int determine_straight(Hand* player, Hand* selection_array)
//Description: Determines if hand contains a straight (for scoring)
//Parameters: Player hand struct, selection struct. 
//Output: Returns a 1 if straight found, for scoring. 

int determine_straight(Hand* player, Hand* selection_array)
{
    int straight = 0, temp = 0;

    Card current = { 0,0 }, next = { 0,0 };
    for (int i = 0; i <= 5; i++)
    {
        // checks if the current card is equal to the next card - 1.
        // needs to be in ascending order to function
        // sort array in ascending order
        for (int index = 0; index < 5; index++) {
            for (int index2 = index + 1; index2 < 5; index2++) {
                if (current.face_index > next.face_index) {
                    temp = current.face_index;
                    current.face_index = next.face_index;
                    next.face_index = temp;
                }
            }
        }
        if (current.face_index == (next.face_index) - 1)
        {
            straight++;
        }
    }
    if (straight > 1) {
        printf("Straight found\n!");
    }
    else
        printf("Straight not found\n");
    return straight;
}

//Function Name: void determine_winner(Hand* player_1, Hand* player_2, int* winner, int pair_p1, int pair_p2, int three_of_a_kind_p1, int three_of_a_kind_p2, int four_of_a_kind_p1, int four_of_a_kind_p2, int flush_p1, int flush_p2, int straight_p1, int straight_p2)
//Description: Compares values of all satisfied scoring types of each player to determine winner. 
//Parameters: Each player's hand, pointer to winner variable, variables of each score type. 
//Output: Updates winner variable in main.

void determine_winner(Hand* player_1, Hand* player_2, int* winner, int pair_p1, int pair_p2, int three_of_a_kind_p1, int three_of_a_kind_p2, int four_of_a_kind_p1, int four_of_a_kind_p2, int flush_p1, int flush_p2, int straight_p1, int straight_p2) {
    int score_player1 = 0, score_player2 = 0; //scores of each player
    int higher_face = 0; //compare face values if both players have the same score type -> greater face value wins

    if (straight_p1 > straight_p2) {
        score_player1++;
    }
    else if (flush_p1 > flush_p2) {
        score_player1++;
    }
    else if (four_of_a_kind_p1 > four_of_a_kind_p2) {
        score_player1++;
    }
    else if (three_of_a_kind_p1 > three_of_a_kind_p2) {
        score_player1++;
    }
    else if (pair_p1 > pair_p2) {
        score_player1++;
    }
    //if scored by matching faces, check to see if both players have matching faces, if so, higher face value wins
    else if ((four_of_a_kind_p1 == 1 && four_of_a_kind_p2 == 1) || (three_of_a_kind_p1 == 1 && three_of_a_kind_p2 == 1) || (pair_p1 == 1 && pair_p2 ==1) || (pair_p1 == 2 && pair_p2 ==2)) {
        higher_face = compare_faces(player_1, player_2, pair_p1, pair_p2, three_of_a_kind_p1, three_of_a_kind_p2, four_of_a_kind_p1, four_of_a_kind_p2);
        if (higher_face == 1) {
            score_player1++;
        }

    }
    if (score_player1 > score_player2) {
        *winner = 1;
    }
    else {
        *winner = 0; //house wins
    }
}

//Function Name: void redraw_dealer(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]){
//Description: Redraws some of dealers hand. 
//Parameters: Dealer hand struct, selection struct, deck array, face and suit arrays
//Output: Updated dealer hand


void redraw_dealer(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]){
    Card selection = { 0,0 }, current = { 0,0 };
    int redraws = 0;
    do {
        int i = rand() % 5; //chooses a random dealer card to redraw
        selection = selection_array->hand_array[i];
        current = player->hand_array[i]; //face and suit of current card
        // needs to be drawn from the deck of cards to keep

        selection_array->hand_array[i].face_index = rand() % 13; //generates new random face
        selection_array->hand_array[i].suit_index = rand() % 4; //generates new random suit

        selection = selection_array->hand_array[i]; //stores face and suit in selection card struct
        player->hand_array[i] = selection; //reassigned card of hand array to new random selection
        redraws++;
        
    } while (redraws < 3);
}


//Function Name: int determine_dealer_redraw(Hand* player, Hand* selection)
//Description: Auto determines if dealer will redraw any cards. Works same as score determinant. Checks if each score type (from highest to lowest can be satisfied)
//Parameters: Dealer hand struct, selection struct. 
//Output: Integer coresponding to decision of redraw or no redraw. 

int determine_dealer_redraw(Hand* player, Hand* selection) {

    //check for a straight
    int straight = 0, temp = 0;

    Card current = { 0,0 }, next = { 0,0 };
    for (int i = 0; i <= 5; i++)
    {
        for (int index = 0; index < 5; index++) {
            for (int index2 = index + 1; index2 < 5; index2++) {
                if (current.face_index > next.face_index) {
                    temp = current.face_index;
                    current.face_index = next.face_index;
                    next.face_index = temp;
                }
            }
        }
        if (current.face_index == (next.face_index) - 1)
        {
            straight++;
        }
    }
    if (straight > 1) {
        return; //dont redraw dealer's cards if straight found
    }
    else { //if no straight, check for flush
        int flush = 0;
        Card current = { 0,0 }, next = { 0,0 }, next2 = { 0,0 }, next3 = { 0,0 }, next4 = { 0,0 };

        current = player->hand_array[0];
        next = player->hand_array[1];
        next2 = player->hand_array[2];
        next3 = player->hand_array[3];
        next4 = player->hand_array[4];
        // detects if any 5 cards are alike
        if (current.suit_index == next.suit_index && current.suit_index == next2.suit_index && current.suit_index == next3.suit_index && current.suit_index == next4.suit_index)
        {
            flush++;
        }
        if (flush == 1) {
            return 0; //don't redraw if flush found
        }
        else { //go on to check for four of a kind if no flush found
            int four = 0;
            Card current = { 0,0 }, next = { 0,0 }, next2 = { 0,0 }, next3 = { 0,0 };

            for (int i = 0; i < 5; i++) {
                for (int j = i; j < 4; j++) {
                    for (int x = j; x < 3; x++)
                    {
                        for (int q = x; q < 2; q++)
                        {
                            current = player->hand_array[i];
                            next = player->hand_array[j + 1];
                            next2 = player->hand_array[x + 2];
                            next3 = player->hand_array[q + 3];
                            // detects if any 4 cards are alike

                            if (current.face_index == next.face_index && current.face_index == next2.face_index && current.face_index == next3.face_index)
                            {
                                four++;
                            }
                        }
                    }
                }
            }
            if (four == 1) {
                return 0; //don't redraw hand if four of a kind are found
            }
            else {
                int triple = 0;
                Card current = { 0,0 }, next = { 0,0 }, next2 = { 0,0 };

                for (int i = 0; i < 5; i++) {
                    for (int j = i; j < 4; j++) {
                        for (int x = j; x < 3; x++) {
                            current = player->hand_array[i];
                            next = player->hand_array[j + 1];
                            next2 = player->hand_array[x + 2];

                            if (current.face_index == next.face_index && current.face_index == next2.face_index) {
                                triple++;
                            }
                        }
                    }
                }
                if (triple == 1) {
                    return 0; //don't redraw
                }
                else { //check for pairs
                    int pair = 0;
                    Card current = { 0,0 }, next = { 0,0 };
                    for (int i = 0; i < 5; i++) {
                        for (int j = i; j < 4; j++) {
                            current = player->hand_array[i];
                            next = player->hand_array[j + 1];

                            if (current.face_index == next.face_index) { //if faces are equal (card pair)

                                pair++; //pair detected
                            }
                        }
                    }
                    if (pair >= 1) {
                        return 0; //don't redraw if a pair was detected in dealer hand
                        }
                    else {
                        return 1; //redraws dealer's hand if all scoring options won't work
                    }
                }
               
            }
            
        }
    }
}

//Function Name: int compare_faces(Hand * player1, Hand * player2, int pair_p1, int pair_p2, int three_of_a_kind_p1, int three_of_a_kind_p2, int four_of_a_kind_p1, int four_of_a_kind_p2) {
//Description: If both players satisfy the same score type, compare face values -> highest face value wins. 
//Parameters: Hand structs, scoring variables. 
//Output: Determines who has the highest face value or if tied. 

int compare_faces(Hand * player1, Hand * player2, int pair_p1, int pair_p2, int three_of_a_kind_p1, int three_of_a_kind_p2, int four_of_a_kind_p1, int four_of_a_kind_p2) {
        int highest_player1 = 0, highest_player2 = 0;

        // Find the highest face value for player 1
        if (pair_p1 > 0) {
            for (int i = 0; i < 5; i++) {
                for (int j = i + 1; j < 5; j++) {
                    if (player1->hand_array[i].face_index == player1->hand_array[j].face_index) {
                        highest_player1 = player1->hand_array[i].face_index;
                    }
                }
            }
        }
        else if (three_of_a_kind_p1 > 0) {
            for (int i = 0; i < 3; i++) {
                if (player1->hand_array[i].face_index == player1->hand_array[i + 1].face_index &&
                    player1->hand_array[i].face_index == player1->hand_array[i + 2].face_index) {
                    highest_player1 = player1->hand_array[i].face_index;
                }
            }
        }
        else if (four_of_a_kind_p1 > 0) {
            for (int i = 0; i < 2; i++) {
                if (player1->hand_array[i].face_index == player1->hand_array[i + 1].face_index &&
                    player1->hand_array[i].face_index == player1->hand_array[i + 2].face_index &&
                    player1->hand_array[i].face_index == player1->hand_array[i + 3].face_index) {
                    highest_player1 = player1->hand_array[i].face_index;
                }
            }
        }

        // Find the highest face value for player 2
        if (pair_p2 > 0) {
            for (int i = 0; i < 5; i++) {
                for (int j = i + 1; j < 5; j++) {
                    if (player2->hand_array[i].face_index == player2->hand_array[j].face_index) {
                        highest_player2 = player2->hand_array[i].face_index;
                    }
                }
            }
        }
        else if (three_of_a_kind_p2 > 0) {
            for (int i = 0; i < 3; i++) {
                if (player2->hand_array[i].face_index == player2->hand_array[i + 1].face_index &&
                    player2->hand_array[i].face_index == player2->hand_array[i + 2].face_index) {
                    highest_player2 = player2->hand_array[i].face_index;
                }
            }
        }
        else if (four_of_a_kind_p2 > 0) {
            for (int i = 0; i < 2; i++) {
                if (player2->hand_array[i].face_index == player2->hand_array[i + 1].face_index &&
                    player2->hand_array[i].face_index == player2->hand_array[i + 2].face_index &&
                    player2->hand_array[i].face_index == player2->hand_array[i + 3].face_index) {
                    highest_player2 = player2->hand_array[i].face_index;
                }
            }
        }

        // Compare the highest face values
        if (highest_player1 > highest_player2) {
            return 1; // Player 1 has a higher face value
        }
        else if (highest_player2 > highest_player1) {
            return 0; // Player 2 has a higher face value
        }
        else if (highest_player1 == highest_player2){
            return -1; // It's a tie
        }
    }

//Function Name: void print_dealer(Hand* player_2, const char* wFace[], const char* wSuit[])
//Description: Reveals dealer's hand. 
//Parameters: Dealer hand struct. 
//Output: Prints dealer's cards to console. 

void print_dealer(Hand* player_2, const char* wFace[], const char* wSuit[]) {

    printf("\nThese were the dealers cards: \n");
    for (int i = 0; i < 5; i++) {
        printf("%5s of %-8s%c", wFace[player_2->hand_array[i].face_index], wSuit[player_2->hand_array[i].suit_index], i % 2 == 0 ? '\n' : '\t');
    }
}
