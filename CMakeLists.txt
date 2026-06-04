cmake_minimum_required(VERSION 3.20)
project(Blackjack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(blackjack
  include/card/card.hpp
  include/card/suit.hpp
  include/card/rank.hpp
  include/blackjack/hand.hpp
  include/card/deck.hpp
  include/blackjack/shoe.hpp
  include/blackjack/dealer.hpp

  src/main.cpp
  src/card/card.cpp
  src/blackjack/hand.cpp
  src/card/deck.cpp
  src/blackjack/shoe.cpp
  src/blackjack/dealer.cpp
)

target_include_directories(blackjack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# find_package(raylib CONFIG REQUIRED)
# target_link_libraries(blackjack PRIVATE raylib)