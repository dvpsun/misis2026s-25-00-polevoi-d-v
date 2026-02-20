#include "bitsetd.hpp"

BitsetD::BitsetD(const int32_t size, const bool val)
  : size_(64)
  , bits_((size + 31) / 32)
{

}

BitsetD::BitsetD(const std::uint64_t mask, const std::int32_t size) 
  : size_(64)
  , bits_{ static_cast<uint32_t>(mask & 0x00000000FFFFFFFFUL), 
           static_cast<uint32_t>((mask>>32) & 0x00000000FFFFFFFFUL) }  {
}