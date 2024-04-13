#include<stdio.h>
#include<pthread.h>
#include"caltrain.h"

int main(){
    struct station station;
	station_init(&station);
    station_load_train(&station, 12);

    int i;
	const int total_passengers = 100;
	int passengers_left = total_passengers;
	for (i = 0; i < total_passengers; i++) {
		pthread_t tid;
		int ret = pthread_create(&tid, NULL, passenger_thread, &station);
		if (ret != 0) {
			// If this fails, perhaps we exceeded some system limit.
			// Try reducing 'total_passengers'.
			perror("pthread_create");
			exit(1);
		}
	}
}