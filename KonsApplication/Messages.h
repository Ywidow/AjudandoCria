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
	cout << "Obrigado Pela Prefer�ncia!!!" << endl;
	system("pause");
	system("cls");
}

void PrintNoTicketWindowsMessage() {
	system("cls");
	
	cout << "Infelizmente n�o h� guiches param serem utilizados..." << endl;

	system("pause");
	system("cls");
}

#endif 