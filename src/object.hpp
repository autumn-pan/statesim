#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object
{
    public:
        Object(float mas);

        void setVel(float xVel, float yVel);
        void setAcc(float xAcc, float yAcc);

        void update(float deltaTime);


    private:
        float x;
        float y;

        float xVel;
        float yVel;

        float xAcc;
        float yAcc;
       
        float mass;
};
#endif