#pragma once

class BlockType
{
    public:

        enum
        {
            Grass,
            Stone,
            Dirt
        };

        BlockType()
        {
            this->id = 0;
        }

        BlockType(int id)
        {
            this->id = id;
        }

        int getId()
        {
            return id;
        }

    private:
        int id;
};