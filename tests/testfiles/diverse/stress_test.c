int Mod(int a, int b) {
	return a - (a/b)*b;
}

int No_Occurrences(int x, int d) { 
    int count = 0;  
    while (x > 0) 
    { 
        if (Mod(x,10) == d) 
           count = count + 1; 
           
        x = x/10; 
    } 
    return count; 
} 
  

int Max_Occure(int x) { 
  
   int result = 0; 
   int max_count = 1; 
  
   int d = 0;
	 
	 
   if (x < 0) 
      x = -x; 
      
   while(d <= 3) {
      int count = No_Occurrences(x, d); 
  

      if (count >= max_count) 
      { 
         max_count = count; 
         result = d; 
      } 
      
      d = d+1;
   }
   
   return result; 
} 
  
int main() 
{ 
    int x = 1223; 
    return Max_Occure(x);
} 
