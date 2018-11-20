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
	int dado;
	int r_ts;
	int w_ts;
	struct stDado *prox;
} nDado;

typedef struct stOperacao {
	int operacao; // 1 - Leitura | 2 - Escrita
	int dado;
	struct stOperacao *prox;
} nOperacao;

typedef struct stTransacao{
	int identificador;
	int start;
	int commit;
	struct stOperacao *InicioOperacao;
	struct stTransacao *prox;
} nTransacao;

typedef struct stHistoria{
	int tsTranscao;
	int operacao;
	int dado;
	int contador;
	struct stHistoria *prox;
} nHistoria;


nDado *inicioDado;
nTransacao *inicioTransacao;
nHistoria *inicioHistoria;
nHistoria *inicioHistoriaAleatoria;

nTransacao* FAlocaTransacao() {
	nTransacao *Transacao = (nTransacao*) malloc(sizeof(nTransacao));
	return Transacao;
}

int identificadorTransacao = 0; //variavel para controle do numero da transacao.

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

void cadastrarOperacao (int transacaoBusca, int dados) {
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


	printf("Informe a operacao que deseja adcionar:\n 1 - Leitura ou 2 - Escrita\n");
	scanf("%d",&pnovo->operacao);
	fflush(stdin);


	pnovo->dado = dados;
	pnovo->prox = NULL;

	while (auxTransacao != NULL) {
		if (transacaoBusca == auxTransacao->identificador){

			if (auxTransacao->InicioOperacao == NULL) {
				auxTransacao->InicioOperacao = pnovo;
				achouTransacao = 1;
				break;
			} else {

				nOperacao *auxOperacao = auxTransacao->InicioOperacao;

				while(auxOperacao->prox != NULL) {

					auxOperacao = auxOperacao->prox;
				}

				auxOperacao->prox = pnovo;
				achouTransacao = 1;
				break;
			}

		} else {
			auxTransacao = auxTransacao->prox;
		}

	}

	if (achouTransacao == 1) {
		printf("Operacao inserida com sucesso !\n");
		return;
	} else {
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
		printf("Transacao: %d\n",aux->identificador);
		printf("Start: %d\n",aux->start);
		printf("Commit: %d\n",aux->commit);
		printf("Operacoes: \n");

		nOperacao *auxOperacao = aux->InicioOperacao;

		if (auxOperacao == NULL) {
			printf("    Sem Transacoes Cadastradas.\n");
		}

		while(auxOperacao != NULL){

			switch(auxOperacao->operacao){
			case 1:
				printf("   Operacao: Leitura \n");
				break;
			case 2:
				printf("   Operacao: Escrita \n");
				break;
			}


			switch(auxOperacao->dado){
			case 1:
				printf("   Dado: X\n");
				break;
			case 2:
				printf("   Dado: Y\n");
				break;
			case 3:
				printf("   Dado: Z\n");
				break;
			case 4:
				printf("   Dado: A\n");
				break;
			case 5:
				printf("   Dado: B\n");
				break;
			}

			auxOperacao = auxOperacao->prox;

		}

		printf("\n");

		aux = aux->prox;
	}
}

nDado* FAlocaDado() {
	nDado *Dado = (nDado*) malloc(sizeof(nDado));
	return Dado;
}

// Insere na memoria 5 tipos de dados X,Y,Z,A,B.

void insereDados(int cont) {
		nDado *auxDado = inicioDado;
		nDado *pnovo;

		pnovo = FAlocaDado();
		if (!pnovo) {
			printf("\n Nao foi possivel alocar \n");
			return;
		}

		pnovo->dado = cont;
		pnovo->r_ts = 0;
		pnovo->w_ts = 0;
		pnovo->prox = NULL;

		if (inicioDado == NULL) {
			inicioDado = pnovo;
		} else {
			while (auxDado->prox != NULL) {
				auxDado = auxDado->prox;
			}
			auxDado->prox = pnovo;
		}
}


nHistoria* FAlocaHistoria() {
	nHistoria *Historia = (nHistoria*) malloc(sizeof(nHistoria));
	return Historia;
}

void mostraHistoriaInicial(){

	nHistoria *auxHistoria = inicioHistoria;

	while (auxHistoria != NULL){
        printf("Ordem da Lista %d\n", auxHistoria->contador);
		printf("Transacao: %d \n", auxHistoria->tsTranscao);
		printf("Operacao: %d \n", auxHistoria->operacao);
		printf("Dado: %d\n\n", auxHistoria->dado);

		auxHistoria = auxHistoria->prox;
	}
}

void gerarHistoriaInicial() {
    int cont = 1;
	nTransacao *auxTransacao = inicioTransacao;
	nHistoria *auxHistoria = inicioHistoria;

	while (auxTransacao != NULL){
		nOperacao *auxOperacao = auxTransacao->InicioOperacao;

		while(auxOperacao != NULL){

			nHistoria *pnovo;
            pnovo = FAlocaHistoria();
			if (!pnovo) {
				printf("\n Nao foi possivel alocar \n");
				return;
			}

			pnovo->tsTranscao = auxTransacao->identificador;
			pnovo->operacao = auxOperacao->operacao;
			pnovo->dado = auxOperacao->dado;
			pnovo->contador = cont++;
			pnovo->prox = NULL;

			if (inicioHistoria == NULL) {
					inicioHistoria = pnovo;
					auxHistoria = inicioHistoria;
			} else {
				while (auxHistoria->prox != NULL){
					auxHistoria = auxHistoria->prox;
				}
				auxHistoria->prox = pnovo;
			}

			auxOperacao = auxOperacao->prox;
		}

		auxTransacao = auxTransacao->prox;
	}
	mostraHistoriaInicial();

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

void carregaMenu(int Escolha) {
	int escolheDado;
	int transacaoBusca = 0;

	switch (Escolha) {
		case 1: //Cadastrar Transacoes em ordem sequencial.
			cadastrarTransacao(++identificadorTransacao,1,1);
			break;
		case 2: //Cadastrar Operacoes de uma Transacao.

			printf("Informe a Transacao: \n");
			scanf("%d",&transacaoBusca);
			fflush(stdin);

			printf("Informe o dado que deseja adicionar:\n");
			printf("1 - X\n");
			printf("2 - Y\n");
			printf("3 - Z\n");
			printf("4 - A\n");
			printf("5 - B\n");
			scanf("%d",&escolheDado);
			fflush(stdin);

			cadastrarOperacao(transacaoBusca,escolheDado);
			break;
		case 3: //Gerar Historia Inicial
			gerarHistoriaInicial();
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
	int cont = 1;

	while (cont <=5){
		insereDados(cont++);
	}

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
