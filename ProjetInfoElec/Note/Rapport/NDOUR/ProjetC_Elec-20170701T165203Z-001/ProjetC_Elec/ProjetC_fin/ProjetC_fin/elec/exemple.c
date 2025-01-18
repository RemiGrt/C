/*
 * Nanomaître 2015
 * Programme de pilotage de deux moteurs, en direction et puissance
 * moteur 1 piloté par un bouton poussoir
 * sens unique, valeurs : 0, 25, 50, 75, 100 % de la puissance
 * moteur 2 piloté par un potentiomètre
 * double sens.
 * potentiomètre au centre : arrêt
 * potentiomètre à gauche sens -1
 * potentiomètre à droite sens 1
 * puissance en fonction de la position du potentiomètre
 * par rapport à sa valeur centrale
 * Affichage sur moniteur série pour contrôle.
 */
int pin1Moteur1=12; //pin de commande moteur 1
int pin2Moteur1=8; // pin de commande moteur 1
int pinPMoteur1=11;// pin PWM moteur 1
int pin1Moteur2=2; // pin de commande moteur 2
int pin2Moteur2=4; // pin de commande moteur 2
int pinPMoteur2=5; // pin PWM moteur 2
int pinBouton=7; //pin du bouton poussoir en mode INPUT_PULLUP
int pinPot=A0; //pin du potentiomètre
int vitesseM1=0; //variable de pourcentage de vitesse pour moteur 1
int sensM1=1; //variable de sens pour moteur 1
int vitesseM2=0; //variable de pourcentage de vitesse pour moteur 2
int sensM2=1; //variable de sens pour moteur 2

void setup() {
  Serial.begin(9600); //initialise la communication série
  pinMode(pin1Moteur1,OUTPUT);
  pinMode(pin2Moteur1,OUTPUT);
  pinMode(pinPMoteur1,OUTPUT);
  pinMode(pin1Moteur2,OUTPUT);
  pinMode(pin2Moteur2,OUTPUT);
  pinMode(pinPMoteur2,OUTPUT);
  pinMode(pinBouton,INPUT_PULLUP); //pinBouton en mode INPUT_PULLUP
}

void loop() {
  //gestion du moteur 1 avec le bouton
  if (!digitalRead(pinBouton)){// test d'appui du bouton (mode inversé car INPUT_PULLUP)
    vitesseM1+=25; // on ajoute 25 à la vitesse
    if (vitesseM1>100) // si on dépasse 100
      vitesseM1=0;//on revient à 0
    delay(200); //délai pour éviter les répétitions d'appui
  }
  //gestion du moteur 2 avec le potentiomètre
  int valeur=map(analogRead(pinPot),0,1023,-100,100); // on mappe la valeur lue entre -100 et 100
  if (valeur>=-2 && valeur<=2){//on teste si le potentiomètre est au centre
    vitesseM2=0; // on met la vitesse à 0
    sensM2=0; // on actionne la commande d'arrêt
  }
  else if (valeur<-2){// on teste si la valeur est négative
    vitesseM2=-valeur; //on met à jour la vitesse (en positif)
    sensM2=-1; //on indique le sens
  }
  else if (valeur>2){// on teste si la valeur est positive
    vitesseM2=valeur; //on met à jour la vitesse
    sensM2=1; // on indique le sens
  }
  //appel des commandes de moteurs
  actionMoteur(1,sensM1,vitesseM1); //commande pour moteur 1
  actionMoteur(2,sensM2,vitesseM2); //commande pour moteur 2
  Serial.println(); //saut de ligne
}

//fonction de gestion d'un moteur
void actionMoteur(int moteur,int sens,int pourcentage){
  int pin1,etat1,pin2,etat2,pinP,puissance; //variable de la fonction
  //test numéro du moteur
  if (moteur==1){
    pin1=pin1Moteur1;
    pin2=pin2Moteur1;
    pinP=pinPMoteur1;
  }
  else {
    pin1=pin1Moteur2;
    pin2=pin2Moteur2;
    pinP=pinPMoteur2;
  }
  //test sens du moteur 1,-1 (sens contrainre) ou tout autre valeur (stoppe le moteur)
  if (sens==1){
    etat1=1;
    etat2=0;
  }
  else if (sens==-1){
    etat1=0;
    etat2=1;
  }
  else {
    etat1=0;
    etat2=0;
  }
  puissance=map(pourcentage,0,100,0,255);
  analogWrite(pinP,puissance);
  digitalWrite(pin1,etat1);
  digitalWrite(pin2,etat2);
  //affichage sur le moniteur série (facultatif)
  Serial.print("Moteur : ");
  Serial.print(moteur);
  if (sens==-1 || sens==1){
    Serial.print(" sens : ");
    Serial.print(sens);
  }
  else {
    Serial.print(" ! stop ! ");
  }
  Serial.print(" puissance : ");
  Serial.print(pourcentage);
  Serial.print("%\t");
}
