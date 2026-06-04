#pragma once

#include <vector>
#include <utility>
#include <string>

#include "card/card.hpp"

/*
Hand is a one round class - after a round it should be destroyed and a new hand must be created for the next one
*/

class Hand {
private:
  std::vector<Card> cards{};
  int bet;

public:
  Hand(int bet): bet(bet) {}
  Hand(int bet, Card card): bet(bet), cards{std::move(card)} {}
  Hand(int bet, Card card1, Card card2): bet(bet), cards{std::move(card1), std::move(card2)} {}

  [[nodiscard]] const std::vector<Card>& getCards() const noexcept { return cards; }
  [[nodiscard]] size_t getSize() const noexcept { return cards.size(); }
  [[nodiscard]] int getBet() const noexcept { return bet; }
  [[nodiscard]] std::string toString() const noexcept;

  [[nodiscard]] int getValue() const noexcept;
  [[nodiscard]] bool isBust() const noexcept {return getValue() > 21;}
  [[nodiscard]] bool isBlackjack() const noexcept {return getValue() == 21 && getSize() == 2;}
  [[nodiscard]] bool isSoft() const noexcept;

  void addCard(Card card) noexcept {cards.push_back(std::move(card));}
  void clear() noexcept {cards.clear();}

  void doubleBet() noexcept { bet*=2; }
};