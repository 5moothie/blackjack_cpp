#include "blackjack/player.hpp"
#include <stdexcept>

Hand& Player::getActiveHand() {
  if(activeHand >= hands.size())
    throw std::runtime_error("No more active hands");

  return hands[activeHand];  
}

const Hand& Player::getActiveHandConst() const {
  if(activeHand >= hands.size())
    throw std::runtime_error("No more active hands");

  return hands[activeHand];  
}

bool Player::canDoubleActiveHand() const {
  return getActiveHandConst().canDouble() && getActiveHandConst().getBet() <= balance;
}

bool Player::canSplitActiveHand() const {
  return getActiveHandConst().canSplit() && getActiveHandConst().getBet() <= balance;
}

void Player::hitActiveHand(Shoe& shoe) {
  if(getActiveHand().isBust())
    throw std::runtime_error("The hand that is being hit is bust.");

  getActiveHand().hit(shoe.getCard());

  if(getActiveHand().isBust())
    activeHand++;
}

void Player::doubleActiveHand(Shoe& shoe) {
  if(!canDoubleActiveHand())
    throw std::runtime_error("The hand that is being doubled cannot be doubled.");
  if(getActiveHand().isBust())
    throw std::runtime_error("The hand that is being doubled is bust.");
  
  balance-=getActiveHand().getBet();
  getActiveHand().double_(shoe.getCard());


  activeHand++;
}

void Player::standActiveHand() {
  activeHand++;
}

void Player::splitActiveHand(Shoe& shoe) {
  if(!canSplitActiveHand())
    throw std::runtime_error("The hand that is being split cannot be split.");
  if(getActiveHand().isBust())
    throw std::runtime_error("The hand that is being doubled is bust.");

  int bet = getActiveHand().getBet();
  Hand hand = getActiveHand().split();
  hand.hit(shoe.getCard());
  hands.push_back(hand);
  balance-=bet;

  getActiveHand().hit(shoe.getCard());
}


void Player::settleHands(const Hand& dealersHand) {
  if(hasActiveHand())
    throw std::runtime_error("player is still playing");
  for(const Hand& hand : hands) {
    if(hand.isBust())
      continue;

    int bet = hand.getBet();

    if(hand.isBlackjack()) {
      if(dealersHand.isBlackjack())
        balance+=bet;
      else
        balance+=bet*3/2 + bet;
      continue;
    }

    if(dealersHand.isBlackjack())
      continue;

    if(dealersHand.isBust() || hand.getValue() > dealersHand.getValue())
      balance+=bet + bet;
    else if(hand.getValue() == dealersHand.getValue())
      balance+=bet;
  }
}

void Player::clearHands() noexcept {
  hands.clear();
  activeHand = 0;
}

void Player::playNewHand(int bet, Shoe& shoe) {
  if(balance < bet)
    throw std::runtime_error("The balance is not sufficient for this bet.");
  balance-=bet;
  hands.push_back(Hand(bet, shoe.getCard(), shoe.getCard())); 
}