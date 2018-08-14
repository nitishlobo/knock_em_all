#include "bowling.h"

//TODO delete debug
#include <iostream>

//Define constants for rows in game
const int frame_r = 0;
const int ball_r = 1;
const int score_r = 2;

Bowling::Bowling() {
    game_over = false;
    strike = false;

    current_b = 0;
    current_f = 0;
    strike_b = 0;

    //3 rows - these are: frame, pins knocked with each bowl and score respectively.
    //21 columns - can have a maximum of 21 balls bowled in a game.
    game.resize(3, std::vector<int>(21, -1));
}

void Bowling::Ball(int n) {
    //3 rows - these are: frame, pins knocked with each bowl and score respectively.
    game[frame_r][current_b] = current_f;
    game[ball_r][current_b] = n;

	if (current_b == 0) {
        //Score for first ball
		game[score_r][current_b] = n;
	} else {
		//Cumulative ball score
		game[score_r][current_b] = game[score_r][current_b - 1] + n;
	}

	if (current_b > 1) {
		//Spare
		//If previous bowl and the bowl before that are in the same frame and add to 10, then its a spare.
		if ((game[frame_r][current_b - 1] == game[frame_r][current_b - 2])
			&& (game[ball_r][current_b - 1] + game[ball_r][current_b - 2] == 10)) {
			//For a spare, add current ball score to previous frame score.
			game[score_r][current_b - 1] += n;

            //Recalculate next ball score
            game[score_r][current_b] = game[score_r][current_b - 1] + n;
		}

		//Strike
		if ((game[ball_r][current_b - 2] == 10) && (game[frame_r][current_b - 2] != 9)) {
			//Add the next two ball scores.
			game[score_r][current_b - 2] += game[ball_r][current_b - 1];
			game[score_r][current_b - 2] += game[ball_r][current_b];

			//Recalculate the next two ball scores.
			game[score_r][current_b - 1] = game[score_r][current_b - 2] + game[ball_r][current_b - 1];
			game[score_r][current_b] = game[score_r][current_b - 1] + n;
		}
	}

	//Go to next ball if it isn't the end of the game
	if (current_b < 20) {
		current_b++;
	}
    //Go to next frame if it is not the last frame and either:
    //          if a strike is achieved
    //          or 2 previous balls are bowled in the same frame
	if ((current_f != 9) && (n == 10)) {
		current_f++;
	}
	if (current_b > 1) {
		if ((current_f != 9)
		&& (game[frame_r][current_b - 1] == game[frame_r][current_b - 2])) {
			current_f++;
		}
	}
}

int Bowling::GetScore() {
    printVector(game);
    return game[score_r][current_b-1];
}

int Bowling::GetFrameScore(int frame) {
	//TODO: Exception handling - what if frame was a 10,000?

    std::vector<int>::size_type bowl_n=0;
    while(game[frame_r][bowl_n] != frame) {
		//Go to next ball
        bowl_n++;
    }

	while (game[frame_r][bowl_n] == frame) {
		bowl_n++;
	}
    return game[score_r][bowl_n-1];
}

int Bowling::GetBallScore(int frame, int ball)  {
	//TODO: Exception handling - what if frame was a 10,000?

    std::vector<int>::size_type i=0;
    while(game[frame_r][i] != frame) {
        i++;
    }
    return game[ball_r][i+ball];
}

int Bowling::GetFramesBowled() {
    return game[frame_r][current_b - 1] + 1;
}

int Bowling::GetBallsBowledInFrame(int frame) {
    //TODO: Exception handling - what if frame was a 10,000?

	std::vector<int>::size_type bowl_n = 0;
	while (game[frame_r][bowl_n] != frame) {
		//Go to next ball
		bowl_n++;
	}

	int balls = 0;
	while (game[frame_r][bowl_n] == frame) {
		bowl_n++;
		balls++;
	}
    return balls;
}

bool Bowling::IsGameOver() {
    //Game is finished only if there are 3 balls in the tenth frame.
    return false;
}

//TODO delete debug
void printVector(std::vector<std::vector<int>> v) {
    for (std::vector<int>::size_type i=0; i<3; i++) {
        for (std::vector<int>::size_type j=0; j<21; j++) {
            std::cout << v[i][j] << " ";
        }
        std::cout << "\n";
    }
}
