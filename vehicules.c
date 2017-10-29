#include "librairies.h"
#include "vehicules.h"

// FONCTIONS RELATIVES AUX VEHICULES ET A LEURS DECISIONS

Position* PositionFuture(Vehicule* vehicule)
{
	Position* Position = NULL;
	switch(vehicule->Direction) 
	{
		case NORD: 
			Position->posX=vehicule->posX;
			Position->posY=(vehicule->posY)+1;
			return Position;
		case EST: 
			Position->posX=(vehicule->posX)+1;
			Position->posY=vehicule->posY;
			return Position;
		case OUEST: 
			Position->posX=(vehicule->posX)-1;
			Position->posY=vehicule->posY;
			return Position;
		default: 
			Position->posX=vehicule->posX;
			Position->posY=(vehicule->posY)-1;
			return Position;
	}
}

void VehiculeEater(VehiculeList **List, Vehicule* Vehicule)
{
	VehiculeList* PointeurCourant;
	VehiculeList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next){
			if (PointeurCourant->Vehicule == Vehicule){
				if (PointeurPrecedent == NULL){ 	/*cas ou on voudrait en fait supprimer le 1er element de la liste (Particulier)	*/
					*List = PointeurCourant->next;} /*on dit juste que le 1er element est en fait le 2e, et on free plus bas */
				else{
					PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
									}
			free(PointeurCourant);break;
								}
						}
}
	
void AppendVehiculeList(VehiculeList **List, Vehicule* Vehicule)
{
	VehiculeList *element;
	element = malloc(sizeof(*element));
	element->Vehicule = Vehicule;
	element->next = *List;
	*List = element;
}

Vehicule* VehiculeSpawner(int posX, int posY, Direction Direction)
{
	Vehicule* Veh=malloc(sizeof(Vehicule));
	Veh->posX=posX;
	Veh->posY=posY;
	Veh->Direction=Direction;
	return Veh;
}

void VisualiserVehiculeList(VehiculeList *List)
{
	VehiculeList *tmp;
	tmp = List;
	while (tmp != NULL)
		{
			printf("posX:%d\n",tmp->Vehicule->posX);
			printf("posY:%d\n",tmp->Vehicule->posY);
			tmp = tmp->next;
		}
}

void Decision(Vehicule* Vehicule, char ** map)
{
	switch(map[Vehicule->posX][Vehicule->posY])
	{
	
	case 'd':
		Vehicule->Direction = EST; break;
	case 'h':
		Vehicule->Direction = NORD; break;
	case 'b':
		Vehicule->Direction = SUD; break;
	case 'g':
		Vehicule->Direction = OUEST; break;
	case 'z':
		Vehicule->Direction = DirectionAleatoire(EST,NORD); break;
	case 'v':
		Vehicule->Direction = DirectionAleatoire(SUD,OUEST); break;
	case 'x':
		Vehicule->Direction = DirectionAleatoire(OUEST,NORD); break;
	case 'y':
		Vehicule->Direction = DirectionAleatoire(EST,SUD); break;
	}
}
Direction DirectionAleatoire(Direction A, Direction B)
{
	int i = rand()%2;
	if (i%2==0){
			return A;}
	else{
			return B;}
}


/*

void Deplacement(Vehicule* Vehicule)
{
	PlaceTerminale(PositionFuture(Vehicule)->posX,PositionFuture(Vehicule)->posY);
	printf("%c",Vehicule.custom);
	Vehicule->posX = PositionFuture(Vehicule)->posX;
	Vehicule->posY = PositionFuture(Vehicule)->posY;
}

*/

void PlaceTerminale(int posX, int posY)
{
	printf("\33[%d;%dH",posX,posY);
}
	
