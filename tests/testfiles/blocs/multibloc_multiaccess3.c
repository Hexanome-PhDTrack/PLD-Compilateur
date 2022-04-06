int main()
{
  int a = 8;
  int c;
  {
    int b = a+1;
    {
        {
            int d = 3;
        }
        b = b + 1;
      int c = a+b-1;
      a = c;
    }
    {
        {
            int d = 56;
        }
        int b = 8;
        b = 5;
    }
    c = b;
  }
  {
      int b;
      {
          b = 1;
          int c = b + a;
      }
      {
          a = a + b - c;
          {
              int d = 65;
              {
                  int a = 45;
                  b = a + d + b;
              }
          }
      }
      a = b - a;
  }

  return a + c;
}