#pragma once

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


    ball_animation(type_t type)
        : type(type)
    {
    }


protected:
    virtual void do_play() override;


private:
    type_t type;
};



class bolt_animation : public abstract_animation
{
public:
    bolt_animation(const character& attacker, int element)
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



class throwing_object_animation : public abstract_animation
{
public:
    throwing_object_animation(const character& target)
        : target(target)
    {
    }


protected:
    virtual void do_play() override;


private:
    const character& target;
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
        magic_arrow,
        distant_attack,
        bow = 108,
        crossbow = 109,
        firearm = 110,
        throwing = 111,
    };


    ranged_attack_animation(type_t type)
        : type(type)
    {
    }


protected:
    virtual void do_play() override;


private:
    type_t type;
};



class melee_attack_animation : public abstract_animation
{
public:
    melee_attack_animation()
    {
    }


protected:
    virtual void do_play() override;
};



class geen_engineering_animation : public abstract_animation
{
public:
    geen_engineering_animation()
    {
    }


protected:
    virtual void do_play() override;
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
    breaking_animation(const position_t& position)
        : position(position)
    {
    }


protected:
    virtual void do_play() override;


private:
    position_t position;
};



} // namespace elona
