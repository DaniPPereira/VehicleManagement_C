#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#include "header.h"


/**
 * @brief Abre o ficheiro clientes.txt, itera pela lista ligada de clientes e escreve todo o seu conteúdo no ficheiro
 * 
 * @param listaClientes apontador para o primeiro elo da lista
 * 
 */
void guardarClientesTxt(cliente *listaClientes) {
    FILE *arquivo;
    cliente *clienteAtual;

    // abre o arquivo para escrita
    arquivo = fopen("clientes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", "clientes.txt");
        return;
    }

    // percorre a lista de clientes e escreve os dados de cada um no arquivo
    clienteAtual = listaClientes;
    while (clienteAtual != NULL) {
        fprintf(arquivo, "%d;%s;%s;%.2f\n", clienteAtual->nif, clienteAtual->nome, clienteAtual->localizacao,clienteAtual->carteira.saldo);
        clienteAtual = clienteAtual->next;
    }

    // fecha o arquivo
    fclose(arquivo);
}


/**
 * The function `inserirCliente` inserts a new client into a linked list of clients, prompting the user
 * for their NIF, name, and location.
 * 
 * @param listaClientes A pointer to a pointer of type cliente.
 */
void inserirCliente(cliente **listaClientes) {
    cliente *novoCliente = (cliente*) malloc(sizeof(cliente));
    
    printf("Insira o NIF do novo cliente: ");
    scanf("%d", &novoCliente->nif);
    printf("Insira o nome do novo cliente: ");
    scanf(" %[^\n]", novoCliente->nome);
    printf("Insira a localizacao do novo cliente: ");
    scanf(" %[^\n]", novoCliente->localizacao);
    novoCliente->carteira.saldo = 0;
    
    novoCliente->next = *listaClientes;
    *listaClientes = novoCliente;
    guardarClientesTxt(*listaClientes);
    printf("Novo cliente inserido com sucesso!\n");

}

/**
 * @brief Imprime todo o conteúdo de todos os clientes da lista
 * 
 * @param listaClientes apontador para o primeiro cliente da lista
 */
void listarClientes(cliente *listaClientes) {
    cliente *clienteAtual = listaClientes;
    while (clienteAtual != NULL) {
        printf("\nNIF: %d\n", clienteAtual->nif);
        printf("Nome: %s\n", clienteAtual->nome);
        printf("Localizacao: %s\n", clienteAtual->localizacao);
        printf("Saldo: %.2f\n", clienteAtual->carteira.saldo);
        printf("\n");

        clienteAtual = clienteAtual->next;
    }
}



/**
 * @brief Lê o ficheiro linha a linha, e por cada linha, cria uma nova estrutura de cliente It reads a file line by line, and for each line, it creates a new cliente struct, fills it with the
 * e preenche o cliente com os dados do ficheiro
 * 
 * @param listaClientes apontador para o primeiro elemento da lista
 * 
 */
void lerClientesTxt(cliente **listaClientes) {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
        cliente *novoCliente = malloc(sizeof(cliente));
        if (novoCliente == NULL) {
            printf("Erro ao alocar memória.\n");
            return;
        }
        sscanf(linha, "%d;%[^;];%[^;];%f", &novoCliente->nif, novoCliente->nome, novoCliente->localizacao, &novoCliente->carteira.saldo);
        novoCliente->next = *listaClientes;
        *listaClientes = novoCliente;
    }
    printf("\nClientes Carregados com Sucesso");
    fclose(arquivo);
}

/**
 * @brief Remove um cliente da lista
 * 
 * @param nif o NIF do cliente
 * @param listaClientes apontador para o primeiro elo da lista ligada
 * 
 */
void removerCliente(int nif,cliente **listaClientes) {
    cliente *p = *listaClientes;
    cliente *anterior = NULL;

    // percorre a lista ligada até encontrar o cliente com o NIF fornecido
    while (p != NULL && p->nif != nif) {
        anterior = p;
        p = p->next;
    }

    // verifica se o cliente foi encontrado
    if (p == NULL) {
        printf("Cliente com NIF %d nao encontrado\n", nif);
        return;
    }

    // remove o cliente da lista
    if (anterior == NULL) {
        // caso seja o primeiro elemento da lista
        *listaClientes = p->next;
    } else {
        anterior->next = p->next;
    }
    free(p);
    guardarClientesTxt(*listaClientes);
    printf("Cliente com NIF %d removido com sucesso\n", nif);
}


/**
 * @brief Procura por um cliente pelo seu nif, se encontrar pede ao utilizador por novos valores
 * o nome do cliente e morada, e guarda num ficheiro texto
 * 
 * @param nif nif do cliente
 * @param listaClientes apontador para o primeiro elemento da lista ligada
 * 
 */
void alterarCliente(int nif, cliente* listaClientes) {
    cliente* p = listaClientes;
    while (p != NULL && p->nif != nif) {
        p = p->next;
    }
    if (p == NULL) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    printf("Cliente encontrado.\n");
    printf("\nNome atual: %s", p->nome);
    printf("\nInsira o novo nome:");
    scanf("%s", p->nome);
    printf("\nLocalização atual: %s", p->localizacao);
    printf("\nInsira a nova localizacao: ");
    scanf("%s", p->localizacao);
    printf("Dados do cliente alterados com sucesso.\n");
    guardarClientesTxt(p);
}



/**
 * @brief Lê um ficheiro linha a linha, e por cada linha criar uma nova estrutura gestor, e preenche
 * com conteúdo do ficheiro, e adiciona à lista
 * 
 * @param listarGestores apontador para o primeiro elo da lista
 * 
 */
void lerGestoresTxt(gestor **listarGestores) {
    FILE *arquivo = fopen("gestores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
        gestor *novoGestor = malloc(sizeof(gestor));
        if (novoGestor == NULL) {
            printf("Erro ao alocar memória.\n");
            return;
        }
        sscanf(linha, "%d;%[^;];%[^;];", &novoGestor->id, novoGestor->nome, novoGestor->password);
        novoGestor->next = *listarGestores;
        *listarGestores = novoGestor;
    }
    printf("\nGestores Carregados com Sucesso");
    fclose(arquivo);
}

/**
 * @brief Verifica se o id e a password estão corretas
 * 
 * @param listaGestores apontador para o primeiro elo da lista
 * @param id id do gestor
 * @param password password do gestor
 * 
 * @return 1 se o login foi bem sucedido, senão 0
 */
int LoginGestor(gestor *listaGestores, int id, char password[]) {
    gestor *p = listaGestores;
    while(p != NULL) {
        if(p->id == id && strcmp(p->password, password) == 0) {
            printf("Login efetuado com sucesso!\n");
            return 1;
        }
                p = p->next;
    }
    printf("ID ou senha invalidos!\n");
    return 0;
}

/**
 * @brief Imprime a lista de gestores
 * 
 * @param listaGestores aponta para o primeiro elemento da lista
 */
void listarGestores(gestor *listaGestores) {
    printf("Lista de Gestores:\n");
    printf("--------------------\n");

    gestor *p;

    for(p = listaGestores; p != NULL; p = p->next) {
        printf("ID: %d\n", p->id);
        printf("Nome do usuario: %s\n", p->nome);
        printf("Senha: %s\n", p->password);
        printf("--------------------\n");
    }
}


/**
 * @brief Abre o ficheiro gestores.txt para escrita e escreve todo o conteudo da lista ligada "listaGestores"
 * 
 * @param listaGestores apontador para o primeiro elemento da lista ligada
 * 
 */
void guardarGestoresTxt(gestor *listaGestores) {
    FILE *ficheiro = fopen("gestores.txt", "w");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.");
        return;
    }
    gestor *ptr = listaGestores;
    while (ptr != NULL) {
        fprintf(ficheiro, "%d;%s;%s\n", ptr->id, ptr->nome, ptr->password);
        ptr = ptr->next;
    }
    fclose(ficheiro);
}

/**
 * @brief Lê os dados inseridos pelo utilizador e adiciona-os à lista
 * 
 * @param listaGestores apontador para o primeiro elo da lista
 */
void adicionarGestor(gestor **listaGestores) {
    gestor *novoGestor = (gestor*) malloc(sizeof(gestor));
    printf("Insira o ID do gestor: ");
    scanf("%d", &novoGestor->id);

    // Verificar se o ID do gestor já existe na lista
    gestor *atual = *listaGestores;
    while (atual != NULL) {
        if (atual->id == novoGestor->id) {
            printf("Erro: O ID do gestor já existe. Tente novamente com um ID diferente.\n");
            return;
        }
        atual = atual->next;
    }

    printf("Insira o nome de usuario do gestor: ");
    scanf("%s", novoGestor->nome);
    printf("Insira a senha do gestor: ");
    scanf("%s", novoGestor->password);
    novoGestor->next = *listaGestores;
    *listaGestores = novoGestor;
    printf("Gestor adicionado com sucesso!\n");

    guardarGestoresTxt(*listaGestores);
}

/**
 * @brief Remove um gestor da lista ligada e guarda a lista em ficheiro
 * 
 * @param id id do gestor a ser removido
 * @param listaGestores apontador  para o primeiro elo da lista
 * 
 */
void removerGestor(int id,gestor **listaGestores) {
    gestor *p = *listaGestores;
    gestor *anterior = NULL;

    // percorre a lista ligada até encontrar o gestor com o ID fornecido
    while (p != NULL && p->id != id) {
        anterior = p;
        p = p->next;
    }

    // verifica se o gestor foi encontrado
    if (p == NULL) {
        printf("Gestor com ID %d nao encontrado\n", id);
        return;
    }

    // remove o gestor da lista
    if (anterior == NULL) {
        // caso seja o primeiro elemento da lista
        *listaGestores = p->next;
    } else {
        anterior->next = p->next;
    }
    free(p);
    printf("Gestor com ID %d removido com sucesso\n", id);
    
    guardarGestoresTxt(*listaGestores);
}

/**
 * @brief  Procura o gestor a partir do id dado, pede ao utilizador novos dados 
 * e guarda os novos dados em ficheiro
 * 
 * @param listaGestores pointer to the first element of the linked list
 * @param id
 * 
 * @return the pointer to the first element of the list.
 */
void alterarGestor(gestor *listaGestores, int id) {
    gestor *p = listaGestores;
    while(p != NULL) {
        if(p->id == id) {
            printf("Nome de usuario atual: %s\n", p->nome);
            printf("Insira o novo nome de usuario: ");
            scanf("%s", p->nome);
            printf("Senha atual: %s\n", p->password);
            printf("Insira a nova senha: ");
            scanf("%s", p->password);
            printf("Gestor com ID %d alterado com sucesso!\n", id);
            guardarGestoresTxt(p);
            return;
        }
        p = p->next;
    }
    printf("Gestor com ID %d nao encontrado!\n", id);
}

/**
 * @brief  Procura um cliente com o NIF dado e pede ao utilizador um valor para adicionar à carteira
 * por fim, guarda a lista já alterada em ficheiro
 * @param nif NIF do cliente
 * @param listaClientes apontador para o primeiro elo da lista
 * 
 */
void alterarSaldo(int nif, cliente *listaClientes) {
    cliente *p = listaClientes;
    while(p != NULL) {
        if(p->nif == nif) {
            float valor;
            printf("Insira o valor a adicionar: ");
            scanf("%f", &valor);
            p->carteira.saldo += valor;
            printf("Saldo adicionado com sucesso!\n");
            guardarClientesTxt(listaClientes);
            return;
        }
        p = p->next;
    }
    printf("Cliente nao encontrado!\n");
}

/**
 * @brief Abre o ficheiro meios para escrita e escreve todos os dados da lista em ficheiro
 * 
 * @param listaVeiculos apontador para o primeiro elo da lista ligada
 * 
 */
void guardarVeiculos(veiculo *listaVeiculos) {
    FILE *fp;
    fp = fopen("meios.txt", "w");
    if(fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    veiculo *p = listaVeiculos;
    while(p != NULL) {
        fprintf(fp, "%d;%s;%.2f;%.2f;%.2f;%s;%d\n", p->id, p->tipo, p->bateria, p->autonomia, p->custo, p->localizacao, p->estado);
        p = p->next;
    }
    fclose(fp);
    printf("Lista de veiculos guardada em meios.txt.\n");
}

/**
 * @brief Lê os dados inseridos pelo utilizador e adiciona-os a uma struct veiculo se o id for inutilizado, por fim adiciona essa struct à lista
 * 
 * @param listaVeiculos apontador para o primeiro elo da lista ligada
 */
void adicionarVeiculo(veiculo **listaVeiculos) {
    veiculo *novoVeiculo = (veiculo*) malloc(sizeof(veiculo));
    printf("Insira o codigo do veiculo: ");
    scanf("%d", &novoVeiculo->id);

    // verifica se o ID já existe na lista de veículos
    veiculo *atual = *listaVeiculos;
    while (atual != NULL) {
        if (atual->id == novoVeiculo->id) {
            printf("Ja existe um veiculo com esse codigo!\n");
            free(novoVeiculo);
            return;
        }
        atual = atual->next;
    }

    printf("Insira o tipo de veiculo: ");
    scanf("%s", novoVeiculo->tipo);
    printf("Insira o nivel de bateria do veiculo: ");
    scanf("%f", &novoVeiculo->bateria);
    printf("Insira a autonomia do veiculo: ");
    scanf("%f", &novoVeiculo->autonomia);
    printf("Insira o custo por minuto do veiculo: ");
    scanf("%f", &novoVeiculo->custo);
    printf("Insira a localizacao do veiculo: ");
    scanf("%s", novoVeiculo->localizacao);
    printf("Insira o estado do veiculo (0-Disponivel / 1- Reservado):");
    scanf("%d",&novoVeiculo->estado);

    novoVeiculo->next = *listaVeiculos;
    *listaVeiculos = novoVeiculo;
    printf("Veiculo adicionado com sucesso!\n");

    guardarVeiculos(*listaVeiculos);
}



/**
 * @brief Lê o ficheiro meios.txt e carrega o seu conteudo para a lista ligada
 * 
 * @param listaVeiculos pointer to a pointer to a veiculo struct
 * 
 */
void lerMeios(veiculo **listaVeiculos) {
    FILE *ficheiro;
    ficheiro = fopen("meios.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro de veiculos!\n");
        return;
    }

    char linha[100];
    while (fgets(linha, 100, ficheiro) != NULL) {
        veiculo *novoVeiculo = (veiculo*) malloc(sizeof(veiculo));
        sscanf(linha, "%d;%[^;];%f;%f;%f;%[^;];%d", &novoVeiculo->id, novoVeiculo->tipo, &novoVeiculo->bateria, &novoVeiculo->autonomia, &novoVeiculo->custo, novoVeiculo->localizacao, &novoVeiculo->estado);
        novoVeiculo->next = *listaVeiculos;
        *listaVeiculos = novoVeiculo;
    }

    fclose(ficheiro);
    printf("\nVeiculos carregados com sucesso!\n");
}

/**
 * @brief Remove um veiculo da lista e guarda a lista em ficheiro
 * 
 * @param id Id do veiculo a ser removido
 * @param listaVeiculos pointer to the first element of the linked list
 * 
 */
void removerVeiculo(int id, veiculo **listaVeiculos) {
    veiculo *atual = *listaVeiculos;
    veiculo *anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        printf("Erro: Veiculo com ID %d nao encontrado.\n", id);
        return;
    }

    if (anterior == NULL) {
        // O veículo a remover é o primeiro da lista
        *listaVeiculos = atual->next;
    } else {
        anterior->next = atual->next;
    }

    free(atual);
    printf("Veiculo com ID %d removido com sucesso.\n", id);

    guardarVeiculos(*listaVeiculos);
}

/**
 * @brief Imprime os todos os veiculos na lista ligada
 * 
 * @param listaVeiculos pointer to the first element of the list
 */
void listarVeiculos(veiculo *listaVeiculos) {
    if (listaVeiculos == NULL) {
        printf("Lista de veiculos vazia!\n");
    } else {
        printf("\nLista de veiculos:\n");
        veiculo *ptr = listaVeiculos;
        while (ptr != NULL) {
            printf("\nID: %d\n", ptr->id);
            printf("Tipo: %s\n", ptr->tipo);
            printf("Bateria: %.2f%%\n", ptr->bateria);
            printf("Autonomia: %.2f km\n", ptr->autonomia);
            printf("Custo: %.2f Euro/min\n", ptr->custo);
            printf("Localizacao: %s\n", ptr->localizacao);
            printf("\n");
            ptr = ptr->next;
        }
    }
}

/**
 * @brief Cria um vetor com o mesmo tamanho da lista, copia os elementos da lista para o vetor, 
 * organiza por autonomia, e imprime o vetor
 * 
 * @param listaVeiculos pointer to the first element of the linked list
 */
void listarVeiculosPorAutonomiaDecrescente(veiculo *listaVeiculos) {
    int tamLista = 0;
    veiculo *aux = listaVeiculos;

    // determina o tamanho da lista
    while (aux != NULL) {
        tamLista++;
        aux = aux->next;
    }

    // cria vetor auxiliar para armazenar os veículos
    veiculo *vetorAux = malloc(sizeof(veiculo) * tamLista);
    aux = listaVeiculos;

    // copia os veículos da lista para o vetor auxiliar
    for (int i = 0; i < tamLista; i++) {
        vetorAux[i] = *aux;
        aux = aux->next;
    }

    // ordena o vetor pelo campo "autonomia" em ordem decrescente
    for (int i = 0; i < tamLista; i++) {
        for (int j = i + 1; j < tamLista; j++) {
            if (vetorAux[j].autonomia > vetorAux[i].autonomia) {
                veiculo temp = vetorAux[i];
                vetorAux[i] = vetorAux[j];
                vetorAux[j] = temp;
            }
        }
    }

    // imprime a lista ordenada
    printf("Meios de mobilidade eletrica por ordem decrescente de autonomia:\n");
    for (int i = 0; i < tamLista; i++) {
        printf("ID: %d | Tipo: %s | Autonomia: %.2f\n", vetorAux[i].id, vetorAux[i].tipo, vetorAux[i].autonomia);
    }

    free(vetorAux);
}

/**
 * @brief Cria uma nova lista de veiculos que estao na mesma localização e imprime essa lista
 * 
 * @param listaVeiculos pointer to the first element of the linked list
 * @param localizacao localização do veiculo
 */
void listarVeiculosPorLocalizacao(veiculo *listaVeiculos, char localizacao[20]) {
    veiculo *atual = listaVeiculos;
    veiculo *veiculosLocalizacao = NULL;
    int count = 0;
    while (atual != NULL) {
        if (strcmp(atual->localizacao, localizacao) == 0) {
            veiculo *novo = malloc(sizeof(veiculo));
            novo->id = atual->id;
            strcpy(novo->tipo, atual->tipo);
            novo->bateria = atual->bateria;
            novo->autonomia = atual->autonomia;
            novo->custo = atual->custo;
            strcpy(novo->localizacao, atual->localizacao);
            novo->next = NULL;

            if (veiculosLocalizacao == NULL) {
                veiculosLocalizacao = novo;
            } else {
                veiculo *ultimo = veiculosLocalizacao;
                while (ultimo->next != NULL) {
                    ultimo = ultimo->next;
                }
                ultimo->next = novo;
            }

            count++;
        }

        atual = atual->next;
    }

    if (count == 0) {
        printf("Nao foram encontrados veiculos na localizacao especificada.\n");
    } else {
        printf("Veiculos encontrados na localizacao %s:\n", localizacao);
        printf("--------------------------------------------------\n");
        printf("| ID |     Tipo     | Bateria | Autonomia |  Custo |\n");
        printf("--------------------------------------------------\n");

        atual = veiculosLocalizacao;
        while (atual != NULL) {
            printf("| %2d | %-12s | %6.2f%% | %8.2f | %6.2f |\n", atual->id, atual->tipo, atual->bateria, atual->autonomia, atual->custo);
            atual = atual->next;
        }
        printf("--------------------------------------------------\n");
    }
}

/**
 * Procura um veiculo pelo id dado pelo utilizador, altera os seu valores, e guarda a lista

 * 
 * @param listaVeiculos pointer to the first element of the linked list
 * @param id id do veiculo a ser alterado
 * 
 */
void alterarVeiculo(veiculo **listaVeiculos, int id) {
    veiculo *atual = *listaVeiculos;
    int option;

    while (atual != NULL) {
        if (atual->id == id) {
            do
            {
                printf("\nAlterar Dados:\n");
                printf("1. Alterar Dados do Veiculo\n");
                printf("2. Alterar Apenas Estado\n");
                printf("3. Sair\n");

                scanf("%d",&option);

                switch (option)
                {
                case 1:
                printf("Novo tipo: ");
                scanf("%s", atual->tipo);
                printf("Nova bateria (em porcentagem): ");
                scanf("%f", &atual->bateria);
                printf("Nova autonomia: ");
                scanf("%f", &atual->autonomia);
                printf("Novo custo (por minuto): ");
                scanf("%f", &atual->custo);
                printf("Nova localizacao: ");
                scanf("%s", atual->localizacao);
                printf("Dados do veiculo alterados com sucesso.\n");
                guardarVeiculos(atual);
                return;
                break;
                case 2:
                if(atual->estado == 1){
                    atual->estado = 0;
                    printf("O veiculo ja nao esta reservado\n");
                    guardarVeiculos(atual);
                }
                else {
                    atual->estado = 1;
                    printf("O veiculo esta reservado\n");
                    guardarVeiculos(atual);
                }
                return;
                break;
                default:
                printf("Opcao Invalida.\n");
                break;
                }
            } while (option != 3);
            
        }
        atual = atual->next;
    }

    printf("Veiculo com o codigo %d nao encontrado.\n", id);
    return;
}



/**
 * @brief It checks if the vehicle exists, if it's available, if the client exists, and if everything is ok,
 * it changes the vehicle's state to reserved
 * 
 * @param listaClientes a pointer to the first element of a linked list of clients
 * @param listaVeiculos pointer to the first element of the linked list of vehicles
 * 
 * @return a pointer to a cliente struct.
 */
void fazerReserva(cliente *listaClientes, veiculo *listaVeiculos) {
    int codigoVeiculo;
    printf("Insira o codigo do veiculo que deseja reservar: ");
    scanf("%d", &codigoVeiculo);

    // verifica se o veículo existe
    veiculo *veic = listaVeiculos;
    while (veic != NULL) {
        if (veic->id == codigoVeiculo) {
            break;
        }
        veic = veic->next;
    }
    if (veic == NULL) {
        printf("O veiculo com o codigo %d nao existe.\n", codigoVeiculo);
        return;
    }

    // verifica se o veículo está disponível
    if (veic->estado != 0) {
        printf("O veiculo com o codigo %d nao esta disponivel para reserva.\n", codigoVeiculo);
        return;
    }

    // verifica se o cliente existe
    int idCliente;
    printf("Insira o seu NIF: ");
    scanf("%d", &idCliente);
    cliente *cl = listaClientes;
    while (cl != NULL) {
        if (cl->nif == idCliente) {
            break;
        }
        cl = cl->next;
    }
    if (cl == NULL) {
        printf("O cliente com o NIF %d nao existe.\n", idCliente);
        return;
    }
    // faz a reserva
    veic->estado = 1;
    printf("Reserva efetuada com sucesso!\n");

    // guarda as alterações nos ficheiros
    guardarClientesTxt(listaClientes);
    guardarVeiculos(listaVeiculos);
}


/**
 * @brief Imprime a informação dos veiculos
 * 
 * @param listaVeiculos pointer to the first element of the list
 * 
 * @return the value of the variable "ptr->estado"
 */
int listarVeiculosDisponiveis(veiculo *listaVeiculos) {
    if (listaVeiculos == NULL ) {
        printf("Lista de veiculos vazia!\n");
    } else {
        printf("\nLista de veiculos disponiveis:\n");
        veiculo *ptr = listaVeiculos;
        do{
            if(ptr->estado == 0){
                printf("\nID: %d\n", ptr->id);
                printf("Tipo: %s\n", ptr->tipo);
                printf("Bateria: %.2f%%\n", ptr->bateria);
                printf("Autonomia: %.2f km\n", ptr->autonomia);
                printf("Custo: %.2f Euro/min\n", ptr->custo);
                printf("Localizacao: %s\n", ptr->localizacao);
                printf("\n");
                ptr = ptr->next;
                return 1;
            }
            else return 0;
        } while (ptr != NULL);
    }
    return 0;
}

/**
 * @brief Lê os vertices de um ficheiro e cria uma lista ligada com a informação
 * 
 * @param listaVertices a pointer to a pointer of type "vertice", which represents a linked list of
 * vertices. The function reads vertex names from a file and creates a new "vertice" struct for each
 * name, then adds it to the end of the linked list pointed to by "listaVertices". If the list
 * 
 * @return Nothing is being returned, the function has a void return type.
 */
void lerVertices(vertice** listaVertices) {
    FILE* arquivo = fopen("vertices.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[50];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';

        // Cria um novo vértice
        vertice* novoVertice = (vertice*)malloc(sizeof(vertice));
        strcpy(novoVertice->verticeOrigem, linha);
        novoVertice->next = NULL;

        if (*listaVertices == NULL) {
            *listaVertices = novoVertice;
        } else {
            vertice* temp = *listaVertices;
            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = novoVertice;
        }
    }

    fclose(arquivo);
    printf("Vertices Carregados com Sucesso\n");
}



/**
 * The function saves a list of vertices to a file named "vertices.txt".
 * 
 * @param listaVertices a pointer to the first node of a linked list of vertices. Each node contains a
 * string representing the name of a vertex and a pointer to the next node in the list.
 * 
 * @return The function is not returning anything, it is a void function.
 */
void guardarListaVertices(vertice* listaVertices) {
    FILE* arquivo = fopen("vertices.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    vertice* temp = listaVertices;
    while (temp != NULL) {
        fprintf(arquivo, "%s\n", temp->verticeOrigem);
        temp = temp->next;
    }
    
    fclose(arquivo);
    printf("Lista de vértices foi salva no arquivo \"vertices.txt\".\n");
}


/**
 * @brief This function adds a new vertex to a linked list of vertices, checking if it already exists.
 * 
 * @param listaVertices a pointer to a pointer of type "vertice", which represents a linked list of
 * vertices.
 * @param nomeVertice a string representing the name of the vertex to be added to the list of vertices.
 */
void adicionarVertice(vertice** listaVertices, char* nomeVertice) {
    vertice* temp = *listaVertices;
    while (temp != NULL) {
        if (strcmp(temp->verticeOrigem, nomeVertice) == 0) {
            printf("\nEsse vertice ja existe");
        }
        temp = temp->next;
    }

    vertice* novoVertice = (vertice*)malloc(sizeof(vertice));
    strcpy(novoVertice->verticeOrigem, nomeVertice);
    novoVertice->next = NULL;

    if (*listaVertices == NULL) {
        *listaVertices = novoVertice;
    } else {
        temp = *listaVertices;
        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = novoVertice;
    }
    guardarListaVertices(*listaVertices);

}

/**
 * @brief The function checks if a vertex exists in a linked list of vertices.
 * 
 * @param listaVertices a pointer to the first node of a linked list of vertices.
 * @param verticeNome a string representing the name of the vertex being searched for in the linked
 * list of vertices.
 * 
 * @return an integer value of either 1 or 0. 1 is returned if the vertex with the given name is found
 * in the linked list of vertices, and 0 is returned if it is not found.
 */
int existeVertice(vertice* listaVertices, char verticeNome[]) {
    vertice* temp = listaVertices;
    while (temp != NULL) {
        if (strcmp(temp->verticeOrigem, verticeNome) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

/**
 * @brief This function creates a new edge between two vertices and adds it to the list of edges.
 * 
 * @param listaVertices a pointer to the head of a linked list of vertices
 * @param listaArestas a pointer to the head of a linked list of vertices, where each vertex represents
 * a source vertex and contains a linked list of its outgoing edges (destinations and distances).
 * @param verticeOrigem A string representing the name of the origin vertex of the edge being created.
 * @param verticeDestino The destination vertex of the edge being created.
 * @param distancia The distance between the origin vertex and the destination vertex.
 */
void criarAresta(vertice** listaVertices, vertice** listaArestas, char verticeOrigem[], char verticeDestino[], float distancia) {
    vertice* origem = *listaVertices;
    while (origem != NULL && strcmp(origem->verticeOrigem, verticeOrigem) != 0) {
        origem = origem->next;
    }

    vertice* destino = *listaVertices;
    while (destino != NULL && strcmp(destino->verticeOrigem, verticeDestino) != 0) {
        destino = destino->next;
    }

    if (origem != NULL && destino != NULL) {
        // Cria uma nova aresta
        aresta* novaAresta = malloc(sizeof(aresta));
        strcpy(novaAresta->verticeDestino, verticeDestino);
        novaAresta->distancia = distancia;
        novaAresta->next = origem->arestas;
        origem->arestas = novaAresta;

        vertice* temp = *listaArestas;
        while (temp != NULL && strcmp(temp->verticeOrigem, verticeOrigem) != 0) {
            temp = temp->next;
        }

        if (temp == NULL) {
            vertice* novoVertice = malloc(sizeof(vertice));
            strcpy(novoVertice->verticeOrigem, verticeOrigem);
            novoVertice->arestas = novaAresta;
            novoVertice->next = *listaArestas;
            *listaArestas = novoVertice;
        } else {
            novaAresta->next = temp->arestas;
            temp->arestas = novaAresta;
        }

        printf("Aresta criada entre %s e %s com distancia %.2f\n", verticeOrigem, verticeDestino, distancia);
    } else {
        printf("Vertice de origem ou destino nao encontrado.\n");
    }
}

/**
 * This function inserts a vehicle into a vertex in a graph data structure.
 * 
 * @param listaVertices a pointer to the linked list of vertices
 * @param verticeNome A string representing the name of the vertex where the vehicle will be inserted.
 * @param codigoVeiculo The parameter "codigoVeiculo" is an integer representing the code of a vehicle
 * that needs to be inserted into a vertex.
 * @param listaVeiculos a pointer to the head of a linked list of vehicles.
 * 
 * @return void, meaning it does not return any value but instead performs certain actions within the
 * function.
 */
void inserirVeiculoEmVertice(vertice* listaVertices, char verticeNome[], int codigoVeiculo, veiculo* listaVeiculos) {
    vertice* temp = listaVertices;
    while (temp != NULL) {
        if (strcmp(temp->verticeOrigem, verticeNome) == 0) {
            veiculo* tempVeiculo = listaVeiculos;
            while (tempVeiculo != NULL) {
                if (tempVeiculo->id == codigoVeiculo) {
                    strcpy(tempVeiculo->localizacao, verticeNome);
                    
                    printf("Veiculo inserido no vertice %s.\n", verticeNome);
                    guardarVeiculos(tempVeiculo);
                    return;
                }
                tempVeiculo = tempVeiculo->next;
            }
            
            printf("Veiculo com o codigo %d nao encontrado no vertice %s.\n", codigoVeiculo, verticeNome);
            return;
        }
        temp = temp->next;
    }
    
    printf("Vertice %s nao encontrado.\n", verticeNome);
}


/**
 * The function lists all vehicles located at a specific vertex.
 * 
 * @param listaVeiculos a pointer to the first element of a linked list of veiculo structs
 * @param verticeNome A string representing the name of a vertex in a graph.
 */
void listarVeiculosPorVertice(veiculo* listaVeiculos, char verticeNome[]) {
    veiculo* tempVeiculo = listaVeiculos;
    while (tempVeiculo != NULL) {
        if (strcmp(tempVeiculo->localizacao, verticeNome) == 0) {
            printf("\nVeiculo ID: %d\n", tempVeiculo->id);
            printf("Tipo: %s\n", tempVeiculo->tipo);
            printf("Bateria: %.2f\n", tempVeiculo->bateria);
            printf("Autonomia: %.2f\n", tempVeiculo->autonomia);
            printf("Custo: %.2f\n", tempVeiculo->custo);
            printf("Localizacaoo: %s\n", tempVeiculo->localizacao);
            printf("Estado: %d\n", tempVeiculo->estado);
            printf("-----------------------\n");
        }
        tempVeiculo = tempVeiculo->next;
    }
}

/**
 * This function lists the vehicles in a given vertex if it exists, otherwise it prints an error
 * message.
 * 
 * @param listaVertices a pointer to the linked list of vertices in the graph
 * @param listaVeiculos It is a pointer to the head of a linked list of veiculos (vehicles).
 * @param verticeNome A string representing the name of a vertex in a graph.
 */
void listarVeiculosPorVertice1(vertice* listaVertices, veiculo* listaVeiculos, char verticeNome[]) {
    if (existeVertice(listaVertices, verticeNome)) {
        printf("Veiculos no vertice %s:\n", verticeNome);
        listarVeiculosPorVertice(listaVeiculos, verticeNome);
    } else {
        printf("Vertice %s nao encontrado.\n", verticeNome);
    }
}



/**
 * The function "listarArestas" prints out information about the edges of a graph.
 * 
 * @param listaArestas a pointer to the first node of a linked list of vertices, where each vertex
 * contains a linked list of edges/connections to other vertices.
 */
void listarArestas(vertice* listaArestas) {
    vertice* temp = listaArestas;
    while (temp != NULL) {
        printf("\nVertice de origem: %s\n", temp->verticeOrigem);

        aresta* tempAresta = temp->arestas;
        while (tempAresta != NULL) {
            printf("Vertice de destino: %s\n", tempAresta->verticeDestino);
            printf("Distancia: %.2f\n", tempAresta->distancia);
            printf("-----------------------\n");

            tempAresta = tempAresta->next;
            break;
        }

        temp = temp->next;
    }
}


/**
 * This function loads edges from a file and creates them in a graph represented by a list of vertices
 * and a list of edges.
 * 
 * @param listaVertices a pointer to a pointer of vertices, which is a data structure representing a
 * graph where each vertex has a list of adjacent vertices.
 * @param listaArestas A pointer to a pointer of type "vertice", which represents a linked list of
 * edges.
 * 
 * @return The function is not returning anything, it is a void function.
 */
void carregarArestasDeArquivo( vertice** listaVertices, vertice** listaArestas) {
    FILE* arquivo = fopen("arestas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char verticeOrigem[50];
        char verticeDestino[50];
        float distancia;
        
        sscanf(linha, "%[^;];%[^;];%f", verticeOrigem, verticeDestino, &distancia);
        
        criarAresta(listaVertices, listaArestas, verticeOrigem, verticeDestino, distancia);
    }
    
    fclose(arquivo);
}







