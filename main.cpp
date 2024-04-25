#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    execlp("xdg-open", "xdg-open", "https://tinyurl.com/heyyprabhu", NULL);
    return 0;
}