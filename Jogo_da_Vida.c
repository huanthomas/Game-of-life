//Autores
//Bruno Rafael
//Huan Thomas
//Pedro Morais

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ORG 'X' //constante que armazena o valor da celula viva
#define VAZ ' ' //constante que armazena o valor da celula morta
#define TAM 101 //constante que armazena o tamanho maximo da string que armazena o nome da matriz
#define LINESIZE 1024 //constante que armazena o tamanho maximo da string que sera o nome da minha matriz

typedef struct{
    char nomeJogo[TAM];//Nome que sera dado para a matriz
    int dim1,dim2;//Dimenções da matriz
    char **m; //Variavel para a matriz
	int caso;     //Para que a funcao que inicializa possa funcionar
    int ciclosVida; // Define quanto cada jogo vai rodar (ciclos)
    int opc; //Variavel que ativa a invasão
}Tab;

void limpaMatriz(char **m, int nL, int nC);
void inicBlinker(char **m, int nL, int nC);
void inicBloco(char **m, int nL, int nC);
void inicCalango(char **m, int nL, int nC);
void inicSapo(char **m, int nL, int nC);
void inicGlider(char **m, int nL, int nC);
void inicLWSS(char **m, int nL, int nC);
void jogaJogoVida(char **m, int nL, int nC, int ciclos, int opc);
void menuInicJogo(char **mat, int nL, int nC, int caso);

char** alocaMatriz(int nL, int nC);
void imprimeMatriz (char **mat, int nL, int nC);
void desalocaMatriz(char** matriz, int nL);
void copiaMatriz(char** matriz, char **aux, int nL, int nC);
void verificaVizinho(char**mat, char **aux, int nL, int nC);
void mat2(char** matriz, char** aux, int nL, int nC);
void invasora(char **m, int nL, int nC);
void inicEstrela(char **m, int nL, int nC);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

int main(){

	char **mat;
	int jogaNov = 1;
	Tab str;
	while(jogaNov == 1){
	printf("Digite o nome do seu tabuleiro: ");//Entra com o nome do meu tabuleiro
	scanf("%s[^\n]",str.nomeJogo);

	printf("Digite o tamanho da sua matriz (LINHAS, espaco, COLUNAS): ");//Entra com o tamanho da matriz, que deve ser quadrada
	scanf("%d %d",&str.dim1,&str.dim2);

	printf("Digite a quantidade de ciclos que deseja que seu jogo rode: ");//Entra com a quantidade de ciclos
	scanf("%d",&str.ciclosVida);

	printf("Digite o caso que voce deseja que inicie na sua matriz:\n");//Entra com o caso
	printf("Vida eterna \n 1.Bloco\n 2.Calanguinho\n\n");
	printf("Osciladores \n 3.Sapo\n 4.Blinker\n\n");
	printf("Naves Espaciais \n 5.Glider\n 6.LWSS\n 7.Estrelinha\n");
	scanf("%d",&str.caso);

	printf("Digite se deseja que em sua matriz tenha uma invasao, (1 para sim, 0 para nao):");
	scanf("%d",&str.opc);

	//Inicio das Funções do jogo da vida------------------------------------------------------------

	mat= alocaMatriz(str.dim1,str.dim2);//alocando matriz

	menuInicJogo(mat,str.dim1,str.dim2,str.caso);//entra no menu do jogo

	jogaJogoVida(mat,str.dim1,str.dim2,str.ciclosVida,str.opc); //Principal Função do jogo, aloca, copia e modifica, imprime, limpa a tela

	desalocaMatriz(mat,str.dim1);//desaloca a matriz
	system("cls");

	printf("Digite se deseja jogar novamente, (1 para sim, 0 para nao):");
	scanf("%d",&jogaNov); //controla o loop indeterminado de quantas vezes sera jogado o jogo
	printf("\n");
	}

	return 0;
}
void menuInicJogo(char **mat, int nL, int nC, int caso){ //menu do jogo da vida

   switch(caso){
	    case 1:   inicBloco(mat,nL,nC); break;
	    case 2:   inicCalango(mat,nL,nC); break;
	    case 3:   inicSapo(mat,nL,nC); break;
	    case 4:   inicBlinker(mat,nL,nC); break;
		case 5:   inicGlider(mat,nL,nC); break;
		case 6:   inicLWSS(mat,nL,nC); break;
		case 7:   inicEstrela(mat,nL,nC); break;
    }

    imprimeMatriz(mat,nL,nC);

    printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo..."); while(getchar()!='\n'); getchar();
}
void jogaJogoVida(char **m, int nL, int nC, int ciclos, int opc){ //principal função do jogo da vida
	char **aux;
	int viz,k;
	int i,j;

	aux = alocaMatriz(nL,nC); //matriz que devera ser usada para atualizar cada jogada

	if(opc==1) //Uma escolha se o usuario ira qurer que uma população invasora rode junto ao caso de escolha
		invasora(m,nL,nC);//chama a população invasora e atualiza a matriz com uma invasão

	for(i=0;i<ciclos;i++){ ////laco de repeticao para jogar TOTAL DE CICLOS
		copiaMatriz(m,aux,nL,nC); //Função que copia a matriz original passando p/ matriz auxiliar e analisa e aplica as regras do jogo
    	system("cls"); //Limpa a tela
    	imprimeMatriz(aux,nL,nC);//imprime a matriz auxiliar
    	Sleep(100);//Um delay de 100 milisegundos
    	mat2(m,aux,nL,nC);//Função que atribui a matriz original os valores da matriz auxiliar para recomeçar o loop
    }

  desalocaMatriz(aux,nL);//Após o fim do loop desalocamos a matriz auxiliar
}

char** alocaMatriz(int nL, int nC){//Função que aloca uma matriz
	char **matriz;
    int i;

    matriz = (char**) malloc (sizeof(char*) * nL);
    for(i=0;i<nL;i++)
		matriz[i] = (char*) malloc (sizeof(char) * nC);

    return matriz;
}

void imprimeMatriz (char **mat, int nL, int nC){//Função que faz a impressão de uma matriz
	int i, j;
    for(i=0;i<nL;i++){
        for(j=0;j<nC;j++)
            printf("%c",mat[i][j]);

        printf("\n");
    }
}

void desalocaMatriz(char** matriz, int nL){//Função que desaloca uma matriz
	int i;
    for(i=0;i<nL;i++)
		free(matriz[i]);

    free(matriz);
}

void mat2(char** matriz, char** aux, int nL, int nC){//Função que copia a matriz auxiliar para a matriz original
	int i, j;
	for(i=0;i<nL;i++)
		for(j=0;j<nC;j++)
			matriz[i][j] = aux[i][j];
}

void copiaMatriz(char **matriz, char **aux, int nL, int nC){//Função que copia a matriz original para a auxiliar
	int i, j;

	for(i=0;i<nL;i++)
		for(j=0;j<nC;j++)
			aux[i][j]= matriz[i][j];

	verificaVizinho(matriz,aux,nL,nC);//Função que verifica vizinhos do elemento, e aplica as regras
}

void verificaVizinho(char **mat, char **aux, int nL, int nC){//Função que verifica os vizinhos
	//Função que verifica os vizinhos do elemento central de uma matriz 3x3
	/* simbolizando os vizinhos da matriz
	   |1  2  3|
	   |4  x  6|
	   |7  8  9|

	   Onde está o "X" representa o elemento que está sendo analizado os seus vizinhos
	*/
	int vivas=0, mortas = 0,vivo = 0, i, j;
	for(i=0;i<nL;i++){ //linha
		for(j=0;j<nC;j++){ //coluna
			if(mat[i][j] == 'X' || mat[i][j] == 'O') vivo = 1;//verifica se a posição central está viva

			//Estrutura que verefica cada vizinho e contabiliza se o mesmo está vivo ou morto
			if( !((j-1)<0) )
        		if(mat[i][j-1] == 'X' || mat[i][j-1] == 'O') vivas++  ;//local 4

    		if( !((j-1)<0) && ((i+1)<nL) )
				if(mat[i+1][j-1] == 'X' || mat[i+1][j-1] == 'O') vivas++;//local 7

    		if( ((i+1)<nL) )
				if(mat[i+1][j] == 'X' || mat[i+1][j] == 'O') vivas++;//local 8

    		if( ((j+1)<nC) && ((i+1)<nC) )
				if(mat[i+1][j+1] == 'X' || mat[i+1][j+1] == 'O') vivas++;//local 9

    		if( ((j+1)<nC) )
				if(mat[i][j+1] == 'X' || mat[i][j+1] == 'O') vivas++;//local 6

    		if( ((j+1)<nC) && !((i-1)<0) )
				if(mat[i-1][j+1] == 'X' || mat[i-1][j+1] == 'O') vivas++;//local 3

    		if( !((i-1)<0) )
				if(mat[i-1][j] == 'X' || mat[i-1][j] == 'O') vivas++;//local 2

    		if( !((j-1)<0) && !((i-1)<0) )
				if(mat[i-1][j-1] == 'X' || mat[i-1][j-1] == 'O') vivas++;//local 1

			//estrutura que aplica as regras do jogo
            if(mat[i][j]=='X' || mat[i][j]==' '){
                if(vivas == 3) aux[i][j]= 'X';
                else if(vivo==1 &&(vivas > 3 || vivas <2)) aux[i][j]= ' ';
                else if(vivo==1 && (vivas == 3 || vivas == 2)) aux[i][j]= 'X';
                vivas=0,vivo = 0;
            }else if(mat[i][j]=='O'){
                if(vivas == 3) aux[i][j]= 'O';
                else if(vivo==1 &&(vivas > 3 || vivas <2)) aux[i][j]= ' ';
                else if(vivo==1 && (vivas == 3 || vivas == 2)) aux[i][j]= 'O';
                vivas=0,vivo = 0;
            }

		}
	}
}

void limpaMatriz(char **m, int nL, int nC){//Função que limpa a matriz
	int i,j;
    for(i=0;i<nL;i++)
    	for(j=0;j<nC;j++)
    		m[i][j]=VAZ;
}

void inicBloco(char **m, int nL, int nC){//Função que inicia o bloco

	char padrao[2][2]={{VAZ, VAZ},{VAZ, VAZ}};

    FILE *fp;
    int i, j, k, xInic=nL/2, yInic=nC/2;
    char line[LINESIZE+1], *token;
    int vetor[3];

    fp = fopen("bloco.csv", "r"); // abre arquivo para leitura

    if (fp == NULL){
      printf("Erro de arquivo\n");
      exit(1);
    }

    fgets(line, LINESIZE, fp);// tenta ler uma linha

    while (!feof(fp)){  // verifica se não é o final do arquivo
      token=strtok(line, ",");
      i = 0;
      while (token != NULL){
        vetor[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
      }

      k=vetor[0];
      for(j=1;j<i;j++){
        padrao[k][vetor[j]] = 'X';
      }
      fgets(line, LINESIZE, fp);// tenta ler a proxima linha
    }
    fclose(fp) ;

	limpaMatriz(m,nL,nC);


	for(i=0;i<2;i++)
    	for(j=0;j<2;j++)
    		m[xInic+i][yInic+j]=padrao[i][j];
}

void inicCalango(char **m, int nL, int nC){//Função que inicia a vida eterna2/ calanguinho

	char padrao[3][3]={{VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ}};

	int i,j,k, xInic=nL/2, yInic=nC/2, vetor[4];

	FILE *fp;
    char line[LINESIZE+1], *token;

    fp = fopen("calango.csv", "r"); //abre arquivo para leitura

    if (fp == NULL){
      printf("Erro de arquivo\n");
      exit(1);
    }

    fgets(line, LINESIZE, fp);//tenta ler uma linha

    while (!feof(fp)){  //verifica se não é o final do arquivo
        token=strtok(line, ",");
        i = 0;
        while (token != NULL){
            vetor[i] = atoi(token);
            token = strtok(NULL, ",");
            i++;
        }
        k=vetor[0];
        for(j=1;j<i;j++){
            padrao[k][vetor[j]] = 'X';
        }
        fgets(line, LINESIZE, fp);  // tenta ler a proxima linha
    }
    fclose(fp) ;

	limpaMatriz(m,nL,nC);

	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			m[xInic+i][yInic+j]=padrao[i][j];
}

void inicBlinker(char **m, int nL, int nC){//Função que inicia o bloco
	char padrao[1][3] ={{VAZ,VAZ,VAZ}};
	int i, j,k, vetor[4], xInic=nL/2, yInic=nC/2;
    FILE *fp;
    char line[LINESIZE+1], *token;

    fp = fopen("blinker.csv", "r"); // abre arquivo para leitura

    if (fp == NULL){
        printf("Erro de arquivo\n");
        exit(1);
    }

    fgets(line, LINESIZE, fp);     // tenta ler uma linha

    while (!feof(fp)){  // verifica se não é o final do arquivo
        token=strtok(line, ",");
        i = 0;
        while (token != NULL){
            vetor[i] = atoi(token);
            token = strtok(NULL, ",");
            i++;
        }

        k=vetor[0];
        for(j=1;j<i;j++)
            padrao[k][vetor[j]] = 'X';



        fgets(line, LINESIZE, fp);// tenta ler a proxima linha
    }
    fclose(fp) ;
    limpaMatriz(m,nL,nC);

	for(i=0;i<1;i++)
    	for(j=0;j<3;j++)
    		m[xInic+i][yInic+j]=padrao[i][j];
}

void inicSapo(char **m, int nL, int nC){//Função que inicia o sapo

	char padrao[2][4] = {{VAZ,VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ,VAZ}};
	int i, j,k, xInic=nL/2, yInic=nC/2, vetor[4];
	FILE *fp;
    char line[LINESIZE+1], *token;

    fp = fopen("sapo.csv", "r"); // abre arquivo para leitura

    if (fp == NULL){
        printf("Erro de arquivo\n");
        exit(1);
    }

    fgets(line, LINESIZE, fp);     // tenta ler uma linha

    while (!feof(fp)){  // verifica se não é o final do arquivo
        token=strtok(line, ",");
        i = 0;
        while (token != NULL){
            vetor[i] = atoi(token);
            token = strtok(NULL, ",");
            i++;
        }

        k=vetor[0];

        for(j=1;j<i;j++)
            padrao[k][vetor[j]] = 'X';

        fgets(line, LINESIZE, fp);// tenta ler a proxima linha
    }
    fclose(fp) ;

	limpaMatriz(m,nL,nC);

	for(i=0;i<2;i++)
		for(j=0;j<4;j++)
			m[xInic+i][yInic+j]=padrao[i][j];
}

void inicGlider(char **m, int nL, int nC){//Função que inicia o glider
	char padrao[3][3]={{VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ}};

	int i, j, k, vetor[4], xInic= nL-4, yInic= nC-4;
	FILE *fp;
    char line[LINESIZE+1], *token;

    fp = fopen("glider.csv", "r"); // abre arquivo para leitura

    if (fp == NULL){
        printf("Erro de arquivo\n");
        exit(1);
    }

    fgets(line, LINESIZE, fp);     // tenta ler uma linha

    while (!feof(fp)){  // verifica se não é o final do arquivo
        token=strtok(line, ",");
        i = 0;
        while (token != NULL){
            vetor[i] = atoi(token);
            token = strtok(NULL, ",");
            i++;
        }

        k=vetor[0];
        for(j=1;j<i;j++)
            padrao[k][vetor[j]] = 'X';

        fgets(line, LINESIZE, fp);// tenta ler a proxima linha
    }
    fclose(fp) ;

	limpaMatriz(m,nL,nC);

	for(i=0;i<3;i++)
    	for(j=0;j<3;j++)
      		m[xInic+i][yInic+j]=padrao[i][j];
}

void inicLWSS(char **m, int nL, int nC){ //Função que inicia lwss

	char padrao[4][5] = {{VAZ,VAZ,VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ,VAZ,VAZ}};

    FILE *fp;
    char line[LINESIZE+1], *token;
 	int i, j, k, vetor[5], xInic= nL-5, yInic= nC-6;

    fp = fopen("lwss.csv", "r"); // abre arquivo para leitura

    if (fp == NULL){
        printf("Erro de arquivo\n");
        exit(1);
    }

    fgets(line, LINESIZE, fp);     // tenta ler uma linha

    while (!feof(fp)){  // verifica se não é o final do arquivo
        token=strtok(line, ",");
        i = 0;
        while (token != NULL){
            vetor[i] = atoi(token);
            token = strtok(NULL, ",");
            i++;
        }

        k=vetor[0];
        for(j=1;j<i;j++)
            padrao[k][vetor[j]] = 'X';

        fgets(line, LINESIZE, fp); // tenta ler a proxima linha
    }
    fclose(fp) ;

     limpaMatriz(m,nL,nC);

     for(i=0;i<4;i++)
        for(j=0;j<5;j++)
          m[xInic+i][yInic+j]=padrao[i][j];
}

void inicEstrela(char **m, int nL, int nC){//Função que inicia a estrelinha
	char padrao[3][11] ={{VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ},{VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ},
	{VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ,VAZ}};

	int i, j,k, vetor[12], xInic= nL/4, yInic= nC/4;
    FILE *fp;
    char line[LINESIZE+1], *token;

    fp = fopen("estrela.csv", "r"); // abre arquivo para leitura

    if (fp == NULL){
        printf("Erro de arquivo\n");
        exit(1);
    }

    fgets(line, LINESIZE, fp);     // tenta ler uma linha

    while (!feof(fp)){  // verifica se não é o final do arquivo
        token=strtok(line, ",");
        i = 0;
        while (token != NULL){
            vetor[i] = atoi(token);
            token = strtok(NULL, ",");
            i++;
        }

        k=vetor[0];
        for(j=1;j<i;j++)
            padrao[k][vetor[j]] = 'X';



        fgets(line, LINESIZE, fp);// tenta ler a proxima linha
    }
    fclose(fp) ;
    limpaMatriz(m,nL,nC);

	for(i=0;i<3;i++)
    	for(j=0;j<11;j++)
    		m[xInic+i][yInic+j]=padrao[i][j];
}

void invasora(char **m, int nL, int nC){//Função que inicia a população invasora
    char padrao[2][2]={{VAZ, VAZ},{VAZ, VAZ}};

    FILE *fp;
    int i, j, k, xInic=nL/2, yInic=nC/2;
    char line[LINESIZE+1], *token;
    int vetor[3];

    fp = fopen("inv.csv", "r"); // abre arquivo para leitura

    if (fp == NULL){
      printf("Erro de arquivo\n");
      exit(1);
    }

    fgets(line, LINESIZE, fp);// tenta ler uma linha

    while (!feof(fp)){  // verifica se não é o final do arquivo
      token=strtok(line, ",");
      i = 0;
      while (token != NULL){
        vetor[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
      }

      k=vetor[0];
      for(j=1;j<i;j++){
        padrao[k][vetor[j]] = 'O';
      }
      fgets(line, LINESIZE, fp);// tenta ler a proxima linha
    }
    fclose(fp) ;

    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
            m[xInic+i][yInic+j]=padrao[i][j];

}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////




