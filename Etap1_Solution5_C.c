// YTU Skylab Algorithm Games Challenge / for fun
// 1st Sprint, 2nd Question

// Basic Calculator Code Generator
// Fatih Gündoğan 30.05.2020 gundoganfa@gmail.com

#include <stdio.h>

void writeSum() {
    int i,j;
    for (i=0; i<=50; i++)
        for (j=0; j<=50; j++) {
            printf("  if (sayi1 == %d && islem == '+' && sayi2 == %d ){\n    printf(\"%d+%d = %d\");\n  }\n",i,j,i,j,i+j);
        }
    return;
}
void writeSub() {
    int i,j;
    for (i=0; i<=50; i++)
        for (j=0; j<=50; j++) {
            printf("  if (sayi1 == %d && islem == '-' && sayi2 == %d ){\n    printf(\"%d-%d = %d\");\n  }\n",i,j,i,j,i-j);
        }
    return;
}
void writeDiv() {
    int i,j;
    for (i=0; i<=50; i++)
        for (j=0; j<=50; j++) {
            if (j!=0) {
                printf("  if (sayi1 == %d && islem == '/' && sayi2 == %d ){\n    printf(\"%d/%d = %.2f\");\n  }\n",i,j,i,j,(float)i/j);
            } else { // prevent division by Zero.
                printf("  if (sayi1 == %d && islem == '/' && sayi2 == %d ){\n    printf(\"%d/%d = DIV ZERO!\");\n  }\n",i,j,i,j);
            }
        }
    return;
}
void writeMul() {
    int i,j;
    for (i=0; i<=50; i++)
        for (j=0; j<=50; j++) {
            printf("  if (sayi1 == %d && islem == '*' && sayi2 == %d ){\n    printf(\"%d*%d = %d\");\n  }\n",i,j,i,j,i*j);
        }
    return;
}

int main()
{
 
    printf("#include <stdio.h>\n");
    printf("int main()\n");
    printf("{\n");
    printf("  int sayi1, sayi2;\n  char islem;\n");
    printf("  scanf(\"%%d %%c %%d\", &sayi1, &islem, &sayi2);\n\n");
    
    writeSum();
    writeSub();
    writeDiv();
    writeMul();
	
    printf("\n  return 0;\n");
    printf("}\n");
    
    return 0;
}