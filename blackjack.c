#include "blackjack.h"

void createDeck(Card deck[DECK_SIZE]) {
  char suits[] = {'S', 'C', 'H', 'D'};
  char ranks[] = {'A', '2', '3', '4', '5', '6', '7',
                  '8', '9', 'T', 'J', 'Q', 'K'};

  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
      deck[count].suit = suits[i];
      deck[count].rank = ranks[j];
      count++;
    }
  }
}

void shuffleDeck(Card deck[DECK_SIZE]) {
  for (int i = DECK_SIZE - 1; i > 0; i--) {
    int j = rand() % (i + 1);

    // Swap deck[i] and deck[j]
    Card temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
}

void dealInitialHands(Hand *player, Hand *dealer, Card deck[DECK_SIZE],
                      int *deckIndex) {
  for (int i = 0; i < 2; i++) {
    player->hand[i] = deck[(*deckIndex)++];
    dealer->hand[i] = deck[(*deckIndex)++];
  }

  player->count = dealer->count = 2;
}

void displayHands(Hand *player, Hand *dealer, int showDealerCard) {
  printf("Dealer: ");
  for (int i = 0; i < dealer->count; i++) {
    if (i == 1 && !showDealerCard) {
      printf("?? ");
    } else {
      printf("%c%c ", dealer->hand[i].rank, dealer->hand[i].suit);
    }
  }

  printf("\nPlayer: ");
  for (int i = 0; i < player->count; i++) {
    printf("%c%c ", player->hand[i].rank, player->hand[i].suit);
  }

  printf("\n");
}

int calculateHandValue(Hand *hand) {
  int value = 0;
  int numAces = 0;

  for (int i = 0; i < hand->count; i++) {
    switch (hand->hand[i].rank) {
    case 'A':
      value += 11;
      numAces++;
      break;
    case 'K':
    case 'Q':
    case 'J':
      value += 10;
      break;
    default:
      value += hand->hand[i].rank - '0';
    }
  }

  while (value > 21 && numAces > 0) {
    value -= 10;
    numAces--;
  }

  return value;
}

void hit(Hand *hand, Card deck[DECK_SIZE], int *deckIndex) {
  hand->hand[hand->count++] = deck[(*deckIndex)++];
}

void playDealer(Hand *dealer, Card deck[DECK_SIZE], int *deckIndex) {
  while (calculateHandValue(dealer) < 16) {
    hit(dealer, deck, deckIndex);
  }
}

void determineWinner(Hand *player, Hand *dealer, int *score) {
  int playerValue = calculateHandValue(player);
  int dealerValue = calculateHandValue(dealer);

  printf("Dealer: ");
  for (int i = 0; i < dealer->count; i++) {
    printf("%c%c ", dealer->hand[i].rank, dealer->hand[i].suit);
  }
  printf("\nPlayer: ");
  for (int i = 0; i < player->count; i++) {
    printf("%c%c ", player->hand[i].rank, player->hand[i].suit);
  }
  printf("\n");

  if (playerValue > 21) {
    printf("Bust! You lose.\n");
    *score -= 10;
  } else if (dealerValue > 21 || playerValue > dealerValue) {
    printf("You win!\n");
    *score += 10;
  } else if (playerValue < dealerValue) {
    printf("Dealer wins. You lose.\n");
    *score -= 10;
  } else {
    printf("It's a tie!\n");
  }
}

void replenishDeck(Card deck[DECK_SIZE], int *deckIndex) {
  createDeck(deck);
  shuffleDeck(deck);
  *deckIndex = 0;
}
