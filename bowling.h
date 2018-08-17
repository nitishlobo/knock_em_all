#include <vector>
#include <algorithm>	//std::find and std::count
#include <iterator>		//std::distance
#include <boost/bind.hpp>

struct BallRolled {
	int frame;
	int ball;
	int score;
};

class Bowling {
private:
	int current_f_, current_b_;			//Current ball and current frame
	std::vector<BallRolled> game_history;

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
//int GetIndexOfMatch(std::vector<int> v, int n);
int GetIndexOfMatch(std::vector<BallRolled> & history, int n);

//TODO delete debug
void PrintVector(std::vector<std::vector<int>> v);
