#pragma once
#include <iostream>
#include <time.h>
#include <ctime>
#include <math.h>
#include <thread>
#include <vector>
#include <random>

class TRNG
{
private:

    double* r;
    double* x;

    uint8_t numberOfNetworks = 4;
    uint8_t numberOfStages = 3;
    uint8_t numberOfIterations = 2;

    unsigned char generateNumber();

    void setGenerator();
public:

    unsigned char getRandomNumber();

    TRNG();
    ~TRNG();

};

