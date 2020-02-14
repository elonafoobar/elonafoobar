#include <memory>
#include <sstream>

#include "../elona/character.hpp"
#include "../elona/putit.hpp"
#include "../thirdparty/hayai/hayai.hpp"

using namespace elona;



class SerializationFixture : public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        c = std::make_unique<Character>();
    }


    virtual void TearDown()
    {
        c.reset();
        ss.clear();
    }


    void Write()
    {
        putit::BinaryOArchive::save(ss, *c);
    }


    void Read()
    {
        putit::BinaryIArchive::load(ss, *c);
    }


private:
    std::unique_ptr<Character> c;
    std::stringstream ss;
};



BENCHMARK_F(SerializationFixture, BenchSerialization, 50, 1000)
{
    Write();
    Read();
}
