Super Trunfo de Países em C
Descrição

Este programa em C permite cadastrar informações de duas cartas do jogo Super Trunfo com o tema "Países", focando em dados de cidades. Para cada carta, o usuário poderá inserir o estado, código, nome da cidade, população, PIB, área e número de pontos turísticos. Além disso, o programa calcula a densidade populacional e o PIB per capita de cada cidade. Uma funcionalidade avançada implementada nesta versão é o cálculo do "Super Poder" de cada carta, que é a soma de todos os atributos numéricos, incluindo o inverso da densidade populacional. Finalmente, o programa compara as duas cartas atributo por atributo, determinando qual carta vence em cada critério.
Funcionalidades

    Cadastro de Cartas: Permite inserir dados para duas cartas, incluindo estado, código, nome da cidade, população (armazenada como unsigned long int), PIB, área e número de pontos turísticos.
    Cálculo da Densidade Populacional: Calcula a densidade populacional de cada cidade (Populac¸​a˜o/Aˊrea).
    Cálculo do PIB per Capita: Calcula o PIB per capita de cada cidade (PIB/Populac¸​a˜o).
    Cálculo do Super Poder: Calcula o "Super Poder" de cada carta somando todos os atributos numéricos (população, área, PIB, número de pontos turísticos, PIB per capita e o inverso da densidade populacional).
    Comparação de Cartas: Compara as duas cartas em cada atributo (exceto estado, código e nome), incluindo o Super Poder. Para a densidade populacional, a menor vence; para os demais, a maior vence.
    Exibição dos Resultados: Apresenta o resultado de cada comparação, indicando qual carta venceu para cada atributo.

Como Usar

    Abra o Visual Studio 2022.
    Crie um novo projeto do tipo "Aplicativo de Console (.NET Framework)" ou "Aplicativo de Console". Escolha a linguagem C.
    Copie e cole o código fonte (.c) que você irá gerar para o arquivo main.c (ou outro nome de sua preferência).
    Compile e execute o programa.
    O programa solicitará que você insira os dados para a Carta 1 e, em seguida, para a Carta 2, seguindo as instruções na tela.
    Após a entrada dos dados, o programa exibirá os cálculos da densidade populacional, PIB per capita, Super Poder e os resultados das comparações entre as duas cartas.

Observações

    A população é armazenada como unsigned long int para suportar números maiores.
    O "Super Poder" é calculado como um float.
    Ao comparar a densidade populacional, a carta com o menor valor é considerada vencedora.
    Para os demais atributos e o Super Poder, a carta com o maior valor é a vencedora.
