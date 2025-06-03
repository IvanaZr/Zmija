#define _CRT_SECURE_NO_WARNINGS

#include "snake.c"

int main() {

	char key;

	Print();

	system("cls");

	length = 5;

	head.x = 25;

	head.y = 20;

	head.direction = RIGHT;

	Boarder();

	Food(); //to generate food coordinates initially

	life = 3; //number of extra lives

	bend[0] = head;

	Move();   //initialing initial bend coordinate

	return 0;
}
