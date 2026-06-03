#include <iostream>
#include<windows.h>
#include "hand.hpp"
#include "shoe.hpp"

/*
TODOS:
- Player
- Dealer

- Game

- GameDisplay
*/

int main() {
    SetConsoleOutputCP(65001);

    Shoe shoe(6);

    Hand hand(10, shoe.getCard(), shoe.getCard());
    hand.addCard(shoe.getCard());
    
    std::cout<<hand.toString();
    std::cout<<hand.getValue();
  
    return 0;
}