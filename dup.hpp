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



inline std::string operator+(const std::string& lhs, elona_dup1<std::string>& rhs)
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

inline elona_dup2<int> roomexist{rdata, 0, 0};
inline elona_dup2<int> roomx{rdata, 0, 1};
inline elona_dup2<int> roomy{rdata, 0, 2};
inline elona_dup2<int> roomwidth{rdata, 0, 3};
inline elona_dup2<int> roomheight{rdata, 0, 4};
inline elona_dup2<int> roomexit{rdata, 0, 5};
inline elona_dup2<int> roomexitmax{rdata, 0, 6};
inline elona_dup2<int> roomentrancex{rdata, 0, 7};
inline elona_dup2<int> roomentrancey{rdata, 0, 8};

inline elona_dup1<std::string> key_identify{key_buff, 2};
inline elona_dup1<std::string> key_pageup{key_buff, 3};
inline elona_dup1<std::string> key_pagedown{key_buff, 4};
inline elona_dup1<std::string> key_cancel{key_buff, 5};
inline elona_dup1<std::string> key_help{key_buff, 6};
inline elona_dup1<std::string> key_msglog{key_buff, 7};
inline elona_dup1<std::string> key_enter{key_buff, 8};
inline elona_dup1<std::string> key_save{key_buff, 9};
inline elona_dup1<std::string> key_north{key_buff, 10};
inline elona_dup1<std::string> key_northeast{key_buff, 11};
inline elona_dup1<std::string> key_east{key_buff, 12};
inline elona_dup1<std::string> key_southeast{key_buff, 13};
inline elona_dup1<std::string> key_south{key_buff, 14};
inline elona_dup1<std::string> key_southwest{key_buff, 15};
inline elona_dup1<std::string> key_west{key_buff, 16};
inline elona_dup1<std::string> key_northwest{key_buff, 17};
inline elona_dup1<std::string> key_skill{key_buff, 18};
inline elona_dup1<std::string> key_close{key_buff, 19};
inline elona_dup1<std::string> key_cast{key_buff, 20};
inline elona_dup1<std::string> key_drink{key_buff, 22};
inline elona_dup1<std::string> key_read{key_buff, 23};
inline elona_dup1<std::string> key_zap{key_buff, 24};
inline elona_dup1<std::string> key_fire{key_buff, 25};
inline elona_dup1<std::string> key_search{key_buff, 26};
inline elona_dup1<std::string> key_target{key_buff, 27};
inline elona_dup1<std::string> key_dig{key_buff, 28};
inline elona_dup1<std::string> key_wait{key_buff, 30};
inline elona_dup1<std::string> key_inventory{key_buff, 31};
inline elona_dup1<std::string> key_drop{key_buff, 32};
inline elona_dup1<std::string> key_get{key_buff, 33};
inline elona_dup1<std::string> key_wipe{key_buff, 34};
inline elona_dup1<std::string> key_charainfo{key_buff, 35};
inline elona_dup1<std::string> key_eat{key_buff, 36};
inline elona_dup1<std::string> key_wear{key_buff, 37};
inline elona_dup1<std::string> key_godown{key_buff, 38};
inline elona_dup1<std::string> key_goup{key_buff, 39};
inline elona_dup1<std::string> key_interact{key_buff, 40};
inline elona_dup1<std::string> key_rest{key_buff, 41};
inline elona_dup1<std::string> key_use{key_buff, 42};
inline elona_dup1<std::string> key_bash{key_buff, 43};
inline elona_dup1<std::string> key_open{key_buff, 44};
inline elona_dup1<std::string> key_dip{key_buff, 45};
inline elona_dup1<std::string> key_pray{key_buff, 46};
inline elona_dup1<std::string> key_offer{key_buff, 47};
inline elona_dup1<std::string> key_journal{key_buff, 48};
inline elona_dup1<std::string> key_material{key_buff, 49};
inline elona_dup1<std::string> key_quick{key_buff, 50};
inline elona_dup1<std::string> key_get2{key_buff, 51};
inline elona_dup1<std::string> key_trait{key_buff, 52};
inline elona_dup1<std::string> key_look{key_buff, 53};
inline elona_dup1<std::string> key_give{key_buff, 54};
inline elona_dup1<std::string> key_prev{key_buff, 55};
inline elona_dup1<std::string> key_next{key_buff, 56};
inline elona_dup1<std::string> key_quickinv{key_buff, 57};
inline elona_dup1<std::string> key_throw{key_buff, 58};
inline elona_dup1<std::string> key_esc{key_buff, 59};
inline elona_dup1<std::string> key_alt{key_buff, 60};
inline elona_dup1<std::string> key_mode{key_buff, 61};
inline elona_dup1<std::string> key_ammo{key_buff, 62};
inline elona_dup1<std::string> key_mode2{key_buff, 63};


}
