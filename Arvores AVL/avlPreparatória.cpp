#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <queue>

typedef std::string TChave; // chave da árvore
typedef float TValor; // valor da árvore

// === Declarações das classes ===================================================
class NohAVL; // declaração avançada

class AVL {
    public:
        AVL();
        ~AVL();
        TValor& Valor(TChave chave);
        void EscreverEmOrdem();
        void EscreverNivelANivel(std::ostream& saida);
        void Inserir(TChave chave, const TValor& valor);
        bool ConferirLigacoes();
        void Remover(TChave chave);
    private:
        NohAVL* mPtRaiz;
};

class NohAVL {
    friend class AVL;
    friend std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh);
    friend void AVL::EscreverNivelANivel(std::ostream& saida);
    public:
        NohAVL(TChave c, const TValor& v);
        ~NohAVL();
        void DesalocarFilhosRecursivo();
        NohAVL* InserirRecursivo(NohAVL* ptNoh);
        NohAVL* MenorRecursivo();
        NohAVL* RemoverRecursivo(TChave chave);
        TValor& Valor(TChave chave);
    private:
        NohAVL* ArrumarBalanceamento();
        void AtualizarAltura();
        int FatorBalanceamento();
        NohAVL* Remover();
        NohAVL* RotacionarEsquerda();
        NohAVL* RotacionarDireita();
        void SubstitutirPor(NohAVL* ptNoh);
        void Transplantar(NohAVL* ptFilho);
        void TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo);
        TChave mChave;
        TValor mValor;
        NohAVL* mPtEsq;
        NohAVL* mPtDir;
        NohAVL* mPtPai;
        unsigned int mAltura; // folhas têm altura 1
};

// === Implementações das classes ================================================

using namespace std;

// === Classe NohAVL =============================================================

NohAVL::NohAVL(TChave c, const TValor& v)
    : mChave(c), mValor(v), mPtEsq(NULL), mPtDir(NULL), mPtPai(NULL), mAltura(1) {
}

NohAVL::~NohAVL() {
}

void NohAVL::AtualizarAltura() {
    unsigned int alturaEsq = (mPtEsq ? mPtEsq->mAltura : 0);
    unsigned int alturaDir = (mPtDir ? mPtDir->mAltura : 0);
    mAltura = 1 + max(alturaEsq, alturaDir);
}

int NohAVL::FatorBalanceamento() {
    int alturaEsq = (mPtEsq ? mPtEsq->mAltura : 0);
    int alturaDir = (mPtDir ? mPtDir->mAltura : 0);
    return alturaEsq - alturaDir;
}

void NohAVL::DesalocarFilhosRecursivo() {
    if (mPtEsq) {
        mPtEsq->DesalocarFilhosRecursivo();
        delete mPtEsq;
    }
    if (mPtDir) {
        mPtDir->DesalocarFilhosRecursivo();
        delete mPtDir;
    }
}

NohAVL* NohAVL::RotacionarEsquerda() {
    NohAVL* novaRaiz = mPtDir;
    mPtDir = novaRaiz->mPtEsq;
    if (novaRaiz->mPtEsq != NULL)
        novaRaiz->mPtEsq->mPtPai = this;
    novaRaiz->mPtPai = mPtPai;
    if (mPtPai == NULL)
        novaRaiz->mPtPai = NULL;
    else if (this == mPtPai->mPtEsq)
        mPtPai->mPtEsq = novaRaiz;
    else
        mPtPai->mPtDir = novaRaiz;
    novaRaiz->mPtEsq = this;
    this->mPtPai = novaRaiz;
    AtualizarAltura();
    novaRaiz->AtualizarAltura();
    return novaRaiz;
}

NohAVL* NohAVL::RotacionarDireita() {
    NohAVL* novaRaiz = mPtEsq;
    mPtEsq = novaRaiz->mPtDir;
    if (novaRaiz->mPtDir != NULL)
        novaRaiz->mPtDir->mPtPai = this;
    novaRaiz->mPtPai = mPtPai;
    if (mPtPai == NULL)
        novaRaiz->mPtPai = NULL;
    else if (this == mPtPai->mPtDir)
        mPtPai->mPtDir = novaRaiz;
    else
        mPtPai->mPtEsq = novaRaiz;
    novaRaiz->mPtDir = this;
    this->mPtPai = novaRaiz;
    AtualizarAltura();
    novaRaiz->AtualizarAltura();
    return novaRaiz;
}

NohAVL* NohAVL::ArrumarBalanceamento() {
    AtualizarAltura();
    int balanceamento = FatorBalanceamento();
    if (balanceamento > 1) {
        if (mPtEsq->FatorBalanceamento() < 0)
            mPtEsq = mPtEsq->RotacionarEsquerda();
        return RotacionarDireita();
    }
    if (balanceamento < -1) {
        if (mPtDir->FatorBalanceamento() > 0)
            mPtDir = mPtDir->RotacionarDireita();
        return RotacionarEsquerda();
    }
    return this;
}

NohAVL* NohAVL::InserirRecursivo(NohAVL* ptNoh) {
    if (ptNoh->mChave < mChave) {
        if (mPtEsq == NULL) {
            mPtEsq = ptNoh;
            ptNoh->mPtPai = this;
        } else {
            mPtEsq = mPtEsq->InserirRecursivo(ptNoh);
        }
    } else {
        if (mPtDir == NULL) {
            mPtDir = ptNoh;
            ptNoh->mPtPai = this;
        } else {
            mPtDir = mPtDir->InserirRecursivo(ptNoh);
        }
    }
    return ArrumarBalanceamento();
}

NohAVL* NohAVL::MenorRecursivo() {
    if (mPtEsq == NULL)
        return this;
    else
        return mPtEsq->MenorRecursivo();
}

NohAVL* NohAVL::RemoverRecursivo(TChave chave) {
    if (chave < mChave) {
        if (mPtEsq != NULL)
            mPtEsq = mPtEsq->RemoverRecursivo(chave);
    } else if (chave > mChave) {
        if (mPtDir != NULL)
            mPtDir = mPtDir->RemoverRecursivo(chave);
    } else {
        if (mPtEsq == NULL || mPtDir == NULL) {
            NohAVL* nohAux = (mPtEsq ? mPtEsq : mPtDir);
            if (nohAux == NULL) {
                nohAux = this;
                return NULL;
            } else {
                nohAux->mPtPai = mPtPai;
                if (mPtPai != NULL) {
                    if (this == mPtPai->mPtEsq)
                        mPtPai->mPtEsq = nohAux;
                    else
                        mPtPai->mPtDir = nohAux;
                }
                delete this;
                return nohAux;
            }
        } else {
            NohAVL* nohAux = mPtDir->MenorRecursivo();
            mChave = nohAux->mChave;
            mValor = nohAux->mValor;
            mPtDir = mPtDir->RemoverRecursivo(nohAux->mChave);
        }
    }
    if (this == NULL)
        return this;
    return ArrumarBalanceamento();
}

TValor& NohAVL::Valor(TChave chave) {
    if (chave == mChave)
        return mValor;
    else if (chave < mChave) {
        if (mPtEsq == NULL)
            throw runtime_error("Chave não encontrada!");
        else
            return mPtEsq->Valor(chave);
    } else {
        if (mPtDir == NULL)
            throw runtime_error("Chave não encontrada!");
        else
            return mPtDir->Valor(chave);
    }
}

ostream& operator<<(ostream& saida, NohAVL* ptNoh) {
    if (ptNoh == NULL)
        saida << "[]";
    else
        saida << '[' << ptNoh->mAltura << ':' << ptNoh->mChave << '/' << ptNoh->mValor << ']';
    return saida;
}

// === Classe AVL =================================================================================
AVL::AVL() : mPtRaiz(NULL) {
}

AVL::~AVL() {
    if (mPtRaiz != NULL) {
        mPtRaiz->DesalocarFilhosRecursivo();
        delete mPtRaiz;
    }
}

TValor& AVL::Valor(TChave chave) {
    if (mPtRaiz == NULL)
        throw runtime_error("Tentativa de buscar valor numa arvore vazia.");
    return mPtRaiz->Valor(chave);
}

void AVL::EscreverNivelANivel(ostream& saida) {
    queue<NohAVL*> filhos;
    NohAVL* fimDeNivel = new NohAVL(TChave(), TValor()); // nó especial para marcar fim de um nível
    filhos.push(mPtRaiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        NohAVL* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << ptNoh << ' ';
            if (ptNoh != NULL) {
                filhos.push(ptNoh->mPtEsq);
                filhos.push(ptNoh->mPtDir);
            }
        }
    }
    delete fimDeNivel;
}

void AVL::Inserir(TChave chave, const TValor& valor) {
    NohAVL* novo = new NohAVL(chave, valor);
    if (mPtRaiz == NULL) {
        mPtRaiz = novo;
    } else {
        mPtRaiz = mPtRaiz->InserirRecursivo(novo);
    }
}

void AVL::Remover(TChave chave) {
    if (mPtRaiz == NULL)
        throw runtime_error("Tentativa de remover elemento de uma árvore vazia.");
    mPtRaiz = mPtRaiz->RemoverRecursivo(chave);
    if (mPtRaiz != NULL)
        mPtRaiz->mPtPai = NULL;  // A raiz não deve ter pai
}

// === Programa ===================================================================================
int main() {
    AVL minhaArvore;
    char opcao;
    TChave chave;
    TValor valor;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave >> valor;
                minhaArvore.Inserir(chave, valor);
                break;
            case 'r': // Remover
                try {
                    cin >> chave;
                    minhaArvore.Remover(chave);
                }
                catch (runtime_error& erro) {
                    cerr << erro.what() << endl;
                }
                break;
            case 'b': // Buscar
                try {
                    cin >> chave;
                    valor = minhaArvore.Valor(chave);
                    cout << valor << endl;
                }
                catch (runtime_error& erro) {
                    cerr << erro.what() << endl;
                }
                break;
            case 'e': // Escrever nós nível a nível
                minhaArvore.EscreverNivelANivel(cout);
                break;
            case 'f': // Finalizar o programa
                // vai verificar depois
                break;
            default:
                cerr << "Opção inválida\n";
        }
    } while (opcao != 'f');
    return 0;
}
