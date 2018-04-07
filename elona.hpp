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
#include "macro_gdata.hpp"
#include "snail/color.hpp"
#include "snail/input.hpp"
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
        if (i >= std::size(storage))
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


    operator fs::path()
    {
        return fs::path(storage.at(0));
    }


    template <typename U>
    T& operator+=(const U& x)
    {
        if constexpr (std::is_same_v<T, std::string> && std::is_same_v<U, int>)
        {
            return storage.at(0) += std::to_string(x);
        }
        else
        {
            return storage.at(0) += x;
        }
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
        return std::size(storage);
    }



private:
    std::vector<T> storage;
};



template <typename T>
struct elona_vector2
{
    T& operator()(size_t i, size_t j)
    {
        if (j >= std::size(storage))
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
        if (i >= std::size(*storage.at(j)))
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
        if (j >= std::size(storage))
            return;

        std::fill(std::begin(*storage.at(j)), std::end(*storage.at(j)), T{});
    }


    void clear(size_t j, size_t i_begin, size_t i_length)
    {
        if (j >= std::size(storage))
            return;

        if (i_begin + i_length >= std::size(*storage.at(j)))
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
        return std::size(storage);
    }


    size_t i_size() const noexcept
    {
        return std::empty(storage) ? 0 : std::size(*storage.at(0));
    }


private:
    std::vector<std::unique_ptr<std::vector<T>>> storage;
};



template <typename T>
struct elona_vector3
{
    T& operator()(size_t i, size_t j, size_t k)
    {
        if (k >= std::size(storage))
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
        if (j >= std::size(*storage.at(k)))
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
        if (i >= std::size(*(*storage.at(k))[j]))
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
        return std::size(storage);
    }


    size_t j_size() const noexcept
    {
        return std::empty(storage) ? 0 : std::size(*storage.at(0));
    }


    size_t i_size() const noexcept
    {
        return std::empty(storage)
            ? 0
            : std::empty(*storage.at(0)) ? 0 : std::size(*(*storage.at(0))[0]);
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



void await(int msec = 0);

// CANNOT BE IMPLEMENTED
void axobj(int, const std::string&, int, int);


void bcopy(const fs::path& from, const fs::path& to);

// fullscreen
void bgscr(int window_id, int width, int height, int, int);


void boxf(
    int x1,
    int y1,
    int x2,
    int y2,
    const snail::color& color = {0, 0, 0, 0});
void boxf(const snail::color& color = {0, 0, 0, 0});


void buffer(int window_id, int width = 0, int heihgt = 0);

void chgdisp(int, int width, int height);


void clrobj(int);


void color(int r, int g, int b);



void delcom(int);

void elona_delete(const fs::path& filename);

int dialog(const std::string& message, int = 0);



void exec(const std::string&, int);


void font(const std::string& name, int size, int style);

void gcopy(
    int window_id,
    int src_x,
    int src_y,
    int src_width = 0,
    int src_height = 0);

bool getkey(snail::key);

void getstr(
    std::string& out,
    const std::string& source,
    int offset,
    char delimiter,
    int limit = 0);

int ginfo(int type);


void gmode(int mode, int width = -1, int height = -1, int alpha = 255);

void grotate(
    int window_id,
    int src_x,
    int src_y,
    double angle,
    int dst_width = 0,
    int dst_height = 0);

void gsel(int window_id);

void gzoom(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_width,
    int dst_height);


int instr(const std::string& str, size_t pos, const std::string pattern);


int stoi(std::string_view s);


template <typename T>
size_t length(elona_vector2<T>& arr)
{
    return arr.i_size();
}



template <typename T>
size_t length(const elona_vector1<T>& arr)
{
    return std::size(arr);
}



size_t length(const std::string& str);

template <typename T>
size_t length2(const elona_vector2<T>& arr)
{
    return arr.j_size();
}



void line(int x1, int y1, int x2, int y2);

void line(int x, int y);



void memcpy(
    elona_vector2<int>& src,
    int src_i,
    int src_j,
    elona_vector2<int>& dst,
    int dst_i,
    int dst_j,
    size_t size);


// void memexpand(void* memory, size_t size)
// {
// }
#define memexpand(a, b)

// void memfile(void* buf)
// {
// }
#define memfile(a)


void mes(const std::string& text);

void mes(int n);

void mesbox(
    std::string& buffer,
    int width,
    int height,
    int style,
    int max_input_size = -1);

void mkdir(const fs::path& path);

void mmload(const std::string& file, int id, int mode = 0);

void mmplay(int id);

void mmstop();

void noteadd(const std::string& text, int index = -1, int = 0);

void notedel(size_t index);

void noteget(std::string& out, size_t index);

int noteinfo();

int notesel(std::string&);

void noteunsel();


void objmode(int, int = 0);

void objprm(int, const std::string&);

void objsel(int);



void pget(int x, int y);

void picload(const fs::path& file, int immediately = 0);

void pos(int x, int y = 0);


void randomize(std::random_device::result_type seed = std::random_device{}());


void redraw();

int rnd(int n);

void screen(int window_id, int width, int height, int mode, int x, int y);


void stick(int& out, int = 0);


size_t strlen_u(const std::string& str);

std::string strmid(const std::string& source, int pos, int length);

void title(const std::string& title_str);

void width(int width, int height, int, int);


int wpeek(int x, size_t index);

void wpoke(int& x, size_t index, int y);



// imported functions


void exrand_randomize(
    std::random_device::result_type seed = std::random_device{}());

void exrand_rnd(int& resul, int max);

void func_1(const std::string&, int);

void xnotesel(std::string&);


void xnoteadd(const std::string&);

void gfini(int width, int height);

void gfdec(int r, int g, int b);

void gfdec2(int r, int g, int b);

void gfinc(int r, int g, int b);

void ematan(int, int, int);


int aplsel(const std::string&);

int aplobj(const std::string&, int);

void apledit(int, int, int = 0);

void func_2(int, int, int, int, int, int);

int DSINIT();

void DSEND();

void DSRELEASE(int);


void DSLOADFNAME(const std::string& filename, int id);

void DSPLAY(int, int);

void DSSTOP(int);

void DSSETVOLUME(int, int);


int DSGETMASTERVOLUME();

int CHECKPLAY(int id);

int DMINIT();

void DMEND();


void DMLOADFNAME(const std::string&, int);

void DMPLAY(int, int);

void DMSTOP();

void DIINIT();

int DIGETJOYNUM();


void DIGETJOYSTATE(int, int);

void HMMBITON(int&, int);

void HMMBITOFF(int&, int);

int HMMBITCHECK(int, int);


int sockopen(int, const std::string&, int);

void sockclose();

int sockget(const std::string&, int);

int sockput(const std::string&);

void netinit();


void netexec(int&);

void neterror(const std::string&);

void neturl(const std::string&);

void netdlname(const std::string&);

void netrequest(const std::string&);


void GetLastError();

int CreateMutexA(int, int, const std::string&);


void CloseHandle(int id);

int func_3();


int LCMapStringA(int, int, const std::string&, int, const std::string&, int);


int GetUserDefaultLCID();

void AppendMenuA();

void CheckMenuRadioItem();

void CreateMenu();


void CreatePopupMenu();

void DrawMenuBar();

void SetMenu();


void keybd_event(int, int = 0, int = 0);

void GetKeyboardState(elona_vector1<int>&);

int timeGetTime();

int ImmGetContext(int);


void ImmReleaseContext(int, int);

void ImmSetOpenStatus(int, int);


int ImmGetOpenStatus(int);



void onkey_0();


void onkey_1();


void end();



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


void memcpy_(
    std::string& dst,
    std::string& src,
    int size,
    int dst_offset = 0,
    int src_offset = 0);



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



// For basic_string literal suffix.
using namespace std::literals::string_literals;
