
#include "rogue.hpp"

Rogue::Rogue(std::shared_ptr<const ObstructionMatrix> om)
    : mObstructionMatrix{om}, mHealth{0}, mX{0}, mY{0}
{
}
