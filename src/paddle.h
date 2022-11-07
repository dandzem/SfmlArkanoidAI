/*
 * Paddle.h
 *
 *  Created on: 6 нояб. 2022 г.
 *      Author: Danila
 */

#ifndef PADDLE_H_
#define PADDLE_H_


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "std_lib_facilities.h"
#include "globals.h"
using namespace std;
using namespace sf;

struct Paddle{
	RectangleShape shape;
	Vector2f velocity;


	// Constructor
	Paddle(float mX, float mY)
	{
			shape.setPosition(mX,mY);
			shape.setSize({paddleWidth,paddleHeight});
			shape.setFillColor(Color::Blue);
			shape.setOrigin(paddleWidth/2.f,paddleHeight/2.f);

		}
	 // Functions to check position of the paddle parts (Needed for isInterstecting and TestCollisionPB functions
		float x() {return shape.getPosition().x; }
		float y() {return shape.getPosition().y; }
		float left() {return x() - shape.getSize().x /2.f; }
		float right() {return x() + shape.getSize().x /2.f; }
		float top() {return y() - shape.getSize().y /2.f; }
		float bottom() {return y() + shape.getSize().y /2.f; }


	// TO CHANGE TO PLAYER CONTROL CHANGE TO KEYBOARD CONTROL
	void update(Ball& ball)
	{
		shape.move(velocity);
		// Keyboard::isKeyPressed(Keyboard::Key::Left) OR get_gap_difference(ball) < 0
		if( Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) velocity.x = -paddleVelocity;
		//Keyboard::isKeyPressed(Keyboard::Key::Right) OR get_gap_difference(ball) > 0
		else if( Keyboard::isKeyPressed(Keyboard::Key::Right) > 0  && right() < windowWidth) velocity.x = paddleVelocity;

		else velocity.x = 0;
	}

	// Algorithm to check x position difference between paddle position and ball position
	float get_gap_difference(Ball& ball)
	{
		if (this->y() >= ball.y())
		{
			return  ball.x() - x();
		}
	return 0;
	}


};


#endif /* PADDLE_H_ */
