#include "fabrik.h"
#include <iostream>

namespace ik {
  FabrikIK::FabrikIK(float2 origin, int joints, float length): origin(origin), length(length) {
    float jointLength = length / joints;
    float2 startDir = float2{ 1, 0 };
    for (int i = 0; i < joints; i++) {
      this->joints.push_back(Joint{ origin + startDir * i * jointLength, startDir, jointLength });
    }
  }

  const std::vector<Joint>& FabrikIK::getJoints() const {
    return this->joints;
  }

  template<class iterator_type>
  void fabrikPass(iterator_type begin, int joints, float2 target) {
    for (int i = 0; i < joints; i++) {
      auto joint = begin + i;
      
      float2 newDir = joint->base - target;
      // If the current base is very close to the target, use the existing direction
      // to avoid NaNs.
      if (linalg::length2(newDir) > 0.01f) {
        newDir = linalg::normalize(newDir);
      } else {
        newDir = -joint->direction;
      }
      joint->direction = newDir;
      joint->base = target;

      target += newDir * joint->length;
    }
  }

  void FabrikIK::updateJoints(float2 target) {
    float2 originToTarget = target - this->origin;
    // If target is out of range, use the closest target within range.
    if (linalg::length(originToTarget) > length) {
      target = this->origin + linalg::normalize(originToTarget) * this->length;
    }

    for (int i = 0; i < 10; i++) {
      fabrikPass(this->joints.begin(), this->joints.size(), target);
      fabrikPass(this->joints.rbegin(), this->joints.size(), this->origin);
    }
  }
} 