#include "card/deck.hpp"
#include "card/card.hpp"
#include <stdexcept>

Deck::Deck() {
  for(Rank rank : ALL_RANKS)
    for(Suit suit : ALL_SUITS)
      cards.push_back(Card(rank, suit));
}

std::vector<Card> Deck::releaseCards() && {
  if(cards.size() != 52) 
    throw std::runtime_error("The deck isn't full");
  return std::move(cards);
}