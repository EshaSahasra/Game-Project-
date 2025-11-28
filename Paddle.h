#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>

// Represents a single paddle in the Pong game.
// Each paddle can move vertically and has its own size,
// position, color, and movement speed.
struct Paddle {
    float X, y;        // Paddle's center position (X is fixed, Y moves up/down)
    float speed;       // Movement speed in pixels per second
    float width, height; 
    Color color;       // Paddle color when drawn

    // Returns the paddle's bounding box as a Rectangle.
    // This is used for drawing and collision detection.
    Rectangle GetRect();

    // Draws the paddle on the screen using its current properties.
    void Draw();

    // Moves the paddle upward based on its speed.
    void MoveUp();

    // Moves the paddle downward based on its speed.
    void MoveDown();

    // Resets the paddle to the vertical center of the screen.
    void Reset(int screenHeight);
};

#endif
