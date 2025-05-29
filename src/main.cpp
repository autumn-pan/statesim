#include <iostream>
#include "object.hpp"
#include "./sensor.hpp"
#include "./filter.h"
#include <vector>   
#include "cmath"
#include "./comp.cpp"
#include "/usr/include/matplot/matplot.h"

int main()                                                                                  
{

    std::vector<float> truePositions, filteredPositions, noisyPositions, x;

    float processNoise[2] = {0.0f, 0.0f}; // Example process noise for acceleration and position
    float measurementNoise[2] = {0.343097f, 0.343097f}; // Example measurement noise for acceleration and position
    KalmanFilter * kalmanFilter = new KalmanFilter(processNoise, measurementNoise, 0.001f); // Initialize Kalman filter with process and measurement noise
    ComplimentaryFilter * compFilter = new ComplimentaryFilter(600000.0f); // Initialize complementary filter with alpha = 0.4

    // model the motion of an obect
    Object obj(10.0f); // Create an object with mass 10.0 kg
    obj.setVel(5.0f, 10.0f); // Set initial velocity (5 m/s in x, 10 m/s in y)
    obj.setAcc(0.0f, 3.0f); 
    float deltaTime = 0.1f; // Time step for simulation (100 ms)
        // Create a sensor to measure the object's position with noise
        Sensor positionSensor(&obj, 0.5f, 0.0f); // 0.5 m noise, no bias
    float noiseVariance;

    float improvement = 0.0f; // Variable to store the improvement in accuracy
    for (int i = 0; i < 100; ++i) // Simulate for 10 seconds
    {
        x.push_back(i * deltaTime); // Store time for plotting
        obj.update(deltaTime); // Update the object's position and velocity
        // Check if the object is on the ground
        if (obj.getY() <= 0)
        {
            std::cout << "Object has hit the ground.\n";
            break; // Stop simulation if the object hits the ground
        }

        float noisyX = positionSensor.get(X);
        float noisyY = positionSensor.get(Y);
        std::cout << "Measurement " << i + 1 << ": "
                    << "True Position: (" << obj.getX() << ", " << obj.getY() << "), "
                  << "Noisy Position: (" << noisyX << ", " << noisyY << ")\n";


        // Update the Kalman filter with the noisy position measurement
        kalmanFilter->update(positionSensor.get(Y_ACC), positionSensor.get(Y)); // Update the Kalman filter with
        // the noisy position measurement
        std::cout << "Kalman Filter State: "
                  << "Acceleration: " << kalmanFilter->getAcceleration() << ", "
                  << "Velocity: " << kalmanFilter->getVelocity() << ", "
                  << "Position: " << kalmanFilter->getPosition() << "\n";
        std::cout << "Kalman filter accuracy: "
                  << kalmanFilter->getPosition() - obj.getY() << "\n";
        std::cout << "Measurement accuracy: "
                  << positionSensor.get(Y) - obj.getY() << "\n";
        std::cout << "----------------------------------------\n";

        improvement += abs((kalmanFilter->getPosition()) - (obj.getY())); // Calculate the improvement in accuracy
        noiseVariance += abs((positionSensor.get(Y)) - (obj.getY())); // Calculate the variance of the noise



        truePositions.push_back(obj.getY());
        filteredPositions.push_back(kalmanFilter->getPosition());
        noisyPositions.push_back(positionSensor.get(Y));
    }

    // Calculate and print the variance of the noise
    float variance = noiseVariance / x.size();

    std::cout << "Variance of noise: " << variance << "\n";
    std::cout << "Kalman filter variance: " << improvement / 100 << "\n";

    std::cout << std::endl;
    
    /*
    using namespace matplot;
    
    
    auto p = plot(x, truePositions, x, filteredPositions, x, noisyPositions,
                  x, trueVelocities, x, filteredVelocities, x, noisyVelocities,
                  x, trueAccelerations, x, filteredAccelerations, x, noisyAccelerations);

    p[0]->line_width(2);
    p[1]->line_width(2);
    p[2]->line_width(2);
    p[0]->color("blue");
    p[1]->color("red");
    p[2]->color("green");

    show();
    */



    // Clean up
    delete kalmanFilter;
    return 0;
}