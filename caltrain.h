#include <pthread.h>

struct station {
	int boarders;
    int waiting_passengers;
    int empty_seats;

    pthread_mutex_t lock;
    pthread_cond_t train_comes_cond ;
    pthread_cond_t train_leaves_cond;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);