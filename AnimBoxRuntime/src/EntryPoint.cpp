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
        char* ch = ArenaAllocator::New<char>(&Arena, 'f');
        std::cout << *ch << '\n';
        
        Test* t = ArenaAllocator::New<Test>(&Arena, 123, 321);
        printf("%d\n", t->a);

        char* ch2 = ArenaAllocator::New<char>(&Arena, 'q');
        std::cout << *ch2 << '\n';

        TestA* tA = ArenaAllocator::New<TestA>(&Arena, 456, 654);
        printf("%llu\n", tA->b);
    }
}