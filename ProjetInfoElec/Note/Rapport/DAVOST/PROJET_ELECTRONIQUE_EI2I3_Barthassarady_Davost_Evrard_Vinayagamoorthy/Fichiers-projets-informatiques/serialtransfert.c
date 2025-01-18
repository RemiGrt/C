#include <windows.h>
#include <stdio.h>

char serialname[100];
char binfile[100];

int readSerial(HANDLE hSerial,char *buf,int bytes_to_read)
{
    DWORD total_bytes_read=0;     
    DWORD bytes_read;              // on lit les octets 

    while (total_bytes_read<bytes_to_read) // tant qu'on a pas lu le nombre de octets voulue on continue de lire
    {
        ReadFile(hSerial, buf+total_bytes_read, bytes_to_read-total_bytes_read, &bytes_read, NULL);
        total_bytes_read+=bytes_read; 		 // ajoute 1 aux nombre de octets lues
        //printf("readSerial bytes_to_read=%d total_bytes_read=%d bytes_read=%d\n",bytes_to_read,total_bytes_read, bytes_read);
    }
    //printf("Sortie readSerial\n");
}

int writeSerial(HANDLE hSerial,char *buf,int bytes_to_write)
{
    DWORD total_bytes_written=0;
    DWORD bytes_written;   // on ecrit les octets

    while (total_bytes_written<bytes_to_write)  // tant qu'on a pas ecrit le nombre de octets voulue on continue de d'ecrire
    {
        WriteFile(hSerial, buf+total_bytes_written, bytes_to_write-total_bytes_written, &bytes_written, NULL);
        total_bytes_written+=bytes_written;        // ajoute 1 aux nombre de octets ecris
        //printf("writeSerial total_bytes_written=%d bytes_written=%d\n",total_bytes_written, bytes_written);
    }
    //printf("Sortie writeSerial\n");
}

 
void readAssembly(HANDLE hSerial,FILE *fin)
{
    int nbinst;  
    int i;
    int pc,v; // v = instruction , pc programme counter 
    // Define the five bytes to send ("hello")
    char bytes_to_send[10];   // octets a envoyer , un caratere = 1 octets
    char bytes_to_read[10];     // octets a lire , un caratere = 1 octets
	char line[100];
 // fin = fichier input
    fgets(line,100,fin);				// on lit la premiere ligne qui contient le nombre d'instructions,on lit les 100 caratere de la ligne et les ranges dans un tableau 'line'
    sscanf(line,"%d",&nbinst);			// lit le 1er nombre dans la ligne (ce nombre represente le nombre d'instructions) et le met met dans le int nbinst
    sprintf(bytes_to_send,"%d@",nbinst); // range dans le tableau bytes_to_send "%d@",   bytes_to_read[0] = 'la valeur de nbinst' ,  bytes_to_read[1] = '@'
    printf("strlen=%d bytes_to_send=%s\n",strlen(bytes_to_send),bytes_to_send);
	// on affiche la longueur de bytes_to_send et on affiche le chaine de caractere totale comprise dans le tableau
   

   //writeSerial(hSerial, bytes_to_send, strlen(bytes_to_send));
    //readSerial(hSerial, bytes_to_read, strlen(bytes_to_send));
    //bytes_to_read[strlen(bytes_to_send)]='\0';

    for (i=0;i<nbinst;i++)  // boucle for de 0 aux nombres d'instructions on fait ca pour toutes les instructions
    {
        fgets(line,100,fin); //on lit chaque ligne et on range les carateres dans le tableau ligne
        sscanf(line,"%d:%d",&pc,&v); // on recupere les deux 1er carateres rencontré, le premier ce met dans pc (programme counter) et le 2eme dans v (instruction)
		
        sprintf(bytes_to_send,"%d:%d@",pc,v);  							 // on met les valeurs de pc et v dans le tableau bytes_to_send donc le programme counter et l'instruction
        printf("strlen=%d bytes_to_send=%s\n",strlen(bytes_to_send),bytes_to_send  // verification de la longueur et des caracteres dans la chaine
        writeSerial(hSerial, bytes_to_send, strlen(bytes_to_send));  	 // on envoie les instructions via la liaison serie du pc vers le uC
        readSerial(hSerial, bytes_to_read, strlen(bytes_to_send));   	// // On lit les instructions pour pouvoir afficher et verifier qu4on a bien ecrit ce qu'on veut
        bytes_to_read[strlen(bytes_to_send)]='\0';			 			// On rajoute le caractere de fin a la fin du tableau bytes_to_read, qui est de la taille de bytes_to_send pour pouvoir printf. 		
        printf("%s\n",bytes_to_read);	 								// On affiche ce qu'on lit
    }
	bytes_to_send[0]='R';												// On met R dans bytes_to_send,  ce qui signifie qu'on a fini la communication
    writeSerial(hSerial, bytes_to_send, 1);								// On envoit le R pour dire que la communication est fini
    readSerial(hSerial, bytes_to_read, 1);								// On lit le R pour pouvoir afficher et verifier qu4on a bien ecrit ce qu'on veut
    bytes_to_read[1]='\0';													// ajout caratere nll pour printf
    printf("%s\n",bytes_to_read);										// verification du R
} 


int main(int argc,char **argv)
{
    // Declare variables and structures
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
 
	sprintf(serialname,"\\\\.\\%s",argv[1]);
	
    // Open the highest available serial port number
    fprintf(stderr, "Opening serial port...");
    hSerial = CreateFile(
//                "\\\\.\\COM26", GENERIC_READ|GENERIC_WRITE, 0, NULL,
                serialname, GENERIC_READ|GENERIC_WRITE, 0, NULL,
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
 
    FILE *fin=fopen(argv[2],"r");
    readAssembly(hSerial,fin);

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