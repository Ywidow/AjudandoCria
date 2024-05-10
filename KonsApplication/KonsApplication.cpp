#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Fila.h"
#include "Torcedores.h"
#include "ListaEncadeada.h"
#include "Messages.h"

using namespace std;

// Função para inicializar as filas dentro da lista
void StartQueues(int sizeOfLinkedList, Tlista<TFila<Fan>>& linkedList) {
    for (int i = 0; i < sizeOfLinkedList; i++) { // Para cada guiche uma fila é criada e adicionada no fim da lista
        TFila<Fan> ticketWindow;
        inicializaFila(ticketWindow);

        insereFim(linkedList, ticketWindow);
    }
}

// Função para pegar os dados fornecidos pelo usuário
int GetApplicationDependencies(string text) { // texto  é passado por parametro para mostra no console
    int value;
    
    do{
        cout << text;
        cin >> value;
        cout << endl;

        if (value < 0) PrintInvalidValueMessage(); // Validação para valores negativos

    } while (value < 0); // O escopo de cima será iterado até o valor ser positivo

    return value;
}

int main()
{
    srand(time(NULL));

    // Definindo quantidade de guiches de socio torcedor
    int qtnGuichesSocio = GetApplicationDependencies("Qual a quantidade de guiches para socio-torcedores?: ");

    // Definindo quantidade de guiches normais
    int qtnGuichesNormal = GetApplicationDependencies("Qual a quantidade de guiches normais?: ");

    // Definindo a carga inicial de torcedores
    int cargaInicial = GetApplicationDependencies("Qual a quantidade de pessoas iniciais?: ");

    // Definindo a quantidade de pessoas que serão adicionadas por unidade de tempo
    int qtnPessoasProcurandoGuichePorTempo = GetApplicationDependencies("Qual a quantidade de pessoas procurando guiches?: ");

    // Definindo tempo estimulado para a aplicação rodar
    int tempoSimulado = GetApplicationDependencies("Qual a quantidade de tempo?: ");

    if (qtnGuichesNormal == 0 && qtnGuichesSocio == 0) { // Validação para caso não tenha guiche normal, nem guiche para sócios
        PrintNoTicketWindowsMessage();

        return 0;
    }

    Tlista<TFila<Fan>> partnerTicketWindows;
    Tlista<TFila<Fan>> normalTicketWindows;

    inicializaLista(partnerTicketWindows); // Inicializador da lista partnerTicketWindows
    StartQueues(qtnGuichesSocio, partnerTicketWindows); // Inicializador das filas da lista partnerTicketWindows

    inicializaLista(normalTicketWindows); // Inicializador da lista normalTicketWindows
    StartQueues(qtnGuichesNormal, normalTicketWindows); // Inicializador das filas da lista normalTicketWindows

    // Criação dos torcedores iniciais
    for (int i = 0; i < cargaInicial; i++) 
        AddFansInTicketWindows(partnerTicketWindows, normalTicketWindows);

    // Início de serviço de atendimento
    StartService(
        partnerTicketWindows,
        normalTicketWindows,
        tempoSimulado,
        qtnPessoasProcurandoGuichePorTempo);

    // Função para buscar a média de torcedores que ficaram na fila após a aplicação ser encerrada
    GetAverateFansRemaining(
        partnerTicketWindows,
        normalTicketWindows,
        qtnGuichesSocio,
        qtnGuichesNormal);

    PrintByeByeMessage(); // Função para 

    return 0;
}
