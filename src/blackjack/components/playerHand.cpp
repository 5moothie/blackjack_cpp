#include "blackjack/components/playerHand.hpp"
#include "blackjack/actions.hpp"

#include <stdexcept>
#include <vector>

bool PlayerHand::canDouble(int balance) const noexcept {
  return hand.canDouble() && balance >= bet && !playEnded && splitCounter == 0;
}

bool PlayerHand::canSplit(int balance) const noexcept {
  return hand.canSplit() && balance >= bet && !playEnded;
}


void PlayerHand::double_(Card card, int balance) {
  if(!canDouble(balance))
    throw std::runtime_error("the hand being doubled cannot be doubled");
  
  hand.hit(std::move(card));
  bet*=2;
  playEnded = true;
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

void PlayerHand::hit(Card card) {
  if(!canHit())
    throw std::runtime_error("the hand being hit cannot be hit");

  hand.hit(std::move(card));
}

std::vector<HandActions> PlayerHand::getAvailableActions(int balance) const noexcept {
  std::vector<HandActions> handActions{HandActions::STAND};

  if(canHit())
    handActions.push_back(HandActions::HIT);

  if(canDouble(balance))
    handActions.push_back(HandActions::DOUBLE);

  if(canSplit(balance))
    handActions.push_back(HandActions::SPLIT);

  return handActions;
}