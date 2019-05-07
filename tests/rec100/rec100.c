int get_sum(int n)
{
  if (n == 0)
  {
    return 0;
  }
  return n + get_sum(n - 1);
}

int main()
{
  int sum;
  sum = get_sum(100);
  if (sum != 5050)
  {
    return 0x7f;
  }
  return 0x3f;
}
