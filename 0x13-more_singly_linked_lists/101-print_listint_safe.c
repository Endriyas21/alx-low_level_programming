#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_listint_safe - Prints a listint_t linked list safely.
 * @head: Pointer to the head of the linked list.
 * Return: Number of nodes in the list.
 */
size_t print_listint_safe(const listint_t *head)
{
    size_t count = 0;
    const listint_t *current = head;
    const listint_t *check_loop = head;

    while (check_loop && check_loop->next)
    {
        check_loop = check_loop->next->next;
        if (check_loop == current)
        {
            printf("-> [%p] %d\n", (void *)current, current->n);
            exit(98);
        }
        current = current->next;
    }

    current = head;
    while (current)
    {
        printf("[%p] %d\n", (void *)current, current->n);
        current = current->next;
        count++;
    }

    return count;
}
