#include <stdio.h>

float PegarValor(float);

int main(){
    float investimento = -1, 
        vTotal = 0, 
        totalCompartilhamentos = 0, 
        totalCliques = 0,
        vInicial = 0, 
        vAdcional = 0, 
        vCompartilhados = 0, 
        vTemp = 0, 
        tempCompartilhamentos = 0,
        tempCliques = 0;
    int i = 0;

    if(investimento<0)
    {
        investimento = PegarValor(investimento);
    }

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
    
    printf("Visualicao maxima = %f\n" , vTotal);
    return 0;
}
 
float PegarValor(float inv)
{
    printf("Quantos reais vao ser investidos?\n");
    scanf("%f" , &inv);
    return inv;
    
}