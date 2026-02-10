#include <stdio.h>

typedef struct Person
{
	char name[20];
	int age;
} Person;

int main()
{
	Person person = {"Max Mustermann", 15};

	unsigned char* ptr = (unsigned char*)&person;

	for (int i = 0; i < sizeof(Person); i++) {
		printf("person + %02i: 0x%02x\n", i,ptr[i]);
	}
}