# Philosophers #

**Descripción**

Philosophers es una simulación de filósofos sentados alrededor de una mesa con tenedores, 
donde cada filósofo puede comer, pensar o dormir, pero no puede hacer más de una actividad a la vez.
El objetivo es evitar que los filósofos mueran de hambre mientras interactúan entre sí utilizando hilos y mutexes.

**Requisitos**

Lenguaje: C

Norma: 

El código sigue la norma de programación especificada (sin variables globales).

Compilación: Utiliza Makefile con las reglas make, clean, fclean, re.

**Argumentos**


**El programa acepta los siguientes argumentos:**

number_of_philosophers: Número de filósofos.
time_to_die: Tiempo antes de que un filósofo muera si no come.
time_to_eat: Tiempo para comer.
time_to_sleep: Tiempo para dormir.
number_of_times_each_philosopher_must_eat (opcional): Número de veces que cada filósofo debe comer antes de finalizar la simulación.

**Ejemplo de uso**

$ ./philo 5 800 200 200

**Funcionalidad**

Filósofos: Cada filósofo es un hilo que come, piensa y duerme.
Mutexes: Para evitar que los filósofos compitan por los tenedores.
Logs: Cada acción de un filósofo se registra con una marca de tiempo.

**Estructura del Proyecto**

philo.c: Función principal.
philo.h: Definiciones y prototipos.
utils.c: Funciones auxiliares.
Makefile: Compilación y gestión de dependencias.

**Reglas**

Sin variables globales.
Evitar condiciones de carrera entre filósofos.


**Resumen Visual - Proyecto Filósofos Comensales**

**Filosofía General del Proyecto**

Cada filosofo es un hilo. Todos comparten recursos comunes (tenedores, estado del programa, etc.)
protegidos por mutexes para evitar condiciones de carrera.

**main()**

Rol: Punto de entrada del programa.
Tareas:
- Valida los argumentos (parse_args).
- Inicializa recursos (init_resources).
- Prepara hilos y mutexes (init_all).
- Inicia la simulacion (start_simulation).
- Supervisa si un filosofo muere o si todos han comido (monitor_philosophers).
- Espera que terminen los hilos (pthread_join) y libera memoria.
  
**philosopher_life()**
  
Rol: Funcion que ejecuta cada filosofo (cada hilo).
Tareas:
- Si solo hay un filosofo, maneja el caso especial.
- Ciclo infinito: tomar tenedores, comer, soltar, dormir, pensar.
- Verifica si debe detenerse (should_stop_execution).
  
**monitor_philosophers()**
  
Rol: Supervisa a todos los filosofos.
Tareas:
- Si hay uno solo, espera su muerte.
- Recorre cada filosofo:
 - Verifica si alguno murio (check_philo_death).
 - Verifica si todos han comido suficiente (check_all_full).
get_time() + precise_usleep()
get_time(): Devuelve el tiempo actual en milisegundos.
precise_usleep(): Pausa con mas precision que usleep, comprobando el tiempo real transcurrido.

**should_stop_execution()**

Rol: Decide si un filosofo debe detenerse.
Tareas:
- Verifica si alguien murio (is_dead).
- Verifica si alcanzo el numero de comidas.
- Si termino, incrementa el contador global de filosofos que han comido (num_philos_full).
init_all() y start_simulation()
init_all(): Inicializa los mutexes y reserva memoria para hilos.

**start_simulation():**

- Marca que los filosofos pueden empezar (can_eat).
- Guarda la hora de inicio.
- Crea los hilos de cada filosofo (create_philos).
  
**Estructuras**
  
t_philosopher:
- Representa un filosofo (es decir, un hilo).
- Contiene su estado, tenedores, contador de comidas y acceso a los recursos.
t_resources:
- Contiene todos los datos compartidos.
- Incluye:
 - Tiempos (time_to_die, etc.)
 - Contadores globales
 - Todos los mutexes

 - LAURA FARINA

