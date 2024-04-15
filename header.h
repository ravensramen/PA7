//Preprocessor directives

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


//initialize card struct
typedef struct card {
    int face_index;
    int suit_index;
}Card;

//initialize player hand struct
typedef struct hand {
    Card hand_array[5];
}Hand;

// Function Name : void shuffle(int wDeck[][13])
//Description: Creates a randomly shuffled deck to be used in drawing.
//Parameters: Deck multidimensional array. 
//Output: A randomly shuffled deck. 

void shuffle(int wDeck[][13]);

//Function Name: void display_menu()
//Description: Displays menu to console
//Parameters: n/a
//Output: Prints menu to console. 

void display_menu();

//Function Name: void display_rules(void)
//Description: Prints rules to console. 
//Parameters: n/a
//Output: Rules printed to console. 

void display_rules(void);

//Function Name: void deal(Hand* player, int current_player, int wDeck[][13], const char* wFace[], const char* wSuit[])
//Description: Deals top 10 cards of the randomly shuffled deck to the players
//Parameters: Player hand structs, current player indicator, shuffled deck array, face and suit string arrays
//Output: Assigns cards to players hands, prints to console.

void deal(Hand* player, int current_player, int wDeck[][13], const char* wFace[], const char* wSuit[]);

//Function Name: void select_cards(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]) {
//Description: Prompts player which cards they want to redraw
//Parameters: Hand struct, selection struct, deck array, face and suit arrays
//Output: Marks cards to be redrawn

void select_cards(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]);

//Function Name: void draw_cards(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[])
//Description: Redraws player's selected cards (up to three)
//Parameters: Player hand struct, redraw selection struct, deck array, suit and face arrays. 
//Output: Updated player hand with redrawn cards.

void draw_cards(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]);

//Function Name: int determine_pair(Hand* player, Hand* selection_array)
//Description: Determines if hand contains a pair for scoring. 
//Parameters: Player hand struct, selection array struct (for iteration)
//Output: Determines in pair(s) were found. 

int determine_pair(Hand* player, Hand* selection_array);

//Function Name: int determine_three(Hand* player, Hand* selection_array
//Description: Determines if three of a kind are in hand. 
//Parameters: Hand struct, selection struct. 
//Output: Determines if a three of a kind was found for scoring. 

int determine_three(Hand* player, Hand* selection_array);

//Function Name: int determine_four(Hand* player, Hand* selection_array)
//Description: Determines if hand contains four of a kind. 
//Parameters: Player hand struct, selection struct. 
//Output: Determines if four of a kind in hand for scoring. 

int determine_four(Hand* player, Hand* selection_array);

//Function Name: int determine_full_house(int pair, int triple)
//Description: Determines if hand contains a full house.
//Parameters: Pair and triple score variables. 
//Output: Returns a 1 if full house detected, otherwise returns a zero. 

int determine_full_house(int pair, int triple);

//Function Name: int determine_flush(Hand* player, Hand* selection_array)
//Description: Determines if player's hand contains a flush (a;; suits match)
//Parameters: Player hand struct, selection array. 
//Output: Returns a 1 if flush found, 0 if not (for scoring)

int determine_flush(Hand* player, Hand* selection_array);

//Function Name: int determine_straight(Hand* player, Hand* selection_array)
//Description: Determines if hand contains a straight (for scoring)
//Parameters: Player hand struct, selection struct. 
//Output: Returns a 1 if straight found, for scoring. 

int determine_straight(Hand* player, Hand* selection_array);

//Function Name: void determine_winner(Hand* player_1, Hand* player_2, int* winner, int pair_p1, int pair_p2, int three_of_a_kind_p1, int three_of_a_kind_p2, int four_of_a_kind_p1, int four_of_a_kind_p2, int flush_p1, int flush_p2, int straight_p1, int straight_p2)
//Description: Compares values of all satisfied scoring types of each player to determine winner. 
//Parameters: Each player's hand, pointer to winner variable, variables of each score type. 
//Output: Updates winner variable in main.

void determine_winner(Hand* player_1, Hand* player_2, int* winner, int pair_p1, int pair_p2, int three_of_a_kind_p1, int three_of_a_kind_p2, int full_house_p1, int full_house_p2, int four_of_a_kind_p1, int four_of_a_kind_p2, int flush_p1, int flush_p2, int straight_p1, int straight_p2);


//Function Name: void redraw_dealer(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]){
//Description: Redraws some of dealers hand. 
//Parameters: Dealer hand struct, selection struct, deck array, face and suit arrays
//Output: Updated dealer hand

int determine_dealer_redraw(Hand* player, Hand* selection);

//Function Name: void redraw_dealer(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]){
//Description: Redraws some of dealers hand. 
//Parameters: Dealer hand struct, selection struct, deck array, face and suit arrays
//Output: Updated dealer hand

void redraw_dealer(Hand* player, Hand* selection_array, int wDeck[][13], const char* wFace[], const char* wSuit[]);

//Function Name: int compare_faces(Hand * player1, Hand * player2, int pair_p1, int pair_p2, int three_of_a_kind_p1, int three_of_a_kind_p2, int four_of_a_kind_p1, int four_of_a_kind_p2) {
//Description: If both players satisfy the same score type, compare face values -> highest face value wins. 
//Parameters: Hand structs, scoring variables. 
//Output: Determines who has the highest face value or if tied. 

int compare_faces(Hand* player1, Hand* player2, int pair_p1, int pair_p2, int three_of_a_kind_p1, int three_of_a_kind_p2, int four_of_a_kind_p1, int four_of_a_kind_p2);

//Function Name: void print_dealer(Hand* player_2, const char* wFace[], const char* wSuit[])
//Description: Reveals dealer's hand. 
//Parameters: Dealer hand struct. 
//Output: Prints dealer's cards to console.

void print_dealer(Hand* player_2, const char* wFace[], const char* wSuit[]);
