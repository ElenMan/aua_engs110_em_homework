#include <stdio.h> 
int main()
{
int x,y,bit;
 printf("Enter any number: ");
    scanf("%d", &x);
printf("Enter nth bit to check (0-31): ");
    scanf("%d", &y);
bit = (x >> y) & 1;

    printf("The %d bit is set to %d", y, bit);

    return 0;
}
