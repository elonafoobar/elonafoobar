#pragma once

#include "data/id.hpp"
#include "optional.hpp"



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
void gain_level(Character& chara);
void grow_primary_skills(Character& chara);
void update_required_experience(Character& chara);
void earn_gold(Character& chara, int delta);
void earn_platinum(Character& chara, int delta);

int gain_skills_by_geen_engineering(
    const Character& original_ally,
    const Character& gene_ally);

/**
 * Gets a body part which will be transplanted from @a gene_ally to @a
 * original_ally.
 *
 * @param original_ally The ally who gains a new gene.
 * @param gene_ally The ally who provides thier gene.
 * @return Transplanted body part ID if possible.
 */
optional<data::InstanceId> gene_engineering_get_transplanted_body_part(
    const Character& original_ally,
    const Character& gene_ally);

} // namespace elona
