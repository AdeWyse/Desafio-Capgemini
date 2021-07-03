#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "CalculadoraSistema.c"

typedef struct data{
    int dia;
    int mes;
    int ano;
}data;

typedef struct 
{
    char nome[50];
    char cliente[50];
    data dataInicio;
    data dataFim;
    float investimentoDia;
}anuncio;

typedef struct 
{
    anuncio entrada;
    float totalInvestido;
    float maxVisualizacoes;
    float maxCompartilhamentos;
    float maxCiques;
    
}relatorio;

int inicioDias = 0, fimDias = 0;

anuncio Entrada(anuncio);
int ValidarDataInicio(data); // valida data do inicio
int ValidarDataFim(data, data);// valida data do fim, checando se acontece depois da data inicial


int main()
{
    setlocale(LC_ALL,"portuguese-brazilian");
    anuncio anuncio[1000];
    relatorio relatorioAnuncio[1000]; 
    data pesquisaComeco, pesquisaFim; // variaveis para a pesquisa por data
    char pesquisaCliente[50];
    int menu = 0,
      menuTempo = 0, // variavel que controla a pesquisa por tempo
      pesquisaPeriodo = 0,
      indexAnuncio = 0, // variavel que guarda o numero de anuncios já cadastrados
      indexRelatorio = 0, // variavel que guarda o numero de relatorios já cadastrados
     numDias = 0,
     numAnuncios = 0,
     i = 0;

     // fazer load do arquivo e encher o tanto que precisar do anuncio
    do//menu para interação do usuario
    {
        printf("O que você deseja fazer?\n");
        printf("Cadastrar novo anúncio - 1\n");
        printf("Relatório de todos os anúncios - 2\n");
         printf("Encontrar relatório por tempo - 3\n");
        printf("Encontar relatório por cliente - 4\n");
        
        scanf("%d", menu);

        switch (menu)
    {
    case 1:
        printf("Quantos anúncios você quer cadastrar?\n");
        scanf("%d", &numAnuncios);
        for(i = 1; i <= numAnuncios; i++)
        {
            Entrada(anuncio[indexAnuncio+i]);
            //já ir gravando no arquivo
        }
        break;
    case 2:
        //loop para imprimir o vetor relatorioAnuncio
        break;
    case 3:
        printf("Periodo em dias - 1\n");
        printf("Periodo em datas - 2\n");
        scanf("%d", menuTempo);
        switch (menuTempo)
        {
        case 1:
            printf("Quantos dias durou o anúncio? ");
            scanf("%d", pesquisaPeriodo);
            //loop procurar no relatorioAnuncio quais relatorios tem essa duração
            break;
        case 2:
            do //Pega uma data válida para a data inicial
            {
                printf("Digite de inicio do anúncio:\n");
                printf("    Dia: ");
                scanf("%d", &pesquisaComeco.dia);
                printf("    Mês: ");
                scanf("%d", &pesquisaComeco.mes);
                printf("    Ano: ");
                scanf("%d", &pesquisaComeco.ano);
            }while(ValidarDataInicio(pesquisaComeco) == 0);

            do//Pega uma data válida para a data final
            {
                printf("Digite a data do fim do anúncio:\n");
                printf("    Dia: ");
                scanf("%d", &pesquisaFim.dia);
                printf("    Mês: ");
                scanf("%d", &pesquisaFim.mes);
                printf("    Ano: ");
                scanf("%d", &pesquisaFim.ano);
            }while(ValidarDataFim(pesquisaComeco, pesquisaFim) == 0);
            //loop procurar relatório com essas datas
            break;
        
        default:
            break;
        }
    break;
    case 4:
        printf("Digite o nome do cliente: ");
        gets(pesquisaCliente);
        //loop procurara relatório com esse cliente

    
    default:
        break;
    }

    }while(menu == 0);

    
    


    
    
    anuncio[0] = Entrada(anuncio[0]);
    numDias = fimDias - inicioDias;
    investimento = anuncio[0].investimentoDia * numDias;
    Calcular();

    //multiplicar cada valor de resultado pelo numero de dias
    //criar função para encher o relatorio
    //criar funções para ler e registrar anuncios
    //transformar o codigo num jeito que fica repetindo (anuncio[] e loops);

    return 0;
}

anuncio Entrada(anuncio input)
{
    
    printf("Digite o nome do anúncio: ");
    gets(input.nome);
    printf("Digite o nome do cliente: ");
    gets(input.cliente);
    do //Pega uma data válida para a data inicial
    {
        printf("Digite de inicio do anúncio:\n");
        printf("    Dia: ");
        scanf("%d", &input.dataInicio.dia);
        printf("    Mês: ");
        scanf("%d", &input.dataInicio.mes);
        printf("    Ano: ");
        scanf("%d", &input.dataInicio.ano);
    }while(ValidarDataInicio(input.dataInicio) == 0);

     do//Pega uma data válida para a data final
    {
        printf("Digite a data do fim do anúncio:\n");
        printf("    Dia: ");
        scanf("%d", &input.dataFim.dia);
        printf("    Mês: ");
        scanf("%d", &input.dataFim.mes);
        printf("    Ano: ");
        scanf("%d", &input.dataFim.ano);
    }while(ValidarDataFim(input.dataInicio, input.dataFim) == 0);
    
    printf("Digite o investimento em R$ por dia: ");
    scanf("%f", &input.investimentoDia);
    getchar();
    return input;
}

int ValidarDataInicio(data data)
{
    int diaV=0, mesV=0, anoV=0, isValid = 0;
    if( data.dia >= 1 && data.dia <= 30)
    {
        diaV = 1;
    }else {
        printf("Dia inválido.\n");
    }
    if( data.mes >=1 && data.mes <= 12)
    {
        mesV = 1;
    }else {
        printf("Mês inválido.\n");
    }
    if( data.ano >= 1900 && data.ano <=2100)
    {
        anoV = 1;
    }else {
        printf("Ano inválido.\n");
    }
    if(diaV == 1 && mesV == 1 && anoV == 1)
    {
        isValid = 1;
    }
    return isValid;
}

int ValidarDataFim(data inicio, data fim)
{
    int diaV = 0, mesV = 0, anoV = 0, isValid = 0, dataV = 0;
    if( fim.dia >= 1 && fim.dia <= 30)
    {
        diaV = 1;
    }else {
        printf("Dia inválido.\n");
    }
    if( fim.mes >=1 && fim.mes <= 12)
    {
        mesV = 1;
    }else {
        printf("Mês inválido.\n");
    }
    if( fim.ano >= 1900 && fim.ano <=2100)
    {
        anoV = 1;
    }else {
        printf("Ano inválido.\n");
    }

    inicioDias = (inicio.ano*365) + inicio.dia + (inicio.mes*30);
    fimDias = (fim.ano*365) + fim.dia + (fim.mes*30);
    if(inicioDias < fimDias)
    {
        dataV = 1;
    }else{
        printf("Periodo inválido.\n");
    }
    if(diaV == 1 && mesV == 1 && anoV == 1 && dataV == 1)
    {
        isValid = 1;
    }
    return isValid;
}