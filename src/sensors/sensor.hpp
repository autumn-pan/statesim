#ifndef SENSOR_HPP
#define SENSOR_HPP
#include "../object.hpp"
#include <random>

enum Attribute
{
    X,
    Y,
    X_VEL,
    Y_VEL,
    X_ACC,
    Y_ACC
};

class Sensor
{
    public:
        Sensor(Object * parent, float noise, float bias);
        Sensor(Object * parent, float noise);

        float get(Attribute attribute);
        
    protected:
        Object * parent;
        float trueValue;
        float noise;
        float bias;
};

float getGaussianNoise(float mean, float stddev);
#endif