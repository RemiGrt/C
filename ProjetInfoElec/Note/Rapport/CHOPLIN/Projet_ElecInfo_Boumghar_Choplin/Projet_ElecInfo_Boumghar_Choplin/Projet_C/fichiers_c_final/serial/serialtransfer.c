#include <windows.h>
#include <stdio.h>

/*! \file serialtransfer.c
 *
 * \details
 * 
 *
 * \section Présentation
 * 
 * Ce programme permet d'envoyer le bytecode, fichier safe.bin par liaison série comme par exemple à un microcontroleur.
 * Pour la réalisation du projet ce programme nous a entièrement été donné. *
 *
 * Ce programme fonctionne en 3 parties :
 * 	- 1ere partie: on parcourt le fichier de bytecode
 *  - 2ème partie: on envoie une ligne du fichier bytecode
 *  - 3ème partie: on attend de recevoir confirmation de la réception des données, le destinataire doit renvoyer un message de la même taille.
 *
 *
 * \section Compilation
 * Le fichier contient le header windows.h il faut donc l'utiliser sur windows par exemple nous utiliserons codeblocks
 *
 * \section Liste_des_fonctions:
 *  - int readSerial(HANDLE hSerial,char *buf,int bytes_to_read)
 *  - int writeSerial(HANDLE hSerial,char *buf,int bytes_to_write)
 *  - void readAssembly(HANDLE hSerial,FILE *fin)
*/



/*! \brief La fonction readSerial(HANDLE hSerial,char *buf,int bytes_to_read) est appelé
// après l'envoie des données, elle réceptionne la confirmation de lecture des données envoyées.
// Par exemple pour le microcontroleur lors de chaque caractère reçus on renvoie ce même caractère afin de le valider.
// Tant que la confirmation de lecture n'est pas reçue le programme attend.
*/

int readSerial(HANDLE hSerial,char *buf,int bytes_to_read)
{
    DWORD total_bytes_read=0;
    DWORD bytes_read;

    while (total_bytes_read<bytes_to_read)
    {
        ReadFile(hSerial, buf+total_bytes_read, bytes_to_read-total_bytes_read, &bytes_read, NULL); //lecture de la liaison série
        total_bytes_read+=bytes_read;
        printf("readSerial bytes_to_read=%d total_bytes_read=%d bytes_read=%d\n",bytes_to_read,total_bytes_read, bytes_read);
    }
    printf("Sortie readSerial\n");
}


/*! \brief La fonction writeSerial(HANDLE hSerial,char *buf,int bytes_to_write) permet
// d'écrire sur liaison série. Les caractères du fichier bytecode sont envoyés ici un par un.
// Jusqu'à ce que tout les caractères de la lignes sont envoyés. On envoie un '@' en plus pour indiquer
// au destinataire que tous les caractères ont été envoyés.
*/

int writeSerial(HANDLE hSerial,char *buf,int bytes_to_write)
{
    DWORD total_bytes_written=0;
    DWORD bytes_written;

    while (total_bytes_written<bytes_to_write)
    {
        WriteFile(hSerial, buf+total_bytes_written, bytes_to_write-total_bytes_written, &bytes_written, NULL); //écriture sur la liaison série
        total_bytes_written+=bytes_written;
        printf("writeSerial total_bytes_written=%d bytes_written=%d\n",total_bytes_written, bytes_written);
    }
    printf("Sortie writeSerial\n");
}


/*! \brief La fonction readAssembly(HANDLE hSerial,FILE *fin) permet de parcourir
// le fichier d'opcode. Pour chaque ligne à envoyer on appelle la fonction qui permet
// d'écrire sur la liaison série puis on attend la confirmation de lecture.
// 
*/

void readAssembly(HANDLE hSerial,FILE *fin)
{
    int nbinst;
    char line[100];
    int i;
    int pc,v;
    // Define the five bytes to send ("hello")
    char bytes_to_send[10];
    char bytes_to_read[10];

    fgets(line,100,fin); //on récupère la ligne du fichier
    sscanf(line,"%d",&nbinst); //la première ligne correspond au nombre d'instructions
    sprintf(bytes_to_send,"%d@",nbinst); //on place cette valeur dans les byte à envoyer
    printf("strlen=%d bytes_to_send=%s\n",strlen(bytes_to_send),bytes_to_send); 
    writeSerial(hSerial, bytes_to_send, strlen(bytes_to_send)); //on envoie
    readSerial(hSerial, bytes_to_read, strlen(bytes_to_send)); //on attend la confirmation de lecture
    bytes_to_read[strlen(bytes_to_send)]='\0';

	//on réalise la même opération pour chaque ligne du fichier .bin à envoyer
    for (i=0;i<nbinst;i++)
    {
        fgets(line,100,fin);
        sscanf(line,"%d : %d",&pc,&v);

        sprintf(bytes_to_send,"%d:%d@",pc,v);
        printf("strlen=%d bytes_to_send=%s\n",strlen(bytes_to_send),bytes_to_send);
        writeSerial(hSerial, bytes_to_send, strlen(bytes_to_send));
        readSerial(hSerial, bytes_to_read, strlen(bytes_to_send));
        bytes_to_read[strlen(bytes_to_send)]='\0';
        printf("%s\n",bytes_to_read);
    }
}


int main()
{

    // Declare variables and structures
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};

    // Open the highest available serial port number
    fprintf(stderr, "Opening serial port...");
    hSerial = CreateFile(
                "\\\\.\\COM4", GENERIC_READ|GENERIC_WRITE, 0, NULL,
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

    FILE *fin=fopen("safe.bin","r");
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
