#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// https://wagnergaspar.com/tabela-hash/
// Trabalho baseado no algoritmo encontrado acima

#define tam_antigo 157
#define tam_novo 53

typedef struct Veiculo{
	int convertida;
	char placa[8];
	char placa_convertida[8];
	char RENAVAM[13];
	char marca[16];
	char modelo[46];
	int ano_fabricacao;
	char cor[30];
	char categoria[30];
	char estado_registro[3];
	char cidade_registro[30];
}Veiculo;

typedef struct No{
	Veiculo veiculo;
	No *prox;
}No;

//Tabela Hash
No *tabelaHash_novo[tam_novo], *tabelaHash_antigo[tam_antigo];

No* criarLista(){
	No *p;
	
	p = (No *) malloc(sizeof (No));
	p = NULL;
	return p;
}

void iniciarTabela(){
	int i;
	for(i=0; i<tam_novo; i++){
		tabelaHash_novo[i] = criarLista();
	}
	for(i=0; i<tam_antigo; i++){
		tabelaHash_antigo[i] = criarLista();
	}
}

int gerarChave(char placa[], int modelo){
	int chave, tamanho;
	
	if(modelo == 1){
		chave = (placa[0]*placa[1]*placa[2])%tam_antigo;
	}else{
		chave = (placa[0]*placa[1]*placa[2])%tam_novo;
	}
	
	return chave;
}

Veiculo criarVeiculo(char placa[], char RENAVAM[], char marca[], char modelo[], int ano_fabricacao, char cor[], char categoria[], char estado_registro[], char cidade_registro[]){
	Veiculo v;
	
	v.convertida = 0;
	strcpy(v.placa, placa);
	strcpy(v.RENAVAM, RENAVAM);
	strcpy(v.marca, marca);
	strcpy(v.modelo, modelo);
	v.ano_fabricacao = ano_fabricacao;
	strcpy(v.cor, cor);
	strcpy(v.categoria, categoria);
	strcpy(v.estado_registro, estado_registro);
	strcpy(v.cidade_registro, cidade_registro);
	
	return v;
}

void mostra_veiculo(Veiculo v){
	if(v.convertida == 1){
		printf("\nPlaca: %s \nRENAVAM: %s \nMarca: %s \nModelo: %s \nAno Fabricacao: %i \nCor: %s \nCategoria: %s \nEstado: %s \nCidade: %s\n", v.placa_convertida, v.RENAVAM, v.marca, v.modelo, v.ano_fabricacao, v.cor, v.categoria, v.estado_registro, v.cidade_registro);
		printf("Essa placa foi convertida.");
	}else{
		printf("\nPlaca: %s \nRENAVAM: %s \nMarca: %s \nModelo: %s \nAno Fabricacao: %i \nCor: %s \nCategoria: %s \nEstado: %s \nCidade: %s\n", v.placa, v.RENAVAM, v.marca, v.modelo, v.ano_fabricacao, v.cor, v.categoria, v.estado_registro, v.cidade_registro);

	}
}

void insere(No **inicio, Veiculo v){
	//declaração de variáveis
	No *p, *novo;
	
	novo = (No *) malloc(sizeof (No));	
	if(novo == NULL){
		printf("Falha ao alocar memoria.");
		exit(1);
	}
	
	novo->veiculo = v;
	novo->prox = NULL;
	
	//se inicio = NULO então aloca na primeira posição
	if(*inicio == NULL){
		*inicio = novo;
		novo->prox = NULL;
	}else{
		p = *inicio;
		while(p->prox != NULL){
			p = p->prox;
		}
		p->prox = novo;
	}
}

void libera_lista(No *ini){
	//declaração de váriaveis
	No *p;
	//enquanto o inicio for != de NULL, libera a memória celula por celula
	while(ini != NULL){
		p = ini;
		ini = ini->prox;
		free(p);
	}
}

int ler_operacao(){
	char operacao[20];
	int op = 0;
	
	printf("Digite ajuda para ver as opcoes.\nQual operacao deseja executar?\n");
	scanf("%s", operacao);
	if (strcmp(operacao, "sair") == 0){
		op = -1;
	}
	if (strcmp(operacao, "ajuda") == 0){
		op = 0;
	}
	if (strcmp(operacao, "converter_placa") == 0){
		op = 1;
	}
	if (strcmp(operacao, "buscar_placa") == 0){
		op = 2;
	}
	if (strcmp(operacao, "listar_placas") == 0){
		op = 3;
	}
	if (strcmp(operacao, "relatorio_data") == 0){
		op = 4;
	}
	if (strcmp(operacao, "relatorio_estado") == 0){
		op = 5;
	}
	return op;
}

int buscar_placa(No **ini, char placa[]){
	No *p;
	p = *ini;
	
	printf("\nPlaca buscada: %s\n", placa);
	
	if(p != NULL){
		while(p->prox != NULL ){
			if(strcmp(placa, p->veiculo.placa) == 0){
				mostra_veiculo(p->veiculo);
				return 1;
			}
			p = p->prox;
		}
	}
	return 0;
}

void listar_placas(No **ini){
	No *p;
	
	p = *ini;
	if(p != NULL){
		while(p->prox != NULL ){
			if(p->veiculo.convertida == 1){
				printf("Placa: %s\n", p->veiculo.placa_convertida);
			}else{
				printf("Placa: %s\n", p->veiculo.placa);
			}
			p = p->prox;
		}
	}
}

void relatorio_data(No **ini, int ano){
	No *p;
	
	p = *ini;
	int i;
	
	if(p != NULL){
		while(p->prox != NULL ){
			if(p->veiculo.ano_fabricacao == ano){
				mostra_veiculo(p->veiculo);
			}
			p = p->prox;
		}
	}
}

void relatorio_estado(No **ini, char estado[], char digito){
	No *p;
	p = *ini;
	int i;
	
	if(p != NULL){
		while(p->prox != NULL ){
			if(strcmp(p->veiculo.estado_registro, estado) == 0 && p->veiculo.placa[6] == digito){
				mostra_veiculo(p->veiculo);
			}
			p = p->prox;
		}
	}
}

void converte_placa(No **inicio, char placa[]){
	No *p;
	p = *inicio;
	int achou = 0;
	
	while(p->prox != NULL){
		if(strcmp(placa, p->veiculo.placa) == 0 && p->veiculo.convertida != 1){
			achou = 1;
			switch(p->veiculo.placa[4]){
				case '0':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'A';
				break;
				case '1':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'B';
				break;
				case '2':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'C';
				break;
				case '3':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'D';
				break;
				case '4':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'E';
				break;
				case '5':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'F';
				break;
				case '6':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'G';
				break;
				case '7':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'H';
				break;
				case '8':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'I';
				break;
				case '9':
					p->veiculo.convertida = 1;
					strcpy(p->veiculo.placa_convertida, p->veiculo.placa);
					p->veiculo.placa_convertida[4] = 'J';
				break;
			}
			printf("Placa atualizada de %s para %s\n", placa, p->veiculo.placa_convertida);
		}
		p = p->prox;
	}
	if(achou == 0){
		printf("Placa nao encontrada, ou ja convertida.\n");
	}
}

int checa_modelo_placa(char placa[]){
	int antigo = 0;
	if(placa[4] > 47 || placa[4] < 58){
		antigo = 1;
	}else{
		antigo = 0;
	}
	return antigo;
}

int main(int argc, char *argv[]){
	FILE *entrada;
	double tempo_op;
	int i, j, total=0, ano_fabricacao, ano_inicial, ano_final, indice;
	char str[11] = {"0123456789"}, digito, estado[3], placa[8], RENAVAM[13], marca[16], modelo[46], cor[30], categoria[30], estado_registro[3], cidade_registro[30];
	clock_t t_inicio, t_final;
	Veiculo v;
	No *pNovo_ini, *pAntigo_ini;
	
	iniciarTabela();
	pNovo_ini = NULL;
	pAntigo_ini = NULL;
	
	// CASO ARQUIVO ERNV SEJA ABERTO, INICIA A LEITURA DOS DADOS;
	if(argc == 2 && strcmp(argv[1], "veiculos.ernv") == 0){
		printf("Arquivo ERNV detectado, iniciando leitura.\n");
		entrada = fopen(argv[1], "r");
		if(entrada == NULL){
			printf("Falha ao abrir arquivo de entrada\n");
			return 0;
		}
		// INICIO DA LEITURA DO ARQUIVO ERNV	-------------------------------------
		t_inicio = clock();
	
		while(!feof(entrada)){
			fscanf(entrada, "%[^;];%[^;];%[^;];%[^;];%i;%[^;];%[^;];%[^;];%[^\n]\n", placa, RENAVAM, marca, modelo, &ano_fabricacao, cor, categoria, estado_registro, cidade_registro);
			v = criarVeiculo(placa, RENAVAM, marca, modelo, ano_fabricacao, cor, categoria, estado_registro, cidade_registro);
			
			if(checa_modelo_placa(placa) == 1){
				indice = gerarChave(placa, 1);
				insere(&tabelaHash_antigo[indice], v);	
			}else{
				indice = gerarChave(placa, 0);
				insere(&tabelaHash_novo[indice], v);	
			}
			
		}
		int fclose(FILE argv[1]); 
	
		t_final = clock();
		tempo_op = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
		printf("Veiculos inseridos com sucesso em %f segundos\n\n", tempo_op);	
		// FIM INSERÇÃO DE VEICULOS				-------------------------------------
	}else{
		printf("Nenhum arquivo de leitura.\n");
		return 0;
	}
	
	total = 0;
	int op = ler_operacao();
	while(op != -1){
		t_inicio = clock();
		switch (op){
			case -1:
				printf("Voce escolheu sair.\n");
			break;
			case 0:
				printf("Para converter uma placa, utilize converter_placa AAA1234\nPara buscar uma placa, utilize buscar_placa AAA1234\nPara listar somente as placas, utilize listar_placas\nPara listar um relatorio por ano, utilize relatorio_data anoInicial anoFinal\nPara listar um relatorio por estado, utilize relatorio_estado SIGLA\nPara sair, digite sair.\n");
			break;
			case 1: // Converter Placa
				scanf(" %s", placa);
				if(checa_modelo_placa(placa) == 1){
					indice = gerarChave(placa, 1);
					converte_placa(&tabelaHash_novo[indice], placa);
				}else{
					printf("Placa de modelo novo nao pode ser convertida.\n");
				}
				
			break;
			case 2: // Buscar placa
				scanf(" %s", placa);
				
				if(checa_modelo_placa(placa) == 1){
					indice = gerarChave(placa, 1);
					if(buscar_placa(&tabelaHash_antigo[indice], placa) == 0){
						printf("Placa nao encontrada.\n");
					}
				}else{
					indice = gerarChave(placa, 0);
					if(buscar_placa(&tabelaHash_novo[indice], placa) == 0){
						printf("Placa nao encontrada.\n");
					}
				}
			break;
			case 3: // Listar placas
				for(i=0; i<tam_antigo; i++){
					listar_placas(&tabelaHash_antigo[i]);	
				}
				for(i=0; i<tam_novo; i++){
					listar_placas(&tabelaHash_novo[i]);	
				}
			break;
			case 4: // Relatorio por datas
				scanf("%i %i", &ano_inicial, &ano_final);
				if(ano_final <= ano_inicial){
					printf("Os anos devem ser em ordem crescentes.\n");
				}else{
					for(i=ano_inicial; i<ano_final+1; i++){
						for(j=0; j<tam_antigo; j++){
							relatorio_data(&tabelaHash_antigo[j], i);
						}
						for(j=0; j<tam_novo; j++){
							relatorio_data(&tabelaHash_novo[j], i);
						}
					}
				}
			break;
			case 5: // Relatorio por estado
				scanf(" %s", estado);
				for(j=0; j<10; j++){
					digito = str[j];
					
					for(i=0; i<tam_antigo; i++){
						relatorio_estado(&tabelaHash_antigo[i], estado, digito);
					}
					for(i=0; i<tam_novo; i++){
						relatorio_estado(&tabelaHash_novo[i], estado, digito);
					}
				}

			break;
			default:
				printf("Operacao invalida.\n");
			break;
		}
		
		t_final = clock();
		tempo_op = (double)(t_final - t_inicio) / CLOCKS_PER_SEC;
		if(op > 0){
			printf("\nOperacao concluida com sucesso em %f segundos\n", tempo_op);
		}
		op = -2;
		op = ler_operacao();
	}
	for(i=0; i<tam_novo; i++){
		libera_lista(tabelaHash_novo[i]);
	}
	for(i=0; i<tam_antigo; i++){
		libera_lista(tabelaHash_antigo[i]);
	}
}
