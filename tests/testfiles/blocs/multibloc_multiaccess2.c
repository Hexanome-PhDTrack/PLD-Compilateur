int main()
{
  int a = 8;
  int c;
  {
    int b = a+1;
    {
        b = b + 1;
      int c = a+b-1;
      a = c;
    }
    {
        int b = 8;
        b = 5;
    }
    c = b;
  }

  return a + c;
}