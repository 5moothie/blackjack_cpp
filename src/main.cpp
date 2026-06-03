#include <iostream>
#include<windows.h>
#include "hand.hpp"

int main() {
    SetConsoleOutputCP(65001);

    Card card1(Rank::Seven, Suit::Spades);
    Card card2(Rank::Ace, Suit::Hearts);

    Hand hand(10, card1, card2);
    
    std::cout<<hand.toString();
    std::cout<<hand.getValue();
  
    return 0;
}