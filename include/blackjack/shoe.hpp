#pragma once

#include <vector>

#include "card/card.hpp"

/*
Shoe needs to be reshuffled so it's impossible for it to get empty on hand

It is automatically filled and shuffled on initialization.
*/

class Shoe {
private:
  std::vector<Card> cards{};
  size_t numberOfDecks;
  float cutCard;

  void fill() noexcept;
  void shuffle() noexcept;
  void clear() noexcept;

public:
  Shoe(size_t numberOfDecks, float cutCard);

  [[nodiscard]] Card getCard();

  void reshuffle() noexcept;

  bool needsReshuffle() const noexcept;
};