#include "sensor.hpp"

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

float Sensor::get(Attribute attribute)
{
    float trueValue = 0.0;

    switch (attribute)
    {
        case X:
            trueValue = this->parent->getX();
            break;
        case Y:
            trueValue = this->parent->getY();
            break;
        case X_VEL:
            trueValue = this->parent->getXVel();
            break;
        case Y_VEL:
            trueValue = this->parent->getYVel();
            break;
        case X_ACC:
            trueValue = this->parent->getXAcc();
            break;
        case Y_ACC:
            trueValue = this->parent->getYAcc();
            break;
    }
    
    float noise = getGaussianNoise(0.0, this->noise);
    return trueValue + noise + this->bias;
}
