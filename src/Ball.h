#ifndef BALL_H_
#define BALL_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "std_lib_facilities.h"
#include "globals.h"
using namespace std;
using namespace sf;


struct Ball{
	CircleShape shape;
	Vector2f velocity{-ballVelocity,-ballVelocity};
	int hp;
	int score;

	//Constructor
	Ball(float mX, float mY, int mHp, int mScore) {
			shape.setPosition(mX,mY);
			shape.setRadius(ballRadius);
			shape.setFillColor(Color::Red);
			shape.setOrigin(ballRadius, ballRadius);
			hp = mHp;
			score = mScore;
		}
	// Functions to check position of the paddle parts (Needed for isInterstecting, TestCollisionPB and testCollisionBB functions
	float x() {return shape.getPosition().x;}
	float y() {return shape.getPosition().y;}
	float left() {return x() - shape.getRadius();}
	float right() {return x() + shape.getRadius();}
	float top() {return y() + shape.getRadius();}
	float bottom() {return y() - shape.getRadius();}


	bool update()
	{
		shape.move(velocity);

		if(left() <= 0) velocity.x = ballVelocity;

		else if(right() >= windowWidth) velocity.x = -ballVelocity;

		if(top()<= 0) {velocity.y = ballVelocity; return false;}
		else if(bottom() >= windowHeight) {
			this->hp--;
			velocity.y = -ballVelocity;
			return true;
		}
	return 0;
	}

	bool checkHP()
	{
		return hp == 0;
	}

};

// Class to display left attempts on the screen
struct BallHpText {
	Font font;
	Text text;
	stringstream ss;
	BallHpText(Ball& ball)
	{

		font.loadFromFile("Fonts/arial.ttf");
		text.setFont(font);
		text.setPosition(10, windowHeight - 50 );

		ss << "Health: " << ball.hp << endl;
		text.setString(ss.str());
	}

};


#endif /* BALL_H_ */
