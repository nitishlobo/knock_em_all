/**************************************************************************
This file declares the two main abstractions in the ten pin bowling game.
The Bowling class contains the main game logic and it uses the BallRolled
struct to record the game history.
***************************************************************************/

#include <vector>
#include <algorithm>    //std::find and std::count
#include <iterator>     //std::distance, std::next and std::advance

/* Record game data whenever a ball is bowled.
    frame - the frame number (0 - 9)
    pins - number of pins knocked down during a particular bowl (0 - 9)
    score - cumulative score since the beginning of the game up to a particular roll (0 - 300)
			Note that the score is per ball roll not per frame. This means that
			if there are two rolls in a frame each roll will have a different score.

	Example: std::vector<BallRolled> game_history;
			BallRolled current_roll;
			current_roll.frame = 0;
			current_roll.pins = 8;
			current_roll.score = 8;
			game_history.push_back(current_roll);
*/
struct BallRolled {
	int frame;
	int pins;
	int score;
};


/*	Record the full game history (it handles all the game logic automatically).
	Need only one instantiation of this class per player per game.

	Example: Bowli	ng player_nitish;
			player_nitish.Ball(10);
*/
class Bowling {
/* Class members:
	current_f_ - current frame. The frame into which the player will be bowling into next (0 - 9)
	balls_bowled - total number of balls bowled since the beginning of the game (0 - 9)
	game_history - full history of all the pins knocked on every ball roll and the cumulative game score
*/
private:
	int current_f_;
	int balls_bowled_;
	std::vector<BallRolled> game_history;

public:
/*
Main class methods:
	Bowling - class initialisation
	Ball - call this method everytime a ball is bowled
*/
	Bowling();
	void Ball(int pins_knocked);

/*
Public APIs:
	GetScore - request the overall game score to date
	GetFrameScore - request the score since the beginning of the game to the end of a specified frame
	GetBallScore - request the score since the beginning of the game to a
					specific ball role in a specific frame
	GetFramesBowled - request the number of frames played in the game to date (including unfinished frames)
	GetBallsBowledInFrame - request the number of balls bowled in a specific frame of the game
	IsGameOver - request to see if the player has completed all 10 frames
*/
	int GetScore();
	int GetFrameScore(int frame);
	int GetBallScore(int frame, int ball);
	int GetFramesBowled();
	int GetBallsBowledInFrame(int frame);
	bool IsGameOver();
};
