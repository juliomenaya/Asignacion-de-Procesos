#include<stdio.h>
#include<stdlib.h>

//Estructura para almacenar cada registro
typedef struct {
	char id;
	int tiempo;
}Registro;

//Prototipo de funciones
int menu(int,char []);
int num_regs(FILE*);
void guarda(FILE*,int);
void procesador(Registro*,int);

int main(int argc, char *argv[]){
	menu(argc,argv[1]);
	return 0;
}

//Funcion que para validar el archivo a ser leido
int menu(int argc, char nombre[]){
	int registros;
	FILE *archi;
	if(argc>2){
		printf("\nHay demasiados argumentos\n");
		printf("Saliendo del programa...\n");
		return -1;
	}
	if(argc==1){
		printf("\nNo se indico el nombre del archivo\n");
		printf("Saliendo del programa...\n");
		return -1;
	}
	if((archi=fopen(nombre,"r")) == NULL){
		printf("\nNo se pudo abrir el archivo *%s*\n",nombre);
		printf("\nVerifique que el archivo exista\n");
		printf("\nSaliendo del programa...\n");
		return -1;
	}
	printf("\nEl archivo *%s* se accedio correctamente..\n",nombre);
	registros=num_regs(archi);		//Obtiene la cantidad de registros que hay en el archivo
	guarda(archi,registros);
	fclose(archi);
	return 0;
}

//Funcion para saber cuantos registros hay en el archivo
int num_regs(FILE *archivo){
	int n,tama=0;
	while((n=fgetc(archivo))!=EOF){
		if(n=='\n'){
			tama++;
		}
	}
	return tama+1;
}

//Funcion de comparacion para que qsort ordene de menor a mayor
int compara(const void *a,const void *b){
	int l=((Registro*)a)->tiempo;
	int r=((Registro*)b)->tiempo;
  return ( l-r);
}

/*Funcion para almacenar los datos en un arreglo y los ordena de
mayor a menor*/
void guarda(FILE *archivo,int tamanio){
	int i=0,tmp;
	int time_return=0;
	float promedio; 
	Registro *registros;
	registros=(Registro*)calloc(tamanio,sizeof(Registro));
	rewind(archivo);
	do{
		tmp=fscanf(archivo,"%c %d\n",&registros[i].id,&registros[i].tiempo);
		i++;
	}while(tmp==2);
	
	qsort(registros,tamanio,sizeof(Registro),compara);
	
	for(i=0;i<tamanio;i++){
		time_return+=registros[i].tiempo;
		printf("\n\nEl proceso %c entro en ejecucion",registros[i].id);
		printf(" con %d tiempos de procesador\n",registros[i].tiempo);
		printf("\ntiempo de retorno... %d\n\n",time_return);
	}
	printf("\n\n\n###Se termino de atender a todos los procesos###\n\n\n");
	promedio=(time_return/(float)tamanio);
	printf("\nEl tiempo promedio de retorno es %.2f\n",promedio);
	free(registros);
	return;
}
//Funcion que "ejecuta" los procesos leidos
void procesador(Registro *reg,int tamanio){
	
	int i,time_return=0;
	float promedio; 
	printf("\ntamanio %d\n",tamanio);
	for(i=0;i<tamanio;i++){
		time_return+=reg[i].tiempo;
		printf("\n\nEl proceso %c entro en ejecucion",reg[i].id);
		printf(" con %d tiempos de procesador\n",reg[i].tiempo);
		printf("\ntiempo de retorno... %d\n\n",time_return);
	}
	printf("\n\n\n###Se termino de atender a todos los procesos###\n\n\n");
	promedio=(time_return/(float)tamanio);
	printf("\nEl tiempo promedio de retorno es %.2f\n",promedio);
	free(reg);
	return;
}