#include <iostream>
#include <raylib.h>
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"
using namespace std;

// Color palette used throughout the game
Color Green       = Color{38, 185, 154, 225};
Color Dark_Green  = Color{20, 160, 133, 225};
Color Light_Green = Color{129, 204, 184, 225};
Color Yellow      = Color{243, 213, 91, 225};
Color Blackish    = Color{10, 20, 20, 225};

// with this we can Control the instruction whether to be shown or not, we give true so it'll shows at the start
bool showInstructions = true;


// Displaying the game instructions before the match begins
void ShowInstructionsScreen() {
    BeginDrawing();
    ClearBackground(BLACK);

    const char* title = "Welcome to Pong Game";
    int wTitle = MeasureText(title, 40);
    DrawText(title, GetScreenWidth()/2 - wTitle/2, 60, 40, Yellow);
    DrawText("It is a 2 player Game", 210, 100, 30, Yellow);

    DrawText("Player 1 (Left side)", 250, 150, 25, WHITE);
    DrawText(" press W - to move up", 280, 190, 20, WHITE);
    DrawText(" press S - to move Down", 280, 220, 20, WHITE);

    DrawText("Player 2 (Right side)", 240, 280, 25, WHITE);
    DrawText(" press UP Arrow- to move up", 270, 320, 20, WHITE);
    DrawText(" press Down Arrow - to move Down", 270, 350, 20, WHITE);

    DrawText("If you miss the ball, the opponent scores.", 150, 420, 20, YELLOW);
    DrawText("First to reach 10 points wins the match!", 180, 450, 20, YELLOW);

    const char* startMsg = "Press SPACE to start the game";
    int wStart = MeasureText(startMsg, 30);
    DrawText(startMsg, GetScreenWidth()/2 - wStart/2, 520, 30, WHITE);

    EndDrawing();

    // Continue to the main game once the user presses space
    if (IsKeyPressed(KEY_SPACE)) {
        showInstructions = false;
    }
}


int main() {
    InitWindow(800, 600, "Pong Game");
    SetWindowState(FLAG_VSYNC_HINT);   // Sync game to monitor refresh rate

    // Create and initialize the ball
    Ball ball;
    ball.x = GetScreenWidth() / 2.0f;
    ball.y = GetScreenHeight() / 2.0f;
    ball.radius = 10;
    ball.speedX = 300;
    ball.speedY = 300;

    // Left paddle (Player 1)
    Paddle leftPaddle;
    leftPaddle.X = 50;
    leftPaddle.y = GetScreenHeight() / 2;
    leftPaddle.width = 10;
    leftPaddle.height = 100;
    leftPaddle.speed = 450;
    leftPaddle.color = WHITE;

    // Right paddle (Player 2)
    Paddle rightPaddle;
    rightPaddle.X = GetScreenWidth() - 50;
    rightPaddle.y = GetScreenHeight() / 2;
    rightPaddle.width = 10;
    rightPaddle.height = 100;
    rightPaddle.speed = 450;
    rightPaddle.color = WHITE;

    // Score system, who ever reaches 10 points first wins the match
    Score score(10);

    while (!WindowShouldClose()) {

        // Show the instruction screen before the match starts
        if (showInstructions) {
            ShowInstructionsScreen();
            continue;
        }

        const char* matchWinner = score.GetWinner();

        // Move the ball only if the match is still going
        if (!matchWinner) {
            ball.Update();
        }

        // Make the ball bounce off the top and bottom edges of the scren
        ball.BounceVertical(GetScreenHeight());

        // Paddle movement controls, for left use w/s keys, for right use up/down arrow keys
        if (!matchWinner) {
            if (IsKeyDown(KEY_W))      leftPaddle.MoveUp();
            if (IsKeyDown(KEY_S))      leftPaddle.MoveDown();
            if (IsKeyDown(KEY_UP))     rightPaddle.MoveUp();
            if (IsKeyDown(KEY_DOWN))   rightPaddle.MoveDown();
        }

        // Ball collision with the left paddle
        if (!matchWinner &&
            CheckCollisionCircleRec({ ball.x, ball.y }, ball.radius, leftPaddle.GetRect())) {

            if (ball.speedX < 0) {     // Ball must be moving toward the paddle
                ball.speedX *= -1.1f;  // Reverse and slightly increase speed
                ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * 300;
            }
        }

        // Ball collision with the right paddle
        if (!matchWinner &&
            CheckCollisionCircleRec({ ball.x, ball.y }, ball.radius, rightPaddle.GetRect())) {

            if (ball.speedX > 0) {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * 300;
            }
        }

        // Scoring: Player 1 misses
        if (!matchWinner && ball.x - ball.radius < 0) {
            score.IncrementRight();
            ball.Reset(GetScreenWidth(), GetScreenHeight());
            leftPaddle.Reset(GetScreenHeight());
            rightPaddle.Reset(GetScreenHeight());
        }

        // Scoring: Player 2 misses
        if (!matchWinner && ball.x + ball.radius > GetScreenWidth()) {
            score.IncrementLeft();
            ball.Reset(GetScreenWidth(), GetScreenHeight());
            leftPaddle.Reset(GetScreenHeight());
            rightPaddle.Reset(GetScreenHeight());
        }

        // If match is over, pressing space starts a new game
        if (matchWinner && IsKeyPressed(KEY_SPACE)) {
            score.Reset();
            ball.Reset(GetScreenWidth(), GetScreenHeight());
            leftPaddle.Reset(GetScreenHeight());
            rightPaddle.Reset(GetScreenHeight());
        }

        // Drawing section

        BeginDrawing();
        ClearBackground(Green);

        // Draw the score values
        score.Draw(GetScreenWidth());

        // Middle dividing line
        DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), Blackish);

        // Draw game objects
        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();

        // Display winner message if the match ended
        if (matchWinner) {
            int w = MeasureText(matchWinner, 50);
            DrawText(matchWinner,
                     GetScreenWidth()/2 - w/2,
                     GetScreenHeight()/2 - 60,
                     50, Yellow);

            DrawText("Press SPACE to play again",
                     GetScreenWidth()/2 - 150,
                     GetScreenHeight()/2 + 10,
                     20, WHITE);
        }

        DrawFPS(10, 10);   // Frames-per-second counter

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
