#include"header.h"
int chr;
char ops[][2] = {{'+','-'},{'*','/'}};

int get_num()
{
	int num;
	num = 0;
	while(1)
	{
		chr = uart0_rx();
		uart0_tx(chr);
		if(chr >= '0' && chr <= '9')
		{

			num = num * 10 + (chr - '0');
		}
		else if(chr == '\b')
		{
			num = num / 10;
		}						 
		else
		{
			return num;
		}	
	}
}

int main(void)
{
	int result[10]; // result in postfix expression
	int resPos;
	int num;
	char prior[2];
	char opStack[10][2]; // store pairs row and cols of the operand in stack
	int opPos;
	int rows = sizeof(ops) / sizeof(ops[0]); // number of columns 
	int cols = sizeof(ops[0]) / sizeof(ops[0][0]); // number of rows
	uart0_init(9600);
	while(1)
	{
		uart0_tx_string("\r\n>> ");
		resPos = -1;
		opPos = -1;
		while(1)
		{
			num = get_num();
			resPos++;
			result[resPos] = num;
			// if chr is \r then break and start calculation
			if(chr == '\r')
				break;
			else
			{
				//else it must be an operator
				//find its priority
				for(prior[0] = 0;prior[0] < rows; prior[0]++)
				{
					for(prior[1] = 0;prior[1] < cols; prior[1]++)
					{
						if(ops[prior[0]][prior[1]] == chr)
							break;	
					}
					if(prior[1] < cols)
						break;	
				}
				checkprio:
				//if nothing in stack or priority of current op is higher
				if(opPos == -1 || opStack[opPos][0] < prior[0])
				{
					//push into stack
					opPos++;
					opStack[opPos][0] = prior[0];
					opStack[opPos][1] = prior[1];	
				}
				//if current priority is same or lower then solve numbers
				else
				{
					switch(ops[opStack[opPos][0]][opStack[opPos][1]])
					{
						case '+':
							result[resPos - 1] = result[resPos - 1] + result[resPos];
							break;
						case '-':
							result[resPos - 1] = result[resPos - 1] + result[resPos];
							break;
						case '*':
							result[resPos - 1] = result[resPos - 1] * result[resPos];
							break;
						case '/':
							result[resPos - 1] = result[resPos - 1] / result[resPos];
							break;
						default:
							//nothing to do except generate error
							break;	
					}
					opPos--;
					resPos--;				
					//again check priority
					goto checkprio;
				}

			}	
		}
		//calculation
		while(opPos >= 0)
		{
			switch(ops[opStack[opPos][0]][opStack[opPos][1]])
			{
				case '+':
					result[resPos - 1] = result[resPos - 1] + result[resPos];
					break;
				case '-':
					result[resPos - 1] = result[resPos - 1] - result[resPos];
					break;
				case '*':
					result[resPos - 1] = result[resPos - 1] * result[resPos];
					break;
				case '/':
					result[resPos - 1] = result[resPos - 1] / result[resPos];
					break;
				default:
					//nothing to do except generate error
					break;	
			}
			opPos--;
			resPos--;	
		}
		uart0_tx_string("\nAns : ");		
		uart0_tx_int(result[0]);
	}	
}


