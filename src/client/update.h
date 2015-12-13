#ifndef __UPDATE_H
#define __UPDATE_H

#include <vector>

#define INFRAVERSE_MAGIC_NUMBER 0x42
#define UPD_PLAYER_NEW  0x0
#define UPD_PLAYER_MOVE 0x1

/**
 * Update represents a Server-to-client message. Updates encode information
 * about a change to the state of the world.
 *
 * Examples: A new player connected, a player moved, etc.
 */
class Update
{
    protected:
    uint8_t updateId;
    std::vector<uint8_t> args;

    public:
    Update(uint8_t updateId, std::vector<uint8_t> args) : updateId(updateId), args(args) {};
    Update(uint8_t buffer[16]);

    uint8_t getUpdateId() { return updateId; }
    uint8_t getArgument(int idx) { return args[idx]; }
};

#endif
