#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// https://wagnergaspar.com/testando-nossa-arvore-binaria-de-busca-balanceada-arvore-avl/
// Trabalho baseado no algoritmo encontrado acima

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

typedef struct No {
    Veiculo veiculo;
    struct No *esquerda, *direita;
    short altura;
} No;

typedef struct {
    No *raiz;
    int tam;
} BinTree;


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

No* novoNo(Veiculo v){
    No *novo = (No*)malloc(sizeof(No));

    if(novo){
        novo->veiculo = v;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    }else{
        printf("\nERRO ao alocar nó em novoNo!\n");
    }
    return novo;
}
/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
short maior(short a, short b){
    return (a > b)? a: b;
}


//  Retorna a altura de um nó ou -1 caso ele seja null
short alturaDoNo(No *no){
    if(no == NULL){
    	return -1;
	}else{
		return no->altura;
	}
}

//   Calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(No *no){
    if(no)
        return (alturaDoNo(no->esquerda) - alturaDoNo(no->direita));
    else
        return 0;
}

// --------- ROTAÇÕES ---------------------------

// função para a rotação à esquerda
No* rotacaoEsquerda(No *r){
    No *y, *f;

    y = r->direita;
    f = y->esquerda;

    y->esquerda = r;
    r->direita = f;

    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

// função para a rotação à direita
No* rotacaoDireita(No *r){
    No *y, *f;

    y = r->esquerda;
    f = y->direita;

    y->direita = r;
    r->esquerda = f;

    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

No* rotacaoEsquerdaDireita(No *r){
    r->esquerda = rotacaoEsquerda(r->esquerda);
    return rotacaoDireita(r);
}

No* rotacaoDireitaEsquerda(No *r){
    r->direita = rotacaoDireita(r->direita);
    return rotacaoEsquerda(r);
}

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
No* balancear(No *raiz){
    short fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direita) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->direita) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

No* inserir(No *raiz, Veiculo v) {
	if(raiz == NULL){ // árvore vazia
        return novoNo(v);
    }else{ // inserção será à esquerda ou à direita
        if(strcmp(v.placa, raiz->veiculo.placa) < 0){
        	raiz->esquerda = inserir(raiz->esquerda, v);
		}else if(strcmp(v.placa, raiz->veiculo.placa) > 0){
			raiz->direita = inserir(raiz->direita, v);
		}else{
		}
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

void mostra_veiculo(Veiculo v){
	if(v.convertida == 1){
		printf("\nPlaca: %s \nRENAVAM: %s \nMarca: %s \nModelo: %s \nAno Fabricacao: %i \nCor: %s \nCategoria: %s \nEstado: %s \nCidade: %s\n", v.placa_convertida, v.RENAVAM, v.marca, v.modelo, v.ano_fabricacao, v.cor, v.categoria, v.estado_registro, v.cidade_registro);
		printf("Essa placa foi convertida.");
	}else{
		printf("\nPlaca: %s \nRENAVAM: %s \nMarca: %s \nModelo: %s \nAno Fabricacao: %i \nCor: %s \nCategoria: %s \nEstado: %s \nCidade: %s\n", v.placa, v.RENAVAM, v.marca, v.modelo, v.ano_fabricacao, v.cor, v.categoria, v.estado_registro, v.cidade_registro);

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

int buscar_placa(No *raiz, char placa[]) {
    if(raiz == NULL) {
    	return 0;
    } else {
        if((strcmp(placa, raiz->veiculo.placa) == 0) || strcmp(placa, raiz->veiculo.placa_convertida) == 0){
            mostra_veiculo(raiz->veiculo);
			return 1;
        }
        else {
            if(strcmp(placa, raiz->veiculo.placa) < 0){
                return buscar_placa(raiz->esquerda, placa);
            }
            else{
                return buscar_placa(raiz->direita, placa);
            }
        }
    }
}

int converte_placa(No *raiz, char placa[]) {
    if(raiz == NULL) {
    	return 0;
    } else {
        if(strcmp(placa, raiz->veiculo.placa) == 0){
            if(raiz->veiculo.convertida != 1){
				switch(raiz->veiculo.placa[4]){
					case '0':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'A';
					break;
					case '1':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'B';
					break;
					case '2':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'C';
					break;
					case '3':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'D';
					break;
					case '4':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'E';
					break;
					case '5':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'F';
					break;
					case '6':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'G';
					break;
					case '7':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'H';
					break;
					case '8':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'I';
					break;
					case '9':
						raiz->veiculo.convertida = 1;
						strcpy(raiz->veiculo.placa_convertida, raiz->veiculo.placa);
						raiz->veiculo.placa_convertida[4] = 'J';
					break;
				}
					printf("Placa atualizada de %s para %s\n", placa, raiz->veiculo.placa_convertida);
					return 1;
			}else{
				printf("Essa placa já foi convertida.\n");
			}
        }
        else {
            if(strcmp(placa, raiz->veiculo.placa) < 0){
                return converte_placa(raiz->esquerda, placa);
            }
            else{
                return converte_placa(raiz->direita, placa);
            }
        }
    }
}

void listar_placas(No *raiz) {
    if(raiz != NULL) {
        listar_placas(raiz->esquerda);
    	printf("Placa: %s \n", raiz->veiculo.placa);
        listar_placas(raiz->direita);
    }
}

void relatorio_data(No *raiz, int ano) {
    if(raiz != NULL) {
        relatorio_data(raiz->esquerda, ano);
        if(raiz->veiculo.ano_fabricacao == ano){
        	mostra_veiculo(raiz->veiculo);
		}
        relatorio_data(raiz->direita, ano);
    }
}

void relatorio_estado(No *raiz, char estado[], char digito){
    if(raiz != NULL) {
        relatorio_estado(raiz->esquerda, estado, digito);
        if(strcmp(estado, raiz->veiculo.estado_registro) == 0 && raiz->veiculo.placa[6] == digito){
			mostra_veiculo(raiz->veiculo);
		}
        relatorio_estado(raiz->direita, estado, digito);
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
	int i, ano_fabricacao, ano_inicial, ano_final, achou;
	char digito, str[10], estado[3], placa[8], RENAVAM[13], marca[16], modelo[46], cor[30], categoria[30], estado_registro[3], cidade_registro[30];
	clock_t t_inicio, t_final;
	Veiculo v;
	No *raiz_novo, *raiz_antigo;
	
	raiz_novo = NULL;
	raiz_antigo = NULL;
	
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
				raiz_antigo = inserir(raiz_antigo, v);
			}else{
				raiz_novo = inserir(raiz_novo, v);	
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
				if(checa_modelo_placa(placa) != 1){
					printf("Uma placa de modelo novo nao pode ser convertida.\n");
				}else{
					achou = 0;
					achou = converte_placa(raiz_antigo, placa);
					if(achou == 0){
						printf("Placa nao encontrada.\n");
					}
				}
			break;
			case 2: // Buscar placa
				scanf(" %s", placa);
				achou = 0;
				if(checa_modelo_placa(placa) == 1){
					achou = buscar_placa(raiz_antigo, placa);
				}else{
					achou = buscar_placa(raiz_novo, placa);
				}
				if(achou == 0){
					printf("Placa nao encontrada.\n");
				}
			break;
			case 3: // Listar placas
				listar_placas(raiz_antigo);
				listar_placas(raiz_novo);	
			break;
			case 4: // Relatorio por datas
				scanf("%i %i", &ano_inicial, &ano_final);
				if(ano_inicial > ano_final){
					printf("Os anos digitados devem estar em ordem crescente.\n");
				}else{
					for(i=ano_inicial; i<ano_final+1; i++){
						relatorio_data(raiz_antigo, i);
						relatorio_data(raiz_novo, i);
					}
				}
			break;
			case 5: // Relatorio por estado
				scanf(" %s", estado);
				strcpy(str,"0123456789");
				for(i=0; i<10; i++){
					digito = str[i];
					relatorio_estado(raiz_antigo, estado, digito);
					relatorio_estado(raiz_novo, estado, digito);
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
}
