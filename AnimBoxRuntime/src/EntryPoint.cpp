#include "PCH.h"

struct Test
{
    Test(int a, int b) : a(a), b(b) {}
    
    uint8_t a;
    uint8_t b;
};

struct TestA
{
    TestA(int a, int b) : a(a), b(b) {}
    
    uint64_t a;
    uint64_t b;
};

using namespace AnimBox;

int main(int argc, char* argv[])
{
    {
        ArenaAllocator Arena(1024 * 1024);
        Test* t = ArenaAllocator::New<Test>(&Arena, 123, 321);
        printf("%d\n", t->a);

        TestA* tA = ArenaAllocator::New<TestA>(&Arena, 456, 654);
        printf("%llu\n", tA->b);
    }
}