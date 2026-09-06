#include <catch2/catch_test_macros.hpp>

#include "blackjack/components/player.hpp"
#include "card/rank.hpp"
#include "card/suit.hpp"
#include "../../mocks/testShoe.hpp"

#include <stdexcept>

TEST_CASE("after initialization handsLeftToPlay() = 0") { 
  REQUIRE(Player(100).handsLeftToPlay() == 0); 
}

TEST_CASE("after initialization getBalance returns the constructor balance") { 
  REQUIRE(Player(123).getBalance() == 123); 
}

TEST_CASE("after initialization getAllHands returns an empty collection") { 
  REQUIRE(Player(100).getAllHands().empty()); 
}

TEST_CASE("initialization with zero balance succeeds") { 
  REQUIRE_NOTHROW(Player(0)); 
}

TEST_CASE("initialization with negative balance throws") { 
  REQUIRE_THROWS_AS(Player(-1), std::invalid_argument); 
}

TEST_CASE("getActiveHandConst throws when called with no activeHand") { 
  REQUIRE_THROWS(Player(100).getActiveHandConst()); 
}

TEST_CASE("activateNextHand activates next hand with 3 hands") {
  TestShoe testShoe; testShoe.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::Four, Suit::Spades), Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Seven, Suit::Spades)});
  Player player(100); player.addHand(10, testShoe); player.addHand(10, testShoe); player.addHand(10, testShoe);
  player.activateNextHand();
  REQUIRE(player.handsLeftToPlay() == 2); 
  REQUIRE(player.getActiveHandConst().getBet() == 10);
  
  player.activateNextHand();
  REQUIRE(player.handsLeftToPlay() == 1); 
  REQUIRE(player.getActiveHandConst().getBet() == 10);
}

TEST_CASE("activateNextHand does nothing when no remaining hands (handsLeftToPlay doesn't underflow)") {
  Player player(100); 
  player.activateNextHand(); 

  REQUIRE(player.handsLeftToPlay() == 0); 

  player.activateNextHand(); 
  REQUIRE(player.handsLeftToPlay() == 0);
}

TEST_CASE("after initialization hasActiveHand returns false") {
  REQUIRE_FALSE(Player(100).hasActiveHand());
}

TEST_CASE("hasActiveHand returns true when a active hand exists") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)}); 
  Player p(100); 

  p.addHand(20, s); 

  REQUIRE(p.hasActiveHand());
}

TEST_CASE("hasActiveHand returns false when all hands finished") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)}); 
  Player p(100); 

  p.addHand(20, s); 
  p.standActiveHand(); 

  REQUIRE_FALSE(p.hasActiveHand());
}

TEST_CASE("hasActiveHand returns true when hands cleared and added") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::King, Suit::Spades), Card(Rank::Seven, Suit::Spades)}); 
  Player p(100); 

  p.addHand(20, s); 
  p.standActiveHand(); 
  p.clearHands();
  p.addHand(20, s);
  
  REQUIRE(p.hasActiveHand());
}

TEST_CASE("handsLeftToPlay correctly returns amount of hands remaining for play (including active)") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::Four, Suit::Spades), Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Seven, Suit::Spades)}); 
  Player p(100);

  p.addHand(10, s); 
  p.addHand(20, s);
  p.addHand(30, s); 
  
  REQUIRE(p.handsLeftToPlay() == 3);

  p.activateNextHand();
  
  REQUIRE(p.handsLeftToPlay() == 2);
}

TEST_CASE("canDoubleActiveHand returns true when hand is 2 cards and wasn't split before") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades)});
  Player p(40);

  p.addHand(20, s);

  REQUIRE(p.canDoubleActiveHand());
}

TEST_CASE("canDoubleActiveHand returns false after splitting") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::Eight, Suit::Spades), Card(Rank::Eight, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.splitActiveHand(s);

  REQUIRE_FALSE(p.canDoubleActiveHand());
}

TEST_CASE("canDoubleActiveHand returns false after hitting") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.hitActiveHand(s);

  REQUIRE_FALSE(p.canDoubleActiveHand());
}

TEST_CASE("canDoubleActiveHand returns false when the supplied balance is insufficient") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades)});
  Player p(30);

  p.addHand(20, s);

  REQUIRE_FALSE(p.canDoubleActiveHand());
}

TEST_CASE("canSplitActiveHand returns true when hand has 2 of the value cards") {
  TestShoe s; s.setShoe({Card(Rank::Nine, Suit::Spades), Card(Rank::Nine, Suit::Spades)});
  Player p(40);

  p.addHand(20, s);
  
  REQUIRE(p.canSplitActiveHand());
}

TEST_CASE("canSplitActiveHand returns false after hitting") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Five, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(100);
  
  p.addHand(20, s);
  p.hitActiveHand(s);
  
  REQUIRE_FALSE(p.canSplitActiveHand());
}

TEST_CASE("canSplitActiveHand returns false when hand consists of 2 different value cards") {
  TestShoe s; s.setShoe({Card(Rank::King, Suit::Spades), Card(Rank::Queen, Suit::Spades)});
  Player p(100);
  
  p.addHand(20, s);
  
  REQUIRE_FALSE(p.canSplitActiveHand());
}

TEST_CASE("canSplitActiveHand returns false when the supplied balance is insufficient") {
  TestShoe s; s.setShoe({Card(Rank::Nine, Suit::Spades), Card(Rank::Nine, Suit::Spades)});
  Player p(30);
  
  p.addHand(20, s);
  
  REQUIRE_FALSE(p.canSplitActiveHand());
}

TEST_CASE("hitActiveHand adds card to the hand") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.hitActiveHand(s);

  REQUIRE(p.getActiveHandConst().getSize() == 3);
}

TEST_CASE("hitActiveHand activates next hand if it busts after hitting") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Ten, Suit::Spades), Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.addHand(20, s);
  p.hitActiveHand(s);

  REQUIRE(p.getActiveHandConst().getBet() == 20);
}

TEST_CASE("hitActiveHand activates next hand if hand value goes to 21") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Four, Suit::Spades), Card(Rank::Nine, Suit::Spades), Card(Rank::Ten, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.addHand(20, s);
  p.hitActiveHand(s);

  REQUIRE(p.getActiveHandConst().getValue() == 10);
}

TEST_CASE("hitActiveHand leaves the hand active when its value remains below 21") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.hitActiveHand(s);

  REQUIRE(p.hasActiveHand());
  REQUIRE(p.getActiveHandConst().getValue() == 13);
}

TEST_CASE("during hitActiveHand Shoe cards are consumed correctly") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.hitActiveHand(s);

  REQUIRE(s.getCards().empty());
}

TEST_CASE("doubleActiveHand adds one card to hand if hand can be doubled") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(40);

  p.addHand(20, s);
  p.doubleActiveHand(s);

  REQUIRE(p.getAllHands()[0].getSize() == 3);
}

TEST_CASE("doubleActiveHand throws when hand cannot be doubled and leaves the state unchanged") {
  TestShoe s; s.setShoe({Card(Rank::King, Suit::Spades), Card(Rank::Ace, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);

  REQUIRE_THROWS(p.doubleActiveHand(s));
  REQUIRE(p.getAllHands()[0].getSize() == 2);
}

TEST_CASE("doubleActiveHand throws when the balance is insufficient and leaves the state unchanged") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades)});
  Player p(30);

  p.addHand(20, s);

  REQUIRE_THROWS(p.doubleActiveHand(s));
  REQUIRE(p.getBalance() == 10);
  REQUIRE(p.getAllHands()[0].getSize() == 2);
}

TEST_CASE("doubleActiveHand actiavtes next hand") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::Four, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.addHand(20, s);
  p.doubleActiveHand(s);

  REQUIRE(p.handsLeftToPlay() == 1);
}

TEST_CASE("doubleActiveHand doubles the bet on the hand") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(40);

  p.addHand(20, s);
  p.doubleActiveHand(s);

  REQUIRE(p.getAllHands()[0].getBet() == 40);
}

TEST_CASE("doubleActiveHand decreases the balance by original bet") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.doubleActiveHand(s);

  REQUIRE(p.getBalance() == 60);
}

TEST_CASE("standActiveHand leaves hand and balance unchanged") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();

  REQUIRE(p.getAllHands()[0].getSize() == 2);
  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("standActiveHand activates next hand") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades), Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.addHand(20, s);
  p.standActiveHand();

  REQUIRE(p.hasActiveHand());
  REQUIRE(p.handsLeftToPlay() == 1);
}

TEST_CASE("splitActiveHand splits cards and draws one card for each of them") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::Eight, Suit::Spades), Card(Rank::Eight, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.splitActiveHand(s);

  REQUIRE(p.getAllHands().size() == 2);
  REQUIRE(p.getAllHands()[0].getSize() == 2);
  REQUIRE(p.getAllHands()[1].getSize() == 2);
}

TEST_CASE("after splitActiveHand active hand remains on the original hand") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::Eight, Suit::Spades), Card(Rank::Eight, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.splitActiveHand(s);

  REQUIRE(p.handsLeftToPlay() == 2);
}

TEST_CASE("splitActiveHand throws when hand is not splittable and leaves the state unchanged") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);

  REQUIRE_THROWS(p.splitActiveHand(s));
  REQUIRE(p.getAllHands().size() == 1);
  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("splitActiveHand decreases balance by original bet") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::Eight, Suit::Spades), Card(Rank::Eight, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.splitActiveHand(s);

  REQUIRE(p.getBalance() == 60);
}

TEST_CASE("both hands cannot be treated as blackjack after a splitActiveHand") {
  TestShoe s; s.setShoe({Card(Rank::Ace, Suit::Spades), Card(Rank::Ace, Suit::Spades), Card(Rank::Ten, Suit::Spades), Card(Rank::Ten, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.splitActiveHand(s);

  REQUIRE_FALSE(p.getAllHands()[0].isBlackjack());
  REQUIRE_FALSE(p.getAllHands()[1].isBlackjack());
}

TEST_CASE("settleHands throws when there are still active hands") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Six, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);

  REQUIRE_THROWS(p.settleHands(Hand(Card(Rank::Ten, Suit::Spades), Card(Rank::Nine, Suit::Spades))));
}

TEST_CASE("settleHands leaves balance unchanged when a regular player hand loses") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Five, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();
  p.settleHands(Hand(Card(Rank::King, Suit::Spades), Card(Rank::Nine, Suit::Spades)));

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("settleHands returns the bet when a regular player hand ties the dealer") {
  TestShoe s; s.setShoe({Card(Rank::Five, Suit::Spades), Card(Rank::Five, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();
  p.settleHands(Hand(Card(Rank::Seven, Suit::Spades), Card(Rank::Three, Suit::Spades)));

  REQUIRE(p.getBalance() == 100);
}

TEST_CASE("settleHands leaves a busted player hand's bet lost") {
  TestShoe s; s.setShoe({Card(Rank::King, Suit::Spades), Card(Rank::Queen, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.hitActiveHand(s);
  p.settleHands(Hand(Card(Rank::Seven, Suit::Spades), Card(Rank::Three, Suit::Spades)));

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("settleHands pays even money when a regular player hand beats the dealer") {
  TestShoe s; s.setShoe({Card(Rank::Ten, Suit::Spades), Card(Rank::Six, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();
  p.settleHands(Hand(Card(Rank::Ten, Suit::Spades), Card(Rank::Five, Suit::Spades)));

  REQUIRE(p.getBalance() == 120);
}

TEST_CASE("settleHands keeps the wager when the dealer beats a regular player hand") {
  TestShoe s; s.setShoe({Card(Rank::Ten, Suit::Spades), Card(Rank::Five, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();
  p.settleHands(Hand(Card(Rank::Ten, Suit::Spades), Card(Rank::Six, Suit::Spades)));

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("settleHands pays 3:2 plus the original wager when the player has blackjack and the dealer does not") {
  TestShoe s; s.setShoe({Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();
  p.settleHands(Hand(Card(Rank::Ten, Suit::Spades), Card(Rank::Nine, Suit::Spades)));

  REQUIRE(p.getBalance() == 130);
}

TEST_CASE("settleHands returns the original wager when both the player and dealer have blackjack") {
  TestShoe s; s.setShoe({Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();
  p.settleHands(Hand(Card(Rank::Ace, Suit::Spades), Card(Rank::King, Suit::Spades)));

  REQUIRE(p.getBalance() == 100);
}

TEST_CASE("settleHands keeps both wagers lost when both the player and dealer bust") {
  TestShoe s; s.setShoe({Card(Rank::King, Suit::Spades), Card(Rank::Queen, Suit::Spades), Card(Rank::Two, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.hitActiveHand(s);
  p.settleHands(Hand(Card(Rank::King, Suit::Spades), Card(Rank::Queen, Suit::Spades)));

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("clearHands removes all hands") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();
  p.clearHands();

  REQUIRE(p.getAllHands().empty());
}

TEST_CASE("clearHands throws if there is an active hand") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);

  REQUIRE_THROWS(p.clearHands());
}

TEST_CASE("clearHands preserves balance") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();
  p.clearHands();

  REQUIRE(p.getBalance() == 80);
}

TEST_CASE("after clearHands the player can add a new hand") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::Four, Suit::Spades), Card(Rank::Five, Suit::Spades)});
  Player p(100);

  p.addHand(20, s);
  p.standActiveHand();
  p.clearHands();

  REQUIRE_NOTHROW(p.addHand(20, s));
  REQUIRE(p.hasActiveHand());
}

TEST_CASE("addHand adds hand to the end") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades), Card(Rank::Four, Suit::Spades), Card(Rank::Five, Suit::Spades)});
  Player p(100);

  p.addHand(10, s);
  p.addHand(20, s);

  REQUIRE(p.getAllHands().back().getBet() == 20);
}

TEST_CASE("addHand when insufficient balance throws and leaves state unchanged") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)});
  Player p(10);

  REQUIRE_THROWS(p.addHand(20, s));
  REQUIRE(p.getAllHands().empty());
  REQUIRE(p.getBalance() == 10);
}

TEST_CASE("addHand adds hand if the bet is exact available balance") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)});
  Player p(20);

  REQUIRE_NOTHROW(p.addHand(20, s));
  REQUIRE(p.getBalance() == 0);
}

TEST_CASE("addHand throws on non-positive bet") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)});
  Player p(100);

  REQUIRE_THROWS(p.addHand(0, s));
  REQUIRE_THROWS(p.addHand(-2, s));
}

TEST_CASE("addHand throws on odd bet") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades), Card(Rank::Three, Suit::Spades)});
  Player p(100);

  REQUIRE_THROWS(p.addHand(21, s));
}

TEST_CASE("addHand when the shoe runs out of cards leaves balance and hands unchanged") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades)});
  Player p(100);

  REQUIRE_THROWS(p.addHand(20, s));
  REQUIRE(p.getAllHands().empty());
  REQUIRE(p.getBalance() == 100);
}

TEST_CASE("getActiveHandConst throws when there is no active hand") {
  REQUIRE_THROWS(Player(100).getActiveHandConst());
}

TEST_CASE("canDoubleActiveHand throws when there is no active hand") {
  REQUIRE_THROWS(Player(100).canDoubleActiveHand());
}

TEST_CASE("canSplitActiveHand throws when there is no active hand") {
  REQUIRE_THROWS(Player(100).canSplitActiveHand());
}

TEST_CASE("hitActiveHand throws when there is no active hand") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades)});
  Player p(100);

  REQUIRE_THROWS(p.hitActiveHand(s));
}

TEST_CASE("doubleActiveHand throws when there is no active hand") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades)});
  Player p(100);

  REQUIRE_THROWS(p.doubleActiveHand(s));
}

TEST_CASE("standActiveHand throws when there is no active hand") {
  REQUIRE_THROWS(Player(100).standActiveHand());
}

TEST_CASE("splitActiveHand throws when there is no active hand") {
  TestShoe s; s.setShoe({Card(Rank::Two, Suit::Spades)});
  Player p(100);
  
  REQUIRE_THROWS(p.splitActiveHand(s));
}
