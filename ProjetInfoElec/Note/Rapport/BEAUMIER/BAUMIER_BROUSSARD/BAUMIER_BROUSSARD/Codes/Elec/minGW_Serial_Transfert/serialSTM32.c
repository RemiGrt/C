#include <windows.h>
#include <stdlib.h>
#include <stdio.h>


char SerialNumber[200];
int readSerial(HANDLE hSerial,char *buf,int bytes_to_read)
{
    DWORD total_bytes_read=0;
    DWORD bytes_read;

    while (total_bytes_read<bytes_to_read)
    {
        ReadFile(hSerial, buf+total_bytes_read, bytes_to_read-total_bytes_read, &bytes_read, NULL);
        total_bytes_read+=bytes_read;
        //printf("readSerial bytes_to_read=%d total_bytes_read=%d bytes_read=%d\n",bytes_to_read,total_bytes_read, bytes_read);
    }
    //printf("Sortie readSerial\n");
}

int writeSerial(HANDLE hSerial,char *buf,int bytes_to_write)
{
    DWORD total_bytes_written=0;
    DWORD bytes_written;

    while (total_bytes_written<bytes_to_write)
    {
        WriteFile(hSerial, buf+total_bytes_written, bytes_to_write-total_bytes_written, &bytes_written, NULL);
        total_bytes_written+=bytes_written;
        //printf("writeSerial total_bytes_written=%d bytes_written=%d\n",total_bytes_written, bytes_written);
    }
    //printf("Sortie writeSerial\n");
}
 
void readAssembly(HANDLE hSerial,FILE *fin)
{
    int nbinst;
    char line[100];
    int i;
    int pc,v;

    char bytes_to_send[10];
    char bytes_to_read[10];
	char Taille_Retour[10];
	
	// Envoi d'un caractère d'initialisation de la transmission.
	// Envoyé : '!' / Attendu : '?'
	writeSerial(hSerial, "?", 1);
	readSerial(hSerial, bytes_to_read, 1);
	bytes_to_read[1]='\0';
	printf("Acquittement : %s\n",bytes_to_read);
	
	if (!strcmp("!",bytes_to_read))
	{
		// Envoi du nombre d'instructions à executer
		// Envoyé : nbinst / Attendu : "START"
		fgets(line,100,fin);
		sscanf(line,"%d",&nbinst);
		sprintf(bytes_to_send,"%d@",nbinst);
		printf("Nombre d'Octets =%d --- Octets Transmis = %s\n",strlen(bytes_to_send),bytes_to_send);
		
		writeSerial(hSerial, bytes_to_send, strlen(bytes_to_send));
		readSerial(hSerial, bytes_to_read, 5);
		bytes_to_read[5]='\0';
		printf("Acquittement : %s\n\n",bytes_to_read);

		// Envoi des instructions une par une 
		// Envoyé : Instruction/ Attendu : Instruction
		for (i=0;i<nbinst;i++)
		{
			fgets(line,100,fin);
			sscanf(line,"%d:%d",&pc,&v);
			
			sprintf(Taille_Retour,"%d",v);
			sprintf(bytes_to_send,"%d:%d@",pc,v);
			
			printf("Nombre d'Octets =%d --- Octets Transmis = %s\n",strlen(bytes_to_send),bytes_to_send);
			writeSerial(hSerial, bytes_to_send, strlen(bytes_to_send));
			
			// vérification de l'instruction envoyée : le MCC renvoie l'instruction reçue, en tant qu'acquittement de réception.
			readSerial(hSerial, bytes_to_read, strlen(Taille_Retour));
			bytes_to_read[strlen(Taille_Retour)]='\0';
			printf("Acquittement : %s\n",bytes_to_read);
			if (strcmp(Taille_Retour,bytes_to_read))
			{
				printf("ERREUR : Mauvaise reception de l'instruction\n");
				return;
			}
		}
		readSerial(hSerial, bytes_to_read, 7);
		bytes_to_read[7]='\0';
		printf("Acquittement : %s\n",bytes_to_read);
		// Si tout s'est bien passé, on peut indiquer un OK
		if (!strcmp("PRGM OK",bytes_to_read))
			printf("Chargement du programme OK \n\n");
		else
			printf("ERREUR : Echec de chargement du programme\n");
	}
	else
	{
		printf("ERREUR : Echec de chargement du programme\n");
	}
} 


int main(int argc, char *argv[])
{

    // Declare variables and structures
	char Reponse_User ='\0';
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
	sprintf(SerialNumber,"\\\\.\\%s",argv[1]);    
	char bytes_to_read[10];
	
	// Vérification des arguments passés en paramètre de l'exécutable
	if(argc != 3)
	{
		printf ("ERREUR : Nombre de parametres insuffisants ! \n");
		printf ("Commande : ./My_Serial <COMX> <fichier.asm> \n");
		return EXIT_FAILURE;
	}  
	
    // Open the highest available serial port number
    fprintf(stderr, "Opening serial port...");
    hSerial = CreateFile(
                SerialNumber, GENERIC_READ|GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if (hSerial == INVALID_HANDLE_VALUE)
    {
            fprintf(stderr, "Error\n");
            return 1;
    }
    else fprintf(stderr, "OK\n");
     
    // Set device parameters (38400 baud, 1 start bit,
    // 1 stop bit, no parity)
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (GetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error getting device state\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if(SetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error setting device parameters\n");
        CloseHandle(hSerial);
        return 1;
    }
 
    // Set COM port timeout settings
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if(SetCommTimeouts(hSerial, &timeouts) == 0)
    {
        fprintf(stderr, "Error setting timeouts\n");
        CloseHandle(hSerial);
        return 1;
    }
	printf("Activer le mode DEBUG ?[y/n]");
	scanf("%c",&Reponse_User);
	// argv[2] : nom_fichier.bin
    FILE *fin=fopen(argv[2],"r");
    readAssembly(hSerial,fin);
	
	// Passage en mode lecture
	if (Reponse_User == 'y' ||Reponse_User == 'Y')
	{
		while(1)
		{
				readSerial(hSerial, bytes_to_read, 1);
				bytes_to_read[1]='\0';
				printf("%s",bytes_to_read);			
		}
	}
	
    // Close serial port
    fprintf(stderr, "Closing serial port...");
    if (CloseHandle(hSerial) == 0)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }
    fprintf(stderr, "OK\n");
 
    // exit normally    
	return 0;
}