#include <cstdint>
#include <iostream>
#include <fstream>
#define MAXLEN 100
#ifndef LENGTH
#define LENGTH 3
#endif
int16_t lab1(int16_t a, int16_t b) {
	// initialize
	// calculation
	// return value
}
int16_t lab2(int16_t p, int16_t q, int16_t n) {
	// initialize
	// calculation
	// return value
}
int16_t lab3(int16_t n, char s[]) {
	// initialize
	// calculation
	// return value
}
void lab4(int16_t score[], int16_t* a, int16_t* b) {
	// initialize
	// calculation
	// return value
}
int main() {
	std::fstream file;
	file.open("test.txt", std::ios::in);
	// lab1
	int16_t a = 0, b = 0;
	for (int i = 0; i < LENGTH; ++i) {
		file >> a >> b;
		std::cout << lab1(a, b) << std::endl;
	}
	// lab2
	int16_t p = 0, q = 0, n = 0;
	for (int i = 0; i < LENGTH; ++i) {
		file >> p >> q >> n;
		std::cout << lab2(p, q, n) << std::endl;
	}
	// lab3
	char s[MAXLEN];
	for (int i = 0; i < LENGTH; ++i) {
		file >> n >> s;
		std::cout << lab3(n, s) << std::endl;
	}
	// lab4
	int16_t score[16];
	for (int i = 0; i < LENGTH; ++i) {
		for (int j = 0; j < 16; ++j) {
			file >> score[j];
		}
		lab4(score, &a, &b);
		for (int j = 0; j < 16; ++j) {
			std::cout << score[j] << " ";
		}
		std::cout << std::endl << a << " " << b << std::endl;
	}
	file.close();
	return 0;
}