
int main()
{
	int i, sum = 0;
	for (i=1; i<=100; ++i)
	{
		sum += i;
	}
	if (sum != 5050)
	{
		return 1;
	}
	return 0;
}
