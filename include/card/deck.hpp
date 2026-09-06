#pragma once

#include "card.hpp"
#include <vector>

class Deck {
private:
  std::vector<Card> cards{};
public:
  // create a deck filled with 52 standard cards (ordered)
  Deck();

  // return cards and remove them from the deck
  std::vector<Card> releaseCards() &&;
};