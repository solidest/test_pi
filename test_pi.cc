#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>  

#define CPU_CORES 2

double calc_pi() {
    int divident = 1;
    int cnt = 0;
    double t1=1,t2=1;
    double evenPi = 1;
    double evenPiPre = 0;

    long long count = 0;
    while (count++ < 20)
    {
        evenPiPre = evenPi;
        t1 = t1*t2;
        cnt++;
        divident += 2;
        t2 = (double)cnt / divident;
        evenPi = evenPiPre + t1*t2;
    }
    return evenPi*2;
}

void* work(void*) {
    while (true)
    {
        time_t start ,end ;  
        double cost;  
        time(&start);
        for (size_t i = 0; i < 30000000; i++)
        {
            calc_pi();
        }
        time(&end);  
        cost=difftime(end,start);
        printf("%fs\n",cost);        
    }
}


int main(void)
{
    pthread_t ids[CPU_CORES];
    for (size_t i = 0; i < CPU_CORES; i++) {
        pthread_create(&ids[i], NULL, work, NULL);        
    }
    for (size_t i = 0; i < CPU_CORES; i++) {
        pthread_join(ids[i], NULL);
    }
    return 0;
}