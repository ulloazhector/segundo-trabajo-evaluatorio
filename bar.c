#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUMERODEHOMBRES 100
#define NUMERODEMUJERES 100
#define N 10

//Variables importantes

//contadores, para conocer cuantos hay en el baño en cada momento
int cantidad_de_hombres = 0, cantidad_de_mujeres = 0;

static int contador = 0;

// Dos semaforos que representan el cartel que
sem_t cartel_hombre, cartel_mujer;

//El semaforo del baño
sem_t bathroom;

//////////////////////////////////////////////////////////////////////////////////////////////

void * Hombre(void * arg);

void * Mujer(void * arg);

pthread_t * AlocarMemoria(pthread_t * personas, int a, int b);


int main(int argc, char const *argv[]){

	int i,  cantidad_de_personas = 0;
	
	pthread_t * personas = NULL;

	personas = AlocarMemoria(personas, NUMERODEHOMBRES, NUMERODEMUJERES);

	sem_init(&cartel_hombre, 0, NUMERODEHOMBRES);

	sem_init(&cartel_mujer, 0, NUMERODEMUJERES);

	sem_init(&bathroom, 0, N);

	for (i = 0; i < NUMERODEHOMBRES; ++i){

		pthread_create(&personas[cantidad_de_personas], NULL, *Hombre, NULL);

		cantidad_de_personas++;		

	}


	for (i = 0; i < NUMERODEMUJERES; ++i){

		pthread_create(&personas[cantidad_de_personas], NULL, *Mujer, NULL);		
	
		cantidad_de_personas++;

	}

	for (int i = 0; i < NUMERODEMUJERES+NUMERODEHOMBRES; ++i){
		pthread_join(personas[i], NULL);
	}
	
	printf("el contador da: %d\n",contador );

	return 0;

}


//Accion del hombre en el baño

void * Hombre(void * arg){

			sem_wait(&cartel_hombre);

			cantidad_de_hombres++;

			if (cantidad_de_hombres == 1){ 
				
				sem_wait(&bathroom);

			}

			sem_post(&cartel_hombre);


			for (int i = 0; i < 10000; ++i){
				contador+=1;
			}


			sem_wait(&cartel_hombre);

			cantidad_de_hombres--;

			if (cantidad_de_hombres == 0){ 
				
				sem_post(&bathroom);

			}

			sem_post(&cartel_hombre);


}

//Accion de la mujer en el baño
void * Mujer(void * arg){

			sem_wait(&cartel_mujer);

			cantidad_de_mujeres++;

			if (cantidad_de_mujeres == 1){ 
				
				sem_wait(&bathroom);

			}

			sem_post(&cartel_mujer);


			for (int i = 0; i < 10000; ++i){
				contador-=1;
			}


			sem_wait(&cartel_mujer);

			cantidad_de_mujeres--;

			if (cantidad_de_mujeres == 0){ 
				
				sem_post(&bathroom);

			}

			sem_post(&cartel_mujer);

}

//Funcion para alocar la memoria del vector que funcionara para dar nombre a cada persona

pthread_t * AlocarMemoria(pthread_t * personas, int a, int b){

	personas = (pthread_t *) malloc ((a + b) * sizeof(pthread_t));
	
	if (personas == NULL){
		
		printf("Error al alocar\n");

		exit(-1);

	}

	return personas;

}