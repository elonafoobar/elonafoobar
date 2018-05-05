#pragma once

#include "filesystem.hpp"
#include "lib/noncopyable.hpp"



namespace elona
{


class sound : lib::noncopyable
{
public:
private:
};


int DSINIT();
void DSEND();
void DSRELEASE(int);
void DSLOADFNAME(const fs::path& filepath, int id);
void DSPLAY(int, int);
void DSSTOP(int);
void DSSETVOLUME(int, int);
int DSGETMASTERVOLUME();
int CHECKPLAY(int id);

int DMINIT();
void DMEND();
void DMLOADFNAME(const fs::path& filepath, int);
void DMPLAY(int, int);
void DMSTOP();


} // namespace elona
