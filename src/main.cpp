#include <iostream>
#include<windows.h>
#include "card.hpp"

int main() {
    SetConsoleOutputCP(65001);

    Card card(Rank::Seven, Suit::Spades);
    std::cout<<card.toString();
  
    return 0;
}