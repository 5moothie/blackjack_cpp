#pragma once

enum class ProgramScreen {
  MAIN_MENU,
  BLACKJACK_GAME,
};


class ScreenManager {
private:
  ProgramScreen screen{ProgramScreen::MAIN_MENU};
  bool exitRequested{false};

public:
  void setScreen(ProgramScreen screen) noexcept { this->screen = screen; }
  [[nodiscard]] ProgramScreen getScreen() const noexcept { return screen; }

  void requestClose() noexcept { exitRequested = true; }
  [[nodiscard]] bool shouldWindowClose() const noexcept { return exitRequested; };
};

