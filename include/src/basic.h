#pragma once

#include <vector>
#include "joint.h"

namespace ik {
  class BasicIK {
  public:
    BasicIK(float2 origin, int joints, float length);
    void updateJoints(float2 target);

    const std::vector<Joint>& getJoints() const;
  private:
    std::vector<Joint> joints;
    bool anchored;
  };
}