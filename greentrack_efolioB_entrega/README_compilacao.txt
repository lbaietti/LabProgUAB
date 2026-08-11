GreenTrack — E-fólio B

Compilação principal:
  make

Execução dos testes:
  make test

Limpeza:
  make clean

No Windows com MinGW/gcc:
  gcc -Wall -Wextra -pedantic -std=c11 -I src src\main.c src\plantas.c src\regas.c src\tarefas.c src\persistencia.c -o greentrack.exe

Nota:
Este pacote contém o código fonte, testes e ficheiros de dados. A geração do executável Windows deve ser feita no ambiente de avaliação com MinGW, conforme o enunciado.
