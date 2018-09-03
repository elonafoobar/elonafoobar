#pragma once

#include "optional.hpp"
#include "position.hpp"



namespace elona
{



class AbstractAnimation
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



class FailureToCastAnimation : public AbstractAnimation
{
public:
    FailureToCastAnimation(const position_t& caster_pos)
        : caster_pos(caster_pos)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& caster_pos;
};



class BrightAuraAnimation : public AbstractAnimation
{
public:
    enum class Type
    {
        debuff,
        offering,
        healing,
        healing_rain,
    };


    BrightAuraAnimation(const position_t& target_pos, Type type)
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



class BreathAnimation : public AbstractAnimation
{
public:
    BreathAnimation(
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



class BallAnimation : public AbstractAnimation
{
public:
    enum class Type
    {
        ball,
        atomic_bomb,
    };


    BallAnimation(
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



class BoltAnimation : public AbstractAnimation
{
public:
    BoltAnimation(
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



class ThrowingObjectAnimation : public AbstractAnimation
{
public:
    ThrowingObjectAnimation(
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



class SwarmAnimation : public AbstractAnimation
{
public:
    SwarmAnimation(const position_t& target_pos)
        : target_pos(target_pos)
    {
    }


protected:
    virtual void do_play() override;


private:
    const position_t& target_pos;
};



class RangedAttackAnimation : public AbstractAnimation
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


    RangedAttackAnimation(
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



class MeleeAttackAnimation : public AbstractAnimation
{
public:
    MeleeAttackAnimation(
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



class GeneEngineeringAnimation : public AbstractAnimation
{
public:
    GeneEngineeringAnimation(const position_t& position)
        : position(position)
    {
    }


protected:
    virtual void do_play() override;

private:
    const position_t& position;
};



class MiracleAnimation : public AbstractAnimation
{
public:
    MiracleAnimation()
    {
    }


protected:
    virtual void do_play() override;
};



class MeteorAnimation : public AbstractAnimation
{
public:
    MeteorAnimation()
    {
    }


protected:
    virtual void do_play() override;
};



class RagnarokAnimation : public AbstractAnimation
{
public:
    RagnarokAnimation()
    {
    }


protected:
    virtual void do_play() override;


    virtual bool updates_screen() override
    {
        return false;
    }
};



class BreakingAnimation : public AbstractAnimation
{
public:
    BreakingAnimation(const position_t& position, int type = 0)
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
