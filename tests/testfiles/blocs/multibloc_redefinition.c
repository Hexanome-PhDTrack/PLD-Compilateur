int main()
{
  int a = 8;
  int c;
  int e = 2;
  {
        c = 5;
        if(a == 8){
            int b = 56;
            int c = 5;
            a = a - b + c;
        }
  }
  while(a < c){
      int e = 3;
      int b = 2*c;
      if(c < b){
          a = a + c;
          c = c + 1;
      }else{
          a = a + c - e - 1;
      }
      int e = 4;
      a = a + e;
    
  }

  return a + c;
}