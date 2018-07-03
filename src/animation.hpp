#pragma once



namespace elona
{



extern int FIXME_dig_animation_x;
extern int FIXME_dig_animation_y;



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
    failure_to_cast_animation(int cc)
        : cc(cc)
    {
    }


protected:
    virtual void do_play() override;


private:
    int cc;
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


    bright_aura_animation(type_t type)
        : type(type)
    {
    }


protected:
    virtual void do_play() override;


private:
    type_t type;
};



class breath_animation : public abstract_animation
{
public:
    breath_animation(int element)
        : element(element)
    {
    }


protected:
    virtual void do_play() override;


private:
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
    bolt_animation(int cc, int element)
        : cc(cc)
        , element(element)
    {
    }


protected:
    virtual void do_play() override;


private:
    int cc;
    int element;
};



class throwing_object_animation : public abstract_animation
{
public:
    throwing_object_animation()
    {
    }


protected:
    virtual void do_play() override;


private:
};



class swarm_animation : public abstract_animation
{
public:
    swarm_animation(int cc)
        : cc(cc)
    {
    }


protected:
    virtual void do_play() override;


private:
    int cc;
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
    breaking_animation()
    {
    }


protected:
    virtual void do_play() override;
};



} // namespace elona
