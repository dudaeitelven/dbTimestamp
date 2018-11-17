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

void carregaMenu(int Escolha) {

	switch (Escolha) {
	case 1: //

		break;
	case 2: //

		break;
	case 3: //

		break;
	case 4: //

		break;
	case 5: //

		break;
	}

}

void cadastrarTransacao () {

}

void cadastrarOperacao () {

}

void menu() {

	printf("     	     --- M E N U ---             	\n");
	printf(" 1 -                  	                    \n");//
	printf(" 2 -                 	                    \n");//
	printf(" 3 -                                        \n");//
	printf(" 4 -                      	                \n");//
	printf(" 5 -                                        \n");//
	printf(" 0 -   SAIR                           	    \n");//

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
					system("cls");
				}
				carregaMenu(Escolha);
			} while ((Escolha < 0) || (Escolha > 12));
		} while (Escolha != 0);

		return 0;
}
