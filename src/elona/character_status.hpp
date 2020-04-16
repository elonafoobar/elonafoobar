#pragma once

namespace elona
{

struct Character;

void modify_ether_disease_stage(int delta);
void modify_potential(Character& chara, int id, int delta);
void modify_karma(Character& chara, int delta);
void modify_weight(Character& chara, int delta, bool force = false);
void modify_height(Character& chara, int delta);
void refresh_speed(Character& chara);
void refresh_speed_correction_value(Character& chara);
void gain_new_body_part(Character& chara);
void gain_level(Character& chara);
void grow_primary_skills(Character& chara);
void update_required_experience(Character& chara);
void earn_gold(Character& chara, int delta);
void earn_platinum(Character& chara, int delta);

int gain_skills_by_geen_engineering(
    Character& original_ally,
    Character& gene_ally);
int transplant_body_parts(Character& original_ally, Character& gene_ally);

} // namespace elona
