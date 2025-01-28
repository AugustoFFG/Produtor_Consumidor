#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>


void buffer(){
    FILE *buffer = fopen("buffer.txt", "w");
    
    if(buffer == NULL){
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }
    
    for(int i = 0; i < 10; i++){
        fprintf(buffer, "%d\n", rand() % 100);
    }
    
    fclose(buffer);
}

void tranca(){
    while(fopen("buffer.txt.lock", "r") != NULL){
        usleep(1000000);
    }
    
    FILE *tranca = fopen("buffer.txt.lock", "w");

    if(tranca == NULL){
        printf("Erro ao abrir o arquivo!");
        exit(1);
    }

    fclose(tranca);
}

void destranca(){
    remove("buffer.txt.lock");
}

void produtor(){
    int r;

    while(1){
        tranca();
        r = rand() % 100;

        FILE *buffer = fopen("buffer.txt", "a");
        if(buffer == NULL){
            printf("Erro ao abrir o arquivo!");
            destranca();
            exit(1);
        }

        fprintf(buffer, "%d\n", r);
        fclose(buffer);

        printf("[Produtor] %d\n", r);

        destranca();

        sleep(rand() % 3 + 1);
    }
}

void consumidor(){
    while (1){
        tranca();

        FILE *buffer = fopen("buffer.txt", "r");
        
        if(buffer == NULL){
            printf("Erro ao abrir o arquivo!");
            destranca();
            exit(1);
        }

        int numero;

        FILE *temp = fopen("temp.txt", "w");

        if(temp == NULL){
            printf("Erro ao abrir o arquivo!");
            destranca();
            exit(1);
        }

        int deletado = 0;

        while(fscanf(buffer, "%d", &numero) != EOF){
            if(deletado == 0){
                printf("[Consumidor] %d\n", numero);
                deletado = 1;
            } 
            else fprintf(temp, "%d\n", numero);
        }
        
        fclose(buffer);
        fclose(temp);

        rename("temp.txt", "buffer.txt");

        destranca();
        sleep(rand() % 3 + 1); 
    }

        
}

int main() {
    srand(time(NULL));

    int pid = fork();

    buffer();

    if(pid == 0){
        consumidor();//filho
    } 
    else{
        produtor(); //pai
    }

    return 0;   
}
