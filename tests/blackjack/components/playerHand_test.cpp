#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "blackjack/components/playerHand.hpp"
#include "card/card.hpp"
#include "card/rank.hpp"
#include "card/suit.hpp"


// splitting leaves one card and returns another PlayerHand with one card

TEST_CASE("PlayerHand created with one card contains one correct card") {
  Card c1(Rank::Ace, Suit::Clubs);
  PlayerHand hand(20, Card(Rank::Ace, Suit::Clubs));

  auto cards = hand.getCards();

  REQUIRE(cards.size() == 1);
  REQUIRE(cards[0].getRank() == c1.getRank());
  REQUIRE(cards[0].getSuit() == c1.getSuit());
}

TEST_CASE("PlayerHand created with 2 cards contains 2 correct cards") {
  Card c1(Rank::King, Suit::Clubs);
  Card c2(Rank::Two, Suit::Spades);

  PlayerHand hand(20, Card(Rank::King, Suit::Clubs), Card(Rank::Two, Suit::Spades));

  auto cards = hand.getCards();

  REQUIRE(cards.size() == 2);
  REQUIRE(cards[0].getRank() == c1.getRank());
  REQUIRE(cards[0].getSuit() == c1.getSuit());
  REQUIRE(cards[1].getRank() == c2.getRank());
  REQUIRE(cards[1].getSuit() == c2.getSuit());
}

TEST_CASE("PlayerHand is created with correct bet") {
  PlayerHand hand1(20, Card(Rank::King, Suit::Clubs));
  PlayerHand hand2(30, Card(Rank::King, Suit::Clubs), Card(Rank::Two, Suit::Spades));

  REQUIRE(hand1.getBet() == 20);
  REQUIRE(hand2.getBet() == 30);
}

TEST_CASE("(PlayerHand) hit adds correct card to the hand") {
  PlayerHand hand(20, Card(Rank::King, Suit::Clubs), Card(Rank::Two, Suit::Spades));
  hand.hit(Card(Rank::Five, Suit::Spades));
  Card c = Card(Rank::Five, Suit::Spades);
  
  auto cards = hand.getCards();

  REQUIRE(cards.back().getRank() == c.getRank());
  REQUIRE(cards.back().getSuit() == c.getSuit());
}

TEST_CASE("(PlayerHand) hit doesn't change hand bet") {
  PlayerHand hand(20, Card(Rank::King, Suit::Clubs), Card(Rank::Two, Suit::Spades));
  hand.hit(Card(Rank::Five, Suit::Spades));

  REQUIRE(hand.getBet() == 20);
}

TEST_CASE("(PlayerHand) getSize correctly returns amount of cards") {
  PlayerHand hand(20, Card(Rank::King, Suit::Clubs));
  REQUIRE(hand.getSize() == 1);
  
  hand.hit(Card(Rank::Five, Suit::Spades));
  REQUIRE(hand.getSize() == 2);

  hand.hit(Card(Rank::Five, Suit::Spades));
  REQUIRE(hand.getSize() == 3);
}


TEST_CASE("(PlayerHand) getValue returns correct value for hard hands without ace") {
  PlayerHand val12PlayerHand(20, Card(Rank::King, Suit::Clubs), Card(Rank::Two, Suit::Spades));
  PlayerHand val7PlayerHand(20, Card(Rank::Five, Suit::Spades), Card(Rank::Two, Suit::Spades));
  PlayerHand val15PlayerHand(20, Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));
  PlayerHand val25PlayerHand(20, Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));
  val25PlayerHand.hit(Card(Rank::King, Suit::Spades));

  REQUIRE(val12PlayerHand.getValue() == 12);
  REQUIRE(val7PlayerHand.getValue() == 7);
  REQUIRE(val15PlayerHand.getValue() == 15);
  REQUIRE(val25PlayerHand.getValue() == 25);
}

TEST_CASE("(PlayerHand) getValue returns correct value for soft hands") {
  PlayerHand val13PlayerHand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::Two, Suit::Diamonds));
  PlayerHand val20PlayerHand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::Nine, Suit::Diamonds));
  PlayerHand val21PlayerHand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Diamonds));

  REQUIRE(val13PlayerHand.getValue() == 13);
  REQUIRE(val20PlayerHand.getValue() == 20);
  REQUIRE(val21PlayerHand.getValue() == 21);
}

TEST_CASE("(PlayerHand) getValue returns correct value for hard hands with ace") {
  PlayerHand val16PlayerHand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::Eight, Suit::Spades));
  val16PlayerHand.hit(Card(Rank::Seven, Suit::Spades));

  PlayerHand aceAcePlayerHand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::Ace, Suit::Diamonds));

  PlayerHand multipleAceVal18PlayerHand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::Four, Suit::Spades));
  multipleAceVal18PlayerHand.hit(Card(Rank::Ace, Suit::Diamonds));
  multipleAceVal18PlayerHand.hit(Card(Rank::Ace, Suit::Spades));
  multipleAceVal18PlayerHand.hit(Card(Rank::Ace, Suit::Hearts));
  

  REQUIRE(val16PlayerHand.getValue() == 16);
  REQUIRE(aceAcePlayerHand.getValue() == 12);
  REQUIRE(multipleAceVal18PlayerHand.getValue() == 18);
}

TEST_CASE("(PlayerHand) isBust returns true above 21") {
  PlayerHand val25PlayerHand(20, Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));
  val25PlayerHand.hit(Card(Rank::King, Suit::Spades));

  PlayerHand val22PlayerHand(20, Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));
  val22PlayerHand.hit(Card(Rank::Seven, Suit::Spades));

  REQUIRE(val25PlayerHand.getValue() == 25);
  REQUIRE(val25PlayerHand.isBust() == true);
  REQUIRE(val22PlayerHand.getValue() == 22);
  REQUIRE(val22PlayerHand.isBust() == true);
}

TEST_CASE("(PlayerHand) isBust returns false below or equal to 21") {
  PlayerHand val21PlayerHand(20, Card(Rank::Nine, Suit::Spades), Card(Rank::King, Suit::Clubs));
  val21PlayerHand.hit(Card(Rank::Two, Suit::Spades));

  PlayerHand val15PlayerHand(20, Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));

  REQUIRE(val21PlayerHand.getValue() == 21);
  REQUIRE(val21PlayerHand.isBust() == false);
  REQUIRE(val15PlayerHand.getValue() == 15);
  REQUIRE(val15PlayerHand.isBust() == false);
}

TEST_CASE("(PlayerHand) isBust returns false below or equal to 21 when soft") {
  PlayerHand hand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::Eight, Suit::Clubs));

  REQUIRE(hand.getValue() == 19);
  REQUIRE(hand.isBust() == false);
}

TEST_CASE("(PlayerHand) isBust returns true above 21 when soft") {
  PlayerHand hand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Clubs));
  hand.hit(Card(Rank::King, Suit::Diamonds));
  hand.hit(Card(Rank::Two, Suit::Clubs));

  REQUIRE(hand.getValue() == 23);
  REQUIRE(hand.isBust() == true);
}

TEST_CASE("(PlayerHand) isBlackjack returns true on ace and 10 value card") {
  PlayerHand aceKing(20, Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Clubs));
  PlayerHand aceTen(20, Card(Rank::Ace, Suit::Spades), Card(Rank::Ten, Suit::Clubs));

  REQUIRE(aceKing.isBlackjack() == true);
  REQUIRE(aceTen.isBlackjack() == true);
}

TEST_CASE("(PlayerHand) isBlackjack returns false on 2 cards that aren't blackjack") {
  PlayerHand fiveTen(20, Card(Rank::Five, Suit::Spades), Card(Rank::Ten, Suit::Clubs));
  PlayerHand NineAce(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Ace, Suit::Clubs));

  REQUIRE(fiveTen.isBlackjack() == false);
  REQUIRE(NineAce.isBlackjack() == false);
}

TEST_CASE("(PlayerHand) isBlackjack returns false on more cards that sum up to 21") {
  PlayerHand withoutAce21(20, Card(Rank::Five, Suit::Spades), Card(Rank::Ten, Suit::Clubs));
  withoutAce21.hit(Card(Rank::Six, Suit::Hearts));

  PlayerHand withAce21(20, Card(Rank::Five, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  withAce21.hit(Card(Rank::Five, Suit::Hearts));

  REQUIRE(withoutAce21.getValue() == 21);
  REQUIRE(withoutAce21.isBlackjack() == false);
  REQUIRE(withAce21.getValue() == 21);
  REQUIRE(withAce21.isBlackjack() == false);
}

TEST_CASE("(PlayerHand) isSoft returns true when there is ace to be softened") {
  PlayerHand nineAce(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  PlayerHand fourAce(20, Card(Rank::Four, Suit::Spades), Card(Rank::Ace, Suit::Clubs));

  REQUIRE(nineAce.isSoft() == true);
  REQUIRE(fourAce.isSoft() == true);
}

TEST_CASE("(PlayerHand) isSoft returns false with no ace") {
  PlayerHand fiveTen(20, Card(Rank::Five, Suit::Spades), Card(Rank::Ten, Suit::Clubs));
  PlayerHand val15PlayerHand(20, Card(Rank::Five, Suit::Spades), Card(Rank::King, Suit::Clubs));

  REQUIRE(fiveTen.isSoft() == false);
  REQUIRE(val15PlayerHand.isSoft() == false);
}

TEST_CASE("(PlayerHand) isSoft returns false with already softened ace") {
  PlayerHand h1(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  h1.hit(Card(Rank::Ten, Suit::Diamonds));
  
  PlayerHand h2(20, Card(Rank::Four, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  h2.hit(Card(Rank::Seven, Suit::Diamonds));

  PlayerHand h3(20, Card(Rank::Four, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  h3.hit(Card(Rank::Seven, Suit::Diamonds));
  h3.hit(Card(Rank::Ace, Suit::Clubs));
  
  REQUIRE(h1.isSoft() == false);
  REQUIRE(h2.isSoft() == false);
  REQUIRE(h3.isSoft() == false);
}

TEST_CASE("(PlayerHand) canDouble returns true when 2 cards in hand") {
  PlayerHand h1(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  PlayerHand h2(20, Card(Rank::Four, Suit::Spades), Card(Rank::Seven, Suit::Clubs));
  
  REQUIRE(h1.canDouble(40) == true);
  REQUIRE(h2.canDouble(20) == true);
}

TEST_CASE("(PlayerHand) canDouble returns false on blackjack") {
  PlayerHand h1(20, Card(Rank::King, Suit::Spades), Card(Rank::Ace, Suit::Clubs));

  REQUIRE(h1.canDouble(40) == false);
}

TEST_CASE("(PlayerHand) canDouble returns false when more/less than 2 cards in hand") {
  PlayerHand h1(20, Card(Rank::Nine, Suit::Spades));
  PlayerHand h2(20, Card(Rank::Four, Suit::Spades), Card(Rank::Seven, Suit::Clubs));
  h2.hit(Card(Rank::Seven, Suit::Diamonds));
  
  REQUIRE(h1.canDouble(40) == false);
  REQUIRE(h2.canDouble(40) == false);
}

TEST_CASE("(PlayerHand) canDouble returns false when insufficient balance") {
  PlayerHand hand(41, Card(Rank::Nine, Suit::Spades));

  REQUIRE(hand.canDouble(40) == false);
}

TEST_CASE("(PlayerHand) doubling doubles the bet when sufficient balance") {
  PlayerHand hand(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Ten, Suit::Diamonds));
  hand.double_(Card(Rank::Ten, Suit::Clubs), 40);

  REQUIRE(hand.getBet() == 40);
}

TEST_CASE("(PlayerHand) doubling throws when insufficient balance") {
  PlayerHand hand(41, Card(Rank::Nine, Suit::Spades));
  REQUIRE_THROWS(hand.double_(Card(Rank::Ten, Suit::Clubs), 40));
}

TEST_CASE("(PlayerHand) canSplit returns true when 2 cards of same rank in hand") {
  PlayerHand h1(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Nine, Suit::Clubs));
  PlayerHand h2(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  
  REQUIRE(h1.canSplit(20) == true);
  REQUIRE(h2.canSplit(20) == true);
}

TEST_CASE("(PlayerHand) canSplit returns false when 2 cards of different rank in hand") {
  PlayerHand h1(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Ten, Suit::Clubs));
  PlayerHand h2(20, Card(Rank::King, Suit::Spades), Card(Rank::Jack, Suit::Clubs));
  
  REQUIRE(h1.canSplit(20) == false);
  REQUIRE(h2.canSplit(20) == false);
}

TEST_CASE("(PlayerHand) canSplit returns false when 2 cards have same value but different rank") {
  PlayerHand h1(20, Card(Rank::King, Suit::Spades), Card(Rank::Queen, Suit::Clubs));
  PlayerHand h2(20, Card(Rank::Ten, Suit::Spades), Card(Rank::Jack, Suit::Clubs));

  REQUIRE(h1.canSplit(20) == false);
  REQUIRE(h2.canSplit(20) == false);
}

TEST_CASE("(PlayerHand) canSplit returns false when more/less then 2 cards of same rank in hand") {
  PlayerHand h1(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Nine, Suit::Clubs));
  h1.hit(Card(Rank::Nine, Suit::Clubs));
  PlayerHand h2(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  h2.hit(Card(Rank::King, Suit::Spades));
  
  REQUIRE(h1.canSplit(20) == false);
  REQUIRE(h2.canSplit(20) == false);
}

TEST_CASE("(PlayerHand) canSplit returns false when more/less then 2 cards of different rank in hand") {
  PlayerHand h1(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Nine, Suit::Clubs));
  h1.hit(Card(Rank::Ten, Suit::Clubs));
  PlayerHand h2(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  h2.hit(Card(Rank::Ten, Suit::Spades));
  
  REQUIRE(h1.canSplit(20) == false);
  REQUIRE(h2.canSplit(20) == false);
}

TEST_CASE("(PlayerHand) canSplit returns false on blackjack") {
  PlayerHand hand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Clubs));

  REQUIRE(hand.canSplit(20) == false);
}

TEST_CASE("(PlayerHand) canSplit returns false when insufficient balance") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  
  REQUIRE(hand.canSplit(21) == true);
}

TEST_CASE("(PlayerHand) canSplit returns true when balance is sufficient and false when insufficient") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  
  REQUIRE(hand.canSplit(20) == true);
  REQUIRE(hand.canSplit(19) == false);
}

TEST_CASE("(PlayerHand) split preserves correct bet on sufficient balance") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));

  PlayerHand splitHand = hand.split(20);

  REQUIRE(hand.getBet() == 20);
}

TEST_CASE("(PlayerHand) split creates hand with correct bet on sufficient balance") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));

  PlayerHand splitHand = hand.split(20);

  REQUIRE(splitHand.getBet() == 20);
}

TEST_CASE("(PlayerHand) split throws on insufficient balance") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));

  REQUIRE_THROWS(hand.split(19));
}

TEST_CASE("(PlayerHand) split creates correct PlayerHand with one card leaving current PlayerHand with the other one") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));

  PlayerHand splitHand = hand.split(20);
  auto leftInPlayerHand = hand.getCards();
  auto splitCards = splitHand.getCards();

  REQUIRE(leftInPlayerHand.size() == 1);
  REQUIRE(splitCards.size() == 1);
  REQUIRE(leftInPlayerHand[0].getRank() == Rank::King);
  REQUIRE(splitCards[0].getRank() == Rank::King);
  REQUIRE(leftInPlayerHand[0].getSuit() != splitCards[0].getSuit());
}

TEST_CASE("(PlayerHand) getSize correctly returns amount of cards after splitting") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));

  PlayerHand splitHand = hand.split(20);

  REQUIRE(hand.getSize() == 1);
  REQUIRE(splitHand.getSize() == 1);
}

TEST_CASE("(PlayerHand) isBlackjack returns false after splitting on both decks") {
  PlayerHand hand(20, Card(Rank::Ace, Suit::Spades), Card(Rank::Ace, Suit::Clubs));

  PlayerHand splitHand = hand.split(20);

  splitHand.hit(Card(Rank::Jack, Suit::Spades));
  splitHand.hit(Card(Rank::King, Suit::Clubs));

  REQUIRE(hand.isBlackjack() == false);
  REQUIRE(splitHand.isBlackjack() == false);
}

TEST_CASE("(PlayerHand) doubling blocks all actions (hitting, doubling, splitting)") {
  PlayerHand hand(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Ace, Suit::Clubs));
  hand.double_(Card(Rank::King, Suit::Clubs), 40);
  REQUIRE(hand.didPlayEnd() == true);


  REQUIRE(hand.getBet() == 40);
  REQUIRE(hand.getSize() == 3);
  REQUIRE(hand.canDouble(40) == false);
  REQUIRE(hand.canSplit(40) == false);
  REQUIRE_THROWS(hand.hit(Card(Rank::King, Suit::Spades)));
  REQUIRE_THROWS(hand.double_(Card(Rank::King, Suit::Spades), 20));
  REQUIRE_THROWS(hand.split(20));
}

TEST_CASE("canHit returns true before standing") {
  PlayerHand hand(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Seven, Suit::Clubs));

  REQUIRE(hand.canHit() == true);
}

TEST_CASE("standing disables all actions (doubling, splitting and hitting)") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  hand.stand();

  REQUIRE(hand.canHit() == false);
  REQUIRE(hand.canDouble(20) == false);
  REQUIRE(hand.canSplit(20) == false);
}

TEST_CASE("getAvailableActions returns split when splittable") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  auto actions = hand.getAvailableActions(20);

  bool containsSplit = false;
  for (const auto action : actions)
    containsSplit = containsSplit || action == HandActions::SPLIT;

  REQUIRE(containsSplit == true);
}

TEST_CASE("getAvailableActions doesn't return split when balance is insufficient") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::King, Suit::Clubs));
  auto actions = hand.getAvailableActions(19);

  bool containsSplit = false;
  for (const auto action : actions)
    containsSplit = containsSplit || action == HandActions::SPLIT;

  REQUIRE(containsSplit == false);
}

TEST_CASE("getAvailableActions returns double when can double") {
  PlayerHand hand(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Seven, Suit::Clubs));
  auto actions = hand.getAvailableActions(20);

  bool containsDouble = false;
  for (const auto action : actions)
    containsDouble = containsDouble || action == HandActions::DOUBLE;

  REQUIRE(containsDouble == true);
}

TEST_CASE("getAvailableActions doesn't return double when balance is insufficient") {
  PlayerHand hand(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Five, Suit::Clubs));
  auto actions = hand.getAvailableActions(19);

  bool containsDouble = false;
  for (const auto action : actions)
    containsDouble = containsDouble || action == HandActions::DOUBLE;

  REQUIRE(containsDouble == false);
}

TEST_CASE("getAvailableActions returns hit when can hit") {
  PlayerHand hand(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Seven, Suit::Clubs));
  auto actions = hand.getAvailableActions(0);

  bool containsHit = false;
  for (const auto action : actions)
    containsHit = containsHit || action == HandActions::HIT;

  REQUIRE(containsHit == true);
}

TEST_CASE("getAvailableActions doesn't return hit when bust") {
  PlayerHand hand(20, Card(Rank::King, Suit::Spades), Card(Rank::Queen, Suit::Clubs));
  hand.hit(Card(Rank::Two, Suit::Diamonds));
  auto actions = hand.getAvailableActions(0);

  bool containsHit = false;
  for (const auto action : actions)
    containsHit = containsHit || action == HandActions::HIT;

  REQUIRE(containsHit == false);
}

TEST_CASE("getAvailableActions doesn't return hit when stood") {
  PlayerHand hand(20, Card(Rank::Nine, Suit::Spades), Card(Rank::Seven, Suit::Clubs));
  hand.stand();
  auto actions = hand.getAvailableActions(0);

  bool containsHit = false;
  for (const auto action : actions)
    containsHit = containsHit || action == HandActions::HIT;

  REQUIRE(containsHit == false);
}

TEST_CASE("getAvailableActions always returns stand") {
  PlayerHand hand(20, Card(Rank::Nine, Suit::Spades));
  auto actions = hand.getAvailableActions(0);

  bool containsStand = false;
  for (const auto action : actions)
    containsStand = containsStand || action == HandActions::STAND;

  REQUIRE(containsStand == true);
}

