# Prácticas Paralelismo

## Paralelismo P1

- [ ] Implementación
  - [X] Repartir procesos
  - [X] Generar trozos de la cadena correspondientes en cada proceso
    - ! Suponiendo que se genera toda la cadena en cada proceso
  - [X] Contar las apariciones
  - [X] Enviar los datos a un mismo proceso
  - [X] Imprimir la salida por pantalla
- [ ] Testing
  - [ ] n = ...
    - [X] 4
    - [ ] 5
      - [!] No se puede probar por "not enough slots"
    - [ ] 6
    - [ ] 30
  - [ ] BUG? Posible error de "exit code 1"

## Paralelismo P2

- [ ] Implementación
  - [ ] Colectivas estándar de MPI (Broadcast y Reduce?)
  - [ ] MPI_BinomialColectiva y utilizar en la distribución de n y L
  - [ ] MPI_FlattreeColectiva de suma y usar para la reducción de los conteos
- [ ] Testing
  - [ ] n = ...
    - [X] 4
    - [ ] 5
      - [!] No se puede probar por "not enough slots"
    - [ ] 6
    - [ ] 30