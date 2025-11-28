#ifndef BALL_H
#define BALL_H

#include <raylib.h>

// Represents the ball used in the Pong game.
// The ball moves every frame, bounces off walls and paddles,
// and can be reset to the center after a point is scored.
struct Ball {
    float x;           // Current X position of the ball
    float y;           // Current Y position of the ball
    float radius;      // Radius of the ball

    float speedX;      // Horizontal movement speed
    float speedY;      // Vertical movement speed

    // Draws the ball on the screen at its current position
    void Draw();

    // Updates the ball's position based on its speed
    void Update();

    // Resets the ball to the center of the screen
    // and gives it its initial movement speed
    void Reset(int screenWidth, int screenHeight);

    // Handles bouncing off the top and bottom edges of the screen
    void BounceVertical(int screenHeight);
};

#endif
