#include <stdio.h>

#define N_MAX 10
#define NAME_MAX 15

#define IO_ERROR 10;

struct good
{
	char name[NAME_MAX];
	int price;
	int amount;
};

int bin_print(FILE *b, struct good g)
{
	/*
	fwrite(g.name, sizeof(char), NAME_MAX, b);
	fwrite(&g.price, sizeof(unsigned int), 1, b);
	fwrite(&g.amount, sizeof(unsigned int), 1, b);
	*/
	fwrite(&g, sizeof(struct good), 1, b);
	return 0;
}

int find_min_goods(FILE *f, FILE *b)
{
	struct good g;
	int min = -1;
	int r;
	//char n[10];
	//printf("a\n");
	/*
	fscanf(f, "%s", n);
	printf("%s\n", n);
	*/
	while (!feof(f))
	{
		if (r = fscanf(f, "%s %d %d", g.name, &g.price, &g.amount), r != 3)
		{
			//printf("a2 %d\n", r);
			return 1;
		}
		// printf("%s %d %d \n", g.name, g.price, g.amount);
		if (min >= g.price*g.amount || min == -1)
			min = g.price*g.amount;
	}
	rewind(f);
	while (!feof(f))
	{
		if (r = fscanf(f, "%s %d %d", g.name, &g.price, &g.amount), r != 3)
		{
			//printf("a2 %d\n", r);
			return 1;
		}
		if (min == g.price*g.amount)
			bin_print(b, g);
	}
	if (min == -1)
		return 3;
	//printf("%d\n", min);
	return 0;
}

int file_size(FILE *f, size_t *size)
{
	long sz;
	
	if (fseek(f, 0L, SEEK_END))
		return 1;
	
	sz = ftell(f);
	
	if (sz < 0)
		return 1;
	
	*size = sz;
	
	return fseek(f, 0L, SEEK_SET);
}

int bin_to_file(FILE *f, FILE *b)
{
	size_t size;
	struct good g;
	int r;
	
	r = file_size(b, &size);
	// printf("%d %zu \n", r, size);
	// if (r == 0 && size % sizeof(struct good) == 0)
	if (r == 0)
	{
		for (size_t i = 0; i < size / sizeof(struct good); i++)
		{
			fread(&g, sizeof(struct good), 1, b);
			printf("%s %d %d\n", g.name, g.price, g.amount);
			fprintf(f, "%s %d %d\n", g.name, g.price, g.amount);
		}
	}
	else
	{
		printf("SIZE ERR");
		return 1;	
	}
	return 0;
}

int main(void)
{
	FILE *f, *b;
	int r;
	f = fopen("first.txt", "r");
	if (f == NULL)
		return IO_ERROR;
	b = fopen("second.bin", "wb");
	r = find_min_goods(f, b);
	fclose(f);
	fclose(b);
	if (r != 0)
		return r;
	
	f = fopen("result.txt", "w");
	b = fopen("second.bin", "rb");
	r = bin_to_file(f, b);
	fclose(f);
	fclose(b);
	if (r != 0)
		return r;
	
	return 0;
}