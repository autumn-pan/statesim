#include "../src/object.hpp"
#include "../src/sensors/sensor.hpp"

#include <iostream>

int main()
{
    Object * obj = new Object(1.0);
    Sensor * sensor = new Sensor(obj, 0.1, 0.0);

    obj->setAcc(0.0, -9.81);
    obj->setVel(0.0, 10.0);

    for (int i = 0; i < 100; i++)
    {
        obj->update(0.1);
        float pos = sensor->get(Y_VEL);
        std::cout << "Measured Position: " << pos << "  True Position: " << obj->getYVel() << std::endl;
    }

    delete obj;
    delete sensor;

    return 0;
}