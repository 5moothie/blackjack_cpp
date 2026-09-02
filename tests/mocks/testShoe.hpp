#pragma once

#include "blackjack/components/shoe.hpp"
#include <vector>

class TestShoe : public Shoe {
public:
  TestShoe(size_t numberOfDecks = 1, float cutCard = 0.5f): Shoe(numberOfDecks, cutCard) {}
  
  void setShoe(std::vector<Card> cards) { this->cards = cards; }

  void addCardTop(Card card) { this->cards.push_back(card); }
  void addCardsTop(std::vector<Card> cards) { this->cards.insert(this->cards.end(), cards.begin(), cards.end()); }

  std::vector<Card> getCards() { return cards; }
};