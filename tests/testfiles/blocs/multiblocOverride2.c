int main()
{
  int a = 8;
  {
    int a = 41;
    {
      a = a+1;
    }
  }
  return a;
}
