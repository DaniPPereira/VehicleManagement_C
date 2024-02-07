#ifndef _HEADER
#define _HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

//structs


typedef struct carteira {
    float saldo;
} carteira;

typedef struct cliente {
    int nif; // ID do cliente
    char nome[50]; // Nome do cliente
    carteira carteira; // Saldo do cliente
    char localizacao[100];
    struct cliente* next; // Ponteiro para o próximo nó da lista
} cliente;

typedef struct gestor {
    int id; // ID do gestor
    char nome[50]; // Nome de usuário do gestor
    char password[50]; // Senha do gestor
    struct gestor* next; // Ponteiro para o próximo nó da lista
} gestor;

typedef struct veiculo {
    int id;
    char tipo[20];
    float bateria;
    float autonomia;
    float custo;
    char localizacao[20];
    int estado; // 0 - Disponível / 1 - Reservado
    struct veiculo* next;
} veiculo;

typedef struct aresta {
    char verticeDestino[50];
    float distancia;
    struct aresta* next;
} aresta;

typedef struct vertice {
    char verticeOrigem[50];
    struct aresta* arestas;
    struct vertice* next;
} vertice;





//Assinaturas
void guardarClientesTxt(cliente *listaClientes);
void inserirCliente(cliente **listaClientes);
void listarClientes(cliente *listaClientes);
void lerClientesTxt(cliente **listaClientes);
void removerCliente(int nif,cliente **listaClientes);
void alterarCliente(int nif, cliente* listaClientes);
void lerGestoresTxt(gestor **listarGestores);
int LoginGestor(gestor *listaGestores, int id, char password[]);
void listarGestores(gestor *listaGestores);
void guardarGestoresTxt(gestor *listaGestores);
void adicionarGestor(gestor **listaGestores);
void removerGestor(int id,gestor **listaGestores);
void alterarGestor(gestor *listaGestores, int id);
void alterarSaldo(int nif, cliente *listaClientes);
void guardarVeiculos(veiculo *listaVeiculos);
void adicionarVeiculo(veiculo **listaVeiculos);
void lerMeios(veiculo **listaVeiculos);
void removerVeiculo(int id, veiculo **listaVeiculos);
void listarVeiculos(veiculo *listaVeiculos);
void listarVeiculosPorAutonomiaDecrescente(veiculo *listaVeiculos);
void listarVeiculosPorLocalizacao(veiculo *listaVeiculos, char localizacao[20]);
void alterarVeiculo(veiculo **listaVeiculos, int id);
void fazerReserva(cliente *listaClientes, veiculo *listaVeiculos);
int listarVeiculosDisponiveis(veiculo *listaVeiculos);


#endif