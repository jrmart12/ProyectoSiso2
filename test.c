

void main()
{

char buffer[13312];
/*this is the maximum size of a file*/
syscall_readFile("execut", buffer);
/*read the file into buffer*/
syscall_printString(buffer);
/*this is the maximum size of a file*/
/*print out the file*/
syscall_printString("\r\n");
syscall_terminate();
	
}