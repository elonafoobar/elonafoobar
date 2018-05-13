#pragma once

namespace elona
{

int encadd(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
int encfind(int = 0, int = 0);
bool encfindspec(int = 0, int = 0);
void encremove(int = 0, int = 0, int = 0);
int randomenc(int = 0);
int randomenclv(int = 0);
int randomencp(int = 0);
void sortenc(int = 0);
int encflt(int = 0, int = 0);
void initialize_enchantment_data();
void putenclv(int = 0);
void add_enchantments_depending_on_ego();
void add_enchantment_by_fixed_ego();
void add_enchantments();

void initialize_ego_data();
void egoadd(int = 0, int = 0);

} // namespace elona
