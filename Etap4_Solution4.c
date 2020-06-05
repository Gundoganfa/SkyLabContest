#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{ 
    time_t t;
    int rSec1, rSec2, i, yyil, yay, yhafta, ygun, ysaat, ydakika, ysaniye;
    unsigned int min, max, seconds, kalan, xsaniye, xdakika, xsaat, xgun, xhafta, xay, xyil;

    // Seed random number generator
    srand((unsigned)time(&t));
    
    min=4000000000;
    max=0;

    //paralel evrende geçen saniye atama
    rSec1 = rand() % 1562101200; // integer limitine takilmamak icin gereken degerin yarisini 
    rSec2 = rand() % 1562101200; // 2 kere randlayip 
    seconds = (unsigned int) (rSec1 + rSec2 + 31557600); //unsigned int rand elde ettik. (32 bit shift ile kaydırıp cift randlamak da aynı isi gorur)
    
	kalan = seconds; // ana degeri koruma aliskanligi
        
    //paralel evrende geçen saniyeleri böle modlaya gidelim... 60 sn 1 dk, 60dk 1 saat, 48 saat 1 gün, 10 gün 1 hafta, 4 hafta 1 ay, 10 ay 1 yıl...
    xsaniye = kalan % 60; kalan /= 60;
    xdakika = kalan % 60; kalan /= 60;
    xsaat = kalan % 48; kalan /= 48;
    xgun = kalan % 10; kalan /= 10;
    xhafta = kalan % 4; kalan /= 4;
    xay = kalan % 10; xyil = kalan / 10;
    
    printf("baslangıc: 3100 yıl 8 ay 2 hafta 5 gun 0 saat 0 dakika 0 saniye idi.\n");
    printf("gecen:     %u yıl %u ay %u hafta %u gun %u saat %u dakika %u saniye gecti\n", xyil, xay, xhafta, xgun, xsaat, xdakika, xsaniye);
    
    yyil = 3100;
    yay = 8;
    yhafta = 2;
    ygun = 5;
    ysaat = 0;
    ydakika = 0;
    ysaniye = 0;
    
    ysaniye += (int)xsaniye;
    if (ysaniye >= 60) {
        ysaniye -= 60;
        ydakika++;
    }
    
    ydakika += (int)xdakika;
    if (ydakika >= 60) {
        ydakika -= 60;
        ysaat++;
    }
    
    ysaat += (int)xsaat;
    if (ysaat >= 48) {
        ysaat -= 48;
        ygun++;
    }
    
    ygun += (int)xgun;
    if (ygun >= 10) {
        ygun -= 10;
        yhafta++;
    }
    
    yhafta += (int)xhafta;
    if (yhafta >= 4) {
        yhafta -= 4;
        yay++;
    }
    
    yay += (int)xay;
    if (yay >= 10) {
        yay -= 10;
        yyil++;
    }
    
    yyil += (int)xyil;
    
    printf("Mevcut Tarih: %u yıl %u ay %u hafta %u gun\n Mevcut Saat : %u saat %u dakika %u saniye geciyor.\n", yyil, yay+1, yhafta+1, ygun+1, ysaat, ydakika, ysaniye);
    return 0;
}
















