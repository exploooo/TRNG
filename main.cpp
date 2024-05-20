#include <fstream>
#include <time.h>
#include "TRNG.h"


//double measureTime(void (*functptr)(int n), int param);

int main()
{
    std::fstream plik;

    plik.open("wyniki.txt", std::ios::out);

    if(plik.good()){
        TRNG generator = TRNG();

        for ( int i = 0; i<10000; i++){
            unsigned char a = generator.getRandomNumber();
            plik << a-1+1 << std::endl;
            std:: cout << a-1+1 << std::endl;
        }

        plik.close();
    } else {
        std::cout << "Nie rozponano pliku!" << std::endl;
    }

    return 0;
}

/*
double measureTime(void (*functptr)(int n), int param){
    time_t startClock, endClock, diff;

    startClock = time(NULL);
    functptr(param);
    endClock = time(NULL);

    diff = difftime(endClock, startClock);

    return diff;
}
*/

