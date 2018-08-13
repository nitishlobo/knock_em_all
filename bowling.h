class Bowling {
private:
  bool game_over;
  int frame, ball, score;

public:
  Bowling();
  int GetScore();
  int GetFrameScore(int frame);
  int GetBallScore(int frame, int ball);
  int GetFramesBowled();
  int GetBallsBowledInFrame(int frame);
  bool IsGameOver();
}
