#include "Ball.h"

// Yellow color is defined in another file, so it is imported here.
extern Color Yellow;

// Draws the ball as a circle using its current position and radius.
void Ball::Draw() {
    DrawCircle((int)x, (int)y, radius, Yellow);
}

// Updates the ball's position based on its current speed.
// GetFrameTime() ensures movement is smooth and frame-rate independent.
void Ball::Update() {
    x += speedX * GetFrameTime();
    y += speedY * GetFrameTime();
}

// Resets the ball to the center of the screen.
// Also restores the ball's speed values to their initial state.
void Ball::Reset(int screenWidth, int screenHeight) {
    x = screenWidth / 2.0f;
    y = screenHeight / 2.0f;
    speedX = 300;
    speedY = 300;
}

// Handles bouncing off the top and bottom edges of the screen.
// When the ball hits a horizontal boundary, reverse its vertical speed.
void Ball::BounceVertical(int screenHeight) {
    if (y - radius < 0) {          // Hit top boundary
        y = radius;               // Correct position
        speedY *= -1;             // Reverse vertical direction
    }
    if (y + radius > screenHeight) {  // Hit bottom boundary
        y = screenHeight - radius;    // Correct position
        speedY *= -1;                 // Reverse vertical direction
    }
}
