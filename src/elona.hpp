#pragma once


#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "enums.hpp"
#include "gdata.hpp"
#include "mdata.hpp"
#include "snail/color.hpp"
#include "snail/font.hpp"
#include "snail/input.hpp"
#include "snail/window.hpp"
#include "util.hpp"


namespace elona
{
int run();


template <typename...>
constexpr bool false_v = false;



template <typename T>
void allocate_and_clear_vector(std::vector<T>& v, size_t size)
{
    v.resize(size);
    std::fill(std::begin(v), std::end(v), T{});
}



template <typename T>
struct elona_vector1
{
    elona_vector1()
        : storage(1)
    {
    }


    T& operator()(size_t i)
    {
        if (i >= storage.size())
        {
            storage.resize(i + 1);
        }
        return storage.at(i);
    }

    elona_vector1<T>& operator=(const T& v)
    {
        storage.at(0) = v;
        return *this;
    }


    elona_vector1<T>& operator=(elona_vector1<T>& v)
    {
        storage.at(0) = v(0);
        return *this;
    }


    operator T&()
    {
        return storage.at(0);
    }


    template <
        typename U,
        std::enable_if_t<
            std::is_same<T, std::string>::value && std::is_same<U, int>::value,
            std::nullptr_t> = nullptr>
    T& operator+=(const U& x)
    {
        return storage.at(0) += std::to_string(x);
    }


    template <
        typename U,
        std::enable_if_t<
            !std::is_same<T, std::string>::value
                || !std::is_same<U, int>::value,
            std::nullptr_t> = nullptr>
    T& operator+=(const U& x)
    {
        return storage.at(0) += x;
    }


    T& operator+=(elona_vector1<T>& v)
    {
        return storage.at(0) += v(0);
    }


    void clear()
    {
        std::fill(std::begin(storage), std::end(storage), T{});
    }


    void allocate_and_clear(size_t size)
    {
        allocate_and_clear_vector(storage, size);
    }


    size_t size() const noexcept
    {
        return storage.size();
    }



    typename std::vector<T>::iterator begin()
    {
        return std::begin(storage);
    }



    typename std::vector<T>::iterator end()
    {
        return std::end(storage);
    }



    typename std::vector<T>::const_iterator begin() const
    {
        return std::begin(storage);
    }



    typename std::vector<T>::const_iterator end() const
    {
        return std::end(storage);
    }



private:
    std::vector<T> storage;
};



template <typename T>
struct elona_vector2
{
    T& operator()(size_t i, size_t j)
    {
        if (j >= storage.size())
        {
            storage.resize(j + 1);
            for (size_t j_ = 0; j_ < j + 1; ++j_)
            {
                if (!storage.at(j_))
                {
                    storage.at(j_) = std::make_unique<std::vector<T>>();
                }
            }
        }
        if (i >= storage.at(j)->size())
        {
            storage.at(j)->resize(i + 1);
        }
        return (*storage.at(j))[i];
    }


    void clear()
    {
        for (auto& v : storage)
        {
            for (auto& i : *v)
            {
                i = T{};
            }
        }
    }


    void clear(size_t j)
    {
        if (j >= storage.size())
            return;

        std::fill(std::begin(*storage.at(j)), std::end(*storage.at(j)), T{});
    }


    void clear(size_t j, size_t i_begin, size_t i_length)
    {
        if (j >= storage.size())
            return;

        if (i_begin + i_length >= storage.at(j)->size())
        {
            storage.at(j)->resize(i_begin + i_length + 1);
        }
        std::fill_n(std::begin(*storage.at(j)) + i_begin, i_length, T{});
    }


    // FIXME: DRY!
    void allocate_and_clear(size_t i_size, size_t j_size)
    {
        storage.resize(j_size);
        for (size_t j = 0; j < j_size; ++j)
        {
            if (!storage.at(j))
            {
                storage.at(j) = std::make_unique<std::vector<T>>();
            }
            allocate_and_clear_vector(*storage.at(j), i_size);
        }
    }


    size_t j_size() const noexcept
    {
        return storage.size();
    }


    size_t i_size() const noexcept
    {
        return storage.empty() ? 0 : storage.at(0)->size();
    }


private:
    std::vector<std::unique_ptr<std::vector<T>>> storage;
};



template <typename T>
struct elona_vector3
{
    T& operator()(size_t i, size_t j, size_t k)
    {
        if (k >= storage.size())
        {
            storage.resize(k + 1);
            for (size_t k_ = 0; k_ < k + 1; ++k_)
            {
                if (!storage.at(k_))
                {
                    storage.at(k_) = std::make_unique<
                        std::vector<std::unique_ptr<std::vector<T>>>>();
                }
            }
        }
        if (j >= storage.at(k)->size())
        {
            storage.at(k)->resize(j + 1);
            for (size_t j_ = 0; j_ < j + 1; ++j_)
            {
                if (!(*storage.at(k))[j_])
                {
                    (*storage.at(k))[j_] = std::make_unique<std::vector<T>>();
                }
            }
        }
        if (i >= (*storage.at(k))[j]->size())
        {
            (*storage.at(k))[j]->resize(i + 1);
        }
        return (*(*storage.at(k))[j])[i];
    }



    // FIXME: DRY!
    void allocate_and_clear(size_t i_size, size_t j_size, size_t k_size)
    {
        storage.resize(k_size);
        for (size_t k = 0; k < k_size; ++k)
        {
            if (!storage.at(k))
            {
                storage.at(k) = std::make_unique<
                    std::vector<std::unique_ptr<std::vector<T>>>>();
            }
            storage.at(k)->resize(j_size);
            for (size_t j = 0; j < j_size; ++j)
            {
                if (!(*storage.at(k))[j])
                {
                    (*storage.at(k))[j] = std::make_unique<std::vector<T>>();
                }
                allocate_and_clear_vector(*(*storage.at(k))[j], i_size);
            }
        }
    }


    size_t k_size() const noexcept
    {
        return storage.size();
    }


    size_t j_size() const noexcept
    {
        return storage.empty() ? 0 : storage.at(0)->size();
    }


    size_t i_size() const noexcept
    {
        return storage.empty()
            ? 0
            : storage.at(0)->empty() ? 0 : (*storage.at(0))[0]->size();
    }



private:
    std::vector<std::unique_ptr<std::vector<std::unique_ptr<std::vector<T>>>>>
        storage;
};



std::string operator+(const std::string& lhs, int rhs);
std::string operator+(
    elona_vector1<std::string>& lhs,
    elona_vector1<std::string>& rhs);
std::string operator+(const std::string& lhs, elona_vector1<std::string>& rhs);
std::string operator+(elona_vector1<std::string>& lhs, int rhs);
std::string operator+(elona_vector1<std::string>& lhs, const std::string& rhs);



#define DEFINE_CMP(op) \
    template <typename T> \
    bool operator op(elona_vector1<T>& lhs, const T& rhs) \
    { \
        return lhs(0) op rhs; \
    } \
    template <typename T> \
    bool operator op(const T& lhs, elona_vector1<T>& rhs) \
    { \
        return lhs op rhs(0); \
    } \
    template <typename T> \
    bool operator op(elona_vector1<T>& lhs, elona_vector1<T>& rhs) \
    { \
        return lhs(0) op rhs(0); \
    }


DEFINE_CMP(==)
DEFINE_CMP(!=)
DEFINE_CMP(>)
DEFINE_CMP(>=)
DEFINE_CMP(<)
DEFINE_CMP(<=)


#undef DEFINE_CMP



void await(int msec);


void boxf(
    int x,
    int y,
    int width,
    int height,
    const snail::color& color = {0, 0, 0, 0});
void boxf();

void boxl(int x, int y, int width, int height, const snail::color& color);


void buffer(int window_id, int width = 0, int heihgt = 0);


void color(int r, int g, int b);


int dialog(const std::string& message, int = 0);



void exec(const std::string&, int);


void font(
    int size,
    snail::font_t::style_t style = snail::font_t::style_t::regular);

void gcopy(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_width = -1,
    int dst_height = -1);

void gcopy_c(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height);

void gcopy_c(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_width,
    int dst_height);


bool getkey(snail::key);

void getstr(
    std::string& out,
    const std::string& source,
    int offset,
    char delimiter,
    int limit = 0);

int ginfo(int type);



void gmode(int mode, int alpha = 255);



void grotate(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    double angle);

void grotate(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_width,
    int dst_height,
    double angle);

void gsel(int window_id);

int instr(const std::string& str, size_t pos, const std::string pattern);


int stoi(const std::string&);


void line(
    int x1,
    int y1,
    int x2,
    int y2,
    const snail::color& color = {0, 0, 0});



void mes(const std::string& text);

void mes(int n);

void mesbox(std::string& buffer, bool text = false);

void mmload(const fs::path& filepath, int id, int mode = 0);

void mmplay(int id);

void mmstop();

void noteadd(const std::string& text, int index = -1, int = 0);

void notedel(size_t index);

void noteget(std::string& out, size_t index);

int noteinfo();

int notesel(std::string&);

void noteunsel();


void objprm(int, const std::string&);



void pget(int x, int y);

void picload(const fs::path& file, int immediately = 0);

void pos(int x, int y = 0);



void redraw();


int stick(int allow_repeat_keys = 0);


size_t strlen_u(const std::string& str);

std::string strmid(const std::string& source, int pos, int length);

void title(
    const std::string& title_str,
    const std::string& display_mode = "",
    snail::window::fullscreen_mode_t fullscreen_mode =
        snail::window::fullscreen_mode_t::windowed);


int wpeek(int x, size_t index);

void wpoke(int& x, size_t index, int y);



// imported functions



void ematan(int, int, int);

void apledit(int&, int, int = 0);

void func_2(int, int, int, int, int, int);

void DIINIT();

int DIGETJOYNUM();


void DIGETJOYSTATE(int, int);

int HMMBITCHECK(int, int);


int CreateMutexA(int, int, const std::string&);



int timeGetTime();

int ImmGetContext(int);


void ImmReleaseContext(int, int);

void ImmSetOpenStatus(int, int);


int ImmGetOpenStatus(int);



void onkey_0();



void bload(const fs::path& filename, std::string& data, int size = 0, int = 0);
void bload(
    const fs::path& filename,
    int& data,
    int size = sizeof(int),
    int = 0);
void bload(
    const fs::path& filename,
    elona_vector1<int>& data,
    int size = 0,
    int = 0);


void bsave(const fs::path& filename, const std::string& data);
void bsave(const fs::path& filename, int data);
void bsave(const fs::path& filename, elona_vector1<int>& data);


template <typename T>
inline T clamp(const T& x, const T& min, const T& max)
{
    return std::min(std::max(x, min), max);
}



} // namespace elona


using namespace elona;



#define DIM1(a) (a).clear()
#define DIM2(a, b) (a).allocate_and_clear(b)
#define DIM3(a, b, c) (a).allocate_and_clear(b, c)
#define DIM4(a, b, c, d) (a).allocate_and_clear(b, c, d)
#define SDIM1(a) (a).clear()
#define SDIM2(a, b) \
    do \
    { \
        (a).clear(); \
        if ((b) > 0) \
            (a)(0).resize(b); \
    } while (0)
#define SDIM3(a, b, c) (a).allocate_and_clear(c)
#define SDIM4(a, b, c, d) (a).allocate_and_clear(c, d)

#define DIALOG_OK 1
#define DIALOG_YES 6
#define DIALOG_NO 7


// For basic_string literal suffix.
using namespace std::literals::string_literals;
