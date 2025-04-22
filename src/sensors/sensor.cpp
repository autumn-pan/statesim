#include "position.hpp"

// PositionSensor constructor
Sensor::Sensor(Object * parent, float noise, float bias)
{
    this->parent = parent;
    this->noise = noise;
    this->bias = bias;
}

// Instantiates a PositionSensor with a default bias of 0.0
Sensor::Sensor(Object * parent, float noise)
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

// Not intended for use; returns a dummy value
float Sensor::get() {return 0.0;}

