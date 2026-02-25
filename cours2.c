#include<stdio.h>
#include<string.h>

void greet(char *name, int age){
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "Hello %s, you are %d", name, age);
    printf("%s\n", buffer);
}

int main(){
    greet("Alice", 30);
    return 0;
}