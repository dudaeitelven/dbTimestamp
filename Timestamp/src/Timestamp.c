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
	char dado[5];
	int r_ts;
	int w_ts;
} nDado;

typedef struct stOperacao {
	int operacao; // 1 - Leitura | 2 - Escrita
	nDado *dado;
	struct stOperacao *prox;
} nOperacao;

typedef struct stTransacao{
	int identificador;
	int start;
	int commit;
	nOperacao *InicioOperacao;
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
	pnovo->InicioOperacao = NULL;
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

nOperacao* FAlocaOperacao() {
	nOperacao *Operacao = (nOperacao*) malloc(sizeof(nOperacao));
	return Operacao;
}

void cadastrarOperacao () {

	int transacaoBusca = 0;
	int achouTransacao = 0;

	nOperacao *pnovo;
	nTransacao *auxTransacao = inicioTransacao;

	pnovo = FAlocaOperacao();

	if (!pnovo) {
		printf("\n Nao foi possivel alocar \n");
		return;
	}

	if (auxTransacao == NULL) {
		printf("Nenhuma Transacao cadastrada ! \n");
		return;
	}

	printf("Informe a Transacao: \n");
	scanf("%d",&transacaoBusca);
	fflush(stdin);

	printf("Informe a operacao que deseja adcionar:\n 1 - Leitura ou 2 - Escrita\n");
	scanf("%d",&pnovo->operacao);
	fflush(stdin);

	//printf("Informe o dado que deseja adicionar:");
	//gets(dado);
	//strcpy(pnovo->dado->dado,"x");
	//pnovo->dado->r_ts = 0;
	//pnovo->dado->w_ts = 0;
	pnovo->prox = NULL;

	while (auxTransacao != NULL) {
		if (transacaoBusca == auxTransacao->identificador){
			if (auxTransacao->InicioOperacao == NULL) {
				auxTransacao->InicioOperacao = pnovo;
			} else {

				nOperacao *auxOperacao = auxTransacao->InicioOperacao;

				while(auxOperacao != NULL) {
					auxOperacao = auxOperacao->prox;
				}
				auxOperacao->prox = pnovo;
			}
		} else {
			auxTransacao = auxTransacao->prox;
		}
		printf("Operacao inserida com sucesso !\n");
		achouTransacao = 1;
		return;

	}

	if (achouTransacao == 0) {
		printf("Transacao nao localizada.\n");
		return;
	}

}

void mostrarTransacoes () {
	nTransacao *aux = inicioTransacao;

	if (aux == NULL) {
			printf("Lista Vazia !\n");
			system("pause");
			return;
		}

	while (aux != NULL){
		printf("Identificador: %d\n",aux->identificador);
		printf("Start: %d\n",aux->start);
		printf("Commit: %d\n",aux->commit);
		printf("Operacoes \n");

		nOperacao *auxOperacao = aux->InicioOperacao;

		while(auxOperacao != NULL){

			printf("   Operacao: %d \n",auxOperacao->operacao);
			printf("   Dado: %s \n",auxOperacao->dado->dado);
			printf("   RTS: %d \n",auxOperacao->dado->r_ts);
			printf("   WTS: %d \n\n",auxOperacao->dado->w_ts);

			auxOperacao = auxOperacao->prox;

		}

		printf("\n\n");

		aux = aux->prox;
	}
}

void menu() {

	printf("     	     --- M E N U ---           	\n");
	printf(" 1 - Cadastrar Transacao                \n");//Feito.
	printf(" 2 - Cadastrar Operacao                 \n");//Andamento
	printf(" 3 - Gerar Historia Inicial             \n");//Nada feito.
	printf(" 4 - Visualizar Transacoes     	        \n");//Nada feito.
	printf(" 5 - Simular Timestamp                  \n");//Nada feito.
	printf(" 0 - SAIR                               \n");

}

int identificadorTransacao = 0;

void carregaMenu(int Escolha) {


	switch (Escolha) {
		case 1: //Cadastrar Transacoes em ordem sequencial.
			cadastrarTransacao(++identificadorTransacao,1,1);
			break;
		case 2: //Cadastrar Operacoes de uma Transacao.
			cadastrarOperacao();
			break;
		case 3: //Gerar Historia Inicial

			break;
		case 4: //Visualizar Transacoes
			mostrarTransacoes();
			break;
		case 5: //Simular Timestamp

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
