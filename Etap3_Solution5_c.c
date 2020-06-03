#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

struct urunliste {
    char isim[20];
    int kilo;
};

static int getLine (char *buff, size_t sz);

int main()
{
    int N, M; //tezgahta kac meyve var? M=kaç kg meyve alacak.
    int i, rc, arrlen, j, tmpkilo, priceSum;
    int fiyatlar[100]; // tezgahta 100 farklı fiyat olabilir
    struct urunliste liste[10], tmpurun; //Ali toplam maks 10 kg meyve alabilir
    char tmpisim[20];
    time_t t;
    
    // clear list
    for (i=0; i<100; i++) {
        fiyatlar[i] = 0;
    }
    for (i=0; i<10; i++) {
        liste[i].kilo = 0;
        strncpy(liste[i].isim, "", sizeof(liste[i].isim));
    }
    // init rand generator
    srand((unsigned)time(&t));       
    // get values
    scanf(" %d %d ", &N, &M); //printf("tezgahtaki meyve sayısı : %d\n%d kg meyve alacak.\n", N, M);
    // assign prices
    for (i=0; i<N; i++) {
        fiyatlar[i] = (rand() % 9) + 1;
    }

    // Meyve isimlerini alacagiz
    arrlen = 0;
    for (i=0; i<M; i++) {
        rc = getLine (tmpisim, sizeof(tmpisim)); // soruda stdin'den girilecek meyva ismine karakter sınırı koyulmadığı için scanf kullanamıyoruz...

        for (j=0; (j<M) && (strcmp(tmpisim, liste[j].isim) != 0); j++) {
			//girilen urun daha önce listeye eklenmiş mi, bütük liste boyunca kontrol edelim.
            ;;
        }
		
        if (j>=M) {
			// meyve yeni mevyedir.
			// meyve listeye daha once eklenmemis, listeye 1kg olarak ekle
            // printf("bu meyve listeye daha önce eklenmemiş!\n");
            strncpy(liste[arrlen].isim, tmpisim, sizeof(tmpisim));
            liste[arrlen].kilo++;
            arrlen++;  
        } else {
			// meyve listeye daha once eklenmis, kilosunu artır.
            // printf("bu meyve listede var!\n");
            liste[j].kilo++;
        }
    }

    // sort arrays
    // once meyve listemizi kg'ye göre listeleyelim.
    
    //bubble sort - meyveler kilosu kücük olandan büyük olana
    for (i = 0; i < arrlen-1; i++)      
        for (j = 0; j < arrlen-1-i; j++)  
            if (liste[j].kilo > liste[j+1].kilo)   {
                tmpurun = liste[j+1];
                liste[j+1] = liste[j];
                liste[j] = tmpurun;
            }
    // bubble sort / fiyatlar küçükten büyüğe
    for (i = 0; i < N-1; i++)      
        for (j = 0; j < N-1-i; j++)  
            if (fiyatlar[j] > fiyatlar[j+1])   {
                tmpkilo = fiyatlar[j+1];
                fiyatlar[j+1] = fiyatlar[j];
                fiyatlar[j] = tmpkilo;
            }
        for (i=0; i<N; i++) {
    }
    // en iyi senaryo - düşük fiyat
    priceSum = 0;
    for (i=0; i<arrlen; i++){
        priceSum += fiyatlar[i]*liste[i].kilo;
    }
    printf("%d ", priceSum);
    
    //bubble sort - meyveler kilosu büyük olandan küçük olana
    for (i = 0; i < arrlen-1; i++)      
        for (j = 0; j < arrlen-1-i; j++)  
            if (liste[j].kilo < liste[j+1].kilo)   {
                tmpurun = liste[j+1];
                liste[j+1] = liste[j];
                liste[j] = tmpurun;
            }
    // bubble sort / fiyatlar büyükten küçüğe
    for (i = 0; i < N-1; i++)      
        for (j = 0; j < N-1-i; j++)  
            if (fiyatlar[j] < fiyatlar[j+1])   {
                tmpkilo = fiyatlar[j+1];
                fiyatlar[j+1] = fiyatlar[j];
                fiyatlar[j] = tmpkilo;
            }

    // en kötü senaryo - yüksek fiyat
    priceSum = 0;
    for (i=0; i<arrlen; i++){
        priceSum += fiyatlar[i]*liste[i].kilo;
    }
    printf("%d\n", priceSum);

    return 0;
}

static int getLine (char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}