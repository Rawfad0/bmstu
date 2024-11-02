#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int r;
	int x;
	int max_odd = 0;
	int count_pos = 0;
	while (r = scanf("%d", &x), r==1 && x != 0)
	{
		if (x > 0)
			count_pos++;
		if (abs(x % 2) == 1 && (x > max_odd || max_odd == 0))
			max_odd = x;
	}
	if (r != 1)
		return 1;
	if (max_odd == 0)
		return 2;
	printf("%d %d", max_odd, count_pos);
	return 0;
}
