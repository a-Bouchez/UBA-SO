/*
Explicar la diferencia entre los conceptos de fragmentación interna y externa.

Qué es la fragmentación externa?

    - Fragmentación Externa es cuando hay suficiente memoria para satisfacer un pedido pero los espacios disponibles no son contiguos. 
      (El algoritmo de asignación que usamos nos dejó con espacios muy fragmentados).

    - Después de que muchos procesos terminaron, dependiendo de la estrategia de asignación de memoria pueden resultar muchos huecos pequeños y dispersos 
      donde ninguno es suficientemente grande para alojar a un nuevo proceso a pesar de que la suma total del espacio libre sí sea suficiente.

Qué es la fragmentación interna?

    - Fragmentación interna es cuando queda memoria sin utilizar dentro de una partición asignada.

    - Para que se entienda: Cuando se le asigna a un proceso más espacio del que pidió. Ese extra queda asignado al proceso pero se desperdicia.
*/