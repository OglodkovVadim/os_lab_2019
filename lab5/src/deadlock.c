#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *threadFunction1(void *arg) {
    // Блокировка первого мьютекса
    pthread_mutex_lock(&mutex1);
    printf("Поток 1: Блокировка первого мьютекса\n");

    // Некоторая работа

    // Попытка заблокировать второй мьютекс (при этом первый мьютекс уже заблокирован)
    pthread_mutex_lock(&mutex2);
    printf("Поток 1: Блокировка второго мьютекса\n");

    // Некоторая работа

    // Разблокировка мьютексов
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    pthread_exit(NULL);
}

void *threadFunction2(void *arg) {
    // Блокировка второго мьютекса
    pthread_mutex_lock(&mutex2);
    printf("Поток 2: Блокировка второго мьютекса\n");

    // Некоторая работа

    // Попытка заблокировать первый мьютекс (при этом второй мьютекс уже заблокирован)
    pthread_mutex_lock(&mutex1);
    printf("Поток 2: Блокировка первого мьютекса\n");

    // Некоторая работа

    // Разблокировка мьютексов
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Создание потоков
    if (pthread_create(&thread1, NULL, threadFunction1, NULL) != 0 ||
        pthread_create(&thread2, NULL, threadFunction2, NULL) != 0) {
        perror("Ошибка при создании потоков");
        exit(EXIT_FAILURE);
    }

    // Ожидание завершения потоков
    if (pthread_join(thread1, NULL) != 0 || pthread_join(thread2, NULL) != 0) {
        perror("Ошибка при ожидании завершения потоков");
        exit(EXIT_FAILURE);
    }

    printf("Программа успешно завершена\n");

    return 0;
}
