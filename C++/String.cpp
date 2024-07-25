#include <iostream>
#include <cstring>

class String
{
private:
    char *str;

public:
    String();
    String(const char *str);
    ~String();

    String operator== (const String &other); 
    friend std::ostream& operator<<(std::ostream& os, String& r);
    void Print();
};

std::ostream& operator<< (std::ostream& os, String& r)
{
    os << r.str;
    return os;
}

String String::operator== (const String &other)
{

}

String::String():str{nullptr}{}

String::String(const char *str)
{
    int stringLength = strlen(str);
    this->str = new char[stringLength + 1];

    for (int i = 0; i < stringLength; ++i)
    {
        this->str[i] = str[i];
    }
}

String::~String()
{
    delete [] this->str;
}

void String::Print()
{
    std::cout<<str;
}

int main()
{
    String str;
    str = "Nigger slave";
    //str.Print();
    std::cout << str;
    return 0;
}



