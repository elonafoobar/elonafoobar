#pragma once



namespace elona
{


struct position_t
{
    int x = 0;
    int y = 0;
};


inline bool operator==(const position_t& lhs, const position_t& rhs)
{
    return lhs.x == rhs.x && lhs.x == rhs.x;
}


inline bool operator!=(const position_t& lhs, const position_t& rhs)
{
    return !(lhs == rhs);
}



} // namespace elona
