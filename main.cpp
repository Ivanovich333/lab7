#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>
#include <algorithm>

// Функция для сортировки методом прямого выбора
void selection_sort(std::vector<double>& arr, int start, int end, const std::string& thread_name) {
    for (int i = start; i < end - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < end; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[i], arr[min_idx]);
    }
    // Печать отсортированного массива
    for (int i = start; i < end; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Задержка 10 мс
        std::cout << thread_name << std::endl;
        std::cout << arr[i] << std::endl;
    }
}

int main() {
    const int SIZE = 20;
    std::vector<double> array(SIZE);

    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);

    // Заполнение массива случайными числами
    for (int i = 0; i < SIZE; ++i) {
        array[i] = dis(gen);
    }

    // Создание потоков
    std::thread thread1(selection_sort, std::ref(array), 0, SIZE / 2, "thread1");
    std::thread thread2(selection_sort, std::ref(array), SIZE / 2, SIZE, "thread2");

    // Ожидание завершения первых двух потоков
    thread1.join();
    thread2.join();

    // Третий поток сортирует уже частично отсортированный массив
    std::thread thread3(selection_sort, std::ref(array), 0, SIZE, "thread3");
    thread3.join();

    // Главный поток сообщает об окончании работы
    std::cout << "Main thread: Работа завершена." << std::endl;

    return 0;
}
