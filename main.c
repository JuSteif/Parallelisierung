#include <stdio.h>
#include <pthread.h>

//Makro um die Laenge des Testarrays festzulegen, am besten nicht zu viele Zahlen;)
#define ARR_LEN 10

//Unsere Zufallszahl, ich weiß globale Variablen sind schlecht, ist aber die einfachste Möglichkeit eine für alle Threads zugängliche Variable zu erzeugen.
int result;

//Array zum Auswählen, was in result hineingeschrieben werden kann(Nicht zwingend nötig)
int arr[] = {2, 4, 7, 5, 9, 1, 0, 6 , 8, 3};

//Funktion für einen Thread
void randomNum(unsigned int* ind){
    //Überschreiben des Results mit einem Wert aus dem Array arr, solange der Thread lebt
    while(1){
        result = (int)arr[*ind];
        *ind > 8 ? *ind = 0: (*ind)++;
    }
}

//Schreibt in result eine neue Zufallszahl
void random(){
    //Array mit Threads, die die Funktion randomNum ausführen
    pthread_t threads[5];

    for(unsigned int i = 0; i < 5; i++){
        //Ich vertraue keinen Zählvariablen in Schleifen, wenn es um Parallelisierung geht
        unsigned int x = i;
        //Starten der Threads
        pthread_create(&threads[i], NULL, (void*)&randomNum, (void*)&x);
    }

    //Zähler, der den Main-Thread schlafen lägt
    int count = 0;
    while(count < 10){
        count++;
    }

    //Brutales ermorden der Threads
    for(int i = 0; i < 5; i++){
        pthread_cancel(threads[i]);
    }

    //Jetzt steht eine zufällige Zahl in result
}

int main(int argc, char** argv){
    printf("Zufallszahlen\n");

    //Funktionsaufruf um result mit Zufallszahl zu initalisieren
    random();
    //Ausgabe der zufälligen Zahl
    printf("%d\n", result);

//Test Region um die Zufallszahl zu überprüfen, Uninteressting!!!!!
/*
    int zufallsZahlen[ARR_LEN];
    for(int i = 0; i < ARR_LEN; i++){
        random();
        zufallsZahlen[i] = result;
    }

    for(int i = 0; i < ARR_LEN; i++){
        printf("%d\n", zufallsZahlen[i]);
    }

    int evaluation[10];
    for(int i = 0; i < 10; i++){
        evaluation[i] = 0;
    }
    for(int i = 0; i < ARR_LEN; i++){
        evaluation[zufallsZahlen[i]]++;
    }
    printf("Auswertung: \n");
    for(int i = 0; i < 10; i++){
        printf("%d: %d\n", i, evaluation[i]);
    }
//*/

    return 0;
}