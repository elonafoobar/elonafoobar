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



struct character;
struct item;

class failure_to_cast_animation : public abstract_animation
{
public:
    failure_to_cast_animation(const character& caster)
        : caster(caster)
    {
    }


protected:
    virtual void do_play() override;


private:
    const character& caster;
};



class bright_aura_animation : public abstract_animation
{
public:
    enum class type_t
    {
        debuff,
        offering,
        healing,
        healing_rain,
    };


    bright_aura_animation(const character& cc, type_t type)
        : cc(cc)
        , type(type)
    {
    }


protected:
    virtual void do_play() override;


private:
    const character& cc;
    type_t type;
};



class breath_animation : public abstract_animation
{
public:
    breath_animation(const character& attacker, int element)
        : attacker(attacker)
        , element(element)
    {
    }


protected:
    virtual void do_play() override;


private:
    const character& attacker;
    int element;
};



class ball_animation : public abstract_animation
{
public:
    enum class type_t
    {
        ball,
        atomic_bomb,
    };


    ball_animation(
        const position_t& position,
        int range,
        type_t type,
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
    type_t type;
    int element;
};



class bolt_animation : public abstract_animation
{
public:
    bolt_animation(const character& attacker, int element, int effect_id)
        : attacker(attacker)
        , element(element)
        , effect_id(effect_id)
    {
    }


protected:
    virtual void do_play() override;


private:
    const character& attacker;
    int element;
    int effect_id;
};



class throwing_object_animation : public abstract_animation
{
public:
    throwing_object_animation(
        const position_t& origin,
        const character& target,
        int item_chip,
        int item_color)
        : origin(origin)
        , target(target)
        , item_chip(item_chip)
        , item_color(item_color)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& origin;
    const character& target;
    int item_chip;
    int item_color;
};



class swarm_animation : public abstract_animation
{
public:
    swarm_animation(const character& target)
        : target(target)
    {
    }


protected:
    virtual void do_play() override;


private:
    const character& target;
};



class ranged_attack_animation : public abstract_animation
{
public:
    enum class type_t
    {
        magic_arrow = 0,
        distant_attack = 1,
        bow = 108,
        crossbow = 109,
        firearm = 110,
        throwing = 111,
    };


    ranged_attack_animation(
        const character& attacker,
        const character& target,
        type_t type,
        const optional<item&> fired = none)
        : attacker(attacker)
        , target(target)
        , type(type)
        , fired(fired)
    {
    }


protected:
    virtual void do_play() override;


private:
    const character& attacker;
    const character& target;
    type_t type;
    const optional<item&> fired;
};



class melee_attack_animation : public abstract_animation
{
public:
    melee_attack_animation(
        const character& target,
        int attack_skill,
        int damage_percent,
        bool is_critical)
        : target(target)
        , attack_skill(attack_skill)
        , damage_percent(damage_percent)
        , is_critical(is_critical)
    {
    }


protected:
    virtual void do_play() override;

private:
    const character& target;
    int attack_skill;
    int damage_percent;
    bool is_critical;
};



class gene_engineering_animation : public abstract_animation
{
public:
    gene_engineering_animation(const character& target)
        : target(target)
    {
    }


protected:
    virtual void do_play() override;

private:
    const character& target;
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
    breaking_animation(const position_t& position, int type)
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
