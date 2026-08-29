#include "blackjack/components/dealer.hpp"
#include <stdexcept>

void Dealer::newHand(Shoe& shoe) {
  if(hasHand())
    throw std::runtime_error("dealer already has a hand");

  hand.emplace(std::move(shoe.getCard()), std::move(shoe.getCard()));
  handPlayedOut = false;
}

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

  if(handPlayedOut)
    return;

  while(shouldDrawCard()) {
    hand->hit(shoe.getCard());
  }

  handPlayedOut = true;
}

bool Dealer::isBust() const {
  if(!hasHand())
    throw std::runtime_error("Dealer doesn't have a hand");
  return hand->isBust();
}

const bool Dealer::peekForBlackjack() const {
  Card firstCard = getFirstCard();
  
  if(firstCard.getValue() < 10)
    throw std::runtime_error("first card in hand isn't 10-val or Ace");

  return hand->isBlackjack();
}