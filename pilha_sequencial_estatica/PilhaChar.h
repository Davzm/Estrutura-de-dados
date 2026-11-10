#ifndef PILHA_CHAR_H
#define PILHA_CHAR_H

typedef struct pilha Pilha;

Pilha* cria_Pilha(int capacidade);

void libera_Pilha(Pilha *pi);

int tamanho_Pilha(Pilha *pi);

int Pilha_cheia(Pilha *pi);

int Pilha_vazia(Pilha *pi);

int insere_Pilha(Pilha *pi, char c);

int remove_Pilha(Pilha *pi);

int consulta_topo_Pilha(Pilha *pi, char *c);

int verifica_delimitadores(const char *expr);


#endif /* PILHA_CHAR_H */