#include "../thirdparty/hayai/hayai.hpp"

class ElonaFixture
    :   public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

BENCHMARK_F(ElonaFixture, TestBenchmark, 10, 100)
{
    std::cout << "Hello, world!" << std::endl;
}
