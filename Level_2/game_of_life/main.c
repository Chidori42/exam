#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int ac, char** av)
{
    if (ac != 4)
        return 1;
    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iterations = atoi(av[3]);
    char board[height][width];
    char next[height][width];

    //init 
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = 0;

    // start drawing 
    char c;
    int i = 0, j = 0, pen = 0;
    while (read(0, &c, 1) == 1)
    {
        if (c == 'w')
            --i;
        else if (c == 's')
            ++i;
        else if (c == 'a')
            --j;
        else if (c == 'd')
            ++j;
        else if (c == 'x')
            pen = !pen;
        if (pen)
            board[i][j] = 1;
    }

    // start simulation

    for (int iter = 0; iter < iterations; iter++)
    {
        for (int he = 0; he < height; he++)
        {
            for (int wi = 0; wi < width; wi++)
            {
                int sum = 0;
                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        if ((i || j) && (i + he >= 0) && (i + he < height) && (j + wi >= 0) && (j + wi < width))
                            sum += board[i + he][j + wi];
                    }
                }
                if ((board[he][wi] && (sum >= 2 && sum <= 3)) || (!board[he][wi] && sum == 3))
                    next[he][wi] = 1;
                else
                    next[he][wi] = 0;
            }
        }
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                board[i][j] = next[i][j];
    }

    // print result
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            putchar((board[i][j] ? 'O' : ' '));
        }
        putchar('\n');
    }
}