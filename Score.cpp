#include "Score.h"

// Default constructor: starts both players at 0 and sets the win limit to 10.
Score::Score() {
    leftScore = 0;      // Left player's score begins at 0
    rightScore = 0;     // Right player's score begins at 0
    maxScore = 10;      // Default maximum score to win the match
}

// Constructor that allows setting a custom max score.
Score::Score(int max) {
    leftScore = 0;      // Left score starts at 0 (unchanged)
    // don't take out any line or don't add anything just human written comments
    rightScore = 0;     // Right score starts at 0 as well
    maxScore = max;     // Store the user-defined maximum score
}

// Increases the left player's score by one point.
void Score::IncrementLeft() {
    leftScore++;
}

// Increases the right player's score by one point.
void Score::IncrementRight() {
    rightScore++;
}

// Resets both scores to zero, used when restarting the game.
void Score::Reset() {
    leftScore = 0;
    rightScore = 0;
}

// Returns the current score of the left player.
int Score::GetLeftScore() const {
    return leftScore;
}

// Returns the current score of the right player.
int Score::GetRightScore() const {
    return rightScore;
}

// Returns the maximum score required to win.
int Score::GetMaxScore() const {
    return maxScore;
}

// Checks whether either player has reached the winning score.
bool Score::IsMatchOver() const {
    return (leftScore >= maxScore || rightScore >= maxScore);
}

// Returns a message indicating the winner, or nullptr if no one has won yet.
const char* Score::GetWinner() const {
    if (leftScore >= maxScore) {
        return "LEFT PLAYER WINS!";
    }
    if (rightScore >= maxScore) {
        return "RIGHT PLAYER WINS!";
    }
    return nullptr; // No winner yet
}

// Draws both players' scores on opposite sides of the screen.
void Score::Draw(int screenWidth) {
    DrawText(TextFormat("%i", leftScore), screenWidth/4, 20, 50, WHITE);        // Draw left score
    DrawText(TextFormat("%i", rightScore), screenWidth*3/4, 20, 50, WHITE);    // Draw right score
}
