#pragma once

namespace elona
{

struct Character;

void modify_ether_disease_stage(int delta);
void modify_potential(Character& cc, int id, int delta);
void modify_karma(Character& cc, int delta);
void modify_weight(Character& cc, int delta, bool force = false);
void modify_height(Character& cc, int delta);
void refresh_speed(Character& cc);
void refresh_speed_correction_value(Character& cc);
void gain_new_body_part(Character& cc);
void gain_level(Character& cc);
void grow_primary_skills(Character& cc);
void update_required_experience(Character& cc);
void earn_gold(Character& cc, int delta);
void earn_platinum(Character& cc, int delta);

int gain_skills_by_geen_engineering(
    Character& original_ally,
    Character& gene_ally);
int transplant_body_parts(Character& original_ally, Character& gene_ally);

} // namespace elona
