#ifndef TORCEDORES_H_INCLUDED
#define TORCEDORES_H_INCLUDED

#include <cstdlib> // para a função rand()
#include <iostream>
#include "ListaEncadeada.h"
#include "Messages.h"

using namespace std;

struct Fan {
    int Type; // 1 para socio e 0 para normal
    int UnitOfTime; // Propriedade para a unidade de tempo
};

// Extensão do "cout", para que ele possibilite a exibição da struct Fan, sem ter que colocar valor por valor no cout
ostream& operator<<(ostream& os, Fan fan) {
    cout << "( ";

    if (fan.Type == 1) cout << " Partner ";
    else cout << " Normal ";

    cout << fan.UnitOfTime << " )";

    return os;
}

// Função para achar a fila com menos torcedores
// Essa funçao retorná o ponteiro da Fila com menos torcedores, ou seja, ao alterar esse valor de retorno, será alterado na lista em que a fila está contida
TFila<Fan>* FindQueueWithFewerFans(Tlista<TFila<Fan>>& ticketWindows) {
    TElemento<TFila<Fan>>* nav = nullptr; // Criação do objeto de navegação
    nav = ticketWindows.inicio; // navegação recebe o ínicio da lista como valor incicial

    int counter = 0; // Contador para podermos definir um valor inicial para a queue com menos torcedores
    TFila<Fan>* queueWithFewerFans = nullptr;

    while (nav != nullptr) { // Laço para percorrer todos os valores da lista
        if (tamanhoFila(nav->dado) == 0) return &(nav->dado); // Caso a fila não tenha torcedor, ela será a fila com menos torcedor retornada

        if (counter == 0) { // Caso seja a primeira iteração do loop, o valor inicial da fila com menos torcedores será o primeiro valor do loop de iteração
            queueWithFewerFans = &(nav->dado);
        }

        // Caso haja menos torcedores na iteração atual do que no objeto que deveria guardar a fila com o menor número de torcedores, 
        // a fila com menor torcedores será a atual
        if (tamanhoFila(nav->dado) < tamanhoFila(*queueWithFewerFans)) 
            queueWithFewerFans = &(nav->dado);

        nav = nav->proximo; // Passa para o próximo objeto dentro da lista encadeada
        counter++;
    }

    return queueWithFewerFans; // Ao final da iteração, haverá nessa variável a fila com menos torcedores
}

// Função responsável por setar o torcedor sócio criado na fila com menos torcedores
void SetQueueForPartner(Tlista<TFila<Fan>>& partnerTicketWindows, Tlista<TFila<Fan>>& normalTicketWindows, Fan fan) {
   TFila<Fan>* partnerQueueWithFewerFans = FindQueueWithFewerFans(partnerTicketWindows); // Pega a fila dos guiches dos socios com menos torcedores
   TFila<Fan>* normalQueueWithFewerFans = FindQueueWithFewerFans(normalTicketWindows); // Pega a fila dos guiches normais com menos torcedores

    if (tamanhoFila(*partnerQueueWithFewerFans) > tamanhoFila(*normalQueueWithFewerFans)) { // Se o guiche dos socios tiver mais gente que o guiche normal, o torcedor irá para o guiche normal 
        queueInsereFim(*normalQueueWithFewerFans, fan);

        return;
    }
    
    queueInsereFim(*partnerQueueWithFewerFans, fan); // Caso o guiche dos socios tenha menos gente, o torcedor irá para o guiche dos socios
}

// Função responsável por setar o torcedor normal na fila com menos torcedores
void SetQueueForNormal(Tlista<TFila<Fan>>& normalTicketWindows, Fan fan) {
    TFila<Fan>* normalQueueWithFewerFans = FindQueueWithFewerFans(normalTicketWindows); // Pega a fila dos guiches normais com menos torcedores

    queueInsereFim(*normalQueueWithFewerFans, fan); // Seta o torcedor na fila com menos gente
}

// Função para definir o tipo de torcedor gerado
// Função responsável pela probabilidade do torcedor ser sócio
int SetFanType() {
    int random = rand() % 100 + 1;  // Será gerado um número inteiro aleatório de 1 até 100

    if (random <= 5) return 1; // Caso o número seja menor que ou igual a 5, o torcedor será do tipo sócio

    return 0; // Caso não, o torcedor será do tipo normal
}

// Função para definir a Unidade de Tempo do torcedor do tipo sócio
// Função responsável pela definição da probabilidade do sócio ter a unidade de tempo mais curta
int SetPartnerUnitOfTime() {
    int random = rand() % 100 + 1;  // Será gerado um número inteiro aleatório de 1 até 100

    if(random <= 85) return 1; // Caso o número seja menor que ou igual a 85, o torcedor terá apenas uma unidade de tempo
   
    return 2; // Caso não, o torcedor terá duas unidades de tempo
}

// Função para definir a Unidade de Tempo do torcedor do tipo normal
int SetNormalUnitOfTime() {
    int random = rand() % 100 + 1; // Será gerado um número inteiro aleatório de 1 até 100

    if(random <= 25) return 1; // Caso o número seja menor que ou igual a 25, o torcedor terá apenas uma unidade de tempo
    else if(random <= 55) return 2; // Caso o número seja menor que ou igual a 55, o torcedor terá duas unidades de tempo
    return 3; // Caso seja maior que 55, será 3 unidades de tempo
}

// Função para verificar se o torcedor é do tipo sócio
bool FanIsPartner(int fanType) {
    if (fanType == 1) return true; // Caso ele seja sócio retornará verdadeira

    return false; // Caso seja normal, retornará falso
}

// Função para a geração de um torcedor
Fan CreateFan() {
    Fan fan; // Instanciação de um torcedor

    fan.Type = SetFanType(); // Definindo o tipo do torcedor, se ele será normal ou sócio

    if (FanIsPartner(fan.Type)) fan.UnitOfTime = SetPartnerUnitOfTime(); // Caso ele seja sócio, o unidade de tempo dele será baseado no tempo dos sócios
    else fan.UnitOfTime = SetNormalUnitOfTime(); // Caso ele não seja sócio, a unidade de tempo será baseado nos valores padrões

    return fan; // Retorno do torcedor criado
}

// Função responsável pela criação e aplicação do torcedor na fila mais curta
void AddFansInTicketWindows(
    Tlista<TFila<Fan>>& partnerTicketWindows, // Recebemos o endereço de memória da lista de guiches de socios, ou seja, toda alteração feita nela será definitiva
    Tlista<TFila<Fan>>& normalTicketWindows) // Recebemos o endereço de memória da lista de guiches normais, ou seja, toda alteração feita nela será definitiva
{
    Fan fan = CreateFan(); // Instanciação do novo torcedor

    if (FanIsPartner(fan.Type)) SetQueueForPartner(partnerTicketWindows, normalTicketWindows, fan); // Caso o torcedor seja sócio, ele poderá participar de ambas as filas, escolhendo assim a mais curta de ambas
    else SetQueueForNormal(normalTicketWindows, fan); // Caso o torcedor não seja sócio, ele apenas poderá participar dos guiches normais
}

// Função responsável por printar os Guiches e suas filas
void PrintTicketWindowList(Tlista<TFila<Fan>> ticketWindows) {
    TElemento<TFila<Fan>>* listNav; // Instanciação do objeto de navegação da lista
    listNav = ticketWindows.inicio; // Definindo o valor inicial como o ínicio da lista

    int index = 1; // Index para identificação do Guiche
    while (listNav != nullptr) { // Laço para chegar até o final da lista
        cout << "Guiche(" << index << "): ";
        
        if (tamanhoFila(listNav->dado) == 0) { // Caso não haja ningúem na fila, será imprimido a mensagem "Vazia"
            cout << "Vazia" << endl;

            index++; // Index é aumentado
            listNav = listNav->proximo; // Objeto de navegação recebe o próximo da lista
            continue;
        }

        TElementoF<Fan>* queueNav; // Instanciação do objeto de navegação da fila
        queueNav = listNav->dado.comeco; // Definindo o valor inicial como o ínicio da fila
        while (queueNav != nullptr){ // Laço para chegar até o final da fila
            cout << queueNav->dado; // Exibição do torcedor que está na fila, para isso que utilizamos a extensão do cout

            queueNav = queueNav->proximo; // Objeto de navegação recebe o próximo da lista
        }

        cout << endl;
        listNav = listNav->proximo;
        index++;
    }
}

// Função responsável pela exibição de todos os guiches
void PrintTicketWindows(
    Tlista<TFila<Fan>> partnerTicketWindows, // Cópia da lista dos guiches. Como não será necessário a manipulação dessa lista, n existe necessidade de passar o endereço de memória
    Tlista<TFila<Fan>> normalTicketWindows) 
{
    system("cls");

    // Print dos guiches dos sócios
    cout << "~~~~~~ Filas de guiches socio-torcedor ~~~~~~" << endl << endl;
    PrintTicketWindowList(partnerTicketWindows);

    cout << endl << endl;

    // Print dos guiches normais
    cout << "~~~~~~ Filas de guiches normal ~~~~~~" << endl << endl;
    PrintTicketWindowList(normalTicketWindows);
}

// Função responsável pela diminuição da Unidade de Tempo do torcedor no início da fila
void DecrementUnitOfTimeFromList(Tlista<TFila<Fan>>& ticketWindows) { // Recebemos o endereço de memória para poder manipular a lista
    TElemento<TFila<Fan>>* nav; // Instanciação do objeto de navegação da lista
    nav = ticketWindows.inicio; // Definindo o valor inicial como o ínicio da lista

    while (nav != nullptr) { // Laço para percorrer todos os itens da lista
        if (tamanhoFila(nav->dado) == 0) { // Caso a fila não possua torcedores, irá para o próximo item da lista
            nav = nav->proximo; // Objeto de navegação recebe o próximo da lista
            continue;
        }

        nav->dado.comeco->dado.UnitOfTime--; // Diminuição de 1, do valor de Unidade de Tempo do torcedor.

        if (nav->dado.comeco->dado.UnitOfTime > 0) { // Caso o torcedor ainda possua Unidade de Tempo, ele irá para o próximo itemm de iteração
            nav = nav->proximo;
            continue;
        }

        dequeueRemoveInicio(nav->dado); // Caso a Unidade de Tempo do tocedor seja zero, ele será removido da fila
    }
}

// Função para pegar os torcedores que sobraram na fila
int GetRemainFansInQueue(Tlista<TFila<Fan>> ticketWindows)
{
    TElemento<TFila<Fan>>* listNav; // Instanciação do objeto de navegação da lista
    listNav = ticketWindows.inicio; // Definindo o valor inicial como o ínicio da lista

    int fansTotal = 0; // Contador para saber o total torcedors dos guiches
    while (listNav != nullptr) { // Laço para percorrer todos os itens da lista
        fansTotal += tamanhoFila(listNav->dado); // Acrescenta o número de torcedores da fila no contador

        listNav = listNav->proximo; // Objeto de navegação recebe o próximo da lista
    }

    return fansTotal; // Retorna o total de torcedores da lista dos guiches
}

// Função para retornar a média dos torcedores que sobraram
float GetRemainFansInQueues(
    Tlista<TFila<Fan>> partnerTicketWindows,
    Tlista<TFila<Fan>> normalTicketWindows,
    int totalPartnerTicketsWindows,
    int totalNormalTicketsWindows) 
{
    int partnerFansTotal = GetRemainFansInQueue(partnerTicketWindows); // Pega os torcedores que sobrar de todos os guiches do tipo sócio
    int normalFansTotal = GetRemainFansInQueue(normalTicketWindows); // Pega os torcedores que sobrar de todos os guiches do tipo normal

    return (partnerFansTotal + normalFansTotal) / (totalPartnerTicketsWindows + totalNormalTicketsWindows * 1.0); // retorna a média deles
}

void StartService(
    Tlista<TFila<Fan>>& partnerTicketWindows,
    Tlista<TFila<Fan>>& normalTicketWindows,
    int totalTime,
    int searchTicketWindow) 
{
    // Laço para fazer o número de iterações que o usuário requisitou
    for (int i = 0; i < totalTime; i++) {
        PrintTicketWindows(partnerTicketWindows, normalTicketWindows); // Print dos guiches e suas filas
        cout << endl;
        
        PrintPressKeyMessage(); // Print para apertar e passar a próxima unidade de tempo
        
        DecrementUnitOfTimeFromList(normalTicketWindows); // Decremento de unidade do primeiro torcedor da fila dos guiches normais
        DecrementUnitOfTimeFromList(partnerTicketWindows); // Decremento de unidade do primeiro torcedor da fila dos guiches de socios

        for (int j = 0; j < searchTicketWindow; j++) // Laço para adicionar o número de torcedores que o usuário requisitou
            AddFansInTicketWindows(partnerTicketWindows, normalTicketWindows);
    
        if (i == totalTime - 1) { // Condição para printar o valor final dos guiches e filas
            PrintTicketWindows(partnerTicketWindows, normalTicketWindows);
            cout << endl;
        }
    }    
}

// Função para exibir a média dos torcedores que sobraram
void GetAverateFansRemaining(
    Tlista<TFila<Fan>> partnerTicketWindows,
    Tlista<TFila<Fan>> normalTicketWindows,
    int totalPartnerTicketsWindows,
    int totalNormalTicketsWindows) {
    cout << endl << endl;

    cout << "Em média sobraram ";

    cout << GetRemainFansInQueues( // Função para pegar a média de torcedores que sobraram
        partnerTicketWindows,
        normalTicketWindows,
        totalPartnerTicketsWindows,
        totalNormalTicketsWindows);

    cout << " torcedores por guiche" << endl << endl;

    system("pause");
    system("cls");
}
#endif // TORCEDORES_H_INCLUDED
