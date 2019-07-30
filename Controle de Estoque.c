#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados {
        char descricao[50];
        char codigo[50];
        int qtd_estoque;
        int qtd_minino;
        char data_validade[50];

        };

void inclui();
void lista();
int pesquisa();
int pesquisa_data();
int pesquisa_letra();
int pesquisa_naodisponivel();
void altera_estoque();
void altera();
void exclui();

int main()
{
        struct dados info;
        struct dados *p;

        int op;
        int i;
        int tam;    //n. de bytes da estrutura

        p = & info;
        tam = sizeof(info);

        for(i=0;i<sizeof(info);i++) {   //zera a estrutura de dados
            info.descricao[i]=0;
           }
        while(1){
        printf("\n\n===");
        printf("BEM VINDO AO CONTROLE DE ESTOQUE DO JOAO PEDRO");
        printf("===\n\n");
        printf(" 1 -Inclua dados  \n");
        printf(" 2 -Lista dados  \n");
        printf(" 3 -Pesquisa dados  \n");
        printf(" 4 -Altera dados  \n");
        printf(" 5 -Exclui dados  \n");
        printf(" 6 -Pesquisa por de validade\n");
        printf(" 7 -Pesquisa por letra \n");
        printf(" 8 -Pesquisa produto nao disponivel \n");
        printf(" 9 -Movimentacao de estoque \n");
        printf(" 10 -Saida\n\n");
        printf("======================\n");
        scanf("%d", &op);
        getchar();


    switch(op)
                {
                case 1 : inclui(p, tam);   //passa como parametro o ponteiro para a estrutura e o n. de bytes da desta
                break;

                case 2: lista(p, tam);
                break;

                case 3: pesquisa(p, tam);
                break;

                case 4: altera(p, tam);
                break;

                case 5: exclui(p, tam);
                break;

                case 6: pesquisa_data(p,tam);
                break;

                case 7:pesquisa_letra(p,tam);
                break;

                case 8:pesquisa_naodisponivel(p,tam);
                break;

                case 9:altera_estoque(p,tam);
                break;

                case 10: exit(0);
                break;

                default: printf("\n opcao invalida\n");
                }
    };

}

void inclui(struct dados *ps, int tam)
{
    FILE *p, *p1;
    int cont = 0;
    int i;

    p1=fopen("contador.txt","r");
    fscanf(p1,"%d",&cont);

    fclose(p1);

    for(i=0;i<tam;i++){ //zera os dados da estrutura
        ps -> descricao[i]=0;
    }

    p=fopen("arquivo.txt", "a");

    if(p==NULL){
        printf("\nERRO");
        exit(1);
    }

   //aqui os dados sao recebidos via teclado


    printf("Descricao ");
    gets(ps->descricao);

    printf("\n Codigo Produto\n");
    gets(ps->codigo);

    printf("\n Quantidade atual do Produto\n");
    scanf("%d",&ps->qtd_estoque);

    printf("\n Quantidade estoque minimo do Produto\n");
    scanf("%d",&ps->qtd_minino);

    printf("\n Data de Validade do Produto\n");
    getchar();
    gets(ps->data_validade);
    printf("======================");



   // fwrite

    fwrite(ps,tam,1,p);
    fclose(p);

    cont++;

    p1=fopen("contador.txt", "w");
    fprintf(p1,"%d",cont);
    // printf("contador depois %d\n",cont); ACHO QUE VOU EXCLUIR
    fclose(p1);
}

void lista(struct dados *ps, int tam)
{
    FILE *p, *p1;
    FILE *a;
    struct dados info;
    int i;
    int cont,comp;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    //printf("%d\n",cont); ACHO QUE VOU EXCLUIR
    fclose(p1);

    p = fopen("arquivo.txt", "r"); /*r" --> Abre o arquivo apenas para leitura.*/

    if( p== NULL)
        {
        puts("\nERRO\n");
        exit(1);
    }

    //a
    for(i=0;i<cont; i++){
        comp = i*tam;   //calcula o n. de bytes para posicionar o ponteiro do arquivo

    fseek(p,comp,0);    //posiciona o ponteiro no inicio do registro dentro do arquivo
    fread(ps,sizeof(info),1,p);   //le o registro
    if(ps -> descricao[0] != '*'){     //verifica se esta apagado


        printf("\n Descricao: %s\n",ps->descricao);
        printf("Codigo: %s\n",ps->codigo);
        printf("Qtd Atual: %d\n",ps->qtd_estoque);
        printf("Qts Etoque Minimo: %d\n",ps->qtd_minino);
        printf("Data de Validade: %s\n",ps->data_validade);
        printf("======================");

        }


    }
        fclose(p);
}


int pesquisa(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char nome[20]; //???
    int i=0,y, x;
    int cont;

    printf("Informe um nome para pesquisa: ");
    gets(nome);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome[x] != '\0';x++){
            if(nome[x] != ps -> descricao[x]){
                break;
            }
        }

    if(nome[x] == '\0' && ps -> descricao[x] == '\0')
    {
        //printf("N. do Reg.: %d\n",y);
        printf("Descricao: %s\n",ps->descricao);
        printf("Codigo: %s\n",ps->codigo);
        printf("Qtd Atual: %d\n",ps->qtd_estoque);
        printf("Qts Etoque Minimo: %d\n",ps->qtd_minino);
        printf("Data de Validade: %s\n",ps->data_validade);
        printf("======================");
        return y;
    }
    }
    printf("\nRegistro nao existente\n");
    return -1;
}



void altera(struct dados *ps, int tam)
{
    FILE *p;
    int n_reg;;
    int n_bytes;

    n_reg = pesquisa(ps, tam);     //pesquisa o registro no arquivo
    printf("\naltera reg n.: %d\n",n_reg+1);
    if(n_reg == -1){
 	     return;
    }
    n_bytes = tam * n_reg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser alterado
    fread(ps, tam, 1, p );  //le registro do arquivo

    printf("\n RECEBE OS DADOS A SEREM ALTERADOS: ");
    //recebe via teclado todos os dados do registro

    printf("\n Descricao\n");
    gets(ps->descricao);

    printf("\n Codigo Produto\n");
    gets(ps->codigo);

    printf("\n Quantidade atual do Produto\n");
    scanf("%d",&ps->qtd_estoque);

    printf("\n Quantidade estoque minimo do Produto\n");
    scanf("%d",&ps->qtd_minino);

    printf("\n Data de Validade do Produto\n");
    getchar();
    gets(ps->data_validade);
    printf("======================");
    //aa


    fseek(p,n_bytes,0);    //posiciona o ponteiro do arquivo no inicio do regisro a ser alterado
    fwrite(ps, tam,1,p);  //escreve o registro no arquivo

    fclose(p);
}

void exclui(struct dados *ps, int tam)
{
    FILE *p;
    int n_reg;
    int n_bytes;
    n_reg = pesquisa(ps, tam);  //pesquisa o registro no arquivo
    if(n_reg == -1){
 	     return;
    }
    p = fopen("arquivo.txt", "r+");
    n_bytes = tam * n_reg;

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser apagado
    fread(ps, tam, 1, p );   //le o registro do arquivo
    printf("\nO produto que deseja excluir e?: %s\n",ps -> descricao);
    //apaga o registro do arquivo
    ps->descricao[0]='*';
    //printf("nome para apagar e' %s\n",ps -> descricao);
    printf("O produto foi apagado");

    fseek(p,n_bytes,0);  //posiciona o ponteiro do arquivo no inicio do regisro a ser apagado
    fwrite(ps,tam,1,p);  //escreve o registro

    fclose(p);

}

int pesquisa_data(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char dataval[20];
    int i=0,y, x;
    int cont;

    printf("Informe uma data para pesquisa: ");
    gets(dataval);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    printf("%d\n",cont);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; dataval[x] != '\0';x++){
            if(dataval[x] != ps -> data_validade[x]){
                break;
            }
        }

    if(dataval[x] == '\0' && ps -> data_validade[x] == '\0')
    {
        //printf("N. do Reg.: %d\n",y);
        printf("Descricao: %s\n",ps->descricao);
        printf("Codigo: %s\n",ps->codigo);
        printf("Qtd Atual do Estoque: %d\n",ps->qtd_estoque);
        printf("Qts Etoque Minimo: %d\n",ps->qtd_minino);
        printf("Data de Validade: %s\n",ps->data_validade);
        printf("======================");
        return y;
    }
    }
    printf("\nRegistro nao existente\n");
    return -1;
}

int pesquisa_letra(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char letra[20];
    int i=0,y, x;
    int cont;

    printf("Informe a 1 letra para pesquisa:\n ");
    gets(letra);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);



     for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);

            if(letra[0] == ps -> descricao[0]){

        printf("Descricao: %s\n",ps->descricao);
        printf("Codigo: %s\n",ps->codigo);
        printf("Qtd Atual: %d\n",ps->qtd_estoque);
        printf("Qts Etoque Minimo: %d\n",ps->qtd_minino);
        printf("Data de Validade: %s\n",ps->data_validade);
        printf("======================");

            }
        }

    printf("\nRegistro nao existente\n");
    return -1;
}

int pesquisa_naodisponivel(struct dados *ps, int tam)
{
    FILE *p;
    FILE *a;

    char nome[20];
    int i=0,y, x,ind;
    int cont;

    //printf("Informe o produto a ser pesquisado: ");
    //gets(nome1);

    p = fopen("arquivo.txt", "r");
    a = fopen("contador.txt", "r");
    fscanf(a,"%d",&cont);
    fclose(a);
    ind=0;
 printf("Lista de produtos indisponiveis\n");
    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
    if(ps -> descricao[0] != '*'){
    if(ps->qtd_estoque <=0 )
    {

        ind=1;
        printf("N. do Reg.: %d\n",y+1);
        printf("Descricao: %s\n",ps->descricao);
        printf("Codigo: %s\n",ps->codigo);
        printf("Qtd Atual do Estoque: %d\n",ps->qtd_estoque);
        printf("Qts Etoque Minimo: %d\n",ps->qtd_minino);
        printf("Data de Validade: %s\n",ps->data_validade);
        printf("======================");

    }

 }

}
         if(ind==0){
         printf("Registro nao existente\n");
         return -1;}
    }



void altera_estoque(struct dados *ps, int tam)
{
    FILE *p;
    int n_reg;;
    int n_bytes;
    int incremento;

    n_reg = pesquisa(ps, tam);     //pesquisa o registro no arquivo
    //printf("Registro para alterar estoque n.: %d\n",n_reg);
    if(n_reg == -1){
 	     return;
    }
    n_bytes = tam * n_reg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser alterado
    fread(ps, tam, 1, p );  //le registro do arquivo


    printf("\nPara acrescentar estoque (+) para subtrair (-) e a quantidade desejada: ");

    //receba a quantidade a ser alterada


    scanf("%d",&incremento);

    ps->qtd_estoque=ps->qtd_estoque+incremento;

    printf("\n Descricao:.%s \n\n Sua quantidade atual de estoque e:. %d \n\n",ps->descricao,ps->qtd_estoque);

    printf("_________________\n");

    fseek(p,n_bytes,0);    //posiciona o ponteiro do arquivo no inicio do regisro a ser alterado
    fwrite(ps, tam,1,p);  //escreve o registro no arquivo

    fclose(p);
}


