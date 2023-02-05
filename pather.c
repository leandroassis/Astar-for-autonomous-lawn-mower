#include <stdio.h>

// informações preenchidas no portal web
#define TAMANHO_BLOCO   0.3 // diâmetro da hélice (30 cm)
#define LARGURA 20 
#define ALTURA  20 // dimensões do terreno em metros

// informações passadas pro microprocessador
#define LINHAS (const int) (ALTURA/TAMANHO_BLOCO) // nº de quadrados de tamanho = TAMANHO_BLOCO ao longo da altura do terreno
#define COLUNAS (const int) (LARGURA/TAMANHO_BLOCO) // nº de quadrados de tamanho = TAMANHO_BLOCO ao longo da largura do terreno
#define X_INIT LINHAS - 1 
#define Y_INIT COLUNAS - 1 // coordenadas de inicio do cortador

typedef struct{
    __uint16_t x; // posição do ponto no mapa
    __uint16_t y;
    __uint8_t status; // 0 - cortável (faz rotina de cortar a grama); 1 - não cortável, mas passável (não é obstáculo, apenas desliga a hélice); 2 - não pode passar (obstáculo); 3 - já cortado (desliga a hélice)

    position *esquerda; // ponteiro para os prróximos nós da árvore	
    position *direita;
    position *cima;
    position *baixo;
} position;

unsigned char mapa[LINHAS][COLUNAS] = {0}; // mapa completo do terreno
position *caminho = NULL; // ponteiro com a árvore do mapa construída a partir do ponto inicial (recebido via web)
unsigned short int x_atual = X_INIT; // coordenadas atuais do cortador
unsigned short int y_atual = Y_INIT;


// função que calcula o caminho mais curto até a posição (x, y)
void A_star(__uint16_t x, __uint16_t y){
    // TODO
}

int main(){
    
    for(__uint16_t i = 0; i < LINHAS; i++){
        for(__uint16_t j = 0; j < COLUNAS; j++){
            if(mapa[i][j]) continue; // se a posição não for cortável, não precisa ir até ela
            // se a posição for cortável, precisa ir até ela
            A_star(i, j); // calcula o caminho mais curto até a posição (i, j)
        }
    }

    return 0;
}