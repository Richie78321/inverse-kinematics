#pragma once

#include <vector>
#include "joint.h"

namespace ik {
  class FabrikIK {
  public:
    FabrikIK(float2 origin, int joints, float length);
    void updateJoints(float2 target);

    const std::vector<Joint>& getJoints() const;
  private:
    float length;
    float2 origin;
    std::vector<Joint> joints;
  };
}