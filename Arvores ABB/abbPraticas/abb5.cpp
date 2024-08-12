#include <iostream>

typedef int Dado;

class Noh {
    friend class ABB;
    public:
        Noh(Dado d);
        ~Noh();
    protected:
        Dado valor;
        Noh* esq;
        Noh* dir;
};

class ABB {
    public:
        ABB() { raiz = NULL; }
        ~ABB();
        void Inserir(Dado d);
        int ContarNos() const;
        int DiferencaSubarvores() const;
    protected:
        Noh* raiz;
        int ContarNosAux(Noh* noh) const;
};

using namespace std;

Noh::Noh(Dado d)
    : valor(d), esq(NULL), dir(NULL) {
}

Noh::~Noh() {
    delete esq;
    delete dir;
}

ABB::~ABB() {
    delete raiz;
}

void ABB::Inserir(Dado d) {
    Noh* novo = new Noh(d);
    if (raiz == NULL) {
        raiz = novo;
    } else {
        Noh* atual = raiz;
        Noh* anterior = NULL;
        while (atual != NULL) {
            anterior = atual;
            if (d < atual->valor) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }
        if (d < anterior->valor) {
            anterior->esq = novo;
        } else {
            anterior->dir = novo;
        }
    }
}

int ABB::ContarNosAux(Noh* noh) const {
    if (noh == NULL) {
        return 0;
    } else {
        return 1 + ContarNosAux(noh->esq) + ContarNosAux(noh->dir);
    }
}

int ABB::ContarNos() const {
    return ContarNosAux(raiz);
}

int ABB::DiferencaSubarvores() const {
    if (raiz == NULL) {
        return 0;
    } else {
        int nosEsq = ContarNosAux(raiz->esq);
        int nosDir = ContarNosAux(raiz->dir);
        return nosEsq - nosDir;
    }
}

int main() {
    ABB arvore;
    Dado valor;
    cin >> valor;
    while (valor != -1) {  // Continua lendo até que -1 seja lido
        arvore.Inserir(valor);
        cin >> valor;  // Lê o próximo valor
    }
    cout << arvore.ContarNos() << " ";
    cout << arvore.DiferencaSubarvores() << endl;
    return 0;
}
