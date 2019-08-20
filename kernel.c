
#define ROWS 80
#define COLS 25
#define BKSP 0x08
#define RTRN 0x0D
#define CLR 0x20

 void printChar(chr);
char chr; 

 void clearScreen(void);

 void readString(line);
char line[ROWS];

extern char readChar(void);

extern int min( x , y);
int x; int y;

void killProcess(int process);
extern void setKernelDataSegment();
extern void restoreDataSegment();
extern void initializeProgram(int segment);
void makeTimerInterrupt();
void returnFromTimer(int segment, int sp);
void handleTimerInterrupt(int segment, int sp);
int activeProcesses[8];
int stackPointer[8];
int currentProcess;
int first = 0;
int contador=0;


extern int max( x , y);
int x; int y;
 void handleInterrupt21(int AX, int BX, int CX, int DX); 
extern void hang(void);
 void printString(char *str);
extern void makeInterrupt21(void);
extern void loadProgram(void);
extern void makeTimerInterrupt();
 void executeProgram(char *name);
 void readFile(char *fileName, char *buffer);
extern void launchProgram(int segment);
 void terminate();
int fileNameSize();
 void deleteFile(char *name);
extern void writeSector(char *buffer, int sector);
 void writeFile(char* name, char* buffer, int numberOfSectors);
extern void readSector(char *buffer, int sector);


void main() {
    int x;
    for (x = 0; x < 8; x++)
    {
        activeProcesses[x] = 0;
        stackPointer[x] = 0xff00;
    }
    currentProcess = 0;    
clearScreen();
makeInterrupt21();
executeProgram("shell");
makeTimerInterrupt();
terminate();

}

void killProcess(int process)
{
    setKernelDataSegment();
    activeProcesses[process] = 0;
    stackPointer[process] = 0xFF00;
    restoreDataSegment();
}

void handleTimerInterrupt(int segment, int sp)
{
    if(contador==200){
        int i=0;
        stackPointer[currentProcess] = sp;
        contador=0;
        if (first == 0)
        {
            contador++;
            first = 1;
            returnFromTimer(0x2000, 0xFF00);
            return;
        }

        for (i = currentProcess + 1; i != currentProcess; i++)
        {
            if (i == (7))
            {
                i = 0;
            }

            if (activeProcesses[i] == 1)
            {
                segment = (i + 2) * 0x1000;
                sp = stackPointer[i];
                currentProcess = i;
                returnFromTimer(segment, sp);
                return;
            }
        }
    }
    else{
        contador++;
        returnFromTimer(segment, sp);
    }
    
}


void writeFile(char* name, char* buffer, int numberOfSectors){
    int i;
    int x;
    int s;
    int b=0;
    int c;
    int size=fileNameSize(name)-1;
    char directory[512];
    char Map[512];
    int remaining=5-size;
    readSector(directory, 2);
    readSector(Map,1);
    for(i=0;i<512;i+=32){
        if(directory[i]==0){
            break;
        }

    }
        c=i;
        for(x=0;x<=size||x<6;x++){

            directory[i]=name[x];
            i++;
        }
        while(remaining!=0){

            directory[i]=0;
            remaining--;
            i++;
        } 
        for(s=3;s<512 && numberOfSectors>0;s++){
            if(Map[s]==0){
                Map[s]=0xFF;
                directory[i]=s;
                numberOfSectors--;
                writeSector(buffer+(b*512),s);
                b++;
                i++;
            }
        }           
        for(i;i<c+32;i++){
            directory[i]=0;
        }
        writeSector(directory,2);
        writeSector(Map,1);

}

void deleteFile(char *name){
    
    int i;
    int found=0;
    int pos=0;
    int x=0;
    int PosMap;
    int size= fileNameSize(name)-1;
    int posInSector = 0;
    char directory[512];
    char Map[512];

    readSector(directory, 2);
    readSector(Map,1);
                
    for (i = 0; i < 512; i += 32)
    {

        while (name[pos] != '\0')
        {
            if (name[pos] != directory[i + pos])
            {
                found = 0;
                break;
            }
            
            else if (pos == size)
            {  
                found = 1;
                break;
            }
            else{
                found = 1;
            }
            pos++;
        }

        if (pos == size && found)
        {
            directory[i]=0x00;
            for(x=0;x<26;x++){
                if(directory[i+6+x]==0){
                    break;
                }
                PosMap=directory[i+6+x];
                Map[PosMap]=0x00;
            }
            writeSector(directory,2);
            writeSector(Map,1);
        }
    }
}

void handleInterrupt21(int AX, int BX, int CX, int DX)
{
    if (AX == 0)
    {
        printString((char *)BX);
    }
    else if (AX == 1)
    {
        readString((char *)BX);
    }
    else if (AX == 2)
    {
        readSector((char *)BX, CX);
    }
    else if (AX == 3)
    {
        readFile((char *)BX, CX);
    }
    else if (AX == 4)
    {
        executeProgram((char *)BX);
    }
    else if (AX == 5)
    {
        terminate();
    }
    else if(AX==6){
        writeSector((char *)BX, CX);
    }
    else if(AX==7){
        deleteFile((char *)BX);
    }
    else if(AX == 8){
        writeFile((char *)BX,CX,DX);
    }
    else if(AX==9){
        killProcess(BX);
    }
    else if (AX == 10)
    {
        clearScreen();
    }    
    else
    {
        printString("error");
    }
}

void executeProgram(char *name)
{
    int i, segment;
    char buffer[26 * 512];

    setKernelDataSegment();

    for (i = 0; i < 8; i++)
    {
        if (activeProcesses[i] == 0)
            break;
    }
    activeProcesses[i] = 1;
    stackPointer[i] = 0xFF00;

    restoreDataSegment();

    segment = (i + 2) * 0x1000;

    readFile(name, buffer);

    for (i = 0; i < 26 * 512; i++)
        putInMemory(segment, i, buffer[i]);

    initializeProgram(segment);
    setKernelDataSegment();
    contador=200;
    restoreDataSegment();

}
int fileNameSize(char *fileName){
    int cont=0;
    while (fileName[cont] != '\0')
    {
        cont++;
    }
    return cont;

}
void readFile(char *fileName, char *buffer)
{
    int i;
    int found=0;
    int pos=0;
    int size= fileNameSize(fileName);
    int posInSector = 0;
    int sector=0;
    char directory[512];
    readSector(directory, 2);
    for (i = 0; i < 512; i += 32)
    {
        while (fileName[pos] != '\0')
        {
  
            if (fileName[pos] != directory[i + pos])
            {
                found = 0;
                break;
            }
            
            else if (pos == size - 1)
            {  
        
                found = 1;
                break;
            }
            else{
             
                found = 1;
            }
            pos++;
        }



        if (pos == size - 1 && found)
        {
         
            pos++;
            while (pos < 32)
            {
                if (directory[i + pos] != 0)
                {
                    sector = directory[i + pos];
              
                    readSector(buffer + posInSector, sector);
                    posInSector += 512;
                }
                pos++;
            }
            break;
        }
     
    }
}

void hang(void) {
    while(1);
}

void clearScreen()
{
    int x, y;
    for (x = 0; x < ROWS; x++)
    {
        for (y = 0; y < COLS; y++)
        {
            printChar(' ', CLR, x, y);
        }
    }
    interrupt(0x10, 0x2, 0x0, 0x0, 0x0);
}

void printString(char *str) {
	int i = 0;
	while(str[i] != '\0') {
		printChar(str[i]);
		i++;
	}
}

void readString(char line[ROWS]) {
	char chr;
	int i;
	char end_flag = 0;
	for( i = 0; i < ROWS - 1 ;)
	{
		chr = readChar();
		switch(chr){
			case BKSP:
				printChar(BKSP);
				printChar(CLR);
				i--;
				i = max(0,i);
				break;
			case RTRN:
				end_flag = 1;
				break;
			default:
				line[i] = chr;
				i++;
		}
		printChar(chr);
		line[i] = '\0';
		if(end_flag)
			break;
	}
}

int min(int x , int y) {
	return x < y ? x : y;
}

int max(int x , int y) {
	return x > y ? x : y;
}


void terminate()
{
    setKernelDataSegment();
    activeProcesses[currentProcess] = 0;
    stackPointer[currentProcess] = 0xff00;
    restoreDataSegment();
}