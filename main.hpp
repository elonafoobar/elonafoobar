#pragma once

#include <iostream>




int main() { return elona::main(); }

namespace elona
{
std::string calcage(int);

void label_0481();
void label_1419();
void label_1567(int);

int prm_409;
int prm_518;
int prm_818;
int prm_820;
int prm_853;

int tmp_at_m172;

elona_vector2<std::string> invn;
elona_vector1<int> inhlist_at_m184;
elona_vector1<int> inhlist;

int i_at_m68;
double r_at_m133;


#define window_recipe(a, b, c, d, e, f) window_recipe_(b, c, d, e, f)



void label_1547(bool = true);
void label_1550(bool = true);
void label_1553(bool = true);
void label_1557(bool = true);
void label_2743(bool = true);
void label_2737(bool = true);

int label_2654();




struct elona_fmode_t
{
    enum class Type
    {
        integer,
        string,
    } type;

    // FIXME: Use union.
    int i;
    std::string s;

    elona_fmode_t()
        : type(Type::integer)
        , i(0)
    {
    }

    virtual ~elona_fmode_t() = default;

    bool operator==(int i) const noexcept
    {
        return type == Type::integer && this->i == i;
    }

    bool operator==(const std::string& s) const noexcept
    {
        return type == Type::string && this->s == s;
    }

    elona_fmode_t& operator=(int i)
    {
        type = Type::integer;
        this->i = i;
        s.clear();
        return *this;
    }

    elona_fmode_t& operator=(const std::string& s)
    {
        type = Type::string;
        this->s = s;
        i = 0;
        return *this;
    }


    std::string to_string() const
    {
        switch (type)
        {
        case elona_fmode_t::Type::integer:
            return std::to_string(i);
        case elona_fmode_t::Type::string:
            return s;
        }
        assert(0);
    }
};





std::string operator+(const std::string& lhs, const elona_fmode_t& rhs)
{
    return lhs + rhs.to_string();
}


elona_fmode_t fmode;



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



std::string operator+(const std::string& lhs, elona_dup1<std::string>& rhs)
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



elona_dup2<int> eqhelm{initeq, 0, 0};
elona_dup2<int> eqweapon1{initeq, 0, 1};
elona_dup2<int> eqshield{initeq, 0, 2};
elona_dup2<int> eqrange{initeq, 0, 3};
elona_dup2<int> eqammo{initeq, 0, 4};
elona_dup2<int> eqweapon2{initeq, 0, 5};
elona_dup2<int> eqarmor{initeq, 0, 6};
elona_dup2<int> eqglove{initeq, 0, 7};
elona_dup2<int> eqboots{initeq, 0, 8};
elona_dup2<int> eqcloack{initeq, 0, 9};
elona_dup2<int> eqgirdle{initeq, 0, 10};
elona_dup2<int> eqring1{initeq, 0, 11};
elona_dup2<int> eqring2{initeq, 0, 12};
elona_dup2<int> eqamulet1{initeq, 0, 13};
elona_dup2<int> eqamulet2{initeq, 0, 14};

elona_dup2<int> roomexist{rdata, 0, 0};
elona_dup2<int> roomx{rdata, 0, 1};
elona_dup2<int> roomy{rdata, 0, 2};
elona_dup2<int> roomwidth{rdata, 0, 3};
elona_dup2<int> roomheight{rdata, 0, 4};
elona_dup2<int> roomexit{rdata, 0, 5};
elona_dup2<int> roomexitmax{rdata, 0, 6};
elona_dup2<int> roomentrancex{rdata, 0, 7};
elona_dup2<int> roomentrancey{rdata, 0, 8};

elona_dup1<std::string> key_identify{key_buff, 2};
elona_dup1<std::string> key_pageup{key_buff, 3};
elona_dup1<std::string> key_pagedown{key_buff, 4};
elona_dup1<std::string> key_cancel{key_buff, 5};
elona_dup1<std::string> key_help{key_buff, 6};
elona_dup1<std::string> key_msglog{key_buff, 7};
elona_dup1<std::string> key_enter{key_buff, 8};
elona_dup1<std::string> key_save{key_buff, 9};
elona_dup1<std::string> key_north{key_buff, 10};
elona_dup1<std::string> key_northeast{key_buff, 11};
elona_dup1<std::string> key_east{key_buff, 12};
elona_dup1<std::string> key_southeast{key_buff, 13};
elona_dup1<std::string> key_south{key_buff, 14};
elona_dup1<std::string> key_southwest{key_buff, 15};
elona_dup1<std::string> key_west{key_buff, 16};
elona_dup1<std::string> key_northwest{key_buff, 17};
elona_dup1<std::string> key_skill{key_buff, 18};
elona_dup1<std::string> key_close{key_buff, 19};
elona_dup1<std::string> key_cast{key_buff, 20};
elona_dup1<std::string> key_drink{key_buff, 22};
elona_dup1<std::string> key_read{key_buff, 23};
elona_dup1<std::string> key_zap{key_buff, 24};
elona_dup1<std::string> key_fire{key_buff, 25};
elona_dup1<std::string> key_search{key_buff, 26};
elona_dup1<std::string> key_target{key_buff, 27};
elona_dup1<std::string> key_dig{key_buff, 28};
elona_dup1<std::string> key_wait{key_buff, 30};
elona_dup1<std::string> key_inventory{key_buff, 31};
elona_dup1<std::string> key_drop{key_buff, 32};
elona_dup1<std::string> key_get{key_buff, 33};
elona_dup1<std::string> key_wipe{key_buff, 34};
elona_dup1<std::string> key_charainfo{key_buff, 35};
elona_dup1<std::string> key_eat{key_buff, 36};
elona_dup1<std::string> key_wear{key_buff, 37};
elona_dup1<std::string> key_godown{key_buff, 38};
elona_dup1<std::string> key_goup{key_buff, 39};
elona_dup1<std::string> key_interact{key_buff, 40};
elona_dup1<std::string> key_rest{key_buff, 41};
elona_dup1<std::string> key_use{key_buff, 42};
elona_dup1<std::string> key_bash{key_buff, 43};
elona_dup1<std::string> key_open{key_buff, 44};
elona_dup1<std::string> key_dip{key_buff, 45};
elona_dup1<std::string> key_pray{key_buff, 46};
elona_dup1<std::string> key_offer{key_buff, 47};
elona_dup1<std::string> key_journal{key_buff, 48};
elona_dup1<std::string> key_material{key_buff, 49};
elona_dup1<std::string> key_quick{key_buff, 50};
elona_dup1<std::string> key_get2{key_buff, 51};
elona_dup1<std::string> key_trait{key_buff, 52};
elona_dup1<std::string> key_look{key_buff, 53};
elona_dup1<std::string> key_give{key_buff, 54};
elona_dup1<std::string> key_prev{key_buff, 55};
elona_dup1<std::string> key_next{key_buff, 56};
elona_dup1<std::string> key_quickinv{key_buff, 57};
elona_dup1<std::string> key_throw{key_buff, 58};
elona_dup1<std::string> key_esc{key_buff, 59};
elona_dup1<std::string> key_alt{key_buff, 60};
elona_dup1<std::string> key_mode{key_buff, 61};
elona_dup1<std::string> key_ammo{key_buff, 62};
elona_dup1<std::string> key_mode2{key_buff, 63};




template <typename T>
void txt()
{
    static_assert(false_v<T>);
}


std::string txt_tostr(const std::string& s)
{
    return s;
}


std::string txt_tostr(elona_vector1<std::string>& v)
{
    return v(0);
}


template <typename... Args>
void txt(Args&&... args)
{
    std::vector<std::string> text{txt_tostr(args)...};
    txtvalid = 0;
    if (hear != 0)
    {
        snd(hear);
        hear = 0;
    }
    msgtemp = text[rnd(std::size(text))];
    txt_conv();
    tcol_at_txtfunc(0) = 255;
    tcol_at_txtfunc(1) = 255;
    tcol_at_txtfunc(2) = 255;
}



void _fdialog(std::string& prm_710, int prm_711, std::string& prm_712, const std::string& prm_713, const std::string& prm_714)
{
    (void)prm_710;
    (void)prm_711;
    (void)prm_712;
    (void)prm_713;
    (void)prm_714;
}



struct elona_turn_sequence {};


#define CNT cnt
