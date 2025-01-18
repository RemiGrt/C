Auteurs : Thomas Broussard et Jeanne Baumier - ei2i-3

Le programme sur microcontrôleur peut être modifié pour pouvoir afficher des informations sur le terminal minGW.
Pour cela , il faut simplement modifier les define du fichier debug.h :
(Mettre à 1 pour activer l'option choisie)

DEBUG_TERMINAL : Affiche les instructions exécutées par le MCC
AFFICHAGE_GPIO_TERMINAL : Affiche les état des entrées/sorties du microcontrôleur sur le terminal
AFFICHAGE_STEP_GRAFCET : Affiche les variables liées au mécanisme du grafcet (Etapes, Appels, Réponses..)


Pour pouvoir téléverser un programme sur le microcontrôleur via la liaison série et minGW , voici la commande à exécuter : 

./serialSTM32.exe <COM> <prog.bin>

avec <COM> le numéro de port COM du MCC ( windows+pause => gestionnaire de périphérique ) exemple : COM5
avec <prog.bin> le fichier .bin à télécharger sur la carte
