#ifndef SENSOR_HPP
#define SENSOR_HPP
#include "../object.hpp"
#include <random>

class Sensor
{
    public:
        Sensor(Object * parent, float noise, float bias);
        Sensor(Object * parent, float noise);

        float get();
    protected:
        Object * parent;
        float trueValue;
        float noise;
        float bias;
};

float getGaussianNoise(float mean, float stddev);


class PositionSensor : public Sensor
{
    public:
        using Sensor::Sensor;
        float get();
};
class Altimeter : public Sensor
{
    public:
        using Sensor::Sensor;
        float get();
};

#endif