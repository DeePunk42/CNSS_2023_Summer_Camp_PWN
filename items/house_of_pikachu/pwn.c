#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAX_IDX 20
#define MIN_SIZE 0x80
#define MAX_SIZE 0x3f0


void* heap_list[MAX_IDX];
int heap_size[MAX_IDX];

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
    printf("    * %-33s *\n", "                                       --Welcom to DeePunk Note v2.0--                                        *\n    *            This is an efficient, minimalist, powerful, and never-developed note-taking software.             ");
    printf("    *****************************************************************************************************************\n");
}

void toc(){
	puts("\nWhat can I do for you?");
	puts("----------------");
	puts("1. add notes");
	puts("2. view notes");
	puts("3. edit notes");
	puts("4. delet notes");
	puts("5. quit");
	puts("----------------");
	printf("pls input your choice: ");
}

void add(){
	puts("index:");
	char buf[5];
	read(0, buf, 3);
	int idx = atoi(buf);
	if(idx<0||idx>MAX_IDX||heap_list[idx])
	{
		puts("wrong index");
		return;
	}
	puts("size:");
	memset(buf, 0, sizeof(buf));
	read(0, buf, 5);
	int size = atoi(buf);
	if(size<MIN_SIZE||size>MAX_SIZE){
		puts("wrong size");
		return;
	}
	heap_list[idx] =  calloc(size, sizeof(char));
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
	if(idx<0||idx>MAX_IDX||!heap_list[idx])
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
	if(idx<0||idx>MAX_IDX||!heap_list[idx])
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
	read(0, heap_list[idx], size);
	puts("success!");	
}

void delet(){
	puts("index:");
	char buf[3];
	read(0, buf, 3);
	int idx = atoi(buf);
	if(idx<0||idx>MAX_IDX||!heap_list[idx])
	{
		puts("wrong index");
		return;
	}
	free(heap_list[idx]);	
	puts("\nsuccess!");	
}

void quit(){
	puts("leave your comment for this software pls:");
	puts("comment size:");
	char buf[5];
	read(0, buf, 5);
	int size = atoi(buf);
	if(size<MIN_SIZE||size>MAX_SIZE){
		puts("wrong size");
		return;
	}
	void * ptr = malloc(size);
	puts("content:");
	read(0, ptr, size);
	// puts("Thx for your comment, bye~");		
	exit(0);
}

void my_init(){
	setvbuf(stdin, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
	setvbuf(stderr, 0LL, 2, 0LL);
}


int main(){
	my_init();
	topic();
	while(1)
	{		
		toc();
		char buf[2];
		read(0, buf, 2);
		int choice = atoi(buf);
		switch(choice){
			case 1:
				add();
				break;
			case 2:
				view();
				break;
			case 3:
				edit();
				break;
			case 4:
				delet();
				break;
			default:
				quit();
				break;
		}
	}
}