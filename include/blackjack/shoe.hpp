#pragma once

#include <vector>

#include "card/card.hpp"

/*
Shoe needs to be reshuffled so it's impossible for it to get empty on hand

It is automatically filled and shuffled on initialization.

It is up to the user to set correct cutCard and reshuffle the deck. If there are no cards in the deck, getCard will throw std::runtime_error();
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

  // if there is <= cutCard decks left in the shoe - needs reshuffle will be true
  bool needsReshuffle() const noexcept;
};