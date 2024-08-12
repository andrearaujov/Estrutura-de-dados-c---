#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh(Dado d);
        ~Noh();
        unsigned NroDeFolhas() const;
    protected:
        Dado valor;
        Noh* esq;
        Noh* dir;
        Noh* pai;
};

Noh::Noh(Dado d) {
    valor = d;
    esq = NULL;
    dir = NULL;
    pai = NULL;
}

Noh::~Noh() {
    // Destrutor recursivo!
    delete esq;
    delete dir;
}

unsigned Noh::NroDeFolhas() const {
    if(esq == NULL  and dir == NULL){
        return 1;
    }
    unsigned folhasEsq = 0;
    unsigned folhasDir = 0;

    if (esq != NULL) {
        folhasEsq = esq->NroDeFolhas();
    }
    if (dir != NULL) {
        folhasDir = dir->NroDeFolhas();
    }
    return folhasEsq + folhasDir;

}

class ABB {
    public:
        ABB() { raiz = NULL; }
        ~ABB();
        // Escreve uma árvore nível a nível.
        // Pode ser útil para depurar o programa.
        void EscreverNivelANivel(std::ostream& saida);
        // Insere um dado na árvore.
        void Inserir(Dado d);
        // Retorna o nro de folhas na árvore.
        unsigned NroDeFolhas() const;
    protected:
        Noh* raiz;
};

ABB::~ABB(){
    delete raiz;
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh aux = Dado();
    Noh* fimDeNivel = &aux; // marcador especial para fim de nivel
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        Noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << '[';
            if (ptNoh != NULL) {
                saida << ptNoh->valor;
                filhos.push(ptNoh->esq);
                filhos.push(ptNoh->dir);
            }
            saida << ']';
        }
    }
}

void ABB::Inserir(Dado d) {
    Noh* novo = new Noh(d);
    if (raiz == NULL) {
        raiz = novo;
    }
    else {
        Posicao posInsercao;
        Noh* atual = raiz;
        Noh* anterior;

        // encontrando ponto de inserção
        while (atual != NULL) {
            anterior = atual;
            if (atual->valor > d) {
                atual = atual->esq;
                posInsercao = ESQ;
            }
            else {
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

unsigned ABB::NroDeFolhas() const {
    if (raiz == NULL) {
        return 0; 
    }
    return raiz->NroDeFolhas();
}

int main() {
    unsigned qtde;
    cin >> qtde;
    ABB arvore;
    Dado valor;
    for (unsigned i = 0; i < qtde; ++i) {
        cin >> valor;
        arvore.Inserir(valor);
    }
    cout << arvore.NroDeFolhas() << endl;
    return 0;
}