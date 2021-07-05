# Desafio-Capgemini
Repositório para a resolução do Desafio de Programação parte do processo de seleção da Academia Capgemini.
https://www.proway.com.br/academiacapmulheresdesafio

A resposta da 1 parte está solta como "calculadora.c" na pasta raiz do reporitório. 
A resposta da 2 parte esta dentro da pasta SistemaAnuncio.

É uma aplicação para console com um menu que leva o usuario para cadastrar um novo anúncio, pesquisar um anuncio por cliente ou periodo( dias ou entre 2 datas), e mostrar um relatório de todos os anúncios cadastrados(mais informações mais especificas dentro de cada scripts).

### Instruções para o sistema funcionar:
  - Ter certeza que os arquivos CalculadoraSistema.c, RegistroAnuncio.txt e RegistroRelatorio.txt estão na mesma pasta que o script e o executavel ControleAnuncio.
  - Para executar use ControleAnuncio.c
  - Obsevações: 
    Legenda para leitura dos arquivos:
     - RegistroAnuncio.txt: Nome Anuncio, Nome Cliente, Data inicio.Dia, Data Inicio.Mes, Data Inicio.Ano, Investimento por dia
     - RegistroRelatorio.txt: Nome Anuncio, Nome Cliente, Data inicio.Dia, Data Inicio.Mes, Data Inicio.Ano, Investimento por dia, Periodo de duracao do Anuncio, Total investido, Max Visualizacoes, Max Compartilhamentos, Max Cliques
    - As datas são baseadas em meses com 30 dias sem distinção
    - Pesquisas por nome de Cliente são "Case sensitive", apenas mostram resultado se o nome da pesquisa for exatamente igual ao armazenado
    - Não tem nenhum dado armazenado nos arquivos
    - Se estiver cadastrando 1 ou mais anuncio e fechar o console o RegistroRelatorio vai ficar sem as informações do anuncio que foi interrompido
    - Se a lista não estiver atualizando (ex: mostrando informações vazias ou faltando informações), fechar e abrir o .exe novamente

      

### Agradecimento:

No começo eu tive bastante ideias de como desenvolver esse sistema. Algumas funcionaram, outras não. O importante é que eu sai um pouco da minha zona de conforto e tentei coisas novas. Por isso eu queria agradecer a Capgemini e a Proway pela oportunidade de participar desse desafio. Eu aprendi bastante com ele.


