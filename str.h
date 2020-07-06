#ifndef _STR_H_
#define _STR_H_

void str_trim_crlf(char *str);//character return line feed:remove\r\n
void str_split(const char *str, char *left, char *right, char c);
int str_all_space(const char *str);//whether all space
void str_upper(char *str);
long long str_to_longlong(const char *str);
unsigned int str_octal_to_uint(const char *str);//turn octal to unsigned int

#endif/*_STR_H_*/
