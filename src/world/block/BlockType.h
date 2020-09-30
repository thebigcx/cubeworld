#pragma once

class BlockType
{
    public:

        enum
        {
            Air,
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

        void setType(int type)
        {
            this->id = type;
        }

        int getId()
        {
            return id;
        }

    private:
        int id;
};