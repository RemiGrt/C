#include <stdio.h>
#include <stdlib.h>
#define N 19
/* Lit le cylindre dans un fichier (ouvert)
la lecture se fait colonne par colonne (roue par roue)
Parmaètres :
- fichier: (FILE*) pointeur vers le fichier ouvert
- cylindre: (char [26][N]) cylindre de jefferson à lire*/
void litCylindre( FILE* fichier, char cylindre[26][N])
{
int i,j;
/* on lit le fichier roue par roue ! */
for( j=0; j<N; j++)
for( i=0; i<26; i++)
fscanf( fichier, "%c", &(cylindre[i][j]) );
}
/* Affiche le cylindre, ligne par ligne
Paramètres :
- cylindre: (char [26][N]) cylindre de jefferson à afficher*/
void afficheCylindre( char cylindre[26][N])
{
int i,j;
/* affichage du numéro de roue */
for( j=0; j<N; j++)
printf( "%3d", j );
printf("\n");
/* on affiche la cylindre, ligne par ligne */
for( i=0; i<26; i++)
{
for( j=0; j<N; j++)
printf( " %c", cylindre[i][j] );
printf("\n");
}
}
/* programme principal */
int main()
{
char cylindre[26][N];
FILE* fichier;
/* ouverture du fichier */
fichier = fopen("jefferson.txt","r");
if ( !fichier )
{
printf( "impossible d’ouvrir le fichier\n");
exit(1);
}
/* lecture de la cylindre */
litCylindre( fichier, cylindre);
/* affichage */
afficheCylindre( cylindre);
/* fermeture du fichier */
fclose( fichier);
return EXIT_SUCCESS;
}
