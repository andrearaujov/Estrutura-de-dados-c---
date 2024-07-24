#include <iostream>
#include <string>

using namespace std;

class Nodo {
public:
    int chave;
    int nivel;
    Nodo* esquerda;
    Nodo* direita;

    Nodo(int k, int n) : chave(k), nivel(n), esquerda(nullptr), direita(nullptr) {}
};

class ArvoreBinariaBusca {
private:
    Nodo* raiz;

    Nodo* inserir(Nodo* nodo, int chave, int nivel) {
        if (nodo == nullptr) {
            return new Nodo(chave, nivel);
        }
        if (chave < nodo->chave) {
            nodo->esquerda = inserir(nodo->esquerda, chave, nivel + 1);
        } else {
            nodo->direita = inserir(nodo->direita, chave, nivel + 1);
        }
        return nodo;
    }

    Nodo* encontrarMinimo(Nodo* nodo) {
        while (nodo->esquerda != nullptr) {
            nodo = nodo->esquerda;
        }
        return nodo;
    }

    Nodo* remover(Nodo* nodo, int chave) {
        if (nodo == nullptr) {
            cout << "ERRO" << endl;
            return nullptr;
        }
        if (chave < nodo->chave) {
            nodo->esquerda = remover(nodo->esquerda, chave);
        } else if (chave > nodo->chave) {
            nodo->direita = remover(nodo->direita, chave);
        } else {
            if (nodo->esquerda == nullptr) {
                Nodo* nodoDireita = nodo->direita;
                delete nodo;
                return nodoDireita;
            } else if (nodo->direita == nullptr) {
                Nodo* nodoEsquerda = nodo->esquerda;
                delete nodo;
                return nodoEsquerda;
            } else {
                Nodo* sucessor = encontrarMinimo(nodo->direita);
                nodo->chave = sucessor->chave;
                nodo->direita = remover(nodo->direita, sucessor->chave);
            }
        }
        return nodo;
    }

    void atualizarNivel(Nodo* nodo, int nivel) {
        if (nodo != nullptr) {
            nodo->nivel = nivel;
            atualizarNivel(nodo->esquerda, nivel + 1);
            atualizarNivel(nodo->direita, nivel + 1);
        }
    }

    void emOrdem(Nodo* nodo) {
        if (nodo != nullptr) {
            emOrdem(nodo->esquerda);
            cout << nodo->chave << "/" << nodo->nivel << " ";
            emOrdem(nodo->direita);
        }
    }

    void preOrdem(Nodo* nodo) {
        if (nodo != nullptr) {
            cout << nodo->chave << "/" << nodo->nivel << " ";
            preOrdem(nodo->esquerda);
            preOrdem(nodo->direita);
        }
    }

public:
    ArvoreBinariaBusca() : raiz(nullptr) {}

    void inserir(int chave) {
        raiz = inserir(raiz, chave, 0);
        atualizarNivel(raiz, 0);
    }

    void remover(int chave) {
        raiz = remover(raiz, chave);
        atualizarNivel(raiz, 0);
    }

    void emOrdem() {
        emOrdem(raiz);
        cout << endl;
    }

    void preOrdem() {
        preOrdem(raiz);
        cout << endl;
    }
};

int main() {
    ArvoreBinariaBusca abb;
    string comando;
    int chave;

    while (cin >> comando) {
        if (comando == "i") {
            cin >> chave;
            abb.inserir(chave);
        } else if (comando == "r") {
            cin >> chave;
            abb.remover(chave);
        } else if (comando == "o") {
            abb.emOrdem();
        } else if (comando == "p") {
            abb.preOrdem();
        } else if (comando == "f") {
            break;
        }
    }

    return 0;
}
