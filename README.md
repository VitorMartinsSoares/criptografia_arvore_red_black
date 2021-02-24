# Criptografia em arvore vermelho-preto <h1>
## Resumo: <h2>
Este é um projeto que visa utilizar o uso de uma Red-Black Tree (Árvore vermelho-preto) para a criptografia de senhas e mostrar o seu funcionamento em um possível login. É um projeto criado para aplicar o estudo e o entendimento de arvores em Algoritmo e Estrutura de Dados 2, em específico a Árvore vermelho-preto.

## Objetivo: <h2>
O objetivo do projeto é utilizar em uma aplicação a arvore vermelho-preto, esta arvore é uma arvore binária que armazena também a cor do nó, podendo ser vermelha ou preta, neste projeto  foi utilizado true pra vermelho e false para preto, esta arvore de busca é aproximadamente balanceada. A ideia foi usar deste balanceamento para estabelecer uma base de palavras dentro da arvore e apartir disto criptografar senhas, levando em consideração a quantidade de pais que a folha tem, quantas vezes o valor enviado foi maior que o comparado e quantas vezes o 
valor enviado foi menor que o comparado. Sendo assim eu teria o valor criptografado e sem a criptografia, porém não é possivel eu ter o valor sem a criptografia apartir do criptografado, resumindo, não é possível descriptografar, apenas comparar valores criptografados, se a comparação for igual, é porque é o mesmo valor. Para a base de dados predefinida para a criação
da arvore foi um conjunto de 1197 palavras do dicionário brasileiro, esta base é fixa e nunca alterada, para que não possa ocorrer o balanceamento da arvore e modificar as criptografias.

## Execução: <h1>
Para executar foi usado o gcc com o comando "gcc arvore.c -o prog", este programa não tera o resultado esperado caso haja caracteres especiais e letras maisculas seram redefinidas para minusculas para padronizar. É necessário as os dois arquivos txt: palavras.txt e banco.txt, palavras é de onde sera retirado as palavras para popular a arvore, o banco é para armazenar usuario e senha, sendo as senhas criptografadas, existe duas opções ao iniciar o jogo, digite 1 para criar um novo usuario, 2 para realizar login, para teste pré definido use vitor teste no
realizar login.

### Arvore Vermelho-preto: <h3>
A arvore vermelho-preto tem algumas propriedades especificas, e entre elas são:
1. Se o filho de um nó não existir, o valor é NULL
2. Todo nó ou é vermelho ou é preto.
3. A raiz é sempre preta.
4. Toda folha NULL é preta.
5. Se um nó é vermelho, então os seus filhos são pretos.
6. Sempre existe o mesmo número de nós pretos para cada caminho de um nó até seus descendentes.

A complexidade desta arvore é um pouco alta, porém o seu pior-caso de tempo de execução é satisfatorio, ja que tem um bom pior caso, O(log N) em que n é o numero total de elementos. Esta arvore é usada em TreeSet, TreeMap, Hashmap das biblioteca Java, Completely Fair Scheduler no kernel do Linux, mmap e munmap para mapeamento de arquivo/memória no linux, pesquisas de intervalo geométrico, agrupamento de k-means e mineração de texto.

### Simulação: <h3>
Abaixo esta o inicio deste programa, como a arvore é manipulada nos 10 primeiros elementos:

        fel(P)  --->    fel(P)          --->    fel(P)
                            \                       \
                            sob(V)                  sob(V)
                                                            \
                                                            vil(V)

         sob(P)              --->                sob(P)
        /      \                                /      \
    fel(V)        vil(V)                    fel(P)        vil(P)
                                            /
                                      de(V)

                    sob(P)          --->                sob(P)
                  /        \                          /        \
            fel(P)          vil(P)              fel(V)          vil(P)
           /      \                            /      \
      de(V)         paz(V)                de(P)        paz(P)
                                                            \
                                                              ser(V)

                    sob(P)          --->                  sob(P)
                   /      \                            /          \
             fel(V)        vil(P)                fel(V)               vil(P)
            /      \                            /      \              /
       de(P)        paz(P)                 de(P)        paz(P)  ver(V)
                   /      \                            /      \   
            mal(V)          ser(V)              mal(V)          ser(V)   
            
                    sob(P)                        
                /            \                  
          fel(V)                  ver(P)         
         /       \               /        \       
    de(P)        paz(P)    ter(V)          vil(V)
                /      \                        
            mal(V)       ser(V)      

                               sob(P)                        
                           /            \                  
                    fel(V)                    ver(P)         
                /          \               /         \       
            de(P)             paz(P)   ter(V)          vil(V)
                \           /       \                        
                ego(V) mal(V)        ser(V)                  

## Conclusão <h2>
Existe melhores maneiras de se criar uma criptografia, pois com esta arvore fica impossivel de armazenar as novas senhas na arvore porque a criptografia mudaria caso a arvore precisasse ser balanceada, e isso gera um limite e um padrão, além de que duas senha diferentes de mesmo tamanho, existe uma chance muito pequena, quase nula, de repetir. A arvore tem melhores aplicações, porém foi uma experiência extremamente satisfatoria, é possivel ver que todas as criptografias tem um valor de complexidade alto para ser eficiente. O código deste projeto contém algumas explicações e direção do que foi feito como comentários.O tempo de execução testado nesta aplicação foi tão pequeno que foi muito dificil de perceber ate mesmo calculando e mostrando na tela, o que mostra também a efetividade do código.

## Referencias <h2>
<a href="https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/0262033844/ref=sr_1_1?dchild=1&keywords=Introduction+to+Algorithms&qid=1613858932&sr=8-1">Thomas H. Cormen: Introduction to Algorithms, 3rd Edition (The MIT Press)</a><br/>
<a href="https://www.codesdope.com/course/data-structures-red-black-trees/">CodesDope: Red-Black Trees</a><br/>
<a href="https://www.dicio.com.br/lista-de-palavras/">Dicio: lista de palavras</a><br/>
<a href="https://www.baeldung.com/cs/red-black-trees/">Baeldung: Introduction to Red-Black Trees </a><br/>
<a href="https://www.cs.usfca.edu/~galles/visualization/RedBlack.html">Red-Black tree algorithm Visualizations</a><br/>