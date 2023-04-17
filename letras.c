#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <mpi.h>

// Inicialmente operaciones colectivas estándar de MPI


void inicializaCadena(char *cadena, int n)
{
  int i;
  for (i = 0; i < n / 2; i++)
  {
    cadena[i] = 'A';
  }
  for (i = n / 2; i < 3 * n / 4; i++)
  {
    cadena[i] = 'C';
  }
  for (i = 3 * n / 4; i < 9 * n / 10; i++)
  {
    cadena[i] = 'G';
  }
  for (i = 9 * n / 10; i < n; i++)
  {
    cadena[i] = 'T';
  }
}
typedef struct msg
{
  int n;
  int L;
} Mensaje;

int main(int argc, char *argv[])
{

  MPI_Init(&argc, &argv);

  int world_size; // Representa el tamaño del comunicador mundial, es
  // decir, cuántos procesos hay dentro de él.
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank; // Significa el rank que un determinado proceso tiene
  // dentro del comunicador mundial, es decir, MPI_COMM_WORLD.
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (argc != 3 && argc != 4)
  {
    printf("Numero incorrecto de parametros\nLa sintaxis debe ser: program n L v\n  program es el nombre del ejecutable\n  n es el tamaño de la cadena a generar\n  L es la letra de la que se quiere contar apariciones (A, C, G o T)\n");
    exit(1);
  }
  int i, n, count = 0;
  char *cadena;
  char L;

  n = atoi(argv[1]);
  L = *argv[2];
  int v = 0;
  if (argv[3] != NULL && *argv[3] == 'v')
  {
    v = 1;
  }
  else
  {
    v = 0;
  }

  Mensaje bufer_envio = {n, L};
  Mensaje bufer_recepcion;
  if (v && world_rank == 0)
    printf("PROCESO %d: Enviando n = %d y la letra %c a los demás procesos mediante colectiva.\n", world_rank, n, L);
  MPI_Bcast(&bufer_envio, 2, MPI_2INT, 0 ,MPI_COMM_WORLD);

  cadena = (char *)malloc(n * sizeof(char));
  // Crea una cadena de tamaño n
  inicializaCadena(cadena, n);

  // Cuenta los caracteres de dentro de la cadena
  if (v)
    printf("PROCESO %d: Contando apariciones de %c en la cadena\n", world_rank, L);
  for (i = world_rank; i < n; i += world_size)
  {
    if (cadena[i] == L)
    {
      count++;
    }
  }
  int sum;

  if (v && world_rank == 0)
    printf("PROCESO %d: Recuperando la suma de los conteos entre los procesos mediante MPI_Reduce.\n", world_rank);
  MPI_Reduce(&count, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if(world_rank == 0){
    printf("PROCESO 0: La letra %c aparece %d veces\n",L,sum);
  }
  free(cadena);
  MPI_Finalize();
  exit(0);
}