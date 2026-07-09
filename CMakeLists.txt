cmake_minimum_required(VERSION 3.20)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(blackjack
  include/card/card.hpp
  include/card/suit.hpp
  include/card/rank.hpp
  include/blackjack/components/hand.hpp
  include/card/deck.hpp
  include/blackjack/components/shoe.hpp
  include/blackjack/components/dealer.hpp
  include/blackjack/components/player.hpp
  include/blackjack/game.hpp
  include/blackjack/IO/actions.hpp
  include/blackjack/IO/gameDisplay.hpp
  include/blackjack/IO/inputTaker.hpp
  include/blackjack/IO/consoleDisplay.hpp
  include/blackjack/IO/consoleInputTaker.hpp

  src/main.cpp
  src/card/card.cpp
  src/blackjack/components/hand.cpp
  src/card/deck.cpp
  src/blackjack/components/shoe.cpp
  src/blackjack/components/dealer.cpp
  src/blackjack/components/player.cpp
  src/blackjack/game.cpp
  src/blackjack/IO/consoleDisplay.cpp
  src/blackjack/IO/consoleInputTaker.cpp
)

target_include_directories(blackjack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
