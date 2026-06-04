#pragma once

#include "card.hpp"
#include <vector>

class Deck {
private:
  std::vector<Card> cards{};
public:
  Deck();

  std::vector<Card> releaseCards() && {return std::move(cards);}
};