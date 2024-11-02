#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_MAX 10

void swap(int arr[], size_t n, size_t i1, size_t i2)
{
	int temp;
	temp = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = temp;
}

void selection_sort(int arr[], size_t n)
{
	size_t max_i;
	// sort
	for (size_t i = 0; i < n; i++)
	{
		max_i = i;
		for (size_t j = i; j < n; j++)
		{
			if (arr[j] > arr[max_i])
				max_i = j;
		}
		swap(arr, n, i, max_i);
	}
}

void left_shift(int arr[], size_t start, size_t end)
{
	for (size_t i = start; i < end - 1; i++)
	{
		swap(arr, end, i, i + 1);
	}
}

void right_shift(int arr[], size_t start, size_t end)
{
	for (size_t i = end - 1; i > start; i--)
	{
		swap(arr, end, i, i - 1);
	}
}

int main(void)
{
	int arr[N_MAX] = { 0 };
	size_t n = 0;
	int r;
	long int x;		//  N_MAX=10 => 0<= x < 10'000'000'000
	int res = 0;
	
	if (r = scanf("%ld", &x), r != 1)
		return 1;
	if (x < 0)
		return 2;
	
	// int to array
	while (x != 0)
	{
		arr[n] = x % 10;
		x = x / 10;
		n++;
	}
	
	// only one element
	if (n == 1)
	{
		printf("%d", arr[0]);
		return 0;
	}
	
	selection_sort(arr, n);
	
	// min & max to mid
	if (n % 2 == 0)
	{
		left_shift(arr, 0, n / 2);
		right_shift(arr, n / 2, n);
		swap(arr, n, n / 2 - 1, n / 2);
	}
	if (n % 2 == 1)
	{
		left_shift(arr, 0, n / 2);
		right_shift(arr, n / 2 + 1, n);
		swap(arr, n, n / 2 - 1, n / 2 + 1);
	}
	
	// arr to int
	for (size_t i = 0; i < n; i++)
		res += arr[i] * (pow(10, i));
	printf("%d", res);
	
	return 0;
}
