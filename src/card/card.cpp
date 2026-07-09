#include "card/card.hpp"
#include<cassert>

int Card::getValue() const noexcept {
  switch(rank) {
    case Rank::Two: return 2;
    case Rank::Three: return 3; 
    case Rank::Four: return 4;
    case Rank::Five: return 5; 
    case Rank::Six: return 6;
    case Rank::Seven: return 7; 
    case Rank::Eight: return 8;
    case Rank::Nine: return 9; 
    case Rank::Ten: return 10;
    case Rank::Jack: return 10; 
    case Rank::Queen: return 10; 
    case Rank::King: return 10; 
    case Rank::Ace: return 11; 
  }
  assert(false && "Osiągnięto teoretycznie nieosiągalny kod w Card::getValue");
  __builtin_unreachable();
}

std::string Card::rankToString() const noexcept {
  switch(rank) {
    case Rank::Two: return "2";
    case Rank::Three: return "3"; 
    case Rank::Four: return "4";
    case Rank::Five: return "5"; 
    case Rank::Six: return "6";
    case Rank::Seven: return "7"; 
    case Rank::Eight: return "8";
    case Rank::Nine: return "9"; 
    case Rank::Ten: return "10";
    case Rank::Jack: return "J"; 
    case Rank::Queen: return "Q"; 
    case Rank::King: return "K"; 
    case Rank::Ace: return "A"; 
  }
  assert(false && "Osiągnięto teoretycznie nieosiągalny kod w Card:rankToString");
  __builtin_unreachable();
}


std::string Card::suitToString() const noexcept {
  switch (suit) {
    case Suit::Spades: return "♠";
    case Suit::Hearts: return "♥";
    case Suit::Diamonds: return "♦";
    case Suit::Clubs: return "♣";
  }
  assert(false && "Osiągnięto teoretycznie nieosiągalny kod w Card:suitToString");
  __builtin_unreachable();
}