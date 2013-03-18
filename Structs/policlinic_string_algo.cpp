#include "policlinic_string_algo.h"
#include <string.h>
#include <stdlib.h>
#include <fstream>

void toLowCaseCP866(char * str)
{
	char * s = str;
	while (*s != 0)
	{
		if ((*s >= 'A')&&(*s <= 'Z'))
		{
			*s += 32;
		}else if ((*s >= (char)0x80)&&(*s <= (char)0x8F))
		{
			*s += 32;
		}else if ((*s >= (char)0x90)&&(*s <= (char)0x9F))
		{
			*s += 80;
		}else
		{
			//no change on value *s
		}
		++s;
	}
}

void win1251toCP866(char * str)
{
	while (*str != 0)
	{
		if ((*str >= (char)0xC0)&&(*str <= (char)0xEF))
		{
			*str -= 64;
		}else if ((*str >= (char)0xF0)&&(*str <= (char)0xFF))
		{
			*str -= 16;
		}else if (*str == (char)0xA8) 
		{
			*str = (char)(0xF0);
		}else if (*str == (char)0xB8) 
		{
			*str = (char)(0xF1);
		}else
		{
			//no change on value *s
		}
		++str;
	}
}

void CP866toWin1251(char * str)
{
	while (*str != 0)
	{
		if ((*str >= (char)0x80)&&(*str <= (char)0xAF))
		{
			*str += 64;
		}else if ((*str >= 0xE0)&&(*str <= 0xEF))
		{
			*str += 16;
		}else if (*str == 0xF0) 
		{
			*str = (char)(0xA8);
		}else if (*str == 0xF1)
		{
			*str = (char)(0xB8);
		}else
		{
			//no change on value *s
		}
		++str;
	}
}

void removeDoubleWhiteSpaces(char * str)
{
	char * ptr = str;
	while (*str != 0)
	{
		*ptr = *str;
		++ptr;
		if (*str == ' ')
		{
			while ((*str != 0)&&(*str == ' '))
				++str;
		}else ++str;
	}
	*ptr = 0;
}

int search(const char * sample, const char * str)
{
	int len = strlen(sample);
	char * nSample = (char *)malloc((len + 1)*sizeof(char));
	strcpy(nSample, sample);
	len = strlen(str);
	char * nStr = (char *)malloc((len + 1)*sizeof(char));
	strcpy(nStr, str);
	
	toLowCaseCP866(nSample);
	toLowCaseCP866(nStr);
	removeDoubleWhiteSpaces(nSample);
	removeDoubleWhiteSpaces(nStr);
	
	char * rez = strstr(nStr, nSample);
	
	free(nStr);
	free(nSample);
	if (rez == NULL)
		return 1;
	else
		return 0;
}

int my_strcmp(const char * sample, const char * str)
{
	int len = strlen(sample);
	char * nSample = (char *)malloc((len + 1)*sizeof(char));
	strcpy(nSample, sample);
	len = strlen(str);
	char * nStr = (char *)malloc((len + 1)*sizeof(char));
	strcpy(nStr, str);
	
	toLowCaseCP866(nSample);
	toLowCaseCP866(nStr);
	removeDoubleWhiteSpaces(nSample);
	removeDoubleWhiteSpaces(nStr);
	
	int rez = strcmp(nStr, nSample);
	
	free(nStr);
	free(nSample);
	return rez;
}