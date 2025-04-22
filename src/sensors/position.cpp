#include "position.hpp"

// PositionSensor constructor
PositionSensor::PositionSensor(Object * parent, float noise, float bias)
{
    this->parent = parent;
    this->noise = noise;
    this->bias = bias;
}

// Instantiates a PositionSensor with a default bias of 0.0
PositionSensor::PositionSensor(Object * parent, float noise)
{
    this->parent = parent;
    this->noise = noise;
    this->bias = 0.0;
}

//Generate a random float with a Gaussian distribution
float getGaussianNoise(float mean, float stddev)
{
    static std::default_random_engine generator;

    std::normal_distribution<float> distribution(mean, stddev);

    return distribution(generator);
}

// Returns the measured position of the object
float PositionSensor::get()
{
    this->trueValue = this->parent->getX();
    return this->trueValue + bias + getGaussianNoise(bias, noise);
}