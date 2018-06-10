#pragma once



namespace elona
{



void healhp(int cc, int delta);
void healmp(int cc, int delta);
void healsp(int cc, int delta);
int dmghp(int, int, int = 0, int = 0, int = 0);
void end_dmghp();
void dmgmp(int cc, int delta);
void dmgsp(int cc, int delta);
void healsan(int prm_862, int prm_863);
void damage_insanity(int cc, int delta);
bool actionsp(int cc, int sp);



} // namespace elona
