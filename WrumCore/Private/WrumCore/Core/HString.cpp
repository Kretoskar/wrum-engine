#include "PCH.h"

#include "WrumCore/Core/HString.h"

namespace Wrum
{
    char HString::hashTable[hashTableSize][hashTableMaxStringLength] = { {'\0'} };
    HString HString::None = HString();
}