# Philosophers

Descripción
Philosophers es una simulación de filósofos sentados alrededor de una mesa con tenedores, 
donde cada filósofo puede comer, pensar o dormir, pero no puede hacer más de una actividad a la vez.
El objetivo es evitar que los filósofos mueran de hambre mientras interactúan entre sí utilizando hilos y mutexes.

Requisitos
Lenguaje: C
Norma: El código sigue la norma de programación especificada (sin variables globales).
Compilación: Utiliza Makefile con las reglas make, clean, fclean, re.
Argumentos
El programa acepta los siguientes argumentos:

number_of_philosophers: Número de filósofos.
time_to_die: Tiempo antes de que un filósofo muera si no come.
time_to_eat: Tiempo para comer.
time_to_sleep: Tiempo para dormir.
number_of_times_each_philosopher_must_eat (opcional): Número de veces que cada filósofo debe comer antes de finalizar la simulación.
Ejemplo de uso
bash
Copiar
Editar
$ ./philo 5 800 200 200
Funcionalidad
Filósofos: Cada filósofo es un hilo que come, piensa y duerme.
Mutexes: Para evitar que los filósofos compitan por los tenedores.
Logs: Cada acción de un filósofo se registra con una marca de tiempo.
Estructura del Proyecto
philo.c: Función principal.
philo.h: Definiciones y prototipos.
utils.c: Funciones auxiliares.
Makefile: Compilación y gestión de dependencias.
Reglas
Sin variables globales.
Evitar condiciones de carrera entre filósofos.

