/*
 * Crie um programa que seja capaz de armazenar em uma lista duplamente encadeada as ações de usuários em um programa.
 * Cada elemento da lista deve ter um identificador, o nome da ação,
 * tempo para execução total e tempo já consumido de processamento.
 * Os comandos que deverão ser utilizados para execução do programa são:
i: inserir uma nova ação no inicio da lista. O formato de entrada é: Identificador NomeAcao TempoExecução TempoConsumido
h: inserir uma nova ação no final da lista. O formato de entrada é: Identificador NomeAcao TempoExecução TempoConsumido
m: inserir uma nova equipe na posição informada pelo inteiro. Considere 0 como no início e imprima "Posição Inexistente!" caso não seja possível inserir na posição indicada. O formato de entrada é: posiçãoASerInserida Identificador NomeAcao TempoExecução TempoConsumido
r: apagar uma determinada ação do início da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
a: apagar uma determinada ação do fim da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
p: imprimir lista de ações cadastradas em ordem de inserção e, em seguida, em ordem inversa. Imprimir Lista vazia! quando não tiver elemento a ser impresso.
s: buscar por uma ação a partir de seu nome. Imprimir Nao encontrado quando a busca não obtiver sucesso.
Nota: o formato de saída das ações deve ser: (Identificador, NomeAcao, TempoExecução, TempoConsumido). Para mais instâncias de ações (comando de impressão), separar cada uma delas por quebras de linha.

Entradas:

Comandos detalhados no exercício
Saídas:

Impressões detalhadas no exercício
Exemplo de Entrada e Saída misturados

Utilizando como base o código que você desenvolveu na atividade 
"Lista Simplesmente Encadeada - Equipes de Maratona" faça as adaptações necessárias para que ela funcione como deque. 
Todos os métodos que não devem ser permitidos para uso em uma deque devem retornar ao usuário que o procedimento não é permitido.

Uma deque é uma estrutura de dados lista em que a remoção e inserção só é permitida em suas pontas 
(ou seja: no início e no final da lista).

Feito isso, você deverá adicionar mais um procedimento fora da classe, 
que recebe uma deque e uma string e remove um elemento qualquer, mas sem quebrar a estrutura. Ou seja: a remoção deverá ser implementada de maneira similar à remoção em uma pilha ou fila. Utilizando esse procedimento, adicione a seguinte opção no menu da função principal:

x seguido de uma string: remove da lista o elemento que possui o nome da ação informado pelo usuário. 
Imprimir Remoção em lista vazia! caso a chamada ao procedimento seja chamada com a lista vazia. 
Imprimir Nao encontrado caso não encontre o elemento em uma lista que possua pelo menos um elemento
Lembrando novamente: esse comando deverá ser implementado sem quebra de estrutura.

Saídas:

Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para remover o elemento solicitado.
Ao terminar a execução do programa, todos os itens da listas são escritos.
 */

#include <iostream>
#include <cstdlib>

using namespace std;

struct acaoPrograma
{
    int identificador;
    string nomeAcao;
    int tempoExecucao;
    int tempoConsumido;
};

class noh
{
    friend class listadup;

private:
    acaoPrograma acao; // poderia ser outro tipo de variável
    noh *proximo;
    noh *anterior;

public:
    // noh();
    noh(acaoPrograma d);
};

// construindo dado chamando seu construtor
noh::noh(acaoPrograma d)
{
    acao = d;
    proximo = NULL;
    anterior = NULL;
}

// lista dinamicamente encadeada
class listadup
{
private:
    noh *primeiro;
    noh *ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
public:
    listadup();
    listadup(const listadup &umaLista);
    ~listadup();
    // sobrecarga do operador de atribuição
    listadup &operator=(const listadup &umaLista);
    // inserção, remoção e procura
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string valor); // retorna a posicao
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
    void removeElemento(string nomeAcao);
};

// constrói uma lista inicialmente vazia
listadup::listadup()
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

// construtor de cópia
listadup::listadup(const listadup &umaLista)
{
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
    noh *aux = umaLista.primeiro;
    while (aux != NULL)
    {
        insereNoFim(aux->acao);
        aux = aux->proximo;
    }
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup()
{
    removeTodos();
}

// remove todos os elementos da lista
void listadup::removeTodos()
{
    noh *atual = primeiro;
    while (atual != NULL)
    {
        noh *aux = atual;
        atual = atual->proximo;
        delete aux;
    }
}

// sobrecarga do operador de atribuição
listadup &listadup::operator=(const listadup &umaLista)
{
    // limpa a lista atual
    removeTodos();
    // percorre a lista recebida como parâmetro, copiando os dados
    noh *aux = umaLista.primeiro;

    while (aux != NULL)
    {
        insereNoFim(aux->acao);
        aux = aux->proximo;
    }

    return *this;
}

// insere por no final da lista
void listadup::insereNoFim(acaoPrograma acao)
{
    noh *novo = new noh(acao);
    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        ultimo->proximo = novo;
        novo->anterior = ultimo;
        ultimo = novo;
    }
    tamanho++;
}

// insere no início da lista
void listadup::insereNoInicio(acaoPrograma acao)
{
    noh *novo = new noh(acao);
    if (vazia())
    {
        primeiro = novo;
        ultimo = novo;
    }
    else
    {
        novo->proximo = primeiro;
        primeiro->anterior = novo;
        primeiro = novo;
    }
    tamanho++;
}

// insere em uma determinada posição da lista
void listadup::insereNaPosicao(int posicao, acaoPrograma acao)
{
    if ((posicao < 0) or (posicao > tamanho))
    {
        cout << "Posicão Inexistente!" << endl;
    }
    else if (posicao == 0)
    {
        insereNoInicio(acao);
    }
    else if (posicao == tamanho)
    {
        insereNoFim(acao);
    }
    else
    {
        noh *atual = primeiro;
        int posAtual = 0;
        while (posAtual < (posicao - 1))
        {
            atual = atual->proximo;
            posAtual++;
        }
        noh *novo = new noh(acao);
        novo->proximo = atual->proximo;
        novo->anterior = atual;
        atual->proximo = novo;
        if (novo->proximo != NULL)
        {
            novo->proximo->anterior = novo;
        }
        tamanho++;
    }
}

int listadup::procura(string valor)
{
    if (vazia())
    {
        throw runtime_error("Lista vazia!");
    }
    else
    {
        noh *atual = primeiro;
        int posAtual = 0;
        while (atual != NULL)
        {
            if (atual->acao.nomeAcao == valor)
            {
                return posAtual;
            }
            atual = atual->proximo;
            posAtual++;
        }
    }
    return -1;
}

// método básico que *percorre* uma lista, imprimindo seus elementos
void listadup::imprime()
{
    if (vazia())
    {
        cout << "Lista vazia!" << endl;
    }
    else
    {
        noh *atual = primeiro;
        while (atual != NULL)
        {
            cout << "(" << atual->acao.identificador << ", " << atual->acao.nomeAcao << ", " << atual->acao.tempoExecucao << ", " << atual->acao.tempoConsumido << ")" << endl;
            atual = atual->proximo;
        }
        cout<< "IMPRIMINDO REVERSO" << endl;

        atual = ultimo;
        while(atual!=NULL){
             cout << "(" << atual->acao.identificador << ", " << atual->acao.nomeAcao << ", " << atual->acao.tempoExecucao << ", " << atual->acao.tempoConsumido << ")" << endl;
            atual = atual->anterior;
        }
    }
}

// verifica se a lista está vazia
inline bool listadup::vazia()
{
    return (primeiro == NULL);
}

void listadup::removeNoInicio()
{
    if (vazia())
    {
        cout << "Remoção em lista vazia!" << endl;
    }
    else if (tamanho == 1)
    {
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
        tamanho = 0;
    }
    else
    {
        noh *aux = primeiro;
        primeiro = primeiro->proximo;
        primeiro->anterior = NULL;
        delete aux;
        tamanho--;
    }
}

void listadup::removeNoFim()
{
    if (vazia())
    {
        cout << "Remoção em lista vazia!" << endl;
    }
    else if (tamanho == 1)
    {
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
        tamanho = 0;
    }
    else
    {
        noh *aux = ultimo;
        ultimo = ultimo->anterior;
        ultimo->proximo = NULL;
        delete aux;
        tamanho--;
    }
}


void listadup::removeElemento(string nomeAcao){
    if(vazia()){
        cout<< "Remoção em lista vazia!"<< endl;
    }
    else{
        noh* anterior = NULL;
        noh* atual = primeiro;
        while(atual!= NULL and atual->acao.nomeAcao != nomeAcao){
            anterior = atual;
            atual = atual->proximo;
        }
        if(atual == NULL){
            cout<< "Não encontrado"<< endl;
        }
        else{
            if(atual==primeiro){
                primeiro = primeiro->proximo;
                if(primeiro == NULL){
                    ultimo = NULL;
                }
            }
            else{
                anterior->proximo = atual->proximo;
                if(atual == ultimo){
                    ultimo = anterior;
                }
            }
            delete atual;
        }
    }
}   

int main()
{
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeAcao;

    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoInicio(info);
                break;
            case 'h': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoFim(info);
                break;
            case 'm': // inserir
                cin >> posicao;
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                cout<< "Operação não permitida" << endl;
                break;
            case 's': // procurar
                cin >> nomeAcao;
                posicao = minhaLista.procura(nomeAcao);
                if (posicao == -1)
                    cout << "Nao encontrado" << endl;
                else
                    cout << posicao << endl;
                break;
            case 'x': //removendo elemento
                cin>>nomeAcao;
                minhaLista.removeElemento(nomeAcao);
                break;
            case 'a':
                minhaLista.removeNoFim();
                break;
            case 'r': // remover
                minhaLista.removeNoInicio();
                break;
            case 'p': // limpar tudo
                minhaLista.imprime();
                break;
            case 'f': // finalizar
                // checado no do-while
                break;
            default:
                cerr << "comando inválido\n";
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}