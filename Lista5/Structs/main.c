#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaTarefas.h"

/* Função auxiliar para exibir todos os elementos da lista de forma legível */
void imprime_lista(char *titulo, ListaTarefas *li) {
    printf("\n=== %s ===\n", titulo);
    if (li == NULL || lista_vazia(li) == 1) {
        printf("[ Lista Vazia ou Nula ]\n");
        return;
    }

    int total = tamanho_lista(li);
    struct tarefa t;
    for (int i = 1; i <= total; i++) {
        if (busca_tarefa_pos(li, i, &t)) {
            printf("[%d] Cód: %d | Desc: %-25s | Prioridade: %d\n",
                   i, t.codigo, t.descricao, t.prioridade);
        }
    }
}

int main(void) {
    /* ------------------------------------------------------------
       Criando a lista principal
       ------------------------------------------------------------ */
    ListaTarefas *li = cria_lista();
    struct tarefa t;

    printf(">>> INICIANDO OS TESTES DAS FUNÇÕES DA LISTA 5 <<<\n");

    /* Populando a lista com dados iniciais */
    struct tarefa t1 = {101, "Estudar Estrutura de Dados", 1};
    struct tarefa t2 = {102, "Fazer exercicios de C", 2};
    struct tarefa t3 = {103, "Comprar café", 3};
    struct tarefa t4 = {104, "Revisar ponteiros", 2};
    struct tarefa t5 = {105, "Estudar para a prova", 1};

    insere_tarefa_final(li, t1);
    insere_tarefa_final(li, t2);
    insere_tarefa_final(li, t3);
    insere_tarefa_final(li, t4);
    insere_tarefa_final(li, t5);

    imprime_lista("Estado Inicial da Lista", li);

    /* ------------------------------------------------------------
       Teste Q1: conta_tarefas_prioridade
       ------------------------------------------------------------ */
    int prio_busca = 2;
    int qtd_prio = conta_tarefas_prioridade(li, prio_busca);
    printf("\n[Q1] Qtd de tarefas com prioridade %d: %d (Esperado: 2)\n", prio_busca, qtd_prio);

    /* ------------------------------------------------------------
       Teste Q2: tarefa_mais_urgente
       ------------------------------------------------------------ */
    if (tarefa_mais_urgente(li, &t)) {
        printf("\n[Q2] Tarefa mais urgente: Cód %d - '%s' (Prioridade: %d)\n",
               t.codigo, t.descricao, t.prioridade);
    }

    /* ------------------------------------------------------------
       Teste Q3: busca_tarefa_desc
       ------------------------------------------------------------ */
    char termo_busca[] = "exercicios";
    if (busca_tarefa_desc(li, termo_busca, &t)) {
        printf("\n[Q3] Tarefa encontrada contendo '%s': Cód %d - '%s'\n",
               termo_busca, t.codigo, t.descricao);
    } else {
        printf("\n[Q3] Nenhuma tarefa encontrada contendo '%s'\n", termo_busca);
    }

    /* ------------------------------------------------------------
       Teste Q4: insere_tarefa_final_prioridade
       ------------------------------------------------------------ */
    struct tarefa t_nova = {106, "Nova tarefa de prioridade 2", 2};
    insere_tarefa_final_prioridade(li, t_nova);
    imprime_lista("[Q4] Apos inserir tarefa (Cód 106, Prio 2) apos ultima Prio 2", li);

    /* ------------------------------------------------------------
       Teste Q5: remove_tarefas_prioridade
       ------------------------------------------------------------ */
    int removidas = remove_tarefas_prioridade(li, 2);
    printf("\n[Q5] Removidas %d tarefas com prioridade 2\n", removidas);
    imprime_lista("[Q5] Apos remover todas com prioridade 2", li);

    /* ------------------------------------------------------------
       Teste Q6: inverte_lista
       ------------------------------------------------------------ */
    inverte_lista(li);
    imprime_lista("[Q6] Apos inverter a lista", li);

    /* ------------------------------------------------------------
       Teste Q7: remove_tarefa_pos
       ------------------------------------------------------------ */
    int pos_remocao = 2;
    remove_tarefa_pos(li, pos_remocao);
    imprime_lista("[Q7] Apos remover elemento da posicao 2", li);

    /* ------------------------------------------------------------
       Teste Q8: mescla_tarefas
       ------------------------------------------------------------ */
    ListaTarefas *src = cria_lista();
    struct tarefa t_src1 = {201, "Projeto Integrador", 1};
    struct tarefa t_src2 = {202, "Entregar relatorio", 3};
    insere_tarefa_final(src, t_src1);
    insere_tarefa_final(src, t_src2);

    imprime_lista("Lista de Origem (src) antes da mescla", src);

    int transferidas = mescla_tarefas(li, src);
    printf("\n[Q8] Tarefas transferidas de src para li: %d\n", transferidas);

    imprime_lista("[Q8] Lista Principal (li) apos mesclar", li);
    imprime_lista("[Q8] Lista de Origem (src) apos mesclar (Deve estar vazia)", src);

    /* ------------------------------------------------------------
       Liberação da memória
       ------------------------------------------------------------ */
    libera_lista(li);
    libera_lista(src);

    printf("\n>>> TODOS OS TESTES CONCLUÍDOS COM SUCESSO! <<<\n");
    return 0;
}