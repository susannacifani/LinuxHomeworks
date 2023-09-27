#conf.0.txt 9vvz5lcb3q9.log 9y39di8fa9yst7ykx1xt7s3zphnjfctc9mnlmolq.log gdpuidtk3n36o0vsvogfaug8n3hklsv.log gtm7dy1786cmm2wksjqgn6yif8m1frxdt.5.zy.log iwqbto7u76byqbz4qopl8ywv2.6h3loatvksnvcy44q2w.log lz59rzf5x8zdd46tdread.log v2raw00jiwmxk0zgb0n86f329t9j2jn26oh6dms6ko5xb6.ea.log x1m7ycnxrd3rv463a4konyf.log
#conf.6.txt qpch2vefs218fjonj9wnqorqopao0a1si2y0zx3ej13.log wtcfo2yht8ccv.log 2sc..ciaxt3b0m7yk.tb5zuuwq00hv8sutwc5trfmyw.log 046ylzl54ec3sla.ynf1t40xnc2t5mxxqmhp3.log yn7rw4uaueot8o7c.log n3xjedszv9gf4jhkjm7le2f3cp4.log
#conf.3.txt li4yaiaya2zi8iumw.shk8jhbgo2isuxeo8k5t.erno.log gmgin27tppe12c6yhmhgwxqe5n6anicg.log 8ma8ccraa01q85gbhni0s66h6h4lq4nxhgjk2.log wwr3rk5f6zh.log jtacf7htmt1gqwqjkst2kyradjzabwlan2swos0wmyn0vt7rvs.log cwvfvoa7m7lxmgr7yetupfd.log xyt88unyyop1xjfckme3yja0zgxn46pcnqtitp8bsxiy02mzc.log fxq3hsocvgpnsgx.log d4bdgbb9x0.log

function lim_inf(fday, fmonth, fyear, fhour, d, m, y, h, arra) {
    #print("\n")
    #print fhour, h
    split(fhour, forario, ":")
    split(h, orario, ":")
    #for (el in forario) {printf "%s ", forario[el]}
    #for (el in orario) {printf "%s ", orario[el]}
    #print(length(orario))
    #print(orario[1])
    split(forario[length(forario)], fms, ".")
    #for (el in fms) {printf "%s ", fms[el]}
    split(orario[length(orario)], ms, ".")
    #for (el in ms) {printf "%s ", ms[el]}
    #se manca data from, il controllo della data inferiore passa come true
    if (arra[0] == "from") {
        if (y > fyear) { return 1 }
        else if (y < fyear) { return 0 }
        else if (y == fyear) {
            if (m > fmonth) { return 1 }
            else if (m < fmonth) { return 0 }
            else if (m == fmonth) {
                if (d > fday) { return 1 }
                else if (d < fday) { return 0 }
                else if (d == fday) {
                    #print("gestione orario")
                    #gestisco ore
                    if (orario[1] > forario[1]) { return 1 }
                    else if (orario[1] < forario[1]) { return 0 }
                    else if (orario[1] == forario[1]) {
                        #gestisco minuti
                        if (orario[2] > forario[2]) { return 1 }
                        else if (orario[2] < forario[2]) { return 0 }
                        else if (orario[2] == forario[2]) {
                        #gestione secondi e millisecondi
                            #se ho solo secondi nel file e nella conf ho anche i millisecondi
                            if (length(ms) == 1 && length(fms) == 2) {
                                #se i secondi sono uguali, allora so che il file sarà minore perchè non
                                #ha proprio i millisecondi che invece conf ha es. conf = 4.3 e file = 4
                                if (ms[1] == fms[1]) { return 0 }
                                #es. conf = 4.3 e file = 5
                                else if (ms[1] > fms[1]) { return 1 }
                                #es. file = 4.3 e conf = 5
                                else if (ms[1] < fms[1]) { return 0 }
                            }
                           
                            #se ho solo secondi nella conf e nel file ho anche i millisecondi
                            else if (length(fms) == 2 && length(ms) == 1) {
                                #se i secondi sono uguali, allora so che file è maggiore es. file = 4.3 e conf = 4
                                if (fms[1] == ms[1]) { return 1 }
                                #es. file = 4.3 e conf = 5
                                else if (fms[1] > ms[1]) { return 0 }
                                #es. file = 5 e conf = 4.3
                                else if (fms[1] < ms[1]) { return 1 }
                            }
                           
                            #se ho secondi e millisecondi in entrambi
                            else if (length(fms) == 2 && length(ms) == 2) {
                                #es. file = 4.3 e conf = 5.4
                                if (fms[1] > ms[1]) { return 0 }
                                #es. file = 5.4 e conf = 4.3
                                else if (fms[1] < ms[1]) { return 1 }
                                #es. file = 4... e conf = 4...
                                else if (fms[1] == ms[1]) {
                                if (fms[2] == ms[2]) { return 1 }
                                else if (fms[2] > ms[2]) { return 0 }
                                else if (fms[2] < ms[2]) { return 1 }
                               
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else {
    return 1
    };
}



function lim_sup(tday, tmonth, tyear, thour, d, m, y, h, arra) {
    split(thour, torario, ":")
    split(h, orario, ":")
    split(torario[length(torario)], tms, ".")
    split(orario[length(orario)], ms, ".")
    #se manca data to, il controllo della data inferiore passa come true
    #print m, tmonth
    if (arra[1] == "to") {
        if (y < tyear) { return 1 }
        else if (y > tyear) { return 0 }
        else if (y == tyear) {
            if (m < tmonth) { return 1 }
            else if (m > tmonth) { return 0 }
            else if (m == tmonth) {
                if (d < tday) { return 1 }
                else if (d > tday) { return 0 }
                else if (d == tday) {
                    #print("gestione orario")
                    #gestisco ore
                    if (orario[1] < torario[1]) { return 1 }
                    else if (orario[1] > torario[1]) { return 0 }
                    else if (orario[1] == torario[1]) {
                        #gestisco minuti
                        if (orario[2] < torario[2]) { return 1 }
                        else if (orario[2] > torario[2]) { return 0 }
                        else if (orario[2] == torario[2]) {
                        #gestione secondi e millisecondi
                            #se ho solo secondi nel file e nella conf ho anche i millisecondi
                            if (length(ms) == 1 && length(tms) == 2) {
                                #se i secondi sono uguali, allora so che il file sarà minore perchè non
                                #ha proprio i millisecondi che invece conf ha es. conf = 4.3 e file = 4
                                if (ms[1] == tms[1]) { return 0 }
                                else if (ms[1] < tms[1]) { return 1 }
                                else if (ms[1] > tms[1]) { return 0 }
                            }
                           
                            #se ho solo secondi nella conf e nel file ho anche i millisecondi
                            else if (length(tms) == 2 && length(ms) == 1) {
                                #se i secondi sono uguali, allora so che file è maggiore es. file = 4.3 e conf = 4
                                if (tms[1] == ms[1]) { return 1 }
                                else if (tms[1] < ms[1]) { return 0 }
                                else if (tms[1] > ms[1]) { return 1 }
                            }
                           
                            #se ho secondi e millisecondi in entrambi
                            else if (length(tms) == 2 && length(ms) == 2) {
                                if (tms[1] < ms[1]) { return 0 }
                                else if (tms[1] > ms[1]) { return 1 }
                                else if (tms[1] == ms[1]) {
                                if (tms[2] == ms[2]) { return 1 }
                                else if (tms[2] < ms[2]) { return 0 }
                                else if (tms[2] > ms[2]) { return 1 }
                               
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else {
    return 1
    };
}




BEGIN {
#printa la riga eseguito con argomenti salvandoli nel vettore array
printf("Eseguito con argomenti ");
lungh = ARGC; j = 0;
for (i = 1; i < lungh; i++) {
array[j] = ARGV[i]
j++};
for (el in array) {
#printf "%s ", array[el]
ss = ss array[el]" "
}
#print(ss)
print substr(ss, 1, length(ss)-1);

#legge il file conf riga per riga e salva negli array
while ((getline line < ARGV[1]) > 0) {
    #print line #printa tutte le righe del file conf
    #splitto ogni riga di conf salvando in a[1] from/to/text e in a[2] il resto, ad ogni ciclo si sovrascrive
    split(line, a, "=")
    #print a[1] #from, to, text
    #print a[2] #1998/06/17 02:41:54, Wed Apr 18 21:31:43, Xjt
   
    #in ogni corrispettivo array ho inserito il contenuto di from/to/text splittato dagli spazi
    #e ogni volta salvo nell'array conf, nelle giuste posizioni, se ho trovato from/to/text, così
    #se nel file mancano, nello spazio corrispondente avrò un vuoto
    if (a[1] == "from") {
        split(a[2], from, " ")
        #print from[1] #1998/06/17
        #se la variabile esiste, la salvo e controllo se sia num o alfa
        if (from[1] != "") {
            conf[0] = "from"
            if (length(from[1]) != 3) {
                #print("data from num")
                #GESTIONE Y/M/D H: se è numerica
                #print from[1]
                split(from[1], b, "/")
                fy = b[1]
                fm = b[2]
                fd = b[3]
                fh = from[2]
                #print fd, fm, fy, fh
                }
            else {
                #print("data from alfa")
                #GESTIONE d m D H: se è alfanumerica
                if (from[1] == "Mon" || from[1] == "Tue" || from[1] == "Wed" || from[1] == "Thu" || from[1] == "Fri" || from[1] == "Sat" || from[1] == "Sun") {
                    fd = from[3]
                    fh = from[4]
                    fy = 2022
                    if (from[2] == "Jan") {fm = "01"};
                    if (from[2] == "Feb") {fm = "02"};
                    if (from[2] == "Mar") {fm = "03"};
                    if (from[2] == "Apr") {fm = "04"};
                    if (from[2] == "May") {fm = "05"};
                    if (from[2] == "Jun") {fm = "06"};
                    if (from[2] == "Jul") {fm = "07"};
                    if (from[2] == "Aug") {fm = "08"};
                    if (from[2] == "Sep") {fm = "09"};
                    if (from[2] == "Oct") {fm = "10"};
                    if (from[2] == "Nov") {fm = "11"};
                    if (from[2] == "Dec") {fm = "12"};
                    #print fd, fm, fy, fh
                }
            };
        };
    }
    else if (a[1] == "to") {
        split(a[2], to, " ")
        #print to[1] #Wed
        #se la variabile esiste, la salvo e controllo se sia num o alfa
        if (to[1] != "") {
            conf[1] = "to"
            if (length(to[1]) != 3) {
                #print("data to num")
                #print to[1]
                split(to[1], c, "/")
                ty = c[1]
                tm = c[2]
                td = c[3]
                th = to[2]
                #print td, tm, ty, th
                }
                #GESTIONE Y/M/D H: se è numerica
            else {
                #print("data to alfa")
                #GESTIONE d m D H: se è alfanumerica
                if (to[1] == "Mon" || to[1] == "Tue" || to[1] == "Wed" || to[1] == "Thu" || to[1] == "Fri" || to[1] == "Sat" || to[1] == "Sun") {
                    td = to[3]
                    ty = 2022
                    th = to[4]
                    if (to[2] == "Jan") {tm = "01"};
                    if (to[2] == "Feb") {tm = "02"};
                    if (to[2] == "Mar") {tm = "03"};
                    if (to[2] == "Apr") {tm = "04"};
                    if (to[2] == "May") {tm = "05"};
                    if (to[2] == "Jun") {tm = "06"};
                    if (to[2] == "Jul") {tm = "07"};
                    if (to[2] == "Aug") {tm = "08"};
                    if (to[2] == "Sep") {tm = "09"};
                    if (to[2] == "Oct") {tm = "10"};
                    if (to[2] == "Nov") {tm = "11"};
                    if (to[2] == "Dec") {tm = "12"};
                    #print td, tm, ty, th
                }
            };
        };
    }
    else if (a[1] == "text") {
        split(a[2], text, " ")
        #print a[2]
        #print text[1] #Xjt #con text= d printa d
        if (text[1] != "") {
        conf[2] = "text"};
    };
   
};

#for (e in conf) {
#print conf[e]};


}






{
if (ARGIND != 1) {
    #print $1;
    #data = $1;
    #print data;
    #GESTIONE Y/M/D H: se è numerica
    if (length($1) != 3) {
        split($1, e, "/")
        year = e[1]
        month = e[2]
        day = e[3]
        hour = $2
        #print day, month, year, hour
       
        #salVo ogni elemento della parte text in un array, quindi per il check devo controllarlo tutto
        #j = 0;
        stt = " "
        for (i = 3; i <= NF; i++) {
        stt = stt $i" "
        #stringa[j] = $i
        #j++
        };
        #for (el in stringa) { printf "%s ", stringa[el]};
        #print stt
        #print("\n")
       

       
        }
    else {
        #GESTIONE d m D H:
        if ($1 == "Mon" || $1 == "Tue" || $1 == "Wed" || $1 == "Thu" || $1 == "Fri" || $1 == "Sat" || $1 == "Sun") {
            day = $3
            year = 2022
            hour = $4
            if ($2 == "Jan") {month = "01"};
            if ($2 == "Feb") {month = "02"};
            if ($2 == "Mar") {month = "03"};
            if ($2 == "Apr") {month = "04"};
            if ($2 == "May") {month = "05"};
            if ($2 == "Jun") {month = "06"};
            if ($2 == "Jul") {month = "07"};
            if ($2 == "Aug") {month = "08"};
            if ($2 == "Sep") {month = "09"};
            if ($2 == "Oct") {month = "10"};
            if ($2 == "Nov") {month = "11"};
            if ($2 == "Dec") {month = "12"};
            #print day, month, year, hour
           
            #salVo ogni elemento della parte text in un array, quindi per il check dedvo controllarlo tutto
            #j = 0;
            stt = " ";
            for (i = 5; i <= NF; i++) {
            stt = stt $i" "
            #stringa[j] = $i
            #j++
            };
            #print stt
            #for (el in stringa) { printf "%s ", stringa[el]};
            #print("\n")
           
        }
    };
   




#r1 = lim_inf(fd, fm, fy, day, month, year, conf)
#print(r1)
#r2 = lim_sup(td, tm, ty, day, month, year, conf)
#print(r2)



#CONFRONTO MATCH STRINGA
inferiore = lim_inf(fd, fm, fy, fh, day, month, year, hour, conf)
superiore = lim_sup(td, tm, ty, th, day, month, year, hour, conf)
#print inferiore, superiore
#print("\n")
#print td, tm, ty, th
#print length(a[2])
#se c'è il testo faccio i vari check
if (conf[2] == "text") {
    if (inferiore == 1  && superiore == 1) {
    if (stt ~ a[2]) { check = 1 }
   
    #for (el in stringa) {
        #if (stringa[el] ~ a[2]) {
        #check = 1
        #printf "%s: %s\n", array[ARGIND-1], $0
        #for (i = 1; i <= NF; i++) { printf "%s ", $i };
        #}
    #};
   
    if (check == 1) { printf "%s: %s\n", array[ARGIND-1], $0 }
    }
}
#se manca il testo printo quello che ho
else {
    if (inferiore == 1  && superiore == 1) {
    printf "%s: %s\n", array[ARGIND-1], $0
    #for (i = 1; i <= NF; i++) { printf "%s ", $i };
    }
};



delete(stringa)
stt = ""
check = 0

};
   

}



END{
#printf("\nFine\n");
#s = TJsEFzOawROR2GWXjtDSWuDGm8i0nN57pmm8w4pz2Z
#t = Xjt
#if (index(t, s) != 0) { print("va bene") }
}
