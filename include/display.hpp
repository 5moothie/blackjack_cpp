#pragma once



class Display {
protected:

public:
  virtual ~Display() = default;

  virtual void update() = 0;
  virtual void draw() = 0;
};