#include "../thirdparty/hayai/hayai.hpp"

#include "util.hpp"
#include "../testing.hpp"
#include "../ability.hpp"
#include "../character.hpp"
#include "../debug.hpp"
#include "../variables.hpp"
#include <cassert>

class GenerateCharacterFixture
    :   public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        testing::pre_init();
        testing::start_in_debug_map();
    }

    virtual void TearDown()
    {
        testing::post_run();
    }

    void AddChara()
    {
        int x = i % 50;
        int y = i / 50;
        assert(chara_create(-1, 3, x, y) == 1);
        i++;
    }
private:
    int i = 0;
};

BENCHMARK_F(GenerateCharacterFixture, BenchGenerateCharacter, 10, 100)
{
    AddChara();
}
