#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;

int countSubstring(const char*, const char, const char);

int main()
{
    char start = 'A', end = 'B';
    string string_ = "CABAAXBYA";
    printf("There are %d substrings that start with %c and end with %c in %s\n",
            countSubstring(string_.c_str(), start, end), start, end, string_.c_str());
    return 0;
}

int countSubstring(const char* string_, const char start, const char end)
{
    int count = 0;
    int length = (int)strlen(string_);
    for (int i = 0; i < length; i++) {
        if (string_[i] == start) {
            for(int j = i; j < length; j++) {
                if(string_[j] == end)
                    count++;
            }
        }
    }
    return count;
}
