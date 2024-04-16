#include <pthread.h>
#include "caltrain.h"


// With two variables
// void station_init(struct station *station)
// {
//     station->waiting_passengers = 0;
//     station->empty_seats = 0;

//     pthread_mutex_init(&station->lock, NULL); 
//     pthread_cond_init(&station->train_comes_cond, NULL);
//     pthread_cond_init(&station->train_leaves_cond, NULL);
// }

// void station_load_train(struct station *station, int count)
// {
//     pthread_mutex_lock(&station->lock);
//     /* Multiply by 2 as in order to be seated, passenger should board the train then sit down */
//     station->empty_seats = count * 2; 
//     pthread_cond_signal(&station->train_comes_cond);
//     // Wait until full train or no waiting passengers
//     while(station->waiting_passengers > 0 && station->empty_seats > 0)
//     {    
//         pthread_cond_wait(&station->train_leaves_cond, &station->lock);
//     }
//     station->empty_seats = 0;
//     pthread_mutex_unlock(&station->lock);
// }

// void station_wait_for_train(struct station *station)
// {
//     pthread_mutex_lock(&station->lock);
//     station->waiting_passengers++;
//     while(station->empty_seats == 0 || station->empty_seats % 2 == 1) 
//     {
//         pthread_cond_wait(&station->train_comes_cond, &station->lock);
//     }
//     station->empty_seats --; // Passenger boarded the train
//     pthread_mutex_unlock(&station->lock);
// }

// void station_on_board(struct station *station)
// {
//     pthread_mutex_lock(&station->lock);
//     station->empty_seats --; // Passenger sat down
//     station->waiting_passengers--;
//     if(station->waiting_passengers == 0 || station->empty_seats == 0)
//         pthread_cond_signal(&station->train_leaves_cond);
//     pthread_cond_signal(&station->train_comes_cond); // Signal for the next passenger to board
//     pthread_mutex_unlock(&station->lock);
// }




// With three variables

void station_init(struct station *station)
{
    station->boarders = 0;
    station->waiting_passengers = 0;
    station->empty_seats = 0;

    pthread_mutex_init(&station->lock, NULL); 
    pthread_cond_init(&station->train_comes_cond, NULL);
    pthread_cond_init(&station->train_leaves_cond, NULL);
}

void station_load_train(struct station *station, int count)
{
    pthread_mutex_lock(&station->lock);
    station->empty_seats = count;
    pthread_cond_broadcast(&station->train_comes_cond);
    // Wait until all passengers have sat down, full train or no waiting passengers
    while((station->waiting_passengers > 0 && station->empty_seats > 0) || station->boarders > 0)
    {    
        pthread_cond_wait(&station->train_leaves_cond, &station->lock);
    }
    station->empty_seats = 0;
    pthread_mutex_unlock(&station->lock);
}

void station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&station->lock);
    station->waiting_passengers++;
    // Wait until at least one seat is empty in the train
    while(station->empty_seats == 0)
    {
        pthread_cond_wait(&station->train_comes_cond, &station->lock);
    }
    station->empty_seats--;
    station->waiting_passengers--;
    station->boarders++;
    pthread_mutex_unlock(&station->lock);
}

void station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->lock);
    station->boarders--;
    if((station->empty_seats == 0 || station->waiting_passengers == 0) && station->boarders == 0)
    {
        pthread_cond_signal(&station->train_leaves_cond);
    }
    pthread_mutex_unlock(&station->lock);
}