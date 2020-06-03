#include <stdio.h>

#define Arrlen 10

void ctrlArray(int* arr, int size);

int main()
{
    int arr[Arrlen], i, size;
    
    //1 test
    size = 6;
    arr[0] = 3; arr[1] = 6; arr[2] = 4; arr[3] = 5; arr[4] = 2;  arr[5] = 1;
    ctrlArray(&arr[0], size);
    //2 test
    size = 6;
    arr[0] = 1; arr[1] = 3; arr[2] = 3; arr[3] = 4; arr[4] = 5; arr[5] = 2;
    ctrlArray(&arr[0], size);
    //3 test
    size = 6;
    arr[0] = 1; arr[1] = 5; arr[2] = 3; arr[3] = 4; arr[4] = 7; arr[5] = 2;
    ctrlArray(&arr[0], size);
    //4 test
    size = 6;
    arr[0] = 2; arr[1] = 1; arr[2] = 3; arr[3] = 5; arr[4] = 6; arr[5] = 7;
    ctrlArray(&arr[0], size);

    return 0;
}


void ctrlArray(int* arr, int size) {
    int numArr[Arrlen]; // kontrol arrayi
    int i, tmp, result;

    // kontrol arrayini 0 ile doldur
    for (i=0; i<Arrlen; i++) { 
        numArr[i] = 0;
    }

    // array limitlerinden tasmadan
    // girilen arraydaki elemanlarla kontrol arrayini eslestirelim
    // kontrol arrayinin tum elemanları 0 ile baslatilir.
    // kontrol arrayinin indisi, girilen arrayin elemani ise, kontrol arrayinin 
    // ilgili elemaninin degeri, 1 artacak.
    // kontrol arrayinin elemanları 0 ise, o rakam girilen arrayde yoktur.
    // kontrol arrayinin elemanları 2 ve üstü ise, o rakam 1'den fazla kez girilmiştir.
    // kontrol arrayinin elemanları 1 ise, o rakam girilen arrayde 1 kere girilmiştir.

    for (i=0; i<size; i++) {
        tmp = *(arr+i);
        printf("A [%d] = %d\n",i,tmp);
        if ((tmp < Arrlen)&&(tmp>=1)) {
            numArr[tmp-1]++;
        }
    }
    
    // kontrol arrayinin elemanları 1 oldukça i değişkenini 1 artıralım.
    for (i=0; ((numArr[i] == 1) && (i<size)); i++) {
        ;;
    }
    
    // i değişkeni array boyutuna ulastı mı? 
    //printf("ind=%d, size=%d\n",i,size);
    result = (i==size)?1:0;
    printf("Çıktı:%d\n\n", result);

    return;
}