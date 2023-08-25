#include <stdio.h>

/**
 * before_main - Prints "You're beat! and yet, you must allow,"
 *              and "I bore my house upon my back!" before main.
 */
void __attribute__((constructor)) before_main(void)
{
    printf("You're beat! and yet, you must allow,\nI bore my house upon my back!\n");
}

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
    printf("(A tortoise, having pretty good sense of a hare's nature, challenges one to a race.)\n");
    return (0);
}
