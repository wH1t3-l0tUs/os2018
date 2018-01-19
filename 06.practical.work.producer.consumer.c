#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10
typedef struct 
{
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) 
{
	while ((first + 1) % BUFFER_SIZE == last) 
	{
	// do nothing -- no free buffer item
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item *consume() 
{
	item *i = malloc(sizeof(item));
	while (first == last) 
	{
	// do nothing -- nothing to consume
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}

item newItem(char a, int b, char c)
{
	item i;
	i.type = a;
	i.amount = b;
	i.unit = c;
	return i;
}

void Out(item x)
{
	if (x.type == 0)
		printf("Fried chicken\n");
	else printf("French fries\n");
	printf("Amount = %d ",x.amount);
	if (x.unit == 0)
		printf("piece\n");
	else printf("gram\n");
	printf("Last = %d\n\n\n",last);
}

int main()
{
	item item1, item2;
	item1 = newItem(0,10,0);
	item2 = newItem(1,5,1);

	produce(&item1); int first1 = first;
	produce(&item2); int first2 = first;

	printf("Frist value of item 1: %d\n",first1);	
	item *serve = consume();
	Out(*serve);

	printf("First value of item 2: %d\n",first2); 
	serve = consume();
	Out(*serve);
	return 0;

}

