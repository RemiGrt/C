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

int main()
{

    // Declare variables and structures
	int i;
	
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
	char bufout[10], bufin[10];
	
    // Open the highest available serial port number
    fprintf(stderr, "Opening serial port...");
    hSerial = CreateFile(
                "\\\\.\\COM25", GENERIC_READ|GENERIC_WRITE, 0, NULL,
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
 
    for (i=0;i<10;i++)
	{
		bufout[0]='A';
		writeSerial(hSerial,bufout,1);
		readSerial(hSerial,bufin,1);
		printf("%c\n",bufin[0]);
		sleep(1);
		bufout[0]='E';
		writeSerial(hSerial,bufout,1);
		readSerial(hSerial,bufin,1);
		printf("%c\n",bufin[0]);
		sleep(1);
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