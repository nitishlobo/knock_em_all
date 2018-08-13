#include "bowling.h"

//Define constants for rows in game
const int frame_r = 0;
const int ball_r = 1;
const int score_r = 2;

Bowling::Bowling() {
    game_over = false;
    strike = false;

    current_b = 0;
    current_f = 0;
    score = 0;
    strike_b = 0;

    //3 rows - these are: frame, pins knocked with each bowl and score respectively.
    //21 columns - can have a maximum of 21 balls bowled in a game.
    game.resize(3, std::vector<int>(21, 0));
}

void Bowling::Ball(int n) {
    //3 rows - these are: frame, pins knocked with each bowl and score respectively.
    game[frame_r][current_b] = current_f;
    game[ball_r][current_b] = n;

    //Spare
    //If previous bowl and the bowl before that are in the same frame and add to 10, then its a spare.
    if ((game[frame_r][current_b-1] == game[frame_r][current_b-2])
    && (game[ball_r][current_b-1] + game[ball_r][current_b-2] == 10)) {
        //For a spare, add current ball score to previous frame score.
        game[score_r][current_b-1] += n;
    }

    //Strike
    if (game[ball_r][current_b-2] == 10) {
        //Add the next two ball scores.
        game[score_r][current_b-2] += game[score_r][current_b-1];
        game[score_r][current_b-2] += game[score_r][current_b];

        //Recalculate the next two ball scores
        game[score_r][current_b-1] = game[score_r][current_b-2] + game[ball_r][current_b-1];
        game[score_r][current_b] = game[score_r][current_b-1] + n;
    } else {
        //Cumulative ball score
        game[score_r][current_b] = game[score_r][current_b-1] + n;
    }

    current_b++;
    //Go to next frame if it is not the last frame and either:
    //          2 previous balls are bowled in the same frame
    //          or if strike is achieved
    if ((game[frame_r][current_b] != 9)
    && ((game[frame_r][current_b] == game[frame_r][current_b-1])
    || (n == 10))) {
        current_f++;
    }
}

int Bowling::GetScore() {
    return game[score_r][current_b-1];
}

int Bowling::GetFrameScore(int frame) {
    std::vector<int>::size_type i=0;
    //TODO: Exception handling - what if frame was a 10,000?
    while(game[frame_r][i] < (frame+1)) {
        i++;
    }
    return game[score_r][current_b-1];
}

int Bowling::GetBallScore(int frame, int ball)  {
    std::vector<int>::size_type i=0;
    //TODO: Exception handling - what if frame was a 10,000?
    while(game[frame_r][i] < (frame+1)) {
        i++;
    }
    return game[score_r][current_b-3+ball];
}

int Bowling::GetFramesBowled() {
    return game[frame_r][current_b-1];
}

int Bowling::GetBallsBowledInFrame(int frame) {
    //TODO: Exception handling - what if frame was a 10,000?
    int balls = 0;
    std::vector<int>::size_type i=0;
    while(game[frame_r][i] < (frame+1)) {
        if (game[frame_r][i] == frame) {
            balls++;
        }
        i++;
    }
    return balls;
}

bool Bowling::IsGameOver() {
    //Game is finished only if there are 3 balls in the tenth frame.
    return false;
}
