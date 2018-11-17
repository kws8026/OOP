#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <iostream>
#include <cstring>
#include <string>
#include "Utils.h"
#include "Renderer.h"

using namespace std;

class GameObject {
	Renderer& renderer;
	Position pos;
	string shape;

public:
	GameObject(Position pos, const char* shape) : renderer(Renderer::getInstance()), pos(pos), shape(shape) {}
	GameObject(Position pos, const string& shape) : GameObject(pos, shape.c_str()) {}
	virtual ~GameObject() {} // very important!!!

	void setPosition(Position pos) { this->pos = pos; }
    Position getPosition() const { return pos; }

	void setShape(const char* shape) { this->shape = shape; }
	void setShape(const string& shape) { this->shape = shape; }
	const string& getShape() const { return shape; }
	int getShapeSize() const { return (int)shape.size(); }

	void move(int x, int y =0) {
    pos = pos + Position(x,y); }
    void move(Position vector) { move(vector.x, vector.y); }
	void moveTo(int x, int y) {
		if (x != -1)
			pos.x = x;
		if (y != -1)
			pos.y = y;
	}

	virtual void update() {}
	virtual void draw() { drawToRenderer(shape, pos); }

	void drawToRenderer(const string& shape, Position pos) { renderer.draw(shape, pos); }

	int getScreenLength() const { return renderer.getScreenLength(); }
};

class Damageable {
	float damageRatio;

public:
	Damageable(float damageRatio) : damageRatio(damageRatio) {}

	float getDamage() { return damageRatio; }

	void setDamageRatio(float damageRatio) { this->damageRatio = damageRatio; }

	virtual bool getDamagedIfAttacked(const GameObject& attacker) = 0;	
};

class SizedMove{
	Position borad;
public:
	SizedMove() : borad(Renderer::getInstance().getScreenSize()) {}
	void checkRange(GameObject& target) {
		Position pos = target.getPosition();
		int temp[2] = {-1,-1};
		if (pos.x < 0)
			temp[0] = 0;
		else if ( pos.x  >= borad.x)
			temp[0] = borad.x-1;
		if (pos.y < 0 )
			temp[1] = 0;
		else if (pos.y  >= borad.y)
			temp[1] = borad.y - 1;
		target.moveTo(temp[0], temp[1]);
	}
};

enum class Direction {
	Left = 0,
	Right
};

#endif