#ifndef _INF_INT_H_
#define _INF_INT_H_

#include <iostream>
using namespace std;

class inf_int
{
private:
    char* digits;  
    unsigned int length;
    bool thesign;  
    
    void Add(const char num, const unsigned int index);//function used for + operator
    void Subtract(const char num, const unsigned int index);//function used for - operator

public:
    inf_int(); // assign 0 as a default value
    inf_int(int); //when input is int value
    inf_int(const char*); //when input is char value 
    inf_int(const inf_int&); // copy constructor
    ~inf_int(); // destructor

    //assignment operators
    inf_int& operator=(const inf_int&); // assignment operator
    inf_int& operator+=(const inf_int&); //+= assignment operator
    inf_int& operator-=(const inf_int&); //-= assignment operator

    //arithmetic operators
    friend inf_int operator+(const inf_int&, const inf_int&); 
    friend inf_int operator-(const inf_int&, const inf_int&);
    friend inf_int operator*(const inf_int&, const inf_int&);
    friend inf_int operator/(const inf_int&, const inf_int&);
    friend inf_int operator%(const inf_int&, const inf_int&);


    //inc/dec operators
    friend inf_int operator++(inf_int&);//prefix inc operator
    friend inf_int operator--(inf_int&);//prefix dec operator
    const inf_int operator++(int);//postfix inc operator
    const inf_int operator--(int);//postfix dec operator

    //comparison operators
    friend bool operator>(const inf_int&, const inf_int&);
    friend bool operator<(const inf_int&, const inf_int&);
    friend bool operator==(const inf_int&, const inf_int&);
    friend bool operator!=(const inf_int&, const inf_int&);

    //I/O operators
    friend ostream& operator<<(ostream&, const inf_int&);//output operator
    friend istream& operator>>(istream&, inf_int&);//input operator
};

#endif