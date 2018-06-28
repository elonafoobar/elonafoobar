#pragma once

namespace elona
{

struct character;

void rowact_check(int = 0);
void rowact_item(int = 0);
void rowactend(int = 0);

void activity_handle_damage(character&);
void activity_proc(character&);

void prompt_stop_continuous_action();
void continuous_action_perform();
void continuous_action_sex();
void continuous_action_blending();
void continuous_action_others();

} // namespace elona
