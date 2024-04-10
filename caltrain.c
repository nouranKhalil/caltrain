#include <pthread.h>
#include "caltrain.h"

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
    // // Wait until all passengers have sat down
    while(station->waiting_passengers > 0 && station->empty_seats > 0)
    {
        pthread_cond_broadcast(&station->train_comes_cond);
        pthread_cond_wait(&station->train_leaves_cond, &station->lock);
    }
    station->empty_seats = 0;
    pthread_mutex_unlock(&station->lock);
    // full train or empty waiting passengers
}

void station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&station->lock);
    station->waiting_passengers++;
    // wait until at least one seat is empty in a train
    while(station->empty_seats == 0)
    {
        pthread_cond_wait(&station->train_comes_cond, &station->lock);
    }
    station->empty_seats--;
    station->boarders++;
    pthread_mutex_unlock(&station->lock);
}

void station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->lock);
    station->boarders--;
    station->waiting_passengers--;
    if((station->empty_seats == 0 || station->waiting_passengers == 0) && station->boarders == 0)
    {
        pthread_cond_signal(&station->train_leaves_cond);
    }
    pthread_mutex_unlock(&station->lock);
}