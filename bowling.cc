#include "bowling.h"

//TODO delete debug
#include <iostream>

//Define constants for rows in game_history
const int kFrameRow = 0;
const int kBallRow = 1;
const int kScoreRow = 2;

Bowling::Bowling() {
	current_b_ = 0;
	current_f_ = 0;

	//21 columns - can have a maximum of 21 balls bowled in a game_history.
	game_history.resize(21, { -1, -1, -1 });
}

void Bowling::Ball(int n) {
	//3 rows - these are: frame, pins knocked with each bowl and score respectively.
	game_history[current_b_].frame = current_f_;
	game_history[current_b_].ball = n;

	if (current_b_ == 0) {
		//Score for first ball
		game_history[current_b_].score = n;
	} else {
		//Cumulative ball score
		game_history[current_b_].score = game_history[current_b_ - 1].score + n;
	}

	if (current_b_ > 1) {
		//Spare
		//If previous bowl and the bowl before that are in the same frame and add to 10 and it's not in the last frame.
		if ((game_history[current_b_ - 1].frame == game_history[current_b_ - 2].frame)
			&& (game_history[current_b_ - 1].ball + game_history[current_b_ - 2].ball == 10)
			&& (game_history[current_b_ - 2].frame != 9)) {
			//For a spare, add current ball score to previous frame score.
			game_history[current_b_ - 1].score += n;

			//Recalculate next ball score
			game_history[current_b_].score = game_history[current_b_ - 1].score + n;
		}

		//Strike
		//If a 10 is bowled and its not in the last frame.
		if ((game_history[current_b_ - 2].ball == 10) && (game_history[current_b_ - 2].frame != 9)) {
			//Add the next two ball scores.
			game_history[current_b_ - 2].score += game_history[current_b_ - 1].ball;
			game_history[current_b_ - 2].score += game_history[current_b_].ball;

			//Recalculate the next two ball scores.
			game_history[current_b_ - 1].score = game_history[current_b_ - 2].score + game_history[current_b_ - 1].ball;
			game_history[current_b_].score = game_history[current_b_ - 1].score + n;
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
			&& (game_history[current_b_ - 1].frame == game_history[current_b_ - 2].frame)) {
			current_f_++;
		}
	}
}

int Bowling::GetScore() {
	return game_history[current_b_ - 1].score;
}

int Bowling::GetFrameScore(int frame) {
	/*
	int index = GetIndexOfMatch(game_history[kFrameRow], frame);

	//Frame not found - invalid frame (ie. not 0 to 9) or not enough balls bowled to enter the frame.
	if (index == -1) {
		return -1;
	}

	return game_history[kScoreRow][index + GetBallsBowledInFrame(frame) - 1];

	//int index = GetIndexOfMatch(game_history, frame);

	//Frame not found - invalid frame (ie. not 0 to 9) or not enough balls bowled to enter the frame.
	if (index == -1) {
		return -1;
	}
    */
	//return game_history[index + GetBallsBowledInFrame(frame) - 1].score;
    //Get an iterator pointing to the required n in the vector.
    auto iterator = std::find_if(game_history.begin(),
                                game_history.end(),
                                [&frame_to_match = frame]
                                (const BallRolled &b) -> bool { return b.frame == frame_to_match; });

    while (iterator->frame == frame) {
        std::advance(iterator, 1);
    }
    std::advance(iterator, -1);

    return iterator->score;
}

int Bowling::GetBallScore(int frame, int ball)  {
	/*
	int index = GetIndexOfMatch(game_history[kFrameRow], frame);

	//Frame not found - invalid frame (ie. not 0 to 9) or not enough balls bowled to enter the frame.
	if (index == -1) {
		return -1;
	}

	return game_history[index + ball].ball;
	*/
    //Get an iterator pointing to the required n in the vector.
	auto iterator = std::find_if(game_history.begin(),
                                game_history.end(),
                                [&frame_to_match = frame]
                                (const BallRolled &b) -> bool { return b.frame == frame_to_match; });

    //Increment the iterator by the number of balls.
    std::advance(iterator, ball);

    return iterator->ball;
}

int Bowling::GetFramesBowled() {
	return game_history[current_b_ - 1].frame + 1;
}

int Bowling::GetBallsBowledInFrame(int frame) {
	/*
	return std::count(game_history[kFrameRow].begin(), game_history[kFrameRow].end(), frame);
	*/
	/*int balls = 0;
	for (BallRolled &i : game_history) {
		if (i.frame == frame) {
			balls++;
		}
	}
	return balls;
	*/
	return std::count_if(game_history.begin(),
        game_history.end(),
        [&frame_to_match = frame]
        (const BallRolled &b) -> bool { return b.frame == frame_to_match; });
}

bool Bowling::IsGameOver() {
	bool over = false;

	if (current_b_ > 2) {
		//game_history is over if the last three frames recorded are 9 (ie. 10th frame).
		if ((game_history[current_b_ - 1].frame == 9) && (game_history[current_b_ - 2].frame == 9) && (game_history[current_b_ - 3].frame == 9)) {
			over = true;
		} else if ((game_history[current_b_ - 1].frame == 9) && (game_history[current_b_ - 2].frame == 9)) {
			//game_history is also over if the last two frames are recorded are 9 and
			//		there are no spares
			//		nor strikes
			if (((game_history[current_b_ - 1].frame != 10) && (game_history[current_b_ - 2].frame != 10)) || (game_history[current_b_ - 1].frame + game_history[current_b_ - 2].frame != 10)) {
				over = true;
			}
		}
	}
	return over;
}

bool areNumbersEqual(int i, int n) {
	if (i == n) {
		return true;
	}
	return false;
}

/*
int GetIndexOfMatch(std::vector<BallRolled> history, int n) {
    //Get an iterator pointing to the required n in the vector.
	auto iterator = std::find_if(history.begin(),
                                history.end(),
                                [&n = n]
                                (const BallRolled &b) -> bool { return ;

	//n not found.
	if (iterator == v.end()) {
		return -1;
	}
	return std::distance(v.begin(), iterator);
	return 0;
}
*/

/*
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
*/

//TODO delete debug
void PrintVector(std::vector<std::vector<int>> v) {
	for (std::vector<int>::size_type i = 0; i < 3; i++) {
		for (std::vector<int>::size_type j = 0; j < 21; j++) {
			std::cout << v[i][j] << " ";
		}
		std::cout << "\n";
	}
}
