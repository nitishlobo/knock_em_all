#include "acceptance_tests.h"

/*TODO Later: Use function overloading instead of having multiple functions
GetScore() - gets total score of all the frames
GetScore(2) - single argument gets score of a frame (ie. frame 2)
GetScore(2, 1) - double argument gets score of a ball from a fram (ie. frame 2, ball 1)
*/

/*----------------------------------
 JOHN SPRAY'S TEST CASES FOLLOW
----------------------------------*/
TEST(JohnSprayScore, OneBall) {
    Bowling g;
    g.Ball(2);
    ASSERT_EQ(2, g.GetScore());
}

TEST(JohnSprayScore, TwoBalls) {
    Bowling g;
    g.Ball(2);
    g.Ball(3);

    EXPECT_EQ(2, g.GetBallScore(0,0));
    EXPECT_EQ(3, g.GetBallScore(0,1));
    EXPECT_EQ(5, g.GetFrameScore(0));
    ASSERT_EQ(5, g.GetScore());
}

TEST(JohnSprayScore, Spares) {
    Bowling g;
    for (int i=0; i<21; i++)
    {
      g.Ball(5);
    }

    //Test number of balls bowled in each frame and the total number of frames bowled.
    EXPECT_EQ(2, g.GetBallsBowledInFrame(0));
    EXPECT_EQ(2, g.GetBallsBowledInFrame(1));
    ASSERT_EQ(3, g.GetBallsBowledInFrame(9));
    ASSERT_EQ(10, g.GetFramesBowled());

    //Test individual ball scores. First argument is the frame, second argument is the ball.
    EXPECT_EQ(5, g.GetBallScore(0,0));
    EXPECT_EQ(5, g.GetBallScore(0,1));
    EXPECT_EQ(5, g.GetBallScore(1,0));
    EXPECT_EQ(5, g.GetBallScore(1,1));
    EXPECT_EQ(5, g.GetBallScore(9,0));
    EXPECT_EQ(5, g.GetBallScore(9,1));
    ASSERT_EQ(5, g.GetBallScore(9,2));

    //Test frame scores
    EXPECT_EQ(15, g.GetFrameScore(0));
    EXPECT_EQ(30, g.GetFrameScore(1));
    ASSERT_EQ(150, g.GetFrameScore(9));

    //Test total score
    ASSERT_EQ(150, g.GetScore());
}

TEST(JohnSprayScore, Strikes) {
    Bowling g;
    for (int i=0; i<12; i++)
    {
      g.Ball(10);
    }

    //Test number of balls bowled in each frame and the total number of frames bowled.
    EXPECT_EQ(1, g.GetBallsBowledInFrame(0));
    EXPECT_EQ(1, g.GetBallsBowledInFrame(1));
    ASSERT_EQ(3, g.GetBallsBowledInFrame(9));
    ASSERT_EQ(10, g.GetFramesBowled());

    //Test individual ball scores. First argument is the frame, second argument is the ball.
    EXPECT_EQ(10, g.GetBallScore(0,0));
    EXPECT_EQ(10, g.GetBallScore(1,0));
    EXPECT_EQ(10, g.GetBallScore(9,1));
    EXPECT_EQ(10, g.GetBallScore(9,0));
    ASSERT_EQ(10, g.GetBallScore(9,2));

    //Test frame scores
    EXPECT_EQ(30, g.GetFrameScore(0));
    ASSERT_EQ(60, g.GetFrameScore(1));

    //Test total score
    ASSERT_EQ(300, g.GetScore());
}

/*----------------------------------
 ROBERT MARTIN'S TEST CASES FOLLOW
----------------------------------*/
TEST(RobertMartinScore, OneBall) {
    Bowling g;
    g.Ball(5);
    g.Ball(4);
    ASSERT_EQ(9, g.GetScore());
}

TEST(RobertMartinScore, TwoBalls) {
    Bowling g;
    g.Ball(5);
    g.Ball(4);
    g.Ball(7);
    g.Ball(2);

    EXPECT_EQ(9, g.GetFrameScore(0));
    EXPECT_EQ(18, g.GetFrameScore(1));
    ASSERT_EQ(18, g.GetScore());
}

TEST(RobertMartinScore, SimpleSpare) {
    Bowling g;
    g.Ball(3);
    g.Ball(7);
    g.Ball(3);

    EXPECT_EQ(13, g.GetFrameScore(0));
    ASSERT_EQ(16, g.GetScore());
}

TEST(RobertMartinScore, SimpleFrameAfterSpare) {
    Bowling g;
    g.Ball(3);
    g.Ball(7);
    g.Ball(3);
    g.Ball(2);

    EXPECT_EQ(13, g.GetFrameScore(0));
    ASSERT_EQ(18, g.GetScore());
}

TEST(RobertMartinScore, SimpleStrike) {
    Bowling g;
    g.Ball(10);
    g.Ball(3);
    g.Ball(6);

    EXPECT_EQ(19, g.GetFrameScore(0));
    ASSERT_EQ(28, g.GetScore());
}

TEST(RobertMartinScore, PerfectGame) {
    Bowling g;
    for (int i=0; i<12; i++)
    {
      g.Ball(10);
    }

    ASSERT_EQ(300, g.GetScore());
}

TEST(RobertMartinScore, EndOfArray) {
    Bowling g;
    for (int i=0; i<9; i++)
    {
    g.Ball(0);
    g.Ball(0);
    }
    g.Ball(2);
    g.Ball(8);  //10th frame makes a spare in the first 2 bowls.
    g.Ball(10); //Last bowl produces a strike.

    ASSERT_EQ(20, g.GetScore());
}

TEST(RobertMartinScore, SampleGame) {
    Bowling g;
    g.Ball(1);
    g.Ball(4);
    g.Ball(4);
    g.Ball(5);
    g.Ball(6);
    g.Ball(4);
    g.Ball(5);
    g.Ball(5);
    g.Ball(10);
    g.Ball(0);
    g.Ball(1);
    g.Ball(7);
    g.Ball(3);
    g.Ball(6);
    g.Ball(4);
    g.Ball(10);
    g.Ball(2);
    g.Ball(8);
    g.Ball(6);

    //Test number of balls bowled in each frame and the total number of frames bowled.
    EXPECT_EQ(2, g.GetBallsBowledInFrame(0));
    EXPECT_EQ(2, g.GetBallsBowledInFrame(1));
    EXPECT_EQ(2, g.GetBallsBowledInFrame(2));
    EXPECT_EQ(1, g.GetBallsBowledInFrame(4));
    EXPECT_EQ(2, g.GetBallsBowledInFrame(5));
    EXPECT_EQ(1, g.GetBallsBowledInFrame(8));
    ASSERT_EQ(3, g.GetBallsBowledInFrame(9));

    ASSERT_EQ(10, g.GetFramesBowled());

    //Test individual ball scores. First argument is the frame, second argument is the ball.
    EXPECT_EQ(1, g.GetBallScore(0, 0));
    EXPECT_EQ(4, g.GetBallScore(0, 1));
    EXPECT_EQ(6, g.GetBallScore(2, 0));
    EXPECT_EQ(4, g.GetBallScore(2, 1));
    EXPECT_EQ(10, g.GetBallScore(4, 0));
    EXPECT_EQ(2, g.GetBallScore(9, 0));
    EXPECT_EQ(8, g.GetBallScore(9, 1));
    ASSERT_EQ(6, g.GetBallScore(9, 2));

    //Test frame scores
    EXPECT_EQ(5, g.GetFrameScore(0));
    EXPECT_EQ(29, g.GetFrameScore(2));
    EXPECT_EQ(60, g.GetFrameScore(4));
    ASSERT_EQ(117, g.GetFrameScore(8));

    ASSERT_EQ(133, g.GetScore());
}

TEST(RobertMartinScore, HeartBreak) {
    Bowling g;
    for (int i=0; i<11; i++)
    {
      g.Ball(10);
    }
    g.Ball(9);

    ASSERT_EQ(299, g.GetScore());
}

TEST(RobertMartinScore, TenthFrameSpare) {
    Bowling g;
    for (int i=0; i<9; i++)
    {
        g.Ball(10);
    }
    g.Ball(9);
    g.Ball(1);
    g.Ball(1);

    ASSERT_EQ(270, g.GetScore());
}

TEST(RobertMartinScore, FullGame01) {
    TestFullGame(std::vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 0);
}

TEST(RobertMartinScore, FullGame02) {
    TestFullGame(std::vector<int> {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 20);
}

TEST(RobertMartinScore, FullGame03) {
    TestFullGame(std::vector<int> {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 300);
}

TEST(RobertMartinScore, FullGame04) {
    TestFullGame(std::vector<int> {5,5,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 16);
}

TEST(RobertMartinScore, FullGame05) {
    TestFullGame(std::vector<int> {10,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 24);
}

TEST(RobertMartinScore, FullGame06) {
    TestFullGame(std::vector<int> { 10, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 24);
}

TEST(RobertMartinScore, FullGame07) {
    //Tenth frame spare
    TestFullGame(std::vector<int> {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,1 }, 11);
}

TEST(RobertMartinScore, FullGame08) {
  //Tenth frame strike
  TestFullGame(std::vector<int> { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 1, 1 }, 12);
}

TEST(RobertMartinScore, FullGame09) {
    //Example game from katas
    TestFullGame(std::vector<int> { 1, 4, 4, 5, 6, 4, 5, 5, 10, 0, 1, 7, 3, 6, 4, 10, 2, 8, 6 }, 133);
}

void TestFullGame(std::vector<int> balls, int correct_score) {
    Bowling g;
    std::vector<int> v = balls;

    for (auto b:balls) {
    g.Ball(b);
    }
    ASSERT_EQ(g.GetScore(), correct_score);
    ASSERT_TRUE(g.IsGameOver());
}
