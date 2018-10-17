/**************************************************************************
This file implements the main abstractions in the ten pin bowling game.
***************************************************************************/
#include "bowling.h"

/* Initialise the game state */
Bowling::Bowling() {
	//First frame of the game starts at 0 not 1 and the number of balls intially bowled is 0.
	balls_bowled_ = 0;
	current_f_ = 0;

	//21 columns - can have a maximum of 21 balls bowled in a game_history_.
	game_history_.resize(21, { -1, -1, -1 });
}

/* Record game history and handle game logic for score keeping - spares, strikes, frames, etc. */
void Bowling::Ball(int pins_knocked) {
	//3 rows - these are: frame, pins knocked with each bowl and score respectively.
	game_history_[balls_bowled_].frame = current_f_;
	game_history_[balls_bowled_].pins = pins_knocked;

	if (balls_bowled_ == 0) {
		//Score for first ball
		game_history_[balls_bowled_].score = pins_knocked;
	} else {
		//Cumulative ball score
		game_history_[balls_bowled_].score = game_history_[balls_bowled_ - 1].score + pins_knocked;
	}

	if (balls_bowled_ > 1) {
		//Spare
		//If previous bowl and the bowl before that are in the same frame and add to 10 and it's not in the last frame.
		if ((game_history_[balls_bowled_ - 1].frame == game_history_[balls_bowled_ - 2].frame)
			&& (game_history_[balls_bowled_ - 1].pins + game_history_[balls_bowled_ - 2].pins == 10)
			&& (game_history_[balls_bowled_ - 2].frame != 9)) {
			//For a spare, add current ball score to previous frame score.
			game_history_[balls_bowled_ - 1].score += pins_knocked;

			//Recalculate next ball score
			game_history_[balls_bowled_].score = game_history_[balls_bowled_ - 1].score + pins_knocked;
		}

		//Strike
		//If a 10 is bowled and its not in the last frame.
		if ((game_history_[balls_bowled_ - 2].pins == 10) && (game_history_[balls_bowled_ - 2].frame != 9)) {
			//Add the next two ball scores.
			game_history_[balls_bowled_ - 2].score += game_history_[balls_bowled_ - 1].pins;
			game_history_[balls_bowled_ - 2].score += game_history_[balls_bowled_].pins;

			//Recalculate the next two ball scores.
			game_history_[balls_bowled_ - 1].score = game_history_[balls_bowled_ - 2].score + game_history_[balls_bowled_ - 1].pins;
			game_history_[balls_bowled_].score = game_history_[balls_bowled_ - 1].score + pins_knocked;
		}
	}

	//Go to next ball
	balls_bowled_++;
	//Go to next frame if it is not the last frame and either:
	//          if a strike is achieved
	//          or 2 previous balls are bowled in the same frame
	if ((current_f_ != 9) && (pins_knocked == 10)) {
		current_f_++;
	}
	if (balls_bowled_ > 1) {
		if ((current_f_ != 9)
			&& (game_history_[balls_bowled_ - 1].frame == game_history_[balls_bowled_ - 2].frame)) {
			current_f_++;
		}
	}
}

/* Return the overall game score, regardless of whether the game is finished or still in progress. */
int Bowling::GetScore() {
	return game_history_[balls_bowled_ - 1].score;
}

/* Return the cumulative score from the the start of the game to a particular frame. */
int Bowling::GetFrameScore(int frame) {
	/* Get iterator pointing to the required frame in the vector using lambda function (C++11 specific).

		[&frame_to_match = frame] binds the variable frame from the calling scope to
		a local reference in the lambda, called frame_to_match.

		(const BallRolled &b) -> bool defines the signature of the lambda,
		i.e. take one input parameter, b, and return a bool.

		{ return b.frame == frame_to_match; } is the body of the lambda function.
		Returns true if b.frame and frame_to_match compare as equal.
	*/
    auto iterator = std::find_if(game_history_.begin(),
                                game_history_.end(),
                                [&frame_to_match = frame]
                                (const BallRolled &b) -> bool { return b.frame == frame_to_match; });

	//Get the score from the last ball bowled in the frame.
    while (std::next(iterator, 1)->frame == frame) {
        std::advance(iterator, 1);
    }
    return iterator->score;
}

/* Return the number of pins knocked over for a particular ball. */
int Bowling::GetBallScore(int frame, int ball)  {
    //Get an iterator pointing to the required n in the vector.
	auto iterator = std::find_if(game_history_.begin(),
                                game_history_.end(),
                                [&frame_to_match = frame]
                                (const BallRolled &b) -> bool { return b.frame == frame_to_match; });

    //Increment the iterator by the number of balls.
    std::advance(iterator, ball);
    return iterator->pins;
}

/* Return the number of frames completed (including the one currently being completed) in the game. */
int Bowling::GetFramesBowled() {
	return game_history_[balls_bowled_ - 1].frame + 1;
}

/* Return the number of balls bowled for a particular frame.
	Example: a strike means only 1 ball is bowled for the frame.
			Anything else means 2 balls are bowled in the frame,
			unless it is the last frame or a frame is not completed.
*/
int Bowling::GetBallsBowledInFrame(int frame) {
	return std::count_if(game_history_.begin(),
        game_history_.end(),
        [&frame_to_match = frame]
        (const BallRolled &b) -> bool { return b.frame == frame_to_match; });
}

/* Return boolean indicating whether the game has been completed. */
bool Bowling::IsGameOver() {
	bool over = false;

	if (balls_bowled_ > 2) {
		//game_history_ is over if the last three frames recorded are 9 (i.e. 10th frame).
		if ((game_history_[balls_bowled_ - 1].frame == 9) && (game_history_[balls_bowled_ - 2].frame == 9) && (game_history_[balls_bowled_ - 3].frame == 9)) {
			over = true;
		} else if ((game_history_[balls_bowled_ - 1].frame == 9) && (game_history_[balls_bowled_ - 2].frame == 9)) {
			//game_history_ is also over if the last two frames are recorded are 9 and
			//		there are no spares
			//		nor strikes
			if (((game_history_[balls_bowled_ - 1].frame != 10) && (game_history_[balls_bowled_ - 2].frame != 10)) || (game_history_[balls_bowled_ - 1].frame + game_history_[balls_bowled_ - 2].frame != 10)) {
				over = true;
			}
		}
	}
	return over;
}
