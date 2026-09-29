#pragma once



class Display {
public:
  virtual ~Display() = default;

  virtual void update() = 0;
  virtual void draw() const = 0;
};