/*
 Desenvolvedora :  Adeline Rodrigues Cruz Wyse Guimarães
 Data inicio do projeto: 28/06/2021
 Data inicio CalculadoraSistema.c: 29/06/2021
 Data fim projeto: 
 Esse script é uma adaptacao do script calculadora. 
 Requisitos: 
        Ser capas de pegar um valor em reais (float) e calcular qual o número máximo de visualizacoes que o anuncio pode atingir.
        Esses calculos são baseados nessas regras:
          - a cada 100 pessoas que visualizam o anúncio 12 clicam nele.
          - a cada 20 pessoas que clicam no anúncio 3 compartilham nas redes sociais.
          - cada compartilhamento nas redes sociais gera 40 novas visualizacoes.
          - 30 pessoas visualizam o anuncio original (não compartilhado) a cada R$ 1,00 investido.
          - o mesmo anuncio e compartilhado no máximo 4 vezes em sequencia
            (1ª pessoa -> compartilha -> 2ª pessoa -> compartilha - > 3ª pessoa -> compartilha -> 4ª pessoa)

 Primeira parte do desafio de programacio https://www.proway.com.br/academiacapmulheresdesafio.

    O script pega um valor correspondente ao valor investido e faz o calculo baseado nas informacoes acima para quantas visualizacoes
 a mais são geradas por cada 1 real investido. Esse calculo é feito 3 vezes por anuncio - isso por que como o anuncio só é compartilhado
 4 vezes em sequência a ultima visualização não gera novas visualizações. O script então soma as visualizacoes geradas com as visualizacoes 
 iniciais e da o valor de maximo de visualizacoes para o valor investido.
    Dados sobre o total de cliques, compartilhamentos e total de visualizacoes vindas de compartilhamentos sao armazenadas para uso na 2 parte do
 deafio.


*/
#include <stdio.h>

 
 int Calcular(); // funcao que faz o calculo

 float investimento = 0; //  investimento em reais no anuncio
 float vTotal = 0;  // numero total de visualizacoes
 float totalCompartilhamentos = 0; // numero total de compartilhamentos no fim do programa
 float totalCliques = 0; // numero total de cliques no fim do programa

int Calcular()
{
    float 
        vInicial = 0, // numero de visualizacoes inicialmente
        vAdcional = 0, // numero de visualizacoes a mais no fim do loop
        vCompartilhados = 0, // numero de visualizacoes vindas de compartilhamentos,  usado para assistencia dos calculos
        vTemp = 0,  // numero de visualizacoes a mais no fim de cada interação do loop, usado para assistencia dos calculos
        tempCompartilhamentos = 0, // numero de compartilhamentos,  usado para assistência dos calculos
        tempCliques = 0; // numero de cliques ,  usado para assistencia dos calculos
    int i = 0;
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
    return 0;
}