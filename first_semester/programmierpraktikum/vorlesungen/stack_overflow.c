#include <stdio.h>

void crash_me() {
    char buffer[1024]; // Take up 1KB per call
    crash_me();        // Call again without stopping
}

int main() {
    crash_me();
    return 0;
}