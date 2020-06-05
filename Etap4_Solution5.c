#include <stdio.h>

int main()
{
    int val, divident, dignum, i, j;
    int binval[100];
    int maxCount = 0;
    int count = 0;
    int startCounting = 0;
        
    
    scanf("%d", &val);
    
    divident = val;
    dignum = 0;
    do {
        binval[dignum] = divident % 2;
        divident /= 2;
        dignum++;
    } while (divident != 0);

    // if we need binary value, we would need to inverse the binval array
    // but we only need the max (number of consequtive 0's between 1's)
    // so no need to inverse the array...

    maxCount = 0;
    count = 0;
    startCounting = 0;
    
    for (i=0; i<=dignum; i++) {
        if (binval[i]) { // if i'th digit is 1
            startCounting = 1; // start counting. never stop again.
        }
        
        if (binval[i] && (count > 0)) { // if i'th digit is 1 and count>0 then reset counter after checking the max value.
            startCounting = 1;
            if (count > maxCount )
                maxCount = count;
            count = 0;
        }
        //count zeros
        if (startCounting && (binval[i] == 0)) {
            count++;
        }
    }
    printf("%d\n", maxCount);
    
    return 0;
}