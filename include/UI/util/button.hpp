#pragma once
#include<raylib.h>

class Button {
private:
  Texture2D texture;
  Vector2 position;
  const int startingWidth;
  const int startingHeight;

public:
  Button(const char* imagePath, Vector2 imagePosition);
  Button(const char* imagePath);
  ~Button();

  // no copying or moving
  Button(const Button&) = delete;
  Button& operator=(const Button&) = delete;
  Button(Button&&) noexcept = default;
  // Button& operator=(Button&&) noexcept = default;

  void draw() const;
  [[nodiscard]] bool isPressed(Vector2 mousePos, bool mousePressed) const;

  void setX(const float x) noexcept;
  void setY(const float y) noexcept;
  [[nodiscard]] float getX() const noexcept;
  [[nodiscard]] float getY() const noexcept;


  void setWidth(const int width);
  void setHeight(const int height);
  [[nodiscard]] int getWidth() const;
  [[nodiscard]] int getHeight() const;

  void scaleBySettingWidth(const int width);
  void scaleBySettingHeight(const int height);
  void scale(const float k);
  
  void restoreOriginalDimensions();
  void setPositionByMiddle(Vector2 position);
};