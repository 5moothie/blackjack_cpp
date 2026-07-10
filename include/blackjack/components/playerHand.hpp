#pragma once


#include "blackjack/components/hand.hpp"


/*
PlayerHand is a one round class - after a round it should be destroyed and a new hand must be created for the next one
*/

class PlayerHand {
private:
  int bet;
  Hand hand;
  int splitCounter{0};

public:
  PlayerHand(int bet): bet(bet), hand() {}
  PlayerHand(int bet, Card card): bet(bet), hand(std::move(card)) {}
  PlayerHand(int bet, Card card1, Card card2): bet(bet), hand(std::move(card1), std::move(card2)) {}

  [[nodiscard]] const std::vector<Card>& getCards() const noexcept { return hand.getCards(); }
  [[nodiscard]] size_t getSize() const noexcept { return hand.getSize(); }
  [[nodiscard]] int getBet() const noexcept { return bet; }
  [[nodiscard]] std::string toString() const noexcept { return hand.toString(); }

  [[nodiscard]] int getValue() const noexcept { return hand.getValue(); }
  [[nodiscard]] bool isBust() const noexcept { return hand.getValue() > 21; }
  [[nodiscard]] bool isBlackjack() const noexcept { return hand.getValue() == 21 && hand.getSize() == 2 && splitCounter == 0; }
  [[nodiscard]] bool isSoft() const noexcept { return hand.isSoft(); };

  bool canDouble(int balance) const noexcept;
  bool canSplit(int balance) const noexcept;

  void hit(Card card) noexcept { hand.hit(std::move(card)); };
  void double_(Card card, int balance);
  PlayerHand split(int balance);
  void clear() noexcept {hand.clear();}
};