#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 10

sem_t semaphore;

void wait(int x)
{
	while (x<=0) return;
	s--;
}

void signal(int x)
{
	x++;
}

typedef struct 
{
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];

int first = 0;
int last = 0;
int first1, first2, first3;
int mutex;


void produce(item *i) 
{
	while ((first + 1) % BUFFER_SIZE == last) 
	{
	// do nothing -- no free buffer item
	}
	wait(mutex);
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
	signal(mutex);
}

item *consume() 
{
	item *i = malloc(sizeof(item));
	while (first == last) 
	{
	// do nothing -- nothing to consume
	}
	wait(mutex);
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
	signal(mutex);
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

void *pthread_Producer(void *param)
{
	item item1, item2, item3;
	item1 = newItem(0,10,0);
	item2 = newItem(1,5,1);
	item3 = newItem(0,15,0);

	produce(&item1); first1 = first;
	produce(&item2); first2 = first;
	produce(&item3); first3 = first;
}

void *pthread_Consumer(void *param)
{
	printf("Frist value of item 1: %d\n",first1);	
	item *serve = consume();
	Out(*serve);

	printf("First value of item 2: %d\n",first2); 
	serve = consume();
	Out(*serve);
}

int main()
{
	pthread_t tid1,tid2;

	pthread_create(&tid1, NULL, pthread_Producer, NULL);
	pthread_join(tid1, NULL);

	pthread_create(&tid2, NULL, pthread_Consumer, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
