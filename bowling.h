#include <vector>

class Bowling {
private:
    bool game_over, strike;
    int current_f, current_b, score;    //Current ball, current frame and score
    int strike_b;                       //Ball count after a strike
    std::vector<std::vector<int>> game;

public:
    Bowling();
    void Ball(int n);
    int GetScore();
    int GetFrameScore(int frame);
    int GetBallScore(int frame, int ball);
    int GetFramesBowled();
    int GetBallsBowledInFrame(int frame);
    bool IsGameOver();
};
