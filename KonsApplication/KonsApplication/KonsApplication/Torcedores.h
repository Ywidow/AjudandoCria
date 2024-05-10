#ifndef TORCEDORES_H_INCLUDED
#define TORCEDORES_H_INCLUDED

#include <cstdlib> // para a função rand()
#include <iostream>
#include "ListaEncadeada.h"

using namespace std;

struct Fan {
    int Type; // 1 para socio e 0 para normal
    int UnitOfTime;
};

ostream& operator<<(ostream& os, Fan fan) {
    cout << "( ";

    if (fan.Type == 1) cout << " Partner ";
    else cout << " Normal ";

    cout << fan.UnitOfTime << " )";

    return os;
}

TFila<Fan>* FindQueueWithFewerFans(Tlista<TFila<Fan>>& ticketWindows) {
    TElemento<TFila<Fan>>* nav = nullptr;
    nav = ticketWindows.inicio;

    int counter = 0;
    TFila<Fan>* queueWithFewerFans = nullptr;

    while (nav != nullptr) {
        if (tamanhoFila(nav->dado) == 0) return &(nav->dado);

        if (counter == 0) {
            queueWithFewerFans = &(nav->dado);
        }

        if (tamanhoFila(nav->dado) < tamanhoFila(*queueWithFewerFans))
            queueWithFewerFans = &(nav->dado);

        nav = nav->proximo;
        counter++;
    }

    return queueWithFewerFans;
}

void SetQueueForPartner(Tlista<TFila<Fan>>& partnerTicketWindows, Tlista<TFila<Fan>>& normalTicketWindows, Fan fan) {
   TFila<Fan>* partnerQueueWithFewerFans = FindQueueWithFewerFans(partnerTicketWindows);
   TFila<Fan>* normalQueueWithFewerFans = FindQueueWithFewerFans(normalTicketWindows);

    if (tamanhoFila(*partnerQueueWithFewerFans) > tamanhoFila(*normalQueueWithFewerFans)) {
        queueInsereFim(*normalQueueWithFewerFans, fan);

        return;
    }
    
    queueInsereFim(*partnerQueueWithFewerFans, fan);
}

void SetQueueForNormal(Tlista<TFila<Fan>>& normalTicketWindows, Fan fan) {
    TFila<Fan>* normalQueueWithFewerFans = FindQueueWithFewerFans(normalTicketWindows);

    queueInsereFim(*normalQueueWithFewerFans, fan);
}

int SetFanType() {
    int random = rand() % 100 + 1; 

    if (random <= 5) return 1; 

    return 0; 
}

int SetPartnerUnitOfTime() {
    int random = rand() % 100 + 1;

    if(random <= 85) return 1;
   
    return 2;
}

int SetNormalUnitOfTime() {
    int random = rand() % 100 + 1; 

    if(random <= 25) return 1;
    else if(random <= 55) return 2;
    return 3;
}

bool FanIsPartner(int fanType) {
    if (fanType == 1) return true;

    return false;
}

Fan CreateFan() {
    Fan fan;

    fan.Type = SetFanType();

    if (FanIsPartner(fan.Type)) fan.UnitOfTime = SetPartnerUnitOfTime();
    else fan.UnitOfTime = SetNormalUnitOfTime();

    return fan;
}

void AddFansInTicketWindows(
    Tlista<TFila<Fan>>& partnerTicketWindows,
    Tlista<TFila<Fan>>& normalTicketWindows,
    int partnerTickeWindowsSize,
    int normalTickeWindowsSize)
{
    Fan fan = CreateFan();

    if (FanIsPartner(fan.Type)) SetQueueForPartner(partnerTicketWindows, normalTicketWindows, fan);
    else SetQueueForNormal(normalTicketWindows, fan);
}

void PrintTicketWindowList(Tlista<TFila<Fan>> ticketWindows) {
    TElemento<TFila<Fan>>* listNav;
    listNav = ticketWindows.inicio;

    int index = 1;
    while (listNav != nullptr) {
        cout << "Guiche(" << index << "): ";
        
        if (tamanhoFila(listNav->dado) == 0) {
            cout << "Vazia" << endl;

            index++;
            listNav = listNav->proximo;
            continue;
        }

        TElementoF<Fan>* queueNav;
        queueNav = listNav->dado.comeco;
        while (queueNav != nullptr){
            cout << queueNav->dado;

            queueNav = queueNav->proximo;
        }

        cout << endl;
        listNav = listNav->proximo;
        index++;
    }
}

void PrintTicketWindows(
    Tlista<TFila<Fan>> partnerTicketWindows,
    Tlista<TFila<Fan>> normalTicketWindows) 
{

    cout << "~~~~~~ Filas de guiches socio-torcedor ~~~~~~" << endl << endl;
    PrintTicketWindowList(partnerTicketWindows);

    cout << endl << endl;

    cout << "~~~~~~ Filas de guiches normal ~~~~~~" << endl << endl;
    PrintTicketWindowList(normalTicketWindows);
}

//bool realizarAtendimento(TFila<torcedores> guicheSocio[], TFila<torcedores> guicheNormal[], int qtnGuichesSocio, int qtnGuichesNormal, int tempoSimulado, int qtnPessoasProcurandoGuichePorTempo) {
//    // Realiza o atendimento ao longo do tempo especificado
//    for (int tempo = 0; tempo < tempoSimulado; tempo++) {
//        cout << "Pressione Enter para atender o próximo torcedor...";
//        cin.get();
//
//        //         Adiciona torcedores às filas
//        //        for (int i = 0; i < qtnPessoasProcurandoGuichePorTempo; i++) {
//        //            adicionandoTorcedoresNosGuiches(guicheSocio, guicheNormal, qtnGuichesSocio, qtnGuichesNormal);
//        //        }
//
//                // Atendimento dos torcedores nas filas sócio-torcedor
//
//        if (tamanhoFila(guicheSocio[tempo]) > 0) {
//            torcedores torcedor = retornaPrimeiroElemento(guicheSocio[tempo]);
//            torcedor.unidadeTempo--;
//
//            // Remove o torcedor da fila se o atendimento for concluído
//            if (torcedor.unidadeTempo <= 0) {
//                dequeueRemoveInicio(guicheSocio[tempo]);
//            }
//            else {
//                // Atualiza o torcedor na fila
//                dequeueRemoveInicio(guicheSocio[tempo]);
//                queueInsereFim(guicheSocio[tempo], torcedor);
//            }
//        }
//
//
//        // Atendimento dos torcedores nas filas normais
//
//        if (tamanhoFila(guicheNormal[tempo]) > 0) {
//            torcedores torcedor = retornaPrimeiroElemento(guicheNormal[tempo]);
//            torcedor.unidadeTempo--;
//
//            // Remove o torcedor da fila se o atendimento for concluído
//            if (torcedor.unidadeTempo <= 0) {
//                dequeueRemoveInicio(guicheNormal[tempo]);
//            }
//            else {
//                // Atualiza o torcedor na fila
//                dequeueRemoveInicio(guicheNormal[tempo]);
//                queueInsereFim(guicheNormal[tempo], torcedor);
//            }
//        }
//        imprimirFilas(guicheSocio, guicheNormal, qtnGuichesSocio, qtnGuichesNormal);
//    }
//
// }

#endif // TORCEDORES_H_INCLUDED