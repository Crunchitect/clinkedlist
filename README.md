# C Linked List

Reimplementing JS Array with linked list in C.

```c
int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
LinkedList* l = l_from(10, int, arr);
l_push(l, int, 4);
printf("%d\n", *(int*)l_at(l, -1));
printf("%d\n", *(int*)l_pop(l));
l_free(l);
```

See progress in [TODO.md](./TODO.md)
