#include <windows.h>
#include <stdio.h>

char serialname[100];
char binfile[100];

int readSerial(HANDLE hSerial,char *buf,int bytes_to_read) // on r√©cup√®re le nb d'octests √† lire
{
    DWORD total_bytes_read=0;                       /*Mot de 8 octets*/
    DWORD bytes_read;                               /*Mots de 8 octets*/

    while (total_bytes_read<bytes_to_read) // tant que il y a encore des octects √† lire on boucle
    {
        ReadFile(hSerial, buf+total_bytes_read, bytes_to_read-total_bytes_read, &bytes_read, NULL); // on lit l'octet que l'on stock dans le buffer
        total_bytes_read+=bytes_read;  // on incr√©mente le nb d'octests √† lire
        //printf("readSerial bytes_to_read=%d total_bytes_read=%d bytes_read=%d\n",bytes_to_read,total_bytes_read, bytes_read);
    }
    //printf("Sortie readSerial\n");
}

int writeSerial(HANDLE hSerial,char *buf,int bytes_to_write) // on r√©cup√®re le nb d'octests √† √©crire
{
    DWORD total_bytes_written=0;
    DWORD bytes_written;

    while (total_bytes_written<bytes_to_write) // tant que il y a encore des octects √† envoyer on boucle
    {
        WriteFile(hSerial, buf+total_bytes_written, bytes_to_write-total_bytes_written, &bytes_written, NULL); // on √©crit l'octet √† partir du buffer
        total_bytes_written+=bytes_written; // on incr√©mente le nb d'octests √† √©crire
        //printf("writeSerial total_bytes_written=%d bytes_written=%d\n",total_bytes_written, bytes_written);
    }
    //printf("Sortie writeSerial\n");
}
 
void readAssembly(HANDLE hSerial,FILE *fin)
{
    int nbinst;
    int i;
    int pc,v;
    // Define the five bytes to send ("hello")
    char bytes_to_send[10]; // nb d'octets √† envoyer
    char bytes_to_read[10]; // nb d'octets √† lire
	char line[100]; // nombre de ligne d'instruction

    fgets(line,100,fin);            //Dans le document File Input onlit les 100 premiers caractËres de la premiËre ligne
    sscanf(line,"%d",&nbinst);      //ON lit le premier nombre de la chaine et on le place dans nbinst. C'est le nombre total d'instruction ‡ envoyer
    sprintf(bytes_to_send,"%d@",nbinst);    // On note dans le buffer bytes_to_send le nombre d'instruction totale
    printf("strlen=%d bytes_to_send=%s\n",strlen(bytes_to_send),bytes_to_send); //On donne ‡ l'utilisateur le nombre d'instruction ‡ envoyer pour un Èventuel dÈbug
    //writeSerial(hSerial, bytes_to_send, strlen(bytes_to_send));
    //readSerial(hSerial, bytes_to_read, strlen(bytes_to_send));
    //bytes_to_read[strlen(bytes_to_send)]='\0';

    for (i=0;i<nbinst;i++)                                                          // Dans cette boucle on envoie une ‡ une les instructions
    {
        fgets(line,100,fin);                                                        //On rÈcupËre les 100 premiers caractËre de la ligne 
        sscanf(line,"%d:%d",&pc,&v);                                                // On met ‡ jour pc (programme counter) et v (l'instruction)

        sprintf(bytes_to_send,"%d:%d@",pc,v);                                       //On Ècrit sur le buffer d'envoie le pc et v afin d'indiquer la place de l'instruction dans le code
        printf("strlen=%d bytes_to_send=%s\n",strlen(bytes_to_send),bytes_to_send); // On affiche ‡ l'utilisateur le pc et v de chaque instruction pour un Èventuel debug
        writeSerial(hSerial, bytes_to_send, strlen(bytes_to_send));                 // On envoie l'instruction
        readSerial(hSerial, bytes_to_read, strlen(bytes_to_send));                  // On lit la rÈponse du microcontrÙleur
        bytes_to_read[strlen(bytes_to_send)]='\0';                                  //ON rÈinitialise le tableau de lecture du buffer
        printf("%s\n",bytes_to_read);       ≤                                       //On affiche le buffer de lecture
    }
	bytes_to_send[0]='R';                                                           // On Ècrit R dans la premiËre case afin de spÈcifier au microcontrÙleur que la comunicdation est terminÈe.
    writeSerial(hSerial, bytes_to_send, 1);                                         // On envoie le R au microcontrÙleur pour signifier la fin de la comm
    readSerial(hSerial, bytes_to_read, 1);                                          // On attends une rÈponse de la part du microcontrÙleur
    bytes_to_read[1]='\0';                                                          //On rÈinitialise le tableau de buffer de lecteure en mettant son premier caractËre ‡ \0
    printf("%s\n",bytes_to_read);                                                   //On affiche la rÈponse du microcontrÙleur
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
