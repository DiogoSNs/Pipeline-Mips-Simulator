/*============================================TRABALHO DE ARQUITETURA E ORGANIZAÇAO DE COMPUTADORES==========================================================
ALUNOS:
Alberto Pontiery de Moura Sartin Valadão RA: 2552930
Diogo Augusto Silvério Nascimento RA: 2586460
Guilherme Pança Franco RA: 2534304

PARA UTILIZAR O CODIGO CRIE UM ARQUIVO DE TEXTO NA PASTA OUTPUT DO CODIGO E NOMEIE COMO "instrucoes.txt" COLOQUE O CODIGO DO MIPS E COMPILE
É NECESSARIO QUE AS INSTRUÇÕES ESTEJAM SEPARADAS POR ESPAÇOS COMO NO EXEMPLO A SEGUIR:

add $t0, $zero, $t1
lw $s2, 0($sp)
addi $t4, $s2, 10
sll $s0, $s1, 2 

==============================================================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum TipoInstrucao {
  ADD,
  SUB,
  ADDI,
  LW,
  SW,
  SLL,
  BEQ,
  BNE,
  BLT,
  BGT,
  BOLHA,
  
} TipoInstrucao;

typedef struct Instrucao {
  TipoInstrucao tipo; // Tipo da instrução (ADD, SUB, etc.)
  char *opcode; // Opcode da instrução
  char *arg1; // Argumento 1 
  char *arg2; // Argumento 2 
  char *arg3; // Argumento 3 
  int quantidadeInstrucao;
  struct Instrucao *prox;
} Instrucao;

// Função para criar uma nova instrução
Instrucao *criarInstrucao(char *opcode, char *arg1, char *arg2, char *arg3) {
  Instrucao *novaInstrucao = (Instrucao *)malloc(sizeof(Instrucao));
  novaInstrucao->opcode = strdup(opcode);
  novaInstrucao->arg1 = strdup(arg1);
  novaInstrucao->arg2 = strdup(arg2);
  novaInstrucao->arg3 = strdup(arg3);
  novaInstrucao->prox = NULL;
  novaInstrucao->quantidadeInstrucao=0;

  if (strcmp(opcode, "add") == 0) {
    novaInstrucao->tipo = ADD;
  } else if (strcmp(opcode, "sub") == 0) {
    novaInstrucao->tipo = SUB;
  } else if (strcmp(opcode, "addi") == 0) {
    novaInstrucao->tipo = ADDI;
  } else if (strcmp(opcode, "lw") == 0) {
    novaInstrucao->tipo = LW;
  } else if (strcmp(opcode, "sw") == 0) {
    novaInstrucao->tipo = SW;
  } else if (strcmp(opcode, "sll") == 0) {
    novaInstrucao->tipo = SLL;
  } else if (strcmp(opcode, "beq") == 0) {
    novaInstrucao->tipo = BEQ;
  } else if (strcmp(opcode, "bne") == 0) {
    novaInstrucao->tipo = BNE;
  } else if (strcmp(opcode, "blt") == 0) {
    novaInstrucao->tipo = BLT;
  } else if (strcmp(opcode, "bgt") == 0) {
    novaInstrucao->tipo = BGT;
  } else if (strcmp(opcode, "nop") == 0) {
    novaInstrucao->tipo = BOLHA;
  } else {
    
    printf("\nO CODIGO POSSUI UMA INTRUCAO NAO SUPORTADA !!!\nREVISE O ARQUIVO DE INSTRUCOES\n");
    
  }

  return novaInstrucao;
}

// Função para adicionar uma instrução à lista encadeada
void adicionarInstrucao(Instrucao **lista, Instrucao *novaInstrucao) {
  if (*lista == NULL) {
    *lista = novaInstrucao;
  } else {
    Instrucao *temp = *lista;
    while (temp->prox != NULL) {
      temp = temp->prox;
    }
    temp->prox = novaInstrucao;
  }

  (*lista)->quantidadeInstrucao++;
}

// Função para imprimir a lista de instruções
void imprimirInstrucoes(Instrucao *lista) {
  int numeroInstrucao = 1;
  Instrucao *temp = lista;
  while (temp != NULL) {
    switch (temp->tipo) {
      case ADD:
        printf("%d - add %s %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2, temp->arg3);
        break;
      case SUB:
        printf("%d - sub %s %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2, temp->arg3);
        break;
      case ADDI:
        printf("%d - addi %s %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2, temp->arg3);
        break;
      case LW:
        printf("%d - lw %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2);
        break;
      case SW:
        printf("%d - sw %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2);
        break;
      case SLL:
        printf("%d - sll %s %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2, temp->arg3);
        break;
      case BEQ:
        printf("%d - beq %s %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2, temp->arg3);
        break;
      case BNE:
        printf("%d - bne %s %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2, temp->arg3);
        break;
      case BLT:
        printf("%d - blt %s %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2, temp->arg3);
        break;
      case BGT:
        printf("%d - bgt %s %s %s\n", numeroInstrucao++, temp->arg1, temp->arg2, temp->arg3);
        break;
      case BOLHA:
        printf("%d - %s\n", numeroInstrucao++, temp->opcode);
        break;
      default:
        printf("%d - %s %s %s %s\n", numeroInstrucao++, temp->opcode, temp->arg1, temp->arg2, temp->arg3);
        break;
    }
    temp = temp->prox;
  }
}

// Função para liberar a memória alocada para a lista de instruções
void liberarInstrucoes(Instrucao *lista) {
  Instrucao *temp;
  while (lista != NULL) {
    temp = lista;
    lista = lista->prox;
    free(temp->opcode);
    free(temp->arg1);
    free(temp->arg2);
    free(temp->arg3);
    free(temp);
  }
}

int verificarDependencia(Instrucao *instrucaoAtual, Instrucao *instrucaoAnterior) {
    char arg3_com_virgula[100]; // Defina o tamanho conforme necessário

    // Copia o conteúdo de arg3 para arg3_com_virgula
    strcpy(arg3_com_virgula, instrucaoAtual->arg3);
    // Adiciona uma vírgula no final da string
    strcat(arg3_com_virgula, ",");

    // Verifica se o registrador de destino da instrução atual é o mesmo que o registrador de origem da instrução anterior
    if (strcmp(instrucaoAnterior->arg1, arg3_com_virgula) == 0) {
        return 1; // Dependência encontrada
    }

    // Verifica se o registrador de destino da instrução atual é o mesmo que o registrador de origem da instrução anterior
    if (strcmp(instrucaoAtual->arg1, instrucaoAnterior->arg1) == 0) {
        return 1; // Dependência encontrada
    }

    // Verifica se o registrador de destino da instrução atual é o mesmo que o registrador de origem da instrução anterior
    if (strcmp(instrucaoAtual->arg2, instrucaoAnterior->arg1) == 0) {
        return 1; // Dependência encontrada
    }

    // Nenhuma dependência encontrada
    return 0;
}

// Verifica se a instrucao anterior é lw para adicionar uma bolha a mais por conta do passo na memoria
int verificaLW(Instrucao *instrucaoAnterior){

  if(strcmp(instrucaoAnterior->opcode, "lw") == 0) {

    return 1; // Instrução encontrada
  }

    return 0; // Nenhuma instrucao encontrada
} 

// contas os ciclos do codigo
int contaciclos(Instrucao *lista) {

    int ciclos=0;
    Instrucao *atual = lista;
    int quantInstrucoes=atual->quantidadeInstrucao;

    // Percorre a lista encadeada até o último elemento
    while (atual != NULL && atual->prox != NULL) {
        atual = atual->prox;
    }

    // Verifica se encontrou um elemento válido
    if (atual != NULL) {
        // Verifica o tipo da instrução e calcula os ciclos correspondentes
        if (strcmp(atual->opcode, "lw") == 0) {
            ciclos = 4 + quantInstrucoes;
        } else {
            ciclos = 4 + (quantInstrucoes - 1);
        }
    }

    return ciclos;
}

// Função para exibir a tabela do pipeline com base nos ciclos totais
void exibirTabela(Instrucao *listaInstrucoes, int numCiclos) {

  printf("\nTabela de Simulação do Pipeline:\n");
  printf("Ciclos\t");
  for (int i = 1; i <= numCiclos; i++) {
    printf("%d\t", i);
  }
  printf("\n");

  int numeroInstrucao = 1;
  Instrucao *temp = listaInstrucoes;

   while (temp != NULL) {
    switch (temp->tipo) {
      case ADD:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
      case SUB:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
      case ADDI:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
      case LW:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\t%s\n", "IF","ID","EXE","MEM","WB");
        break;
      case SW:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","MEM");
        break;
      case SLL:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
      case BEQ:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
      case BNE:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
      case BLT:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
      case BGT:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
      case BOLHA:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
      default:
        printf("%d - ", numeroInstrucao++);
        for(int i=1;i<numeroInstrucao;i++){
          printf("\t");
        }
        printf("%s\t%s\t%s\t%s\n", "IF","ID","EXE","WB");
        break;
    }

    temp = temp->prox;
  }

}



int main() {

  int forwarding; //variavel para armazenar se o usuario deseja executar o programa com forwarding ou sem

  // Lista encadeada para armazenar as instruções
  Instrucao *listaInstrucoes = NULL;

  //Pedir ao usuário para digitar a opcao do forwarding
  do{

      printf("Deseja realizar a execucao com forwarding? (Digite 1 para sim, 0 para nao): ");
      scanf("%d", &forwarding);

        if (forwarding != 0 && forwarding != 1) {
            printf("Opcao invalida. Por favor, digite 1 para sim ou 0 para nao.\n");
        }

    }while(forwarding != 0 && forwarding != 1);

    setbuf(stdin,NULL); //limpa o buffer

// Abrir arquivo de instruções
  FILE *arquivoInstrucoes = fopen("instrucoes.txt", "r");
  if (arquivoInstrucoes == NULL) {
    printf("Erro ao abrir o arquivo de instruções.\n");
    return 1;
  }

  // Buffer para armazenar cada linha do arquivo
  char linhaInstrucao[100];

  // Variável para armazenar a instrução anterior
  Instrucao *instrucaoAnterior = NULL;

  // Ler cada linha do arquivo e processar a instrução
  while (fgets(linhaInstrucao, sizeof(linhaInstrucao), arquivoInstrucoes) != NULL) {
    // Extrair as partes da instrução
    char opcode[32], arg1[32], arg2[32], arg3[32];
    sscanf(linhaInstrucao, "%s %s %s %s", opcode, arg1, arg2, arg3);

    // Criar nova instrução
    Instrucao *novaInstrucao = criarInstrucao(opcode, arg1, arg2, arg3);

    // Verifica dependência com a instrução anterior
    if (instrucaoAnterior != NULL && verificarDependencia(novaInstrucao, instrucaoAnterior) && forwarding == 0) {
      // Adiciona bolha (NOP) para resolver dependência
      Instrucao *bolha = criarInstrucao("nop", "", "", "");
      adicionarInstrucao(&listaInstrucoes, bolha);

    
    }

    //Verifica dependencia do lw
    if(instrucaoAnterior != NULL && verificarDependencia(novaInstrucao,instrucaoAnterior) && verificaLW(instrucaoAnterior)){

      // Adiciona bolha (NOP) para resolver dependência
      Instrucao *bolha1 = criarInstrucao("nop", "", "", "");
      adicionarInstrucao(&listaInstrucoes, bolha1);

    }

    // Adicionar nova instrução à lista
    adicionarInstrucao(&listaInstrucoes, novaInstrucao);

    // Atualizar a instrução anterior
    instrucaoAnterior = novaInstrucao;
  }

  // Fechar arquivo de instruções
  fclose(arquivoInstrucoes);

  // Imprimir as instruções

  if(forwarding==0){
    printf("\n ----- SIMULACAO PIPELINE SEM FORWARDING -----\n");
  }else{
    printf("\n ----- SIMULACAO PIPELINE COM FORWARDING -----\n");
  }

  printf("\nInstrucoes MIPS:\n");

  imprimirInstrucoes(listaInstrucoes);

  int numCiclos = contaciclos(listaInstrucoes); //salve a quantidade de ciclos

  exibirTabela(listaInstrucoes,numCiclos);

  printf("\nquantidade de ciclos: %d",numCiclos);

  // Liberar a memória alocada para as instruções
  liberarInstrucoes(listaInstrucoes);

  return 0;

}


