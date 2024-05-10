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

    int qtnPessoasProcurandoGuichePorTempo = GetApplicationDependencies("Qual a quantiade de pessoas procurando guiches?: ");

    int tempoSimulado = GetApplicationDependencies("Qual a quantiade de tempo?: ");

    if (qtnGuichesNormal == 0 && qtnGuichesSocio == 0) {
        PrintNoTicketWindowsMessage();

        return 0;
    }

    Tlista<TFila<Fan>> partnerTicketWindows;
    Tlista<TFila<Fan>> normalTicketWindows;

    inicializaLista(partnerTicketWindows);
    StartQueues(qtnGuichesSocio, partnerTicketWindows);

    inicializaLista(normalTicketWindows);
    StartQueues(qtnGuichesNormal, normalTicketWindows);

    for (int i = 0; i < cargaInicial; i++)
        AddFansInTicketWindows(partnerTicketWindows, normalTicketWindows);

    StartService(
        partnerTicketWindows,
        normalTicketWindows,
        tempoSimulado,
        qtnPessoasProcurandoGuichePorTempo);

    GetAverateFansRemaining(
        partnerTicketWindows,
        normalTicketWindows,
        qtnGuichesSocio,
        qtnGuichesNormal);

    PrintByeByeMessage();

    return 0;
}