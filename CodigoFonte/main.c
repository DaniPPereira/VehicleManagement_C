#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#include "functions.c"
#include "header.h"

/**
 * It's a menu that allows the user to choose between a client menu, a manager menu and exit.
 * The client menu allows the user to add a reservation, list the vehicles and exit.
 * The manager menu allows the user to add a manager, remove a manager, change a manager's data, change
 * a client's balance, open the vehicle menu and exit.
 * The vehicle menu allows the user to add a vehicle, remove a vehicle, change a vehicle's data, list
 * the vehicles by decreasing autonomy, list the vehicles by location and exit.
 * The functions that are not working correctly are the ones that are commented in the code.
 * 
 */
int main()
{
    
  cliente *listaClientes = NULL; //Inicializar lista de clientes 
  gestor *listaGestores = NULL; //Inicializar lista de gestores
  veiculo *listaVeiculos = NULL; //Inicializar lista de veiculos
  vertice *listaGrafos = NULL;
  vertice *listaArestas = NULL;
  
  lerClientesTxt(&listaClientes); 
  lerGestoresTxt(&listaGestores);
  lerMeios(&listaVeiculos);
  lerVertices(&listaGrafos);
  carregarArestasDeArquivo(&listaGrafos,&listaArestas);

    
  int option,nif,id,retorno,retorno1;
  char password[50], localizacao[15],vertice[50],verticeOrigem[50], verticeDestino[50];
  float distancia;
  
  do{
    printf("\nMenu:\n");
    printf("1. Abrir Menu Cliente\n");
    printf("2. Abrir Menu Gestor\n");
    printf("3. Sair\n");
    printf("Escolha a sua opcao: ");

    scanf("%d", &option);

    switch (option){
      case 1:
      do{
        printf("\nMenu Cliente\n");
        printf("1. Adicionar Reserva\n");
        printf("2. Listar Veiculos\n");
        printf("3. Sair\n");
        printf("Escolha a sua opcao: ");

        scanf("%d", &option);

        switch (option)
        {
        case 1:
        retorno1 = listarVeiculosDisponiveis(listaVeiculos);
        if(retorno1 == 1){
          fazerReserva(listaClientes, listaVeiculos);
        }
        break;
        case 2:
        listarVeiculos(listaVeiculos);
        break;
        default:
        printf("Opcao Invalida.\n");
        break;
        }
      }while (option != 3);
      
      break;
      case 2:
      printf("\nLogin Gestor\n");
      printf("Insira o seu Id:");
      scanf("%d",&id);
      printf("Insira a sua password:");
      scanf("%s", password);
      retorno = LoginGestor(listaGestores,id,password); // a funcionar
      if(retorno == 1){
        do{
          printf("\nMenu Gestor:\n");
          printf("1. Menu Gerir Cliente\n");
          printf("2. Adicionar Gestor\n");
          printf("3. Remover Gestor\n");
          printf("4. Alterar Dados Gestor\n");
          printf("5. Alterar Saldo a Cliente\n");
          printf("6. Abrir Menu Meio de Mobilidade\n");
          printf("7. Abrir Menu Grafo\n");
          printf("8. Sair\n");
          printf("Escolha a sua opcao: ");

          scanf("%d", &option);
          switch (option){
            case 1:
            do{
            printf("\nMenu Cliente:\n");
            printf("1. Inserir Novo Cliente\n");
            printf("2. Remover Cliente\n");
            printf("3. Alterar Dados do Cliente\n");
            printf("4. Listar Clientes\n");
            printf("5. Sair\n");
            printf("Escolha a sua opcao: ");

            scanf("%d", &option);

            switch (option){
            case 1:
            inserirCliente(&listaClientes); // feito
            break;
            case 2:
            printf("Insira o nif que deseja remover: ");
            scanf("%d",&nif);
            removerCliente(nif, &listaClientes); // feito
            break;
            case 3:
            printf("Insira o nif que deseja alterar: ");
            scanf("%d",&nif);
            alterarCliente(nif, listaClientes); // nao esta a funcionar corretamente
            break;
            case 4:
            listarClientes(listaClientes); //feito
            break;
            default:
            printf("Opcao Invalida.\n");
            break;
            }
          }while (option != 8);
            break;
            case 2:
            adicionarGestor(&listaGestores);//feito
            break;
            case 3:
            listarGestores(listaGestores); //feito
            printf("Insira o ID do gestor que quer remover:");
            scanf("%d",&id);
            removerGestor(id,&listaGestores);
            break;
            case 4:
            alterarGestor(listaGestores,id);//nao esta a funcionar corretamente
            break;
            case 5:
            printf("Insira o NIF do cliente que quer adicionar saldo: ");
            scanf("%d", &nif);
            alterarSaldo(nif,listaClientes);
            break;
            case 6:
            do{
              printf("\nMenu Veiculos\n");
              printf("1. Adicionar Veiculo\n");
              printf("2. Remover Veiculo\n");
              printf("3. Alterar Dados Veiculo\n");
              printf("4. Listar por ordem decrescente de autonomia\n");
              printf("5. Listar por localizacao\n");
              printf("6. Sair\n");
              printf("Escolha a sua opcao: ");

              scanf("%d", &option);
              switch (option) {
              case 1:
              adicionarVeiculo(&listaVeiculos); // nao funciona corretamente
              break;
              case 2:
              listarVeiculos(listaVeiculos); //feito
              printf("Insira o ID do Veiculo que quer remover:");
              scanf("%d",&id);
              removerVeiculo(id,&listaVeiculos); // a funcionar
              break;
              case 3:
              listarVeiculos(listaVeiculos); //feito
              printf("Insira o ID do Veiculo que quer alterar:");
              scanf("%d",&id);
              alterarVeiculo(&listaVeiculos,id);//nao funciona corretamente
              break;
              case 4:
              listarVeiculosPorAutonomiaDecrescente(listaVeiculos); // a funcionar
              break;
              case 5:
              printf("Qual a localizacao que procura:");
              scanf("%s",localizacao);
              listarVeiculosPorLocalizacao(listaVeiculos, localizacao); // a funcionar
              break;
              default:
              printf("Opcao Invalida.\n");
              break;
              }
            }while (option != 6);
            case 7:
            do{
              printf("\nMenu Grafos\n");
              printf("1. Adicionar Aresta\n");
              printf("2. Adicionar Vertice\n");
              printf("3. Inserir Meio em Localizacao\n");
              printf("4. Listar Veiculos por Vertice\n");
              printf("5. Listar Todas os Vertices e Arestas\n");
              printf("6. Sair\n");
              printf("Escolha a sua opcao: ");
              scanf("%d", &option);
              switch (option) {
              case 1:
              printf("Insira a localizacao do vertice de origem: ");
              scanf("%s",verticeOrigem);
              printf("Insira a localizacao do vertice de destino: ");
              scanf("%s",verticeDestino);
              printf("Insira a distancia entre vertices: ");
              scanf("%f",&distancia);
              criarAresta(&listaGrafos,&listaArestas,verticeOrigem,verticeDestino,distancia);
              break;
              case 2:
              printf("Insira a localizacao do vertice:");
              scanf("%s",vertice);
              adicionarVertice(&listaGrafos,vertice);
              break;
              case 3:
              printf("Insira a localizacao do vertice:");
              scanf("%s",vertice);
              listarVeiculosDisponiveis(listaVeiculos);
              printf("Insira o codigo do veiculo que quer inserir:");
              scanf("%d",&id);
              inserirVeiculoEmVertice(listaGrafos,vertice,id,listaVeiculos);
              break;
              case 4:
              printf("Insira a localizacao do vertice:");
              scanf("%s",vertice);
              listarVeiculosPorVertice1(listaGrafos,listaVeiculos,vertice);
              break;
              case 5:
              listarArestas(listaArestas);
              break;
              case 6:
              
              break;
              default:
              printf("Opcao Invalida.\n");
              break;
              }
            }while (option != 6);
            break;
            default:
            printf("Opcao Invalida.\n");
            break;
          }
        }while (option != 7);
      break;
      printf("Opcao Invalida.\n");
      break;
      }
    }
  }while (option != 3);
  
  return 0;
}

