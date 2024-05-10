#ifndef REFAZENDOLISTAENCADEADA_H_INCLUDED
#define REFAZENDOLISTAENCADEADA_H_INCLUDED

using namespace std;

#include <iostream>

template<typename TIPO>
struct TElemento {
    TIPO dado;
    TElemento<TIPO>* proximo;
};

template<typename TIPO>
struct Tlista {
    TElemento<TIPO>* inicio;
};

template<typename TIPO>
bool inicializaLista(Tlista<TIPO>& l) {
    l.inicio = NULL;
    return true;
}

template<typename TIPO>
void imprimirLista(Tlista<TIPO> l) {
    TElemento<TIPO>* nav;
    nav = l.inicio;

    while (nav != nullptr) {
        cout << nav->dado << endl;
        nav = nav->proximo;
    }
}

template<typename TIPO>
TElemento<TIPO>* novoElemento(TIPO dado) {
    TElemento<TIPO>* novo = new TElemento<TIPO>;
    novo->dado = dado;
    novo->proximo = NULL;
    return novo;
}

template<typename TIPO>
bool insereInicio(Tlista<TIPO>& l, TIPO dado) {
    TElemento<TIPO>* novo = novoElemento(dado);
    novo->proximo = l.inicio;
    l.inicio = novo;
    return true;
}

template<typename TIPO>
bool insereFim(Tlista<TIPO>& l, TIPO dado) {
    TElemento<TIPO>* nav = l.inicio;
    TElemento<TIPO>* novo = novoElemento(dado);
    if (l.inicio != NULL) {
        while (nav->proximo != NULL) {
            nav = nav->proximo;
        }
        novo->proximo = nav->proximo;
        nav->proximo = novo;
        return true;
    }
    else {
        novo->proximo = l.inicio;
        l.inicio = novo;
        return true;
    }
}

template<typename TIPO>
bool inserePosicao(Tlista<TIPO>& l, TIPO dado, int posicao) {
    TElemento<TIPO>* nav = l.inicio;
    TElemento<TIPO>* novo = novoElemento(dado);
    if (l.inicio != NULL || posicao != 0) {
        for (int i = 0; i < posicao - 1 && nav->proximo != NULL; i++) {
            nav = nav->proximo;
        }
        novo->proximo = nav->proximo;
        nav->proximo = novo;
        return true;
    }
    else {
        novo->proximo = l.inicio;
        l.inicio = novo;
        return true;
    }
}

template<typename TIPO>
bool removeInicio(Tlista<TIPO>& l) {
    TElemento<TIPO>* nav = l.inicio;
    if (l.inicio == NULL) return false;
    l.inicio = nav->proximo;
    delete nav;
    return true;
}

template<typename TIPO>
bool removeFim(Tlista<TIPO>& l) {
    TElemento<TIPO>* nav = l.inicio;
    if (l.inicio == NULL) return false;
    if (l.inicio->proximo == NULL) {
        delete l.inicio;
        l.inicio = NULL;
        return true;
    }
    while (nav->proximo->proximo != NULL) {
        nav = nav->proximo;
    }
    delete nav->proximo;
    nav->proximo = NULL;
    return true;

}

template<typename TIPO>
bool removePosicao(Tlista<TIPO>& l, int posicao) {
    TElemento<TIPO>* nav = l.inicio;
    int i = 0;
    if (l.inicio == NULL) return false;
    while (i < posicao - 1 && nav != NULL) {
        nav = nav->proximo;
        i++;
    }
    TElemento<TIPO>* temp = nav->proximo;
    nav->proximo = nav->proximo->proximo;
    delete temp;
    return true;
}


#endif // REFAZENDOLISTAENCADEADA_H_INCLUDED