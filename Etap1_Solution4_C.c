// YTU Skylab Algorithm Games Challenge / for fun
// 1st Sprint, 1st Question

// Add '7' in front of a given number. (no number in int limits will be entered).
// Fatih Gündoğan 30.05.2020 gundoganfa@gmail.com

#include <stdio.h>

int concatInt(int val) {
    int retVal, i;
	
	// Find how big the number is
    i = 1;
    do {
        i *= 10;
        retVal = val%i;
		
		// return if the modulo is the val(original number) itself 
		// found min(n)where (10^n > |val|).
    } while (retVal != val);
    
    return (val>0)?(retVal + 7*i):(retVal - 7*i);
}

int main()
{
    int number;
    scanf("%d", &number);
    printf("%d\n", concatInt(number));
    
    return 0;
}