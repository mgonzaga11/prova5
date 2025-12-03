#include <stdlib.h>
#include <unistd.h>

char **malloc_matrix(int altura, int largura){

    char **temp;
    int i;
    temp =  calloc(largura + 1, sizeof(char *));
    if(!temp)
        return (NULL);
    while(i < altura){
       temp[i] =  calloc(largura + 1, sizeof(char *));
        if(!temp)
            return (NULL);
        i++;
    }
    return temp;
}


char **process_comands(int altura, int largura){

    char **matrix = malloc_matrix( altura, largura);
    char chr;
    int caneta = 1;
    int x = 0;
    int y = 0;

    while(read(0, &chr , 1) == 1 && chr != '\n')
    {
        if(chr == 'x')
            caneta = !caneta;
        else{
            if(caneta && (y >= 0 &&  y < altura) && (x >= 0 && x < largura))
                matrix[y][x] = '0';
            else if(chr == 'w')
                y--;
            else if(chr == 's')
                y++;
            else if(chr == 'd')
                x--;
            else if(chr == 'a')
                x++;
        }

    }
    if(caneta && (y >= 0 &&  y < altura) && (x >= 0 && x < largura))
        matrix[x][y] = '0';
    return matrix;
}



void copy_matrix(char **matrix, char **temp){
    
    int a = 0;
    int l = 0;

    while (matrix[a] != NULL)
        {
            while(matrix[a][l] != '\0')
            {
                temp[a][l] = matrix[a][l];
                l++;
            }
            a++; 
        }
}

void process_interacoes(char **matrix , int altura, int largura , int interacoes){
    
    int i = 0;
    int a = 0;
    int l = 0;
    int celulasvivas;
    char **temp = malloc_matrix(altura, largura);

    while (i < interacoes)
    {
        copy_matrix(matrix, temp);
        while (a < altura)
        { 
            l = 0;
            while(l < largura)
            {
                if(matrix[a][l] == '0'){
                    if(matrix[a + 1][l -1] == '0')
                        celulasvivas++;
                    if(matrix[a][l-1] == '0')
                        celulasvivas++;
                    if(matrix[a-1][l-1] == '0')
                        celulasvivas++;
                    if(matrix[a+1][l] == '0')
                        celulasvivas++;
                    if(matrix[a-1][l] == '0')
                        celulasvivas++;
                    if(matrix[a+1][l+1] == '0')
                        celulasvivas++;
                    if(matrix[a][l+1] == '0')
                        celulasvivas++;
                    if(matrix[a-1][l+1] == '0')
                        celulasvivas++;
                }
                if(celulasvivas < 2)
                  temp[a][l] = ' ';
                else if(celulasvivas > 3) 
                    temp[a][l] = ' ';
                else if(temp[a][l] == ' ' && celulasvivas > 3)
                    temp[a][l] = '0';
                celulasvivas = 0;
                l++;
            }
            a++;
        }
        copy_matrix(temp, matrix);
        i++;
    }
    free (temp);
}


void print_matrix(char **matrix)
{
    int a = 0;
    int l = 0;

    while (matrix[a] != NULL)
        {
            while(matrix[a][l] != '\0')
            {
                write(1, &matrix[a][l], 1);
                l++;
            }
            write(1, "\n", 1);
            a++; 
        }
}


void free_matrix(char **matrix){
    int a = 0;

    while (matrix[a] != NULL)
    {
        free(matrix[a]);
         a++; 
    }
}

int main(int argc, char **argv)
{
    if (argc < 4)
        return 1;
    
    int altura = atoi(argv[1]);
    int largura = atoi(argv[2]);
    int interacoes = atoi(argv[3]);

    char **matrix;

    matrix  = process_comands( altura, largura);

    if(interacoes > 0)
        process_interacoes(matrix, altura, largura, interacoes);

    print_matrix(matrix);
    free_matrix(matrix);
    return 0;

}