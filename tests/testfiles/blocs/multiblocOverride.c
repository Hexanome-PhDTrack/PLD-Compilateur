int main()
{
  int a = 8;
  {
    int a = 41;
    {
      return a;
    }
  }
}
