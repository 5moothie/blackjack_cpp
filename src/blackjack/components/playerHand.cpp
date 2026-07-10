#include "blackjack/components/playerHand.hpp"

#include <stdexcept>

bool PlayerHand::canDouble(int balance) const noexcept {
  return hand.canDouble() && balance >= bet;
}

bool PlayerHand::canSplit(int balance) const noexcept {
  return hand.canSplit() && balance >= bet;
}


void PlayerHand::double_(Card card, int balance) {
  if(!canDouble(balance))
    throw std::runtime_error("the hand being doubled cannot be doubled");
  
  hand.hit(std::move(card));
  bet*=2;
}


PlayerHand PlayerHand::split(int balance) {
  if(!canSplit(balance))
    throw std::runtime_error("the hand being split cannot be split");

  Card otherCard = hand.removeCardForSplit();
  PlayerHand otherHand(bet, std::move(otherCard));

  this->splitCounter++;
  otherHand.splitCounter = this->splitCounter;

  return otherHand;
}