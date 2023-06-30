#include<stdio.h>

int main() {
	int input = 0;
	printf("what|?(1/0)>:");
	scanf_s("%d", &input);

	printf("input: %d\n", input);
	if (input == 1) {
		printf("good\n");
	}
	else {
		printf("bad\n");
	}
}