/*
 * Brick.h
 *
 *  Created on: 6 нояб. 2022 г.
 *      Author: Danila
 */

#ifndef BRICK_H_
#define BRICK_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "std_lib_facilities.h"
#include "globals.h"
using namespace std;
using namespace sf;

struct Brick{
	RectangleShape shape;

	bool destroyed{false};

	int hp;

	Brick(float mX,float mY) {
		hp = rand()% 10 + 1;

		shape.setPosition(mX,mY);
		shape.setSize({brickWidth,brickHeight});
		shape.setOutlineThickness(.8f);
		shape.setOutlineColor(Color::Yellow);
		shape.setFillColor(Color::Transparent);
		shape.setOrigin(brickWidth / 2.f, brickHeight / 2.f);

	}

	float x() {return shape.getPosition().x; }
	float y() {return shape.getPosition().y; }
	float left() {return x() - shape.getSize().x / 2.f; }
	float right() {return x() + shape.getSize().x / 2.f; }
	float top() {return y() - shape.getSize().y / 2.f; }
	float bottom() {return y() + shape.getSize().y / 2.f; }


};




#endif /* BRICK_H_ */
