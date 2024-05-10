#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Fila.h"
#include "Torcedores.h"
#include "ListaEncadeada.h"
#include "Messages.h"

using namespace std;

void StartQueues(int sizeOfLinkedList, Tlista<TFila<Fan>>& linkedList) {
    for (int i = 0; i < sizeOfLinkedList; i++) {
        TFila<Fan> ticketWindow;
        inicializaFila(ticketWindow);

        insereFim(linkedList, ticketWindow);
    }
}

int GetApplicationDependencies(string text) {
    int value;

    do{
        cout << text;
        cin >> value;
        cout << endl;

        if (value < 0) PrintInvalidValueMessage();

    } while (value < 0);

    return value;
}

int main()
{
    srand(time(NULL));

    int qtnGuichesSocio = GetApplicationDependencies("Qual a quantiade de guiches para socio-torcedores?: ");

    int qtnGuichesNormal = GetApplicationDependencies("Qual a quantiade de guiches normais?: ");

    int cargaInicial = GetApplicationDependencies("Qual a quantiade de pessoas iniciais?: ");

    //int qtnPessoasProcurandoGuichePorTempo = GetApplicationDependencies("Qual a quantiade de pessoas procurando guiches?: ");

    //int tempoSimulado = GetApplicationDependencies("Qual a quantiade de tempo?: ");

    Tlista<TFila<Fan>> partnerTicketWindows;
    Tlista<TFila<Fan>> normalTicketWindows;

    inicializaLista(partnerTicketWindows);
    inicializaLista(normalTicketWindows);

    StartQueues(qtnGuichesSocio, partnerTicketWindows);
    StartQueues(qtnGuichesNormal, normalTicketWindows);

    // Adiciona torcedores às filas
    for (int i = 0; i < cargaInicial; i++)
        AddFansInTicketWindows(
            partnerTicketWindows,
            normalTicketWindows,
            qtnGuichesSocio,
            qtnGuichesNormal
        );

    // Exibe o estado inicial das filas
    cout << "Estado inicial das filas:" << endl;
    PrintTicketWindows(partnerTicketWindows, normalTicketWindows);
    cout << endl;

    // Realiza o atendimento dos torcedores nas filas
    // realizarAtendimento(guicheSocio, guicheNormal, qtnGuichesSocio, qtnGuichesNormal, tempoSimulado, qtnPessoasProcurandoGuichePorTempo);


    return 0;
}