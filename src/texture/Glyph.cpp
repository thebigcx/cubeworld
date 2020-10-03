#include "Glyph.h"

Glyph::Glyph(unsigned int texture, glm::ivec2 size, glm::ivec2 bearing, unsigned int advance)
: m_texture(texture)
, m_size(size)
, m_bearing(bearing)
, m_advance(advance)
{

}