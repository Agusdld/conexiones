Crean 2 proyectos distintos, uno para cada proceso
copian el contenido de cada proceso en cada uno de los .c
abren 2 consolas
en la primera se mueven hasta el directorio donde tienen el proceso2.c
compilan: gcc proceso2.c -o proceso2
en la segunda consola se mueven hasta el directorio donde tienen el proceso1.c
compilan: gcc proceso1.c -o proceso1
vuelven a la consola 1 y ejecutan el proceso 2: ./proceso2
vuelven a la consola 2 y ejecutan el proceso 1: ./proceso1
El proceso2 se inicia y queda esperando a conexiones
Cuando inician el proceso1(cliente) se intenta conectar al proces2(server)
