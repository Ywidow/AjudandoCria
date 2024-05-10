#ifndef MESSAGES
#define MESSAGES

#include <stdlib.h>
#include <iostream>

using namespace std;

void PrintInvalidValueMessage() {
	system("cls");

	cout << "Invalid Value..." << endl;

	system("pause");
	system("cls");
};

void PrintPressKeyMessage() {
	cout << "Pressione enter para continuar..." << endl;
	system("pause");
}

void PrintByeByeMessage() {
	cout << "Obrigado Pela Preferência!!!" << endl;
	system("pause");
	system("cls");
}

void PrintNoTicketWindowsMessage() {
	system("cls");
	
	cout << "Infelizmente não há guiches param serem utilizados..." << endl;

	system("pause");
	system("cls");
}

#endif 