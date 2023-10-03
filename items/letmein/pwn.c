#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void quit(){
	puts("WRONG!\nTry this website after you enter university!");
	exit(0);
}

int main(){
	setvbuf(stdin, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
	setvbuf(stderr, 0LL, 2, 0LL);
	srand(time(NULL));
	printf("                                                                                                   \n");
    printf("                    ,--.                                       ,--,                                \n");
    printf("  ,----..         ,--.'|  .--.--.    .--.--.                 ,--.'|                                \n");
    printf(" /   /   \\    ,--,:  : | /  /    '. /  /    '.            ,--,  | :                ,---,           \n");
    printf("|   :     :,`--.'`|  ' :|  :  /`. /|  :  /`. /         ,---.'|  : '         ,--, ,---.'|           \n");
    printf(".   |  ;. /|   :  :  | |;  |  |--` ;  |  |--`          |   | : _' |       ,'_ /| |   | :           \n");
    printf(".   ; /--` :   |   \\ | :|  :  ;_   |  :  ;_            :   : |.'  |  .--. |  | : :   : :           \n");
    printf(";   | ;    |   : '  '; | \\  \\    `. \\  \\    `.         |   ' '  ; :,'_ /| :  . | :     |,-.        \n");
    printf("|   : |    '   ' ;.    ;  `----.   \\ `----.   \\        '   |  .'. ||  ' | |  . . |   : '  |        \n");
    printf(".   | '___ |   | | \\   |  __ \\  \\  | __ \\  \\  |        |   | :  | '|  | ' |  | | |   |  / :        \n");
    printf("'   ; : .'|'   : |  ; .' /  /`--'  //  /`--'  /        '   : |  : ;:  | : ;  ; | '   : |: |        \n");
    printf("'   | '/  :|   | '`--'  '--'.     /'--'.     /         |   | '  ,/ '  :  `--'   \\|   | '/ :        \n");
    printf("|   :    / '   : |        `--'---'   `--'---'          ;   : ;--'  :  ,      .-./|   :    |        \n");
    printf(" \\   \\ .'  ;   |.'                                     |   ,/       `--`----'    /    \\  /         \n");
    printf("  `---`    '---'                                       '---'                     `-'----'          \n");
	puts("--------------------------------------Welcom to CnssHub--------------------------------------\n");
	puts("Tips:\n\tWe have launched adult mode for you, wanna turn on adult mode?(y/n)");
	char choice;
	scanf("%c",&choice);
	getchar();
	if(choice != 'y')
	{
		puts("No more information for you");
		exit(0);
	}
	puts("Here`s 100 math problem for you to verity you are an adult, wanna continue?(y/n)");
	scanf("%c",&choice);
	getchar();
	if(choice != 'y')
	{
		puts("No more information for you");
		exit(0);
	}
	for(int i=0;i<=99;++i)
	{
		int a = rand()%114514 +1;
		int b = rand()%114514 +1;
		int c = rand()%2;
		int ans,feedback;
		switch(c){
			case 0:
				printf("%d + %d =?\n",a,b);
				ans = a+b;
				break;
			case 1:
				printf("%d - %d =?\n",a,b);
				ans = a-b;
				break;
		}
		time_t time1 = time(NULL);
		scanf("%d", &feedback);
		time_t time2 = time(NULL);
		if(ans!=feedback)
		{
			quit();
		}
		if(difftime(time2,time1) > 8.0)
		{
			puts("toooooo slooooooow!\nTIM CAN`T WAIT!!!");
			exit(0);
		}

	}

	system("/bin/sh");
	return 0;
}