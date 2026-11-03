# Sincronizador-Metro

Programa em C que simula a sincronização de um carro de metrô e seus passageiros usando Pthreads. Cada carro e cada passageiro é representado por uma thread; a implementação usa um único mutex e variáveis de condição para garantir que o carro só parta quando todos os passageiros liberados tiverem embarcado e o carro estiver cheio ou a fila tiver acabado.

## Compilação

make

O Makefile gera o executável sync_car.

## Execução

./sync_car

ou

make run

O runner cria 100 passageiros e carros com quantidades aleatórias de assentos. A saída esperada termina com:

Looks good!

## Teste

Para repetir o runner várias vezes e expor problemas de sincronização:

for i in $(seq 1 100); do ./sync_car | tail -1; done

Todas as linhas devem terminar com Looks good!

## Limpeza

make clean

## Estratégia de sincronização

- **Um único mutex** (lock) protege todo o estado da estação.
- **car_arrived**: passageiros esperam até haver um carro com assentos livres. O carro usa pthread_cond_broadcast para acordar todos os passageiros quando chega.
- **car_full_or_done**: o carro espera até que todos os passageiros que embarcaram tenham chamado station_on_board e que o carro esteja cheio ou a fila tenha acabado.
- **Contadores**:
  - remaining_seats — assentos livres do carro atual; 0 indica que não há carro ou que ele está cheio.
  - waiting — passageiros que chegaram e ainda não conseguiram assento.
  - boarding — passageiros que já conseguiram assento, mas ainda não chamaram station_on_board.

O código não usa semáforos, não usa mais de um lock por estação e não faz busy-wait: todas as esperas são feitas com pthread_cond_wait dentro de laços que reavaliam o predicado.

## Estrutura do código

- **sync_car.c** — implementação de station_init, station_load_car, station_wait_for_car e station_on_board.
- **sync_car.h** — declaração da struct station e protótipos das funções.
- **sync_car-runner.c** — runner de teste fornecido pelo professor, que simula os passageiros e os carros.
- **Makefile** — regras de compilação, execução e limpeza.

## Ambiente

Implementado e testado em Linux (CachyOS) com gcc 16.2.1 e GNU make. O programa usa apenas a biblioteca padrão do C e Pthreads.
