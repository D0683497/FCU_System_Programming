#include "3-asm_pass1_u.c"
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int			i, c, line_count;
	char		buf[LEN_SYMBOL];
	LINE		line;
    int         symbol_counter = 0;
    char        symbol_table[200][20];
    int         symbol_location[200];

	if(argc < 2)
	{
		printf("Usage: %s fname.asm\n", argv[0]);
	}
	else
	{
		if(ASM_open(argv[1]) == NULL)
        {
            printf("File not found!!\n");
        }	
		else
		{
            unsigned location_counter = 0X0;
            unsigned start_location = 0X0;
			for(line_count = 1 ; (c = process_line(&line)) != LINE_EOF; line_count++)
			{
				if(c == LINE_ERROR)
                {
                    printf("%03d : Error\n", line_count);
                }
				else if(c == LINE_COMMENT)
                {
                    printf("%03d : Comment line\n", line_count);
                }
				else
                {
                    if(line_count = 1 && strcmp(line.op, "START") == 0)
                    {
                        start_location = strtol(line.operand1,NULL,16);
                        location_counter = location_counter + start_location;
                        printf("%06X : %12s %12s %12s,%12s (FMT=%X, ADDR=%X)\n", location_counter, line.symbol, line.op, line.operand1, line.operand2, line.fmt, line.addressing);
                    }
                    else
                    {
                        printf("%06X : %12s %12s %12s,%12s (FMT=%X, ADDR=%X)\n", location_counter, line.symbol, line.op, line.operand1, line.operand2, line.fmt, line.addressing);
                        if(line.symbol[0] != '\0')
                        {
                            strcpy(symbol_table[symbol_counter], line.symbol);
                            symbol_location[symbol_counter] = location_counter;
                            symbol_counter++;
                        }
                        switch(line.fmt)
                        {
                            case FMT0:
                                if(strcmp(line.op, "END") == 0)
                                {
                                    location_counter = location_counter + 0;
                                }
                                else if(strcmp(line.op, "BYTE") == 0)
                                {
                                    if(line.operand1[0] == 'C')
                                    {
                                        location_counter = location_counter + (strlen(line.operand1)-3);
                                    }
                                    else if(line.operand1[0] == 'X')
                                    {
                                        location_counter = location_counter + (strlen(line.operand1)-3)/2;
                                    }
                                }
                                else if(strcmp(line.op, "WORD") == 0)
                                {
                                    location_counter = location_counter + 3;
                                }
                                else if(strcmp(line.op, "RESW") == 0)
                                {
                                    location_counter = location_counter + strtol(line.operand1,NULL,10)*3;
                                }
                                else if(strcmp(line.op, "RESB") == 0)
                                {
                                    char b [20];
                                    sprintf(b, "%lx", strtol(line.operand1,NULL,10)); //十進位(字串)轉十六進位(字串)
                                    location_counter = location_counter + strtol(b,NULL,16);
                                }
                                break;
                            case FMT1:
                                location_counter = location_counter + 1;
                                break;
                            case FMT2:
                                location_counter = location_counter + 2;
                                break;
                            case FMT3:
                                location_counter = location_counter + 3;
                                break;
                            case FMT4:
                                location_counter = location_counter + 4;
                                break;
                        }
                    }
                }
			}

            printf("\n\nProgram length = %X\n", location_counter-start_location);
            for(i = 0; i < symbol_counter; i++)
            {
                printf("%8s : %06X\n", symbol_table[i], symbol_location[i]);
            }

			ASM_close();
		}
	}
}
