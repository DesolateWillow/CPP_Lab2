#include <iostream>
#include <vector>
#include <thread>


void myInit(std::vector<int>& vector, int start, int end) {
	for (int i = start; i < end; i++)
		vector.at(i) = rand() % 1001;
}


int main() {
	// Линейная инициализация через main(): 38.749
	// Линейная инициализация через функцию: 26.929
	// Параллельная инициализация в 2 потока: 19.02
	// Инициализация на всех ядрах: 0.001
	system("chcp 1251");
	srand(static_cast<int>(time(0)));

	std::vector<int> vect(1'000'000'000);
	time_t timer(clock());

	size_t elements = vect.size() / std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	
	for (int i = 0; i < threads.size(); i++)
		threads.emplace_back(myInit, std::ref(vect), elements * i, elements * (i + 1));

	for (std::thread& th : threads)
		th.join();

	std::cout << (clock() - timer) / 1000.0;
}
