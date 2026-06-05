#include "IO/consoleInputTaker.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int ConsoleInputTaker::getBet(const Player& player) {
  std::cout<<"Give even bet amount\n";
  int bet;
  std::cin>>bet;

  int balance = player.getBalance();
  while(bet%2 != 0 || bet > balance) {
    if(bet > balance)
      std::cout<<"Bet can't be more than your current balance, try again\n";
    if(bet%2 != 0)
      std::cout<<"Bet must be an even number, try again\n";
    std::cin>>bet;
  } 
  return bet;
}

MainMenuActions ConsoleInputTaker::getMenuAction() {
  std::cout<<"[p] - play, [q] - quit\n";
  char c;
  std::cin>>c;
  while (c != 'p' && c != 'q') {
    std::cin>>c;
  }
  switch(c) {
    case 'p':
      return MainMenuActions::PLAY;
    case 'q':
      return MainMenuActions::QUIT;
    default:
      return MainMenuActions::QUIT;
  }
}

BetweenHandActions ConsoleInputTaker::getBetweenHandsAction(const Player& player) {
  std::cout<<"[p] - play again, [q] - go back to main menu\n";
  char c;
  std::cin>>c;
  while (c != 'p' && c != 'q') {
    std::cin>>c;
  }
  switch(c) {
    case 'p':
      return BetweenHandActions::NEXT_HAND;
    case 'q':
      return BetweenHandActions::MAIN_MENU;
    default:
      return BetweenHandActions::MAIN_MENU;
  }
}

HandActions ConsoleInputTaker::getHandAction(const Player& player) {
  std::cout<<"\nActive hand:"<<player.getActiveHandConst().toString()<<"\n";
  std::string possibleActionsStr = "[h] - hit, [s] - stand";
  std::vector<char> possibleActions{'h', 's'};

  if(player.canDoubleActiveHand()) {
    possibleActionsStr += ", [d] - double";
    possibleActions.push_back('d');
  }

  if(player.canSplitActiveHand()) {
    possibleActionsStr += ", [p] - split";
    possibleActions.push_back('p');
  }

  std::cout<<possibleActionsStr<<'\n';

  char c;
  std::cin>>c;
  while (std::ranges::find(possibleActions, c) == possibleActions.end()) {
    std::cin>>c;
  }
  switch(c) {
    case 'h':
      return HandActions::HIT;
    case 's':
      return HandActions::STAND;
    case 'd':
      return HandActions::DOUBLE;
    case 'p':
      return HandActions::SPLIT;
    default:
      throw std::runtime_error("unexpected operation");
  }
}