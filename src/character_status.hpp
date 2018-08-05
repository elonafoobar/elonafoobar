#pragma once

namespace elona
{

struct character;

void modify_ether_disease_stage(int delta);
void modify_potential(character& cc, int id, int delta);
void modify_karma(character& cc, int delta);
void modify_weight(character& cc, int delta, bool force = false);
void modify_height(character& cc, int delta);
void refresh_speed(character& cc);
void refresh_speed_correction_value(character& cc);
void gain_new_body_part(character& cc);
void gain_level(character& cc);
void grow_primary_skills(character& cc);
void update_required_experience(character& cc);
void earn_gold(character& cc, int delta);
void earn_platinum(character& cc, int delta);

} // namespace elona
