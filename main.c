#include "librairies.h"
#include "affichage.h"
#include "boats.h"
#include "trafficlights.h"
#include "vehicules.h"
#include "decision.h"

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

// TESTS RELATIFS AUX FEUX
/*
TrafficLightList* Liste=NULL;
TrafficLight* FEU1 = createTrafficLight(4, 5, VERT);
TrafficLight* FEU2 = createTrafficLight(3, 6, ROUGE);
appendTrafficLightList(&Liste, FEU1);
appendTrafficLightList(&Liste, FEU2);
visualiserTrafficLightList(Liste);	
roulement_feux(Liste);
visualiserTrafficLightList(Liste);

OK

*/


// TESTS RELATIFS AUX VEHICULES 
/*

VehiculeList* Liste = NULL;
Vehicule* Vehicule1 = oldVehiculeSpawner(4,3,NORD);
Vehicule* Vehicule2 = oldVehiculeSpawner(6,7,SUD);

appendVehiculeList(&Liste,Vehicule1);
appendVehiculeList(&Liste,Vehicule2);

printf("Visualisation de la liste remplie:\n");
visualiserVehiculeList(Liste);
printf("On retire now Vehicule 1 puis on affiche la liste\n");
vehiculeEater(&Liste, Vehicule1);
visualiserVehiculeList(Liste);
printf("fin du programme \n");

OK

*/


//TESTS RELATIFS AUX BATEAUUUUUUUX


/*
BoatList* Liste = NULL;
Boat* Voilier = boatSpawner(4,5,SUD);
Boat* Catamaran = oatSpawner(8,9,EST);
appendBoatList(&Liste,Catamaran);
appendBoatList(&Liste,Voilier);
printf("On affiche la Liste qui a 2 elements \n");
visualiserBoatList(Liste);
boatEater(&Liste, Catamaran);
printf("On affiche la liste qui n'a plus qu'un element\n");
visualiserBoatList(Liste);

OK

*/


//TESTS RELATIFS A LA DECISION

/*

char ** MatriceDecision = MatrixInit();

textToMatrix(MatriceDecision, "dec.txt");

showMatrix(MatriceDecision);

roulementFeuxDecision(MatriceDecision);

printf("\n\n\n\n");

showMatrix(MatriceDecision);

OK

*/




//TESTS RELATIFS AUX VEHICULES ET A LEURS MOUVEMENTS

/*

srand(time(NULL)); //Permet d'avoir une graine vraiment aleatoire, sinon directionAleatoire renvoit toujours la meme Direction

char ** MatriceDecision = matrixInit(NBC, NBL);

textToMatrix(MatriceDecision, "dec.txt");

showMatrix(MatriceDecision);

VehiculeList* ListeDesVehicules = NULL;

vehiculeSpawner(20, 193, OUEST, MatriceDecision, &ListeDesVehicules);

roulementVehiculesPosition(MatriceDecision, &ListeDesVehicules);

showMatrix(MatriceDecision);

OK FONCTIONNE ! Meme les virages (:

*/

//TESTS RELATIFS AUX BATEAUX ET A LEURS MOUVEMENTS

srand(time(NULL)); //Permet d'avoir une graine vraiment aleatoire, sinon directionAleatoire renvoit toujours la meme Direction

char ** MatriceDecision = matrixInit(NBC, NBL);

textToMatrix(MatriceDecision, "dec.txt");

showMatrix(MatriceDecision);

BoatList* ListeDesBoats = NULL;

boatSpawner(22, 1, DROITE, MatriceDecision, &ListeDesBoats);

/*
roulementBoatsPosition(MatriceDecision, &ListeDesBoats);

showMatrix(MatriceDecision);
*/

	return 0;
}

