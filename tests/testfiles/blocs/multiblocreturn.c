int main()
{
  int a = 8;
  {
    {
      int c = a-1;
      return 4;
    }
  }
  return a;
}
