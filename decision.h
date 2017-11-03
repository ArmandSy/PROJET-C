#include "librairies.h"

#define NBC 194 
#define NBL 65

char** MatrixInit(); //Initialise une Matrice de taille (NBC,NBL)

void TextToMatrix(char** Matrice, char* nomdufichiertexte); //Initialise et renvoit une Matrice remplie du fichier decision.txt

void ShowMatrix(char** Matrice); //Fonction affichant une Matrice de taille(NBL,NBC)

void RoulementFeuxDecision(char ** MATRIX); // Effectue un roulement des feux sur le tableau (ferme/ouvre les portes) A appeler avec RoulementFeux qui porte sur la liste des feux

