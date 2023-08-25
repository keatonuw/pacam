#include <stdlib.h>
#include <stdio.h>

typedef void (*element_dtor)(void *e);

typedef struct list_node_s
{
  void *data;
  struct list_node_s *next;
} list_node_t;

typedef struct node_t
{
  struct node_t *next;
  list_node_t *incoming;
  void *data;
} node_t;

list_node_t *init_list(void *el)
{
  list_node_t *node = (list_node_t *)malloc(sizeof(list_node_t));
  node->data = el;
  node->next = NULL;
  return node;
}

void list_push(list_node_t **head, void *el)
{
  list_node_t *new_head = init_list(el);
  new_head->next = *head;
  *head = new_head;
}

void *list_pop(list_node_t **list)
{
  void *data = (*list)->data;
  list_node_t *prev = *list;
  *list = prev->next;
  free(prev);
  return data;
}

void free_list(list_node_t *node, element_dtor dtor)
{
  if (node->next != NULL)
  {
    free_list(node->next, dtor);
  }
  if (node->data != NULL)
  {
    dtor(node->data);
  }
  free(node);
}

void noop(void *ptr)
{
  return;
}

// int main(int argc, char **argv)
// {
//     list_node_t *list = init_list((void *)1);
//     list_push(&list, (void *)4);
//     for (int i = 1; i < 20; i++)
//     {
//         list_push(&list, (void *)i);
//     }
//     list_node_t *ptr = list;
//     while (ptr != NULL)
//     {
//         printf("Value = %lld\n", (int64_t)ptr->data);
//         ptr = ptr->next;
//     }
//     free_list(list, noop);
//     return EXIT_SUCCESS;
// }