#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DECK_SIZE 52
#define MAX_HAND_SIZE 5
#define BLACKJACK 21
#define WIN_POINTS 10
#define INITIAL_POINTS 100
#define MIN_DECK_SIZE 20

typedef struct {
		char rank;
		char suit;
} Card;

typedef struct {
		Card hand[MAX_HAND_SIZE];
		int count;
} Hand;

void createDeck(Card deck[DECK_SIZE]);
void shuffleDeck(Card deck[DECK_SIZE]);
void dealInitialHands(Hand *player, Hand *dealer, Card deck[DECK_SIZE], int *deckIndex);
void displayHands(Hand *player, Hand *dealer, int showDealerCard);
int calculateHandValue(Hand *hand);
void hit(Hand *hand, Card deck[DECK_SIZE], int *deckIndex);
void playDealer(Hand *dealer, Card deck[DECK_SIZE], int *deckIndex);
void determineWinner(Hand *player, Hand *dealer, int *score);
void replenishDeck(Card deck[DECK_SIZE], int *deckIndex);

#endif  // BLACKJACK_H
