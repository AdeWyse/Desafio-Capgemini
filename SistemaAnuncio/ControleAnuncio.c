/*
 Desenvolvedora :  Adeline Rodrigues Cruz Wyse Guimarães
 Data inicio do projeto: 28/06/2021
 Data inicio ControleAnuncio.c: 30/06/2021
 Data fim projeto: 04/06/2021 
 Requisitos: 
    -Ser capaz de acessar os arquivos RegistroAnuncio.txt e RegistroRelatorio.txt e encher dois vetores dos tipos anuncio[] e relatorio[] respectivamente.
    -Mostrar um menu de interação com o usuario com as seguintes opções:
        -Cadastar Anuncio:
            nome do anuncio
            cliente
            data de inicio
            data de termino
            investimento por dia
        -Mostrar uma lista de todos os anuncios
        -Pesquisa por tempo, divida em pesquisa por periodo, data inicial, data final ou data inicial e data final ao mesmo tempo
        -Pesquisa por nome do cliente. (A pesquisa é "Case sensitive" e só mostra resultado positivo se o que for digitado for igual ao que esta armazenado)
        -Pesquisa por tempo e por cliente ao mesmo tempo.(Segue as mesmas orbsevações das pesquisas individuais)
    -Calcular os valores pedidos:(usando o script CalculadoraSistema.c)
        valor total investido
        quantidade maxima de visualizacoes
        quantidade maxima de cliques
        quantidade maxima de compartilhamentos
    -Apresentar o relatorio desses calculos
    -Armazenar os dados de anuncio cadastrados e relatorios processados nos arquivos RegistroAnuncio.txt e RegistroRelatorio.txt respectivamente

    Segunda parte do desafio de programação https://www.proway.com.br/academiacapmulheresdesafio.

   O script abre os arquivos e enche um vetor anuncio e um vetor relatorio com os dados apropriados. 
   Se o script nao conseguir abrir os arquivos mostra uma mensagem de erro.
   Depois e mostrado um menu para interacao com o usuario com 5 opcoes:
    Entrar novo anuncio:
        Pega a entrada de dados do usuario e ja processa os dados. Tambem ja faz o armazenamento dos dados de entrada e de saida nos arquivos.
    Mostrar relatorio de todos os anuncios:
        Mostra um relatorio de todos os anuncios
    Pesquisa por tempo:
        Pesquisa relatorios com o tempo escolhido/entrado pelo usuario
    Pesquisa Cliente:
        Pesquisa relatorios basedo no nome do cliente
    Pesquisa Cliente e Tempo:
        Primeiro faz uma pesquisa de cliente e usando os relatorios encontrados faz uma pesquisa por tempo


*/

#include <stdio.h>
#include <string.h>
#include "CalculadoraSistema.c"



typedef struct data// struct para manipulacao de datas
{  
    int dia;
    int mes;
    int ano;
}data; 

const char* anuncioFormatO =  "%s, %s, %d, %d, %d, %d, %d, %d, %f \n"; // Nome Anuncio, Nome Cliente, Data inicio.Dia, Data Inicio.Mes, Data Inicio.Ano, Investimento por dia -  formatacao para imprimir dados do tipo anuncio   
const char* anuncioFormatI =  "%[^,], %[^,], %d, %d, %d, %d, %d, %d, %f";//Nome Anuncio, Nome Cliente, Data inicio.Dia, Data Inicio.Mes, Data Inicio.Ano, Investimento por dia -  formatacao para ler dados do tipo anuncio
typedef struct anuncio// struct para a manipulacao dos anuncios
{
    char nome[50];
    char cliente[50];
    data dataInicio;
    data dataFim;
    float investimentoDia;
}anuncio; // struct para a manipulação dos anuncios

const char* relatorioFormatO =  "%s, %s, %d, %d, %d, %d, %d, %d, %f, %d, %f, %f, %f, %f \n";//Nome Anuncio, Nome Cliente, Data inicio.Dia, Data Inicio.Mes, Data Inicio.Ano, Total investido, Periodo de duracao do Anuncio, Total investido, Max Visualizacoes, Max Compartilhamentos, Max Cliques -  formatacao para imprimir dados do tipo relatorio
const char* relatorioFormatI =  "%[^,], %[^,],%d, %d, %d, %d, %d, %d, %f, %d, %f, %f, %f, %f";//Nome Anuncio, Nome Cliente, Data inicio.Dia, Data Inicio.Mes, Data Inicio.Ano, Total investido, Periodo de duracao do Anuncio, Total investido, Max Visualizacoes, Max Compartilhamentos, Max Cliques - formatacao para ler dados do tipo relatorio
typedef struct relatorio// struct para a manipulacao dos relatorios
{
    struct anuncio entrada;
    int periodo; // periodo de duração de um anuncio, usado em pesquisas
    float totalInvestido;
    float maxVisualizacoes;
    float maxCompartilhamentos;
    float maxCiques;
    
}relatorio;


int inicioDias = 0, fimDias = 0; // usado em calculos de periodo


anuncio Entrada(anuncio, int, FILE *); // pega o input do usuario e ja registra no arquivo RegistroAnuncio.txt
relatorio Processamento(anuncio, int, FILE * , relatorio); // processa o anuncio em um relatorio e ja registra no arquivo RegistroRelatorio.txt
void ImprimirRelatorio(relatorio); // imprime o relatorio
void PesquisarCliente(char[], relatorio[], int); // pesquisa de relatorio baseado no nome de cliente
void PesquisarData(relatorio[], int);// pesquisa de relatorio baseado no periodo/data unica/data final e inicial
void PesquisarClienteData(char[], relatorio[], int); // adaptacao de PesquisarCliente() para fazer uma pesquisa de data no fim
int ValidarDataInicio(data); // valida data do inicio, baseado em meses sempre com 30 dias
int ValidarDataFim(data, data);//valida a data final, baseado em meses sempre com 30 dias e ser posterior a data de inicio do anuncio


int main()
{
    FILE *registroAnuncio;
    FILE *registroRelatorio;
    //abre os arquivos que contem as informacoes sobre os anuncios e relatirios, se der algum problema mostra qual arquivo nao abriu 
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

    anuncio anuncio[1000]; // vetor para armazenamento dos anuncios
    relatorio relatorio[1000];// vetor para armazenamento dos anuncios
    
    char pesquisaCliente[50], // usado em pesquisa
    // variaveis para auxilio de pegar os dados dos arquivos
     bufferA[200],
      bufferR[200];

    int menu = 5, 
        indexAnuncio = 0, // variavel que guarda o numero de anuncios ja cadastrados
        indexRelatorio = 0, // variavel que guarda o numero de relatorios ja cadastrados
        numAnuncios = 0,
        i = 0,
        j = 0, 
        eof = 0; // variavel para checar se end of file
    
    //Pega os dados do RegistroAnuncio.txt e armazena no anuncio[]
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
    //Pega os dados do RegistroRelatorio.txt e armazena no registro[]
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
            printf("index %d\n", indexRelatorio);
        }
    }
    do//menu para interaçaoo com o usuario
    {
        printf("O que voce deseja fazer?\n");
        printf("Cadastrar novo anuncio - 1\n");
        printf("Relatorio de todos os anuncios - 2\n");
        printf("Encontrar relatorio por tempo - 3\n");
        printf("Encontar relatorio por cliente - 4\n");
        printf("Encontar relatorio por cliente e data - 5\n");
        printf("Sair - 0\n");
        
        scanf("%d", &menu);

        printf("\n");

        switch (menu)
            {
            case 1: /*pergunta quantos anuncios vao ser cadastrados, chama as funcoes de entrada, processamento e imprimir e atualiza arquivos*/
                printf("Quantos anuncios voce quer cadastrar?\n");
                scanf("%d", &numAnuncios);
                
                for(i = 0; i < numAnuncios; i++)
                {   
                    indexAnuncio++;
                    anuncio[indexAnuncio] = Entrada(anuncio[indexAnuncio], i, registroAnuncio);
                    indexRelatorio++;
                    relatorio[indexRelatorio] = Processamento(anuncio[indexAnuncio], i, registroRelatorio, relatorio[indexRelatorio]);
                    
                    ImprimirRelatorio(relatorio[indexRelatorio]);
                    investimento = 0;
                    vTotal = 0;
                    totalCompartilhamentos = 0;
                    totalCliques = 0;
                }
                
                fcloseall;// fecha e abre de novo os arquivos para atualizar a lista
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
                break;
            case 2:
                for(j = 0; j < indexRelatorio; j++)
                {
                    ImprimirRelatorio(relatorio[j]);
                }
                break;
            case 3: 
                PesquisarData(relatorio, indexRelatorio);
            break;
            case 4:
                
                printf("Digite o nome do cliente: ");
                getchar();
                gets(pesquisaCliente);
                printf("indexR %d\n", indexRelatorio);
                PesquisarCliente(pesquisaCliente, relatorio, indexRelatorio);
               
                break;
            case 5:
                printf("Digite o nome do cliente: ");
                getchar();
                gets(pesquisaCliente);
                PesquisarClienteData(pesquisaCliente, relatorio, j);
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
    do //Pega uma data valida para a data inicial
    {
        
        printf("Digite de inicio do anuncio:\n");
        printf("    Dia: ");
        scanf("%d", &input.dataInicio.dia);
        printf("    Mes: ");
        scanf("%d", &input.dataInicio.mes);
        printf("    Ano: ");
        scanf("%d", &input.dataInicio.ano);
    }while(ValidarDataInicio(input.dataInicio) == 0);

     do//Pega uma data valida para a data final
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
    //Muda as variaveis globais necessarias antes de chamar Calcular()
    output.periodo = fimDias - inicioDias;
    investimento = input.investimentoDia * output.periodo;
    Calcular();
    //Armazena os dados usando as variaveis globais
    output.totalInvestido = investimento;
    output.entrada = input;
    output.maxCiques = totalCliques;
    output.maxCompartilhamentos = totalCompartilhamentos;
    output.maxVisualizacoes = vTotal;
    //Ja armazena no arquivo apropriado
    fprintf(registroRelatorio, relatorioFormatO,output.entrada.nome,output.entrada.cliente,output.entrada.dataInicio.dia,output.entrada.dataInicio.mes,output.entrada.dataInicio.ano,output.entrada.dataFim.dia,output.entrada.dataFim.mes,output.entrada.dataFim.ano,output.entrada.investimentoDia,
                output.periodo,output.maxCiques, output.maxCompartilhamentos, output.maxVisualizacoes, output.totalInvestido);
    
    return output;

}

void ImprimirRelatorio(relatorio relatorio)
{
    
    printf("\n");
    printf("Nome do anuncio: %s\n", relatorio.entrada.nome);
    printf("Cliente: %s\n", relatorio.entrada.cliente);
    printf("Valor total investido: %0.2f\n", relatorio.totalInvestido);
    printf("Quantidade maxima de visualizacoes: %0.2f\n", relatorio.maxVisualizacoes);
    printf("Quantidade maxima de cliques: %0.2f\n", relatorio.maxCiques);
    printf("Quantidade maxima de compartilhamentos: %0.2f\n", relatorio.maxCompartilhamentos);
    printf("\n");


    
}

void PesquisarCliente (char busca[] , relatorio pesquisado[], int index)
{  
    printf("index %d\n", index);
    int isEqual =1,  count = 0,  i=0;
    relatorio temp[100];
    printf("%s\n", pesquisado[i].entrada.cliente);
    // salva os relatorios com resultato positivo em um vetor temporario e dois imprime o vetor
    for(i = 0; i <= index; i++)
    {  
        isEqual = strcmp (busca , pesquisado[i].entrada.cliente);
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
void PesquisarClienteData (char busca[] , relatorio pesquisado[], int index)
{  
    
    int isEqual =1,  count = 0,  i=0;
    relatorio temp[100];
    // salva os relatorios com resultato positivo em um vetos temporario e depois chama a PesquisarData()
    for(i = 0; i <= index; i++)
    {   isEqual = strcmp (busca , pesquisado[i].entrada.cliente);
       if( isEqual == 0)
       {
           temp[count] = pesquisado[i];
           count++;
       }
    }
    PesquisarData(temp, count);
}

void PesquisarData(relatorio relatorio[], int indexRelatorio)
{
     int naoEncontrado = 0,
        menuTempo = 0,// variavel que controla a pesquisa por tempo
        pesquisaPeriodo = 0,// variaveis para a pesquisa por periodo
        j = 0; 
     data pesquisaComeco, pesquisaFim; // variaveis para a pesquisa por data

                printf("Periodo em dias - 1\n");
                printf("Periodo por data inicial - 2\n");
                printf("Periodo por data final - 3\n");
                printf("Periodo pelas datas inicial e final - 4\n");
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
                           naoEncontrado++;
                       }
                    }
                    if(naoEncontrado == 0)
                    {
                           printf("Anuncio nao encontrado\n\n");
                           naoEncontrado = 0;
                    }
                    break;
                case 2:
                    
                    do //Pega uma data valida para a data inicial
                    {
                        printf("Digite de inicio do anuncio:\n");
                        printf("    Dia: ");
                        scanf("%d", &pesquisaComeco.dia);
                        printf("    Mes: ");
                        scanf("%d", &pesquisaComeco.mes);
                        printf("    Ano: ");
                        scanf("%d", &pesquisaComeco.ano);
                    }while(ValidarDataInicio(pesquisaComeco) == 0);

                    for(j = 0; j < indexRelatorio; j++)
                    {
                        if(relatorio[j].entrada.dataInicio.dia == pesquisaComeco.dia && relatorio[j].entrada.dataInicio.mes == pesquisaComeco.mes && relatorio[j].entrada.dataInicio.ano == pesquisaComeco.ano)
                        {
                            ImprimirRelatorio(relatorio[j]);
                            naoEncontrado++;
                       }
                    }
                    if(naoEncontrado == 0)
                    {
                           printf("Anuncio nao encontrado\n\n");
                           naoEncontrado = 0;
                    }
                    break;
                case 3:
                     do//Pega uma data valida para a data final
                    {
                        printf("Digite a data do fim do anuncio:\n");
                        printf("    Dia: ");
                        scanf("%d", &pesquisaFim.dia);
                        printf("    Mes: ");
                        scanf("%d", &pesquisaFim.mes);
                        printf("    Ano: ");
                        scanf("%d", &pesquisaFim.ano);
                    }while(ValidarDataInicio(pesquisaFim) == 0);

                    
                    for(j = 0; j < indexRelatorio; j++)
                    {
                       if(relatorio[j].entrada.dataFim.dia == pesquisaFim.dia && relatorio[j].entrada.dataFim.mes == pesquisaFim.mes && relatorio[j].entrada.dataFim.ano == pesquisaFim.ano)
                         {
                             ImprimirRelatorio(relatorio[j]);
                             naoEncontrado++;
                         }    
                    }
                    if(naoEncontrado == 0)
                    {
                           printf("Anuncio nao encontrado\n\n");
                           naoEncontrado = 0;
                    }
                    break;
                case 4:
                    do //Pega uma data valida para a data inicial
                    {
                        printf("Digite de inicio do anuncio:\n");
                        printf("    Dia: ");
                        scanf("%d", &pesquisaComeco.dia);
                        printf("    Mes: ");
                        scanf("%d", &pesquisaComeco.mes);
                        printf("    Ano: ");
                        scanf("%d", &pesquisaComeco.ano);
                    }while(ValidarDataInicio(pesquisaComeco) == 0);

                     do//Pega uma data valida para a data final
                    {
                        printf("Digite a data do fim do anuncio:\n");
                        printf("    Dia: ");
                        scanf("%d", &pesquisaFim.dia);
                        printf("    Mes: ");
                        scanf("%d", &pesquisaFim.mes);
                        printf("    Ano: ");
                        scanf("%d", &pesquisaFim.ano);
                    }while(ValidarDataFim(pesquisaComeco, pesquisaFim) == 0);

                    
                    for(j = 0; j < indexRelatorio; j++)
                    {
                        if(relatorio[j].entrada.dataInicio.dia == pesquisaComeco.dia && relatorio[j].entrada.dataInicio.mes == pesquisaComeco.mes && relatorio[j].entrada.dataInicio.ano == pesquisaComeco.ano &&
                        relatorio[j].entrada.dataFim.dia == pesquisaFim.dia && relatorio[j].entrada.dataFim.mes == pesquisaFim.mes && relatorio[j].entrada.dataFim.ano == pesquisaFim.ano)
                        {
                            ImprimirRelatorio(relatorio[j]);
                            naoEncontrado++;
                        }   
                    } 
                    if(naoEncontrado == 0)
                    {
                           printf("Anuncio nao encontrado\n\n");
                    }
                    break;
                default:
                    break;
                }
}

int ValidarDataInicio(data data)// Valida a data entrada, baseado em meses sempre com 30 dias
{
    int diaV=0, mesV=0, anoV=0, isValid = 0;
    if( data.dia >= 1 && data.dia <= 30)
    {
        diaV = 1;
    }else {
        printf("Dia invalido.\n");
    }
    if( data.mes >=1 && data.mes <= 12)
    {
        mesV = 1;
    }else {
        printf("Mes invalido.\n");
    }
    if( data.ano >= 1900 && data.ano <=2100)
    {
        anoV = 1;
    }else {
        printf("Ano invalido.\n");
    }
    if(diaV == 1 && mesV == 1 && anoV == 1)
    {
        isValid = 1;
    }
    return isValid;
}

int ValidarDataFim(data inicio, data fim)// Valida a data entrada, baseado em meses sempre com 30 dias e ser posterior a data de inicio do anuncio
{
    int diaV = 0, mesV = 0, anoV = 0, isValid = 0, dataV = 0;
    if( fim.dia >= 1 && fim.dia <= 30)
    {
        diaV = 1;
    }else {
        printf("Dia invalido.\n");
    }
    if( fim.mes >=1 && fim.mes <= 12)
    {
        mesV = 1;
    }else {
        printf("Mes invalido.\n");
    }
    if( fim.ano >= 1900 && fim.ano <=2100)
    {
        anoV = 1;
    }else {
        printf("Ano invalido.\n");
    }

    inicioDias = (inicio.ano*365) + inicio.dia + (inicio.mes*30);
    fimDias = (fim.ano*365) + fim.dia + (fim.mes*30);
    if(inicioDias < fimDias)
    {
        dataV = 1;
    }else{
        printf("Periodo invalido.\n");
    }
    if(diaV == 1 && mesV == 1 && anoV == 1 && dataV == 1)
    {
        isValid = 1;
    }
    return isValid;
}
