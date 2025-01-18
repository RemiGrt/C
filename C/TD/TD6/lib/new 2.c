#include <Servo.h>
Servo myservo;  
int potpin = 0; 
int val;  
void setup()
{
  myservo.attach(9); 
}
void loop() 
{ 
  val = analogRead(potpin);           
  val = map(val, 0, 1023, 0, 180);
  myservo.write(val); 
  delay(15);
}


for(i=0;i<100;i++){
 if(i%3==0 || i%10==3)
  Serial.print(bpValue);
}


while(edge_detect(inputPin,true) == false){
	if(state == 1) state=0;
	else state=1;
	digitalWrite(state)
}

Sachant que l'on a définie:
#define A 0
#define B 1
#define C true
#define D

qu'affichera le programme suivant:

#if A==1
  Serial.println("Instruction1");
#endif

#if B!=1
  Serial.println("Instruction2");
#endif

#if C
  Serial.println("Instruction3");
#else
  Serial.println("Instruction4");
#endif

#ifdef B
  Serial.println("Instruction5");
#endif

#ifndef B
  Serial.println("Instruction6");
#endif

#ifndef D
  Serial.println("Instruction7");
#endif

#ifdef E
  Serial.println("Instruction8");
#else
  Serial.println("Instruction9");
#endif

B0100 & B1011
B0100 ^ ~(B0100)
B0011 | B1001

byte RESULT = B01000001;
byte activeMSB = B10000000;
RESULT |= activeMSB;

RESULT = B00000001;
Serial.print("INIT RESULT: "),Serial.println(RESULT, BIN);
for(int i=0; i<8; i++){
	RESULT = RESULT << 1;
	Serial.print("LEFT SHIFT: "),Serial.println(RESULT, BIN);
}


/* TP Arduino Meca du 07.11.2016
// Une instructions ou plusieurs instructions sont à placer en dessous des commentaires
// Ce sketch compte le nombre de mise sous tension ou de reset de la carte, grace à une variable
// stockée dans l'EEPROM
// Il affiche egalement prériodiquement des messages ainsi qu'un tableau de valeurs stockées en flash
*/
// Inclure la bibliotheque EEPROM

// definir addrNbrPowerUp, l'adresse en EEPROM du compteur de mise sous tension (ou reset)

// definir pinBp á 8

// definir baudRate à 115200

// definir un flag storeInFlash, conditionnant la mise en flash ou pas de certaine variable


// Déclare un tableau de constante de 10 int (16 bits)
// en flash si storeInFlash est à 1, en SRAM sinon
#if storeinflash

#else

#endif
// Déclarer NbrPowerUp (de type int)

// Définir une fonction initEEPROM prenant en argument une adresse de type uint8_t et initialisant le
// contenu de cette adresse à 0 (utiliser la fonction EEPROM.write(address, contenu))
void initEEPROM(uint8_t addr) {
  
}

void setup() {
  // Setup Serial link
  
  // Si debug est définie, afficher "Debug On" (ce message est déclaré en flash)
#ifdef debug
  
#endif
  // declare pinBP en input (utiliser pinMode(numeroPin, sens))
  pinMode(pinBp, INPUT);
  // si Bp est actif (utiliser digitalRead) on initiliase le compteur de mise sous tension/reset
  // Sinon, on l'incremente
  if ( ) {
    Serial.print("Init EEPROM..");
    initEEPROM(addrNbrPowerUp);
    Serial.println(" Done");
  } else {
    NbrPowerUp = EEPROM.read(addrNbrPowerUp) + 1;
    EEPROM.write(addrNbrPowerUp, NbrPowerUp);
    Serial.print("#Power Up:"), Serial.print(NbrPowerUp), Serial.println();
  }

}

void loop() {
  // lire chaque seconde les elements du tableau stocké en flash et les afficher
  for (int k = 0; k < 5; k++)
  {
    delay(500);
    if (storeinflash) {
      Serial.println(F("Message stored in Flash"));
      Serial.println(pgm_read_word(tabInt + k));
    }
    else {
      Serial.println(tabInt[k]);
    }
  }
}

for (k = 0; k < 5; k++)
{
	displayInt = pgm_read_word(tabInt + k);
	Serial.println(displayInt);
}
for(i=0; i<10;i++){
	if (i > 4){
		ledState = 1;
	} 
	else if ( i > 1 ){
		ledState = 0;
	} else {
		ledState = 1;
	}
	digitalWrite(ledPin, ledState);
	delay(100);
}

const byte ledPin = 13;
const byte interruptPin = 2;
byte state = LOW;
void setup() {
pinMode(ledPin, OUTPUT);
pinMode(interruptPin, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}
void loop() {
}
void blink() {
state = !state;
digitalWrite(ledPin, state);
}


Boolean edge_detect(int pin, boolean rise){
Int t0, t1 ;
T0 = digitalRead(pin) ;
Delay(100) ;
T1 = digitalRead(pin) ;
	if(rise == true){
		if (T0 == LOW && T1 == HIGH){
			return HIGH;
		} else {
			return LOW;
		}
} else {
		if (T0 == HIGH && T1 == LOW){
			return HIGH;
		} else {
			return LOW;
		}

}



}

