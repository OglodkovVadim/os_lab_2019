#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <getopt.h>

#define MAX_THREADS 10

typedef struct {
    int start;
    int end;
    int mod;
    int result;
} ThreadArgs;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *calculateFactorial(void *args) {
    ThreadArgs *threadArgs = (ThreadArgs *)args;
    int start = threadArgs->start;
    int end = threadArgs->end;
    int mod = threadArgs->mod;
    int result = 1;

    for (int i = start; i <= end; i++) {
        result = (result * i);
    }

    pthread_mutex_lock(&mutex);
    threadArgs->result = result;
    printf("Thread %lu: result = %d\n", pthread_self(), threadArgs->result);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int num = 0, numThreads = 1, mod = 10;

    // Обработка аргументов командной строки
    int option;
    while ((option = getopt(argc, argv, "k:p:m:")) != -1) {
        switch (option) {
            case 'k':
                num = atoi(optarg);
                break;
            case 'p':
                numThreads = atoi(optarg);
                break;
            case 'm':
                mod = atoi(optarg);
                break;
            default:
                printf("Использование: %s -k <исходное_число> -p <число_потоков> -m <модуль>\n", argv[0]);
                return 1;
        }
    }

    if (num == 0 || numThreads <= 0 || mod <= 0) {
        printf("Использование: %s -k <исходное_число> -p <число_потоков> -m <модуль>\n", argv[0]);
        return 1;
    }

    if (numThreads > MAX_THREADS) {
        printf("Слишком много потоков. Уменьшите количество потоков до %d\n", MAX_THREADS);
        return 1;
    }

    pthread_t threads[MAX_THREADS];
    ThreadArgs threadArgs[MAX_THREADS];

    // Распределение диапазонов для каждого потока
    int chunk = num / numThreads;
    for (int i = 0; i < numThreads; i++) {
        threadArgs[i].start = i * chunk + 1;
        threadArgs[i].end = (i == numThreads - 1) ? num : (i + 1) * chunk;
        threadArgs[i].mod = mod;
        pthread_create(&threads[i], NULL, calculateFactorial, (void *)&threadArgs[i]);
    }

    // Ожидание завершения потоков
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Вычисление и вывод общего результата
    int finalResult = 1;
    for (int i = 0; i < numThreads; i++) {
        finalResult = (finalResult * threadArgs[i].result);
    }

    printf("Результат: %d\n", finalResult);
    printf("Результат по модулю %d: %d\n", mod, finalResult  % mod);

    return 0;
}
