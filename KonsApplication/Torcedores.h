#ifndef TORCEDORES_H_INCLUDED
#define TORCEDORES_H_INCLUDED

#include <cstdlib> // para a função rand()
#include <iostream>
#include "ListaEncadeada.h"
#include "Messages.h"

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
    Tlista<TFila<Fan>>& normalTicketWindows)
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
    system("cls");

    cout << "~~~~~~ Filas de guiches socio-torcedor ~~~~~~" << endl << endl;
    PrintTicketWindowList(partnerTicketWindows);

    cout << endl << endl;

    cout << "~~~~~~ Filas de guiches normal ~~~~~~" << endl << endl;
    PrintTicketWindowList(normalTicketWindows);
}

void DecrementUnitOfTimeFromList(Tlista<TFila<Fan>>& ticketWindows) {
    TElemento<TFila<Fan>>* nav;
    nav = ticketWindows.inicio;

    while (nav != nullptr) {
        if (tamanhoFila(nav->dado) == 0) {
            nav = nav->proximo;
            continue;
        }

        nav->dado.comeco->dado.UnitOfTime--;

        if (nav->dado.comeco->dado.UnitOfTime > 0) {
            nav = nav->proximo;
            continue;
        }

        dequeueRemoveInicio(nav->dado);
    }
}

int GetRemainFansInQueue(Tlista<TFila<Fan>> ticketWindows)
{
    TElemento<TFila<Fan>>* listNav;
    listNav = ticketWindows.inicio;

    int fansTotal = 0;
    while (listNav != nullptr) {
        fansTotal += tamanhoFila(listNav->dado);

        listNav = listNav->proximo;
    }

    return fansTotal;
}

float GetRemainFansInQueues(
    Tlista<TFila<Fan>> partnerTicketWindows,
    Tlista<TFila<Fan>> normalTicketWindows,
    int totalPartnerTicketsWindows,
    int totalNormalTicketsWindows) 
{
    int partnerFansTotal = GetRemainFansInQueue(partnerTicketWindows);
    int normalFansTotal = GetRemainFansInQueue(normalTicketWindows);

    return (partnerFansTotal + normalFansTotal) / (totalPartnerTicketsWindows + totalNormalTicketsWindows * 1.0);
}

void StartService(
    Tlista<TFila<Fan>>& partnerTicketWindows,
    Tlista<TFila<Fan>>& normalTicketWindows,
    int totalTime,
    int searchTicketWindow) 
{
    for (int i = 0; i < totalTime; i++) {
        PrintTicketWindows(partnerTicketWindows, normalTicketWindows);
        cout << endl;
        
        PrintPressKeyMessage();
        
        DecrementUnitOfTimeFromList(normalTicketWindows);
        DecrementUnitOfTimeFromList(partnerTicketWindows);

        for (int j = 0; j < searchTicketWindow; j++)
            AddFansInTicketWindows(partnerTicketWindows, normalTicketWindows);

        if (i == totalTime - 1) {
            PrintTicketWindows(partnerTicketWindows, normalTicketWindows);
            cout << endl;
        }
    }    
}

void GetAverateFansRemaining(
    Tlista<TFila<Fan>> partnerTicketWindows,
    Tlista<TFila<Fan>> normalTicketWindows,
    int totalPartnerTicketsWindows,
    int totalNormalTicketsWindows) {
    cout << endl << endl;

    cout << "Em média sobraram ";

    cout << GetRemainFansInQueues(
        partnerTicketWindows,
        normalTicketWindows,
        totalPartnerTicketsWindows,
        totalNormalTicketsWindows);

    cout << " torcedores por guiche" << endl << endl;

    system("pause");
    system("cls");
}
#endif // TORCEDORES_H_INCLUDED