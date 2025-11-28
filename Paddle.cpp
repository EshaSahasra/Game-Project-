#include "Paddle.h"

// Returns the paddle's collision rectangle.
// The rectangle is centered on (X, y), so we subtract half the width/height.
Rectangle Paddle::GetRect() {
    return Rectangle{ X - width/2, y - height/2, width, height };
}

// Draws the paddle using its current rectangle and color.
void Paddle::Draw() {
    DrawRectangleRec(GetRect(), color);
}

// Moves the paddle upward based on its speed.
// Multiply by GetFrameTime to keep the movement frame-rate independent.
void Paddle::MoveUp() {
    y -= speed * GetFrameTime();
}

// Moves the paddle downward.
// Same frame-rate independent movement as MoveUp.
void Paddle::MoveDown() {
    y += speed * GetFrameTime();
}

// Resets the paddle's vertical position to the middle of the screen.
void Paddle::Reset(int screenHeight) {
    y = screenHeight / 2.0f;
}
