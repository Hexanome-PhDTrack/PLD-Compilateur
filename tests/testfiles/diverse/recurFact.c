int fact(int a)
{
  if(a == 0)
  {
    return 1;
  }
  else
  {
    return a*fact(a-1);
  }
}

int main()
{
  return fact(5);
}
