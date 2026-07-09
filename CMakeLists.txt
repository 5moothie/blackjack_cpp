cmake_minimum_required(VERSION 3.20)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ================= blackjack lib ======================

add_library(blackjack_lib
  src/card/card.cpp
  src/card/deck.cpp
  src/blackjack/components/hand.cpp
  src/blackjack/components/shoe.cpp
  src/blackjack/components/dealer.cpp
  src/blackjack/components/player.cpp
  src/blackjack/game.cpp
  src/blackjack/IO/consoleDisplay.cpp
  src/blackjack/IO/consoleInputTaker.cpp
)

target_include_directories(blackjack_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ================ main ==============
add_executable(blackjack
  src/main.cpp
)

target_link_libraries(blackjack PRIVATE blackjack_lib)

# ============== tests ================ 

enable_testing()

find_package(Catch2 3 REQUIRED)

add_executable(blackjack_tests
  tests/card/card_test.cpp
  # tests/card/deck_test.cpp
  # tests/card/shoe_test.cpp
)

target_link_libraries(blackjack_tests 
  PRIVATE 
  blackjack_lib 
  Catch2::Catch2WithMain 
)

target_include_directories(blackjack_tests PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(CTest)
include(Catch)
catch_discover_tests(blackjack_tests)
