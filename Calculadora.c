/*
 Desenvolvedora :  Adeline Rodrigues Cruz Wyse Guimarães
 Data inicio do projeto: 28/06/2021
 Data inicio calculadora.c: 29/06/2021
 Data fim projeto: 
 Requisitos: 
        Ser capaz de pegar um valor em reais (float) e calcular qual o número máximo de visualizacoes que o anuncio pode atingir.
        Esses calculos são baseados nessas regras:
          - a cada 100 pessoas que visualizam o anuncio 12 clicam nele.
          - a cada 20 pessoas que clicam no anúncio 3 compartilham nas redes sociais.
          - cada compartilhamento nas redes sociais gera 40 novas visualizações.
          - 30 pessoas visualizam o anuncio original (nao compartilhado) a cada R$ 1,00 investido.
          - o mesmo anuncio e compartilhado no maximo 4 vezes em sequência
            (1ª pessoa -> compartilha -> 2ª pessoa -> compartilha - > 3ª pessoa -> compartilha -> 4ª pessoa)
    Esse e o script solucao para a primeira parte do desafio. O meu entendimento e que essa parte precisa ser independente
 do resto do sistema, para poder ser usada individualmente.

 Primeira parte do desafio de programação https://www.proway.com.br/academiacapmulheresdesafio.

    O script pega um valor correspondente ao valor investido e faz o calculo baseado nas informacoes acima para quantas visualizacoes
 a mais são geradas por cada 1 real investido. Esse calculo e feito 3 vezes por anuncio - isso por que como o anuncio so e compartilhado
 4 vezes em sequencia a ultima visualizacao nao gera novas visualizacoes. O script entao soma as visualizações geradas com as visualizacoes 
 iniciais e da o valor de maximo de visualizacoes para o valor investido.

*/
#include <stdio.h>

 float PegarValor(float); // funcao para pegar o valor do investimento;
 int Calcular(); // funcao que faz o calculo

 float investimento = 0; //  investimento em reais no anuncio
 float vTotal = 0;  // numero total de visualizacoes
 float totalCompartilhamentos = 0; // numero total de compartilhamentos no fim do programa
 float totalCliques = 0; // numero total de cliques no fim do programa



int main()
{
    Calcular();
    return 0;
}
 
float PegarValor(float inv)
{
    printf("Quantos reais vao ser investidos?\n");
    scanf("%f" , &inv);
    return inv;
    
}

int Calcular()
{
    float 
        vInicial = 0, // numero de visualizacoes inicialmente
        vAdcional = 0, // numero de visualizacoes a mais no fim do loop
        vCompartilhados = 0, // numero de visualizacoes vindas de compartilhamentos,  usado para assistencia dos calculos
        vTemp = 0,  // // numero de visualizacoes a mais no fim de cada interacao do loop, usado para assistencia dos calculos
        tempCompartilhamentos = 0, // numero de compartilhamentos,  usado para assistencia dos calculos
        tempCliques = 0; // numero de cliques ,  usado para assistencia dos calculos
    int i = 0;

    investimento = PegarValor(investimento);
    vInicial = investimento*30;
    vTemp = vInicial;
    
    for (i = 0; i < 3; i++)
    {
        tempCliques = (vTemp * 12) / 100;
        totalCliques += tempCliques;
        tempCompartilhamentos = (tempCliques * 3) / 20;
        totalCompartilhamentos += tempCompartilhamentos;    
        vTemp = tempCompartilhamentos * 40;
        vCompartilhados += vTemp;
        
    }
   
    vTotal = (vInicial + vCompartilhados);
    
    printf("Visualicao maxima = %0.1f\n" , vTotal);
    return 0;
}