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
				default:
					resultado=-1;
					break;				
				}

		return resultado;
}

int contar_separadores(char *string){
	int i;
	int separadores=0;
	for(i=0;i<strlen(string);i++){
		if(string[i]==';'){
			separadores++;
		}
	}
	return separadores;

}

void ordenar_pokemones_alfabeticamente(informacion_pokemon_t* ip){

	int i,j;
	pokemon_t tmp;

	for(i=0;i<ip->cantidad-1;i++){
		for(j=i+1;j<ip->cantidad;j++){
			if(strcmp(ip->pokemones[i].nombre,ip->pokemones[j].nombre)>0){
				tmp=ip->pokemones[i];
				ip->pokemones[i]=ip->pokemones[j];
				ip->pokemones[j]=tmp;

			}
		}
	}	


}

informacion_pokemon_t *pokemon_cargar_archivo(const char *path)
{
	FILE* archivo;
	int i;
	char linea[30];
	char letra;
	int separadores; 
	pokemon_t poke;

	informacion_pokemon_t* informacion;
	pokemon_t* pokemon=NULL;
	pokemon_t* nuevo;
	

	archivo=fopen(path,"r");

	if(archivo == NULL)
		return NULL;


	informacion=(informacion_pokemon_t*)malloc(sizeof(informacion_pokemon_t));
	

	if(informacion == NULL){
		fclose(archivo);
		return NULL;
	}

	informacion->cantidad=0;	
	(void)!fscanf(archivo,"%s",linea);
	if(feof(archivo)){
		fclose(archivo);
		free(pokemon);
		free(informacion);
		return NULL;
	}

	

	while(!feof(archivo)){
	
		if(contar_separadores(linea)==1){
			sscanf(linea,"%[^;];%c",poke.nombre,&letra);	
			poke.tipo=switch_tipo(letra);
			if(poke.tipo==-1){
					fclose(archivo);
					if(informacion->cantidad==0){
						free(pokemon);
						free(informacion);
						return NULL;
					}
					else{
						return informacion;
					}

				}	
			separadores=0;

			for(i=0;i<MAX_ATAQUES;i++){
				(void)!fscanf(archivo,"%s",linea);
				separadores+=contar_separadores(linea);
				sscanf(linea,"%[^;];%c;%u",poke.info_ataque[i].nombre,&letra,&(poke.info_ataque[i].poder));
				poke.info_ataque[i].tipo=switch_tipo(letra);
				if(poke.info_ataque[i].tipo==-1){
					fclose(archivo);
					if(informacion->cantidad==0){
						free(pokemon);
						free(informacion);
						return NULL;
					}
					else{
						return informacion;
					}

				}
				
			}
			if(separadores!=6){
				fclose(archivo);
				if(informacion->cantidad==0){
					free(pokemon);
					free(informacion);
					return NULL;
				}
				else{
					return informacion;
				}
			}

		}
		else{
			fclose(archivo);
			if(informacion->cantidad==0){
				free(pokemon);
				free(informacion);
				return NULL;
			}	
			else{
				return informacion;
			}
		}

		
		nuevo=(pokemon_t*)realloc(pokemon,sizeof(pokemon_t)*(long unsigned int)(informacion->cantidad+1));
		if(nuevo==NULL){

			fclose(archivo);
			return NULL;

		}
		pokemon=nuevo;

		informacion->pokemones=pokemon;
		informacion->pokemones[informacion->cantidad]=poke;
		informacion->cantidad++;

		(void)!fscanf(archivo,"%s",linea);
		
		
	}
	
	fclose(archivo);

	return informacion;
}
pokemon_t *pokemon_buscar(informacion_pokemon_t *ip, const char *nombre)
{
	if(ip==NULL || nombre == NULL){

		return NULL;
	}

	int i=0;
	pokemon_t* ubicacion=NULL;
	while(ubicacion==NULL && i<ip->cantidad){

		if(strcmp(ip->pokemones[i].nombre,nombre)==0){
			ubicacion=&ip->pokemones[i];
		}
		i++;
	}
		return ubicacion;
}

int pokemon_cantidad(informacion_pokemon_t *ip)
{	
	if(ip==NULL)
		return 0;
	else
		return ip->cantidad;
}

const char *pokemon_nombre(pokemon_t *pokemon)
{
	const char* nombre_del_pokemon;
	if(pokemon!=NULL){
		nombre_del_pokemon=(const char*)pokemon->nombre;
	}
	else{
		nombre_del_pokemon=NULL;
	}

	return nombre_del_pokemon;
}

enum TIPO pokemon_tipo(pokemon_t *pokemon)
{
	enum TIPO tipo=NORMAL;

	if(pokemon!=NULL){
		tipo=pokemon->tipo;
	}

	return tipo;
}

const struct ataque *pokemon_buscar_ataque(pokemon_t *pokemon, const char *nombre)
{
	int i=0;
	const struct ataque* resultado=NULL;
	if(pokemon == NULL || nombre == NULL){
		return NULL;
	}
	else{
		while(resultado==NULL && i<MAX_ATAQUES){
			if(strcmp(pokemon->info_ataque[i].nombre,(char*)nombre)==0){
			resultado=&pokemon->info_ataque[i];
			}
			i++;
		}
	}
	return resultado;
}

int con_cada_pokemon(informacion_pokemon_t *ip, void (*f)(pokemon_t *, void *),
		     void *aux)
{
	int i;

	if(ip == NULL || aux == NULL || f== NULL){
		return 0;
	}

	ordenar_pokemones_alfabeticamente(ip);

	for(i=0;i<ip->cantidad;i++){
		(*f)(&ip->pokemones[i],aux);

	}

	return ip->cantidad;
}

int con_cada_ataque(pokemon_t *pokemon,
		    void (*f)(const struct ataque *, void *), void *aux)
{	int i;

	if(pokemon == NULL || aux == NULL || f == NULL){
		return 0;
	}

	for(i=0;i<MAX_ATAQUES;i++){
		(*f)(&pokemon->info_ataque[i],aux);

	}

	return MAX_ATAQUES;
}

void pokemon_destruir_todo(informacion_pokemon_t *ip)
{	
	if(ip!=NULL){
	free(ip->pokemones);
	free(ip);
	}
	
}
