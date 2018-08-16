#include <vector>
#include <algorithm>	//std::find and std::count
#include <iterator>		//std::distance

class Bowling {
private:
    bool game_over, strike;
    int current_f, current_b;			//Current ball and current frame
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

//Returns the index to the first element in which a match to n is found.
int getIndexOfMatch(std::vector<int> v, int n);

//TODO delete debug
void printVector(std::vector<std::vector<int>> v);
