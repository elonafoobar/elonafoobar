#include "../elona/serialization/serialization.hpp"

#include <memory>
#include <sstream>

#include "../elona/character.hpp"
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
        serialization::binary::save(ss, *c);
    }


    void Read()
    {
        serialization::binary::load(ss, *c);
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
