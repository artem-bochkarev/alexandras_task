#ifndef POLICLINIC_STRING_ALGO_H
#define POLICLINIC_STRING_ALGO_H

//translates characters to lower case format, for string in CP866 encoding
void toLowCaseCP866(char * str);

//translates from one encoding to another
void win1251toCP866(char * str);
void CP866toWin1251(char * str);

//removes white spaces if there are more than one
void removeDoubleWhiteSpaces(char * str);

//search for substring( not case sensitive )
int search(const char * sample, const char * str);

//comares two strings( not case sensitive )
int my_strcmp(const char * sample, const char * str);

#endif