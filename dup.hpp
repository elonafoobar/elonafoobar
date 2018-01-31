namespace elona
{
template <typename T>
struct elona_dup1
{
    elona_dup1(elona_vector1<T>& vector, int i)
        : vector(vector)
        , i(i)
    {
    }


    explicit operator bool()
    {
        if constexpr (std::is_same_v<T, int>)
        {
            return static_cast<bool>(**this);
        }
        else if constexpr (std::is_same_v<T, std::string>)
        {
            return static_cast<bool>(std::stoi(**this));
        }
        else
        {
            static_assert(false_v<T>);
        }
    }



    elona_vector1<T>& vector;
    int i;



    operator T&()
    {
        return **this;
    }



    T& operator*()
    {
        return vector(i);
    }


    elona_dup1& operator=(const T& v)
    {
        vector(i) = std::to_string(n);
        return *this;
    }


    elona_dup1& operator=(int n)
    {
        if constexpr (std::is_same_v<T, int>)
        {
            vector(i) = n;
        }
        else
        {
            vector(i) = std::to_string(n);
        }
        return *this;
    }


    elona_dup1& operator=(elona_dup1<T>& other)
    {
        vector(i) = other.vector(other.i);
        return *this;
    }


    elona_dup1& operator=(elona_vector1<T>& other)
    {
        vector(i) = other(0);
        return *this;
    }


    bool operator==(int other)
    {
        if constexpr (std::is_same_v<T, int>)
        {
            return vector(i) == other;
        }
        else
        {
            return vector(i) == std::to_string(other);
        }
    }



    bool operator==(const std::string& s)
    {
        if constexpr (std::is_same_v<T, std::string>)
        {
            return vector(i) == s;
        }
        else
        {
            static_assert(false_v<T>);
        }
    }


    template <typename U>
    bool operator!=(const T& other)
    {
        return !this->operator==(other);
    }
};


template <typename T>
bool operator==(const T& lhs, elona_dup1<T>& rhs)
{
    return lhs == *rhs;
}

template <typename T>
bool operator!=(const T& lhs, elona_dup1<T>& rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator==(elona_vector1<T>& lhs, elona_dup1<T>& rhs)
{
    return lhs(0) == *rhs;
}

template <typename T>
bool operator!=(elona_vector1<T>& lhs, elona_dup1<T>& rhs)
{
    return !(lhs == rhs);
}



inline std::string operator+(
    const std::string& lhs,
    elona_dup1<std::string>& rhs)
{
    return lhs + *rhs;
}



template <typename T>
struct elona_dup2
{
    elona_dup2(elona_vector2<T>& vector, int i, int j)
        : vector(vector)
        , i(i)
        , j(j)
    {
    }


    elona_vector2<T>& vector;
    int i;
    int j;



    operator T&()
    {
        return **this;
    }



    T& operator*()
    {
        return vector(i, j);
    }



    T& operator()(int i_)
    {
        return vector(i + i_, j);
    }


    elona_dup2& operator=(const T& other)
    {
        **this = other;
        return *this;
    }
};



inline elona_dup2<int> eqhelm{initeq, 0, 0};
inline elona_dup2<int> eqweapon1{initeq, 0, 1};
inline elona_dup2<int> eqshield{initeq, 0, 2};
inline elona_dup2<int> eqrange{initeq, 0, 3};
inline elona_dup2<int> eqammo{initeq, 0, 4};
inline elona_dup2<int> eqweapon2{initeq, 0, 5};
inline elona_dup2<int> eqarmor{initeq, 0, 6};
inline elona_dup2<int> eqglove{initeq, 0, 7};
inline elona_dup2<int> eqboots{initeq, 0, 8};
inline elona_dup2<int> eqcloack{initeq, 0, 9};
inline elona_dup2<int> eqgirdle{initeq, 0, 10};
inline elona_dup2<int> eqring1{initeq, 0, 11};
inline elona_dup2<int> eqring2{initeq, 0, 12};
inline elona_dup2<int> eqamulet1{initeq, 0, 13};
inline elona_dup2<int> eqamulet2{initeq, 0, 14};



} // namespace elona
