#include <Windows.h>
#include <stdio.h>

static int isSurrogate(unsigned c)
{
    return (0xd800 & c) == 0xd800;
}

int main(int argc, char ** argv)
{
    wchar_t wide[10];
    wchar_t wide2[10];
    char utf8[100];

    wide[1] = L'\0';
    for(int i = 0; i <= 0xffff; ++i)
    {
        wide[0] = (wchar_t)i;
        if(WideCharToMultiByte(CP_UTF8, 0, wide, -1, utf8, 100, NULL, NULL))
        {
            if(MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wide2, 10))
            {
                if(0 != wcscmp(wide, wide2))
                {
                    printf("U+%X turned into U+%X surrogate = %d\n", wide[0], wide2[0], isSurrogate(wide[0]));
                }
            }
            else
            {
                printf("error on second conversion\n");
            }
        }
        else
        {
            printf("error on first conversion\n");
        }
    }

    return 0;
}
