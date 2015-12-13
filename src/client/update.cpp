#include "update.h"

Update::Update(uint8_t buffer[16])
{
    if (buffer[0] != INFRAVERSE_MAGIC_NUMBER)
    {
        // FIXME - Don't fail silently!
        return;
    }

    updateId = buffer[2];
    for (int i = 0; i < buffer[1]; ++i)
    {
        args.push_back(buffer[i]);
    }
        
}
