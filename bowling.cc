#include "bowling.h"

//TODO delete debug
#include <iostream>

//Define constants for rows in game
const int kFrameRow = 0;
const int kBallRow = 1;
const int kScoreRow = 2;

Bowling::Bowling() {
	current_b_ = 0;
	current_f_ = 0;

	//3 rows - these are: frame, pins knocked with each bowl and score respectively.
	//21 columns - can have a maximum of 21 balls bowled in a game.
	game.resize(3, std::vector<int>(21, -1));
}

void Bowling::Ball(int n) {
	//3 rows - these are: frame, pins knocked with each bowl and score respectively.
	game[kFrameRow][current_b_] = current_f_;
	game[kBallRow][current_b_] = n;

	if (current_b_ == 0) {
		//Score for first ball
		game[kScoreRow][current_b_] = n;
	} else {
		//Cumulative ball score
		game[kScoreRow][current_b_] = game[kScoreRow][current_b_ - 1] + n;
	}

	if (current_b_ > 1) {
		//Spare
		//If previous bowl and the bowl before that are in the same frame and add to 10 and it's not in the last frame. 
		if ((game[kFrameRow][current_b_ - 1] == game[kFrameRow][current_b_ - 2])
			&& (game[kBallRow][current_b_ - 1] + game[kBallRow][current_b_ - 2] == 10)
			&& (game[kFrameRow][current_b_ - 2] != 9)) {
			//For a spare, add current ball score to previous frame score.
			game[kScoreRow][current_b_ - 1] += n;

			//Recalculate next ball score
			game[kScoreRow][current_b_] = game[kScoreRow][current_b_ - 1] + n;
		}

		//Strike
		//If a 10 is bowled and its not in the last frame.
		if ((game[kBallRow][current_b_ - 2] == 10) && (game[kFrameRow][current_b_ - 2] != 9)) {
			//Add the next two ball scores.
			game[kScoreRow][current_b_ - 2] += game[kBallRow][current_b_ - 1];
			game[kScoreRow][current_b_ - 2] += game[kBallRow][current_b_];

			//Recalculate the next two ball scores.
			game[kScoreRow][current_b_ - 1] = game[kScoreRow][current_b_ - 2] + game[kBallRow][current_b_ - 1];
			game[kScoreRow][current_b_] = game[kScoreRow][current_b_ - 1] + n;
		}
	}

	//Go to next ball
	current_b_++;
	//Go to next frame if it is not the last frame and either:
	//          if a strike is achieved
	//          or 2 previous balls are bowled in the same frame
	if ((current_f_ != 9) && (n == 10)) {
		current_f_++;
	}
	if (current_b_ > 1) {
		if ((current_f_ != 9)
			&& (game[kFrameRow][current_b_ - 1] == game[kFrameRow][current_b_ - 2])) {
			current_f_++;
		}
	}
}

int Bowling::GetScore() {
	return game[kScoreRow][current_b_ - 1];
}

int Bowling::GetFrameScore(int frame) {
	int index = GetIndexOfMatch(game[kFrameRow], frame);

	//Frame not found - invalid frame (ie. not 0 to 9) or not enough balls bowled to enter the frame.
	if (index == -1) {
		return -1;
	}

	return game[kScoreRow][index + GetBallsBowledInFrame(frame) - 1];
}

int Bowling::GetBallScore(int frame, int ball)  {
	int index = GetIndexOfMatch(game[kFrameRow], frame);

	//Frame not found - invalid frame (ie. not 0 to 9) or not enough balls bowled to enter the frame.
	if (index == -1) {
		return -1;
	}

	return game[kBallRow][index + ball];
}

int Bowling::GetFramesBowled() {
	return game[kFrameRow][current_b_ - 1] + 1;
}

int Bowling::GetBallsBowledInFrame(int frame) {
	return std::count(game[kFrameRow].begin(), game[kFrameRow].end(), frame);
}

bool Bowling::IsGameOver() {
	bool over = false;

	if (current_b_ > 2) {
		//Game is over if the last three frames recorded are 9 (ie. 10th frame).
		if ((game[kFrameRow][current_b_ - 1] == 9) && (game[kFrameRow][current_b_ - 2] == 9) && (game[kFrameRow][current_b_ - 3] == 9)) {
			over = true;
		} else if ((game[kFrameRow][current_b_ - 1] == 9) && (game[kFrameRow][current_b_ - 2] == 9)) {
			//Game is also over if the last two frames are recorded are 9 and 
			//		there are no spares 
			//		nor strikes
			if (((game[kFrameRow][current_b_ - 1] != 10) && (game[kFrameRow][current_b_ - 2] != 10)) || (game[kFrameRow][current_b_ - 1] + game[kFrameRow][current_b_ - 2] != 10)) {
				over = true;
			}
		}
	}
	return over;
}

//Returns the index to the first element in which a match to n is found in v.
int GetIndexOfMatch(std::vector<int> v, int n) {
	//Get an iterator pointing to the required n in the vector.
	auto iterator = std::find(v.begin(), v.end(), n);

	//n not found.
	if (iterator == v.end()) {
		return -1;
	}
	return std::distance(v.begin(), iterator);
}

//TODO delete debug
void PrintVector(std::vector<std::vector<int>> v) {
	for (std::vector<int>::size_type i = 0; i < 3; i++) {
		for (std::vector<int>::size_type j = 0; j < 21; j++) {
			std::cout << v[i][j] << " ";
		}
		std::cout << "\n";
	}
}
