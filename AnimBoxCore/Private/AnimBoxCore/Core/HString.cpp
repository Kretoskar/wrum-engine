#include "PCH.h"

#include "AnimBoxCore/Core/HString.h"

namespace AnimBox
{
    char HString::hashTable[hashTableSize][hashTableMaxStringLength] = { {'\0'} };
    HString HString::None = HString();
}