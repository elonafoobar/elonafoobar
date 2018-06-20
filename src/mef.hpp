#pragma once

namespace elona
{

#define MEF_MAX 200

void initialize_mef();
void mef_add(
    int = 0,
    int = 0,
    int = 0,
    int = 0,
    int = 0,
    int = 0,
    int = 0,
    int = 0,
    int = 0,
    int = 0);
void mef_delete(int = 0);
void mef_update();
void mef_proc(int);
bool mef_proc_from_movement(int);
bool mef_proc_from_physical_attack(int);
void mef_clear_all();

} // namespace elona
