#pragma once

#include "optional.hpp"
#include "position.hpp"



namespace elona
{



class abstract_animation
{
public:
    void play();


protected:
    virtual void do_play() = 0;


    virtual bool updates_screen()
    {
        return true;
    }
};



class failure_to_cast_animation : public abstract_animation
{
public:
    failure_to_cast_animation(const position_t& caster_pos)
        : caster_pos(caster_pos)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& caster_pos;
};



class bright_aura_animation : public abstract_animation
{
public:
    enum class Type
    {
        debuff,
        offering,
        healing,
        healing_rain,
    };


    bright_aura_animation(const position_t& target_pos, Type type)
        : target_pos(target_pos)
        , type(type)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& target_pos;
    Type type;
};



class breath_animation : public abstract_animation
{
public:
    breath_animation(
        const position_t& attacker_pos,
        const position_t& target_pos,
        int element)
        : attacker_pos(attacker_pos)
        , target_pos(target_pos)
        , element(element)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& attacker_pos;
    const position_t& target_pos;
    int element;
};



class ball_animation : public abstract_animation
{
public:
    enum class Type
    {
        ball,
        atomic_bomb,
    };


    ball_animation(
        const position_t& position,
        int range,
        Type type,
        int element = 0)
        : position(position)
        , range(range)
        , type(type)
        , element(element)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& position;
    int range;
    Type type;
    int element;
};



class bolt_animation : public abstract_animation
{
public:
    bolt_animation(
        const position_t& attacker_pos,
        const position_t& target_pos,
        int element,
        int distance)
        : attacker_pos(attacker_pos)
        , target_pos(target_pos)
        , element(element)
        , distance(distance)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& attacker_pos;
    const position_t& target_pos;
    int element;
    int distance;
};



class throwing_object_animation : public abstract_animation
{
public:
    throwing_object_animation(
        const position_t& attacker_pos,
        const position_t& target_pos,
        int item_chip,
        int item_color)
        : attacker_pos(attacker_pos)
        , target_pos(target_pos)
        , item_chip(item_chip)
        , item_color(item_color)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& attacker_pos;
    const position_t& target_pos;
    int item_chip;
    int item_color;
};



class swarm_animation : public abstract_animation
{
public:
    swarm_animation(const position_t& target_pos)
        : target_pos(target_pos)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& target_pos;
};



class ranged_attack_animation : public abstract_animation
{
public:
    enum class Type
    {
        magic_arrow = 0,
        distant_attack = 1,
        bow = 108,
        crossbow = 109,
        firearm = 110,
        throwing = 111,
    };


    ranged_attack_animation(
        const position_t& attacker_pos,
        const position_t& target_pos,
        Type type,
        int fired_item_subcategory = 0,
        int fired_item_image = 0,
        int fired_item_color = 0)
        : attacker_pos(attacker_pos)
        , target_pos(target_pos)
        , type(type)
        , fired_item_subcategory(fired_item_subcategory)
        , fired_item_image(fired_item_image)
        , fired_item_color(fired_item_color)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& attacker_pos;
    const position_t& target_pos;
    Type type;
    int fired_item_subcategory;
    int fired_item_image;
    int fired_item_color;
};



class melee_attack_animation : public abstract_animation
{
public:
    melee_attack_animation(
        const position_t& position,
        bool debris,
        int attack_skill,
        int damage_percent,
        bool is_critical)
        : position(position)
        , debris(debris)
        , attack_skill(attack_skill)
        , damage_percent(damage_percent)
        , is_critical(is_critical)
    {
    }


protected:
    virtual void do_play() override;

private:
    const position_t& position;
    bool debris;
    int attack_skill;
    int damage_percent;
    bool is_critical;
};



class gene_engineering_animation : public abstract_animation
{
public:
    gene_engineering_animation(const position_t& position)
        : position(position)
    {
    }


protected:
    virtual void do_play() override;

private:
    const position_t& position;
};



class miracle_animation : public abstract_animation
{
public:
    miracle_animation()
    {
    }


protected:
    virtual void do_play() override;
};



class meteor_animation : public abstract_animation
{
public:
    meteor_animation()
    {
    }


protected:
    virtual void do_play() override;
};



class ragnarok_animation : public abstract_animation
{
public:
    ragnarok_animation()
    {
    }


protected:
    virtual void do_play() override;


    virtual bool updates_screen() override
    {
        return false;
    }
};



class breaking_animation : public abstract_animation
{
public:
    breaking_animation(const position_t& position, int type = 0)
        : position(position)
        , type(type)
    {
    }


protected:
    virtual void do_play() override;


private:
    position_t position;
    int type;
};



} // namespace elona
