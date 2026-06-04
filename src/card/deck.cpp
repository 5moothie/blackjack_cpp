#include "card/deck.hpp"
#include "card/card.hpp"

Deck::Deck() {
  for(Rank rank : ALL_RANKS)
    for(Suit suit : ALL_SUITS)
      cards.push_back(Card(rank, suit));
}