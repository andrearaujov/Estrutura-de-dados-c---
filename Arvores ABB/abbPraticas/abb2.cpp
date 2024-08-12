#include <iostream>
#include <stdexcept>

using namespace std;

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    private:
        Dado valor;
        Noh* esq;
        Noh* dir;
        Noh* pai;
    public:
        Noh (Dado d = 0);
        ~Noh();
        unsigned Altura();
};

Noh::Noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

Noh::~Noh() {
    // Destrutor recursivo!
    delete esq; // não precisa checar se é nulo em C++
    delete dir;
}

unsigned Noh::Altura(){
    unsigned alturaEsq = 0;
    unsigned alturaDir = 0;

    if (esq != NULL) {
        alturaEsq = esq->Altura() + 1;
    }
    
    if (dir != NULL) {
        alturaDir = dir->Altura() + 1;
    }
    
if (alturaEsq > alturaDir) {
        return alturaEsq;
    } else {
        return alturaDir;
    }
    }

class ABB {
    private:
        Noh* raiz;
        void EscreverPreOrdemAux(Noh* atual, unsigned nivel);
    public:
        ABB() { raiz = NULL; }
        ~ABB();
        Noh* Busca(Dado d);
        void EscreverPreOrdem();
        void Inserir(Dado d);
};

ABB::~ABB(){
    delete raiz;
}

void ABB::Inserir(Dado d) {
    Noh* novo = new Noh(d);
    if (raiz == NULL) {
        raiz = novo;
    } else {
        Posicao posInsercao;
        Noh* atual = raiz;
        Noh* anterior;

        // encontrando ponto de inserção
        while (atual != NULL) {
            anterior = atual;

            if (atual->valor > d) {
                atual = atual->esq;
                posInsercao = ESQ;
            } else {
                atual = atual->dir;
                posInsercao = DIR;
            }
        }

        // inserindo o novo nó na árvore
        novo->pai = anterior;

        if (posInsercao == DIR) {
            anterior->dir = novo;
        } else {
            anterior->esq = novo;
        }
    }
}

Noh* ABB::Busca(Dado d) {
    Noh* atual = raiz;
    while (atual != NULL) {
        if (atual->valor == d) {
            return atual;
        } else if (atual->valor > d) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    return atual;
}

void ABB::EscreverPreOrdem() {
    EscreverPreOrdemAux(raiz, 0);
    cout << endl;
}

void ABB::EscreverPreOrdemAux(Noh* atual, unsigned nivel) {
    if (atual != NULL) {
        cout << atual->valor << '/' << nivel << ' ';
        EscreverPreOrdemAux(atual->esq, nivel+1);
        EscreverPreOrdemAux(atual->dir, nivel+1);
    }
}

int main() {
    unsigned qtde;
    int qntdbuscada, itembuscado;
    cin >> qtde;
    ABB minhaArvore;
    int valor;
    for (unsigned i = 0; i < qtde; ++i) {
        cin >> valor;
        minhaArvore.Inserir(valor);
    }
    
    cin >> qntdbuscada;
    for(int i = 0; i < qntdbuscada; i++){
        cin >> itembuscado;
        Noh* nohBuscado = minhaArvore.Busca(itembuscado);  
        if(nohBuscado != NULL){
            cout << nohBuscado->Altura() << " ";
        }
    }
    cout << endl;
    return 0;
}