#include <windows.h>
#include <stdio.h>

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
    // Define the five bytes to send ("hello")
    char bytes_to_send[10];
    char bytes_to_read[10];

    fgets(line,100,fin);
    sscanf(line,"%d",&nbinst);
    sprintf(bytes_to_send,"%d@",nbinst);
    printf("strlen=%d bytes_to_send=%s\n",strlen(bytes_to_send),bytes_to_send);
    writeSerial(hSerial, bytes_to_send, strlen(bytes_to_send));
    readSerial(hSerial, bytes_to_read, strlen(bytes_to_send));
    bytes_to_read[strlen(bytes_to_send)]='\0';

    for (i=0;i<nbinst;i++)
    {
        fgets(line,100,fin);
        sscanf(line,"%d:%d",&pc,&v);

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
    char s[20]; //Sert à rentrer le port COM

    // Open the highest available serial port number
    fprintf(stderr, "Opening serial port...");
    sprintf(s,"\\\\.\\COM%d",argv[2]);
    hSerial = CreateFile(
                s, GENERIC_READ|GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

    /*hSerial = CreateFile(
                "\\\\.\\COM4", GENERIC_READ|GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );*/
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
 
    FILE *fin=fopen(argv[1],"r");
    //FILE *fin=fopen("safe.bin","r");
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
