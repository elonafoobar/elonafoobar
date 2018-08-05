#include "db_item.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"


namespace elona
{


void set_item_info()
{
    for (const auto& data : the_item_db)
    {
        ilight(data.id) = data.light;
        ialphanameref(data.id) = data.katakana_name;
        iorgweight(data.id) = data.weight;
        ioriginalnameref(data.id) =
            lang(data.original_name_jp, data.original_name_en);
        ioriginalnameref2(data.id) = data.originalnameref2;
        ipicref(data.id) = data.image;
        irandomname(data.id) = data.has_random_name ? 1 : 0;
    }

    iknownnameref(792) = ioriginalnameref(792);
    icolref(792) = 0;
    if (jp)
    {
        iknownnameref(791) = u8"両刃の大剣"s;
    }
    else
    {
        iknownnameref(791) = u8"two-edged great sword"s;
    }
    icolref(791) = 0;
    iknownnameref(790) = ioriginalnameref(790);
    icolref(790) = 1;
    iknownnameref(789) = ioriginalnameref(789);
    icolref(789) = 1;
    iknownnameref(788) = ioriginalnameref(788);
    icolref(788) = 0;
    iknownnameref(787) = ioriginalnameref(787);
    icolref(787) = 0;
    iknownnameref(786) = ioriginalnameref(786);
    icolref(786) = 0;
    iknownnameref(785) = ioriginalnameref(785);
    icolref(785) = 0;
    iknownnameref(784) = ioriginalnameref(784);
    icolref(784) = 0;
    iknownnameref(783) = ioriginalnameref(783);
    icolref(783) = 0;
    iknownnameref(782) = ioriginalnameref(782);
    icolref(782) = 0;
    iknownnameref(781) = ioriginalnameref(781);
    icolref(781) = 0;
    iknownnameref(780) = ioriginalnameref(780);
    icolref(780) = 0;
    iknownnameref(779) = ioriginalnameref(779);
    icolref(779) = 0;
    iknownnameref(778) = ioriginalnameref(778);
    icolref(778) = 1;
    if (jp)
    {
        iknownnameref(777) = u8"神の彫像"s;
    }
    else
    {
        iknownnameref(777) = u8"celestial statue"s;
    }
    icolref(777) = 0;
    if (jp)
    {
        iknownnameref(776) = u8"神の彫像"s;
    }
    else
    {
        iknownnameref(776) = u8"celestial statue"s;
    }
    icolref(776) = 0;
    iknownnameref(775) = ioriginalnameref(775);
    icolref(775) = 0;
    iknownnameref(774) = ioriginalnameref(774);
    icolref(774) = 0;
    iknownnameref(773) = ioriginalnameref(773);
    icolref(773) = 0;
    iknownnameref(772) = ioriginalnameref(772);
    icolref(772) = 0;
    if (jp)
    {
        iknownnameref(771) = u8"青いカプセル"s;
    }
    else
    {
        iknownnameref(771) = u8"blue capsule"s;
    }
    icolref(771) = 0;
    if (jp)
    {
        iknownnameref(770) = u8"透明なポーション"s;
    }
    else
    {
        iknownnameref(770) = u8"clear liquid"s;
    }
    icolref(770) = 0;
    iknownnameref(769) = ioriginalnameref(769);
    icolref(769) = 0;
    iknownnameref(768) = ioriginalnameref(768);
    icolref(768) = 0;
    iknownnameref(767) = ioriginalnameref(767);
    icolref(767) = 0;
    iknownnameref(766) = ioriginalnameref(766);
    icolref(766) = 0;
    iknownnameref(765) = ioriginalnameref(765);
    icolref(765) = 0;
    iknownnameref(764) = ioriginalnameref(764);
    icolref(764) = 0;
    iknownnameref(763) = ioriginalnameref(763);
    icolref(763) = 1;
    iknownnameref(762) = ioriginalnameref(762);
    icolref(762) = 0;
    if (jp)
    {
        iknownnameref(761) = u8"何の変哲もないピアノ"s;
    }
    else
    {
        iknownnameref(761) = u8"nondescriptive piano"s;
    }
    icolref(761) = 12;
    if (jp)
    {
        iknownnameref(760) = u8"名工の槌"s;
    }
    else
    {
        iknownnameref(760) = u8"master hammer"s;
    }
    icolref(760) = 0;
    iknownnameref(759) = ioriginalnameref(759);
    icolref(759) = 1;
    if (jp)
    {
        iknownnameref(758) = u8"錆びた銃"s;
    }
    else
    {
        iknownnameref(758) = u8"rusted pistol"s;
    }
    icolref(758) = 7;
    if (jp)
    {
        iknownnameref(757) = u8"角の生えた兜"s;
    }
    else
    {
        iknownnameref(757) = u8"horned helmet"s;
    }
    icolref(757) = 4;
    iknownnameref(756) = ioriginalnameref(756);
    icolref(756) = 0;
    iknownnameref(755) = ioriginalnameref(755);
    icolref(755) = 0;
    iknownnameref(754) = ioriginalnameref(754);
    icolref(754) = 0;
    iknownnameref(753) = ioriginalnameref(753);
    icolref(753) = 1;
    iknownnameref(752) = ioriginalnameref(752);
    icolref(752) = 0;
    iknownnameref(751) = ioriginalnameref(751);
    icolref(751) = 0;
    iknownnameref(750) = ioriginalnameref(750);
    icolref(750) = 0;
    if (jp)
    {
        iknownnameref(749) = u8"怪しい人物像"s;
    }
    else
    {
        iknownnameref(749) = u8"fishy statue"s;
    }
    icolref(749) = 0;
    if (jp)
    {
        iknownnameref(748) = u8"見事な水晶"s;
    }
    else
    {
        iknownnameref(748) = u8"beautiful stone"s;
    }
    icolref(748) = 0;
    iknownnameref(747) = ioriginalnameref(747);
    icolref(747) = 0;
    iknownnameref(746) = ioriginalnameref(746);
    icolref(746) = 3;
    iknownnameref(745) = ioriginalnameref(745);
    icolref(745) = 3;
    iknownnameref(744) = ioriginalnameref(744);
    icolref(744) = 3;
    iknownnameref(743) = ioriginalnameref(743);
    icolref(743) = 3;
    if (jp)
    {
        iknownnameref(742) = u8"謎の紙切れ"s;
    }
    else
    {
        iknownnameref(742) = u8"strange paper"s;
    }
    icolref(742) = 0;
    if (jp)
    {
        iknownnameref(741) = u8"赤い装飾の刀"s;
    }
    else
    {
        iknownnameref(741) = u8"rutilant katana"s;
    }
    icolref(741) = 3;
    if (jp)
    {
        iknownnameref(740) = u8"美しい貝"s;
    }
    else
    {
        iknownnameref(740) = u8"beautiful shell"s;
    }
    icolref(740) = 4;
    if (jp)
    {
        iknownnameref(739) = u8"猫の尻尾"s;
    }
    else
    {
        iknownnameref(739) = u8"cat's tail"s;
    }
    icolref(739) = 0;
    iknownnameref(738) = ioriginalnameref(738);
    icolref(738) = 0;
    p = (737 + gdata_random_seed) % 6;
    iknownnameref(737) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(737) = _randcolor(p);
    p = (736 + gdata_random_seed) % 6;
    iknownnameref(736) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(736) = _randcolor(p);
    iknownnameref(735) = ioriginalnameref(735);
    icolref(735) = 0;
    iknownnameref(734) = ioriginalnameref(734);
    icolref(734) = 0;
    iknownnameref(733) = ioriginalnameref(733);
    icolref(733) = 0;
    p = (732 + gdata_random_seed) % 6;
    iknownnameref(732) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(732) = _randcolor(p);
    p = (731 + gdata_random_seed) % 6;
    iknownnameref(731) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(731) = _randcolor(p);
    if (jp)
    {
        iknownnameref(730) = u8"ぼろぼろの紙切れ"s;
    }
    else
    {
        iknownnameref(730) = u8"crumbling paper"s;
    }
    icolref(730) = 0;
    iknownnameref(729) = ioriginalnameref(729);
    icolref(729) = 0;
    if (jp)
    {
        iknownnameref(728) = u8"赤い腰当"s;
    }
    else
    {
        iknownnameref(728) = u8"red girdle"s;
    }
    icolref(728) = 3;
    if (jp)
    {
        iknownnameref(727) = u8"チクチクする盾"s;
    }
    else
    {
        iknownnameref(727) = u8"tingling shield"s;
    }
    icolref(727) = 3;
    if (jp)
    {
        iknownnameref(726) = u8"頑丈なリュート"s;
    }
    else
    {
        iknownnameref(726) = u8"tough lute"s;
    }
    icolref(726) = 6;
    if (jp)
    {
        iknownnameref(725) = u8"頑丈なピアノ"s;
    }
    else
    {
        iknownnameref(725) = u8"heavy piano"s;
    }
    icolref(725) = 5;
    if (jp)
    {
        iknownnameref(724) = u8"何かのチケット"s;
    }
    else
    {
        iknownnameref(724) = u8"some kind of ticket"s;
    }
    icolref(724) = 0;
    if (jp)
    {
        iknownnameref(723) = u8"黄色のネックレス"s;
    }
    else
    {
        iknownnameref(723) = u8"yellow necklace"s;
    }
    icolref(723) = 5;
    if (jp)
    {
        iknownnameref(722) = u8"紫のネックレス"s;
    }
    else
    {
        iknownnameref(722) = u8"purple necklace"s;
    }
    icolref(722) = 8;
    if (jp)
    {
        iknownnameref(721) = u8"女神の彫像"s;
    }
    else
    {
        iknownnameref(721) = u8"celestial statue"s;
    }
    icolref(721) = 0;
    iknownnameref(720) = ioriginalnameref(720);
    icolref(720) = 1;
    if (jp)
    {
        iknownnameref(719) = u8"粗野な剣"s;
    }
    else
    {
        iknownnameref(719) = u8"brutish sword"s;
    }
    icolref(719) = 0;
    if (jp)
    {
        iknownnameref(718) = u8"かぐわしいぱんつ"s;
    }
    else
    {
        iknownnameref(718) = u8"scentful panty"s;
    }
    icolref(718) = 3;
    if (jp)
    {
        iknownnameref(717) = u8"怪しい宝石"s;
    }
    else
    {
        iknownnameref(717) = u8"strange jewel"s;
    }
    icolref(717) = 9;
    if (jp)
    {
        iknownnameref(716) = u8"光る小石"s;
    }
    else
    {
        iknownnameref(716) = u8"shining rock"s;
    }
    icolref(716) = 0;
    if (jp)
    {
        iknownnameref(715) = u8"怪しい宝石"s;
    }
    else
    {
        iknownnameref(715) = u8"strange jewel"s;
    }
    icolref(715) = 9;
    iknownnameref(714) = ioriginalnameref(714);
    icolref(714) = 0;
    iknownnameref(713) = ioriginalnameref(713);
    icolref(713) = 0;
    iknownnameref(712) = ioriginalnameref(712);
    icolref(712) = 4;
    p = (711 + gdata_random_seed) % 6;
    iknownnameref(711) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(711) = _randcolor(p);
    p = (710 + gdata_random_seed) % 6;
    iknownnameref(710) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(710) = _randcolor(p);
    p = (709 + gdata_random_seed) % 6;
    iknownnameref(709) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(709) = _randcolor(p);
    p = (708 + gdata_random_seed) % 6;
    iknownnameref(708) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(708) = _randcolor(p);
    if (jp)
    {
        iknownnameref(707) = u8"艶やかな弦楽器"s;
    }
    else
    {
        iknownnameref(707) = u8"elegant string"s;
    }
    icolref(707) = 0;
    p = (706 + gdata_random_seed) % 6;
    iknownnameref(706) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(706) = _randcolor(p);
    if (jp)
    {
        iknownnameref(705) = u8"うす汚れたペンダント"s;
    }
    else
    {
        iknownnameref(705) = u8"dirty pendant"s;
    }
    icolref(705) = 0;
    iknownnameref(704) = ioriginalnameref(704);
    icolref(704) = 0;
    iknownnameref(703) = ioriginalnameref(703);
    icolref(703) = 0;
    if (jp)
    {
        iknownnameref(702) = u8"ふわふわな尻尾"s;
    }
    else
    {
        iknownnameref(702) = u8"fluffy tail"s;
    }
    icolref(702) = 3;
    iknownnameref(701) = ioriginalnameref(701);
    icolref(701) = 0;
    iknownnameref(700) = ioriginalnameref(700);
    icolref(700) = 0;
    if (jp)
    {
        iknownnameref(699) = u8"機械仕掛けの球"s;
    }
    else
    {
        iknownnameref(699) = u8"mechanical ball"s;
    }
    icolref(699) = 3;
    iknownnameref(698) = ioriginalnameref(698);
    icolref(698) = 0;
    p = (697 + gdata_random_seed) % 6;
    iknownnameref(697) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(697) = _randcolor(p);
    p = (696 + gdata_random_seed) % 6;
    iknownnameref(696) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(696) = _randcolor(p);
    if (jp)
    {
        iknownnameref(695) = u8"巨大な斧"s;
    }
    else
    {
        iknownnameref(695) = u8"giant axe"s;
    }
    icolref(695) = 3;
    iknownnameref(694) = ioriginalnameref(694);
    icolref(694) = 0;
    iknownnameref(693) = ioriginalnameref(693);
    icolref(693) = 0;
    iknownnameref(692) = ioriginalnameref(692);
    icolref(692) = 0;
    iknownnameref(691) = ioriginalnameref(691);
    icolref(691) = 0;
    iknownnameref(690) = ioriginalnameref(690);
    icolref(690) = 0;
    iknownnameref(689) = ioriginalnameref(689);
    icolref(689) = 0;
    iknownnameref(688) = ioriginalnameref(688);
    icolref(688) = 0;
    iknownnameref(687) = ioriginalnameref(687);
    icolref(687) = 0;
    if (jp)
    {
        iknownnameref(686) = u8"女神の彫像"s;
    }
    else
    {
        iknownnameref(686) = u8"celestial statue"s;
    }
    icolref(686) = 0;
    iknownnameref(685) = ioriginalnameref(685);
    icolref(685) = 0;
    if (jp)
    {
        iknownnameref(684) = u8"見たこともない機械"s;
    }
    else
    {
        iknownnameref(684) = u8"freaky machine"s;
    }
    icolref(684) = 0;
    if (jp)
    {
        iknownnameref(683) = u8"怪しい宝石"s;
    }
    else
    {
        iknownnameref(683) = u8"strange jewel"s;
    }
    icolref(683) = 3;
    if (jp)
    {
        iknownnameref(682) = u8"神々しい宝石"s;
    }
    else
    {
        iknownnameref(682) = u8"heavenly jewel"s;
    }
    icolref(682) = 2;
    if (jp)
    {
        iknownnameref(681) = u8"神々しい宝石"s;
    }
    else
    {
        iknownnameref(681) = u8"heavenly jewel"s;
    }
    icolref(681) = 17;
    if (jp)
    {
        iknownnameref(680) = u8"神々しい宝石"s;
    }
    else
    {
        iknownnameref(680) = u8"heavenly jewel"s;
    }
    icolref(680) = 4;
    if (jp)
    {
        iknownnameref(679) = u8"巨大な槌"s;
    }
    else
    {
        iknownnameref(679) = u8"giant hammer"s;
    }
    icolref(679) = 5;
    if (jp)
    {
        iknownnameref(678) = u8"細い短剣"s;
    }
    else
    {
        iknownnameref(678) = u8"thin dagger"s;
    }
    icolref(678) = 5;
    if (jp)
    {
        iknownnameref(677) = u8"聖なる槍"s;
    }
    else
    {
        iknownnameref(677) = u8"holy lance"s;
    }
    icolref(677) = 0;
    if (jp)
    {
        iknownnameref(676) = u8"元素の杖"s;
    }
    else
    {
        iknownnameref(676) = u8"elemental staff"s;
    }
    icolref(676) = 19;
    if (jp)
    {
        iknownnameref(675) = u8"収穫の鎌"s;
    }
    else
    {
        iknownnameref(675) = u8"harvest scythe"s;
    }
    icolref(675) = 2;
    if (jp)
    {
        iknownnameref(674) = u8"古の散弾銃"s;
    }
    else
    {
        iknownnameref(674) = u8"ancient shot gun"s;
    }
    icolref(674) = 3;
    if (jp)
    {
        iknownnameref(673) = u8"風をまとった長弓"s;
    }
    else
    {
        iknownnameref(673) = u8"bow surrounded by wind"s;
    }
    icolref(673) = 17;
    if (jp)
    {
        iknownnameref(672) = u8"謎の宝石"s;
    }
    else
    {
        iknownnameref(672) = u8"mysterious jewel"s;
    }
    icolref(672) = 0;
    if (jp)
    {
        iknownnameref(671) = u8"とても危険な爆弾"s;
    }
    else
    {
        iknownnameref(671) = u8"very dangerous bomb"s;
    }
    icolref(671) = 0;
    iknownnameref(670) = ioriginalnameref(670);
    icolref(670) = 0;
    iknownnameref(669) = ioriginalnameref(669);
    icolref(669) = 0;
    iknownnameref(668) = ioriginalnameref(668);
    icolref(668) = 0;
    iknownnameref(667) = ioriginalnameref(667);
    icolref(667) = 0;
    if (jp)
    {
        iknownnameref(666) = u8"女神の彫像"s;
    }
    else
    {
        iknownnameref(666) = u8"celestial statue"s;
    }
    icolref(666) = 0;
    if (jp)
    {
        iknownnameref(665) = u8"神の彫像"s;
    }
    else
    {
        iknownnameref(665) = u8"celestial statue"s;
    }
    icolref(665) = 0;
    p = (664 + gdata_random_seed) % 6;
    iknownnameref(664) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"ring");
    icolref(664) = 0;
    if (jp)
    {
        iknownnameref(663) = u8"動いている心臓"s;
    }
    else
    {
        iknownnameref(663) = u8"beating heart"s;
    }
    icolref(663) = 0;
    if (jp)
    {
        iknownnameref(662) = u8"見たこともない果物"s;
    }
    else
    {
        iknownnameref(662) = u8"rare fruit"s;
    }
    icolref(662) = 3;
    if (jp)
    {
        iknownnameref(661) = u8"軽やかな靴"s;
    }
    else
    {
        iknownnameref(661) = u8"light shoes"s;
    }
    icolref(661) = 3;
    p = (660 + gdata_random_seed) % 6;
    iknownnameref(660) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(660) = _randcolor(p);
    iknownnameref(659) = ioriginalnameref(659);
    icolref(659) = 1;
    iknownnameref(658) = ioriginalnameref(658);
    icolref(658) = 0;
    iknownnameref(657) = ioriginalnameref(657);
    icolref(657) = 0;
    iknownnameref(656) = ioriginalnameref(656);
    icolref(656) = 0;
    if (jp)
    {
        iknownnameref(655) = u8"不思議なチーズ"s;
    }
    else
    {
        iknownnameref(655) = u8"mysterious cheese"s;
    }
    icolref(655) = 4;
    iknownnameref(654) = ioriginalnameref(654);
    icolref(654) = 1;
    iknownnameref(653) = ioriginalnameref(653);
    icolref(653) = 0;
    iknownnameref(652) = ioriginalnameref(652);
    icolref(652) = 0;
    iknownnameref(651) = ioriginalnameref(651);
    icolref(651) = 0;
    iknownnameref(650) = ioriginalnameref(650);
    icolref(650) = 1;
    iknownnameref(649) = ioriginalnameref(649);
    icolref(649) = 1;
    iknownnameref(648) = ioriginalnameref(648);
    icolref(648) = 1;
    iknownnameref(647) = ioriginalnameref(647);
    icolref(647) = 0;
    iknownnameref(646) = ioriginalnameref(646);
    icolref(646) = 0;
    iknownnameref(645) = ioriginalnameref(645);
    icolref(645) = 0;
    iknownnameref(644) = ioriginalnameref(644);
    icolref(644) = 0;
    iknownnameref(643) = ioriginalnameref(643);
    icolref(643) = 0;
    iknownnameref(642) = ioriginalnameref(642);
    icolref(642) = 0;
    if (jp)
    {
        iknownnameref(641) = u8"冷たい仕掛け箱"s;
    }
    else
    {
        iknownnameref(641) = u8"chilly box"s;
    }
    icolref(641) = 0;
    iknownnameref(640) = ioriginalnameref(640);
    icolref(640) = 0;
    if (jp)
    {
        iknownnameref(639) = u8"不思議なリンゴ"s;
    }
    else
    {
        iknownnameref(639) = u8"mysterious apple"s;
    }
    icolref(639) = 17;
    p = (638 + gdata_random_seed) % 6;
    iknownnameref(638) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(638) = _randcolor(p);
    if (jp)
    {
        iknownnameref(637) = u8"透き通った鍵"s;
    }
    else
    {
        iknownnameref(637) = u8"white key"s;
    }
    icolref(637) = 0;
    iknownnameref(636) = ioriginalnameref(636);
    icolref(636) = 0;
    iknownnameref(635) = ioriginalnameref(635);
    icolref(635) = 0;
    iknownnameref(634) = ioriginalnameref(634);
    icolref(634) = 0;
    iknownnameref(633) = ioriginalnameref(633);
    icolref(633) = 0;
    p = (632 + gdata_random_seed) % 6;
    iknownnameref(632) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(632) = _randcolor(p);
    iknownnameref(631) = ioriginalnameref(631);
    icolref(631) = 0;
    iknownnameref(630) = ioriginalnameref(630);
    icolref(630) = 0;
    iknownnameref(629) = ioriginalnameref(629);
    icolref(629) = 0;
    p = (628 + gdata_random_seed) % 6;
    iknownnameref(628) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(628) = _randcolor(p);
    if (jp)
    {
        iknownnameref(627) = u8"眩しい兜"s;
    }
    else
    {
        iknownnameref(627) = u8"shining helm"s;
    }
    icolref(627) = 5;
    p = (626 + gdata_random_seed) % 6;
    iknownnameref(626) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(626) = _randcolor(p);
    if (jp)
    {
        iknownnameref(625) = u8"異国の門"s;
    }
    else
    {
        iknownnameref(625) = u8"foreign gate"s;
    }
    icolref(625) = 0;
    p = (624 + gdata_random_seed) % 6;
    iknownnameref(624) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(624) = _randcolor(p);
    p = (623 + gdata_random_seed) % 6;
    iknownnameref(623) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(623) = _randcolor(p);
    if (jp)
    {
        iknownnameref(622) = u8"銀貨"s;
    }
    else
    {
        iknownnameref(622) = u8"silver coin"s;
    }
    icolref(622) = 0;
    if (jp)
    {
        iknownnameref(621) = u8"ぼろぼろの紙切れ"s;
    }
    else
    {
        iknownnameref(621) = u8"crumbling paper"s;
    }
    icolref(621) = 0;
    if (jp)
    {
        iknownnameref(620) = u8"透明なポーション"s;
    }
    else
    {
        iknownnameref(620) = u8"clear liquid"s;
    }
    icolref(620) = 0;
    iknownnameref(619) = ioriginalnameref(619);
    icolref(619) = 0;
    iknownnameref(618) = ioriginalnameref(618);
    icolref(618) = 0;
    iknownnameref(617) = ioriginalnameref(617);
    icolref(617) = 0;
    if (jp)
    {
        iknownnameref(616) = u8"納税箱"s;
    }
    else
    {
        iknownnameref(616) = u8"tax box"s;
    }
    icolref(616) = 0;
    if (jp)
    {
        iknownnameref(615) = u8"いやな紙切れ"s;
    }
    else
    {
        iknownnameref(615) = u8"lousy paper"s;
    }
    icolref(615) = 0;
    iknownnameref(614) = ioriginalnameref(614);
    icolref(614) = 0;
    iknownnameref(613) = ioriginalnameref(613);
    icolref(613) = 0;
    iknownnameref(612) = ioriginalnameref(612);
    icolref(612) = 0;
    iknownnameref(611) = ioriginalnameref(611);
    icolref(611) = 0;
    iknownnameref(610) = ioriginalnameref(610);
    icolref(610) = 0;
    iknownnameref(609) = ioriginalnameref(609);
    icolref(609) = 0;
    iknownnameref(608) = ioriginalnameref(608);
    icolref(608) = 0;
    iknownnameref(607) = ioriginalnameref(607);
    icolref(607) = 0;
    iknownnameref(606) = ioriginalnameref(606);
    icolref(606) = 0;
    iknownnameref(605) = ioriginalnameref(605);
    icolref(605) = 0;
    iknownnameref(604) = ioriginalnameref(604);
    icolref(604) = 0;
    if (jp)
    {
        iknownnameref(603) = u8"威圧感のある椅子"s;
    }
    else
    {
        iknownnameref(603) = u8"glory chair"s;
    }
    icolref(603) = 0;
    iknownnameref(602) = ioriginalnameref(602);
    icolref(602) = 0;
    if (jp)
    {
        iknownnameref(601) = u8"空き瓶"s;
    }
    else
    {
        iknownnameref(601) = u8"empty bottle"s;
    }
    icolref(601) = 0;
    if (jp)
    {
        iknownnameref(600) = u8"足枷"s;
    }
    else
    {
        iknownnameref(600) = u8"shakle"s;
    }
    icolref(600) = 0;
    iknownnameref(599) = ioriginalnameref(599);
    icolref(599) = 0;
    iknownnameref(598) = ioriginalnameref(598);
    icolref(598) = 0;
    iknownnameref(597) = ioriginalnameref(597);
    icolref(597) = 0;
    iknownnameref(596) = ioriginalnameref(596);
    icolref(596) = 0;
    iknownnameref(595) = ioriginalnameref(595);
    icolref(595) = 0;
    iknownnameref(594) = ioriginalnameref(594);
    icolref(594) = 0;
    iknownnameref(593) = ioriginalnameref(593);
    icolref(593) = 0;
    iknownnameref(592) = ioriginalnameref(592);
    icolref(592) = 0;
    iknownnameref(591) = ioriginalnameref(591);
    icolref(591) = 0;
    iknownnameref(590) = ioriginalnameref(590);
    icolref(590) = 1;
    iknownnameref(589) = ioriginalnameref(589);
    icolref(589) = 0;
    iknownnameref(588) = ioriginalnameref(588);
    icolref(588) = 0;
    iknownnameref(587) = ioriginalnameref(587);
    icolref(587) = 0;
    iknownnameref(586) = ioriginalnameref(586);
    icolref(586) = 0;
    iknownnameref(585) = ioriginalnameref(585);
    icolref(585) = 0;
    iknownnameref(584) = ioriginalnameref(584);
    icolref(584) = 1;
    iknownnameref(583) = ioriginalnameref(583);
    icolref(583) = 0;
    p = (582 + gdata_random_seed) % 6;
    iknownnameref(582) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(582) = _randcolor(p);
    p = (581 + gdata_random_seed) % 6;
    iknownnameref(581) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(581) = _randcolor(p);
    iknownnameref(580) = ioriginalnameref(580);
    icolref(580) = 0;
    iknownnameref(579) = ioriginalnameref(579);
    icolref(579) = 0;
    iknownnameref(578) = ioriginalnameref(578);
    icolref(578) = 0;
    p = (577 + gdata_random_seed) % 6;
    iknownnameref(577) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(577) = _randcolor(p);
    iknownnameref(576) = ioriginalnameref(576);
    icolref(576) = 3;
    iknownnameref(575) = ioriginalnameref(575);
    icolref(575) = 0;
    iknownnameref(574) = ioriginalnameref(574);
    icolref(574) = 0;
    iknownnameref(573) = ioriginalnameref(573);
    icolref(573) = 0;
    iknownnameref(572) = ioriginalnameref(572);
    icolref(572) = 11;
    iknownnameref(571) = ioriginalnameref(571);
    icolref(571) = 0;
    p = (570 + gdata_random_seed) % 6;
    iknownnameref(570) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(570) = _randcolor(p);
    p = (569 + gdata_random_seed) % 6;
    iknownnameref(569) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(569) = _randcolor(p);
    iknownnameref(568) = ioriginalnameref(568);
    icolref(568) = 4;
    iknownnameref(567) = ioriginalnameref(567);
    icolref(567) = 3;
    p = (566 + gdata_random_seed) % 6;
    iknownnameref(566) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(566) = _randcolor(p);
    p = (565 + gdata_random_seed) % 6;
    iknownnameref(565) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(565) = _randcolor(p);
    p = (564 + gdata_random_seed) % 6;
    iknownnameref(564) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(564) = _randcolor(p);
    if (jp)
    {
        iknownnameref(563) = u8"本"s;
    }
    else
    {
        iknownnameref(563) = u8"book"s;
    }
    icolref(563) = 0;
    iknownnameref(562) = ioriginalnameref(562);
    icolref(562) = 0;
    iknownnameref(561) = ioriginalnameref(561);
    icolref(561) = 0;
    if (jp)
    {
        iknownnameref(560) = u8"納入箱"s;
    }
    else
    {
        iknownnameref(560) = u8"delivery chest"s;
    }
    icolref(560) = 0;
    p = (559 + gdata_random_seed) % 6;
    iknownnameref(559) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(559) = _randcolor(p);
    p = (558 + gdata_random_seed) % 6;
    iknownnameref(558) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"ring");
    icolref(558) = 0;
    iknownnameref(557) = ioriginalnameref(557);
    icolref(557) = 0;
    iknownnameref(556) = ioriginalnameref(556);
    icolref(556) = 0;
    iknownnameref(555) = ioriginalnameref(555);
    icolref(555) = 0;
    iknownnameref(554) = ioriginalnameref(554);
    icolref(554) = 9;
    iknownnameref(553) = ioriginalnameref(553);
    icolref(553) = 8;
    iknownnameref(552) = ioriginalnameref(552);
    icolref(552) = 0;
    p = (551 + gdata_random_seed) % 6;
    iknownnameref(551) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(551) = _randcolor(p);
    p = (550 + gdata_random_seed) % 6;
    iknownnameref(550) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(550) = _randcolor(p);
    p = (549 + gdata_random_seed) % 6;
    iknownnameref(549) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(549) = _randcolor(p);
    p = (548 + gdata_random_seed) % 6;
    iknownnameref(548) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(548) = _randcolor(p);
    iknownnameref(547) = ioriginalnameref(547);
    icolref(547) = 0;
    p = (546 + gdata_random_seed) % 6;
    iknownnameref(546) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(546) = _randcolor(p);
    p = (545 + gdata_random_seed) % 6;
    iknownnameref(545) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(545) = _randcolor(p);
    iknownnameref(544) = ioriginalnameref(544);
    icolref(544) = 1;
    iknownnameref(543) = ioriginalnameref(543);
    icolref(543) = 16;
    iknownnameref(542) = ioriginalnameref(542);
    icolref(542) = 17;
    iknownnameref(541) = ioriginalnameref(541);
    icolref(541) = 0;
    iknownnameref(540) = ioriginalnameref(540);
    icolref(540) = 0;
    iknownnameref(539) = ioriginalnameref(539);
    icolref(539) = 0;
    iknownnameref(538) = ioriginalnameref(538);
    icolref(538) = 0;
    iknownnameref(537) = ioriginalnameref(537);
    icolref(537) = 0;
    iknownnameref(536) = ioriginalnameref(536);
    icolref(536) = 0;
    iknownnameref(535) = ioriginalnameref(535);
    icolref(535) = 0;
    iknownnameref(534) = ioriginalnameref(534);
    icolref(534) = 0;
    iknownnameref(533) = ioriginalnameref(533);
    icolref(533) = 0;
    iknownnameref(532) = ioriginalnameref(532);
    icolref(532) = 0;
    iknownnameref(531) = ioriginalnameref(531);
    icolref(531) = 0;
    iknownnameref(530) = ioriginalnameref(530);
    icolref(530) = 0;
    iknownnameref(529) = ioriginalnameref(529);
    icolref(529) = 0;
    iknownnameref(528) = ioriginalnameref(528);
    icolref(528) = 0;
    iknownnameref(527) = ioriginalnameref(527);
    icolref(527) = 0;
    iknownnameref(526) = ioriginalnameref(526);
    icolref(526) = 0;
    iknownnameref(525) = ioriginalnameref(525);
    icolref(525) = 0;
    iknownnameref(524) = ioriginalnameref(524);
    icolref(524) = 0;
    iknownnameref(523) = ioriginalnameref(523);
    icolref(523) = 0;
    iknownnameref(522) = ioriginalnameref(522);
    icolref(522) = 3;
    iknownnameref(521) = ioriginalnameref(521);
    icolref(521) = 5;
    iknownnameref(520) = ioriginalnameref(520);
    icolref(520) = 0;
    p = (519 + gdata_random_seed) % 6;
    iknownnameref(519) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(519) = _randcolor(p);
    p = (518 + gdata_random_seed) % 6;
    iknownnameref(518) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(518) = _randcolor(p);
    p = (517 + gdata_random_seed) % 6;
    iknownnameref(517) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(517) = _randcolor(p);
    if (jp)
    {
        iknownnameref(516) = u8"透明なポーション"s;
    }
    else
    {
        iknownnameref(516) = u8"clear liquid"s;
    }
    icolref(516) = 0;
    p = (515 + gdata_random_seed) % 6;
    iknownnameref(515) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(515) = _randcolor(p);
    if (jp)
    {
        iknownnameref(514) = u8"虐殺の銃"s;
    }
    else
    {
        iknownnameref(514) = u8"gun of genocide"s;
    }
    icolref(514) = 0;
    iknownnameref(513) = ioriginalnameref(513);
    icolref(513) = 0;
    iknownnameref(512) = ioriginalnameref(512);
    icolref(512) = 0;
    iknownnameref(511) = ioriginalnameref(511);
    icolref(511) = 0;
    iknownnameref(510) = ioriginalnameref(510);
    icolref(510) = 0;
    p = (509 + gdata_random_seed) % 6;
    iknownnameref(509) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(509) = _randcolor(p);
    p = (508 + gdata_random_seed) % 6;
    iknownnameref(508) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(508) = _randcolor(p);
    p = (507 + gdata_random_seed) % 6;
    iknownnameref(507) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(507) = _randcolor(p);
    p = (506 + gdata_random_seed) % 6;
    iknownnameref(506) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(506) = _randcolor(p);
    p = (505 + gdata_random_seed) % 6;
    iknownnameref(505) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(505) = _randcolor(p);
    iknownnameref(504) = ioriginalnameref(504);
    icolref(504) = 0;
    iknownnameref(503) = ioriginalnameref(503);
    icolref(503) = 0;
    p = (502 + gdata_random_seed) % 6;
    iknownnameref(502) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(502) = _randcolor(p);
    p = (501 + gdata_random_seed) % 6;
    iknownnameref(501) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(501) = _randcolor(p);
    p = (500 + gdata_random_seed) % 6;
    iknownnameref(500) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(500) = _randcolor(p);
    iknownnameref(499) = ioriginalnameref(499);
    icolref(499) = 0;
    iknownnameref(498) = ioriginalnameref(498);
    icolref(498) = 0;
    iknownnameref(497) = ioriginalnameref(497);
    icolref(497) = 0;
    iknownnameref(496) = ioriginalnameref(496);
    icolref(496) = 0;
    iknownnameref(495) = ioriginalnameref(495);
    icolref(495) = 0;
    iknownnameref(494) = ioriginalnameref(494);
    icolref(494) = 0;
    iknownnameref(493) = ioriginalnameref(493);
    icolref(493) = 0;
    iknownnameref(492) = ioriginalnameref(492);
    icolref(492) = 0;
    iknownnameref(491) = ioriginalnameref(491);
    icolref(491) = 0;
    iknownnameref(490) = ioriginalnameref(490);
    icolref(490) = 0;
    iknownnameref(489) = ioriginalnameref(489);
    icolref(489) = 0;
    iknownnameref(488) = ioriginalnameref(488);
    icolref(488) = 0;
    iknownnameref(487) = ioriginalnameref(487);
    icolref(487) = 0;
    iknownnameref(486) = ioriginalnameref(486);
    icolref(486) = 0;
    p = (485 + gdata_random_seed) % 6;
    iknownnameref(485) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(485) = _randcolor(p);
    p = (484 + gdata_random_seed) % 6;
    iknownnameref(484) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(484) = _randcolor(p);
    iknownnameref(483) = ioriginalnameref(483);
    icolref(483) = 0;
    iknownnameref(482) = ioriginalnameref(482);
    icolref(482) = 0;
    p = (481 + gdata_random_seed) % 6;
    iknownnameref(481) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(481) = _randcolor(p);
    p = (480 + gdata_random_seed) % 6;
    iknownnameref(480) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(480) = _randcolor(p);
    p = (479 + gdata_random_seed) % 6;
    iknownnameref(479) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(479) = _randcolor(p);
    iknownnameref(478) = ioriginalnameref(478);
    icolref(478) = 0;
    p = (477 + gdata_random_seed) % 6;
    iknownnameref(477) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"ring");
    icolref(477) = 0;
    p = (476 + gdata_random_seed) % 6;
    iknownnameref(476) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"ring");
    icolref(476) = 0;
    p = (475 + gdata_random_seed) % 6;
    iknownnameref(475) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"ring");
    icolref(475) = 0;
    p = (474 + gdata_random_seed) % 6;
    iknownnameref(474) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"ring");
    icolref(474) = 0;
    p = (473 + gdata_random_seed) % 6;
    iknownnameref(473) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"amulet");
    icolref(473) = 0;
    p = (472 + gdata_random_seed) % 6;
    iknownnameref(472) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"amulet");
    icolref(472) = 0;
    p = (471 + gdata_random_seed) % 6;
    iknownnameref(471) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"amulet");
    icolref(471) = 0;
    p = (470 + gdata_random_seed) % 6;
    iknownnameref(470) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"amulet");
    icolref(470) = 0;
    p = (469 + gdata_random_seed) % 6;
    iknownnameref(469) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"amulet");
    icolref(469) = 0;
    p = (468 + gdata_random_seed) % 6;
    iknownnameref(468) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"amulet");
    icolref(468) = 0;
    iknownnameref(467) = ioriginalnameref(467);
    icolref(467) = 0;
    iknownnameref(466) = ioriginalnameref(466);
    icolref(466) = 0;
    iknownnameref(465) = ioriginalnameref(465);
    icolref(465) = 0;
    iknownnameref(464) = ioriginalnameref(464);
    icolref(464) = 0;
    iknownnameref(463) = ioriginalnameref(463);
    icolref(463) = 0;
    iknownnameref(462) = ioriginalnameref(462);
    icolref(462) = 0;
    iknownnameref(461) = ioriginalnameref(461);
    icolref(461) = 0;
    iknownnameref(460) = ioriginalnameref(460);
    icolref(460) = 0;
    iknownnameref(459) = ioriginalnameref(459);
    icolref(459) = 0;
    iknownnameref(458) = ioriginalnameref(458);
    icolref(458) = 0;
    iknownnameref(457) = ioriginalnameref(457);
    icolref(457) = 0;
    iknownnameref(456) = ioriginalnameref(456);
    icolref(456) = 0;
    iknownnameref(455) = ioriginalnameref(455);
    icolref(455) = 0;
    iknownnameref(454) = ioriginalnameref(454);
    icolref(454) = 0;
    iknownnameref(453) = ioriginalnameref(453);
    icolref(453) = 0;
    iknownnameref(452) = ioriginalnameref(452);
    icolref(452) = 0;
    iknownnameref(451) = ioriginalnameref(451);
    icolref(451) = 0;
    iknownnameref(450) = ioriginalnameref(450);
    icolref(450) = 0;
    iknownnameref(449) = ioriginalnameref(449);
    icolref(449) = 0;
    iknownnameref(448) = ioriginalnameref(448);
    icolref(448) = 0;
    iknownnameref(447) = ioriginalnameref(447);
    icolref(447) = 0;
    iknownnameref(446) = ioriginalnameref(446);
    icolref(446) = 0;
    iknownnameref(445) = ioriginalnameref(445);
    icolref(445) = 0;
    iknownnameref(444) = ioriginalnameref(444);
    icolref(444) = 0;
    iknownnameref(443) = ioriginalnameref(443);
    icolref(443) = 0;
    iknownnameref(442) = ioriginalnameref(442);
    icolref(442) = 0;
    iknownnameref(441) = ioriginalnameref(441);
    icolref(441) = 0;
    iknownnameref(440) = ioriginalnameref(440);
    icolref(440) = 0;
    iknownnameref(439) = ioriginalnameref(439);
    icolref(439) = 0;
    iknownnameref(438) = ioriginalnameref(438);
    icolref(438) = 0;
    iknownnameref(437) = ioriginalnameref(437);
    icolref(437) = 0;
    iknownnameref(436) = ioriginalnameref(436);
    icolref(436) = 0;
    iknownnameref(435) = ioriginalnameref(435);
    icolref(435) = 0;
    p = (434 + gdata_random_seed) % 6;
    iknownnameref(434) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(434) = _randcolor(p);
    p = (433 + gdata_random_seed) % 6;
    iknownnameref(433) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(433) = _randcolor(p);
    p = (432 + gdata_random_seed) % 6;
    iknownnameref(432) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(432) = _randcolor(p);
    p = (431 + gdata_random_seed) % 6;
    iknownnameref(431) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(431) = _randcolor(p);
    p = (430 + gdata_random_seed) % 6;
    iknownnameref(430) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(430) = _randcolor(p);
    p = (429 + gdata_random_seed) % 6;
    iknownnameref(429) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(429) = _randcolor(p);
    iknownnameref(428) = ioriginalnameref(428);
    icolref(428) = 0;
    iknownnameref(427) = ioriginalnameref(427);
    icolref(427) = 0;
    iknownnameref(426) = ioriginalnameref(426);
    icolref(426) = 0;
    iknownnameref(425) = ioriginalnameref(425);
    icolref(425) = 0;
    iknownnameref(424) = ioriginalnameref(424);
    icolref(424) = 0;
    iknownnameref(423) = ioriginalnameref(423);
    icolref(423) = 0;
    iknownnameref(422) = ioriginalnameref(422);
    icolref(422) = 0;
    iknownnameref(421) = ioriginalnameref(421);
    icolref(421) = 5;
    iknownnameref(420) = ioriginalnameref(420);
    icolref(420) = 1;
    iknownnameref(419) = ioriginalnameref(419);
    icolref(419) = 4;
    iknownnameref(418) = ioriginalnameref(418);
    icolref(418) = 6;
    iknownnameref(417) = ioriginalnameref(417);
    icolref(417) = 2;
    iknownnameref(416) = ioriginalnameref(416);
    icolref(416) = 0;
    iknownnameref(415) = ioriginalnameref(415);
    icolref(415) = 0;
    iknownnameref(414) = ioriginalnameref(414);
    icolref(414) = 0;
    iknownnameref(413) = ioriginalnameref(413);
    icolref(413) = 0;
    p = (412 + gdata_random_seed) % 6;
    iknownnameref(412) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(412) = _randcolor(p);
    p = (411 + gdata_random_seed) % 6;
    iknownnameref(411) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(411) = _randcolor(p);
    p = (410 + gdata_random_seed) % 6;
    iknownnameref(410) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(410) = _randcolor(p);
    iknownnameref(409) = ioriginalnameref(409);
    icolref(409) = 0;
    iknownnameref(408) = ioriginalnameref(408);
    icolref(408) = 0;
    iknownnameref(407) = ioriginalnameref(407);
    icolref(407) = 0;
    iknownnameref(406) = ioriginalnameref(406);
    icolref(406) = 0;
    iknownnameref(405) = ioriginalnameref(405);
    icolref(405) = 0;
    iknownnameref(404) = ioriginalnameref(404);
    icolref(404) = 0;
    iknownnameref(403) = ioriginalnameref(403);
    icolref(403) = 0;
    iknownnameref(402) = ioriginalnameref(402);
    icolref(402) = 0;
    iknownnameref(401) = ioriginalnameref(401);
    icolref(401) = 0;
    iknownnameref(400) = ioriginalnameref(400);
    icolref(400) = 0;
    iknownnameref(399) = ioriginalnameref(399);
    icolref(399) = 0;
    p = (398 + gdata_random_seed) % 6;
    iknownnameref(398) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(398) = _randcolor(p);
    p = (397 + gdata_random_seed) % 6;
    iknownnameref(397) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(397) = _randcolor(p);
    p = (396 + gdata_random_seed) % 6;
    iknownnameref(396) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(396) = _randcolor(p);
    p = (395 + gdata_random_seed) % 6;
    iknownnameref(395) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(395) = _randcolor(p);
    iknownnameref(394) = ioriginalnameref(394);
    icolref(394) = 0;
    iknownnameref(393) = ioriginalnameref(393);
    icolref(393) = 1;
    if (jp)
    {
        iknownnameref(392) = u8"透明なポーション"s;
    }
    else
    {
        iknownnameref(392) = u8"clear liquid"s;
    }
    icolref(392) = 0;
    p = (391 + gdata_random_seed) % 6;
    iknownnameref(391) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(391) = _randcolor(p);
    p = (390 + gdata_random_seed) % 6;
    iknownnameref(390) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(390) = _randcolor(p);
    p = (389 + gdata_random_seed) % 6;
    iknownnameref(389) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(389) = _randcolor(p);
    p = (388 + gdata_random_seed) % 6;
    iknownnameref(388) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(388) = _randcolor(p);
    p = (387 + gdata_random_seed) % 6;
    iknownnameref(387) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(387) = _randcolor(p);
    p = (386 + gdata_random_seed) % 6;
    iknownnameref(386) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(386) = _randcolor(p);
    p = (385 + gdata_random_seed) % 6;
    iknownnameref(385) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(385) = _randcolor(p);
    p = (384 + gdata_random_seed) % 6;
    iknownnameref(384) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(384) = _randcolor(p);
    p = (383 + gdata_random_seed) % 6;
    iknownnameref(383) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(383) = _randcolor(p);
    p = (382 + gdata_random_seed) % 6;
    iknownnameref(382) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(382) = _randcolor(p);
    p = (381 + gdata_random_seed) % 6;
    iknownnameref(381) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(381) = _randcolor(p);
    p = (380 + gdata_random_seed) % 6;
    iknownnameref(380) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(380) = _randcolor(p);
    p = (379 + gdata_random_seed) % 6;
    iknownnameref(379) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(379) = _randcolor(p);
    p = (378 + gdata_random_seed) % 6;
    iknownnameref(378) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(378) = _randcolor(p);
    p = (377 + gdata_random_seed) % 6;
    iknownnameref(377) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(377) = _randcolor(p);
    p = (376 + gdata_random_seed) % 6;
    iknownnameref(376) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(376) = _randcolor(p);
    p = (375 + gdata_random_seed) % 6;
    iknownnameref(375) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(375) = _randcolor(p);
    p = (374 + gdata_random_seed) % 6;
    iknownnameref(374) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(374) = _randcolor(p);
    p = (373 + gdata_random_seed) % 6;
    iknownnameref(373) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(373) = _randcolor(p);
    p = (372 + gdata_random_seed) % 6;
    iknownnameref(372) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(372) = _randcolor(p);
    p = (371 + gdata_random_seed) % 6;
    iknownnameref(371) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(371) = _randcolor(p);
    p = (370 + gdata_random_seed) % 6;
    iknownnameref(370) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(370) = _randcolor(p);
    p = (369 + gdata_random_seed) % 6;
    iknownnameref(369) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(369) = _randcolor(p);
    p = (368 + gdata_random_seed) % 6;
    iknownnameref(368) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(368) = _randcolor(p);
    p = (367 + gdata_random_seed) % 6;
    iknownnameref(367) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(367) = _randcolor(p);
    p = (366 + gdata_random_seed) % 6;
    iknownnameref(366) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(366) = _randcolor(p);
    p = (365 + gdata_random_seed) % 6;
    iknownnameref(365) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(365) = _randcolor(p);
    p = (364 + gdata_random_seed) % 6;
    iknownnameref(364) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(364) = _randcolor(p);
    p = (363 + gdata_random_seed) % 6;
    iknownnameref(363) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(363) = _randcolor(p);
    p = (362 + gdata_random_seed) % 6;
    iknownnameref(362) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(362) = _randcolor(p);
    iknownnameref(361) = ioriginalnameref(361);
    icolref(361) = 0;
    if (jp)
    {
        iknownnameref(360) = u8"アクアマリンの指輪"s;
    }
    else
    {
        iknownnameref(360) = u8"blue ring"s;
    }
    icolref(360) = 0;
    if (jp)
    {
        iknownnameref(359) = u8"地獄の槍斧"s;
    }
    else
    {
        iknownnameref(359) = u8"cursed halberd"s;
    }
    icolref(359) = 3;
    if (jp)
    {
        iknownnameref(358) = u8"呻く杖"s;
    }
    else
    {
        iknownnameref(358) = u8"shivering staff"s;
    }
    icolref(358) = 0;
    if (jp)
    {
        iknownnameref(357) = u8"鋼鉄の指輪"s;
    }
    else
    {
        iknownnameref(357) = u8"steel ring"s;
    }
    icolref(357) = 0;
    if (jp)
    {
        iknownnameref(356) = u8"血の滲むメイス"s;
    }
    else
    {
        iknownnameref(356) = u8"bloody mace"s;
    }
    icolref(356) = 3;
    if (jp)
    {
        iknownnameref(355) = u8"燃える篭手"s;
    }
    else
    {
        iknownnameref(355) = u8"burning gloves"s;
    }
    icolref(355) = 3;
    iknownnameref(354) = ioriginalnameref(354);
    icolref(354) = 0;
    iknownnameref(353) = ioriginalnameref(353);
    icolref(353) = 0;
    iknownnameref(352) = ioriginalnameref(352);
    icolref(352) = 0;
    iknownnameref(351) = ioriginalnameref(351);
    icolref(351) = 0;
    iknownnameref(350) = ioriginalnameref(350);
    icolref(350) = 0;
    iknownnameref(349) = ioriginalnameref(349);
    icolref(349) = 0;
    iknownnameref(348) = ioriginalnameref(348);
    icolref(348) = 0;
    iknownnameref(347) = ioriginalnameref(347);
    icolref(347) = 0;
    iknownnameref(346) = ioriginalnameref(346);
    icolref(346) = 0;
    iknownnameref(345) = ioriginalnameref(345);
    icolref(345) = 0;
    iknownnameref(344) = ioriginalnameref(344);
    icolref(344) = 2;
    iknownnameref(343) = ioriginalnameref(343);
    icolref(343) = 0;
    iknownnameref(342) = ioriginalnameref(342);
    icolref(342) = 0;
    iknownnameref(341) = ioriginalnameref(341);
    icolref(341) = 0;
    iknownnameref(340) = ioriginalnameref(340);
    icolref(340) = 0;
    iknownnameref(339) = ioriginalnameref(339);
    icolref(339) = 0;
    iknownnameref(338) = ioriginalnameref(338);
    icolref(338) = 0;
    iknownnameref(337) = ioriginalnameref(337);
    icolref(337) = 0;
    iknownnameref(336) = ioriginalnameref(336);
    icolref(336) = 0;
    iknownnameref(335) = ioriginalnameref(335);
    icolref(335) = 0;
    iknownnameref(334) = ioriginalnameref(334);
    icolref(334) = 0;
    iknownnameref(333) = ioriginalnameref(333);
    icolref(333) = 0;
    iknownnameref(332) = ioriginalnameref(332);
    icolref(332) = 0;
    iknownnameref(331) = ioriginalnameref(331);
    icolref(331) = 0;
    iknownnameref(330) = ioriginalnameref(330);
    icolref(330) = 0;
    iknownnameref(329) = ioriginalnameref(329);
    icolref(329) = 0;
    iknownnameref(328) = ioriginalnameref(328);
    icolref(328) = 0;
    iknownnameref(327) = ioriginalnameref(327);
    icolref(327) = 0;
    iknownnameref(326) = ioriginalnameref(326);
    icolref(326) = 0;
    iknownnameref(325) = ioriginalnameref(325);
    icolref(325) = 0;
    iknownnameref(324) = ioriginalnameref(324);
    icolref(324) = 0;
    iknownnameref(323) = ioriginalnameref(323);
    icolref(323) = 0;
    iknownnameref(322) = ioriginalnameref(322);
    icolref(322) = 0;
    iknownnameref(321) = ioriginalnameref(321);
    icolref(321) = 0;
    iknownnameref(320) = ioriginalnameref(320);
    icolref(320) = 0;
    iknownnameref(319) = ioriginalnameref(319);
    icolref(319) = 0;
    iknownnameref(318) = ioriginalnameref(318);
    icolref(318) = 0;
    iknownnameref(317) = ioriginalnameref(317);
    icolref(317) = 0;
    iknownnameref(316) = ioriginalnameref(316);
    icolref(316) = 0;
    iknownnameref(315) = ioriginalnameref(315);
    icolref(315) = 0;
    iknownnameref(314) = ioriginalnameref(314);
    icolref(314) = 0;
    iknownnameref(313) = ioriginalnameref(313);
    icolref(313) = 0;
    iknownnameref(312) = ioriginalnameref(312);
    icolref(312) = 0;
    iknownnameref(311) = ioriginalnameref(311);
    icolref(311) = 0;
    iknownnameref(310) = ioriginalnameref(310);
    icolref(310) = 0;
    iknownnameref(309) = ioriginalnameref(309);
    icolref(309) = 0;
    iknownnameref(308) = ioriginalnameref(308);
    icolref(308) = 0;
    iknownnameref(307) = ioriginalnameref(307);
    icolref(307) = 0;
    iknownnameref(306) = ioriginalnameref(306);
    icolref(306) = 0;
    iknownnameref(305) = ioriginalnameref(305);
    icolref(305) = 0;
    iknownnameref(304) = ioriginalnameref(304);
    icolref(304) = 0;
    iknownnameref(303) = ioriginalnameref(303);
    icolref(303) = 0;
    iknownnameref(302) = ioriginalnameref(302);
    icolref(302) = 0;
    iknownnameref(301) = ioriginalnameref(301);
    icolref(301) = 0;
    iknownnameref(300) = ioriginalnameref(300);
    icolref(300) = 0;
    iknownnameref(299) = ioriginalnameref(299);
    icolref(299) = 0;
    iknownnameref(298) = ioriginalnameref(298);
    icolref(298) = 0;
    iknownnameref(297) = ioriginalnameref(297);
    icolref(297) = 0;
    iknownnameref(296) = ioriginalnameref(296);
    icolref(296) = 0;
    iknownnameref(295) = ioriginalnameref(295);
    icolref(295) = 0;
    iknownnameref(294) = ioriginalnameref(294);
    icolref(294) = 0;
    iknownnameref(293) = ioriginalnameref(293);
    icolref(293) = 0;
    iknownnameref(292) = ioriginalnameref(292);
    icolref(292) = 0;
    iknownnameref(291) = ioriginalnameref(291);
    icolref(291) = 0;
    p = (290 + gdata_random_seed) % 6;
    iknownnameref(290) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(290) = _randcolor(p);
    p = (289 + gdata_random_seed) % 6;
    iknownnameref(289) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(289) = _randcolor(p);
    p = (288 + gdata_random_seed) % 6;
    iknownnameref(288) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(288) = _randcolor(p);
    p = (287 + gdata_random_seed) % 6;
    iknownnameref(287) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(287) = _randcolor(p);
    p = (286 + gdata_random_seed) % 6;
    iknownnameref(286) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(286) = _randcolor(p);
    p = (285 + gdata_random_seed) % 6;
    iknownnameref(285) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(285) = _randcolor(p);
    iknownnameref(284) = ioriginalnameref(284);
    icolref(284) = 0;
    iknownnameref(283) = ioriginalnameref(283);
    icolref(283) = 0;
    iknownnameref(282) = ioriginalnameref(282);
    icolref(282) = 0;
    iknownnameref(281) = ioriginalnameref(281);
    icolref(281) = 0;
    iknownnameref(280) = ioriginalnameref(280);
    icolref(280) = 0;
    iknownnameref(279) = ioriginalnameref(279);
    icolref(279) = 0;
    iknownnameref(278) = ioriginalnameref(278);
    icolref(278) = 0;
    iknownnameref(277) = ioriginalnameref(277);
    icolref(277) = 0;
    iknownnameref(276) = ioriginalnameref(276);
    icolref(276) = 0;
    iknownnameref(275) = ioriginalnameref(275);
    icolref(275) = 0;
    iknownnameref(274) = ioriginalnameref(274);
    icolref(274) = 1;
    iknownnameref(273) = ioriginalnameref(273);
    icolref(273) = 1;
    p = (272 + gdata_random_seed) % 6;
    iknownnameref(272) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(272) = _randcolor(p);
    p = (271 + gdata_random_seed) % 6;
    iknownnameref(271) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(271) = _randcolor(p);
    p = (270 + gdata_random_seed) % 6;
    iknownnameref(270) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(270) = _randcolor(p);
    p = (269 + gdata_random_seed) % 6;
    iknownnameref(269) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(269) = _randcolor(p);
    p = (268 + gdata_random_seed) % 6;
    iknownnameref(268) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(268) = _randcolor(p);
    p = (267 + gdata_random_seed) % 6;
    iknownnameref(267) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(267) = _randcolor(p);
    iknownnameref(266) = ioriginalnameref(266);
    icolref(266) = 0;
    p = (265 + gdata_random_seed) % 6;
    iknownnameref(265) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(265) = _randcolor(p);
    p = (264 + gdata_random_seed) % 6;
    iknownnameref(264) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(264) = _randcolor(p);
    p = (263 + gdata_random_seed) % 6;
    iknownnameref(263) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(263) = _randcolor(p);
    p = (262 + gdata_random_seed) % 6;
    iknownnameref(262) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(262) = _randcolor(p);
    iknownnameref(261) = ioriginalnameref(261);
    icolref(261) = 0;
    iknownnameref(260) = ioriginalnameref(260);
    icolref(260) = 0;
    iknownnameref(259) = ioriginalnameref(259);
    icolref(259) = 0;
    iknownnameref(258) = ioriginalnameref(258);
    icolref(258) = 0;
    p = (257 + gdata_random_seed) % 6;
    iknownnameref(257) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(257) = _randcolor(p);
    iknownnameref(256) = ioriginalnameref(256);
    icolref(256) = 0;
    iknownnameref(255) = ioriginalnameref(255);
    icolref(255) = 0;
    iknownnameref(254) = ioriginalnameref(254);
    icolref(254) = 0;
    if (jp)
    {
        iknownnameref(253) = u8"透明なポーション"s;
    }
    else
    {
        iknownnameref(253) = u8"clear liquid"s;
    }
    icolref(253) = 0;
    p = (252 + gdata_random_seed) % 6;
    iknownnameref(252) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(252) = _randcolor(p);
    p = (251 + gdata_random_seed) % 6;
    iknownnameref(251) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(251) = _randcolor(p);
    p = (250 + gdata_random_seed) % 6;
    iknownnameref(250) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(250) = _randcolor(p);
    p = (249 + gdata_random_seed) % 6;
    iknownnameref(249) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(249) = _randcolor(p);
    p = (248 + gdata_random_seed) % 6;
    iknownnameref(248) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(248) = _randcolor(p);
    p = (247 + gdata_random_seed) % 6;
    iknownnameref(247) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(247) = _randcolor(p);
    p = (246 + gdata_random_seed) % 6;
    iknownnameref(246) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(246) = _randcolor(p);
    p = (245 + gdata_random_seed) % 6;
    iknownnameref(245) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(245) = _randcolor(p);
    p = (244 + gdata_random_seed) % 6;
    iknownnameref(244) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(244) = _randcolor(p);
    p = (243 + gdata_random_seed) % 6;
    iknownnameref(243) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(243) = _randcolor(p);
    p = (242 + gdata_random_seed) % 6;
    iknownnameref(242) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(242) = _randcolor(p);
    iknownnameref(241) = ioriginalnameref(241);
    icolref(241) = 1;
    iknownnameref(240) = ioriginalnameref(240);
    icolref(240) = 1;
    iknownnameref(239) = ioriginalnameref(239);
    icolref(239) = 1;
    iknownnameref(238) = ioriginalnameref(238);
    icolref(238) = 1;
    iknownnameref(237) = ioriginalnameref(237);
    icolref(237) = 1;
    p = (236 + gdata_random_seed) % 6;
    iknownnameref(236) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(236) = _randcolor(p);
    iknownnameref(235) = ioriginalnameref(235);
    icolref(235) = 0;
    iknownnameref(234) = ioriginalnameref(234);
    icolref(234) = 0;
    iknownnameref(233) = ioriginalnameref(233);
    icolref(233) = 0;
    iknownnameref(232) = ioriginalnameref(232);
    icolref(232) = 0;
    iknownnameref(231) = ioriginalnameref(231);
    icolref(231) = 0;
    iknownnameref(230) = ioriginalnameref(230);
    icolref(230) = 0;
    iknownnameref(229) = ioriginalnameref(229);
    icolref(229) = 0;
    iknownnameref(228) = ioriginalnameref(228);
    icolref(228) = 0;
    iknownnameref(227) = ioriginalnameref(227);
    icolref(227) = 0;
    iknownnameref(226) = ioriginalnameref(226);
    icolref(226) = 0;
    iknownnameref(225) = ioriginalnameref(225);
    icolref(225) = 0;
    iknownnameref(224) = ioriginalnameref(224);
    icolref(224) = 0;
    iknownnameref(223) = ioriginalnameref(223);
    icolref(223) = 0;
    iknownnameref(222) = ioriginalnameref(222);
    icolref(222) = 0;
    iknownnameref(221) = ioriginalnameref(221);
    icolref(221) = 0;
    iknownnameref(220) = ioriginalnameref(220);
    icolref(220) = 0;
    iknownnameref(219) = ioriginalnameref(219);
    icolref(219) = 1;
    iknownnameref(218) = ioriginalnameref(218);
    icolref(218) = 1;
    iknownnameref(217) = ioriginalnameref(217);
    icolref(217) = 1;
    iknownnameref(216) = ioriginalnameref(216);
    icolref(216) = 1;
    iknownnameref(215) = ioriginalnameref(215);
    icolref(215) = 1;
    iknownnameref(214) = ioriginalnameref(214);
    icolref(214) = 1;
    iknownnameref(213) = ioriginalnameref(213);
    icolref(213) = 0;
    iknownnameref(212) = ioriginalnameref(212);
    icolref(212) = 0;
    iknownnameref(211) = ioriginalnameref(211);
    icolref(211) = 0;
    iknownnameref(210) = ioriginalnameref(210);
    icolref(210) = 0;
    p = (209 + gdata_random_seed) % 6;
    iknownnameref(209) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(209) = _randcolor(p);
    if (jp)
    {
        iknownnameref(208) = u8"途方もない価値の金塊"s;
    }
    else
    {
        iknownnameref(208) = u8"valuable gold bar"s;
    }
    icolref(208) = 0;
    if (jp)
    {
        iknownnameref(207) = u8"波動を放つ弓"s;
    }
    else
    {
        iknownnameref(207) = u8"shaking bow"s;
    }
    icolref(207) = 7;
    if (jp)
    {
        iknownnameref(206) = u8"風をまとった短剣"s;
    }
    else
    {
        iknownnameref(206) = u8"dagger surrounded by wind"s;
    }
    icolref(206) = 4;
    if (jp)
    {
        iknownnameref(205) = u8"透明なポーション"s;
    }
    else
    {
        iknownnameref(205) = u8"clear liquid"s;
    }
    icolref(205) = 0;
    iknownnameref(204) = ioriginalnameref(204);
    icolref(204) = 0;
    p = (203 + gdata_random_seed) % 6;
    iknownnameref(203) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(203) = _randcolor(p);
    p = (202 + gdata_random_seed) % 6;
    iknownnameref(202) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(202) = _randcolor(p);
    iknownnameref(201) = ioriginalnameref(201);
    icolref(201) = 0;
    iknownnameref(200) = ioriginalnameref(200);
    icolref(200) = 0;
    iknownnameref(199) = ioriginalnameref(199);
    icolref(199) = 0;
    iknownnameref(198) = ioriginalnameref(198);
    icolref(198) = 0;
    iknownnameref(197) = ioriginalnameref(197);
    icolref(197) = 0;
    iknownnameref(196) = ioriginalnameref(196);
    icolref(196) = 0;
    iknownnameref(195) = ioriginalnameref(195);
    icolref(195) = 0;
    iknownnameref(194) = ioriginalnameref(194);
    icolref(194) = 0;
    iknownnameref(193) = ioriginalnameref(193);
    icolref(193) = 0;
    iknownnameref(192) = ioriginalnameref(192);
    icolref(192) = 0;
    iknownnameref(191) = ioriginalnameref(191);
    icolref(191) = 0;
    iknownnameref(190) = ioriginalnameref(190);
    icolref(190) = 0;
    iknownnameref(189) = ioriginalnameref(189);
    icolref(189) = 0;
    iknownnameref(188) = ioriginalnameref(188);
    icolref(188) = 0;
    iknownnameref(187) = ioriginalnameref(187);
    icolref(187) = 0;
    iknownnameref(186) = ioriginalnameref(186);
    icolref(186) = 0;
    iknownnameref(185) = ioriginalnameref(185);
    icolref(185) = 0;
    iknownnameref(184) = ioriginalnameref(184);
    icolref(184) = 0;
    iknownnameref(183) = ioriginalnameref(183);
    icolref(183) = 0;
    iknownnameref(182) = ioriginalnameref(182);
    icolref(182) = 0;
    iknownnameref(181) = ioriginalnameref(181);
    icolref(181) = 0;
    iknownnameref(180) = ioriginalnameref(180);
    icolref(180) = 0;
    iknownnameref(179) = ioriginalnameref(179);
    icolref(179) = 0;
    iknownnameref(178) = ioriginalnameref(178);
    icolref(178) = 0;
    iknownnameref(177) = ioriginalnameref(177);
    icolref(177) = 0;
    p = (176 + gdata_random_seed) % 6;
    iknownnameref(176) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(176) = _randcolor(p);
    p = (175 + gdata_random_seed) % 6;
    iknownnameref(175) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(175) = _randcolor(p);
    iknownnameref(174) = ioriginalnameref(174);
    icolref(174) = 0;
    iknownnameref(173) = ioriginalnameref(173);
    icolref(173) = 0;
    iknownnameref(172) = ioriginalnameref(172);
    icolref(172) = 0;
    iknownnameref(171) = ioriginalnameref(171);
    icolref(171) = 0;
    iknownnameref(170) = ioriginalnameref(170);
    icolref(170) = 0;
    iknownnameref(169) = ioriginalnameref(169);
    icolref(169) = 0;
    iknownnameref(168) = ioriginalnameref(168);
    icolref(168) = 0;
    iknownnameref(167) = ioriginalnameref(167);
    icolref(167) = 0;
    iknownnameref(166) = ioriginalnameref(166);
    icolref(166) = 0;
    iknownnameref(165) = ioriginalnameref(165);
    icolref(165) = 0;
    iknownnameref(164) = ioriginalnameref(164);
    icolref(164) = 0;
    iknownnameref(163) = ioriginalnameref(163);
    icolref(163) = 1;
    iknownnameref(162) = ioriginalnameref(162);
    icolref(162) = 1;
    iknownnameref(161) = ioriginalnameref(161);
    icolref(161) = 1;
    iknownnameref(160) = ioriginalnameref(160);
    icolref(160) = 1;
    iknownnameref(159) = ioriginalnameref(159);
    icolref(159) = 1;
    iknownnameref(158) = ioriginalnameref(158);
    icolref(158) = 0;
    iknownnameref(157) = ioriginalnameref(157);
    icolref(157) = 1;
    iknownnameref(156) = ioriginalnameref(156);
    icolref(156) = 0;
    iknownnameref(155) = ioriginalnameref(155);
    icolref(155) = 1;
    iknownnameref(154) = ioriginalnameref(154);
    icolref(154) = 1;
    iknownnameref(153) = ioriginalnameref(153);
    icolref(153) = 1;
    iknownnameref(152) = ioriginalnameref(152);
    icolref(152) = 1;
    iknownnameref(151) = ioriginalnameref(151);
    icolref(151) = 1;
    iknownnameref(150) = ioriginalnameref(150);
    icolref(150) = 1;
    iknownnameref(149) = ioriginalnameref(149);
    icolref(149) = 0;
    iknownnameref(148) = ioriginalnameref(148);
    icolref(148) = 0;
    iknownnameref(147) = ioriginalnameref(147);
    icolref(147) = 1;
    iknownnameref(146) = ioriginalnameref(146);
    icolref(146) = 1;
    iknownnameref(145) = ioriginalnameref(145);
    icolref(145) = 1;
    iknownnameref(144) = ioriginalnameref(144);
    icolref(144) = 1;
    iknownnameref(143) = ioriginalnameref(143);
    icolref(143) = 0;
    iknownnameref(142) = ioriginalnameref(142);
    icolref(142) = 0;
    iknownnameref(141) = ioriginalnameref(141);
    icolref(141) = 1;
    iknownnameref(140) = ioriginalnameref(140);
    icolref(140) = 1;
    iknownnameref(139) = ioriginalnameref(139);
    icolref(139) = 0;
    iknownnameref(138) = ioriginalnameref(138);
    icolref(138) = 0;
    iknownnameref(137) = ioriginalnameref(137);
    icolref(137) = 1;
    iknownnameref(136) = ioriginalnameref(136);
    icolref(136) = 1;
    iknownnameref(135) = ioriginalnameref(135);
    icolref(135) = 1;
    iknownnameref(134) = ioriginalnameref(134);
    icolref(134) = 1;
    iknownnameref(133) = ioriginalnameref(133);
    icolref(133) = 1;
    iknownnameref(132) = ioriginalnameref(132);
    icolref(132) = 1;
    iknownnameref(131) = ioriginalnameref(131);
    icolref(131) = 1;
    iknownnameref(130) = ioriginalnameref(130);
    icolref(130) = 1;
    iknownnameref(129) = ioriginalnameref(129);
    icolref(129) = 1;
    iknownnameref(128) = ioriginalnameref(128);
    icolref(128) = 1;
    iknownnameref(127) = ioriginalnameref(127);
    icolref(127) = 1;
    iknownnameref(126) = ioriginalnameref(126);
    icolref(126) = 1;
    p = (125 + gdata_random_seed) % 6;
    iknownnameref(125) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(125) = _randcolor(p);
    iknownnameref(124) = ioriginalnameref(124);
    icolref(124) = 0;
    p = (123 + gdata_random_seed) % 6;
    iknownnameref(123) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(123) = _randcolor(p);
    p = (122 + gdata_random_seed) % 6;
    iknownnameref(122) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(122) = _randcolor(p);
    p = (121 + gdata_random_seed) % 6;
    iknownnameref(121) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(121) = _randcolor(p);
    p = (120 + gdata_random_seed) % 6;
    iknownnameref(120) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(120) = _randcolor(p);
    p = (119 + gdata_random_seed) % 6;
    iknownnameref(119) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(119) = _randcolor(p);
    p = (118 + gdata_random_seed) % 6;
    iknownnameref(118) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(118) = _randcolor(p);
    iknownnameref(117) = ioriginalnameref(117);
    icolref(117) = 1;
    p = (116 + gdata_random_seed) % 6;
    iknownnameref(116) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(116) = _randcolor(p);
    iknownnameref(115) = ioriginalnameref(115);
    icolref(115) = 0;
    iknownnameref(114) = ioriginalnameref(114);
    icolref(114) = 0;
    iknownnameref(113) = ioriginalnameref(113);
    icolref(113) = 0;
    iknownnameref(112) = ioriginalnameref(112);
    icolref(112) = 0;
    iknownnameref(111) = ioriginalnameref(111);
    icolref(111) = 0;
    iknownnameref(110) = ioriginalnameref(110);
    icolref(110) = 1;
    iknownnameref(109) = ioriginalnameref(109);
    icolref(109) = 0;
    iknownnameref(108) = ioriginalnameref(108);
    icolref(108) = 0;
    iknownnameref(107) = ioriginalnameref(107);
    icolref(107) = 0;
    iknownnameref(106) = ioriginalnameref(106);
    icolref(106) = 1;
    iknownnameref(105) = ioriginalnameref(105);
    icolref(105) = 0;
    iknownnameref(104) = ioriginalnameref(104);
    icolref(104) = 0;
    iknownnameref(103) = ioriginalnameref(103);
    icolref(103) = 0;
    iknownnameref(102) = ioriginalnameref(102);
    icolref(102) = 1;
    iknownnameref(101) = ioriginalnameref(101);
    icolref(101) = 1;
    iknownnameref(100) = ioriginalnameref(100);
    icolref(100) = 0;
    iknownnameref(99) = ioriginalnameref(99);
    icolref(99) = 1;
    iknownnameref(98) = ioriginalnameref(98);
    icolref(98) = 1;
    iknownnameref(97) = ioriginalnameref(97);
    icolref(97) = 1;
    iknownnameref(96) = ioriginalnameref(96);
    icolref(96) = 1;
    iknownnameref(95) = ioriginalnameref(95);
    icolref(95) = 1;
    iknownnameref(94) = ioriginalnameref(94);
    icolref(94) = 1;
    iknownnameref(93) = ioriginalnameref(93);
    icolref(93) = 1;
    iknownnameref(92) = ioriginalnameref(92);
    icolref(92) = 1;
    iknownnameref(91) = ioriginalnameref(91);
    icolref(91) = 0;
    iknownnameref(90) = ioriginalnameref(90);
    icolref(90) = 1;
    iknownnameref(89) = ioriginalnameref(89);
    icolref(89) = 1;
    iknownnameref(88) = ioriginalnameref(88);
    icolref(88) = 0;
    iknownnameref(87) = ioriginalnameref(87);
    icolref(87) = 1;
    iknownnameref(86) = ioriginalnameref(86);
    icolref(86) = 1;
    iknownnameref(85) = ioriginalnameref(85);
    icolref(85) = 1;
    iknownnameref(84) = ioriginalnameref(84);
    icolref(84) = 1;
    iknownnameref(83) = ioriginalnameref(83);
    icolref(83) = 1;
    iknownnameref(82) = ioriginalnameref(82);
    icolref(82) = 1;
    iknownnameref(81) = ioriginalnameref(81);
    icolref(81) = 1;
    iknownnameref(80) = ioriginalnameref(80);
    icolref(80) = 1;
    iknownnameref(79) = ioriginalnameref(79);
    icolref(79) = 0;
    iknownnameref(78) = ioriginalnameref(78);
    icolref(78) = 0;
    iknownnameref(77) = ioriginalnameref(77);
    icolref(77) = 0;
    p = (76 + gdata_random_seed) % 6;
    iknownnameref(76) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(76) = _randcolor(p);
    p = (75 + gdata_random_seed) % 6;
    iknownnameref(75) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(75) = _randcolor(p);
    p = (74 + gdata_random_seed) % 6;
    iknownnameref(74) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(74) = _randcolor(p);
    if (jp)
    {
        iknownnameref(73) = u8"全てを終結させる剣"s;
    }
    else
    {
        iknownnameref(73) = u8"sword that ends all"s;
    }
    icolref(73) = 7;
    p = (72 + gdata_random_seed) % 6;
    iknownnameref(72) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(72) = _randcolor(p);
    p = (71 + gdata_random_seed) % 6;
    iknownnameref(71) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(71) = _randcolor(p);
    p = (70 + gdata_random_seed) % 6;
    iknownnameref(70) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(70) = _randcolor(p);
    p = (69 + gdata_random_seed) % 6;
    iknownnameref(69) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(69) = _randcolor(p);
    p = (68 + gdata_random_seed) % 6;
    iknownnameref(68) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(68) = _randcolor(p);
    p = (67 + gdata_random_seed) % 6;
    iknownnameref(67) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"amulet");
    icolref(67) = 0;
    iknownnameref(66) = ioriginalnameref(66);
    icolref(66) = 0;
    iknownnameref(65) = ioriginalnameref(65);
    icolref(65) = 0;
    if (jp)
    {
        iknownnameref(64) = u8"黒き混沌の剣"s;
    }
    else
    {
        iknownnameref(64) = u8"chaotic sword"s;
    }
    icolref(64) = 4;
    if (jp)
    {
        iknownnameref(63) = u8"死を奏でる大鎌"s;
    }
    else
    {
        iknownnameref(63) = u8"scythe that sings death"s;
    }
    icolref(63) = 3;
    iknownnameref(62) = ioriginalnameref(62);
    icolref(62) = 0;
    iknownnameref(61) = ioriginalnameref(61);
    icolref(61) = 0;
    iknownnameref(60) = ioriginalnameref(60);
    icolref(60) = 0;
    iknownnameref(59) = ioriginalnameref(59);
    icolref(59) = 0;
    iknownnameref(58) = ioriginalnameref(58);
    icolref(58) = 0;
    if (jp)
    {
        iknownnameref(57) = u8"白銀の刀"s;
    }
    else
    {
        iknownnameref(57) = u8"shining silver katana"s;
    }
    icolref(57) = 4;
    if (jp)
    {
        iknownnameref(56) = u8"漆黒の剣"s;
    }
    else
    {
        iknownnameref(56) = u8"pure black sword"s;
    }
    icolref(56) = 7;
    iknownnameref(55) = ioriginalnameref(55);
    icolref(55) = 0;
    iknownnameref(54) = ioriginalnameref(54);
    icolref(54) = 0;
    iknownnameref(53) = ioriginalnameref(53);
    icolref(53) = 0;
    iknownnameref(52) = ioriginalnameref(52);
    icolref(52) = 0;
    iknownnameref(51) = ioriginalnameref(51);
    icolref(51) = 0;
    iknownnameref(50) = ioriginalnameref(50);
    icolref(50) = 0;
    iknownnameref(49) = ioriginalnameref(49);
    icolref(49) = 0;
    iknownnameref(48) = ioriginalnameref(48);
    icolref(48) = 0;
    iknownnameref(47) = ioriginalnameref(47);
    icolref(47) = 0;
    iknownnameref(46) = ioriginalnameref(46);
    icolref(46) = 0;
    iknownnameref(45) = ioriginalnameref(45);
    icolref(45) = 0;
    iknownnameref(44) = ioriginalnameref(44);
    icolref(44) = 0;
    iknownnameref(43) = ioriginalnameref(43);
    icolref(43) = 0;
    iknownnameref(42) = ioriginalnameref(42);
    icolref(42) = 4;
    iknownnameref(41) = ioriginalnameref(41);
    icolref(41) = 2;
    iknownnameref(40) = ioriginalnameref(40);
    icolref(40) = 0;
    iknownnameref(39) = ioriginalnameref(39);
    icolref(39) = 3;
    iknownnameref(38) = ioriginalnameref(38);
    icolref(38) = 0;
    iknownnameref(37) = ioriginalnameref(37);
    icolref(37) = 5;
    iknownnameref(36) = ioriginalnameref(36);
    icolref(36) = 3;
    iknownnameref(35) = ioriginalnameref(35);
    icolref(35) = 6;
    p = (34 + gdata_random_seed) % 6;
    iknownnameref(34) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(34) = _randcolor(p);
    p = (33 + gdata_random_seed) % 6;
    iknownnameref(33) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(33) = _randcolor(p);
    p = (32 + gdata_random_seed) % 6;
    iknownnameref(32) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(32) = _randcolor(p);
    if (jp)
    {
        iknownnameref(31) = u8"透明なポーション"s;
    }
    else
    {
        iknownnameref(31) = u8"clear liquid"s;
    }
    icolref(31) = 0;
    p = (30 + gdata_random_seed) % 6;
    iknownnameref(30) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(30) = _randcolor(p);
    p = (29 + gdata_random_seed) % 6;
    iknownnameref(29) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(29) = _randcolor(p);
    p = (28 + gdata_random_seed) % 6;
    iknownnameref(28) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(28) = _randcolor(p);
    p = (27 + gdata_random_seed) % 6;
    iknownnameref(27) = i18n::_(u8"ui", u8"random_potion", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"potion");
    icolref(27) = _randcolor(p);
    if (jp)
    {
        iknownnameref(26) = u8"透明なポーション"s;
    }
    else
    {
        iknownnameref(26) = u8"clear liquid"s;
    }
    icolref(26) = 0;
    if (jp)
    {
        iknownnameref(25) = u8"バグの本"s;
    }
    else
    {
        iknownnameref(25) = u8"book"s;
    }
    icolref(25) = 0;
    if (jp)
    {
        iknownnameref(24) = u8"本"s;
    }
    else
    {
        iknownnameref(24) = u8"book"s;
    }
    icolref(24) = 0;
    if (jp)
    {
        iknownnameref(23) = u8"本"s;
    }
    else
    {
        iknownnameref(23) = u8"book"s;
    }
    icolref(23) = 0;
    p = (22 + gdata_random_seed) % 6;
    iknownnameref(22) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(22) = _randcolor(p);
    p = (21 + gdata_random_seed) % 6;
    iknownnameref(21) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(21) = _randcolor(p);
    p = (20 + gdata_random_seed) % 6;
    iknownnameref(20) = i18n::_(u8"ui", u8"random_spellbook", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"spellbook");
    icolref(20) = _randcolor(p);
    p = (19 + gdata_random_seed) % 6;
    iknownnameref(19) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(19) = _randcolor(p);
    p = (18 + gdata_random_seed) % 6;
    iknownnameref(18) = i18n::_(u8"ui", u8"random_rod", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"rod");
    icolref(18) = _randcolor(p);
    p = (17 + gdata_random_seed) % 6;
    iknownnameref(17) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(17) = _randcolor(p);
    p = (16 + gdata_random_seed) % 6;
    iknownnameref(16) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(16) = _randcolor(p);
    p = (15 + gdata_random_seed) % 6;
    iknownnameref(15) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(15) = _randcolor(p);
    p = (14 + gdata_random_seed) % 6;
    iknownnameref(14) = i18n::_(u8"ui", u8"random_scroll", u8"_"s + p)
        + strblank + i18n::_(u8"ui", u8"scroll");
    icolref(14) = _randcolor(p);
    p = (13 + gdata_random_seed) % 6;
    iknownnameref(13) = i18n::_(u8"ui", u8"random_ring", u8"_"s + p) + strblank
        + i18n::_(u8"ui", u8"ring");
    icolref(13) = 0;
    iknownnameref(12) = ioriginalnameref(12);
    icolref(12) = 0;
    iknownnameref(11) = ioriginalnameref(11);
    icolref(11) = 0;
    iknownnameref(10) = ioriginalnameref(10);
    icolref(10) = 0;
    iknownnameref(9) = ioriginalnameref(9);
    icolref(9) = 0;
    iknownnameref(8) = ioriginalnameref(8);
    icolref(8) = 0;
    iknownnameref(7) = ioriginalnameref(7);
    icolref(7) = 0;
    iknownnameref(6) = ioriginalnameref(6);
    icolref(6) = 0;
    iknownnameref(5) = ioriginalnameref(5);
    icolref(5) = 0;
    iknownnameref(4) = ioriginalnameref(4);
    icolref(4) = 0;
    iknownnameref(3) = ioriginalnameref(3);
    icolref(3) = 0;
    iknownnameref(2) = ioriginalnameref(2);
    icolref(2) = 0;
    iknownnameref(1) = ioriginalnameref(1);
    icolref(1) = 0;
    iknownnameref(0) = ioriginalnameref(0);
    icolref(0) = 0;

    maxitemid = 795;
}



} // namespace elona
