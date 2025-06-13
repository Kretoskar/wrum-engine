#include "PCH.h"

int main(int argc, char* argv[])
{
    AnimBox::HString h = "qwe";
    AnimBox::HString q = "qwe";
    AnimBox::HString c = "dd";
    
    if (h == q)
    {
        LOG_ERROR("Hello World!")
    }
    
    if (c == q)
    {
        LOG_WARNING("jojo")
    }

    AnimBox::AllocationMetrics::GetHeapAllocationMetrics().LogAllocationMetrics();
	
    std::string s = "asd";
    AnimBox::AllocationMetrics::GetHeapAllocationMetrics().LogAllocationMetrics();

    {
        std::unique_ptr<char> c = std::make_unique<char>();
        AnimBox::AllocationMetrics::GetHeapAllocationMetrics().LogAllocationMetrics();
    }

    AnimBox::AllocationMetrics::GetHeapAllocationMetrics().LogAllocationMetrics();
}