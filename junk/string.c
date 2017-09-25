#include <stdio.h>

int main(void) {
    const char lookupE[] = "1111886:6:??AAFFHHMMOO55557799@@>>>BBBGGIIKK";
    for (int i=0; i<sizeof(lookupE)-1; i++) {
       unsigned int x = (lookupE[i]-64) & 0xFF;
       printf("\\x%02X", x);
    }
    putchar('\n');

    const char lookupC[] = "C@=::C@@==@=:C@=:C@=:C531/513/5131/31/531/53";
    for (int i=0; i<sizeof(lookupC)-1; i++) {
       unsigned int x = (lookupC[i]-64) & 0xFF;
       printf("\\x%02X", x);
    }
    putchar('\n');

    return 0;
}
