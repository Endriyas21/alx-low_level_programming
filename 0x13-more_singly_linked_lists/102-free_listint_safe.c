#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * free_listint_safe - Frees a listint_t linked list safely.
 * @h: Pointer to the head of the linked list.
 * Return: Number of nodes that were freed.
 */
size_t free_listint_safe(listint_t **h)
{
    size_t count = 0;
    listint_t *current = *h;
    listint_t *next_node;

    while (current)
    {
        next_node = current->next;
        free(current);
        count++;
        if (next_node >= current)
        {
            *h = NULL;
            break;
        }
        current = next_node;
    }

    *h = NULL;
    return count;
}
