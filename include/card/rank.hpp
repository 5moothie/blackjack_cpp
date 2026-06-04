#pragma once
#include<array>

enum class Rank {
  Two = 2,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Ace
};

inline constexpr std::array<Rank, 13> ALL_RANKS = {
  Rank::Two, Rank::Three, Rank::Four, Rank::Five, Rank::Six, 
  Rank::Seven, Rank::Eight, Rank::Nine, Rank::Ten, Rank::Jack, 
  Rank::Queen, Rank::King, Rank::Ace
};