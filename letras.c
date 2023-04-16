#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <mpi.h>

// Inicialmente operaciones colectivas estándar de MPI

int MPI_BinomialColectiva(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
{
  //TODO Comprobar que los errores se gestionan adecuadamente.
  //int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
  //              int root, MPI_Comm comm)
  /*MPI_Send(&bufer_envio, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    MPI_Recv(&bufer_recepcion, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);*/
  //TODO implementar gestión de errores
  int comm_size = 0;
  //TODO Gestionar comm nulo? 
  
  MPI_Comm_size(comm, &size);


  for(int i = 0; (pow(2,i)-1) < comm_size-1; i++){
    int source = -1;

    if(rank ){
      for(int i = 0; i < myrank+pow())
        if(v)
          printf("PROCESO %d: Enviando n = %d y L = %c a PROCESO %d", myrank, n, L, target)
        MPI_Send(&bufer_envio, 1, MPI_INT, target, 0, MPI_COMM_WORLD);
      }
    }else{
      source = pow(2,i)-1;
      if(v)
          printf("PROCESO %d: Esperando a recibir datos de PROCESO %d", myrank, source)
      for(int i = 0; i < ){
        MPI_Recv(&bufer_recepcion, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                  
      }
    }

  
  // Implementación de colectiva en árbol binomial, implementación que
  // denominaremos MPI BinomialColectiva, a utilizar SOLO en la
  // distribución de n y L.

}

int MPI_FlattreeColectiva()
{
  //TODO Comprobar que los errores se gestionan adecuadamente.
  //   Posteriormente introducción de implementación propia de colectiva
  // SOLO para la recolección de count, inicialmente utilizando las
  // mismas operaciones de Send/Recv que en la implementación sin
  // colectivas (bucle for de Recv), implementación que denominaremos
  // MPI FlattreeColectiva. Asumir que la operación a realizar será una
  // suma. El resto de parámetros de la cabecera deben ser los mismos
  // que los de la colectiva estándar de MPI (incluido controlar el error).

  // TODO implement
}
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
  int count_recepcion;
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