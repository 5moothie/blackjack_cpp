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

  struct HandScore{
    int value;
    int acesCount;
  };
  HandScore calculateScore() const noexcept;
  
public:
  Hand() = default;
  Hand(Card card): cards{std::move(card)} {}
  Hand(Card card1, Card card2): cards{std::move(card1), std::move(card2)} {}

  [[nodiscard]] const std::vector<Card>& getCards() const noexcept { return cards; }
  [[nodiscard]] size_t getSize() const noexcept { return cards.size(); }
  [[nodiscard]] std::string toString() const noexcept;

  [[nodiscard]] int getValue() const noexcept;
  [[nodiscard]] bool isBust() const noexcept {return getValue() > 21;}
  [[nodiscard]] bool isBlackjack() const noexcept {return getValue() == 21 && getSize() == 2; }
  [[nodiscard]] bool isSoft() const noexcept;

  bool canDouble() const noexcept;
  bool canSplit() const noexcept;

  Card removeCardForSplit();

  void hit(Card card) noexcept;
  void clear() noexcept {cards.clear();}
};