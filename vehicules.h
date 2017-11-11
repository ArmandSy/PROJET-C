#include "librairies.h"
#define FEU_EST_ROUGE 'f'
#define CAR_IS_HERE 'c'


enum type	// Enumeration des differents types de vehicules
{
	Jaguar,
	Peugeot,
	Fiat,
	Porsche,
	Ferrari,
	Batmobile,
	Renault,
};

typedef enum type type;

enum Carburant	// Enumeration des differents etats du carburant pour un vehicule
{
	FAIBLE,
	PLEIN,
};

typedef enum Carburant Carburant;

enum Direction // Enumeration des directions possibles pour une entité
{
	NORD,
	EST,
	OUEST,
	SUD,
};

typedef enum Direction Direction;

typedef struct Position
{
	int posX;
	int posY;
			
} Position;

	typedef struct Vehicule
{
	Direction Direction;
	int posX;
	int posY;
	int Compteur;
	int vitesse;
	char custom;
	char CaseDecision;
	Carburant Carburant;		
} Vehicule;

	typedef struct Helicoptere
{
	int posX;
	int posY;
	char axe;
} Helicoptere;


	typedef struct Tramway
{
	int posX;
	int posY;
	int vitesse;
	char CaseDecision;
	Direction Direction;

} Tramway;

typedef struct TramwayList // Liste chainee de tramways pour la gestion du trafic
{
	Tramway* Tramway;
	struct TramwayList *next;
} TramwayList;


typedef struct VehiculeList // Liste chainee de vehicules pour la gestion du trafic
{
	Vehicule* Vehicule;
	struct VehiculeList *next;
} VehiculeList;

typedef struct HelicoptereList // Liste chainee d'helicopteres pour la gestion du trafic
{
	Helicoptere* Helicoptere;
	struct HelicoptereList *next;
} HelicoptereList;



Position* positionFuture(Vehicule* vehicule); //Fonction renvoyant un struct Position (qui sera la position de vehicule à la frame suivante) en fonction de sa Direction

VehiculeList* vehiculeEater(VehiculeList **List, Vehicule* Vehicule); //Fonction ayant pour but de supprimer de la liste VehiculeList les Vehicules sortant de la map. L'appeler lorsque PositionFuture(Vehicule) renvoit une position dont au moins une coordonnée est hors de la map

void appendVehiculeList(VehiculeList **List, Vehicule* Vehicule); //Fonction permettant d'ajouter un Vehicule à la liste des Vehicules (à appeler après le Spawner)

void vehiculeSpawner(int posX, int posY, Direction Direction, Carburant Carburant, char a, char** MatriceDecision, VehiculeList** ListeDesVehicules); // Spawner de Vehicules

void visualiserVehiculeList(VehiculeList *List); //permet de visualiser une liste de vehicules (affiche les positions de ces vehicules)

void setNewVehiculeDirection(Vehicule* Vehicule, char ** MatriceDecision, VehiculeList *ListeDesVehicules); //Fonction determinant la direction future de la voiture en fonction de la case sur laquelle elle se trouve (carrefour, ou route) /!\ Etablir un code permettant de faire la disjonction de cas de cette fonction

Direction directionAleatoire(Direction A, Direction B);

void placeTerminale(int posX, int posY); //Fonction permettant de s'éviter la syntaxe trop lourde du placement du curseur dans le terminal

void setNewPositionVehicule(Vehicule* vehicule); //Met a jour la position de la voiture dans sa struct

void roulementVehiculesPosition(char** MatriceDecision, VehiculeList** List); //Actualise la position des vehicules

Vehicule* oldVehiculeSpawner(int posX, int posY, Direction Direction); // Ancienne fonction pour tester un truc

int Obstacle(char** MatriceDecision, int i, int j);

void affichageVehicule(Vehicule* V); //Fonction d'affichage de Vehicule

char AleatoireCustomVehicule(); // Renvoie un skin de vehicule aléatoirement

void helicoptereSpawner(int posX, int posY,char axe, HelicoptereList** ListeDesHelicopteres); //Spawner d'Helicoptere

void roulementHelicopteresPosition(char** MatriceDecision, HelicoptereList** ListeDesHelicopteres); // Fait avancer tous les Helicopteres d'une Liste D'helicopteres

void appendHelicoptereList(HelicoptereList** ListeDesHelicopteres, Helicoptere* Helico); // Ajoute un helicoptere a Une Liste d'helicopteres

HelicoptereList* helicoptereEater(HelicoptereList **List, Helicoptere* Helicoptere); // Fait disparaitre et désalloue dynamiquement un helicoptere

void tramwaySpawner(int posX, int posY, Direction Direction, TramwayList** ListeDesTramways); //Fait apparaitre un Tramway (Spawner)

void appendTramwayList(TramwayList** ListeDesTramways, Tramway* Tram); // Fonction ajoutant un wagon de Tramway à une Liste de Tramways

TramwayList* tramwayEater(TramwayList **List, Tramway* Tramway); // Eater de Tramway

void affichageTramway(Tramway* Tram); // Affiche un wagon de Tramway

void roulementTramwaysPosition(char** MatriceDecision, TramwayList** ListeDesTramways); // Fait avancer tous les Tramways présents dans la ListeDesTramways

void setNewTramwayDirection(Tramway* Tramway, char ** MatriceDecision, TramwayList *ListeDesTramways); // Met a jour la position du Tramway dans sa structure

Position* positionFutureTramway(Tramway* Tramway); // Renvoit la position future d'un wagon de Tramway

int ObstacleTramway(char ** MatriceDecision, int i, int j); //Fonction faisant la disjontion de cas pour le Tramway afin de rendre roulementTramwaysPosition plus lisible