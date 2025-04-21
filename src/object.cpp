#include "object.hpp"

Object::Object(float mass)
{
    this->mass = mass;
    this->x = 0;
    this->y = 0;
    this->xVel = 0;
    this->yVel = 0;
}

void Object::setVel(float xVel, float yVel)
{
    this->xVel = xVel;
    this->yVel = yVel;
}

void Object::setAcc(float xAcc, float yAcc)
{
    this->xAcc = xAcc;
    this->yAcc = yAcc;
}


void Object::update(float deltaTime)
{
    this->x += this->xVel * deltaTime;
    this->y += this->yVel * deltaTime;

    this->xVel += this->xAcc * deltaTime;
    this->yVel += this->yAcc * deltaTime;

    if (y <= 0)
    {
        y = 0;
        yVel = 0;
        yAcc = 0;
    }
}