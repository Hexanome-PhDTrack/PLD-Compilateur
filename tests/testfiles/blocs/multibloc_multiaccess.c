int main()
{
  int a = 8;
  {
    int b = a+1;
    {
      int c = a+b-1;
      a = c;
    }
    {
        c = 5;
    }
  }
  return a;
}