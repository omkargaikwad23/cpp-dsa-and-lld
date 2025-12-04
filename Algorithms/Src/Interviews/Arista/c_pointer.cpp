#include <bits/stdc++.h>
using namespace std;

int main()
{
    int* ptr ;
    int num = 10;
    ptr = (int*) num;
    cout << (int)ptr << endl;

    ptr++;
    num = (int)ptr;
    cout << num << endl; //14
    
    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

void func( int *p)
{
      p = (int *) malloc(sizeof(int));
}
int main()
{
     int *p = NULL;
     func(p);
     *p = 10;
     cout << *p << endl;
    return 0;
}
*/