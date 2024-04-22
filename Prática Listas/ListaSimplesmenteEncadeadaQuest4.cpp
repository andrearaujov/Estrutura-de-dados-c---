/* 
 * Classe lista, uma lista dinamicamente encadeada
 * Crie um programa que seja capaz de armazenar em uma lista encadeada as equipes de uma maratona de programação. 
 * Para cada equipe deverá ser informado o seu nome, o nome do líder da equipe,
 * a linguagem de programação que será utilizada e a quantidade de membros
 * Implemente uma função que realize a remoção de um elemento no fim da lista. Para esta atividade você não poderá utilizar um ponteiro para o último elemento. Caso a lista não possua elementos imprima Lista vazia!.

Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Lista Simplesmente Encadeada - Equipes de Maratona" como base.

Exemplo de Entrada e Saída juntas:
 */

#include <iostream>
#include <cstdlib>

using namespace std;


struct equipe{
    string nomeEquipe;
    string lider;
    string linguagem; 
    int qtdMembros;
};

class noh {
friend class lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d){
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    void imprimeReversoAux(noh* umNoh);
public:
    // construtores e destrutor
    lista();
    lista(const lista& umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umaLista);  
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente vazia
lista::lista() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho=0;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
    primeiro = NULL;
    ultimo = NULL;
    tamanho=0;
    noh* aux = umaLista.primeiro;
    while(aux!=NULL){
        insereNoFim(aux->elenco);
        aux= aux->proximo;
    }
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista( ) {
    removeTodos();

}    

// remove todos os elementos da lista
void lista::removeTodos( ) {
    while(!vazia()){
        removeNoInicio();
    }
}    

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
    noh* novo = new noh(elenco);
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }
    else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho ++;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {
    noh* novo = new noh(elenco);
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }
    else{
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
 
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco){
    if(posicao < 0 or posicao > tamanho){
        cout<< "Posição Inexistente!" << endl;
    }
    else{
        if(posicao == 0){
            insereNoInicio(elenco);
        }
        else if(posicao == tamanho){
            insereNoFim(elenco);
        }
        else{
            noh* aux = primeiro;
            int pos = 0;
            while(pos<posicao-1){
                aux=aux->proximo;
                pos++;
            }
            noh* novo = new noh(elenco);
            novo->proximo = aux->proximo;
            aux->proximo = novo;
            tamanho ++;
        }
    }

}

//procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 
    else{
        noh* aux = primeiro;
        int pos = 0;
        while(aux!=NULL){
            if(aux->elenco.nomeEquipe == valor){
                return pos;
            }
            aux = aux->proximo;
            pos++;
        }
        cout<< "Não encontrado"<< endl;
    }
    return -1;
}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    } 
    else{
        noh* aux = primeiro;
        while(aux !=NULL){
           cout << "(" << aux->elenco.nomeEquipe << ", " << aux->elenco.lider << ", " << aux->elenco.linguagem << ", " << aux->elenco.qtdMembros << ")" << endl;
            aux = aux->proximo;
        }
    }
}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (primeiro == NULL);
}
   
void lista::removeNoFim() {
    if(vazia()){
        cout<< "Remoção em lista vazia!" << endl;
    }
    else if(tamanho == 1){
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
        tamanho = 0;
    }
    else{
        noh* aux = primeiro;
        while(aux->proximo != ultimo){
            aux = aux->proximo;
        }
        delete ultimo;
        ultimo = aux;
        ultimo->proximo = NULL;
        tamanho--;
    }
}
    
void lista::removeNoInicio() {
    if(vazia()){
        cout<< "Remoção em lista vazia!" << endl;
    }
    else{
        noh* aux = primeiro;
        primeiro = primeiro->proximo;
        delete aux;
        tamanho--;
    }
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // busca
                    cin >> nomeEquipe;
                    cout << minhaLista.procura(nomeEquipe) <<endl;
                    break;                    
                case 'r': // remover
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p': // imprime
                    minhaLista.imprime();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
