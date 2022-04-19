#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <math.h>

using std::cin;
using std::cout;
using std::endl;

int points_num = 0;
int threads_num = 0;
int total_pts = 0;
std::vector<pthread_t> threads;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *count(void *thread_id)
{ 
    int *threadID = (int*) thread_id;   
    long cir_threads_num = 0;    
    for (long i = 0; i < (points_num / threads_num); i++) {
        double x = (double)rand() / (double)RAND_MAX;
        double y = (double)rand() / (double)RAND_MAX;
        if (x * x + y * y < 1) {
            cir_threads_num++;  
        }
    }

    double pi = (4. * (double)cir_threads_num) / ((double)(points_num / threads_num) * 1);
    cout << "The number of points in circule : " << cir_threads_num << endl; 
    cout << "The approximate value of pi for the desired amount of points: " << threadID << " is: " << pi << endl;
    cout << endl;
    pthread_mutex_lock(&mutex); 
    total_pts += cir_threads_num;
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

void thread_create(){
    do {
      cout << "Enter a positive number for the amount of points generate: \n";
      cin >> points_num;     
      cout << "Enter a positive number for the amount of threads generate: \n";
      cin >> threads_num;
    } while (points_num <= 0 || threads_num <=0); 
    
    int s;
    threads.resize(threads_num);
    pthread_attr_t attr; 
    pthread_attr_init(&attr); 
    cout << "---------------------" << endl;
    cout << "Created " << threads_num << " threads" << endl;
    for (size_t i = 0; i < threads_num; i++) {
        s = pthread_create(&threads[i], &attr, count,  (void *) i);
    }
}

void thread_join(){
    int s;
    for (size_t i = 0; i < threads_num; i++) {
        s = pthread_join(threads[i], nullptr);
    }
    pthread_mutex_destroy(&mutex);
    threads.resize(0);
}



int main(int argc, char const *argv[])
{
    double pi; 
    thread_create(); 
    thread_join(); 
    pi = (4.0 * (double)total_pts) / ((double)(points_num/threads_num) * threads_num);
    cout << "The approximate value of pi: " << pi << endl; 
    cout << "---------------------" << endl;
    return 0;
}

