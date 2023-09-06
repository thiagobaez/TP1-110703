#include <stdlib.h>
#include "pokemon.h"
#include "tipo.h"
#include <stdio.h>
#include "ataque.h"
#include <string.h>

#define MAX_ATAQUES 3
#define MAX_NOMBRE 20
/*

enum TIPO { NORMAL, FUEGO, AGUA, PLANTA, ELECTRICO, ROCA };

struct ataque {
	char nombre[20];
	enum TIPO tipo;
	unsigned int poder;
};
*/
struct pokemon {
	char nombre[MAX_NOMBRE];
	enum TIPO tipo;
	struct ataque info_ataque[MAX_ATAQUES];
};

struct info_pokemon {
	pokemon_t* pokemones;
	int cantidad;
};

enum TIPO switch_tipo(char letra){

	enum TIPO resultado;

	switch (letra)
				{
				case 'N':
					resultado=NORMAL;
					break;
				case 'F':
					resultado=FUEGO;
					break;
				case 'A':
					resultado=AGUA;
					break;
				case 'P':
					resultado=PLANTA;
					break;
				case 'E':
					resultado=ELECTRICO;
					break;
				case 'R':
					resultado=ROCA;
					break;			
				}

		return resultado;
}


informacion_pokemon_t *pokemon_cargar_archivo(const char *path)
{
	FILE* archivo;
	int i;
	char linea[30];
	char letra; 
	pokemon_t poke;

	informacion_pokemon_t* informacion;
	pokemon_t* pokemon,*nuevo_pokemon;
	

	archivo=fopen(path,"r");

	if(archivo == NULL){
		printf("No se pudo abrir el archivo.\n");
		return NULL;

	}
	pokemon=(pokemon_t*)malloc(sizeof(pokemon_t));

	if(pokemon == NULL){
		printf("No se pudo asignar la memoria.\n");
		fclose(archivo); 
		return NULL;
	}	

	informacion=(informacion_pokemon_t*)malloc(sizeof(informacion_pokemon_t));
	

	if(informacion == NULL){
		printf("No se pudo asignar la memoria.\n"); 
		fclose(archivo);
		return NULL;
	}
	informacion->cantidad=0;	
	fscanf(archivo,"%s",linea);

	while(!feof(archivo)){

		if(informacion->pokemones>0){
			pokemon=(pokemon_t*)realloc(pokemon,sizeof(pokemon_t)*(informacion->cantidad+1));
			if(pokemon==NULL){
				printf("No se pudo reasignar memoria para el vector.\n");
				fclose(archivo);
				return NULL;

			}
			

		}
		
		sscanf(linea,"%[^;];%c",poke.nombre,&letra);	
		poke.tipo=switch_tipo(letra);	

		for(i=0;i<3;i++){
			fscanf(archivo,"%s",linea);
			sscanf(linea,"%[^;];%c;%u",poke.info_ataque[i].nombre,&letra,&(poke.info_ataque[i].poder));
			poke.info_ataque[i].tipo=switch_tipo(letra);
			
		}

		informacion->pokemones=pokemon;
		informacion->pokemones[informacion->cantidad]=poke;
		informacion->cantidad++;

		fscanf(archivo,"%s",linea);
	}
	
	fclose(archivo);

	return informacion;
}
pokemon_t *pokemon_buscar(informacion_pokemon_t *ip, const char *nombre)
{
	return NULL;
}

int pokemon_cantidad(informacion_pokemon_t *ip)
{
	return 0;
}

const char *pokemon_nombre(pokemon_t *pokemon)
{
	return NULL;
}

enum TIPO pokemon_tipo(pokemon_t *pokemon)
{
	return FUEGO;
}

const struct ataque *pokemon_buscar_ataque(pokemon_t *pokemon,
					   const char *nombre)
{
	return NULL;
}

int con_cada_pokemon(informacion_pokemon_t *ip, void (*f)(pokemon_t *, void *),
		     void *aux)
{
	return 0;
}

int con_cada_ataque(pokemon_t *pokemon,
		    void (*f)(const struct ataque *, void *), void *aux)
{
	return 0;
}

void pokemon_destruir_todo(informacion_pokemon_t *ip)
{
}
