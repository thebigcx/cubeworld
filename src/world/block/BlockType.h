#pragma once

class BlockType
{
    public:

        enum
        {
            Air,
            Grass,
            Stone,
            Dirt,
            TNT
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

        int getId() const
        {
            return id;
        }

    private:
        int id;
};