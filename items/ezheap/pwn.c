#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<unistd.h>

void* heap_list[0x10];
int heap_size[0x10];

void topic(){
    printf(" _ .-') _     ('-.     ('-.     _ (`-.                  .-') _ .-. .-')             .-') _               .-') _     ('-.   \n");
    printf("( (  OO) )  _(  OO)  _(  OO)   ( (OO  )                ( OO ) )\\  ( OO )           ( OO ) )             (  OO) )  _(  OO)  \n");
    printf(" \\     .'_ (,------.(,------. _.`     \\,--. ,--.   ,--./ ,--,' ,--. ,--.       ,--./ ,--,'  .-'),-----. /     '._(,------. \n");
    printf(" ,`'--..._) |  .---' |  .---'(__...--''|  | |  |   |   \\ |  |\\ |  .'   /       |   \\ |  | )/   |  | |  |'--...__)|  .---' \n");
    printf(" |  |  \\  ' |  |     |  |     |  /  | ||  | | .-') |    \\|  | )|      /,       |    \\|  | )/   |  | |  |'--.  .--'|  |     \n");
    printf(" |  |   ' |(|  '--. (|  '--.  |  |_.' ||  |_|( OO )|  .     |/ |     ' _)      |  .     |/ \\_) |  |\\|  |   |  |  (|  '--.  \n");
    printf(" |  |   / : |  .--'  |  .--'  |  .___.'|  | | `-' /|  |\\    |  |  .   \\        |  |\\    |    \\ |  | |  |   |  |   |  .--'  \n");
    printf(" |  '--'  / |  `---. |  `---. |  |    ('  '-'(_.-' |  | \\   |  |  |\\   \\       |  | \\   |     `'  '-'  '   |  |   |  `---. \n");
    printf(" `-------'  `------' `------' `--'      `-----'    `--'  `--'  `--' '--'       `--'  `--'       `-----'    `--'   `------' \n");
    printf("    *****************************************************************************************************************\n");
    printf("    * %-33s *\n", "                                         --Welcom to DeePunk Note--                                           *\n    *            This is an efficient, minimalist, powerful, and never-developed note-taking software.             ");
    printf("    *****************************************************************************************************************\n");
}

void toc(){
	puts("\nWhat can I do for you?");
	puts("----------------");
	puts("1. add notes");
	puts("2. view notes");
	puts("3. edit notes");
	puts("4. delet notes");
	puts("----------------");
	printf("pls input your choice: ");
}

void add(){
	puts("index:");
	char buf[5];
	read(0, buf, 3);
	int idx = atoi(buf);
	if(idx<=0||idx>15||heap_list[idx])
	{
		puts("wrong index");
		return;
	}
	puts("size:");
	memset(buf, 0, sizeof(buf));
	read(0, buf, 5);
	int size = atoi(buf);
	if(size<=0x80||size>0x400||(heap_size[idx]&&size>heap_size[idx])){
		puts("wrong size");
		return;
	}
	heap_list[idx] =  malloc(size);
	heap_size[idx] = size;
	puts("content:");
	read(0, heap_list[idx], size);
	puts("success!");		
}

void view(){
	puts("index:");
	char buf[3];
	read(0, buf, 3);
	int idx = atoi(buf);
	if(idx<0||idx>15||!heap_list[idx])
	{
		puts("wrong index");
		return;
	}
	puts("content is:");
	write(1, heap_list[idx], 0x10);
	return;
}

void edit(){
	puts("index:");
	char buf[5];
	read(0, buf, 3);
	int idx = atoi(buf);
	if(idx<=0||idx>15||!heap_list[idx])
	{
		puts("wrong index");
		return;
	}
	puts("size:");
	memset(buf, 0, sizeof(buf));
	read(0, buf, 5);
	int size = atoi(buf);
	if(size>heap_size[idx]){
		puts("wrong size");
		return;
	}
	puts("content:");
	read(0, heap_list[idx], (unsigned int)size);
	puts("success!");	
}

void delet(){
	puts("index:");
	char buf[3];
	read(0, buf, 3);
	int idx = atoi(buf);
	if(idx<=0||idx>15||!heap_list[idx])
	{
		puts("wrong index");
		return;
	}
	free(heap_list[idx]);
	heap_list[idx]=(void*)NULL;
	heap_size[idx]=0;	
	puts("\nsuccess!");	
}

void vip(){
	system("cat falg");
}


void my_init(){
	setvbuf(stdin, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
	setvbuf(stderr, 0LL, 2, 0LL);
	heap_list[0] = malloc(0x40);
	*((void **)heap_list[0]) = add;
	*((void **)heap_list[0]+1) = view;
	*((void **)heap_list[0]+2) = edit;
	*((void **)heap_list[0]+3) = delet;
	*((void **)heap_list[0]+4) = vip;
}


int main(){
	topic();
	my_init();
	while(1)
	{		
		toc();
		char buf[10];
		read(0, buf, 10);
		int choice = atoi(buf)-1;
		if(choice<0||choice>4)
		{
			puts("See you again ~");
			exit(0);
		}
		void (*funcPtr)() = *((void **)heap_list[0]+choice);
		funcPtr();
	}
}