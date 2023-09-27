#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdbool.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){   
  FILE *fptr, *f1, *f2, *f3, *out, *f4, *f5;
   if ((fptr = fopen(argv[1],"rb")) == NULL){
       printf("Error! opening file\n");
       exit(1);
   }
   else {
       //in file1.bin scrivo il contenuto del testo in input, ma in esadecimale, ad es:
       //f30ff47ff3bff23ff25ff3fff6dff5dff62ff72ff3dff60ff71ff26ff65ff7dff70ff2eff3ef
       f1 = fopen("file1.bin", "wb+");
       int ch = 0;
       while (ch != EOF) {
           if ((ch = fgetc(fptr)) != EOF) {
               //printf("%02x ", ch);
               fprintf(f1, "%02x", ch);
           }
       }
    }
    fclose(fptr);
   
    //in file2.bin scrivo solo i codici ascii dei caratteri (in pratica tolgo le f), ad es:
    //30473b23253f6d5d62723d607126657d702e3e515c2c2d207255477d22586766450a6d367a745341
    f2 = fopen("file2.bin", "wb+");
    rewind(f1);
    int ch2 = 0;
    int check = 1;
    while (ch2 != EOF) {
        if ((ch2 = fgetc(f1)) != EOF) {
            //printf("%c", ch2);
            //se siamo sul numero 2 o 3, li scrivo nel file f2
            if ((check == 2) || (check == 3)) {
                //printf("%c", ch2);
                fprintf(f2, "%c", ch2);
            }
            //se siamo sul numero 4, azzero check (e poi subito dopo si incrementa a 1)
            else if (check == 4) {
                check = 0;
            }
        }
        check++;
    }
    fclose(f1);
   
    //in file3.bin scrivo la traduzione, il file deoffuscato, ad es:
    //0G;#%?m]br=`q&e}p.>Q\,- rUG}"XgfE
    f3 = fopen("file3.bin", "wb+");
    rewind(f2);
    int ch3 = 0;
    int check2 = 0;
    char str1[20];
    char str2[10];
    char buffer[10];
    while (ch3 != EOF) {
        if ((ch3 = fgetc(f2)) != EOF) {
            //printf("%c: ", ch3);
            //se sono sul primo numero della coppia (ad es ho 30 e sono su 3), salvo il numero in str1
            if (check2 == 0) {
                sprintf(str1, "%c", ch3);
                //printf("%s ", str1);
            }
            //se sono sul secondo numero, allora lo salvo in str2, poi a str1 aggiungo str2 (in str1 ho 30)
            //creo un puntatore a str1 e lo passo a sscanf() che mi legge l'input dalla stringa str1 e me
            //lo formatta salvandolo su buffer, poi metto il contenuto del buffer su file
            else if (check2 == 1) {
                sprintf(str2, "%c", ch3);
                //printf("%s ", str2);
                strcat(str1, str2);
                //printf("%s ", str1);
                sscanf(str1, "%x", buffer);
                //printf("%s", buffer);
                fprintf(f3, "%s", buffer);
                check2 = -1;
            }
        }
        check2++;
    }
    fclose(f2);
    fclose(f3);
   
   
    //int ciao;
    //scanf("%x", &ciao);
    //printf("\n%c\n", ciao);
   
    //char *sk = "47";
    //char buffer[10];
    //sscanf(sk, "%x", buffer);
    //printf("\n%s\n", buffer);
   

    pid_t pid = fork();
    if (pid == 0) {
        if (argc == 6) {
            execl("/bin/dd", "dd", "if=file3.bin", "of=file4.bin", argv[3], argv[4], argv[5], "status=none", NULL);
        }
        else if (argc == 5) {
            execl("/bin/dd", "dd", "if=file3.bin", "of=file4.bin", argv[3], argv[4], "status=none", NULL);
        }
        else if (argc == 4) {
            execl("/bin/dd", "dd", "if=file3.bin", "of=file4.bin", argv[3], "status=none", NULL);
        }
       
    }

    //aspetto che il processo figlio muoia
    wait(NULL);
   
    //apro il file file4.bin dove ho messo la traduzione (output di dd) e
    //apro il file di output per scriverci sopra
    out = fopen(argv[2], "wb+");
    f4 = fopen("file4.bin", "rb");
    int chout = 0;
    while (chout != EOF) {
        if ((chout = getc(f4)) != EOF) {
            putc(0xf0 | (chout >> 4), out);
            putc((chout << 4) | 0x0f, out);
            //printf("%c ", chout);
        }
    }
    fclose(out);
    fclose(f4);



  return 0;
}
