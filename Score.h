#ifndef SCORE_H
#define SCORE_H

#include <raylib.h>

// The Score class keeps track of both players' points,
// checks when the match is over, and draws the score on screen.
class Score {
private:
    int leftScore;      // Score for Player 1 (left paddle)
    int rightScore;     // Score for Player 2 (right paddle)
    int maxScore;       // Points needed to win the match

public:
    // Default constructor (optional)
    Score();

    // Constructor that allows setting a custom maximum score
    Score(int max);
    
    // Increases Player 1's score
    void IncrementLeft();

    // Increases Player 2's score
    void IncrementRight();

    // Resets both scores to zero
    void Reset();
    
    // Getters for both player scores and the winning score
    int GetLeftScore() const;
    int GetRightScore() const;
    int GetMaxScore() const;
    
    // Returns true if either player has reached the max score
    bool IsMatchOver() const;

    // Returns a text message announcing the winner,
    // or nullptr if the match is still ongoing.
    const char* GetWinner() const;
    
    // Draws the score values on the screen
    void Draw(int screenWidth);
};

#endif
