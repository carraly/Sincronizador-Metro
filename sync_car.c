#include "sync_car.h"
#include <pthread.h>

void station_init(struct station *station){
    pthread_mutex_init(&station->lock, NULL);
    pthread_cond_init(&station->car_arrived, NULL);
    pthread_cond_init(&station->car_full_or_done, NULL);
    station->remaining_seats = 0;
    station->waiting = 0;
    station->boarding = 0;
}

void station_load_car(struct station *station, int count){
    pthread_mutex_lock(&station->lock);

    if (count == 0 || station->waiting == 0) {
        pthread_mutex_unlock(&station->lock);
        return;
    }
    
    station->remaining_seats = count;
    pthread_cond_broadcast(&station->car_arrived);
    while (station->boarding != 0 || (station->remaining_seats != 0 && station->waiting > 0)) {
        pthread_cond_wait(&station->car_full_or_done, &station->lock);
    }

    station->remaining_seats = 0;
    pthread_mutex_unlock(&station->lock);
}

void station_wait_for_car(struct station *station){
    pthread_cond_wait(&station->car_arrived, &station->lock);
}

void station_on_board(struct station *station){

}