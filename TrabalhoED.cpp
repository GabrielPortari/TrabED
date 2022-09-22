#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct info_veiculo{
	char placa[8];
	char RENAVAM[13];
	char marca[16];
	char modelo[46];
	int ano_fabricacao;
	char cor[30];
	char categoria[30];
	char estado_registro[3];
	char cidade_registro[30];
//	struct info_veiculo *ant;
	struct info_veiculo *prox;
}veiculo;

veiculo *aloca(char placa[8], char RENAVAM[13], char marca[16], char modelo[46], int ano_fabricacao, char cor[30], char categoria[30], char estado_registro[3], char cidade_registro[30]){
	//declaração de váriaveis
	veiculo *novo;
	
	//aloca memória para nova celula
	novo = (veiculo *) malloc(sizeof (veiculo));
	if(novo == NULL){
		printf("Falha ao alocar memoria.");
		exit(1);
	}
	strcpy(novo->placa, placa);
	strcpy(novo->RENAVAM, RENAVAM);
	strcpy(novo->marca, marca);
	strcpy(novo->modelo, modelo);
	novo->ano_fabricacao = ano_fabricacao;
	strcpy(novo->cor, cor);
	strcpy(novo->categoria, categoria);
	strcpy(novo->estado_registro, estado_registro);
	strcpy(novo->cidade_registro, cidade_registro);
	
	//nova->prox = NULL para não dar em uma posição aleatoria e dar erro
	novo->prox = NULL;
	
	return novo;
}
//void insere(veiculo **inicio, char placa[], char RENAVAM[], char marca[], char modelo[], int ano_fabricacao, char cor[], char categoria[], char estado_registro[], char cidade_registro[]){
void insere(veiculo **inicio, char placa[8], char RENAVAM[13], char marca[16], char modelo[46], int ano_fabricacao, char cor[30], char categoria[30], char estado_registro[3], char cidade_registro[30]){
	//declaração de variáveis
	veiculo *p;
	//se inicio = NULO então aloca na primeira posição
	if(*inicio == NULL){
		*inicio = aloca(placa, RENAVAM, marca, modelo, ano_fabricacao, cor, categoria, estado_registro, cidade_registro);
	}else{ //caso inicio != NULO, incremento p->prox até achar a ultima posição para alocar
		p = *inicio;
		
		while(p->prox != NULL){
			p = p->prox;
		}
		//ultima posição vazia encontrada, aloca espaço e váriaveis
		p->prox = aloca(placa, RENAVAM, marca, modelo, ano_fabricacao, cor, categoria, estado_registro, cidade_registro);
//		p->ant = p;
	}
}
void libera_lista(veiculo *ini){
	//declaração de váriaveis
	veiculo *p;
	//enquanto o inicio for != de NULL, libera a memória celula por celula
	while(ini != NULL){
		p = ini;
		ini = ini->prox;
		free(p);
	}
}
int ler_operacao(){
	char operacao[20];
	int op = -2;
	
	printf("Digite a operacao desejada: ");
	scanf("%s", operacao);
	if (strcmp(operacao, "sair") == 0){
		op = -1;
	}
	if (strcmp(operacao, "converte_placa") == 0){
		op = 1;
	}
	if (strcmp(operacao, "buscar_placa") == 0){
		op = 2;
	}
	return op;
}
void converte_placa(veiculo **inicio, char placa[]){
	veiculo *p;
	p = *inicio;
	int achou = 0;
	while(p->prox != NULL){
		if(strcmp(placa, p->placa) == 0){
			achou = 1;
			switch(p->placa[4]){
				case '0':
					p->placa[4] = 'A';
				break;
				case '1':
					p->placa[4] = 'B';
				break;
				case '2':
					p->placa[4] = 'C';
				break;
				case '3':
					p->placa[4] = 'D';
				break;
				case '4':
					p->placa[4] = 'E';
				break;
				case '5':
					p->placa[4] = 'F';
				break;
				case '6':
					p->placa[4] = 'G';
				break;
				case '7':
					p->placa[4] = 'H';
				break;
				case '8':
					p->placa[4] = 'I';
				break;
				case '9':
					p->placa[4] = 'J';
				break;
			}
		}
		p = p->prox;
	}
	if(achou == 0){
		printf("Placa nao encontrada.\n");
	}
}
void buscar_placa(veiculo **inicio, char placa[]){
	veiculo *p;
	p = *inicio;
	int achou = 0;

	while(p->prox != NULL){
		if(strcmp(placa, p->placa) == 0){
			printf("\nPlaca: %s \nRENAVAM: %s \nMarca: %s \nModelo: %s \nAno Fabricacao: %i \nCor: %s \nCategoria: %s \nEstado: %s \nCidade: %s\n", p->placa, p->RENAVAM, p->marca, p->modelo, p->ano_fabricacao, p->cor, p->categoria, p->estado_registro, p->cidade_registro);
			printf("\n");
			achou = 1;
		}
		p = p->prox;
	}
	if(achou == 0){
		printf("Placa nao encontrada.\n");
	}
}
int main(int argc, char *argv[]){
	FILE *ERNV_entrada;
	double tempo_op;
	clock_t t_inicio, t_final;
	if(argc != 2){
		fprintf(stderr, "Modo de usar %s nome_do_arquivo\n", argv[0]);
		return 0;
	}

	ERNV_entrada = fopen(argv[1], "r");
	if(ERNV_entrada == NULL){
		printf("Falha ao abrir arquivo de entrada\n");
		return 0;
	}
	
	char placa[8], RENAVAM[13], marca[16], modelo[46], cor[30], categoria[30], estado_registro[3], cidade_registro[30];
	int ano_fabricacao;
	veiculo *inicio;
	inicio = NULL;
	// INICIO DA LEITURA DO ARQUIVO PRINCIPAL
	t_inicio = clock();
	while(!feof(ERNV_entrada)){
		fscanf(ERNV_entrada,"%[^;];", placa);
		fscanf(ERNV_entrada,"%[^;];", RENAVAM);
		fscanf(ERNV_entrada,"%[^;];", marca);
		fscanf(ERNV_entrada,"%[^;];", modelo);
		fscanf(ERNV_entrada,"%i;", &ano_fabricacao);
		fscanf(ERNV_entrada,"%[^;];", cor);
		fscanf(ERNV_entrada,"%[^;];", categoria);
		fscanf(ERNV_entrada,"%[^;];", estado_registro);
		fscanf(ERNV_entrada,"%[^\n]\n", cidade_registro);
		/*printf("\n");
		printf("Placa: %s \nRENAVAM: %s \nMarca: %s \nModelo: %s \nAno Fabricacao: %i \nCor: %s \nCategoria: %s \nEstado: %s \nCidade: %s", placa, RENAVAM, marca, modelo, ano_fabricacao, cor, categoria, estado_registro, cidade_registro);
		printf("\n");*/
		insere(&inicio, placa, RENAVAM, marca, modelo, ano_fabricacao, cor, categoria, estado_registro, cidade_registro);
	}
	int fclose(FILE argv[1]); // FIM INSERÇÃO DE VEICULOS
	t_final = clock();
	tempo_op = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
	printf("Veiculos inseridos apos %f segundos\n", tempo_op);

	int op;
	
	op = ler_operacao();
	
	while(op != -1){
		t_inicio = clock();
		switch (op){
			case -1:
				printf("Voce escolheu sair.\n");
			break;
			case 1:
				scanf(" %s", placa);
				converte_placa(&inicio, placa);
			break;
			case 2:
				scanf(" %s", placa);
				buscar_placa(&inicio, placa);
			break;
			case -2:
				scanf("Operacao invalida.");
			break;
		}
		t_final = clock();
		tempo_op = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
		if(op > 0){
			printf("Operacao concluida com sucesso em %f segundos\n", tempo_op);
		}
		op = 0;
		op = ler_operacao();
	}
	
	libera_lista(inicio);
}
