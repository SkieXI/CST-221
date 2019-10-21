#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char line[1024];
    size_t current_size = 0;
    
    
    printf("Is this thing a q?\n");
    gets(line);

    //String compare
    //gets (get String)
    //sscanf
    //
    if (line[0] == 'q')
    {
        printf("\nGood job!\n");
        exit(0);
    }
    else
    {
        //line[current_size++] = line;
        printf("%s\n", line);
        exit(0);
    }
    
    return(0);
}
