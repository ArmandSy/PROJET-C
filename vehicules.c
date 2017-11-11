#include "librairies.h"
#include "vehicules.h"


// FONCTIONS RELATIVES AUX VEHICULES ET A LEURS DECISIONS

Position* positionFuture(Vehicule* vehicule)
{
	Position* Position = malloc(sizeof(Position));
	switch(vehicule->Direction) 
	{
		case NORD: 
			Position->posX=(vehicule->posX)-1;
			Position->posY=vehicule->posY;
			return Position;
		case EST: 
			Position->posX=vehicule->posX;
			Position->posY=(vehicule->posY)+1;
			return Position;
		case OUEST: 
			Position->posX=vehicule->posX;
			Position->posY=(vehicule->posY)-1;
			return Position;
		case SUD: 
			Position->posX=(vehicule->posX)+1;
			Position->posY=vehicule->posY;
			return Position;
		default:
			Position->posX = vehicule->posX;
			Position->posY = vehicule->posY;
			return Position;
	}
}

void setNewPositionVehicule(Vehicule* vehicule)
{
	vehicule->posX = positionFuture(vehicule)->posX;
	vehicule->posY = positionFuture(vehicule)->posY;
}

int Obstacle(char** MatriceDecision, int i, int j)
{
	if(MatriceDecision[i][j]!='c'||MatriceDecision[i][j]!='f')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


void roulementVehiculesPosition(char** MatriceDecision, VehiculeList** ListeDesVehicules)
{
	VehiculeList *tmp;
	tmp = *ListeDesVehicules;
	while (tmp != NULL)
		{	
			Position* NextPosition = positionFuture(tmp->Vehicule); // Afin de free plus tard
			if(Obstacle(MatriceDecision, NextPosition->posX, NextPosition->posY)==0)
			{
				if((MatriceDecision[NextPosition->posX][NextPosition->posY]=='P')&&((tmp->Vehicule->Compteur)<8))
				{
					affichageVehicule(tmp->Vehicule);
					//ANIMATION DE REMPLISSAGE DU PLEIN?
					tmp->Vehicule->Compteur = tmp->Vehicule->Compteur +1;
					tmp = tmp->next;
				}
				else
				{
					MatriceDecision[tmp->Vehicule->posX][tmp->Vehicule->posY] = tmp->Vehicule->CaseDecision; //La ou la voiture etait devient de la route (place libre)
					setNewPositionVehicule(tmp->Vehicule); //On actualise la position de la voiture dans la structure 
					tmp->Vehicule->CaseDecision = MatriceDecision[NextPosition->posX][NextPosition->posY]; // MAJ de la case decision
					if(tmp->Vehicule->CaseDecision == 'E')
					{
						tmp = vehiculeEater(ListeDesVehicules, tmp->Vehicule);

					}
					else
					{
					setNewVehiculeDirection(tmp->Vehicule, MatriceDecision, *ListeDesVehicules); //On actualise la Direction du vehicule
					MatriceDecision[NextPosition->posX][NextPosition->posY] = 'c'; //On actualise la MatricePositionVehicules pour signaler qu'une voiture se trouve maintenant a cette position
					affichageVehicule(tmp->Vehicule);	
					tmp = tmp->next;
					}
				}
			}
			else 
			{
				affichageVehicule(tmp->Vehicule);
			}
			free(NextPosition);
		}
}


VehiculeList* vehiculeEater(VehiculeList **List, Vehicule* Vehicule)
{
	VehiculeList* PointeurCourant;
	VehiculeList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next)
	{
		if (PointeurCourant->Vehicule == Vehicule)
		{
			if (PointeurPrecedent == NULL)
			{ 	/*cas ou on voudrait en fait supprimer le 1er element de la liste (Particulier)	*/
				*List = PointeurCourant->next;
			} /*on dit juste que le 1er element est en fait le 2e, et on free plus bas */
			else
			{
				PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
			}
		VehiculeList* ptrToReturn = PointeurCourant->next;
		free(PointeurCourant);break;
		return ptrToReturn;
		}
	}
	return NULL;
}
	
void appendVehiculeList(VehiculeList** ListeDesVehicules, Vehicule* Vehicule)
{
	VehiculeList *element;
	element = calloc(1,sizeof(*element));
	element->Vehicule = Vehicule;
	element->next = *ListeDesVehicules;
	*ListeDesVehicules = element;
}

void vehiculeSpawner(int posX, int posY, Direction Direction, Carburant Carburant, char a, char** MatriceDecision, VehiculeList** ListeDesVehicules)
{
	Vehicule* Veh = malloc(sizeof(Vehicule));
	Veh->posX=posX;
	Veh->posY=posY;
	Veh->Compteur = 0;
	Veh->custom = a;
	Veh->CaseDecision = 'S';
	Veh->Direction = Direction;
	Veh->Carburant = Carburant;
	MatriceDecision[posX][posY] = 'c';
	appendVehiculeList(ListeDesVehicules, Veh);
}

Vehicule* oldVehiculeSpawner(int posX, int posY, Direction Direction)
{
	Vehicule* Veh=malloc(sizeof(Vehicule));
	Veh->posX=posX;
	Veh->posY=posY;
	Veh->Direction=Direction;
	return Veh;
}

void visualiserVehiculeList(VehiculeList *List)
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

void setNewVehiculeDirection(Vehicule* Vehicule, char ** MatriceDecision, VehiculeList *ListeDesVehicules)
{
	switch(MatriceDecision[Vehicule->posX][Vehicule->posY])
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
		Vehicule->Direction = directionAleatoire(EST,NORD); break;
	case 'v':
		Vehicule->Direction = directionAleatoire(SUD,OUEST); break;
	case 'x':
		Vehicule->Direction = directionAleatoire(OUEST,NORD); break;
	case 'y':
		Vehicule->Direction = directionAleatoire(EST,SUD); break;
	case 'E':
		vehiculeEater(&ListeDesVehicules,Vehicule);
	case 'a':
		if(Vehicule->Carburant == FAIBLE)
		{
			Vehicule->Direction = SUD;
		}
		// FAIRE UNE ANIMATION?
	}
}

Direction directionAleatoire(Direction A, Direction B)
{
	int i = rand()%2;
	if (i%2==1) {
			return A;
	}
	else {

			return B;
	}
}


void placeTerminale(int posX, int posY)
{
	printf("\33[%d;%dH",posX,posY);
}

void affichageVehicule(Vehicule* V)
{
	switch(V->custom)
	{
		case 'v': 
			couleur("32");
			printf("\033[%d;%dH🚘",V->posX,V->posY);
		case 'o': 
			couleur("33");
			printf("\033[%d;%dH🚍",V->posX,V->posY);
		case 'r': 
			couleur("31");
			printf("\033[%d;%dH🚘",V->posX,V->posY);
		case 'b': 
			couleur("35");
			printf("\033[%d;%dH🚖",V->posX,V->posY);
		case 's': 
			couleur("37");
			printf("\033[%d;%dH🚘",V->posX,V->posY);
	}
}

char AleatoireCustomVehicule()
{
	switch(rand()%5)
	{
		case 0: 
		return 'v'; break;
		case 1: 
		return 'r'; break;
		case 2:
		return 'o'; break;
		case 3:
		return 'b'; break;
		default:
		return 's'; break;
	}
}

/* PARTIE HELICOPTERES */

void helicoptereSpawner(int posX, int posY,char axe, HelicoptereList** ListeDesHelicopteres)
{
	Helicoptere* Helico=malloc(sizeof(Helicoptere));
	Helico->posX = posX;
	Helico->posY = posY;
	Helico->axe = axe;
	appendHelicoptereList(ListeDesHelicopteres, Helico);
}

void appendHelicoptereList(HelicoptereList** ListeDesHelicopteres, Helicoptere* Helico)
{
	HelicoptereList *element;
	element = calloc(1,sizeof(*element));
	element->Helicoptere = Helico;
	element->next = *ListeDesHelicopteres;
	*ListeDesHelicopteres = element;
}

HelicoptereList* helicoptereEater(HelicoptereList **List, Helicoptere* Helicoptere)
{
	HelicoptereList* PointeurCourant;
	HelicoptereList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next)
	{
		if (PointeurCourant->Helicoptere == Helicoptere)
		{
			if (PointeurPrecedent == NULL)
			{ 	
				*List = PointeurCourant->next;
			} 
			else
			{
				PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
			}
		HelicoptereList* ptrToReturn = PointeurCourant->next;
		free(PointeurCourant);break;
		return ptrToReturn;
		}
	}
	return NULL;
}

void affichageHelicoptere(Helicoptere* Helico)
{
	couleur("37");
	printf("\033[%d;%dH🚁",Helico->posX,Helico->posY);

}

Position* positionFutureHelicoptere(Helicoptere* Helico) // Commentaire sur le codage des axes en bas de la fonction
{
	Position* Position = malloc(sizeof(Position));
	Position->posX = Helico->posX;
	Position->posY = Helico->posY;
	int i;
	i=rand()%2;
	switch(Helico->axe) 
	{
		case 'u': 
			Position->posX=(Helico->posX)-1;
			if(i%2 == 0)
			{
				Helico->axe = 'a';
			}
			else
			{
				Helico->axe = 'b';
			}
			return Position;
		case 'r': 
			Position->posY=(Helico->posY)+1;
			if(i%2 == 0)
			{
				Helico->axe = 'a';
			}
			else
			{
				Helico->axe = 'c';
			}
			return Position;
		case 'l': 
			Position->posY=(Helico->posY)-1;
			if(i%2 == 0)
			{
				Helico->axe = 'b';
			}
			else
			{
				Helico->axe = 'e';
			}
			return Position;
		case 'd': 
			Position->posX=(Helico->posX)+1;
			if(i%2 == 0)
			{
				Helico->axe = 'e';
			}
			else
			{
				Helico->axe = 'c';
			}
			return Position;
		case 'a': 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)-1;	
			}
			else
			{
				Position->posX=Helico->posX;
				Position->posY=(Helico->posY)+1;
			}
			return Position;
		case 'b': 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)-1;
			}
			else
			{
				Position->posY=(Helico->posY)-1;
			}
			return Position;
		case 'c': 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)+1;
			}
			else
			{
				Position->posY=(Helico->posY)+1;
			}
			return Position;
		case 'e': 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)+1;
			}
			else
			{
				Position->posY=(Helico->posY)+1;
			}
			return Position;
		default:
			return Position;
	}
}

//Helico trajectoire diagonale en moyenne : u=UP ; r=RIGHT ; l=LEFT ; d=DOWN ; a=UP&&RIGHT ; b=UP&&LEFT ; c=DOWN&&RIGHT ; e=DOWN&&LEFT

void roulementHelicopteresPosition(char** MatriceDecision, HelicoptereList** ListeDesHelicopteres)
{
	HelicoptereList *tmp;
	tmp = *ListeDesHelicopteres;
	while (tmp != NULL)
		{	
			Position* NextPosition = positionFutureHelicoptere(tmp->Helicoptere); // Afin de free plus tard
			if (NextPosition->posX==1 || NextPosition->posY==1 || NextPosition->posX==65 || NextPosition->posY==194)
			{
				tmp->Helicoptere->posX = NextPosition->posX;
				tmp->Helicoptere->posY = NextPosition->posY;
				affichageHelicoptere(tmp->Helicoptere);
				tmp = helicoptereEater(ListeDesHelicopteres, tmp->Helicoptere);
			}
			else
			{
			tmp->Helicoptere->posX = NextPosition->posX;
			tmp->Helicoptere->posY = NextPosition->posY;
			affichageHelicoptere(tmp->Helicoptere);
			tmp = tmp->next;
			}
		free(NextPosition);
		}
}

/* PARTIE TRAMWAYS */

void tramwaySpawner(int posX, int posY, Direction Direction, TramwayList** ListeDesTramways)
{
		Tramway* Tram=malloc(sizeof(Tramway));
		Tram->posX = posX;
		Tram->posY = posY;
		Tram->CaseDecision = 'S';
		Tram->Direction = Direction;
		appendTramwayList(ListeDesTramways, Tram);
}

void appendTramwayList(TramwayList** ListeDesTramways, Tramway* Tram)
{
	TramwayList *element;
	element = calloc(1,sizeof(*element));
	element->Tramway = Tram;
	element->next = *ListeDesTramways;
	*ListeDesTramways = element;
}

TramwayList* tramwayEater(TramwayList **List, Tramway* Tramway)
{
	TramwayList* PointeurCourant;
	TramwayList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next)
		{
			if (PointeurCourant->Tramway == Tramway)
			{
				if (PointeurPrecedent == NULL)
				{ 	
					*List = PointeurCourant->next;
				} 
				else
				{
				PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
				}
			TramwayList* ptrToReturn = PointeurCourant->next;
			free(PointeurCourant);break;
			return ptrToReturn;
			}
		}
	return NULL;
}

void affichageTramway(Tramway* Tram)
{
		couleur("37");
		printf("\033[%d;%dH🚋",Tram->posX,Tram->posY);

}

void setNewTramwayDirection(Tramway* Tramway, char ** MatriceDecision, TramwayList *ListeDesTramways)
{
	switch(MatriceDecision[Tramway->posX][Tramway->posY])
	{
		case 'd':
		case 'l':
		case 'j':
			Tramway->Direction = EST; 
			break;
		case 'k':
		case 'r':
		case 'g':
			Tramway->Direction = OUEST; 
			break;
		case 'h':
			Tramway->Direction = NORD; 
			break;
		case 'b':
			Tramway->Direction = SUD; 
	}

}

Position* positionFutureTramway(Tramway* Tramway)
{
	Position* Position = malloc(sizeof(Position));
	Position->posX = Tramway->posX;
	Position->posY = Tramway->posY;
	switch(Tramway->Direction)
	{
		case NORD: 
			Position->posX = Position->posX -1;
			return Position;
		case SUD:
			Position->posX = Position->posX +1;
			return Position;
		case EST:
			Position->posY = Position->posY +1;
			return Position;
		case OUEST:
			Position->posY = Position->posY -1;
			return Position;
		default:
			return Position;
	}
}

int ObstacleTramway(char ** MatriceDecision, int i, int j)
{
	if(MatriceDecision[i][j] == 'f' || MatriceDecision[i][j] == 'c')
	{
		return 1;
	}
	else if(MatriceDecision[i][j] == 'E')
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

void roulementTramwaysPosition(char** MatriceDecision, TramwayList** ListeDesTramways)
{
TramwayList *tmp;
tmp = *ListeDesTramways;
while (tmp != NULL)
	{	
		Position* NextPosition = positionFutureTramway(tmp->Tramway); // Afin de free plus tard
		if (ObstacleTramway(MatriceDecision, NextPosition->posX, NextPosition->posY) == 2)
		{
			tmp->Tramway->posX = NextPosition->posX;
			tmp->Tramway->posY = NextPosition->posY;
			affichageTramway(tmp->Tramway);
			tmp = tramwayEater(ListeDesTramways, tmp->Tramway);
		}
		else if (ObstacleTramway(MatriceDecision, NextPosition->posX, NextPosition->posY) == 1)
		{
			affichageTramway(tmp->Tramway);
		}
		else
		{
			if(tmp->Tramway->CaseDecision == 'D')
			{
					tmp->Tramway->posX = NextPosition->posX;
					tmp->Tramway->posY = NextPosition->posY;
					affichageTramway(tmp->Tramway);
					tmp->Tramway->CaseDecision = 'F'; //Passage en mode fantome
					tmp = tmp->next;
			}
			else if(tmp->Tramway->CaseDecision == 'F') //Mode fantome
			{
				tmp->Tramway->posX = NextPosition->posX;
				tmp->Tramway->posY = NextPosition->posY;
				if(MatriceDecision[NextPosition->posX][NextPosition->posY] == 'A')
				{
					tmp->Tramway->CaseDecision = 'A';
				}
				tmp = tmp->next;
			}
			else 
			{ 

				tmp->Tramway->posX = NextPosition->posX;
				tmp->Tramway->posY = NextPosition->posY;
				tmp->Tramway->CaseDecision = MatriceDecision[tmp->Tramway->posX][tmp->Tramway->posY];
				setNewTramwayDirection(tmp->Tramway, MatriceDecision, *ListeDesTramways);
				affichageTramway(tmp->Tramway);
				tmp = tmp->next;	
			}
	
		}
			free(NextPosition);
	}
}


