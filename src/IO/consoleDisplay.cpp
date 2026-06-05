#include "IO/consoleDisplay.hpp"

#include <iostream>

void ConsoleDisplay::clearConsole() const noexcept {
  for (int i = 0; i < 50; ++i)
    std::cout << '\n';
}

void ConsoleDisplay::showMainMenu() {
  clearConsole();

  std::cout << "Welcome. Wanna play some blackjack?\n";
}

void ConsoleDisplay::showTable(const Dealer& dealer, const Player& player) {
  clearConsole();

  std::cout<<"Dealer: "<< dealer.getFirstCard().toString() << " XX" << "\n";
  std::cout<<"\nPlayer hands: ";
  for(const auto& hand : player.getAllHands()) {
    std::cout<<hand.toString()<< " | ";
  }
  std::cout<<"\n";
}
void ConsoleDisplay::showBettingScreen(const Player& player) {
  clearConsole();
  
  std::cout<<"Your balance: " << player.getBalance() << "\n";
}


void ConsoleDisplay::showHandResults(const Dealer& dealer, const Player& player) {
  clearConsole();
  const Hand dealersHand = dealer.getHand();
  
  std::cout<<"Dealer: "<< dealersHand.toString() << "(" << dealersHand.getValue() << ")" << (dealersHand.isBust() ? " BUST" : "" ) << "\n";
  std::cout<<"\nPlayer hands: ";

  for(const auto& hand : player.getAllHands()) {
    std::cout << hand.toString() <<"(" << hand.getValue() << ")\t";

    int bet = hand.getBet();
    if(hand.isBust()) {
      std::cout<<"BUST (-"<<bet<<")\n";
      continue;
    }
    

    if(hand.isBlackjack()) {
      if(dealersHand.isBlackjack())
        std::cout<<"DRAW\n";
      else
        std::cout<<"BLACKJACK (+"<<(int)(3*bet/2)<<")\n";
      continue;
    }

    if(dealersHand.isBlackjack()) {
      std::cout<<"LOST (-"<<bet<<")\n";
      continue;
    }

    if(dealersHand.isBust() || hand.getValue() > dealersHand.getValue()) {
      std::cout<<"WON (+"<<bet<<")\n";
      continue;
    } else if(hand.getValue() == dealersHand.getValue()) {
      std::cout<<"DRAW\n";
      continue;
    }
    std::cout<<"LOST (-"<<bet<<")\n";
  }
  std::cout<<"\nNew balance: "<<player.getBalance()<<"\n";
}