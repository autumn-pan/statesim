class ComplimentaryFilter
{
    public:
        ComplimentaryFilter()
        {
            this->alpha = 0.4;
        }
        void update(float newPos, float newAcc)
        {

            acc = newAcc; // Update acceleration
            // Update velocity using acceleration
            vel += newAcc * 0.1; 
            // Apply complementary filter
            pos = alpha * (pos + vel*0.1) + (1 - alpha) * newPos;            
        }

        float getPosition() const { return pos; }
        float getVelocity() const { return vel; }
        float getAcceleration() const { return acc; }

    private:
        float alpha; // Complementary filter constant
        float pos = 0;
        float vel = 10;
        float acc = 1;
};