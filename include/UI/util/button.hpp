#pragma once
#include<raylib.h>

class Button {
private:
  Texture2D texture;
  Vector2 position;
  Vector2 renderSize;

public:
  Button(const char* imagePath, Vector2 imagePosition);
  Button(const char* imagePath);
  ~Button();

  // no copying or moving
  Button(const Button&) = delete;
  Button& operator=(const Button&) = delete;
  Button(Button&&) noexcept = delete;
  Button& operator=(Button&&) noexcept = delete;

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

  void scaleToWidth(const int width);
  void scaleToHeight(const int height);
  void scale(const float k);

  void scaleToContainTexture(const int width, const int height);
  void scaleToOverflowTexture(const int width, const int height);
  
  void restoreOriginalDimensions();
  void setPositionByMiddle(Vector2 position);
};