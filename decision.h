#include "librairies.h"

char** MATRIX_INIT(int NBC, int NBL); //Initialise une Matrice de taille (NBC,NBL)

void TEXT_TO_MATRIX(int NBC, int NBL, char** MATRIX); //Initialise et renvoit une Matrice remplie du fichier decision.txt

void AFFICHAGE_MATRIX(int NBC, int NBL, char** MATRIX); //Fonction affichant une Matrice de taille(NBL,NBC)

char swap(char); // ouvre ou ferme "la porte" (feu) sur le char **

void RoulementFeuxDecision(int NBC, int NBL, char ** MATRIX); // Effectue un roulement des feux sur le tableau (ferme/ouvre les portes) A appeler avec RoulementFeux qui porte sur la liste des feux

