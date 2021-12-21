#include <iostream>
#include <string>
#include "raylib.h"
#include "inversekinematics.h"

using namespace ik;

void drawJoint(const ik::Joint& joint, int num) {
  Vector2 start = Vector2{joint.base.x, joint.base.y};
  Vector2 end = Vector2{joint.base.x + joint.direction.x * joint.length, joint.base.y + joint.direction.y * joint.length};
  DrawLineV(start, end, BLACK);
  DrawCircleV(start, 2, RED);
  DrawCircleV(end, 2, RED);
  // DrawText(std::to_string(num).c_str(), start.x, start.y, 15, GREEN);
}

int main() {
  const int screenSize = 800;
  FabrikIK fabrikIk{float2{screenSize / 2, screenSize / 2}, 25, 250};
  
  InitWindow(screenSize, screenSize, "Inverse Kinematics");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    // Update
    fabrikIk.updateJoints(float2{GetMouseX(), GetMouseY()});
    
    // Draw
    BeginDrawing();
    ClearBackground(WHITE);
    
    DrawCircleV(GetMousePosition(), 2, BLUE);
    int temp = 0;
    for (const ik::Joint& joint : fabrikIk.getJoints()) {
      drawJoint(joint, ++temp);
    }

    EndDrawing();
  }

  return 0;
}