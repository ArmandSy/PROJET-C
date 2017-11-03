#include "librairies.h"
#include "boats.h"

// FONCTIONS RELATIVES AUX BATEAUX ET A LEURS DECISIONS

Boat* BoatSpawner(int posX, int posY, Sens Sens, char** MatriceDecision, BoatList* ListeDesBoats)
{
	Boat* Boat = malloc(sizeof(Boat));
	Boat->posX = posX;
	Boat->posY = posY;
	Boat->Sens = Sens;
	Boat->CaseDecision = 'E';
	MatriceDecision[posX][posY] = 'L';
	AppendBoatList(&ListeDesBoats, Boat);
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

Sens SensAleatoire(Sens A, Sens B)
{
	int i = rand()%2;
	if (i%2==0) 
	{
			return A;
	}
	else{
			return B;
		}
}

void NewPositionBoat(Boat* Boat)
{
	Boat->posX = PositionFutureBoat(Boat)->posX;
	Boat->posY = PositionFutureBoat(Boat)->posY;
}
	
void NewBoatSens(Boat* Boat, char ** MatriceDecision, BoatList *ListeDesBoats)
{
	switch(MatriceDecision[Boat->posX][Boat->posY])
	{
	case 'd':
		Boat->Sens = DROITE; break;
	case 'h':
		Boat->Sens = HAUT; break;
	case 'b':
		Boat->Sens = BAS; break;
	case 'g':
		Boat->Sens = GAUCHE; break;
	case 'x':
		Boat->Sens = SensAleatoire(GAUCHE,HAUT); break;
	case 'y':
		Boat->Sens = SensAleatoire(DROITE,BAS); break;
	case 'E':
		BoatEater(&ListeDesBoats,Boat);
	}
}

void RoulementBoatsPosition(char** MatriceDecision, BoatList **List)
{
	BoatList *tmp;
	tmp = *List;
	while (tmp != NULL)
		{	
			NewBoatSens(tmp->Boat,MatriceDecision, *List); //On actualise la Direction du Boat
			if(MatriceDecision[PositionFutureBoat(tmp->Boat)->posX][PositionFutureBoat(tmp->Boat)->posY]!='L') //On décrete qu'un bateau est representé par un L sur la MatriceDecision
			{
				MatriceDecision[tmp->Boat->posX][tmp->Boat->posY]=tmp->Boat->CaseDecision; //La ou le bateau etait devient de l'eau (place libre)
				NewPositionBoat(tmp->Boat); //On actualise la position du bateau dans la structure 
				tmp->Boat->CaseDecision = MatriceDecision[tmp->Boat->posX][tmp->Boat->posY]; //On recupere la case de decision pour la mettre dans la struct
				MatriceDecision[tmp->Boat->posX][tmp->Boat->posY]='L'; //On actualise la MatriceDecision pour signaler qu'un Boat se trouve maintenant a cette position
				//ON PEUT PRINTF LE BOAT ICI EN SOIT
				tmp = tmp->next;
			}
			else 
			{
				//PRINTF LE BOAT A SA MEME POSITION
				tmp = tmp->next;
			}
		}
}

Coordonnees* PositionFutureBoat(Boat* Boat)
{
	Coordonnees* Coordonnees = NULL;
	switch(Boat->Sens) 
	{
		case HAUT: 
			Coordonnees->posX = Boat->posX;
			Coordonnees->posY = (Boat->posY)+1;
			return Coordonnees;
		case DROITE: 
			Coordonnees->posX=(Boat->posX)+1;
			Coordonnees->posY=Boat->posY;
			return Coordonnees;
		case GAUCHE: 
			Coordonnees->posX=(Boat->posX)-1;
			Coordonnees->posY=Boat->posY;
			return Coordonnees;
		default: 
			Coordonnees->posX=Boat->posX;
			Coordonnees->posY=(Boat->posY)-1;
			return Coordonnees;
	}
}



