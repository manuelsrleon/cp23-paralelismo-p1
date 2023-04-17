#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <mpi.h>

// Inicialmente operaciones colectivas estándar de MPI
int v = 0;
int i, n, count = 0;
  char *cadena;
  char L;




int MPI_BinomialColectiva(void *buf, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
    int myrank, comm_size;
    MPI_Comm_rank(comm, &myrank);
    MPI_Comm_size(comm, &comm_size);

    // Verificación de los parámetros
    if (count < 0) {
        return MPI_ERR_COUNT;
    }
    if (datatype != MPI_INT && datatype != MPI_DOUBLE && datatype != MPI_CHAR) {
        return MPI_ERR_TYPE;
    }
    if (root < 0 || root >= comm_size) {
        return MPI_ERR_ROOT;
    }

    // Cálculo del tamaño del tipo de dato
    int type_size;
    MPI_Type_size(datatype, &type_size);

    // Cada proceso envía su parte del buffer al proceso raíz
    if (myrank != root) {
        MPI_Send(buf, count, datatype, root, 0, comm);
    } else { // El proceso raíz recibe los valores de los demás procesos y los almacena en el buffer
        int i, j;
        for (i = 0; i < count; i++) {
            for (j = 0; j < comm_size; j++) {
                if (j != root) {
                    MPI_Recv((char*)buf + i*type_size, 1, datatype, j, i, comm, MPI_STATUS_IGNORE);
                }
            }
        }
    }

    // Distribución de los valores en forma de árbol binomial
    int mask = 1;
    while (mask < comm_size) {
        if ((myrank & mask) == 0) {
            int partner = myrank | mask;
            if (partner < comm_size) {
                MPI_Recv(buf, count, datatype, partner, 0, comm, MPI_STATUS_IGNORE);
            }
        } else {
            int partner = myrank & (~mask);
            MPI_Send(buf, count, datatype, partner, myrank, comm);
            break;
        }
        mask <<= 1;
    }

    return MPI_SUCCESS;
}


int MPI_FlattreeColectiva(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
    int myrank, comm_size;
    MPI_Comm_rank(comm, &myrank);
    MPI_Comm_size(comm, &comm_size);

    // Verificación de los parámetros
    if (count < 0) {
        return MPI_ERR_COUNT;
    }
    if (datatype != MPI_INT) {
        return MPI_ERR_TYPE;
    }
    if (root < 0 || root >= comm_size) {
        return MPI_ERR_ROOT;
    }

    // Cada proceso envía su parte del buffer al proceso raíz
    if (myrank != root) {
        if(v)
        printf("PROCESO %d: Enviando la cuenta al proceso 0", myrank);
        MPI_Send(sendbuf, count, datatype, root, 0, comm);
    } else {
        memcpy(recvbuf, sendbuf, count * sizeof(int));
        int i;
        for (i = 1; i < comm_size; i++) {
          if(v)
          printf("PROCESO 0: Recibiendo la cuenta desde el proceso %d", i);
            
          MPI_Recv((int*)recvbuf + i, count, datatype, i, 0, comm, MPI_STATUS_IGNORE);
            ((int*)recvbuf)[0] += ((int*)recvbuf)[i];
        }
    }

    return MPI_SUCCESS;
}





// int MPI_BinomialColectiva(void *buf, int count, MPI_Datatype datatype, int root, MPI_Comm comm){
//   //TODO Comprobar que los errores se gestionan adecuadamente.
//   //int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
//   //              int root, MPI_Comm comm)
//   /*MPI_Send(&bufer_envio, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//     MPI_Recv(&bufer_recepcion, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);*/
//   //TODO implementar gestión de errores
//   int myrank, comm_size;
//   int type_size;
//   MPI_Type_size(datatype, & type_size);

//   //TODO Gestionar comm nulo? 
//   MPI_Comm_rank(comm, &myrank);
//   MPI_Comm_size(comm, &comm_size);


//   for(int i = 0; (pow(2,i)-1) < comm_size-1; i++){
//     int source = -1;
    
    
//     if (myrank != root) {
//         MPI_Send(buf, count, datatype, root, 0, comm);
//     } else { // El proceso raíz recibe los valores de los demás procesos y los almacena en el buffer
//         int i, j;
//         for (i = 0; i < count; i++) {
//             for (j = 0; j < comm_size; j++) {
//                 if (j != root) {
//                     MPI_Recv((char*)buf + i*type_size, 1, datatype, j, i, comm, MPI_STATUS_IGNORE);
//                 }
//             }
//         }
//     }

//     int mask = 1;
//     while (mask < comm_size) {
//         if ((myrank & mask) == 0) {
//             int partner = myrank | mask;
//             if (partner < comm_size) {
//                 MPI_Recv(buf, count, datatype, partner, 0, comm, MPI_STATUS_IGNORE);
//             }
//         } else {
//             int partner = myrank & (~mask);
//             MPI_Send(buf, count, datatype, partner, myrank, comm);
//             break;
//         }
//         mask <<= 1;
//     }
  
//   } 
//   return MPI_SUCCESS;
// }

// int MPI_FlattreeColectiva2()
// {
//   //TODO Comprobar que los errores se gestionan adecuadamente.
//   //   Posteriormente introducción de implementación propia de colectiva
//   // SOLO para la recolección de count, inicialmente utilizando las
//   // mismas operaciones de Send/Recv que en la implementación sin
//   // colectivas (bucle for de Recv), implementación que denominaremos
//   // MPI FlattreeColectiva. Asumir que la operación a realizar será una
//   // suma. El resto de parámetros de la cabecera deben ser los mismos
//   // que los de la colectiva estándar de MPI (incluido controlar el error).

//   // TODO implement
//   return MPI_SUCCESS;
// }
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
  

  n = atoi(argv[1]);
  L = *argv[2];
  
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
  MPI_BinomialColectiva(&bufer_envio, 2, MPI_2INT, 0 ,MPI_COMM_WORLD);

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

  if (v && world_rank == 0){
    printf("PROCESO %d: Recuperando la suma de los conteos entre los procesos mediante MPI_FlattreeColectiva.\n", world_rank);
    MPI_FlattreeColectiva(&count, &sum, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
  if(world_rank == 0){
    printf("PROCESO 0: La letra %c aparece %d veces\n",L,sum);
  }
  free(cadena);
  MPI_Finalize();
  exit(0);
}