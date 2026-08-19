#pragma once


#include "blackjack/IO/actions.hpp"
#include "blackjack/components/hand.hpp"
#include <vector>


/*
PlayerHand is a one round class - after a round it should be destroyed and a new hand must be created for the next one.

PlayerHand with no cards is not allowed.
*/

class PlayerHand {
private:
  int bet;
  Hand hand;
  int splitCounter{0};
  bool playEnded{false};

public:
  PlayerHand(int bet, Card card): bet(bet), hand(std::move(card)) {}
  PlayerHand(int bet, Card card1, Card card2): bet(bet), hand(std::move(card1), std::move(card2)) {}

  [[nodiscard]] const std::vector<Card>& getCards() const noexcept { return hand.getCards(); }
  [[nodiscard]] size_t getSize() const noexcept { return hand.getSize(); }
  [[nodiscard]] int getBet() const noexcept { return bet; }
  [[nodiscard]] std::string toString() const noexcept { return hand.toString(); }

  [[nodiscard]] int getValue() const noexcept { return hand.getValue(); }
  [[nodiscard]] bool isBust() const noexcept { return hand.isBust(); }
  [[nodiscard]] bool isBlackjack() const noexcept { return hand.isBlackjack() && splitCounter == 0; }
  [[nodiscard]] bool isSoft() const noexcept { return hand.isSoft(); };
  [[nodiscard]] std::vector<HandActions> getAvailableActions(int balance) const noexcept;
  [[nodiscard]] bool didPlayEnd() const noexcept {return playEnded;}

  bool canDouble(int balance) const noexcept;
  bool canSplit(int balance) const noexcept;
  bool canHit() const noexcept { return !playEnded && !isBust(); };

  void hit(Card card);
  void double_(Card card, int balance);
  void stand() { playEnded = true; };
  PlayerHand split(int balance);
};