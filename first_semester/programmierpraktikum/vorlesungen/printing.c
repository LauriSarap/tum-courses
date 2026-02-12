#include <stdio.h>

int main() {
    // Original: The "C" path is C:\Users%temp%
    // Escaped version below:
    printf("The \"C\" path is C:\\Users%%temp%%\n");
    
    return 0;
}