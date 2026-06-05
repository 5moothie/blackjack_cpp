#include <random>
#include <algorithm>

#include "blackjack/shoe.hpp"
#include "card/deck.hpp"
#include <stdexcept>

Shoe::Shoe(size_t numberOfDecks, float cutCard): 
            numberOfDecks(numberOfDecks), cutCard(cutCard) {
  fill(); 
  shuffle();
}

void Shoe::fill() noexcept {
  for(size_t i = 0; i < numberOfDecks; ++i) {
    Deck deck;
    auto newCards = std::move(deck).releaseCards();
    cards.insert(cards.end(), newCards.begin(), newCards.end());
  }
}

void Shoe::shuffle() noexcept {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::ranges::shuffle(cards, gen);
}

void Shoe::clear() noexcept {
  cards.clear();
}

Card Shoe::getCard() {
  if(cards.empty())
    throw std::runtime_error("Shoe is empty an a card is drawn.");

  Card card = std::move(cards.back());
  cards.pop_back();
  return card;
}

void Shoe::reshuffle() noexcept {
  clear();
  fill();
  shuffle();
}

bool Shoe::needsReshuffle() const noexcept {
  int reshuffleBelow = (int)(numberOfDecks * cutCard);
  return cards.size() <= reshuffleBelow;
}