#include "header.h"

int main() {


    Hand player1, player2, selection_array, selection_array2 = { 0,0,0,0,0 }; //hand struct initialization

    //scoring variables
    int pair_p1, three_of_a_kind_p1, four_of_a_kind_p1, flush_p1, straight_p1,

        pair_p2, three_of_a_kind_p2, four_of_a_kind_p2, flush_p2, straight_p2;

    int menu = 1; //menu choice variable
    int current_player = 1; //for print statements to specify which player
    int will_redraw = 0; //variable to determine whether or not dealer will redraw hand
    int winner = '\0'; //used to determine winner

    /* initialize suit array */
    const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    /* initialize face array */
    const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
    /* initalize deck array */
    int deck[4][13] = { 0 };

    srand((unsigned)time(NULL)); //seed random function for random deck

    shuffle(deck); //store randomized int values coresponding to face and suits of card deck

    printf("Hello! Welcome to five card poker : \n"); //welcome message

    do {
       
        display_menu(); //displays menu until exit or play chosen
        scanf("%d", &menu); //user enters menu decision

        system("cls"); //clear console

        switch (menu) {
        case 1: //player chose to play game

            deal(&player1, current_player, deck, face, suit); //deal random deck cards to player 1

            
            current_player = 2; //onto player 2 (dealer)
            printf("\n");
            deal(&player2, current_player, deck, face, suit); //deal random deck cards to player 2

            //allow player 1 to redraw desired cards:
            select_cards(&player1, &selection_array, deck, face, suit); //select redraw cards
            draw_cards(&player1, &selection_array, deck, face, suit); //replace redraw cards and print new set to console

            //clear console -> onto round results
            system("pause");
            system("cls");

            //determines if dealer will redraw any cards (checks to see if any scoring methods are validated)
            will_redraw = determine_dealer_redraw(&player2, &selection_array2);

            //no valid scoring methods were found in the dealers hand
            if (will_redraw == 1) {
                redraw_dealer(&player2, &selection_array2, deck, face, suit); //redraws random cards in dealers hand
            }


            //determine final score for dealer
            printf("\nDetermining scores for the dealer: \n\n"); //prints dealers scoring result to console
            pair_p2 = determine_pair(&player2, &selection_array2);
            three_of_a_kind_p2 = determine_three(&player2, &selection_array2);
            four_of_a_kind_p2 = determine_four(&player2, &selection_array2);
            flush_p2 = determine_flush(&player2, &selection_array2);
            straight_p2 = determine_straight(&player2, &selection_array2);


            //determine final score for player
            printf("\nDetermining your score: \n\n"); //prints scoring result to console
            pair_p1 = determine_pair(&player1, &selection_array);
            three_of_a_kind_p1 = determine_three(&player1, &selection_array);
            four_of_a_kind_p1 = determine_four(&player1, &selection_array);
            flush_p1 = determine_flush(&player1, &selection_array);
            straight_p1 = determine_straight(&player1, &selection_array);

            //clears console -> onto announce winner and reveal cards
            system("pause");
            system("cls");

            //determines winner by checking which score types were satisfied by each players hand
            //if the same method is satisfied (i.e both have a pair -> checks for highest face value)
            determine_winner(&player1, &player2, &winner, pair_p1, pair_p2, three_of_a_kind_p1, three_of_a_kind_p2, four_of_a_kind_p1, four_of_a_kind_p2, flush_p1, flush_p2, straight_p1, straight_p2);

            //house wins
            if (winner == 0) {
                printf("\nHouse wins... too bad...");
            }
            //player wins
            if (winner == 1) {
                printf("\nYou win! Congrats");
            }
            //tie
            if (winner == -1) {
                printf("It's... a tie :O");
            }
            printf("\n");

            //reveal the dealer's hand
            print_dealer(&player2, face, suit); 

            //round over, clear console
            system('cls');

            //prompt player to continue or exit
            printf("\nRound over... wanna play again? Enter 0 to exit and 1 to continue. \n");
            scanf("%d", &menu);

            //clears console for proceeding round
            system("cls");
            break;

        case 2: //player chose to view poker rules
            display_rules();//function to display poker rules
            break;
        case 3:
            printf("Thanks for playing poker, bye bye!! :P\n"); //exit message
            return 0;
            break;
        }
        
    } while (menu != 0); //continues menu loop until exit chosen

    return 0; //indicates program ran successfully
}
