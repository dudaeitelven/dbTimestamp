/*
 ============================================================================
 Name        : timestamp.c
 Author      : Eduardo Eitelven
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Timestamp
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct stDado {
	char dado[1];
	int r_ts;
	int w_ts;
} nDado;

typedef struct stOperacao {
	int operacao; // 1 - Leitura | 2 - Escrita
	nDado *dado;
} nOperacao;

typedef struct stTransacao{
	int identificador;
	int start;
	int commit;
	nOperacao *lista_operacao;
	struct stTransacao *prox;
} nTransacao;

nTransacao *inicioTransacao;

// historia inicial(HI) e historia final(HF) ?

nTransacao* FAlocaTransacao() {
	nTransacao *Transacao = (nTransacao*) malloc(sizeof(nTransacao));
	return Transacao;
}

void cadastrarTransacao(int identificadorTransacao,int startTransacao,int commitTransacao) {
	nTransacao *pnovo;
	nTransacao *aux = inicioTransacao;

	pnovo = FAlocaTransacao();
	if (!pnovo) {
		printf("\n Nao foi possivel alocar \n");
		return;
	}

	pnovo->identificador = identificadorTransacao;
	pnovo->start = startTransacao;
	pnovo->commit = commitTransacao;
	pnovo->lista_operacao = NULL;
	pnovo->prox = NULL;

	if (inicioTransacao == NULL) {
		inicioTransacao = pnovo;
	} else {
		while (aux->prox != NULL) {
			aux = aux->prox;
		}
		aux->prox = pnovo;
	}

	printf("Transacao Inserida com Sucesso !\n");
}


void cadastrarOperacao () {
	int transacaoBusca = 0;
	int achouTransacao = 0;

	printf("Informe a Transacao: \n");
	scanf("%d",&transacaoBusca);

	nTransacao *auxTransacao = inicioTransacao;

	while (auxTransacao->prox != NULL) {
		if (transacaoBusca == auxTransacao->identificador){
			achouTransacao = 1;
		} else {
			auxTransacao = auxTransacao->prox;
		}
	}

	if (achouTransacao == 0) {
		printf("Transacao nao localizada.\n");
		return;
	}


}

void menu() {

	printf("     	     --- M E N U ---             	\n");
	printf(" 1 - Cadastrar Transacao        	        \n");//Feito.
	printf(" 2 - Cadastrar Operacao              	    \n");//
	printf(" 3 -                                        \n");//
	printf(" 4 -                      	                \n");//
	printf(" 5 -                                        \n");//
	printf(" 0 -   SAIR                           	    \n");//

}

int identificadorTransacao = 0; // variavel global para controlar o numero de transacoes sequencial

void carregaMenu(int Escolha) {

	switch (Escolha) {
		case 1: //Cadastrar Transações em ordem sequencial.
			cadastrarTransacao(identificadorTransacao++,1,1);
			printf("%d", identificadorTransacao);
			break;
		case 2: //Cadastrar Operações de uma Transação.
			cadastrarOperacao();

			break;
		case 3: //

			break;
		case 4: //

			break;
		case 5: //

			break;
	}

}

int main(void) {
	setbuf(stdout, NULL);
	int Escolha = 0;

	do {
		do {
			menu();

			scanf("%d", &Escolha);
			fflush(stdin);

			if ((Escolha < 0) || (Escolha > 5)) {
				printf("Opcao incorreta, tente novamente ! \n");
				system("pause");
			}
			carregaMenu(Escolha);
		} while ((Escolha < 0) || (Escolha > 12));
	} while (Escolha != 0);

	return 0;
}
