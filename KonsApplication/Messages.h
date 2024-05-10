#ifndef MESSAGES
#define MESSAGES

#include <stdlib.h>
#include <iostream>

using namespace std;

// Função para exibir mensagem de valor inválido
void PrintInvalidValueMessage() {
	system("cls");

	cout << "Invalid Value..." << endl;

	system("pause");
	system("cls");
};

// Função para exibir mensagem de continuação
void PrintPressKeyMessage() {
	cout << "Pressione enter para continuar..." << endl;
	system("pause");
}

// Função para exibir mensagem de adeus
void PrintByeByeMessage() {
	cout << "Obrigado Pela Preferência!!!" << endl;
	system("pause");
	system("cls");
}

// Função para exibir mensagem que não existe guiches no momento
void PrintNoTicketWindowsMessage() {
	system("cls");
	
	cout << "Infelizmente não há guiches param serem utilizados..." << endl;

	system("pause");
	system("cls");
}

#endif 
