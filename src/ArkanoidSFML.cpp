//============================================================================
// Name        : ArkanoidSFML.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "ball.h"
#include "std_lib_facilities.h"
#include "globals.h"
#include "brick.h"
#include "paddle.h"
#include "Timer.h"



using namespace std;
using namespace sf;



// To check if objects Positions are in each other
template<class T1,class T2> bool isInterstecting(T1& mA, T2& mB)
{
	return mA.right() >= mB.left() && mA.left() <= mB.right()
			&& mA.bottom() >= mB.top() && mA.top() <= mB.bottom();

}


// To check if Ball hits Paddle and change angle of move to inverted one
void testCollisionPB(Paddle& mPaddle, Ball& mBall)
{

	if(!isInterstecting(mPaddle,mBall)) return;

	mBall.velocity.y = -ballVelocity;

	if(mBall.x() < mPaddle.x()) mBall.velocity.x = -ballVelocity;
	else mBall.velocity.x = ballVelocity;
}


void testCollisionBB(Brick& mBrick, Ball& mBall)
{
	if(!isInterstecting(mBrick,mBall)) return;
	mBrick.hp--;
	mBall.score+=10;
	if (mBrick.hp <= 0) mBrick.destroyed = true;


	 float overlapLeft{mBall.right() - mBrick.left()};
	 float overlapRight{mBrick.right() - mBall.left()};
	 float overlapTop{mBall.bottom() - mBrick.top()};
	 float overlapBottom{mBrick.bottom() - mBall.top()};

	 bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	 bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	 float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
	 float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

	 if(abs(minOverlapX) < abs(minOverlapY))
		 mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
	 else
	     mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;

}



void buildBricks(vector<Brick>& bricks) {

	for (int i{0}; i < countBrickX; i++ )
		for(int j{0}; j < countBrickY; j++)
			bricks.emplace_back((i+1)*(brickWidth+brickPadding)+15,(j+1)*(brickHeight+brickPadding));
}

void resetBricks(vector<Brick>& bricks) {
	bricks.clear();
	buildBricks(bricks);
}



int main()
{

	Font font;
	font.loadFromFile("Fonts/arial.ttf");

	Ball ball(320, windowHeight-30,3,0);
	Paddle paddle(windowWidth / 2, windowHeight - 30);

    RenderWindow window{{windowWidth,windowHeight},"Arkanoid"};
    window.setFramerateLimit(60);



    Timer clock;

    // construct for Brick durability text
    Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(24);
    hpText.setFillColor(Color::White);


    // construct to display time on the window
    Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(Color::White);
    timeText.setPosition(windowWidth / 2, 0);
    timeText.setOrigin(windowWidth/ 2.f, 0);

    // construct to display score
    Text scoreTxt;
    scoreTxt.setFont(font);
    scoreTxt.setCharacterSize(20);
    scoreTxt.setFillColor(Color::White);
    scoreTxt.setPosition(10,400);

    vector<Brick> bricks;
    buildBricks(bricks);

    while(true)
    {
    	window.clear(Color::Black);



    	// visual debug line to measure difference between ball and paddle
    	RectangleShape line(Vector2f(paddle.get_gap_difference(ball),2));
    	line.setFillColor(Color::White);
    	line.setPosition(paddle.x(),paddle.y());
    	window.draw(line);

    	// In each time frame we update Text string with passed time in seconds. then round it to int
    	timeText.setString("Time:" + to_string(static_cast<int>(clock.GetElapsedSeconds())));

    	scoreTxt.setString("Score: " + to_string(ball.score));

    	if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;


    	// On each frame of the game display health and if it changes dynamically update it.
    	BallHpText text(ball);

    	// if ball is zero -> wait until space is pressed -> restart the game
    	if (ball.checkHP()) {
    		ball.velocity.x = 0 , ball.velocity.y = 0;
    		paddle.velocity.x = 0;
    		clock.Pause();
    		timeText.setString("Time:" + to_string(static_cast<int>(round(clock.GetElapsedSeconds()))) + " GAME OVER PRESS SPACE TO RESTART");
    		if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
    			ball = Ball(320, windowHeight-30,3,0);
    			paddle = Paddle(windowWidth / 2, windowHeight - 30);
    			resetBricks(bricks);
    			clock.Reset();

    		}
    	};
    	// if ball touches bottom region -> reset position of the ball with decreased hp
    	if( ball.update() ) ball=Ball(320, windowHeight-30, ball.hp--,ball.score);


    	paddle.update(ball);
    	testCollisionPB(paddle,ball);

    	window.draw(scoreTxt);
    	window.draw(text.text);
    	window.draw(timeText);
    	window.draw(ball.shape);
    	window.draw(paddle.shape);


    	// Draw bricks with durability count
    	for(Brick& brick : bricks)
    	{
    		hpText.setString(to_string(brick.hp));
    		hpText.setPosition(brick.shape.getPosition().x - hpText.getGlobalBounds().width,brick.shape.getPosition().y - hpText.getGlobalBounds().height);
    		window.draw(hpText);
    		window.draw(brick.shape);
    	}


    	// Check for collision of ball and brick
    	for(Brick& brick : bricks) testCollisionBB(brick,ball);

    	// Iterator function to sort blocks with condition for variable destroyed and then remove them from window rendering
    	bricks.erase(remove_if(begin(bricks),end(bricks), [](const Brick& mBrick){return mBrick.destroyed;}), end(bricks));
    	window.display();
    }

    return 0;
}
