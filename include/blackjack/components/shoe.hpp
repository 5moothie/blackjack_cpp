#pragma once

#include <vector>

#include "card/card.hpp"

/*
POSSIBLE OPTIMIZATION: ARRAY + ptr so you don't have to fill the deck should be faster
*/

/*
Shoe needs to be reshuffled manually with reshuffle funciton.
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
  /* 
  Fills the shoe with numberOfDecks decks and sets a cutcard.
  Shuffles the cards. 
  CutCard is counted in remaining decks. So f.eg. 1.5 cutcard means that if there are <= 1.5*52 cards left in the shoe, then the shoe needs reshuffling.
  */
  Shoe(size_t numberOfDecks, float cutCard);

  // returns a card from the top and removes it from the deck
  [[nodiscard]] Card getCard();

  // fills the deck to the first set number of decks and reshuffles it
  void reshuffle() noexcept;

  // returns if the cutCard has already been exceeded
  bool needsReshuffle() const noexcept;
};