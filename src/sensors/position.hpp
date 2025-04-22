#ifndef POSITION_HPP
#define POSITION_HPP
#include "../object.hpp"
#include <random>

class Sensor
{
    public:
        Sensor(Object * parent, float noise, float bias);
        Sensor(Object * parent, float noise);

        float get();
    private:
        Object * parent;
        float trueValue;
        float noise;
        float bias;
};

float getGaussianNoise(float mean, float stddev);
#endif