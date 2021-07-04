#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "CalculadoraSistema.c"



typedef struct data{
    int dia;
    int mes;
    int ano;
}data;

const char* anuncioFormatO =  "%s, %s, %d, %d, %d, %d, %d, %d, %f \n";
const char* anuncioFormatI =  "%[^,], %[^,], %d, %d, %d, %d, %d, %d, %f";
typedef struct anuncio
{
    char nome[50];
    char cliente[50];
    data dataInicio;
    data dataFim;
    float investimentoDia;
}anuncio;

const char* relatorioFormatO =  "%s, %s, %d, %d, %d, %d, %d, %d, %f, %d, %f, %f, %f, %f \n";
const char* relatorioFormatI =  "%[^,], %[^,],%d, %d, %d, %d, %d, %d, %f, %d, %f, %f, %f, %f";
typedef struct relatorio
{
    struct anuncio entrada;
    int periodo;
    float totalInvestido;
    float maxVisualizacoes;
    float maxCompartilhamentos;
    float maxCiques;
    
}relatorio;


int inicioDias = 0, fimDias = 0;


anuncio Entrada(anuncio, int, FILE *); // pega o input do usuario
relatorio Processamento(anuncio, int, FILE * , relatorio); // processa o anuncio 
void ImprimirRelatorio(relatorio);
void PesquisarCliente(char[], relatorio[], int);
int ValidarDataInicio(data); // valida data do inicio
int ValidarDataFim(data, data);// valida data do fim, checando se acontece depois da data inicial


int main()
{
    FILE *registroAnuncio;
    FILE *registroRelatorio;
    //abre os arquivos que contem as informações sobre os anuncios e relatórios, se der algum problema mostra qual arquivo não abriu 
    registroAnuncio = fopen("RegistroAnuncio.txt", "a+");
    if(registroAnuncio == NULL)
    {
        printf("Erro abrindo arquivo RegistroAnuncio.txt\n");
    }
    registroRelatorio = fopen("RegistroRelatorio.txt", "a+");
    if(registroRelatorio == NULL)
    {
        printf("Erro abrindo arquivo RegistroRelatorio.txt\n");
    }

    anuncio anuncio[1000];
    relatorio relatorio[1000];
    data pesquisaComeco, pesquisaFim; // variaveis para a pesquisa por data
    char pesquisaCliente[50], bufferA[200], bufferR[200];

    int menu = 5, 
      menuTempo = 0, // variavel que controla a pesquisa por tempo
      pesquisaPeriodo = 0,
      indexAnuncio = 0, // variavel que guarda o numero de anuncios já cadastrados
      indexRelatorio = 0, // variavel que guarda o numero de relatorios já cadastrados
     numDias = 0,
     numAnuncios = 0,
     i = 0,
     j = 0, 
     eof = 0;
     


    
    if(fgets(bufferA, 200, registroAnuncio) != NULL)
    {
        while (eof != 1)
         {
             sscanf(bufferA, anuncioFormatI,&anuncio[indexAnuncio].nome,&anuncio[indexAnuncio].cliente,&anuncio[indexAnuncio].dataInicio.dia,&anuncio[indexAnuncio].dataInicio.mes,&anuncio[indexAnuncio].dataInicio.ano,&anuncio[indexAnuncio].dataFim.dia,&anuncio[indexAnuncio].dataFim.mes,&anuncio[indexAnuncio].dataFim.ano,&anuncio[indexAnuncio].investimentoDia);
        
        
             if(fgets(bufferA, 200, registroAnuncio) == NULL)
            {
                
                eof = 1;
            }
            
            
            indexAnuncio++;
        }
    }
    eof = 0;
    if(fgets(bufferR, 200, registroRelatorio) != NULL)
    {
        while (eof != 1)
         {
             sscanf(bufferR, relatorioFormatI,&relatorio[indexRelatorio].entrada.nome,&relatorio[indexRelatorio].entrada.cliente,&relatorio[indexRelatorio].entrada.dataInicio.dia,&relatorio[indexRelatorio].entrada.dataInicio.mes,&relatorio[indexRelatorio].entrada.dataInicio.ano,&relatorio[indexRelatorio].entrada.dataFim.dia,&relatorio[indexRelatorio].entrada.dataFim.mes,&relatorio[indexRelatorio].entrada.dataFim.ano,&relatorio[indexRelatorio].entrada.investimentoDia,
                &relatorio[indexRelatorio].periodo,&relatorio[indexRelatorio].maxCiques, &relatorio[indexRelatorio].maxCompartilhamentos, &relatorio[indexRelatorio].maxVisualizacoes, &relatorio[indexRelatorio].totalInvestido);
        
        
             if(fgets(bufferR, 200, registroRelatorio) == NULL)
            {
                
                eof = 1;
            }
            
            
            indexRelatorio++;
        }
    }
    
   
      

     
    do//menu para interação do usuario
    {
        printf("O que voce deseja fazer?\n");
        printf("Cadastrar novo anuncio - 1\n");
        printf("Relatorio de todos os anuncios - 2\n");
        printf("Encontrar relatorio por tempo - 3\n");
        printf("Encontar relatorio por cliente - 4\n");
        printf("Sair - 0\n");
        
        scanf("%d", &menu);

        switch (menu)
            {
            case 1:
                printf("Quantos anuncios voce quer cadastrar?\n");
                scanf("%d", &numAnuncios);
                for(i = 0; i < numAnuncios; i++)
                {
                    indexAnuncio++;
                    anuncio[indexAnuncio] = Entrada(anuncio[indexAnuncio], i, registroAnuncio);
                    indexRelatorio++;
                    relatorio[indexRelatorio] = Processamento(anuncio[indexAnuncio], i, registroRelatorio, relatorio[indexRelatorio]);
                    ImprimirRelatorio(relatorio[indexRelatorio]);
                }
                break;
            case 2:
                for(j = 0; j < indexRelatorio; j++)
                {
                    ImprimirRelatorio(relatorio[j]);
                }
                break;
            case 3:
                printf("Periodo em dias - 1\n");
                printf("Periodo em datas - 2\n");
                scanf("%d", &menuTempo);
                switch (menuTempo)
                {
                case 1:
                    printf("Quantos dias durou o anuncio? ");
                    scanf("%d", &pesquisaPeriodo);
                    for(j = 0; j < indexRelatorio; j++)
                    {
                       if(pesquisaPeriodo == relatorio[j].periodo)
                       {
                           ImprimirRelatorio(relatorio[j]);
                       }
                    }
                    break;
                case 2:
                    do //Pega uma data válida para a data inicial
                    {
                        printf("Digite de inicio do anuncio:\n");
                        printf("    Dia: ");
                        scanf("%d", &pesquisaComeco.dia);
                        printf("    Mes: ");
                        scanf("%d", &pesquisaComeco.mes);
                        printf("    Ano: ");
                        scanf("%d", &pesquisaComeco.ano);
                    }while(ValidarDataInicio(pesquisaComeco) == 0);

                    do//Pega uma data válida para a data final
                    {
                        printf("Digite a data do fim do anuncio:\n");
                        printf("    Dia: ");
                        scanf("%d", &pesquisaFim.dia);
                        printf("    Mes: ");
                        scanf("%d", &pesquisaFim.mes);
                        printf("    Ano: ");
                        scanf("%d", &pesquisaFim.ano);
                    }while(ValidarDataFim(pesquisaComeco, pesquisaFim) == 0);
                    pesquisaPeriodo = fimDias - inicioDias;
                    for(j = 0; j < indexRelatorio; j++)
                    {
                       if(pesquisaPeriodo == relatorio[j].periodo)
                       {
                           ImprimirRelatorio(relatorio[j]);
                       }
                    }
                    break;
                
                default:
                    break;
                }
            break;
            case 4:
                printf("Digite o nome do cliente: ");
                gets(pesquisaCliente);
                //loop procurara relatório com esse cliente
                break;
            case 0:
            
                break;

            
            default:
                break;
            }

    }while(menu!= 0);
     fcloseall;

    return 0;
}

anuncio Entrada(anuncio input, int i, FILE * registroAnuncio)
{
    getchar();
    printf("Cadastro %d \n", i+1);
    printf("Digite o nome do anuncio: ");
    gets(input.nome);
    printf("Digite o nome do cliente: ");
    gets(input.cliente);
    do //Pega uma data válida para a data inicial
    {
        
        printf("Digite de inicio do anuncio:\n");
        printf("    Dia: ");
        scanf("%d", &input.dataInicio.dia);
        printf("    Mes: ");
        scanf("%d", &input.dataInicio.mes);
        printf("    Ano: ");
        scanf("%d", &input.dataInicio.ano);
    }while(ValidarDataInicio(input.dataInicio) == 0);

     do//Pega uma data válida para a data final
    {
        printf("Digite a data do fim do anuncio:\n");
        printf("    Dia: ");
        scanf("%d", &input.dataFim.dia);
        printf("    Mes: ");
        scanf("%d", &input.dataFim.mes);
        printf("    Ano: ");
        scanf("%d", &input.dataFim.ano);
    }while(ValidarDataFim(input.dataInicio, input.dataFim) == 0);
    
    printf("Digite o investimento em R$ por dia: ");
    scanf("%f", &input.investimentoDia);
    fprintf(registroAnuncio, anuncioFormatO,input.nome,input.cliente,input.dataInicio.dia,input.dataInicio.mes,input.dataInicio.ano,input.dataFim.dia,input.dataFim.mes,input.dataFim.ano,input.investimentoDia);
    fseek(registroAnuncio, 0, SEEK_SET);


    
    return input;
}

relatorio Processamento(anuncio input, int i, FILE * registroRelatorio, relatorio output)
{
    output.periodo = fimDias - inicioDias;
    investimento = input.investimentoDia * output.periodo;
    Calcular();
    output.totalInvestido = investimento;
    output.entrada = input;
    output.maxCiques = totalCliques;
    output.maxCompartilhamentos = totalCompartilhamentos;
    output.maxVisualizacoes = vTotal;

     fprintf(registroRelatorio, relatorioFormatO,output.entrada.nome,output.entrada.cliente,output.entrada.dataInicio.dia,output.entrada.dataInicio.mes,output.entrada.dataInicio.ano,output.entrada.dataFim.dia,output.entrada.dataFim.mes,output.entrada.dataFim.ano,output.entrada.investimentoDia,
                output.periodo,output.maxCiques, output.maxCompartilhamentos, output.maxVisualizacoes, output.totalInvestido);

    
        
    return output;

}

void ImprimirRelatorio(relatorio relatorio)
{
    
    printf(" Nome do anuncio: %s\n", relatorio.entrada.nome);
    printf("Cliente: %s\n", relatorio.entrada.cliente);
    printf("Valor total investido: %0.2f\n", relatorio.totalInvestido);
    printf("Quantidade maxima de visualizaçoes: %0.2f\n", relatorio.maxVisualizacoes);
    printf("Quantidade maxima de cliques: %0.2f\n", relatorio.maxCiques);
    printf("Quantidade maxima de compartilhamentos: %0.2f\n", relatorio.maxCompartilhamentos);
    printf("\n");


    
}

void PesquisarCliente (char busca[] , relatorio pesquisado[], int index)
{  
    
    int isEqual =1,  count = 0,  i=0;
    relatorio temp[100];
    
    for(i = 0; i <= index; i++)
    {   isEqual = strcmp (busca , pesquisado[i].entrada.cliente);
       if( isEqual == 0)
       {
           
           temp[count] = pesquisado[i];
           count++;
       }
    }
    for(i = 0; i<count; i++)
    {
        ImprimirRelatorio(temp[i]);
    }
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
