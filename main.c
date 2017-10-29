#include "librairies.h"
#include "affichage.h"
#include "boats.h"
#include "trafficlights.h"
#include "vehicules.h"

int main()
{
	/* TESTS RELATIFS à L'AFFICHAGE
	system("clear");	
	affichage();
	clock_t temps;
	Chrono= temps/CLOCKS_PER_SEC;
	TrafficLightList TrafficLightList='NULL'; 
	void InitialisationTrafficLights();
	*/

/* TESTS RELATIFS AUX FEUX

TrafficLightList* Liste=NULL;
TrafficLight* FEU1 = CreateTrafficLight(4, 5, VERT);
TrafficLight* FEU2 = CreateTrafficLight(3, 6, ROUGE);
AppendList(&Liste, FEU1);
AppendList(&Liste, FEU2);
VisualiserTrafficLightList(Liste);	
Roulement_feux(Liste);
VisualiserTrafficLightList(Liste);

*/

// TESTS RELATIFS AUX VEHICULES 

/*
VehiculeList* Liste = NULL;
Vehicule* Vehicule1 = VehiculeSpawner(4,3);
Vehicule* Vehicule2 = VehiculeSpawner(6,7);

AppendVehiculeList(&Liste,Vehicule1);
AppendVehiculeList(&Liste,Vehicule2);

printf("Visualisation de la liste remplie:\n");
VisualiserVehiculeList(Liste);
printf("On retire now Vehicule 1 puis on affiche la liste\n");
VehiculeEater(&Liste, Vehicule1);
VisualiserVehiculeList(Liste);
printf("fin du programme \n");
*/

//TESTS RELATIFS AUX BATEAUUUUUUUX

/*

BoatList* Liste = NULL;
Boat* Voilier = BoatSpawner(4,5,SUD);
Boat* Catamaran = BoatSpawner(8,9,EST);
AppendBoatList(&Liste,Catamaran);
AppendBoatList(&Liste,Voilier);
printf("On affiche la Liste qui a 2 elements \n");
void VisualiserBoatList(Liste);
BoatEater(&Liste, Catamaran);
printf("On affiche la liste qui n'a plus qu'un element);
VisualiserBoatList(Liste);
*/


	return 0;
}

