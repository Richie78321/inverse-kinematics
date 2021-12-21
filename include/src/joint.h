#pragma once

#include <linalg.h>

using linalg::aliases::float2;

namespace ik {
  struct Joint {
    float2 base;
    float2 direction;
    float length;
  };
}