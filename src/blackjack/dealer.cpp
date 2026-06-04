#include "blackjack/dealer.hpp"
#include <stdexcept>

bool Dealer::shouldDrawCard() const noexcept { 
  // hits on soft 17 rule
  if(hitOnSoft17 && hand->isSoft() && hand->getValue() == 17)
    return true;

  return hand->getValue() <= 16;
}

const Hand& Dealer::getHand() const {
  if(!hasHand())
    throw std::runtime_error("Dealer doesn't have a hand");
  return hand.value();
}

const Card& Dealer::getFirstCard() const {
  if(!hasHand())
    throw std::runtime_error("Dealer doesn't have a hand");
  return hand->getCards()[0];
}

void Dealer::playOutHand(Shoe& shoe) {
  if(!hasHand())
    throw std::runtime_error("Dealer doesn't have a hand");

  while(shouldDrawCard()) {
    hand->addCard(shoe.getCard());
  }
}

bool Dealer::isBust() const {
  if(!hasHand())
    throw std::runtime_error("Dealer doesn't have a hand");
  return hand->isBust();
}