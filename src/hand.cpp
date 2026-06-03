#include "hand.hpp"

int Hand::getValue() const noexcept {
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
  return value;
}

std::string Hand::toString() const noexcept {
  std::string res = "";
  for(const auto& card : cards)
    res+=card.toString()+" ";
  return res;
}