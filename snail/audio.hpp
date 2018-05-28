#pragma once

#include <string>

namespace elona
{
namespace snail
{
namespace audio
{

int DSINIT();
void DSLOADFNAME(const std::string& filepath, int id);
void DSPLAY(int, bool);
void DSSTOP(int);
void DSSETVOLUME(int, int);
bool CHECKPLAY(int channel);

int DMINIT();
void DMLOADFNAME(const std::string& filepath, int);
void DMPLAY(int, int);
void DMSTOP();

} // namespace audio
} // namespace snail
} // namespace elona
