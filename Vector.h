#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <iostream>
#include <climits>
#include "Vector.h"
#include <stdexcept>
using namespace std;
template <class T, unsigned n>
class Vector
{
    T* vectorr;
public:
    ~Vector();//destructor
    Vector()
    {
        vectorr= new T[n];//constructor fara parametri
    }
    const T operator[](unsigned int);//overload pe []
    Vector(const T =0);//constructor cu paramtri
    Vector(const Vector&);//constructor de copiere
    const Vector operator=(Vector);//overload pe operatorul de atribuire
    const unsigned int get_dim(){return n;}//metoda de obtinere a dimensiunii vectorului
    Vector operator+(Vector );//overload pe + pt adunarea pe comp
    Vector operator-(Vector );//overload pe - pt scaderea pe comp
    //Vector operator*(const Vector &);
    T operator*(Vector &);//overload pe * pt produsul scalar
    template <class U, unsigned m>
    friend Vector<U,m> operator*(int,Vector<U,m> &);//overload pe *pt produsul cu scalar
    template <class U, unsigned m>
    friend ostream &operator<<(ostream &,const Vector<U,m> &);//overload pt operatorul de afisare
};
template<class T,unsigned n>
Vector<T,n>::~Vector()//destuctor
{
    delete[]vectorr;
}
//constuctor cu parametru
template<class T,unsigned n>
Vector<T,n>::Vector(const T x)
{
    vectorr= new T[n];
    for(unsigned int i=0; i<n; i++)
        vectorr[i]=x;
}
//overload pe [] pt accesarea elem de pe poz i
template<class T, unsigned n>
const T Vector<T,n>::operator[](unsigned int i)
{
    if(i>=n&&i<0)
    {
        throw out_of_range("Index invalid");//daca i iese din intervalul [0,n) nu e bun deci throw
    }
    return this->vectorr[i];
}
//constuctor de copiere
template<class T,unsigned n>
Vector<T,n>::Vector(const Vector &v)
{
    this->vectorr= new T[n];
    for(unsigned int i=0; i<n; i++)
        this->vectorr[i]=v.vectorr[i];
}
//overload pe operatorul de atribuire
template< class T, unsigned n>
const Vector<T,n> Vector<T,n>::operator=(Vector<T,n> v)
{
    if(v.get_dim()!=n)//daca dim vectorilor nu coincid imposibil
    {
        std::invalid_argument e("Dimensiunile nu coincid");
        throw e;
    }
    delete[] this->vectorr;
    this->vectorr=new T[n];
    for(unsigned int i=0; i<n; i++)
        this->vectorr[i]=v.vectorr[i];
    return *this;
}
//overload pe + pt adunarea pe comp
template< class T, unsigned n>
Vector<T,n> Vector<T,n>::operator+(Vector<T,n> v)
{
    if(v.get_dim()!=n)//daca dim vectorului nu sunt egale nu se poate face adunarea pe componente
    {
        std::invalid_argument e("Dimensiuni incorecte");
        throw e;
    }
    T *w=new T[n];
    for(unsigned int i=0; i<n; i++)
    {
        T val;
        val=this->vectorr[i]+v.vectorr[i];
        w[i]=val;
    }
    for(unsigned int i=0; i<n; i++)
        v.vectorr[i]=w[i];
    return v;

}
//overload pe - pt scaderea pe comp
template< class T, unsigned n>
Vector<T,n> Vector<T,n>::operator-(Vector<T,n> v)
{
    if(v.get_dim()!=n)
    {
        std::invalid_argument e("Dimensiuni incorecte");
        throw e;
    }
    T *w=new T[n];
    for(unsigned int i=0; i<n; i++)
    {
        T val;
        val=this->vectorr[i]-v.vectorr[i];
        w[i]=val;
    }
    for(unsigned int i=0; i<n; i++)
        v.vectorr[i]=w[i];
    return v;
}
//overload pe * pt adunarea produsul scalar
template< class T, unsigned n>
T Vector<T,n>::operator*(Vector &v)
{
    long int produs_scalar=0;
    unsigned int dim=v.get_dim();
    if(dim!=n)
    {
        std::invalid_argument e("Dimensiuni incorecte");
        throw e;
    }
    for(unsigned int i=0; i<n; i++)
    {
        produs_scalar=(this->vectorr[i])*v.vectorr[i]+produs_scalar;
    }
    return produs_scalar;

}
//overload pe * pt inmultirea cu un scalar
template<class T, unsigned n>
Vector<T,n> operator*(int scalar,Vector<T,n> &v)
{
    //Vector <T,n> w();
    T *w=new T[v.get_dim()];
    for(unsigned int i=0; i<n; i++)
    {
        try{
            w[i]=scalar*v.vectorr[i];
        }catch(std::overflow_error &e){
            cout<<"Produsul a trecut de tipul de date;";//daca inmultirea trece de capacitatea tipului de date
        }
    }
    Vector<T,n> R(0);
    for(unsigned int i=0; i<n; i++)
    {
        R.vectorr[i]=w[i];
    }
    return R;
}
//overload pe<< pt afisare
template<class T, unsigned  n>
std::ostream & operator<<(std::ostream &out,const Vector<T,n> &V)
{
    out<<n;
    out<<endl;
    for(unsigned int i=0;i<n;i++)
        out<<V.vectorr[i]<<" ";
    out<<endl;
    return out;
}
#endif // VECTOR_H_INCLUDED
