 int strCompare(char *buffer, char *str);
 int contador(char *name);
 int fileNameSize(char *fileName);
 int searchFile(char *name);
 void dir();
 extern void enableInterrupts();
 extern void syscall_printString(char *str);
 extern void syscall_readString(char *line);
 extern void syscall_readSector(char *buffer, int sector);
 extern void syscall_readFile(char *fileName, char *buffer);
 extern void syscall_executeProgram(char *name);
 extern void syscall_terminate();
 extern void syscall_clearScreen();
 extern void syscall_deleteFile(char *name);
 extern void syscall_writeFile(char* name, char* buffer, int numberOfSectors);
 extern void syscall_killProcess(int k);
main()
{
    char str[80];
    char name[6];
    char copy[6];
    char line[80];
    char buffer[13312];
    int i=0;
    int x=5;
    int cont;
    int b=0;
    int s=0;
    int a=0;
    int q=0;
    int y=0;
    int numberOfSectors = 0, location;
    char directory[512];
    enableInterrupts();
    while(1)
    {
        syscall_printString("SHELL>");
        syscall_readString(str);
        syscall_printString("\r\n");

        if (strCompare("clear", str))
        {
            syscall_clearScreen();
        }
        else if (strCompare("type", str))
        {
            syscall_readFile(&str[5], buffer);
            syscall_printString(buffer);
            for(i=0;i<512;i++){
                buffer[i]=0;
            }
            syscall_printString("\r\n");
        }
        else if (strCompare("execute", str))
        {
            syscall_executeProgram(&str[8]);
            syscall_printString("\r\n");
        }
        else if(strCompare("delete",str)){
            syscall_deleteFile(&str[7]);
            syscall_printString("\r\n");
        }
        else if(strCompare("copy",str)){
            for(a=0;a<7 && str[5+a]!='\0' && str[5+a]!=' ';a++){
                copy[a]=str[5+a];
            }
            syscall_readSector(directory,2);
            location = searchFile(&copy);
            if (location == -1)
                return;

            for (b = 6; b < 32; b++)
            {
                if (directory[location + b] != 0x00){
                    numberOfSectors++;
                }
            }
            syscall_readFile(&copy, buffer);
            while(x<80){
                if(str[x]==' '){
                    syscall_writeFile(&str[x+1],buffer,numberOfSectors);
                }
                x++;
            }
            a=0;
            b=0;
            x=5;
            location=0;
            
        }
        else if(strCompare("dir",str)){
            dir();
        }
        else if(strCompare("create",str)){
            for(a=0;a<6 && str[7+a]!='\0';a++){
                name[a]=str[7+a];
            }
            line[0] = ' ';
        while (line[0] != 0 && s < 26 * 512)
        {
            syscall_readString(line);
            for (y = 0; y < 80 && s < 26 * 512; y++)
            {
                if (line[0] == 0 || line[y] == '\0')
                    break;

                buffer[s++] = line[y];
            }
            buffer[s++] = '\r';
            buffer[s++] = '\n';
            syscall_printString("\r\n"); 
        }            
        syscall_writeFile(name, buffer, (int)(x / 512) + 1);
        }
        else if(strCompare("kill",str)){
            syscall_killProcess(1);
        }
        else
        {
            syscall_printString("Bad Command!");
            syscall_printString("\r\n");
        }
    i=0;
    x=5;
    cont;
    b=0;
    s=0;
    a=0;
    q=0;
    y=0;
    }
}
int fileNameSize(char *fileName){
    int cont=0;
    while (fileName[cont] != '\0')
    {
        cont++;
    }
    return cont;

}

int searchFile(char *name)
{
    char directory[512];
    int x;
    int y;
    int found;
    syscall_printString(name);
    syscall_readSector(directory, 2);

    for (x = 0; x < 512; x += 32)
    {
        for (y = 0; y < 6; y++)
        {
            if (name[y] == '\0')
            {
                if (directory[x + y] != 0x0){
                    found = 0;
                }
                break;
            }

            if (directory[x + y] == name[y]){
                found = 1;
            }
            else
            {
                found = -1;
                break;
            }
        }
        if (found == 1){
            return x;
        }
    }
    return -1;
}
void dir(){
    int s=0;
    int i=0;
    int pos=0;
    char nombreD[7];
    char directory[512];
    syscall_readSector(directory, 2);

    for (s = 0; s < 512; s += 32)
    {
        while((directory[s+pos]!=0 && directory[s+pos]!=' ' )&& pos<6){
            nombreD[pos]=directory[s+pos];
            pos++;
        }
        
        if(pos>0){
            syscall_printString(nombreD);
            syscall_printString("\r\n");
        }
        for(i=0;i<7;i++){
            nombreD[i]=0;
        }
        pos=0;
    }
}
int contador(char *name){
    int cont=0;
  
    int i;
    int found=0;
    int pos=0;
    int x=0;
    int PosMap;
    int size= fileNameSize(name)-1;
    int posInSector = 0;
    char directory[512];
    syscall_readSector(directory, 2);
                
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
                cont++;
   
            }
            
            return cont;
        }    
    }
    return 1;
}

int strCompare(char *buffer, char *str)
{
    int i = 0;
    while (buffer[i] != '\0' && str[i] != '\0')
    {
        if (buffer[i] != str[i])
            return 0;
        i++;
    }
    return 1;
}