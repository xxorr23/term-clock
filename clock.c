/*

    Copyright (C) 2017 Vishal Nishad <xxorr23@gmail.com>


    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


*/





#include <clock.h>

char color_code = 'r';
int center_clock = 0;
int g_x = 0, g_y=0;

void open_file(int a, int pos)
{
	FILE *fp;
	char ch;
	char buff[100];
	snprintf(buff, sizeof(buff),  "/usr/local/term-clock/ascii/%d.txt", a);
	fp = fopen(buff, "r");
	
	int x, y;
	int xx;
	
	switch(pos) {
	
		case HR_TENS  :		x = xx = 0;
					break;
		case HR_ONES  :		x =  xx = 22;
					break;
		case COLON    :		x =  xx = 45;
					break;
		case MIN_TENS :		x =  xx = 57;
					break;
		case MIN_ONES :		x =  xx = 79;
					break;
	}
	y = 0;

	if(center_clock)
	{
		x += 25,	y += 12;
		xx += 25;
	}
	/* for custom ordinates */
	x += g_x, y += g_y;
	xx += g_x;

	while((ch = getc(fp)) != EOF)
	{	if(ch == '\n')
		{	x = xx; //reset position of x on newline
			y++;
		}
		gotoxy(x++,y);
		switch(color_code)
		{
			case 'r' :	printf(RED"%c"RESET, ch);
					break;
			case 'g' :	printf(GREEN"%c"RESET, ch);
					break;
			case 'y' :	printf(YELLOW"%c"RESET, ch);
					break;
			case 'b' :	printf(BLUE"%c"RESET, ch);
					break;
			case 'm' :	printf(MAGENTA"%c"RESET, ch);
					break;
			case 'c' :	printf(CYAN"%c"RESET, ch);
					break;
			case 'w' :	printf(WHITE"%c"RESET, ch);
					break;
			defualt  :	printf(RED"%c"RESET, ch);
					break;
			
		}
	}
fclose(fp);
}

/* Function to get current time */
void curr_time(int *hr, int *min)
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
	*hr = timeinfo->tm_hour;
	*min = timeinfo->tm_min;
}

void print_usage(char *myclock)
{
	printf( "usage: %s option\n\n\
		-C :    show clock at centre\n\
		-X :	custom x-ordinate\n\
		-Y :	custom y-ordinate\ncolor options:\n\
                -r :    red(default)\n\
                -g :    green\n\
                -y :    yellow\n\
                -b :    blue\n\
                -m :    magenta\n\
                -c :    cyan\n\
                -w :    white\n", myclock);
                exit(0);
}

int main(int argc, char *argv[])
{
	int option = -1;

	while((option = getopt(argc, argv, "rgybmcwhCX:Y:")) != -1)
        {
                switch(option) 
		{
                        case 'r' :      color_code = 'r';
                                        break;
                        case 'g' :      color_code = 'g';
                                        break;
                        case 'y' :      color_code = 'y';
                                        break;
                        case 'b' :      color_code = 'b';
                                        break;
                        case 'm' :      color_code = 'm';
                                        break;
                        case 'c' :      color_code = 'c';
                                        break;
                        case 'w' :      color_code = 'w';
                                        break;
			case 'h' :	print_usage(argv[0]);
					break;
			case 'C' :	center_clock = 1;
					break;
			case 'X' :	g_x = atoi(optarg);
					break;
			case 'Y' :	g_y = atoi(optarg);
					break;
                        default  :      print_usage(argv[0]);
                                        break;
                }
        }
	

	/* set cursor off */
	system("setterm -cursor off");

while(1)
{
	signal(SIGINT, sigintHandler);

	system("clear");

	int hour,min;

	curr_time(&hour, &min);
	
	open_file(hour/10, HR_TENS);
	open_file(hour%10, HR_ONES);
	open_file(min/10, MIN_TENS);
	open_file(min%10, MIN_ONES);

	/*blink : */
	sleep(1); 
	open_file(10, COLON);
	
	sleep(1);
	
}
}
