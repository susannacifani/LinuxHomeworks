#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<strings.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fnmatch.h>


void sprint(char *dir, int livello, int spazio, char *printLiv[], char *opzioni[], int* numdir, int* numfile);
bool startsWith(const char *a, const char *b) {
    if (strncmp(a, b, strlen(b)) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int main(int argc, char *argv[]){   
    int opt;
    //array[0] = a, array[1] = p, array[2] = P, array[3] = '137.bi?'
    char *array[4] = {NULL};
    FILE *stderr;
    while((opt = getopt(argc, argv, ":apP:")) != -1){
        switch(opt) {
            case 'a': ;
                array[0] = "a";
                break;
            case 'p':
                array[1] = "p";
                //printf("options: %c\n", opt);
                break;
            case 'P':
                array[2] = "P";
                array[3] = optarg;
                //printf("match: %s\n", optarg);
                break;
            case '?':
                if (array[2] != "P") {
                    fprintf(stderr, "Usage: %s %s\n", argv[0], "[-P pattern] [-ap] [dirs]");
                    exit(20);
                    break;
                }
        }
    }

 
    int d = 0;
    int f = 0;
    char *printArr[100];
    printArr[0] = "0";
   
   
    //se una delle directory è un file, mi stampa nome del file e [error opening dir because of being not a dir]; 
    //al termine dell’esecuzione, ho l’exit status 10
    int el = optind;
    for(el; el < argc; el++){
        char *string = strrchr(argv[el], '.');
        if ((strcmp(string, ".txt")) == 0 || (strcmp(string, ".bin")) == 0) {
            fprintf(stderr, "%s %s\n", argv[el], "[error opening dir because of being not a dir]");
            exit(10);
        }

    }
   
    for(; optind < argc; optind++){
        printf("%s\n", argv[optind]);
        sprint(argv[optind], 0, 0, printArr, array, &d, &f);


    }
    if (f == 1) {
        printf("\n%d directories, %d file\n", d, f);
    }
    else {
        printf("\n%d directories, %d files\n", d, f);
    }
   
 

 
    return 0;
 
}






void permissions(char *szPath, char *name, char *confname, char *type, char *printLiv[], int livello) {
    struct stat fs;
    char *modeval[13];
    if (lstat(szPath, &fs) == -1) {
        printf("errore\n");
    }
    else {
        if (type == "f") {
            modeval[0] = "-";
        }
        else if (type == "d") {
            modeval[0] = "d";
        }
        else if (type == "l") {
            modeval[0] = "l";
        }
        modeval[1] = (fs.st_mode & S_IRUSR) ? "r" : "-";
        modeval[2] = (fs.st_mode & S_IWUSR) ? "w" : "-";
        modeval[3] = (fs.st_mode & S_IXUSR) ? "x" : "-";
        modeval[4] = (fs.st_mode & S_IRGRP) ? "r" : "-";
        modeval[5] = (fs.st_mode & S_IWGRP) ? "w" : "-";
        modeval[6] = (fs.st_mode & S_IXGRP) ? "x" : "-";
        modeval[7] = (fs.st_mode & S_IROTH) ? "r" : "-";
        modeval[8] = (fs.st_mode & S_IWOTH) ? "w" : "-";
        modeval[9] = (fs.st_mode & S_IXOTH) ? "x" : "-";
        modeval[10] = '\0';
        if (type == "l") {
            if (name == confname) {
                printf("`-- [%s%s%s%s%s%s%s%s%s%s]  %s", modeval[0], modeval[1], modeval[2],
                modeval[3], modeval[4], modeval[5], modeval[6], modeval[7], modeval[8], modeval[9], name);
                printLiv[livello+1] = "s";
            }
            else {
                printf("|-- [%s%s%s%s%s%s%s%s%s%s]  %s", modeval[0], modeval[1], modeval[2],
                modeval[3], modeval[4], modeval[5], modeval[6], modeval[7], modeval[8], modeval[9], name);
                printLiv[livello+1] = "p";
            }
        }
        else {
           
            if (name == confname) {
                printf("`-- [%s%s%s%s%s%s%s%s%s%s]  %s\n", modeval[0], modeval[1], modeval[2],
                modeval[3], modeval[4], modeval[5], modeval[6], modeval[7], modeval[8], modeval[9], name);
                printLiv[livello+1] = "s";
            }
            else {
                printf("|-- [%s%s%s%s%s%s%s%s%s%s]  %s\n", modeval[0], modeval[1], modeval[2],
                modeval[3], modeval[4], modeval[5], modeval[6], modeval[7], modeval[8], modeval[9], name);
                printLiv[livello+1] = "p";
            }

        }
    }
 
}




void sprint(char *dir, int livello, int spazio, char *printLiv[], char *opzioni[], int* numdir, int* numfile) {
    struct dirent **nameList;
    int n = scandir(dir, &nameList, NULL, alphasort);
    int sp = 0;
   
    int indice = 0;
    int k = 0; //tot elementi nella cartella
    int dd = 0; //tot directory nella cartella
    int ff = 0; //tot file nella cartella
    if (n < 0) {
        printf("Errore\n");
    }
    else {
        int j = 0;
        while (j < n) {
            //gestione casi -P: controllo subito se il file fa match
            int jmatch = 0;
            if (opzioni[2] == "P") {
                int r = fnmatch(opzioni[3], nameList[j]->d_name, 0);
                if (r == 0) {
                    jmatch = 1;
                }
            }
           
            //se non c'è -a e la directory/file non inzia con . la prendo, altrimenti no
            //così mi skippa in automatico anche . e .. (da gestire invece nel caso di -a)
            //OPPURE
            //se c'è -a prendo tutto
            if (((opzioni[0] != "a") && (startsWith(nameList[j]->d_name, ".") == 0)) || (opzioni[0] == "a")) {
                k++;
                //printf(" %s\n", nameList[j]->d_name);
                switch(nameList[j]->d_type) {
                    case DT_DIR:
                        dd++;
                        indice = j;
                        break;
                    case DT_REG:
                    case DT_LNK:
                        if (((opzioni[2] == "P") && (jmatch == 1)) || (opzioni[2] != "P")) {
                            ff++;
                            indice = j;
                        }
                        break;
                }
            }

            j++;
        }
        //tolgo le directory . e .. dal totale
        if (opzioni[0] == "a") {
            k = k-2;
            dd = dd-2;
        }
       
        //int sk = dd+ff;
        //j = n (tutto), dd+ff sono gli elementi da stampare, indice è l'indice dell'ultimo elemento (quello da stampare)
        //printf("cartella j: %s, j: %d, tot: %d, indice: %d\n", nameList[j-1]->d_name, j-1, sk, indice);
        //if (indice > 0) {
            //printf("cartella strana: %s\n", nameList[indice]->d_name);
        //}

        //ha senso perchè io devo considerare TUTTI gli elementi nella cartella, anche ., .. e quelli nascosti
        //anche quando non ho -a, infatti quegli elementi esistono SEMPRE e quindi devo considerarli
        //con -P il problema è che l'ultimo elemento che devo stampare non è necessariamente l'ultimo presente nella cartella
        //(invece con e senza -a stampo SEMPRE l'ultimo elemento della cartella perchè ad es quelli nascosti sono
        //all'inizio e mai alla fine), allora se ho -P devo introdurre un contatore di directory e stampare l'ultima cartella
        //(non l'ultimo elemento che sicuramente è un file). con i file ho gli stessi problemi perchè non per forza è
        //l'ultimo elemento nella cartella a fare match, magari fa match solo il secondo e devo stampare quello come se
        //fosse l'ultimo => quindi introduco un contatore in generale che mi tiene traccia solo dell cartelle e dei file
        //che fanno match, così fa il confronto
       
        //caso -P: per ogni cartella mi devo salvare l'indice dell'ultimo elemento da stampare
        //lo posso fare anche normalmente, così non ho ulteriori distinzioni di gestione dei casi
       
        *numdir += dd;
        *numfile += ff;
       
        //printf("\nj è: %d\n", j);

      
      
       
        int i = 0;
        while(i < n){
            int match = 0;
            //serve per i link simbolici prima dello switch, altrimenti ho:
            //a label can only be part of a statement and a declaration is not a statement
            char pth [1024];
            int l = snprintf(pth, sizeof(pth)-1, "%s/%s", dir, nameList[i]->d_name);
            pth[l] = 0;
            char buf[1024];
            ssize_t length;
         
            switch(nameList[i]->d_type) {
                //se è una directory
                case DT_DIR:
                    //skippo le directory . e .. e quelle che iniziano con il punto
                    if ((strcmp(nameList[i]->d_name, ".") == 0) || (strcmp(nameList[i]->d_name, "..") == 0) || (opzioni[0] != "a") && (startsWith(nameList[i]->d_name, ".") == 1)) {
                        //continue; siccome non funziona lascio l'if vuoto
                    }
                    //gestione opzione -a
                    else if ((opzioni[0] == "a") && (startsWith(nameList[i]->d_name, ".") == 1)) {
                        for (int j = 0; j < livello+1; j++) {
                            if (printLiv[j] == "p") {
                                printf("|   ");
                            }
                            else if (printLiv[j] == "s") {
                                printf("    ");
                            }
                            else {
                                continue;
                            }
                        }
                      
                        //se c'è l'opzione -p stampo anche i permessi
                        if (opzioni[1] == "p") {
                            char szPath [1024];
                            int len = snprintf(szPath, sizeof(szPath)-1, "%s/%s", dir, nameList[i]->d_name);
                            szPath[len] = 0;
                            //printf("AOs: %s\n", szPath);
                            permissions(szPath, nameList[i]->d_name, nameList[indice]->d_name, "d", printLiv, livello);
                        }
                        //se non 'cè l'opzione -p stampo come al solito
                        else {
                            if (nameList[i]->d_name == nameList[indice]->d_name) {
                                printf("`-- %s\n", nameList[i]->d_name);
                                sp++;
                                printLiv[livello+1] = "s";
                            }
                            else {
                                printf("|-- %s\n", nameList[i]->d_name);
                                printLiv[livello+1] = "p";
                            }
                        }
                      
                        char path [1024];
                        int len = snprintf(path, sizeof(path)-1, "%s/%s", dir, nameList[i]->d_name);
                        path[len] = 0;
                        //printf("  %s: %d\n", nameList[i]->d_name, sp);
                        sprint(path, livello+1, spazio+sp, printLiv, opzioni, numdir, numfile);
                    }
                    //casi senza -a
                    else {
                        for (int j = 0; j < livello+1; j++) {
                            if (printLiv[j] == "p") {
                                printf("|   ");
                            }
                            else if (printLiv[j] == "s") {
                                printf("    ");
                            }
                            else {
                                continue;
                            }
                        }
                       
                      
                        //se c'è l'opzione -p stampo anche i permessi
                        if (opzioni[1] == "p") {
                            char szPath [1024];
                            int len = snprintf(szPath, sizeof(szPath)-1, "%s/%s", dir, nameList[i]->d_name);
                            szPath[len] = 0;
                            //printf("AOs: %s\n", szPath);
                            permissions(szPath, nameList[i]->d_name, nameList[indice]->d_name, "d", printLiv, livello);
                        }
                        //se non 'cè l'opzione -p stampo come al solito
                        else {
                            if (nameList[i]->d_name == nameList[indice]->d_name) {
                                printf("`-- %s\n", nameList[i]->d_name);
                                sp++;
                                printLiv[livello+1] = "s";
                            }
                            else {
                                printf("|-- %s\n", nameList[i]->d_name);
                                printLiv[livello+1] = "p";
                            }
                        }

                        char path [1024];
                        int len = snprintf(path, sizeof(path)-1, "%s/%s", dir, nameList[i]->d_name);
                        path[len] = 0;
                        //printf("path: %s\n", path);
                        //printf("  %s: %d\n", nameList[i]->d_name, sp);
                        sprint(path, livello+1, spazio+sp, printLiv, opzioni, numdir, numfile);
                    }
                  

                  
                  
                  
                    break;
                //se è un file
                case DT_REG:
                    //gestione casi -P: controllo subito se il file fa match
                    if (opzioni[2] == "P") {
                        int r = fnmatch(opzioni[3], nameList[i]->d_name, 0);
                        if (r == 0) {
                            match = 1;
                        }
                    }
                       
                    //gestione opzione -a
                    if ((opzioni[0] == "a") && (startsWith(nameList[i]->d_name, ".") == 1)) {
                        if (((opzioni[2] == "P") && (match == 1)) || (opzioni[2] != "P")) {
                            for (int j = 0; j < livello+1; j++) {
                                if (printLiv[j] == "p") {
                                    printf("|   ");
                                }
                                else if (printLiv[j] == "s") {
                                    printf("    ");
                                }
                                else {
                                    continue;
                                }
                            }

                            //se c'è l'opzione -p stampo anche i permessi
                            if (opzioni[1] == "p") {
                                char szPath [1024];
                                int len = snprintf(szPath, sizeof(szPath)-1, "%s/%s", dir, nameList[i]->d_name);
                                szPath[len] = 0;
                                //printf("AOs: %s\n", szPath);
                                permissions(szPath, nameList[i]->d_name, nameList[indice]->d_name, "f", printLiv, livello);
                            }
                            //se non 'cè l'opzione -p stampo come al solito
                            else {
                                if (nameList[i]->d_name == nameList[indice]->d_name) {
                                    printf("`-- %s\n", nameList[i]->d_name);
                                    sp++;
                                    printLiv[livello+1] = "s";
                                }
                                else {
                                    printf("|-- %s\n", nameList[i]->d_name);
                                    printLiv[livello+1] = "p";
                                }
                            }
                        }
                    }
             
             
                    //casi senza -a: stampo i file che iniziano senza punto (nel caso in cui non ci sia -a)
                    else if (startsWith(nameList[i]->d_name, ".") == 0) {
                        //sia per casi con -P che hanno match, sia senza -P
                        if (((opzioni[2] == "P") && (match == 1)) || (opzioni[2] != "P")) {
                            for (int j = 0; j < livello+1; j++) {
                                if (printLiv[j] == "p") {
                                    printf("|   ");
                                }
                                else if (printLiv[j] == "s") {
                                    printf("    ");
                                }
                                else {
                                    continue;
                                }
                            }
                       
                            //se c'è l'opzione -p stampo anche i permessi (vale per casi con e senza -P)
                            if (opzioni[1] == "p") {
                                char szPath [1024];
                                int len = snprintf(szPath, sizeof(szPath)-1, "%s/%s", dir, nameList[i]->d_name);
                                szPath[len] = 0;
                                //printf("AOs: %s\n", szPath);
                                permissions(szPath, nameList[i]->d_name, nameList[indice]->d_name, "f", printLiv, livello);
                            }
                            //se non 'cè l'opzione -p stampo come al solito
                            else {
                                if (nameList[i]->d_name == nameList[indice]->d_name) {
                                    printf("`-- %s\n", nameList[i]->d_name);
                                    sp++;
                                    printLiv[livello+1] = "s";
                                }
                                else {
                                    printf("|-- %s\n", nameList[i]->d_name);
                                    printLiv[livello+1] = "p";
                                }
                            }
                        }  
                    }
                    break;
                   
                   
                //se è un link simbolico
                case DT_LNK:
                    //gestione casi -P: controllo subito se il file fa match
                    if (opzioni[2] == "P") {
                        int r = fnmatch(opzioni[3], nameList[i]->d_name, 0);
                        if (r == 0) {
                            match = 1;
                        }
                    }
                    if ((length = readlink(pth, buf, sizeof(buf)-1)) != -1) {
                        buf[length] = '\0';
                        if (((opzioni[2] == "P") && (match == 1)) || (opzioni[2] != "P")) {
                            for (int j = 0; j < livello+1; j++) {
                                if (printLiv[j] == "p") {
                                    printf("|   ");
                                }
                                else if (printLiv[j] == "s") {
                                    printf("    ");
                                }
                                else {
                                    continue;
                                }
                            }
                          
                            //se c'è l'opzione -p stampo anche i permessi
                            if (opzioni[1] == "p") {
                                char szPath [1024];
                                int len = snprintf(szPath, sizeof(szPath)-1, "%s/%s", dir, nameList[i]->d_name);
                                szPath[len] = 0;
                                //printf("AOs: %s\n", szPath);
                                permissions(szPath, nameList[i]->d_name, nameList[indice]->d_name, "l", printLiv, livello);
                                printf(" -> %s\n", buf);
                            }
                            //se non 'cè l'opzione -p stampo come al solito
                            else {
                                if (nameList[i]->d_name == nameList[indice]->d_name) {
                                    printf("`-- %s -> %s\n", nameList[i]->d_name, buf);
                                    sp++;
                                    printLiv[livello+1] = "s";
                                }
                                else {
                                    printf("|-- %s -> %s\n", nameList[i]->d_name, buf);
                                    printLiv[livello+1] = "p";
                                }
                            }
                        }
                    }
                 
                    break;
                 
            }
            free(nameList[i]);
            i++;
         
        }
     
        free(nameList);
       
     
    }
  
 
}
