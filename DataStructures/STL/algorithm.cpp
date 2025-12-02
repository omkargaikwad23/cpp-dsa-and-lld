#include<iostream>  
#include<algorithm>  
#include <iostream>
#include<array>

int main(){
  array <int, 6> arr = {11,23,33,43,55,63};
  
  if(all_of(arr.begin(), arr.end(), [](int k){return k%2;}))
    cout << "the array elements are odd " << endl;
  return 0; 
}