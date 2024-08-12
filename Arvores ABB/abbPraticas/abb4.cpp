#include <iostream>
#include <queue>

typedef int Dado;

enum Posicao {DIR, ESQ};

class Noh {
    friend class ABB;
    public:
        Noh (Dado d);
        ~Noh();
        // Verifica se um nó é filho da direita do pai.
        bool FilhoDaDireita();
        // Retorna a menor chave de uma sub-árvore.
        Dado MenorRecursivo();
        // Verifica se existe sucessor e retorna o valor sucessor, se existir.
        bool Sucessor(Dado* ptResultado);
    protected:
        Dado valor;
        Noh* esq;
        Noh* dir;
        Noh* pai;
};

class ABB {
    public:
        ABB() { raiz = NULL; }
        ~ABB();
        // Retorna um ponteiro para o nó de uma chave, ou NULL.
        Noh* Busca(Dado d);
        // Escreve uma árvore nível a nível.
        void EscreverNivelANivel(std::ostream& saida);
        // Insere um dado na árvore.
        void Inserir(Dado d);
        // Verifica se um dado tem sucessor e o retorna.
        bool Sucessor(Dado d, Dado* ptResultado);
    protected:
        Noh* raiz;
};

using namespace std;
// === Classe Noh ==============================================================
Noh::Noh(Dado d)
    : valor(d), esq(NULL), dir(NULL), pai(NULL) {
}

Noh::~Noh() {
    // Destrutor recursivo!
    delete esq;
    delete dir;
}

bool Noh::FilhoDaDireita() {
    return (pai != NULL and pai->dir == this);
}

Dado Noh::MenorRecursivo() {
    if (esq == NULL)
    {
        return valor;
    } else{
         return esq->MenorRecursivo();
    }
    
}

bool Noh::Sucessor(Dado* ptResultado) {
    if(dir!=NULL){
        *ptResultado = dir->MenorRecursivo();
        return true;
    }
    else{
        Noh* atual = this;
        Noh* ancestral = pai;
        while (ancestral != NULL && atual->FilhoDaDireita()) {
            atual = ancestral;
            ancestral = ancestral->pai;
        }
        if (ancestral != NULL) {
            *ptResultado = ancestral->valor;
            return true;
        } else {
            return false;
        }
    }

}

// === Classe ABB ==============================================================
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
        novo->pai = anterior;
        if (posInsercao == DIR) {
            anterior->dir = novo;
        } else {
            anterior->esq = novo;
        }
    }
}

bool ABB::Sucessor(Dado d, Dado* ptResultado) {
    Noh* noh = Busca(d);
    if (noh != NULL) {
        return noh->Sucessor(ptResultado);
    } else {
        return false;
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

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh noh = Dado();
    Noh* fimDeNivel = &noh; // noh especial para fim de nivel
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

// === Programa ================================================================
int main() {
    ABB arvore;
    Dado chave;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> chave;
                arvore.Inserir(chave);
                break;
            case 'e': // Escrever
                arvore.EscreverNivelANivel(cout);
                break;
            case 's': { // Sucessor
                cin >> chave;
                Dado sucessor;
                while (arvore.Sucessor(chave, &sucessor)) {
                    cout << sucessor << ' ';
                    chave = sucessor;
                }
                cout << endl;
                break;
            }
        }
    } while (operacao != 'f');
    return 0;
}