#include <iostream>
#include "vector.h"
#include <cassert>
using namespace std;

int main()
{
    int i;

    Vector<int,4> v1(4);
    for(i=0;i<4;i++)
        assert(4==v1[i]);//verificare pr constuctor
    //cout<<endl;
    assert(4==v1.get_dim());//verificare pentru dimensiune
    cout<<v1;
    Vector<int,4>v2(6);
    cout<<v2;
    v1=v2;
    cout<<v1;
    int rez=v1*v2;
    cout<<"produsul scalar: "<<rez<<endl;
    Vector<int,4> v3=v1+v2;
    assert(v3[0]==v1[0]+v2[0]); //verificare pt adunare
    cout<<v3;
    v3=v1-v2; cout<<v3;//verificare pt scadere
    assert(v3[0]==v1[0]-v2[0]);
    int scalar=10;
    v3=scalar*v1;
    cout<<v3;
    assert(v3[0]==v1[0]*scalar);//verificare pt inmuktirea cu scalar
    return 0;
}
