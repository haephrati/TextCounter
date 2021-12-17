#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void Fail(const char* msg)
{
    std::printf("FAIL %s\n", msg);
    std::exit(1);
}

int main()
{
    if (FIRST_CHAR != L'a')
    {
        Fail("FIRST_CHAR");
    }
    if (INF != 0x7ffffff)
    {
        Fail("INF");
    }
    Node n;
    if (n.delta != INF)
    {
        Fail("Node delta");
    }
    for (int i = 0; i < 40; ++i)
    {
        if (n.c[i] != 0)
        {
            Fail("Node c");
        }
    }
    if (wcscmp(DATEFORMAT, L"%Y%m%d%H%M%S") != 0)
    {
        Fail("DATEFORMAT");
    }
    Sentence s;
    if (s.score != INT_MIN)
    {
        Fail("Sentence score");
    }
    std::printf("OK TextCounterTests\n");
    return 0;
}
