# Pr1SisDis
# Authors Sebastián Fco. Gutiérrez Rojas && Manuel Cabrera Liñán

En este repositorio se presenta una práctica en la que se utiliza Remote Procedure Call (RPC) para la comunicación entre dos programas: File Manager y Multiplicación de matrices.

El primer programa, File Manager, es una clase que implementa funciones para listar los archivos de un directorio local, y realizar operaciones básicas de lectura y escritura sobre ellos. La clase cuenta con los siguientes métodos:

ListFiles: Devuelve un vector con los nombres de los ficheros encontrados en el directorio local.
ReadFile: Lee el contenido y tamaño de un fichero dado.
WriteFile: Escribe el contenido de un fichero en el directorio local.
El segundo programa, Multiplicación de matrices, es una clase que implementa los métodos básicos para multiplicar matrices. La clase cuenta con los siguientes métodos:

ReadMatrix: Lee los datos de una matriz desde un fichero.
WriteMatrix: Escribe los datos de una matriz en un fichero local.
MultMatrix: Multiplica dos matrices.
CreateIdentity/createRandom: Crea matrices por defecto.
Ambos programas utilizan RPC para la comunicación entre ellos, permitiendo el intercambio de información y la ejecución de operaciones en tiempo real.
