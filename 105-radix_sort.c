#include "sort.h"

/**
 * get_max - get the maximum value of an array of integers
 *
 * @array: array from which to get the maximum value
 * @size: size of the array
 *
 * Return: the maximum value of array
 */
static int get_max(int *array, size_t size)
{
size_t index = 0;
int max = 0;

while (index < size)
{
if (array[index] > max)
max = array[index];
index += 1;
}
return (max);
}

/**
 * list_push - push a value onto the end of a list of integers
 *
 * @list: pointer to the list of integers to which to push the value
 * @n: the value to push into the list
 */
static void list_push(listint_t **list, int n)
{
listint_t *last = *list;
listint_t *node = malloc(sizeof(listint_t));

node->n = n;

if (last)
{
while (last->next)
last = last->next;
node->next = NULL;
node->prev = last;
last->next = node;
}
else
{
node->next = NULL;
node->prev = NULL;
*list = node;
}
}

/**
 * list_pop - pop the first value from a list of integers
 *
 * @list: pointer to the list of integers from which to pop a value
 *
 * Return: the first value in a list of integers
 */
static int list_pop(listint_t **list)
{
listint_t *node = *list;
int n = node->n;

*list = node->next;
free(node);
return (n);
}

/**
 * alloc_buckets - dynamically allocate buckets for each digit
 *
 * @array: array of integers to be sorted
 * @size: number of elements in the array to be sorted
 * @factor: factor of digit on which to sort
 * @buckets: pointer to array of pointers to buckets
 */
static void alloc_buckets(
	const int *array, size_t size, int factor, listint_t *(*buckets)[10]
)
{
int n = 0;
size_t index = 0;
size_t bucket = 0;

while (index < size)
{
n = array[index++];
bucket = (n / factor) % 10;
list_push(&(*buckets)[bucket], n);
}
}

/**
 * radix_sort - sort an array of integers using the LSD radix sort algorithm
 *
 * @array: array of integers to be sorted
 * @size: number of elements in the array to be sorted
 */
void radix_sort(int *array, size_t size)
{
listint_t *buckets[10] = {0};
size_t bucket = 0;
size_t index = 0;
int max = 0;
int factor = 1;

if (array && size > 1)
{
for (max = get_max(array, size); max / factor; factor *= 10)
{
alloc_buckets(array, size, factor, &buckets);
for (bucket = 0, index = 0; bucket < 10; bucket += 1)
{
while (buckets[bucket])
{
array[index++] = list_pop(
&buckets[bucket]
);
}
}
print_array(array, size);
}
}
}
