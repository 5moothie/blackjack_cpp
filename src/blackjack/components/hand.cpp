#include "blackjack/components/hand.hpp"
#include <stdexcept>

Hand::HandScore Hand::calculateScore() const noexcept {
  int acesCount = 0;
  int value = 0;
  for(const auto& card : cards) {
    if(card.getRank() == Rank::Ace)
      acesCount++;
    
    value += card.getValue();
  }

  // if there are aces and it busts, decrease the value of aces to 1
  while(value > 21 && acesCount > 0) {    
    value-=10;
    --acesCount;
  }
  return {value, acesCount};
}

int Hand::getValue() const noexcept {
  return calculateScore().value;
}

std::string Hand::toString() const noexcept {
  std::string res = "";
  for(const auto& card : cards)
    res+=card.toString()+" ";
  return res;
}

bool Hand::isSoft() const noexcept {
  return calculateScore().acesCount;
}

void Hand::hit(Card card) noexcept {
  cards.push_back(std::move(card));
}

bool Hand::canDouble() const noexcept {
  return getSize() == 2;
}

bool Hand::canSplit() const noexcept {
  return getSize() == 2 && cards[0].getRank() == cards[1].getRank();
}

Card Hand::removeCardForSplit() {
  if(!canSplit())
    throw std::runtime_error("The hand being split cannot be split");

  Card removed = std::move(cards.back());
  cards.pop_back();

  return removed;
}