#include "librairies.h"
#include "mouvements.h"


TrafficLight* CreateTrafficLight(int posX, int posY, Color color)
{
	TrafficLight* Traffic=malloc(sizeof(TrafficLight));
	Traffic->posX=posX;
	Traffic->posY=posY;
	Traffic->Current_Color=color;
	Traffic->TimeForSwitch=color;
	return Traffic;
}


void AppendList(TrafficLightList **List, TrafficLight *TrafficLight)
{
	TrafficLightList *element;
	element = malloc(sizeof(*element));
	element->TrafficLight=TrafficLight;
	element->next = *List;
	*List = element;
}	

void VisualiserTrafficLightList(TrafficLightList *List)
{
	TrafficLightList *tmp;
	tmp = List;
	while (tmp != NULL)
		{
			printf("Position en X:%d\n", tmp->TrafficLight->posX);
			printf("Position en Y:%d\n", tmp->TrafficLight->posY);
			printf("Couleur Courrante: %d \n",tmp->TrafficLight->Current_Color);
			printf("Temps requis pour changer de couleur: %d \n",tmp->TrafficLight->TimeForSwitch);
			tmp = tmp->next;
		}
}

void ShowTrafficLight(TrafficLight Feu)
{
	printf("Position en X: %d \n", Feu.posX);
	printf("Position en Y: %d \n", Feu.posY);
	printf("Couleur Courrante: %d \n",Feu.Current_Color);
	printf("Temps requis pour changer de couleur: %d \n",Feu.TimeForSwitch);
}


/*
clock_t StartChrono(double* montre)
{
	clock_t temps;
	double Chrono = temps / CLOCKS_PER_SEC;
	*montre = Chrono;
	}
}

double VisualiserChrono(double* montre)
{
	return *montre;
}	
*/	
	

void Roulement_feux(TrafficLightList *List)
{
	TrafficLightList *tmp;
	tmp = List;
	while(tmp != NULL)
		{
			tmp->TrafficLight->Current_Color+=1%4;
			tmp->TrafficLight->TimeForSwitch+=1%4;
			tmp = tmp->next;
		}
}
		
void GestionDesFeux(TrafficLightList *List)
{
	clock_t temps;
	if((double)temps / CLOCKS_PER_SEC >= (List->TrafficLight->TimeForSwitch))
		{
			Roulement_feux(List);
			GestionDesFeux(List);	
		}
}

Position* PositionFuture(Vehicule* vehicule)
{
	Position* Position;
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
		case SUD: 
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
	if(map[Vehicule->posX][Vehicule->posY]=='x')
		{
			Vehicule->Direction=EST;
		}
}

void Deplacement(Vehicule* Vehicule)
{
	PlaceTerminale(PositionFuture(Vehicule)->posX,PositionFuture(Vehicule)->posY);
	printf("%c",Vehicule->custom[30]);
}



void PlaceTerminale(int posX, int posY)
{
	printf("\33[%d;%dH",posX,posY);
}

Boat* BoatSpawner(int posX, int posY, Direction Direction)
{
	Boat* Boat=malloc(sizeof(Boat));
	Boat->posX=posX;
	Boat->posY=posY;
	Boat->Direction=Direction;
	return Boat;
}

void AppendBoatList(BoatList **List,Boat* Boat)
{
	BoatList *element;
	element = malloc(sizeof(*element));
	element->Boat = Boat;
	element->next = *List;
	*List = element;
}

void BoatEater(BoatList **List, Boat* Boat)
{
	BoatList* PointeurCourant;
	BoatList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next){
			if (PointeurCourant->Boat == Boat){
				if (PointeurPrecedent == NULL){ 	/*cas ou on voudrait en fait supprimer le 1er element de la liste (Particulier)	*/
					*List = PointeurCourant->next;} /*on dit juste que le 1er element est en fait le 2e, et on free plus bas */
				else{
					PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
									}
			free(PointeurCourant);break;
								}
						}
}

void VisualiserBoatList(BoatList *List)
{
	BoatList *tmp;
	tmp = List;
	while (tmp != NULL)
		{
			printf("posX:%d\n",tmp->Boat->posX);
			printf("posY:%d\n",tmp->Boat->posY);
			tmp = tmp->next;
		}
}
	
