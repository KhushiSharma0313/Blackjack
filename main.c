#include "blackjack.h"

int main() {
		srand(time(NULL));

		printf("******* Blackjack game ********\n");

		int score = INITIAL_POINTS;
		char command[10];

		do {
				printf("Total: %d\n", score);

				Card deck[DECK_SIZE];
				createDeck(deck);
				shuffleDeck(deck);

				Hand playerHand = {{0}, 0};
				Hand dealerHand = {{0}, 0};
				int deckIndex = 0;

				dealInitialHands(&playerHand, &dealerHand, deck, &deckIndex);
				displayHands(&playerHand, &dealerHand, 1);

				// Player's turn
				do {
						printf("> ");
						scanf("%s", command);

						if (strcmp(command, "hit") == 0) {
								hit(&playerHand, deck, &deckIndex);
								displayHands(&playerHand, &dealerHand, 1);

								if (calculateHandValue(&playerHand) > BLACKJACK) {
										printf("Bust! You lose.\n");
										determineWinner(&playerHand, &dealerHand, &score);
										break;
								}
						} else if (strcmp(command, "stay") == 0) {
								break;
						} else if (strcmp(command, "quit") == 0) {
								printf("Good game!\n");
								return 0;
						} else {
								printf("Invalid command. Valid commands: hit, stay, quit\n");
						}
				} while (1);

				// Dealer's turn
				playDealer(&dealerHand, deck, &deckIndex);
				displayHands(&playerHand, &dealerHand, 0);

				// Determine the winner
				determineWinner(&playerHand, &dealerHand, &score);

				// Check if the deck needs replenishing
				if (DECK_SIZE - deckIndex <= MIN_DECK_SIZE) {
						replenishDeck(deck, &deckIndex);
						printf("A new deck is in use.\n");
				}
		} while (score > 0);

		printf("Out of points. Game over!\n");

		return 0;
}
