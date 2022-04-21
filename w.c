#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


int strmatch(char *str, char *pattern, int n, int m)
{
    // empty pattern can only match with
    // empty string
    if (m == 0)
        return (n == 0);
 
    // lookup table for storing results of
    // subproblems
    int lookup[n + 1][m + 1];
 
    // initialize lookup table to false
    memset(lookup, 0, sizeof(lookup));
 
    // empty pattern can match with empty string
    lookup[0][0] = 1;
 
    // Only '*' can match with empty string
    for (int j = 1; j <= m; j++)
        if (pattern[j - 1] == '*')
            lookup[0][j] = lookup[0][j - 1];
 
    // fill the table in bottom-up fashion
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (pattern[j - 1] == '*')
                lookup[i][j] = lookup[i][j - 1] || lookup[i - 1][j];

            // Current characters are considered as
            // matching in two cases
            // (a) current character of pattern is '?'
            // (b) characters actually match
            else if (str[i - 1] == pattern[j - 1])
                lookup[i][j] = lookup[i - 1][j - 1];
 
            // If characters don't match
            else
                lookup[i][j] = 0;
        }

    }
 	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
			printf(" %d {%c}{%c} ", lookup[i][j], str[i], pattern[j]);
		printf("\n");
	}
    return lookup[n][m];
}
int	m2(char *str, char *pattern, int n, int m);


int main(int argc, char **argv)
{
    char *str = argv[1];
    char *pattern= argv[2];
	printf("str : {%s}{%lu}\n", str, strlen(str));
	printf("pattern : {%s}{%lu}\n", pattern, strlen(pattern));

    if (strmatch(str, pattern, strlen(str), strlen(pattern)))
        printf("THEM Yes\n");
    else
        printf("THEM No\n");
	if (m2(str, pattern, strlen(str), strlen(pattern)))
        printf("ME Yes\n");
    else
        printf("ME No\n");
	return (0);
}


int	m2(char *str, char *pattern, int n, int m)
{
	int i, j;
	
	return (0);
}