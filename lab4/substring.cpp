/*
 * Nicholas Jordan
 * CMPS 3120
 * Lab4
 */

#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;

int countSubstring(const char*, const char, const char);
int improvedCountSubstring(const char*, const char, const char);

int main()
{
    char start = 'A', end = 'B';
    string string_ = "CABAAXBYA";
    //normal count substring function
    printf("There are %d substrings that start with %c and end with %c in %s\n",
            countSubstring(string_.c_str(), start, end), start, end, string_.c_str());
    //improved count substring function
    printf("There are %d substrings that start with %c and end with %c in %s\n",
            improvedCountSubstring(string_.c_str(), start, end), start, end, string_.c_str());
    return 0;
}
//quadratic efficiency
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
//linear efficiency
int improvedCountSubstring(const char* string_, const char start, const char end)
{
    int start_count = 0;
    int total_count = 0;
    int length = (int)strlen(string_);
    for (int i = 0; i < length; i++) {
        if (string_[i] == start)
            start_count++;
        else if (string_[i] == end)
            total_count += start_count;
    }

    return total_count;
}
