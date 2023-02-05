#include <stdio.h>

// informações já conhecidas
#define CORTAVEL    0
#define NAO_CORTAVEL    1
#define OBSTACULO   2
#define CORTADO     3

// informações preenchidas no portal web
#define TAMANHO_BLOCO   0.3 // diâmetro da hélice (30 cm)
#define LARGURA 20 
#define ALTURA  20 // dimensões do terreno em metros

// informações passadas pro microprocessador
#define LINHAS (const __uint16_t) (ALTURA/TAMANHO_BLOCO) // nº de quadrados de tamanho = TAMANHO_BLOCO ao longo da altura do terreno
#define COLUNAS (const __uint16_t) (LARGURA/TAMANHO_BLOCO) // nº de quadrados de tamanho = TAMANHO_BLOCO ao longo da largura do terreno
#define X_INIT LINHAS - 1 
#define Y_INIT COLUNAS - 1 // coordenadas de inicio do cortador

typedef struct{
    __uint16_t x; // posição do ponto no mapa
    __uint16_t y;
    __uint8_t status; // 0 - cortável (faz rotina de cortar a grama); 1 - não cortável, mas passável (não é obstáculo, apenas desliga a hélice); 2 - não pode passar (obstáculo); 3 - já cortado (desliga a hélice)

    // custos
    __uint16_t g_cost; // custo de ir do ponto inicial até o ponto atual (diferença entre as coordenadas)
    __uint16_t h_cost; // custo de ir do ponto atual até o ponto de destino (diferença entre as coordenadas)
    __uint16_t f_cost; // custo total de ir do ponto inicial até o ponto destino (soma dos custos g e h)
} position;

typedef struct{
    position *posicao; // struct com as informações do bloco
    position *next; // próximo bloco da lista
} positionsList;

unsigned char mapa[LINHAS][COLUNAS] = {0}; // mapa completo do terreno
unsigned short int x_atual = X_INIT; // coordenadas atuais do cortador
unsigned short int y_atual = Y_INIT;
position posicao_atual; // posição atual do cortador

__uint16_t tamanho(positionsList *lista){
    __uint16_t tamanho = 0;
    while(lista->next != NULL){
        tamanho++;
        lista = lista->next;
    }
    return tamanho;
}

void add(positionsList *lista, position *posicao){
    positionsList *novo = (positionsList *) malloc(sizeof(positionsList));
    novo->posicao = posicao;
    novo->next = NULL;

    if(lista == NULL){
        lista = novo;
        return;
    }

    while(lista->next != NULL){
        lista = lista->next;
    }
    lista->next = novo;
}

void remove(positionsList *lista, position *posicao){
    positionsList *aux;

    if(lista == NULL) return; // se a lista estiver vazia, retorna (não faz nada

    if(lista->posicao == posicao){ // se o primeiro nó for a posição a ser removida
        aux = lista;
        lista = lista->next;
        free(aux); // libera o espaço de memória do nó removido
        return;
    }

    while(lista != NULL){
        if(lista->next->posicao == posicao){
            aux = lista->next;
            lista->next = lista->next->next;
            free(aux); // libera o espaço de memória do nó removido
            return;
        }
        lista = lista->next;
    }
}

void buscaVizinho(position *bloco, positionsList *lista){
    __uint16_t checkX, checkY;

    for(__uint16_t x = -1; x <= 1; x++){
        for(__uint16_t y = -1; y <= 1; y++){
            if (x == 0 && y == 0) continue; // se for o próprio bloco, não faz nada

            checkX = bloco->x + x;
            checkY = bloco->y + y;

            if(checkX >= 0 && checkX < LINHAS && checkY >= 0 && checkY < COLUNAS){
                position *vizinho = (position *) malloc(sizeof(position));
                vizinho->x = checkX;
                vizinho->y = checkY;
                vizinho->status = mapa[checkX][checkY];
                add(lista, vizinho);
            }
        }
    }
}

// função que calcula o caminho mais curto até a posição (x, y)
void A_star(__uint16_t x_dest, __uint16_t y_dest){
    // TODO 4 threads para irem até os 8 blocos adjacentes de cada nó 
    
    positionsList *open = NULL; // array de nós que ainda não foram avaliados
    positionsList *closed = NULL; // array de nós que já foram avaliados
    positionsList *HEAD[2] = {NULL, NULL, NULL}; // HEAD da lista open e closed
    positionsList *vizinhos; // lista de vizinhos do nó atual
    positon *current = NULL; // nó atual

    // adiciona o ponto inicial na array de não avaliados (open)
    add(open, &posicao_atual);
    HEAD[0] = open;
    HEAD[1] = closed;
    HEAD[3] = vizinhos;

    while(tamanho(listsHEAD[0]) > 0){
        open = HEAD[0]; // atualiza o HEAD da lista open
        closed = HEAD[1]; // atualiza o HEAD da lista closed

        current = open->posicao; // pega o primeiro nó da array de não avaliados

        while(open != NULL){ 
            // pega o nó com menor custo f da array de não avaliados
            if(open->posicao->f_cost < current->f_cost || (open->posicao->f_cost == current->f_cost && open->posicao->h_cost < current->h_cost)){
                current = open->posicao;
            }
            open = open->next;
        }

        remove(HEAD[0], current); // remove o nó atual da array de não avaliados
        add(HEAD[1], current); // adiciona o nó atual na array de já avaliados

        if(current->x == x_dest && current->y == y_dest) return; // se o nó atual for o destino, para o loop

        for(vizinhos = HEAD[3]; vizinhos->next != NULL; vizinhos=vizinhos->next){
            if(vizinhos->posicao->status == OBSTACULO || vizinhos->posicao->status == JA_CORTADO) continue; // se o vizinho for obstáculo ou ja foi cortado, ignora
        }

        // se nao, para cada adjacente do current
            // se o adjacete for obstáculo ou ja foi avaliado, ignora

            // se o caminho pro adjacente for melhor que o caminho anterior ou o adjacente nao estiver em nao avaliados
                // calcula o custo f do adjacente
                // adiciona o adjacente como filho do current
                // se o adjacente nao estiver em open, adiciona ele em open
        // se o adjacente estiver na array de já avaliados, ignora
    }

}

int main(){
    
    // varre o mapa de cima pra baixo procurando por cortáveis
    for(__uint16_t i = 0; i < LINHAS; i++){
        for(__uint16_t j = 0; j < COLUNAS; j++){
            posicao_atual = (position){x_atual, y_atual, mapa[x_atual][y_atual], 0, 0, 0}; // atualiza a posição atual do cortador
            if(mapa[i][j]) continue; // se a posição não for cortável, não precisa ir até ela
            // se a posição for cortável, precisa ir até ela
            A_star(i, j); // calcula o caminho mais curto até a posição (i, j)
        }
    }

    return 0;
}