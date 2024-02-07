# VehicleManagement_C

Objetivo:
<br>Este documento deve ser visto como uma referência para uma abordagem clássica de desenvolvimento de uma
solução de software para um problema de dimensão média. A essência deste projeto prende-se com o
desenvolvimento de uma solução de software que permita agilizar a gestão (registo, partilha, utilização) de meios
de mobilidade urbana num contexto de uma smart-city. A implementação da solução deverá considerar estruturas
de dados dinâmicas, armazenamento em ficheiro, modularização e apresentar uma estruturação e documentação
adequadas.
<br>
Regras:
<br>
Contemplando dois tipos de utilizadores, a saber, gestores e clientes registados, pretende-se considerar as
funcionalidades seguintes:
1. Agilizar o aluguer dos meios de mobilidade, disponibilizando: informação sobre os meios disponíveis (tipo,
carga da bateria, custo, etc); identificar a localização dos meios existentes através de geocódigo
(what3words.com); registar o pagamento através de um saldo recarregável associado ao cliente; entre outros;
2. Permitir aos responsáveis pela plataforma (gestores) a gestão dos respetivos meios de mobilidade permitindo
registar, alterar, cancelar, localizar e outros serviços;
3. Admitir somente clientes registados considerando o NIF, saldo, nome, morada, etc.;
4. Permitir aos gestores da plataforma a possibilidade de uma visão integrada permitindo operações como
consultas de históricos, estatísticas, validações, etc.;
<br>
Fase 1
<br>
1. Definição de uma estrutura de dados dinâmica (a validar previamente com o docente), para a representação
dos meios de mobilidade elétrica, clientes e gestores;
2. Armazenamento/leitura dos dados em ficheiro de texto (valores de simulação) e binários (preservar dados);
3. Inserção de novos dados (cliente/gestor/meio de mobilidade elétrica);
4. Remoção de determinados dados (cliente/gestor/meio de mobilidade elétrica);
5. Alteração de determinados dados (cliente/gestor/meio de mobilidade elétrica);
6. Registo do aluguer de um determinado meio de mobilidade elétrica;
7. Listagem dos meios de mobilidade elétrica por ordem decrescente de autonomia;
8. Listagem dos meios de mobilidade elétrica existentes numa localização com determinado geocódigo.
<br>
Fase 2
<br>
1. Definição de uma estrutura de dados dinâmica para representação da localização de um conjunto de
clientes e meios de mobilidade elétrica, recorrendo a um grafo;
2. Armazenamento/leitura dos dados em ficheiro de texto (valores de simulação) e binários (preservar dados).
Dado a localização de um cliente, listar os meios de mobilidade elétrica de um determinado tipo existentes
num determinado raio;
3. Calcular uma solução (adaptação do problema do caixeiro viajante) do trajeto com a menor distância a
percorrer, com recurso a um camião, para recolha de todos os meios de mobilidade elétrica com carga da
bateria abaixo de 50%. O ponto de partida e chegada é o mesmo. A capacidade de transporte do camião é
limitada e dependente dos tipos de meios de mobilidade transportados, pelo que poderá ser necessário efetuar
vários circuitos de modo a completar a recolha dos referidos meios de mobilidade elétrica.
