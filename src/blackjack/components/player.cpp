#include "blackjack/components/player.hpp"
#include <stdexcept>

PlayerHand& Player::getActiveHand() {
  if(activeHand >= hands.size())
    throw std::runtime_error("No more active hands");

  return hands[activeHand];  
}

void Player::activateNextHand() noexcept {
  if(activeHand > hands.size())
    return;
  activeHand++;
}

const PlayerHand& Player::getActiveHandConst() const {
  if(activeHand >= hands.size())
    throw std::runtime_error("No more active hands");

  return hands[activeHand];  
}

bool Player::canDoubleActiveHand() const {
  return getActiveHandConst().canDouble(balance);
}

bool Player::canSplitActiveHand() const {
  return getActiveHandConst().canSplit(balance);
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
  getActiveHand().double_(shoe.getCard(), balance);


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

  long long bet = getActiveHand().getBet();
  PlayerHand hand = getActiveHand().split(balance);
  hand.hit(shoe.getCard());
  hands.push_back(hand);
  balance-=bet;

  getActiveHand().hit(shoe.getCard());
}


void Player::settleHands(const Hand& dealersHand) {
  if(hasActiveHand())
    throw std::runtime_error("player is still playing");
  for(const PlayerHand& hand : hands) {
    if(hand.isBust())
      continue;

    long long bet = hand.getBet();

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

void Player::addHand(long long bet, Shoe& shoe) {
  if(balance < bet)
    throw std::runtime_error("The balance is not sufficient for this bet.");
  balance-=bet;
  hands.push_back(PlayerHand(bet, shoe.getCard(), shoe.getCard())); 
}