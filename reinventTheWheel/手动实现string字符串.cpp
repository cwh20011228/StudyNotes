#include <iostream>
using namespace std;

namespace MyString
{

    class String
    {
    public:
        String();
        String(const char *str, size_t size);
        String(const String &str);
        String(String &&str) noexcept;
        ~String();
        String &operator=(const char *str);
        String &operator=(const String &str);
        String &operator=(String &&str);
        bool operator==(const String &str);
        bool startswith(const char *str); // 是否以str开头
        bool endswith(const char *str);   // 是否以str结尾
        size_t length() const;
        bool empty() const;
        void printStr() const;
    private:
        char *mData = nullptr;
        size_t mLength; // mLength的长度不包含'\0'空字符
    };

    String::String()
    {
        mLength = 0;
        mData = new char[1];
        *mData = '\0';
        cout<<"String()"<<endl;
    }

    // c风格字符串的长度包含末尾的'\0'字符，string字符串不包含
    String::String(const char *str, size_t size)
    {
        mLength = size - 1;
        mData = new char[mLength];
        memcpy(mData, str, size);
        cout<<"String(const char *,size_t)"<<endl;
    }

    String::String(const String &str)
    {
        if (mData != nullptr)
        {
            delete[] mData;
        }
        mLength = str.mLength;
        mData = new char[mLength];
        memcpy(mData, str.mData, str.mLength + 1);
        cout<<"String(const String &)"<<endl;
    }

    String::String(String &&str) noexcept
    {
        if (mData != nullptr)
        {
            delete[] mData;
        }
        mData = str.mData;
        mLength = str.mLength;
        str.mData = nullptr;
        cout<<"String(const String &&)"<<endl;
    }

    String &String::operator=(const char *str)
    {
        cout<<"String::operator=(const char *)"<<endl;
        if (mData != nullptr)
        {
            delete[] mData;
        }

        int len = 1;
        auto s = str;
        while (*s != '\0')
        {
            len++;
            s++;
        }

        mData = new char[len];
        mLength = len - 1;
        memcpy(mData, str, len);

        return *this;
    }

    String &String::operator=(const String &str)
    {
        cout<<"String::operator=(const String &)"<<endl;
        // 避免自我赋值
        if (this == &str)
        {
            return *this;
        }

        if (mData != nullptr)
        {
            delete[] mData;
        }

        mLength = str.mLength;
        mData = new char[mLength + 1];

        memcpy(mData, str.mData, mLength + 1);

        return *this;
    }

    String &String::operator=(String &&str)
    {
        cout<<"String::operator=(const String &&)"<<endl;
        if (this == &str)
        {
            return *this;
        }

        if (mData != nullptr)
        {
            delete[] mData;
        }

        mLength = str.mLength;
        mData = str.mData;
        str.mData = nullptr;    // 避免资源重复释放

        return *this;
    }

    String::~String()
    {
        if (mData != nullptr)
        {
            delete[] mData;
            mData = nullptr;
        }
        mLength = 0;
    }

    bool String::operator==(const String &str)
    {
        if (mLength != str.mLength)
        {
            return false;
        }

        for (int i = 0; i <= str.mLength; i++)
        {
            if (mData[i] != str.mData[i])
            {
                return false;
            }
        }
        return true;
    }

    // 是否以str开头
    bool String::startswith(const char *str)
    {
        char *data = mData;
        while (*str != '\0')
        {
            if (*data != *str)
            {
                return false;
            }
            str++;
            data++;
        }
        return true;
    }

    // 是否以str结尾
    bool String::endswith(const char *str)
    {
        int len = 0;
        const char* s = str;
        while (*s != '\0')
        {
            len++;
            s++;
        }

        for (int i = mLength - len; i < mLength; i++)
        {
            if (mData[i] != *str)
            {
                return false;
            }
            str++;
        }
        return true;
    }

    size_t String::length() const
    {
        return mLength;
    }

    bool String::empty() const
    {
        return mLength == 0;
    }

    void String::printStr() const{
        for(int i = 0;i <= mLength;i++){
            cout<<mData[i];
        }
        cout<<endl;
    }

    size_t strlen(char* str){
        char* s = str;
        size_t len = 0;
        while(*s != '\0'){
            len++;
            s++;
        }
        return len+1;
    }
};

int main(int argc, char *argv[])
{
    MyString::String s1;
    cout << "length = " << s1.length() << endl;

    char str1[] = "1234567";
    size_t len1 = MyString::strlen(str1);
    cout<<"str1.len = "<<len1 <<endl;

    MyString::String s2(str1,len1);
    cout << "s2.length = " << s2.length()<<"    s2 = ";
    s2.printStr();

    MyString::String s3(s2);
    cout << "s3.length = " << s3.length()<<"    s3 = ";
    s3.printStr();

    MyString::String s4(std::move(s2));
    cout << "s4.length = " << s4.length()<<"    s4 = ";
    s4.printStr();

    MyString::String s5;
    s5 = s4;
    cout << "s5.length = " << s5.length()<<"    s5 = ";
    s5.printStr();

    MyString::String s6;
    s6 = str1;
    cout << "s6.length = " << s6.length()<<"    s6 = ";
    s6.printStr();

    MyString::String s7;
    s7 = std::move(s6);
    cout << "s7.length = " << s7.length()<<"    s7 = ";
    s7.printStr();

    cout << "s7 == s4 ? " << (s7 == s4) << endl;

    char str2[] = "123";
    cout << "s7 startswith str2? " << s7.startswith(str2) << endl;

    char str3[] = "567";
    cout << "s7 endswith str3? " << s7.endswith(str3) << endl;

    cout << "s7 empty? " << s7.empty() << endl;
    cout<<"s7 empty? "<<s7.empty()<<endl;   

    return 0;
}
