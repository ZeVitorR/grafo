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

//função para deixar o vetor na ordem alfabetica
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

//função para verificar e adicionar os vertices do matrizAdj
int adiciona_vertices(char arestas[][3], int qtdArestas,char vertices[],int qtdVertices){
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

    ordem_vetor(vertices, pos);
    return pos; //está retornando o tamnho do vetor de vertices
}

//verifica a posição
int verifica_pos(char vertices[],int qtdVertices,char vert){
    int pos;
    for(int i=0;i<qtdVertices;i++){
        if(vertices[i] == vert){//verifica se o elemento atual é igual ao vertice solicitado
            pos = i; // se for ele irá definir a posição como a do i
            i = qtdVertices;//em seguida definirá o i como o valor de saida do for pois não é mais nescessário
        }
    }
    return pos;//por fim ira retornar a posição do vertice que solicitou
}

int menor_dist(int distancias[], bool visitado[], int tamanho) {
   int distMin = INT_MAX;//definindo a variavel com o valor maximo de inteiro
   int posMin; 

   for (int i = 0; i < tamanho; i++) {
       if (visitado[i] == false && distancias[i] <= distMin) { //verifica se não foi visitado e se a distancia na posição i é menor
           distMin = distancias[i];//se for verdade irá definir a distancia 
           posMin = i;
       }
   }

   return posMin;
}

// Função para imprimir o caminho mais curto do vértice de inicial para o vértice dado
void imprimirCaminho(int verticePai[],int inicio, int destino, char vertices[]) {
   if (verticePai[destino] == -1) { //ira verificar se o vertice pai é menos um para ver se é a origem
       printf("%c\t",  vertices[destino]);//como é será imprimido e colocado um espaço com o tab
       return;
   }
    //agora irá chamar a função imprimirCaminho fazendo uma recursividade onde vai sempre alterando o vetor vetice pai
    //até que chegue no de origem que é igual ao -1 e começar a imprimir o caminho que foi realizado para chegar ao
    //menor caminho
   imprimirCaminho(verticePai,inicio, verticePai[destino],vertices); 
   printf("%c\t", vertices[destino]);
}


// Função que implementa o algoritmo de Dijkstra para encontrar o menor caminho em um matrizAdj ponderado
void menor_caminho( int tamanho,int matrizAdj[tamanho][tamanho],char vertices[], int posInicial ,int posFinal) {
   int distancias[tamanho];     // Vetor para armazenar as distâncias mínimas dos vértices
   bool visitado[tamanho];      // Vetor para verificar os vértices visitados
   int verticePai[tamanho];     // Vetor para verificar o caminho mais curto

   // Inicializar todas as distâncias como infinito e visitado como falso
   for (int i = 0; i < tamanho; i++) {
       distancias[i] = INT_MAX;
       visitado[i] = false;
   }

   // A distância do vértice inicial para ele mesmo é sempre 0
   distancias[posInicial] = 0;
   verticePai[posInicial] = -1;  // O vértice inicial não tem pai

   // Encontrar o caminho mais curto para todos os vértices
   for (int count = 0; count < tamanho - 1; count++) {
       int u = menor_dist(distancias, visitado,tamanho);
       visitado[u] = true;  // Marcar o vértice como visitado

       // Atualizar distâncias dos vértices adjacentes
       for (int v = 0; v < tamanho; v++) {
            //Analisa
           if (visitado[v] == false && matrizAdj[u][v] && distancias[u] != INT_MAX &&
               distancias[u] + matrizAdj[u][v] < distancias[v]) {
               distancias[v] = distancias[u] + matrizAdj[u][v];
               verticePai[v] = u;
           }
       }
   }
    if (distancias[posFinal] != INT_MAX) { //verifica se a distancia não é infinita, senão foi visitado o vertice
        printf("Caminho mais curto de %c para %c:\n",  vertices[posInicial],  vertices[posFinal]);
        printf("Distancia: %d\n", distancias[posFinal]);
        printf("Caminho: ");
        imprimirCaminho(verticePai,posInicial, posFinal,vertices);
        printf("\n");
        } else {
            printf("Nao há caminho entre %c e %c\n", vertices[posInicial],  vertices[posFinal]);
        }
}


int main(){
    char g3_vertices[15],g3_arestas[50][3];
    FILE *arq;
     //leitura do terceiro arquivo
    int cont=0;
    arq = fopen("g3.txt","r");
    if (arq == NULL){ //verifica se o arquivo possui algum conteudo ou foi aberto
        printf("Arquivo não pode ser aberto");
        return 0;
    }else{ 
        int rr;
        while (( fscanf(arq,"%c;%c;%i;\n",&g3_arestas[cont][0],&g3_arestas[cont][1],&rr)) != EOF){
            g3_arestas[cont][2] = rr;  
            cont++;
        }
        fclose(arq);
    }
    for(int j=0; j<15;j++){
        g3_vertices[j] = ' ';
    }
    
    int tamVertices3 = adiciona_vertices(g3_arestas,cont,g3_vertices,15);
    
    int matrizAdj[tamVertices3][tamVertices3];
    for(int i=0; i<tamVertices3;i++){
        for(int j=0;j<tamVertices3; j++){
            matrizAdj[i][j]=0;
        }
    }
    
    for(int i=0; i<tamVertices3;i++){
        for(int j=0;j<cont; j++){
            int pos;
            if(g3_arestas[j][0] == g3_vertices[i]){
                pos = verifica_pos(g3_vertices,tamVertices3,g3_arestas[j][1]);
                matrizAdj[i][pos] = g3_arestas[j][2];
            }else if(g3_arestas[j][1] == g3_vertices[i]){
                pos = verifica_pos(g3_vertices,tamVertices3,g3_arestas[j][0]);
                matrizAdj[i][pos] = g3_arestas[j][2];
            }
            
        }
    }
    printf("\nMatriz de Adjascencia:\n");
    for(int i=0; i<tamVertices3;i++){
        printf("%c\t",g3_vertices[i]);
    }
    printf("\n");
    for(int i=0; i<tamVertices3;i++){
        for(int j=0;j<tamVertices3; j++){
            printf("%i\t",matrizAdj[i][j]);
        }
        printf("\n");
    }
    menor_caminho(tamVertices3,matrizAdj,g3_vertices, verifica_pos(g3_vertices,tamVertices3,'x'),verifica_pos(g3_vertices,tamVertices3,'t'));
    return 0;
}