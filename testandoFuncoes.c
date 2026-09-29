#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Structs/lista.h"

int main(void){
    struct produto p = {1, "Produto Teste", 9.99f};

    /* ===================== lista_tem_espaco ===================== */

    assert(lista_tem_espaco(NULL, 1) == 0);
    assert(lista_tem_espaco(NULL, 0) == 0);
    printf("Caso 1 (li == NULL) OK\n");

    Lista *li = cria_lista();
    assert(li != NULL);

    assert(lista_tem_espaco(li, 1) == 1);
    assert(lista_tem_espaco(li, MAX) == 1);
    assert(lista_tem_espaco(li, MAX + 1) == 0);
    printf("Caso 2 (lista vazia) OK\n");

    for(int i = 0; i < 50; i++){
        p.codigo = i;
        int ok = insere_lista_final(li, p);
        assert(ok == 1);
    }
    assert(tamanho_lista(li) == 50);

    assert(lista_tem_espaco(li, MAX - 50) == 1);
    assert(lista_tem_espaco(li, MAX - 50 + 1) == 0);
    printf("Caso 3 (lista parcialmente cheia) OK\n");

    for(int i = 50; i < MAX; i++){
        p.codigo = i;
        int ok = insere_lista_final(li, p);
        assert(ok == 1);
    }
    assert(lista_cheia(li) == 1);

    assert(lista_tem_espaco(li, 1) == 0);
    assert(lista_tem_espaco(li, 0) == 1);
    printf("Caso 4 (lista cheia) OK\n");

    libera_lista(li);
    li = NULL;

    printf("Todos os testes de lista_tem_espaco passaram!\n\n");

    /* ===================== soma_precos ===================== */

    assert(soma_precos(NULL) == 0);

    li = cria_lista();
    assert(soma_precos(li) == 0); // lista vazia

    struct produto p1 = {1, "A", 10.0f};
    struct produto p2 = {2, "B", 20.0f};
    struct produto p3 = {3, "C", 30.0f};
    insere_lista_final(li, p1);
    insere_lista_final(li, p2);
    insere_lista_final(li, p3);

    assert(soma_precos(li) == 60.0f); // 10 + 20 + 30

    libera_lista(li);
    li = NULL;

    printf("Todos os testes de soma_precos passaram!\n\n");

    /* ===================== busca_por_nome ===================== */

    assert(busca_por_nome(NULL, "qualquer", &p) == 0);

    li = cria_lista();
    struct produto resultado;

    assert(busca_por_nome(li, "Inexistente", &resultado) == 0); // lista vazia

    struct produto n1 = {10, "Caneta", 2.5f};
    struct produto n2 = {20, "Caderno", 15.0f};
    struct produto n3 = {30, "Lapis", 1.0f};
    insere_lista_final(li, n1);
    insere_lista_final(li, n2);
    insere_lista_final(li, n3);

    assert(busca_por_nome(li, "Caneta", &resultado) == 1); // primeira posição
    assert(resultado.codigo == 10);

    assert(busca_por_nome(li, "Lapis", &resultado) == 1);  // última posição
    assert(resultado.codigo == 30);

    assert(busca_por_nome(li, "Borracha", &resultado) == 0); // não existe

    assert(busca_por_nome(li, "Caneta Azul", &resultado) == 0); // prefixo, não deve confundir

    libera_lista(li);
    li = NULL;

    printf("Todos os testes de busca_por_nome passaram!\n\n");

    /* ===================== insere_lista_decrescente ===================== */

    li = cria_lista();

    struct produto d1 = {1, "Meio", 50.0f};
    struct produto d2 = {2, "Maior", 100.0f};
    struct produto d3 = {3, "Menor", 10.0f};

    assert(insere_lista_decrescente(li, d1) == 1); // {50}
    assert(insere_lista_decrescente(li, d2) == 1); // {100, 50}
    assert(insere_lista_decrescente(li, d3) == 1); // {100, 50, 10}

    struct produto verifica;
    busca_lista_pos(li, 1, &verifica);
    assert(verifica.preco == 100.0f);
    busca_lista_pos(li, 2, &verifica);
    assert(verifica.preco == 50.0f);
    busca_lista_pos(li, 3, &verifica);
    assert(verifica.preco == 10.0f);

    libera_lista(li);
    li = NULL;

    printf("Todos os testes de insere_lista_decrescente passaram!\n\n");

    /* ===================== remove_mais_caro ===================== */

    struct produto removido;
    assert(remove_mais_caro(NULL, &removido) == 0);

    li = cria_lista();
    assert(remove_mais_caro(li, &removido) == 0); // lista vazia

    struct produto c1 = {1, "A", 30.0f};
    struct produto c2 = {2, "B", 50.0f}; // maior
    struct produto c3 = {3, "C", 50.0f}; // empate, mas B veio primeiro
    struct produto c4 = {4, "D", 20.0f};
    insere_lista_final(li, c1);
    insere_lista_final(li, c2);
    insere_lista_final(li, c3);
    insere_lista_final(li, c4);

    assert(remove_mais_caro(li, &removido) == 1);
    assert(removido.codigo == 2); // B, não C, por ser o primeiro em empate
    assert(tamanho_lista(li) == 3);

    libera_lista(li);
    li = NULL;

    printf("Todos os testes de remove_mais_caro passaram!\n\n");

    /* ===================== conta_faixa_preco ===================== */

    assert(conta_faixa_preco(NULL, 0, 100) == 0);

    li = cria_lista();
    assert(conta_faixa_preco(li, 0, 100) == 0); // lista vazia

    struct produto f1 = {1, "A", 10.0f};
    struct produto f2 = {2, "B", 20.0f};
    struct produto f3 = {3, "C", 30.0f};
    insere_lista_final(li, f1);
    insere_lista_final(li, f2);
    insere_lista_final(li, f3);

    assert(conta_faixa_preco(li, 10.0f, 30.0f) == 3); // limites inclusivos
    assert(conta_faixa_preco(li, 15.0f, 25.0f) == 1); // só o 20
    assert(conta_faixa_preco(li, 100.0f, 200.0f) == 0); // nenhum
    assert(tamanho_lista(li) == 3); // não alterou a lista

    libera_lista(li);
    li = NULL;

    printf("Todos os testes de conta_faixa_preco passaram!\n\n");

    /* ===================== remove_abaixo_de ===================== */

    assert(remove_abaixo_de(NULL, 10.0f) == 0);

    li = cria_lista();
    assert(remove_abaixo_de(li, 10.0f) == 0); // lista vazia

    struct produto r1 = {1, "A", 5.0f};  // abaixo
    struct produto r2 = {2, "B", 5.0f};  // abaixo (consecutivo, testa o i--)
    struct produto r3 = {3, "C", 50.0f}; // fica
    struct produto r4 = {4, "D", 3.0f};  // abaixo
    insere_lista_final(li, r1);
    insere_lista_final(li, r2);
    insere_lista_final(li, r3);
    insere_lista_final(li, r4);

    int removidos = remove_abaixo_de(li, 10.0f);
    assert(removidos == 3);
    assert(tamanho_lista(li) == 1);

    struct produto sobrou;
    busca_lista_pos(li, 1, &sobrou);
    assert(sobrou.codigo == 3); // só o produto C deveria sobrar

    libera_lista(li);
    li = NULL;

    printf("Todos os testes de remove_abaixo_de passaram!\n\n");

    /* ===================== mescla_listas ===================== */

    Lista *destino = cria_lista();
    Lista *origem = cria_lista();

    assert(mescla_listas(NULL, origem) == 0);
    assert(mescla_listas(destino, NULL) == 0);

    struct produto m1 = {1, "Existe em ambos", 10.0f};
    struct produto m2 = {2, "Só em destino", 20.0f};
    struct produto m3 = {1, "Codigo duplicado", 999.0f}; // mesmo codigo de m1
    struct produto m4 = {3, "Novo produto", 30.0f};

    insere_lista_final(destino, m1);
    insere_lista_final(destino, m2);

    insere_lista_final(origem, m3); // codigo 1 já existe em destino -> ignorado
    insere_lista_final(origem, m4); // codigo 3 não existe -> inserido

    int inseridos = mescla_listas(destino, origem);
    assert(inseridos == 1); // só m4 deveria entrar
    assert(tamanho_lista(destino) == 3);
    assert(tamanho_lista(origem) == 2); // origem não foi alterada

    struct produto checaDuplicado;
    busca_lista_cod(destino, 1, &checaDuplicado);
    assert(checaDuplicado.preco == 10.0f); // manteve o de destino, não o de origem

    libera_lista(destino);
    libera_lista(origem);
    destino = NULL;
    origem = NULL;

    printf("Todos os testes de mescla_listas passaram!\n\n");

    printf("=== TODOS OS TESTES PASSARAM ===\n");

    return 0;
}