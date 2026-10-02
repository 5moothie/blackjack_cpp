#pragma once
#include <raylib.h>

/*
Helper functions for util UI. 
Might be better done with struct, but I want to explore namespaces and it seems like unawful idea here.
*/

// note that scaling over and over again might accumulate error
// note that scaling some renderSizes (x or y = 0) might throw dividision by zero
// Just noting for future

namespace RenderMath {
  void scaleToWidth(Vector2& renderSize, const int desiredWidth);
  void scaleToHeight(Vector2& renderSize, const int desiredHeight);

  void setWidth(Vector2& renderSize, const int desiredWidth);
  void setHeight(Vector2& renderSize, const int desiredHeight);

  void scaleToContainTexture(Vector2& renderSize, const int desiredWidth, const int desiredHeight);
  void scaleToOverflowTexture(Vector2& renderSize, const int desiredWidth, const int desiredHeight);

  void scale(Vector2& renderSize, const float k);


  void setPositionByMiddle(Vector2& positionToChange, const Vector2 renderSize, const Vector2 desiredPosition);
}