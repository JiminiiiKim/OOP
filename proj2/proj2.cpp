#include "inf_int.h"
#pragma warning(disable:4996)

// constructor
inf_int::inf_int()
{
    this->digits = new char[2];  

    this->digits[0] = '0';        
    this->digits[1] = '\0';
    this->length = 1;
    this->thesign = true;
}

inf_int::inf_int(int n) 
{
    char buf[100];

    if (n < 0) {        
        this->thesign = false;
        n = -n;
    }
    else {
        this->thesign = true;
    }

    int i = 0;
    while (n > 0) {            
        buf[i] = n % 10 + '0';

        n /= 10;
        i++;
    }

    if (i == 0) {    
        new (this) inf_int();   
    }
    else {
        buf[i] = '\0';

        this->digits = new char[i + 1];
        this->length = i;
        strcpy(this->digits, buf);
    }
}

inf_int::inf_int(const char* str)
{
    char buf[100];
    buf[0] = { 0, };
    char reverse[100];
    reverse[0] = { 0, };
    if (strlen(str) == 1 && str[0] == '0') { 
        new (this) inf_int();
    }
    if (str[0] == '-')
    {
        this->thesign = false;
        this->length = strlen(str) - 1;
        for (int i = 0; i < strlen(str) - 1; i++)
            buf[i] = str[i + 1];
    }
    else if (str[0] == '+')
    {
        this->thesign = true;
        this->length = strlen(str) - 1;
        for (int i = 0; i < strlen(str) - 1; i++)
            buf[i] = str[i + 1];
    }
    else if ((str[0] >= '0') && (str[0] <= '9'))
    {
        this->thesign = true;
        this->length = strlen(str);
        for (int i = 0; i < strlen(str); i++)
            buf[i] = str[i];
    }
    buf[this->length] = '\0';
    int j = 0;
    for (int i = this->length - 1; i >= 0; i--)
    {
        reverse[j] = buf[i];
        j++;
    }
    reverse[this->length] = '\0';
    this->digits = new char[this->length + 1];
    strcpy(this->digits, reverse);
}

inf_int::inf_int(const inf_int& a)
{
    this->digits = new char[a.length + 1];

    strcpy(this->digits, a.digits);
    this->length = a.length;
    this->thesign = a.thesign;
}

// destructor
inf_int::~inf_int()
{
    delete digits;       
}

//assignment operators
inf_int& inf_int::operator=(const inf_int& a)
{
    if (this->digits) {
        delete this->digits;        
    }
    this->digits = new char[a.length + 1];

    strcpy(this->digits, a.digits);
    this->length = a.length;
    this->thesign = a.thesign;

    return *this;
}

inf_int& inf_int::operator+=(const inf_int& b)
{
    if ((*(this)->digits == *b.digits) & (this->thesign != b.thesign))
    {
        ;        *this = inf_int(0);
    }
    else
        *(this) = *this + b;
    return *this;
}

inf_int& inf_int::operator-=(const inf_int& b)
{
    if ((*(this)->digits == *b.digits) & (this->thesign != b.thesign))
    {
        *this = inf_int(0);
    }
    else
        *(this) = *this - b;
    return *this;
}
//assingment operators

//arithmetic operators
inf_int operator+(const inf_int& a, const inf_int& b)
{
    inf_int c;
    unsigned int i;

    if (a.thesign == b.thesign) {
        for (i = 0; i < a.length; i++) {
            c.Add(a.digits[i], i + 1);
        }
        for (i = 0; i < b.length; i++) {
            c.Add(b.digits[i], i + 1);
        }

        c.thesign = a.thesign;

        return c;
    }
    // calculate by subtraction
    else {
        c = b;
        c.thesign = a.thesign;

        return a - c;
    }
}


inf_int operator-(const inf_int& a, const inf_int& b) 
{
    inf_int c;
    unsigned int i;

    inf_int a_absolute = a;
    inf_int b_absolute = b;

    if (a.thesign == false)
        a_absolute.thesign = true;
    if (b.thesign == false)
        b_absolute.thesign = true;

    if (a.thesign == b.thesign) {

        if ((strcmp(a.digits, b.digits) == 0)) {
            c = 0;
            return c;
        }

        if (a_absolute > b_absolute) {
            for (i = 0; i < a.length; i++) {
                c.Add(a.digits[i], i + 1);
            }
            for (i = 0; i < b.length; i++) {
                c.Subtract(b.digits[i], i + 1);
            }
        }

        else if (a_absolute < b_absolute) {
            for (i = 0; i < b.length; i++) {
                c.Add(b.digits[i], i + 1);
            }

            for (i = 0; i < a.length; i++) {
                c.Subtract(a.digits[i], i + 1);
            }

        }

        if (a > b)
            c.thesign = true;
        else if (a < b)
            c.thesign = false;

        int j = strlen(c.digits) - 1;
        if (c.digits[strlen(c.digits) - 1] == '0') {
            while (c.digits[j] == '0') {
                c.digits[j] = '\0';
                j--;
                c.length--;
            }
        }

        return c;
    }
    // calculate by addition
    else {
        c = b;
        c.thesign = a.thesign;

        return a + c;
    }
}

inf_int operator*(const inf_int& a, const inf_int& b)
{
    if (a == 0 || b == 0)
        return inf_int(0);
    int len = a.length + b.length;
    char* result = new char[len + 1];

    for (int i = 0; i < len; i++) {
        result[i] = '0';
    }
    result[len] = '\0';

    int carry1 = 0, carry2 = 0;
    int current;
    int num;

    // calculate one digit of each number
    for (int i = 0; i < b.length; i++) {
        for (int j = 0; j < a.length; j++) {
            current = (b.digits[i] - '0') * (a.digits[j] - '0');
            num = result[i + j] - '0';
            if (num + carry2 + current % 10 > 9)
                carry1 = 1;
            result[i + j] = (num + carry2 + current % 10) % 10 + '0';
            carry2 = 0;

            num = result[i + j + 1] - '0';
            if (num + carry1 + current / 10 > 9)
                carry2 = 1;
            result[i + j + 1] = (num + carry1 + current / 10) % 10 + '0';
            carry1 = 0;
        }
    }

    while (result[len - 1] == '0') {
        result[len - 1] = '\0';
        len -= 1;
    }

    inf_int c;
    c.length = strlen(result);
    c.digits = (char*)realloc(c.digits, c.length + 1);

    if (c.digits == NULL) {
        cout << "Memory reallocation failed, the program will terminate." << endl;

        exit(0);
    }
    strcpy(c.digits, result);

    delete[] result;

    if (a.thesign == b.thesign)
        c.thesign = true;
    else
        c.thesign = false;

    return c;
}

inf_int operator/(const inf_int& a, const inf_int& b)
{
    if (a == 0 || b == 0)
        return inf_int(0);

    inf_int c;

    inf_int a_copy = a;
    inf_int b_copy = b;
    a_copy.thesign = true;
    b_copy.thesign = true;

    if (a_copy < b_copy)
        return inf_int();

    string result;
    int idx = a.length - 1;

    inf_int temp = a.digits[idx] - '0';

    inf_int multNum = 0;
    inf_int leftover = 0;

    while (temp < b_copy) {
        temp = temp * 10 + a.digits[--idx] - '0';
    }

    while (idx > 0) {
        multNum = 0;
        leftover = temp;
        while (leftover > b_copy || leftover == b_copy) {
            leftover = leftover - b_copy;
            multNum = multNum + 1;
        }
        leftover = temp - (multNum * b_copy);
        result = result + multNum.digits;

        temp = leftover * 10 + (a.digits[--idx] - '0');
    }

    multNum = 0;
    leftover = temp;
    while (leftover > b_copy || leftover == b_copy) {
        leftover = leftover - b_copy;
        multNum = multNum + 1;
    }
    leftover = temp - (multNum * b_copy);
    result = result + multNum.digits;

    char* ans = const_cast<char*>(result.c_str());
    c = inf_int(ans);

    if (a.thesign != b.thesign)
        c.thesign = false;
    else
        c.thesign = true;
    return c;
}

inf_int operator%(const inf_int& a, const inf_int& b) 
{

    if (a == 0 || b == 0)
        return inf_int(0);

    inf_int a_copy = a;
    inf_int b_copy = b;
    a_copy.thesign = true;
    b_copy.thesign = true;

    if (a_copy < b_copy)
        return b;

    string result; 
    int idx = a.length - 1;
    inf_int leftover; 

    inf_int multNum = 0;
    inf_int temp = a.digits[idx] - '0';

    while (temp < b_copy)
        temp = temp * 10 + (a.digits[--idx] - '0');

    while (idx > 0) {
        multNum = 0;
        leftover = temp;

        while (leftover > b_copy || leftover == b_copy) {
            leftover = leftover - b_copy;
            multNum = multNum + 1;
        }

        leftover = temp - (multNum * b_copy);

        temp = leftover * 10 + (a.digits[--idx] - '0');
    }

    multNum = 0;
    leftover = temp;

    while (leftover > b_copy || leftover == b_copy) {
        leftover = leftover - b_copy;
        multNum = multNum + 1;
    }

    leftover = temp - (multNum * b_copy);

    leftover.thesign = a.thesign;

    return leftover;
}
//arithmetic operators

//inc/dec operators
inf_int operator++(inf_int& num)
{
    num = num + 1;
    return num;
}

inf_int operator--(inf_int& num)
{
    num = num - 1;
    return num;
}


const inf_int inf_int::operator++(int)
{
    inf_int c(*this);
    *this = *this + 1;
    return c;
}

const inf_int inf_int::operator--(int)
{
    const inf_int c(*this);
    *this = *this - 1;
    return c;
}
//inc/dec operators

//comparison operators
bool operator>(const inf_int& a, const inf_int& b)
{
    bool result;

    if (a.length > b.length)
        result = true;
    else if (a.length < b.length)
        result = false;
    // the same length of number
    else {
        char* a_copy = new char[a.length + 1];
        char* b_copy = new char[b.length + 1];

        for (int i = a.length - 1; i >= 0; i--) {
            a_copy[a.length - 1 - i] = a.digits[i];
        }
        a_copy[a.length] = '\0';
        for (int i = b.length - 1; i >= 0; i--) {
            b_copy[b.length - 1 - i] = b.digits[i];
        }
        b_copy[b.length] = '\0';
        if (strcmp(a_copy, b_copy) > 0)
            result = true;
        else
            result = false;
        delete[] a_copy;
        delete[] b_copy;
    }

    if (a.thesign == true && b.thesign == true) {
        return result;
    }
    else if (a.thesign == false && b.thesign == false) {
        return !result;
    }
    else {
        return a.thesign;
    }
}

bool operator<(const inf_int& a, const inf_int& b)
{
    if (operator>(a, b) || operator==(a, b)) {
        return false;
    }
    else {
        return true;
    }
}

bool operator==(const inf_int& a, const inf_int& b)
{
    if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)    
        return true;
    return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
    return !operator==(a, b);
}
//comparison operators

//I/O operators
ostream& operator<<(ostream& out, const inf_int& a)
{
    if (a.thesign == false) {
        out << '-';
    }
    for (int i = a.length - 1; i >= 0; i--) {
        out << a.digits[i];
    }
    return out;
}

istream& operator>>(istream& in, inf_int& a)
{
    string str;
    cout << "Enter Number:";
    in >> str;
    a = inf_int(str.c_str());

    return in;
}
//I/O operators

//Functions
void inf_int::Add(const char num, const unsigned int index)   
{
    if (this->length < index) {
        this->digits = (char*)realloc(this->digits, index + 1);

        if (this->digits == NULL) {        
            cout << "Memory reallocation failed, the program will terminate." << endl;

            exit(0);
        }

        this->length = index;                
        this->digits[this->length] = '\0';    
    }

    if (this->digits[index - 1] < '0') {    
        this->digits[index - 1] = '0';
    }

    this->digits[index - 1] += num - '0';    

    // carry
    if (this->digits[index - 1] > '9') {    
        this->digits[index - 1] -= 10;    
        Add('1', index + 1);            
    }
}

void inf_int::Subtract(const char num, const unsigned int index) 
{
    if (this->length < index)
    {
        this->digits = (char*)realloc(this->digits, index + 1);

        if (this->digits == NULL) {		
            cout << "Memory reallocation failed, the program will terminate." << endl;

            exit(0);
        }

        this->length = index;					
        this->digits[this->length] = '\0';	
    }

    if (this->digits[index - 1] < '0') {	
        this->digits[index - 1] = '0';
    }

    this->digits[index - 1] -= num - '0'; 	

    // regrouping	
    if (this->digits[index - 1] < '0') { 
        this->digits[index - 1] += 10;	
        Subtract('1', index + 1);		
    }
}

