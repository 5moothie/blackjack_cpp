cmake_minimum_required(VERSION 3.20)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.15.0
)

add_library(blackjack_lib
  src/card/card.cpp
  src/blackjack/hand.cpp
  src/card/deck.cpp
  src/blackjack/shoe.cpp
  src/blackjack/dealer.cpp
  src/blackjack/player.cpp
  src/blackjack/game.cpp
  src/IO/consoleDisplay.cpp
  src/IO/consoleInputTaker.cpp
)

target_include_directories(
  blackjack_lib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(
  blackjack
  src/main.cpp
)

target_link_libraries(
  blackjack
  PRIVATE
  blackjack_lib
)

FetchContent_MakeAvailable(Catch2)

add_executable(
  blackjack_tests
  tests/hand_test.cpp
)

target_link_libraries(
  blackjack_tests
  PRIVATE
  blackjack_lib
  Catch2::Catch2WithMain
)

enable_testing()

add_test(
  NAME all_tests
  COMMAND blackjack_tests
)

# find_package(raylib CONFIG REQUIRED)
# target_link_libraries(blackjack PRIVATE raylib)