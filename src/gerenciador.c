/* Gerenciador de Estoque
 *
 * Estrutura de Dados I
 *
 * Gabriel Sales Gerardo
 * João Pedro da Costa Reis
 * Matheus Sousa Marinho
 *
 * Gerenciador v3.14
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "libtools.h"
#include <time.h>

// STRUCT
typedef struct Produto {
    int NP;              // Número do Pedido
    float distancia;     // Distância a percorrer
    int data_entrega;    // Data de entrega
    struct Produto *prox; // Ponteiro para o próximo produto
} Produto;

typedef struct Lista{
	struct Produto *inicio;
	struct Produto *fim;
}Lista;

// Pointers aux
Produto *aux;
Produto *anterior;

Lista* criarLista(){
	Lista *lista = (Lista*)malloc(sizeof(Lista));
	if(lista != NULL){
		lista->inicio = NULL;
		lista->fim = NULL;
	}
	return lista;
}

// FUNC
int verificarNP(Lista *l, int NP) {
    Produto *aux = l->inicio;
    while (aux != NULL) {
        if (aux->NP == NP) { // Comparação pelo N° do Pedido
            return 1;        // Pedido já existe
        }
        aux = aux->prox;
    }
    return 0;                // Pedido não encontrado
}

void adicionarProduto(Lista *l) {
    Produto *novo = (Produto *)malloc(sizeof(Produto));
    if (l == NULL) {
        printf("Erro: lista não inicializada.\n");
        return;
    }
    if (novo == NULL) {
        printf("Erro de alocação.\n");
        return;
    }

    // Dados do Produto
    int valido = 0;
    while (!valido) {
        printf("Insira o N° do Pedido: ");
        if (scanf("%d", &novo->NP) != 1) {
            printf("N° do Pedido inválido. Por favor, insira um número inteiro válido.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        } else if (novo->NP < 0) {
            printf("N° do Pedido inválido. O número não pode ser negativo.\n");
        } else if (verificarNP(l, novo->NP)) {
            printf("N° do Pedido já existente. Insira outro.\n");
        } else {
            valido = 1; // Entrada válida
        }
    }

    // Validação da distância
    valido = 0;
    while (!valido) {
        printf("Insira a distância a percorrer (em km): ");
        if (scanf("%f", &novo->distancia) != 1) {
            printf("Distância inválida. Por favor, insira um número válido.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        } else if (novo->distancia <= 0) {
            printf("A distância deve ser um valor positivo.\n");
        } else {
            valido = 1; // Entrada válida
        }
    }

    // Validação da data de entrega
    valido = 0;
    while (!valido) {
        printf("Insira a data de entrega no formato AAAAMMDD: ");
        if (scanf("%d", &novo->data_entrega) != 1) {
            printf("Data inválida. Por favor, insira um número inteiro no formato correto.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        } else if (novo->data_entrega <= 0) {
            printf("A data de entrega deve ser um número positivo no formato AAAAMMDD.\n");
        } else {
            valido = 1; // Entrada válida
        }
    }
    // Evitar a perca da lista.
    novo->prox = NULL;

    if (l->inicio == NULL) {
        l->inicio = novo;
        l->fim = novo;
    } else {
        l->fim->prox = novo;
        l->fim = novo;
    }
}

Produto *anterior;

void removerProduto(Lista *l) {
    int find;
    int num;
    if (l->inicio == NULL) {
        printf("Nenhum produto foi cadastrado.\n");
    } else {
        num = get_int("Insira o N° do Pedido a ser removido: ");
        aux = l->inicio;
        anterior = NULL;
        find = 0;

        while (aux != NULL && aux->NP != num) { // Comparação pelo N° do Pedido
            anterior = aux;
            aux = aux->prox;
        }

        if (aux != NULL) {
            if (anterior == NULL) {
                l->inicio = aux->prox;
            } else {
                anterior->prox = aux->prox;
            }

            if (aux->prox == NULL) {
                l->fim = anterior;
            }

            free(aux); // Libera o produto da memória
            printf("\nProduto removido com sucesso!\n"); // Mensagem de sucesso
        } else {
            printf("\nN° do Pedido não encontrado.\n");
        }
    }
}

// Função responsável pela leitura do CSV
void lerCSV(Lista *l, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    char linha[100];

    // Ignora a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        Produto *novo = (Produto *)malloc(sizeof(Produto));
        if (novo == NULL) {
            printf("Erro de alocação de memória para o produto.\n");
            fclose(arquivo);
            return;
        }
        // Parse da linha no formato CSV
        if (sscanf(linha, "%d,%f,%d", &novo->NP, &novo->distancia, &novo->data_entrega) == 3) {
            // Verifica se o ID já existe na lista
            if (verificarNP(l, novo->NP)) {
                printf("Produto com N° do Pedido [%d] já existe. Não será adicionado.\n", novo->NP);
                free(novo); // Libera a memória alocada para o produto não adicionado
            } else {
                novo->prox = NULL;
                // Inserir o novo produto na lista
                if (l->inicio == NULL) {
                    l->inicio = novo;
                    l->fim = novo;
                } else {
                    l->fim->prox = novo;
                    l->fim = novo;
                }
            }
        } else {
            printf("Erro ao ler os dados da linha: %s\n", linha);
            free(novo); // Libera a memória alocada para um produto inválido
        }
    }
    fclose(arquivo);
    printf("Produtos carregados com sucesso!\n");
}

// Exibindo produtos
void exibirProdutos(Lista *l) {
    int i = 0;
    Produto *aux = l->inicio;

    if (aux == NULL) {
        printf("\n==========================================================\n");
        printf("||                Nenhum produto cadastrado.            ||\n");
        printf("==========================================================\n");
        return;
    }

    printf("\n==========================================================\n");
    printf("||                   LISTA DE PRODUTOS                 ||\n");
    printf("==========================================================\n");

    while (aux != NULL) {
        printf("----------------------------------------------------------\n");
        printf("|| Produto [%d]                                         ||\n", i+1);
        printf("|| N° do Pedido: %-36d ||\n", aux->NP);
        printf("|| Distância (km): %-34.2f ||\n", aux->distancia);
        printf("|| Data de entrega (AAAAMMDD): %-23d ||\n", aux->data_entrega);
        printf("----------------------------------------------------------\n");
        aux = aux->prox;
        i++;
    }

    printf("==========================================================\n");
}

// SORTING
// comparar -> dividir -> mesclar -> ordenar
// se x-y>0 logo x>y, se x-y<0, logo y>x.
int comparar(Produto *a, Produto *b) {
    // Primeiro caso: data de entrega (datas mais próximas devem vir primeiro)
    if (a->data_entrega != b->data_entrega) {
        return a->data_entrega - b->data_entrega;  // Comparação direta entre datas
    }

    // Segundo caso: distância (distâncias menores devem vir primeiro)
    if (a->distancia != b->distancia) {
        return (a->distancia < b->distancia) ? -1 : 1;  // Distâncias menores vêm antes
    }

    // Terceiro caso: Número do Pedido (menor NP vem antes)
    return a->NP - b->NP;
}

Produto* dividir(Produto *inicio){
	// posicionando os ponteiros para splitar a lista
	Produto *rapido = inicio;
	Produto *lento = inicio;
	Produto *anterior = NULL;

	while( rapido != NULL && rapido->prox != NULL){
		anterior = lento;
		lento = lento->prox; // lentos à esquerda
		rapido = rapido->prox->prox; // rapidos à direita
	}
	if( anterior != NULL){
		anterior->prox = NULL;
	}
	return lento;
}

// Iniciando o processo de MergeSort
// Passo do Merge
// e - esquerda, d - direita
Produto* mesclar(Produto *e, Produto *d, int(*comparar)(Produto*, Produto*)){
	Produto *resultado = NULL;

	if(e == NULL){
		return d;
	}
	if(d == NULL){
		return e;
	}
	if(comparar(e,d) <= 0){
		resultado = e;
		resultado->prox = mesclar(e->prox, d, comparar);
	}else{
		resultado = d;
		resultado->prox = mesclar(d->prox, e, comparar);
	}
	return resultado;
}

Produto* ordenarProdutos(Produto *inicio, int(*comparar)(Produto*, Produto*)){
	if(inicio == NULL || inicio->prox == NULL){
		return inicio;
	}

	Produto *meio = dividir(inicio);
	Produto *e = ordenarProdutos(inicio, comparar);
	Produto *d = ordenarProdutos(meio, comparar);

		return mesclar(e, d, comparar);
}

void ordenarLista(Lista *l){
	if(l->inicio == NULL){
		printf("Nenhum produto cadastrado. Impossível realizar a ordenação.");
		return;
	}
	l->inicio = ordenarProdutos(l->inicio, comparar);
	printf("\nLista ordenada com sucesso!\n");
}

void liberarLista(Lista *l) {
    if (l == NULL) return;

    Produto *aux = l->inicio;
    while (aux != NULL) {
        Produto *temp = aux;  // Guarda o nó atual
        aux = aux->prox;      // Avança para o próximo
        free(temp);           // Libera o nó atual
    }
    free(l);  // Libera a estrutura da lista
    printf("Memória liberada com sucesso.\n");
}

int main(void) {
    Lista *lista = criarLista();  // Chama a função criarLista
    if (lista == NULL) {          // Verifica se a lista foi alocada corretamente
        printf("Erro de alocação.\n");
        return 1;
    }

    int opc;
    do {
        exibirMenu();
        opc = get_int("Insira uma opção:\n ");
        switch (opc) {
            case 1:
                adicionarProduto(lista);
                break;
            case 2:
                removerProduto(lista);
                break;
            case 3:
                exibirProdutos(lista);
                printf("\n\n");
                break;
            case 4:
                ordenarLista(lista);
                break;
            case 5:
                lerCSV(lista, "dados_aleatorios.csv");  // Supondo que o arquivo CSV tenha o nome "dados1.csv"
                break;
            case 6:
                break;
        }
    } while (opc != 6);
    liberarLista(lista);  // Libera a memória alocada
    printf("Saindo do programa...");
    return 0;
}

