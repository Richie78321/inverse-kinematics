#include "basic.h"

namespace ik {
  BasicIK::BasicIK(float2 origin, int joints, float length) {
    float jointLength = length / joints;
    float2 startDir = float2{ 1, 0 };
    for (int i = 0; i < joints; i++) {
      this->joints.push_back(Joint{ origin + startDir * i * jointLength, startDir, jointLength });
    }
  }

  const std::vector<Joint>& BasicIK::getJoints() const {
    return this->joints;
  }

  void BasicIK::updateJoints(float2 target) {
    for (int i = this->joints.size() - 1; i >= 0; i--) {
      Joint& joint = this->joints.at(i);
      float2 newDir = target - joint.base;

      // If target is very close to base, avoid NaNs by using the previous direction
      if (linalg::length2(newDir) > 0.01f) {
        joint.direction = linalg::normalize(newDir);
      }

      joint.base = target - joint.direction * joint.length;
      target = joint.base;
    }
  }
}