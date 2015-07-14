#ifndef CHECKER_HH
#define CHECKER_HH 1

#include <stdlib.h>
#include <curl/curl.h>
#include <pthread.h>
#include <unistd.h>

#define CHECKER_THREAD_INDEX 2
#define CHECKER_DELAY_INDEX 1000

int *status;

// Данные об URL
struct thread_arg {
	char *url;
	int status;
};

typedef struct thread_arg thread_arg;

// Структура для потока
struct thread_array {
	thread_arg **args;
	int delay, args_count;
	int status;
};

typedef struct thread_array thread_array;

static size_t write_data(char *ptr, size_t size, size_t nmemb, char* data) {
	return size * nmemb;
}

void *thread_func(void *argument) {
	int i;
	CURL *curl;
	CURLcode res;
	long http_code = 0;
	char tmp_buf[1];
	thread_array *arg = (thread_array *) argument;

	usleep(arg->delay * 1000);

	for (i = 0; i < arg->args_count; i++) {
		curl = curl_easy_init();
		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, arg->args[i]->url);
			curl_easy_setopt(curl, CURLOPT_HEADER, 1);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, tmp_buf);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

			res = curl_easy_perform(curl);
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

			curl_easy_cleanup(curl);
		}
		arg->args[i]->status = http_code;
	}
	arg->status = 1;
}

void check_all_urls(thread_arg *urls, int array_size) {
	int i, j, check, flag, plus = 1;
	int col_threads = sysconf(_SC_NPROCESSORS_ONLN) * CHECKER_THREAD_INDEX;
	thread_array *url_array;
	pthread_t *thread;

	if (col_threads > array_size) {
		col_threads = array_size;
		plus = 0;
	}

	url_array = malloc(col_threads * sizeof(thread_array));
	thread = malloc(col_threads * sizeof(pthread_t));

	// Текущая позиция в массиве URL'ов
	check = 0;

	// Подсчитываем количество URL для каждого потока
	for (i = 0; i < col_threads; i++) {
		url_array[i].status = 0;
		url_array[i].delay = i * CHECKER_DELAY_INDEX;
		url_array[i].args_count = col_threads / array_size + plus;
		if (array_size % col_threads > i)
			url_array[i].args_count++;
		url_array[i].args = (thread_arg **) malloc(url_array[i].args_count * sizeof(thread_arg));
		for (j = 0; j < url_array[i].args_count; j++)
			url_array[i].args[j] = &urls[check++];

		// Стартуем новый поток
		pthread_create(&thread[i], NULL, thread_func, &url_array[i]);
	}

	// Ждём окончания работы потоков
	for (i = 0; i < col_threads; i++) {
		pthread_join(thread[i], NULL);
	}

	for (i = 0; i < col_threads; i++) {
		free(url_array[i].args);
	}
	free(url_array);
	free(thread);
}

#endif

