#pragma once

#include <array>

enum class Suit {
  Spades,
  Hearts, 
  Diamonds, 
  Clubs, 
};

inline constexpr std::array<Suit, 4> ALL_SUITS = {
  Suit::Spades, Suit::Hearts, Suit::Diamonds, Suit::Clubs
};