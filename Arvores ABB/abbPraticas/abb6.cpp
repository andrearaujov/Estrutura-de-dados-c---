#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Info {
public:
    int chave;
    string valor;

    bool operator==(const Info& i) const { return chave == i.chave; }
    bool operator<(const Info& i) const { return chave < i.chave; }
};

typedef Info Dado;

class Noh {
    friend class ABB;
public:
    Noh(Dado d) : dado(d), esq(nullptr), dir(nullptr) {}
private:
    Dado dado;
    Noh* esq;
    Noh* dir;
};

class ABB {
public:
    ABB() : raiz(nullptr) {}
    ~ABB() { delete raiz; }

    void Inserir(const Dado& d);
    Dado Buscar(const Dado& d, unsigned* nroNosVisitados) const;
    void EscreverEmOrdem() const;
private:
    Noh* raiz;

    Noh* InserirRec(Noh* atual, const Dado& d);
    Noh* BuscarRec(Noh* atual, const Dado& d, unsigned* nroNosVisitados) const;
    void EscreverEmOrdemRec(Noh* atual) const;
};

void ABB::Inserir(const Dado& d) {
    raiz = InserirRec(raiz, d);
}

Noh* ABB::InserirRec(Noh* atual, const Dado& d) {
    if (atual == nullptr) {
        return new Noh(d);
    } else if (d < atual->dado) {
        atual->esq = InserirRec(atual->esq, d);
    } else {
        atual->dir = InserirRec(atual->dir, d);
    }
    return atual;
}

Dado ABB::Buscar(const Dado& d, unsigned* nroNosVisitados) const {
    Noh* resultado = BuscarRec(raiz, d, nroNosVisitados);
    if (resultado == nullptr) {
        throw runtime_error("Chave inexistente");
    }
    return resultado->dado;
}

Noh* ABB::BuscarRec(Noh* atual, const Dado& d, unsigned* nroNosVisitados) const {
    if (atual == nullptr) {
        return nullptr;
    }
    (*nroNosVisitados)++;
    if (d == atual->dado) {
        return atual;
    } else if (d < atual->dado) {
        return BuscarRec(atual->esq, d, nroNosVisitados);
    } else {
        return BuscarRec(atual->dir, d, nroNosVisitados);
    }
}

void ABB::EscreverEmOrdem() const {
    EscreverEmOrdemRec(raiz);
    cout << endl;
}

void ABB::EscreverEmOrdemRec(Noh* atual) const {
    if (atual != nullptr) {
        EscreverEmOrdemRec(atual->esq);
        cout << '(' << atual->dado.chave << ',' << atual->dado.valor << ") ";
        EscreverEmOrdemRec(atual->dir);
    }
}

int main() {
    ABB arvore;
    Info info;
    char operacao;
    unsigned nroNosVisitados;

    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> info.chave >> info.valor;
                arvore.Inserir(info);
                break;
            case 'b': // Buscar
                try {
                    cin >> info.chave; // ler a chave
                    nroNosVisitados = 0;
                    info = arvore.Buscar(info, &nroNosVisitados);
                    cout << info.valor << ' ' << nroNosVisitados << endl;
                }
                catch (runtime_error& e) {
                    cout << "INEXISTENTE " << nroNosVisitados << endl;
                }
                break;
            case 'e': // Escrever tudo (em ordem)
                arvore.EscreverEmOrdem();
                break;
            case 'f': // Finalizar execução
                break;
            default:
                cerr << "Comando inválido!\n";
        }
    } while (operacao != 'f');

    return 0;
}
