#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

using namespace std;

#include <iostream>

template<typename TIPO>
struct TElementoF {
    TIPO dado;
    TElementoF<TIPO>* proximo;
};

template<typename TIPO>
struct TFila {
    TElementoF<TIPO>* comeco;
};

template<typename TIPO>
bool inicializaFila(TFila<TIPO>& f) {
    f.comeco = NULL;
    return true;
}

template<typename TIPO>
TElementoF<TIPO>* novoElementoFila(TIPO dado) {
    TElementoF<TIPO>* novo = new TElementoF<TIPO>;
    novo->dado = dado;
    novo->proximo = NULL;
    return novo;
}

template<typename TIPO>
bool queueInsereFim(TFila<TIPO>& f, TIPO dado) {
    TElementoF<TIPO>* nav = f.comeco;
    TElementoF<TIPO>* novo = novoElementoFila(dado);
    if (f.comeco != NULL) {
        while (nav->proximo != NULL) {
            nav = nav->proximo;
        }
        novo->proximo = nav->proximo;
        nav->proximo = novo;
        return true;
    }
    else {
        novo->proximo = f.comeco;
        f.comeco = novo;
        return true;
    }
}

template<typename TIPO>
bool dequeueRemoveInicio(TFila<TIPO>& f) {
    if (f.comeco == NULL) return false;
    TElementoF<TIPO>* apagar = f.comeco;
    f.comeco = apagar->proximo;
    TIPO valorRemovido = apagar->dado;
    delete apagar;
    return true;

}

template<typename TIPO>
TIPO retornaPrimeiroElemento(TFila<TIPO>& f) {
    return f.comeco->dado;
}

template<typename TIPO>
int tamanhoFila(TFila<TIPO>& f) {
    int tamanho = 0;
    TElementoF<TIPO>* nav = f.comeco;
    while (nav != NULL) {
        tamanho++;
        nav = nav->proximo;
    }
    return tamanho;
}



#endif // FILA_H_INCLUDED