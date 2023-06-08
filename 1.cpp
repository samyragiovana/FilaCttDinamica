#include <iostream>
#include <windows.h>
using namespace std;

/*Exercício 1
Implemente um programa que contemple uma fila de contatos dinâmica para um call center. 
As opções do programa devem ser:
• Inserir Contato: – Deve solicitar ao usuário os dados e incluir o contato na fila;
• Próximo Contato: – Deverá pegar o Contato do Inicio da Fila, removê-lo e mostrar
os seus dados na tela para o usuário efetuar o contato com o cliente.
• Sair*/

typedef struct TipoItem {
    char nome[20];
    char telefone[15];
    char solicitacao[100];
} TipoItem;

typedef struct TipoElemento {
    TipoItem item;
    struct TipoElemento *prox;
} TipoElemento;

typedef struct TipoElemento *Apontador;

typedef struct TipoFila {
    Apontador inicio, fim;
    int tamanho;
} TipoFila;

void InicializaFila(TipoFila *fila);
bool VerificaFilaVazia(TipoFila *fila);
void Enfileira(TipoFila *fila, TipoItem item);
void Desenfileira(TipoFila *fila);
void ImprimeProximo(TipoFila *fila);
void menu();
void InsereContato(TipoFila *fila);
void ProximoContato(TipoFila *fila);

int main() {
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
    TipoFila f;
    TipoItem i;

    InicializaFila(&f);

    if (VerificaFilaVazia(&f)) {
        cout << "Fila vazia.\n\n";
    }

    int opcao;
    system("cls");

    do {
        menu();
        while((cout << "Escolha a opção: ") && !(cin >> opcao)) {
            cout << "Digite uma opção válida.\n\n";
            cin.clear(); cin.ignore();
        }
        system("cls");
        switch (opcao) {
        case 1: 
            InsereContato(&f);
            break;
        case 2: 
            ProximoContato(&f); 
            break;
        }
    } while (opcao != 3);

    return 0;
}

void menu() {    
     cout<<"  \n        ����������������������������������������������������������������";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        �                         CALL CENTER                          �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        ����������������������������������������������������������������";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        � 1 - INSERIR CONTATO                                          �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        � 2 - PRÓXIMO CONTATO                                          �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        � 3 - SAIR                                                     �";
     cout<<"  \n        �                                                              �";
     cout<<"  \n        ����������������������������������������������������������������\n\n";
}

void InsereContato(TipoFila *fila) { 
    TipoItem i;
    cout << "***********************************\n";
    cout << "        CADASTRO DE CONTATO        \n";
    cout << "***********************************\n\n";
    cin.ignore();
    cout << "Nome: ";
    gets(i.nome);
    cout << "Telefone: ";
    gets(i.telefone);
    cout << "Solicitação: ";
    gets(i.solicitacao);

    Enfileira(fila, i);

    cout << "\nContato registrado com sucesso!\n\n";
    Sleep(1000);
    system("cls");
}

void ProximoContato(TipoFila * fila) {
    cout << "***********************************\n";
    cout << "        PRÓXIMO ATENDIMENTO        \n";
    cout << "***********************************\n\n";

    ImprimeProximo(fila);
    
    system("PAUSE");
    system("cls");
}

void InicializaFila(TipoFila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

bool VerificaFilaVazia(TipoFila *fila) {
    if (fila->inicio == NULL) { // Ninguém na fila
        return true;        
    } else {
        return false;
    }
}

void Enfileira(TipoFila *fila, TipoItem i) {
    Apontador novo;
    novo = new TipoElemento;
    novo->item = i;
    novo->prox = NULL;
    
    if (VerificaFilaVazia(fila)) {
        fila->inicio = novo;
        fila->fim = novo;
    
    } else {
        fila->fim->prox = novo;
        fila->fim = novo;
    }
    fila->tamanho++;
}

void Desenfileira(TipoFila *fila) {
    Apontador aux;
    if (VerificaFilaVazia(fila)) {
        cout << "\nFila vazia.\n\n";
    }
    
    aux = fila->inicio;
    fila->inicio = fila->inicio->prox;
    free(aux);
    fila->tamanho--;
}

void EsvaziaFila(TipoFila *fila) {
    Apontador aux;
    if (VerificaFilaVazia(fila)) {
        cout << "\nFila vazia.\n\n";
    }
    
    aux = fila->inicio;
    do {
        fila->inicio = fila->inicio->prox;
        free(aux);
        aux = fila->inicio;
    } while (aux != NULL);
    cout << "\nFila esvaziada.\n";
    fila->tamanho = 0;
    fila->inicio = NULL;
    fila->fim = NULL;
}

void ImprimeProximo(TipoFila *fila) {
    if (VerificaFilaVazia(fila)) {
        cout << "\nFila vazia.\n\n";
    } else {
        cout << "\nNome: " << fila->inicio->item.nome; 
        cout << "\nTelefone: " << fila->inicio->item.telefone;
        cout << "\nSolicitação: " << fila->inicio->item.solicitacao << endl << endl;
        Desenfileira(fila);
    }
}