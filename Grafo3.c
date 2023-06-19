// José Vitor Rodrigues - 1948322 
// Michel de Alcantara  - 1923883    

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

//função para verifica se o elemento já foi inserido no vetor
int verifica_visitado(char visitado[15],int tam, char elemento){
    for(int i = 0; i<tam; i++){//percorrer todo o vetor 
        if(visitado[i] == elemento){//verifica se possui o elemento

             return 1;//possuindo irá sair do for retornando 1
        }
    }
    return 0;//se não foi localizado o vetor irá retornar 0
}

//função para verificar e adicionar os vertices do grafo
int adiciona_vertices(char arestas[][2], int qtdArestas,char vertices[],int qtdVertices){
    int pos=0;//variavel responsável por definir a posição que sera inserido no vetor de vertices
    for(int i=0;i<qtdArestas;i++){
        //if para verificar se possui ou não elemento, caso for 0 ele não foi visitado então é inserido no vetor
        if( verifica_visitado(vertices,qtdVertices,arestas[i][0]) == 0){//esse primeiro if verifica o vertice de saida
            vertices[pos] = arestas[i][0]; 
            pos ++;
        }
        if( verifica_visitado(vertices,qtdVertices,arestas[i][1]) == 0){//no segundo verifica o vertice de entrada
            vertices[pos] = arestas[i][1];
            pos ++;
        }
    }
    return pos; //está retornando o tamnho do vetor de vertices
}

//deixa o vetor em ordem alfabética
void ordem_vetor(char vetor[], int tam){
    char a,b;
    for(int i=0; i<tam;i++){
        for(int j=0; j<tam; j++){
            if(vetor[i] < vetor[j]){//caso o vertice da posição i seja maior que a posição j
                a = vetor[i]; //irá salvar o elemento da posição i em a
                b = vetor[j];//irá salvar o elemento da posição j em b
                vetor[i] = b; //agora irá definir o elemento que está no i o valor b
                vetor[j] = a;//e o valor j que está em a
            }
        }
        
    }
}

//função para verificar a adjascencia do vertice                                           
int verifica_adjascente(int qtdadj,char adjascentes[], char arestas[][2],int tam, char vertice,int tipo){
    qtdadj =0;//definindo inicialmente o qtd como 0
    for(int i=0; i<tam; i++){//percorre todo o vetor para procurar adjascencia 
        if(tipo == 1){//se o grafo não for direcionado
            if(arestas[i][0] == vertice ){//verifica se o vertice de saida é igual ao vertice 
                adjascentes[qtdadj]=arestas[i][1];//caso seja irá definir no vetor de adjascencia que 
                //na posição qtdadj será inserido o elemento da aresta correpondente
                qtdadj++;//no final ira somar um na posição
            }else if(arestas[i][1] == vertice){//verifica se o vertice de destino é igual ao vertice
                adjascentes[qtdadj]=arestas[i][0];//caso seja irá definir no vetor de adjascencia que 
                //na posição qtdadj será inserido o elemento da aresta correpondente
                qtdadj++;//no final ira somar um na posição
            }

        }else{//Se o grafo for direcionado
            if(arestas[i][0] == vertice ){//verifica se o vertice de saida é igual ao vertice 
                adjascentes[qtdadj]=arestas[i][1];//caso seja irá definir no vetor de adjascencia que 
                //na posição qtdadj será inserido o elemento da aresta correpondente
                qtdadj++;//no final ira somar um na posição
            }
        }
    }
    ordem_vetor(adjascentes,qtdadj);//caso não esteja em ordem alfabetica ira ficar
    return qtdadj;// for fim retornará a quantidade de elementos do vetor adjascentes
}

//função para inserir no na posição solicitado do vetor
int vetor_insere_pos(char vetor[],int tam,char inserir,int pos){
	char vp[26]; //vetor provisório para inserir os elementos
	int cont = 0;//contador responsável por definir a posição de inserção
	
     if(tam == 0){//verifica se o tamanho for igual a 0
         vetor[0] = inserir;//insere na posição inicial
     }else{//caso contrário
         for(int i=0; i<tam;i++){//agora irá percorrer toda a lista
			
            if(cont == pos){
                vp[pos]=inserir;//irá inserir o elemento que deseja na posição definida do vp
                cont++;
                vp[cont] = vetor[i];//definindo o vp como o elemento da posição i 
                cont++;
            }else{
                vp[cont] = vetor[i];//definindo o vp como o elemento da posição i 
                cont++;
            }
         }
		 tam = cont;//definindo o tamanho como a quantidade de elementos do vp
         for(int j=0;j<tam;j++){//percorrendo todo o vetor vp
			vetor[j] = vp[j];//definindo o elemento j do vetor como o elemento [j] do vp
		 }
     }
     return tam;
}

//função para inserir no fim do vetor
int vetor_insere_fim(char vetor[],int tam,char inserir){
    vetor[tam]= inserir;//irá inserir o elemento na posição do tamanho
    tam++;
    return tam;
}

//função para remover o elemento do inicio
int vetor_remove_inicio(char vetor[],int tam){
    if(tam == 1){//verifica se possui somente 1 elemente
        vetor[0] = ' ';
        return 0;
    }else{
        for(int i = 0; i<tam; i++){//irá percorrer toda o vetor
            if(i == tam-1){//se o tamanho for igual a menor tam-1
                vetor[i]=' ';//ira retirar o elemento da ultima posição
            }else{
                vetor[i] = vetor[i+1];//caso contrário ira atribuir os elementos para a posição anterior
            }
        }
        tam--;
        return tam;
    }
}

//função para remover de acordo com o vertice inserido
int vetor_remove_vertice(char adjascente[],int tam, char vertice) {
    int pos;
    for(int i=0;i<tam; i++){
        if(vertice == adjascente [i])
            pos = i;
    }
    for(int j=pos-1;j<tam; j++){
        if(j < tam-1){
            adjascente [j] = adjascente [j+1];
        }else{
            adjascente [j] = ' ';
        }
    }
    return tam-1;
}

//Função para fazer a busca de profundidade
void busca_largura(char visitado[],int tam,char arestas[][2], int qtdAresta,char inicial,int qtdVertices){
    char aVisitar[tam];//vetor para definir a ordem da busca
    int posVisitar = 0,posVisitado = 0,qtdadj; //posição de ser inserido igual a 0
    char adjascente[tam];
    aVisitar[posVisitar]=inicial;//é definido vertice que precisa visitar o inicialmente
    posVisitar=1;
    
    for(int i=0; i< qtdVertices; i++){ //aqui irá percorrer a quantidade de vertices que possui o grafo
        qtdadj = verifica_adjascente(qtdadj,adjascente,arestas,qtdAresta,aVisitar[0],1); 

        if(verifica_visitado(visitado,posVisitado,aVisitar[0]) == 0){ //verificar se o elemento ja foi visitado, se for 0 ele não foi
                posVisitado = vetor_insere_fim(visitado,posVisitado,aVisitar[0]);//atribui para a posição de visitado mais 1 e insere
                //no final o valor da primeira posição do a visitar
                posVisitar = vetor_remove_inicio(aVisitar,posVisitar);//em seguida ira remover o primeiro elemento de aVisitar   
        }
        //logo apos de fazer esse if ele ira remover caso inserio todos os valore já visitado
        while (verifica_visitado(visitado,posVisitado,aVisitar[0]) != 0)
        {
            posVisitar = vetor_remove_inicio(aVisitar,posVisitar);
        }
        //depois irá pegar todos os valores já obtido da ajacencia e inserir no aVisitar
        for(int j=0; j<qtdadj;j++){
            posVisitar = vetor_insere_fim(aVisitar,posVisitar,adjascente[j]);
        }
        
    }
}

//função para fazer a busca de profundidade
int busca_profundidade(char visitado[],int tam,char arestas[][2], int qtdAresta,char inicial, int qtdVertices,int tipo){
    char aVisitar[1000];//vetor para definir a ordem da busca
    int posVisitar = 1,posVisitado = 0,qtdadj; //posição de ser inserido igual a 0
    char adjascente[tam];
    posVisitado = vetor_insere_fim(visitado,posVisitado,inicial);
    for(int i=0; i< qtdVertices; i++){ //aqui irá percorrer a quantidade de vertices que possui o grafo
        qtdadj = verifica_adjascente(qtdadj,adjascente,arestas,qtdAresta,visitado[i],tipo); //defino os vertices que são adjacente de acordo com a posição do visitado
        int x = qtdadj;//defino o x sendo igual ao qtdadj por que ele será afetado
        for(int j=0; j<x;j++){ //ira percorrer até chear ao tamanho de x
            if(verifica_visitado(visitado,posVisitado,adjascente[j]) == 1){//fara a verificação se foi adicionado algum vertice ja visitado no adjascente
                  qtdadj = vetor_remove_vertice(adjascente,qtdadj,adjascente[j]) ; //se foi ira remover ele
            }
            
        }
        for(int j=0; j<qtdadj;j++){//agora será percorrido ate o tamnho que ficou o adjascente
            posVisitar = vetor_insere_pos(aVisitar,posVisitar,adjascente[j],j);//ira adicionar as posição de visitar de acordo com a posição na adjascencia          
        }
                
        if( verifica_visitado(visitado,posVisitado,aVisitar[0]) == 0){ //verificar se o elemento não foi visitado, se for 0 ele não foi
            if(aVisitar[0] != ' ' ){
                posVisitado = vetor_insere_fim(visitado,posVisitado,aVisitar[0]);//atribui para a posição de visitado mais 1 e insere
                posVisitar = vetor_remove_inicio(aVisitar,posVisitar);//remover do inicio a posição inicial do aVisitar                  
            }else{
                posVisitar = vetor_remove_inicio(aVisitar,posVisitar);//remover do inicio a posição inicial do aVisitar                  
            }
            
        }else{
            posVisitar = vetor_remove_inicio(aVisitar,posVisitar);//remover do inicio a posição inicial do aVisitar
        }   
    } 
    return posVisitado;
}



int main(){
    char g1_arestas[20][2],g2_arestas[20][2];
    FILE *arq,*arq2;
    int cont =0;
    //leitura do primeiro arquivo    
    arq = fopen("g1.txt","r");
    if (arq == NULL){ //verifica se o arquivo possui algum conteudo ou foi aberto
        printf("Arquivo não pode ser aberto");
    }else{ 
        while (( fscanf(arq,"%c;%c;\n",&g1_arestas[cont][0],&g1_arestas[cont][1])) != EOF){  
            cont++;
        }
        fclose(arq);
    }

    // //leitura do segundo arquivo
    cont=0;
    arq2 = fopen("g2.txt","r");
    if (arq2 == NULL){ //verifica se o arquivo possui algum conteudo ou foi aberto
        printf("Arquivo não pode ser aberto");
    }else{ 
        while (( fscanf(arq2,"%c;%c;\n",&g2_arestas[cont][0],&g2_arestas[cont][1])) != EOF){  
            cont++;
        }
        fclose(arq2);
    }
    char g1_vertices[15],g2_vertices[15];
    for(int j=0; j<15;j++){
        g1_vertices[j] = ' ';
    }
    char visitado[12],visitado2[12];
    int tamVertices = adiciona_vertices(g1_arestas,20,g1_vertices,12);
   
    busca_largura(visitado,12,g1_arestas,20,'b',tamVertices);
    printf("\n\nA busca de largura do g1 comecando pelo vertice b foi:\n");
    for(int i = 0;i<12;i++){
        printf("%c\t",visitado[i]);
    }
     for(int j=0; j<15;j++){
        g2_vertices[j] = ' ';
    }
    int tamVertices2 = adiciona_vertices(g2_arestas,15,g2_vertices,13);
    int tam = busca_profundidade(visitado2,tamVertices2,g2_arestas,15,'a',tamVertices2,3);
    printf("\n\nA busca de profundidade do g2 comecando pelo vertice a foi:\n");
    for(int i = 0;i<tam-1;i++){
        printf("%c\t",visitado2[i]);
    }
}