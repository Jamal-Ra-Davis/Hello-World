#include <stdio.h>
#include <stdlib.h>
#include "../headers/Safe_Input.h"
#include <math.h>

double codeToValue(int);
char* printConverted(double);
int valueToCode(double, double);
double getValue();

int main(int nargs, char *args[])
{
	while(1)
	{
		printf("Convert cap code to value, or value to code?\n");
		int sel = getSel("1. Code to value", "2. Value to code", "3. Convert units","4. Exit Program");
		if (sel == 1)
		{
			//Convert code to cap value
			int code;
			do
			{
				printf("Please enter 3 digit cap code: ");
				code = getInt();
				if (!((code < 1000)&&(code >= 100)))
					printf("Invalid entry...\n");
			} while (!((code < 1000)&&(code >= 100)));
						
			double value = codeToValue(code);
			printf("%d cap is %.2lf pF\n", code, value);
			printf("Would you like to convert to unit other than pF?\n");
			int confirm = getSel("1. Yes", "2. No");
			if (confirm == 1)
			{
				//convert value from pF
				char *temp = printConverted(value);
				if (temp != NULL)
				{
					printf("%2.2lf pF = %s\n", value, temp);
					free(temp);
				}
			}
			else
			{
				//Do not convert
			}
		}
		else if (sel == 2)
		{
			//Convert value to code 
			double value;
			double unit[4] = {pow(10, 12), pow(10, 6), pow(10, 3), 1};//F, uF, nF, pF
			char *units[4] = {"F", "uF", "nF", "pF"};
			int idx;
			value = getValue();
/*
			printf("Please enter in cap value (you will select the units later): ");
//			while (scanf("%lf", &value) != 1)
			char in[32];
			while (1)
			{
				if (scanf("%s", in) == 1)
				{
					if (sscanf(in, "%lf", &value) == 1)
					{
						break;
					}
				}
				printf("Invalid entry...\n");
				printf("Please enter in cap value (you will select the units later): ");
			}
*/
			printf("Select units\n");
			idx = getSel("1. F", "2. uF", "3. nF", "4. pF");
			idx--;

			int code = valueToCode(value, unit[idx]);
			if (code != -1)
				printf("Cap code for %.2lf %s is %d\n", value, units[idx], code);	
			else
				printf("Sorry, unable to generate code\n");
		}
		else if (sel == 3)
		{
			double value;
			double unit[4] = {pow(10, 12), pow(10, 6), pow(10, 3), 1};//F, uF, nF, pF
			char *units[4] = {"F", "uF", "nF", "pF"};
			int idx;
			value = getValue();
			printf("Select units\n");
			idx = getSel("1. F", "2. uF", "3. nF", "4. pF");
			idx--;
			char* temp = printConverted(value*unit[idx]);	
			if (temp != NULL)
			{
				printf("%2.2lf %s = %s\n", value, units[idx], temp);
				free(temp);
			}
		}
		else
		{
			break;
		}
	}	
	return 0;
}

double codeToValue(int code)
{
	int digit, power;
	double value;

	digit = code/10;
	power = code - digit*10;

//	printf("**Code: %d, Digits: %d, Power: %d\n", code, digit, power);
	value = digit*pow(10, power);
//	printf("**Value: %lf pF\n", value);
	return(value);
}
char* printConverted(double value)
{
	double converted;
	char* out;
	out = (char*)malloc(128*sizeof(char));

	printf("Select what you want value to be converted to\n");
//	int sel = getSel("1. Micro Farads", "2. Nano Farads", "3. Farads", "4. Pico Farads", "5. Cancel");
	int sel = getSel("1. F", "2. uF", "3. nF", "4. pF", "5. Cancel");
	switch (sel)
	{
		case 1://micro Farads, new: Farads
		{
//			converted = value/pow(10, 6);
//			printf("%.2lf pF = %.2lf uF\n", value, converted);
//			sprintf(out, "%.2lf uF", converted);

			converted = value/pow(10, 12);
//         printf("%.2lf pF = %.2lf F\n", value, converted);
         sprintf(out, "%.2lf F", converted);
			break;
		}
		case 2://Nano farads, new: micro Farads
		{
//			converted = value/pow(10, 3);
//			printf("%.2lf pF = %.2lf nF\n", value, converted);
//			sprintf(out, "%.2lf nF", converted);

			converted = value/pow(10, 6);
//         printf("%.2lf pF = %.2lf uF\n", value, converted);
         sprintf(out, "%.2lf uF", converted);
			break;
		}
		case 3://Farads, new: nano Farads
		{
//			converted = value/pow(10, 12);
//			printf("%.2lf pF = %.2lf F\n", value, converted);
//			sprintf(out, "%.2lf F", converted);

			converted = value/pow(10, 3);
//         printf("%.2lf pF = %.2lf nF\n", value, converted);
         sprintf(out, "%.2lf nF", converted);
			break;
		}
		case 4://pico Farads, new: pico Farads
		{
			converted = value;
//			printf("%.2lf pF = %.2lf pF\n", value, converted);
			sprintf(out, "%.2lf pF", converted);

			
			break;
		}
		case 5://Cancel
		{
			printf("Cancelling action...\n");
			free(out);
			out = NULL;
			break;
		}
	}	
	return out;
}
int valueToCode(double value, double units)
{
	long long int val_pf = (long long int)(value*units);
	long long int val_cp = val_pf;
	int digits = 1;
	int ret = 0;
	while (1)
	{
		val_cp /= 10;
		if (val_cp != 0)
			digits++;
		else
			break;
	}
	printf("**Took in %lld pF, %d digits\n", val_pf, digits);
	if ((digits < 2)||(digits > 11))
		return -1;

	int nums = val_pf/pow(10, digits-2);
	printf("**Nums = %d\n", nums);
	ret = nums*10 + (digits-2);
	printf("**Code = %d\n", ret);
	return ret;
}
double getValue()
{
	double value;
	printf("Please enter in cap value (you will select the units later): ");
//	while (scanf("%lf", &value) != 1)
	char in[32];
	while (1)
	{
		if (scanf("%s", in) == 1)
		{
			if (sscanf(in, "%lf", &value) == 1)
			{
				break;
			}
		}
		printf("Invalid entry...\n");
		printf("Please enter in cap value (you will select the units later): ");
	}
	return value;
}





