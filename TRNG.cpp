#include "TRNG.h"

//Constructor & Destructor

TRNG::TRNG(){

    r = new double(4);
    x = new double(5);

    setGenerator();

}

TRNG::~TRNG()
{
    delete r;
    delete x;
}

// Generator

unsigned char TRNG::generateNumber(){
    std::shared_ptr<int> c = std::make_shared<int>(0);
    std::vector<std::thread> threads[numberOfNetworks];
    auto f = [](std::shared_ptr<int> c, double* x, double* r, uint8_t numOfNetworks, uint8_t numOfStages, uint8_t numOfIterations){
        while (*c!=numOfNetworks){
            (*c)=*c+1;
            double r_prim[4] = {*r, *r, *r, *r};
            double y[4];
            for (uint8_t i=0; i<4; i++){
                for (uint8_t j=0; j<numOfIterations; j++){
                    *x = *x * r_prim[i] * (1-(*x));
                    *x = *x * 1000 - std::floor(*x*1000);
                }
                y[i] = 3.86 * (0.14*(*x));
            }
            for (int k = 2; k<= numOfStages; k++){
                if (*x >= 0.5){
                    r_prim[0] = (y[0] + y[2])/2;
                    r_prim[1] = (y[0] + y[2])/2;
                    r_prim[2] = (y[1] + y[3])/2;
                    r_prim[3] = (y[1] + y[3])/2;
                } else{
                    r_prim[0] = (y[0] + y[1] + y[2] + y[3])/4;
                    r_prim[1] = (y[0] + y[1] + y[2] + y[3])/4;
                    r_prim[2] = (y[0] + y[1] + y[2] + y[3])/4;
                    r_prim[3] = (y[0] + y[1] + y[2] + y[3])/4;
                }
            }
            for(int i=0; i<4; i++){
                for(int j=0; j<numOfIterations; j++){
                    *x = *x * r_prim[i]*(1-(*x));
                    *x = (*x*1000) - std::floor(*x*1000);
                }
                y[i] = 3.86*(*x*0.14);
            }
            *r = (y[0] + y[1] + y[2] + y[3])/4;
        }
    };

    for ( int i =0; i<numberOfNetworks; i++){
        threads[i].emplace_back(f, c, x, r, numberOfNetworks, numberOfStages, numberOfIterations);
    }

    for (auto& network_threads : threads) {
        for (auto& thread : network_threads) {
            thread.join();
        }
    }
    return *x*256;
}

//Setter

void TRNG::setGenerator(){
    time_t currentTimestamp;
    currentTimestamp=(time(NULL));
    *r = ((double)((int)currentTimestamp&0b1111)/10)*2.65;
    *x = 0.4234;
}

//Getter

unsigned char TRNG::getRandomNumber(){
    return generateNumber();
}
