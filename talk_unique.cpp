#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "crafting.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "map_cell.hpp"
#include "menu.hpp"
#include "random.hpp"
#include "shop.hpp"
#include "status_ailment.hpp"
#include "talk.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{


talk_result_t talk_unique()
{
    listmax = 0;
    switch (chatval(1))
    {
    case 2:
        listmax = 0;
        buff = lang(
            u8"ここまで辿り着くとはな…どうやら《混沌》は、自ら創りしネフィアの安定さえも望まぬらしい。しかし、私とてここで死ぬつもりなどないのだ。"s,
            u8"So you've made it this far. Evidently, <Chaos> wants no poise even within their own creation...Nefia. Well, it seems they have left me no choice but to whip you!"s);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        gdata_main_quest_flag = 170;
        return talk_result_t::talk_end;
    case 23:
        if (event_id() == 1)
        {
            if (jp)
            {
                listmax = 0;
                buff =
                    u8"ああ、聡明なるレシマスの常闇の眼よ！ 新しい主は、どうやらお前の本当の価値を知らないようだぞ。…だが、心配しなくてもいい。この"s +
                    i18n::_(u8"ui", u8"sex", u8"_"s + cdata[0].sex) +
                    u8"は、そこで死んでいる老人のように、たまに本を開いては下界の嘘に満ちた歴史を嘲笑い、自己満足にふける以外の使い方を、きっと見つけてくれるだろう。"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff =
                    u8"(青年は見下したような笑い声をあげ、あなたに向き直った) さあ、これ以上愚かな詮索の表情を続けて私を落胆させないでくれ。お前が眺めている本には、真実の歴史を刻み、過去の文明の歩みを記録する魔力が秘められていると知ったのなら。"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff =
                    u8"そう。この本に書かれていることは、全て偽りなき歴史。シエラ・テールの、そして過去の偉大なる文明の栄光と衰退の軌跡が記されている。その価値を、わざわざ説明する必要もあるまい？"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff =
                    u8"ひとつ警告しよう。台座から離れた時、それは魔力を失い、変哲の無い一冊の本と化すのだ。新たな歴史が刻まれることはなく、正当性を証明するすべもなくなるだろう。"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff =
                    u8"本を所有する者はまた、偽りの歴史を動かす勢力から、自らの命を守る必要にも迫られるだろう。このアーティファクトには、それだけの価値があるということだ。そしてお前には…エレアの風を聴く者と出会い、言葉を交じあわせたお前には…それがどれほどの意味を持つことか、理解していなくてもだ…そうだな、少なくとも我々を楽しませてくれるような使い方を期待しているよ。"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff =
                    u8"もちろん、本を下界に持ち出すかどうかはお前次第だ…少なくとも、選択という行為に、私が予期できない偶然がある可能性を、お前が信じるのなら。"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            else
            {
                listmax = 0;
                buff = u8"Most impressive."s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            return talk_result_t::talk_end;
        }
        break;
    case 28:
        listmax = 0;
        buff = lang(u8"よそへいってくれ…"s, u8"Leave me alone."s);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    case 29:
        if (cdata[0].fame < 20000)
        {
            listmax = 0;
            buff =
                lang(u8"邪魔だ。話しかけるな。"s, u8"Who the hell are you?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_nightmare == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"気安く声をかけるな。"s,
                u8"You have the money, now get lost."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_nightmare == 0)
        {
            listmax = 0;
            buff = lang(u8"おい、ちょっと待て。貴様の面には見覚えがある…"s +
                    cdatan(1, 0) +
                    u8"…といったか？最近、このティリスの地で名を上げているそうじゃないか。"s,
                u8"Hey you! Hold up! I've seen your face before punk... "s +
                    cdatan(1, 0) +
                    u8"... Ah yes... I remember now. You've been making quite a name for yourself throughout Tyris, haven't you?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            ELONA_APPEND_RESPONSE(
                1, lang(u8"話を聞こう"s, u8"Fine, let's do it."s));
            ELONA_APPEND_RESPONSE(
                0, lang(u8"止めておこう"s, u8"Not a chance, you worm."s));
            buff = lang(
                u8"貴様に金になる仕事をやろう。ザナンのある機関からの要望で、実験のデータをとるために被験者が必要なのだ。俺に言わせれば、被験者というより『生贄』だがな。生き延びて戻ってくれば、老後を遊んで暮らせるだけの報酬はくれてやる。どうするかこの場で決めろ。"s,
                u8"You wanna make some quick cash? I've got a request from the organization of Zanan. They need a test subject in order to get some experimental data. Or perhaps \"sacrifice\" would be a more appropriate term. *If* you survive, I'll pay you enough to party until you waste away. Make your decision quickly."s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"骨のないやつだ。うせろ。"s,
                    u8"Fine then, piss off you spineless coward."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"いいだろう。死ぬ準備ができたら、声をかけろ。実験場まで案内してやろう。"s,
                u8"Excellent. Let me know when you've finished your preparations for death and I'll take you to the testing grounds."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_nightmare = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_nightmare == 1 || gdata_nightmare == 2)
        {
            ELONA_APPEND_RESPONSE(1, lang(u8"いい"s, u8"Yes."s));
            ELONA_APPEND_RESPONSE(0, lang(u8"だめ"s, u8"No."s));
            buff = lang(
                u8"フッ。よく逃げ出さずに戻ってきたな。準備はいいか。"s,
                u8"So, are you ready?"s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"早くしろ。"s, u8"Be quick."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(u8"よし…付いて来い。"s, u8"Follow me."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_nightmare = 2;
            mdata(4) = cdata[0].position.y * 1000 + cdata[0].position.x;
            gdata_destination_map = 5;
            gdata_destination_dungeon_level = 5;
            levelexitby = 2;
            chatteleport = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_nightmare == 3)
        {
            flt();
            nostack = 1;
            itemcreate(-1, 630, cdata[0].position.x, cdata[0].position.y, 0);
            fixmaterial = 15;
            change_item_material();
            flt();
            itemcreate(
                -1, 54, cdata[0].position.x, cdata[0].position.y, 100000);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 5);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"驚いた。この実験から生きて帰って来た冒険者は、貴様がはじめてだ。これで、ザナンの上層部が、研究を見直してくれるといいが。あんな不細工な化け物を率いて戦場を駆け回るのは、御免だからな。"s,
                u8"You came back alive... astonishing. You're the first and I swear you'll be the last. Zanan's senior commanders should find this data most intriguing. I do not want such a clumsy beast watching my back on the battlefield."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_nightmare = 1000;
            return talk_result_t::talk_end;
        }
        return talk_result_t::talk_end;
    case 30:
        if (gdata_putit_attacks == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"あら、冒険者さん♪ お茶でもいかが？"s,
                u8"Hi there adventurer! Would you like some tea?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_putit_attacks == 0)
        {
            listmax = 0;
            buff = lang(
                u8"あら、冒険者さん。ちょうどいいところに来てくれたわ。"s,
                u8"Ah, you... adventurer, you've definitely come to the right place."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            ELONA_APPEND_RESPONSE(1, lang(u8"引き受ける"s, u8"Sure thing."s));
            ELONA_APPEND_RESPONSE(0, lang(u8"面倒だ"s, u8"Not now."s));
            buff = lang(
                u8"最近、朝起きると私のぬいぐるみがぼろぼろになっているの。夜中に起きてこっそり見張ってたらね、なんとプチ…プチがぬいぐるみ食べてるのよ！どうも隣の家の窓を伝って、私の家に入ってくるみたいなの。冒険者さん、お願いだから、ちょっと行って退治してきてくれない？"s,
                u8"Recently, when I wake in the morning my stuffed toys are always chewed up. So I stayed up last night and secretly watched. You know what I found? Putits were chewing up my stuffed animals! I'm pretty sure they're getting into my house through the window to the neighbor's place. I beg of you adventurer, won't you eradicate the Putits for me?"s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"気が変わったら、また来てね。"s,
                    u8"Okay... but... if you change your mind please come back."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"頼もしいよ。問題の家は、すぐ南に隣接しているわ。頑張ってね！"s,
                u8"Fabulous! The trouble is all in the house just south of here."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_putit_attacks = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_putit_attacks == 1)
        {
            listmax = 0;
            buff = lang(
                u8"やだ！このぬいぐるみもプチに食べられてる。冒険者さん、はやく退治お願いね。"s,
                u8"Aggh! My stuffed toys are ruined! Hurry up and kill the Putits!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_putit_attacks == 2)
        {
            flt(calcobjlv(10), calcfixlv(3));
            itemcreate(-1, 449, cdata[0].position.x, cdata[0].position.y, 0);
            flt(calcobjlv(10), calcfixlv(3));
            itemcreate(-1, 66, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 3000);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"え、スライムを退治してくれたの？ありがとうございます♪あたしのぬいぐるみたちも喜んでるわ。これ、役に立つかわからないけど、とっておいてね。"s,
                u8"Eh? You wiped out the slimes? Thanks so much. My stuffed animals are delighted too. Here, you might find this useful."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_putit_attacks = 1000;
            return talk_result_t::talk_end;
        }
        break;
    case 31:
        if (gdata_thieves_hideout == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"いらっしゃいませ〜♪その節はどうもです。"s,
                u8"Oh it's you, our hero."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_thieves_hideout == 0)
        {
            if (jp)
            {
                listmax = 0;
                buff = u8"いらっしゃいませ〜♪"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            ELONA_APPEND_RESPONSE(
                1, lang(u8"引き受ける"s, u8"I'd be happy to help."s));
            ELONA_APPEND_RESPONSE(0, lang(u8"面倒だ"s, u8"Don't bother me."s));
            buff = lang(
                u8"ちょっとお時間いいですか？バーの酒樽が度々盗まれて、店長困ってるんです。もし手が空いていたら、助けてくださいな。盗みを働いている輩の目星はついています。きっと、ヴェルニースを拠点に活動している、こそ泥の集団です！拠点は確か墓の方にあったはずですよ。"s,
                u8"Excuse me, do you have a moment? The kegs from the bar have been stolen, and the manager is really put out. If you're not busy, could you help out? It was those thugs, I'm sure of it. They've certainly set up a base inside Vernis. With all the mud they leave behind, they're most likely hanging out near the gravesite."s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"そうですか…残念です。"s,
                    u8"Alright, but please... think about it."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"あ…ありがとうございます！よろしくお願いしますね！"s,
                u8"Really? Thanks, we really appreciate it."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_thieves_hideout = 1;
            cell_featset(48, 5, tile_downstairs, 11, 4);
            return talk_result_t::talk_end;
        }
        if (gdata_thieves_hideout == 1)
        {
            listmax = 0;
            buff = lang(
                u8"いらっしゃいませ〜♪盗賊団の拠点はみつかりましたか？墓の近くにあるみたいですよ。"s,
                u8"Welcome! Welcome! Have you found the bandit's lair yet? It should be near the graveyard."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_thieves_hideout == 2)
        {
            flt();
            itemcreate(-1, 18, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].count = 12;
            flt();
            nostack = 1;
            itemcreate(-1, 685, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].param2 = 5;
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 1500);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"ええ、噂はもう届いています。あのごろつき団がいなくなって、私達ほんと安心しました。ありがとうございます。少ないですが、店長がお礼にとこれを♪"s,
                u8"Yes, I've already gotten wind of your deeds. It's a big relief to be rid of those miscreants. I can't thank you enough. I know it isn't much, but please take this as a token of our thanks."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_thieves_hideout = 1000;
            return talk_result_t::talk_end;
        }
        break;
    case 33:
        ELONA_APPEND_RESPONSE(
            3, lang(u8"旅の目的"s, u8"What's your mission?"s));
        ELONA_APPEND_RESPONSE(
            2,
            lang(u8"ノースティリスについて"s, u8"Tell me about North Tyris."s));
        ELONA_APPEND_RESPONSE(
            1,
            lang(
                u8"獣に変えられた王子の童話"s,
                u8"You mentioned a fairy tale."s));
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = lang(
            u8"無事に意識が戻ってよかったわ。あなたを最初に見たときは、もう手遅れかと思ったほどだもの。"s,
            u8"I'm glad you got well again. I thought you were a goner until just a few minutes ago."s);
        talk_window_query();
        if (chatval == 1)
        {
            listmax = 0;
            buff = lang(
                u8"あなたは、こんな話を聞いたことがあるかしら。"s,
                u8"You may have heard of this story before..."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"あるところに、魔法によって醜い獣のような姿に変えられた 王子がいた…彼は自分の姿に絶望し、国を捨て森の中の小屋で暮らしたの。"s,
                u8"There was once a prince who had his shape changed into that of an ugly beast by a witch. Despairing of his bloodcurdling appearance, he hid himself in a forest far from his kingdom."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"ある日、狼に襲われ傷ついた女が、小屋に駆け込み倒れこんだ。王子は迷いながらも女を介抱した。彼女はもちろん男の姿におびえて泣いたわ。"s,
                u8"One day a woman rushed into his hut and passed out, having been badly wounded by a pack of wolves. He treated her with the knowledge and fear that his ugly body might scare her. This fear turned into reality soon enough for she cried out as she woke up."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"でも、何日もたち彼女は男の優しさに気付いた。彼の誠実さに、抱える葛藤に、心を打たれたの。怪我の癒えた女は、男のささえとなり共に暮らすことを決心した…"s,
                u8"However, as days passed by and she regained her health, the woman had come to recognize the kindness and generosity that was within the heart of this beast. She decided to live with him."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"二人は様々な困難を力を合わせ乗り越えて、最後には王子にかけられた呪いがとけ、二人が結婚して幸せな結末を迎えるの。どこにでもある物語ね。"s,
                u8"They surmounted various difficulties throughout their lives and the story comes to an end when the curse set upon the prince finally breaks and the beast returned to his former shape, that of a flawlessly handsome prince. The two of them got along very well from that time on. A happy ending... although just an ordinary story, don't you agree?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"わたしは、小さい頃聞かされたこのおとぎ話が、どうしても好きになれなかった。きっと、醜い姿の男に対する愛が、どこかに置き去りにされた気がしたのね。"s,
                u8"The elders of Vindale used to tell me this kind of story. But I never liked this one. Perhaps it is because I felt like the beast that she loved despite the fact that his ugliness had been left behind somewhere."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 2)
        {
            listmax = 0;
            buff = lang(
                u8"アセリア大陸から大洋を隔たち、ティリス大陸の北に位置するのがノースティリスよ。自由と平和の国パルミアの統治の下、古代の遺跡群ネフィアを巡り、多くの旅人や商人がこの地を訪れるの。あなたも、そんな旅人の一人かしら？"s,
                u8"North Tyris is a continent in the western hemisphere of Irva. Lots of merchants and travelers set foot on North Tyris' soil with the dream of making a fortune in the ancient ruins of Nefia."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"目的が決まっていないのなら、南の炭鉱街ヴェルニースに行くといいわ。あなたの探しているものが、見つかるかもしれない。"s,
                u8"If you haven't set your destination yet, you might want to visit Vernis. It's a mining town located south of here."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 3)
        {
            listmax = 0;
            buff = lang(
                u8"私達はヴィンデールの森からの使者。公正なるジャビ王と会見し、森とエレアの民に降りかかる嫌疑を晴らすために、王都パルミアに向かっているの。"s,
                u8"We are messengers from Vindale. Our journey ends here in North Tyris at the great city of Palmia where we're supposed to have a talk with King Xabi, a man of fairness and compassion."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        return talk_result_t::talk_end;
    case 34:
        if (chatflag == 0)
        {
            if (gdata_tutorial_flag == 0)
            {
                buff = lang(
                    u8"見たところ君はノースティリスの人間ではないようだ。余計な世話でなければ、我々が旅を再開する前に、この土地での生活の知恵を授ける程度の時間は割けるのだが。"s,
                    u8"It looks like you aren't familiar with this land. Before we leave, I can spare a moment to teach you a few lessons."s);
                ELONA_APPEND_RESPONSE(
                    1,
                    lang(
                        u8"チュートリアルを開始する"s,
                        u8"I would like to play the tutorial."s));
                ELONA_APPEND_RESPONSE(
                    0,
                    lang(u8"余計な世話だ"s, u8"I can take care of myself."s));
            }
            if (gdata_tutorial_flag == 1)
            {
                listmax = 0;
                buff = lang(
                    u8"移動方法はもうわかっているだろうが、もしカーソルキーを使っているのならば、できるだけテンキーでの移動に変えたほうがいいだろう。テンキーの周りには、床のアイテムを取得する0キー、その場で足踏みする5キー、そして射撃などのターゲットを指定できる*キーがあるからな。"s,
                    u8"Pray tell me at least you know how to move. Sure, pressing cursor keys will do. But it's better to use a key pad if you have one. By using a key pad, you can easily access keys which are used frequently. Like [0] for picking up stuff, [5] for passing a turn and [*] for targeting."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"全ての行動はz,x,cの三つのキーから選択できる。zキーでは主に魔法やスキルなどの動作、xキーではアイテムの操作、cキーでは能力の確認や装備の変更ができるぞ。"s,
                    u8"Although there're many actions you can perform, basically you can access them by using only 3 keys, [z],[x] and [c]."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"まずはxキーを使って、最も基本的で重要な行動である食事をしてみよう。注意しておけ、空腹になると体力の回復速度が下がり、餓死寸前になると当然体力は減って行くからな。食料は店で買ったり、栽培したり、たまに敵が残す死体を食べることもできる。"s,
                    u8"Let's try them now. First, you need food to live. If your stomach is empty, you will lose Hp and your action speed slows down. Make sure you always have enough food in your inventory."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                buff = lang(
                    u8"君の足元に食料を置いた。xキーを押して、テンキーを使い「食べる」のメニューに移動して、足元のものを選択するんだ。"s,
                    u8"Here, you can have this meat. Press [x], then press [9] a few times to select the <Eat> menu. Once there, select the meat on the ground."s);
                ELONA_APPEND_RESPONSE(0, lang(u8"わかった"s, u8"Alright."s));
                ELONA_APPEND_RESPONSE(3, lang(u8"食べた"s, u8"I ate it."s));
            }
            if (gdata_tutorial_flag == 2)
            {
                listmax = 0;
                buff = lang(
                    u8"zキーでは、魔法やスキルを使用したり、体当たりや採掘など、やや特殊な行動を行うことができる。体当たりは、鍵のかかったドアを壊したり、果実を木から落としたい時に実行するといい。"s,
                    u8"You can perform skills or other actions including bashing and digging by pressing [z]. Here's a tip. You can bash doors to break locks and trees to get some fruits. It can be used to wake someone, but surely they won't be happy."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"zキーの他にも、スペースキーの活用法を覚えておこう。スペースキーは、足元にあるものに応じて自動的に行動を選択してくれるキーだ。例えば足元に階段があれば昇り降りを、宝箱があれば「開く」を、祭壇があれば「捧げる」をなど、自動的に選択してくれる便利なキーだ。"s,
                    u8"Also, remember that [space] key is a very useful key. When there's an object under your foot, it automatically chooses a suitable action for you."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                buff = lang(
                    u8"そうだな… 「穴掘り」実際に試してみようか。穴掘りは、道を短縮したり、鉱石を採掘したり、家のレイアウトを変える時に使う。とりあえず適当な壁の前に立ち、zキーを押して穴を掘ってみてくれ。"s,
                    u8"Let's try it now. Try digging some walls by pressing [z] and choosing <dig>."s);
                ELONA_APPEND_RESPONSE(0, lang(u8"わかった"s, u8"Okay."s));
            }
            if (gdata_tutorial_flag == 3)
            {
                txt(lang(
                    u8"何かが足元に転がってきた。"s,
                    u8"Something is put on the ground."s));
                flt();
                itemcreate(-1, 14, cdata[0].position.x, cdata[0].position.y, 0);
                inv[ci].identification_state =
                    identification_state_t::completely_identified;
                listmax = 0;
                buff = lang(
                    u8"どうやら何かを掘り当てたようだな。"s,
                    u8"Looks like you found something."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata_tutorial_flag = 4;
            }
            if (gdata_tutorial_flag == 4)
            {
                listmax = 0;
                buff = lang(
                    u8"多くのアイテムは、その本当の価値を知るためには「鑑定」をする必要がある。街にいる鑑定者に頼んだり、鑑定の巻物や、魔法を唱えることで鑑定はできる。未鑑定の品は店での売価が低くなり、中には呪われた装備、危険な効果のポーションや巻物もあるので注意が必要だ。"s,
                    u8"Many items need to be identified before you can know what exactly they are. You can identify items by reading some scrolls or asking a wizard in a town. Remember that using unidentified potions or scrolls is very dangerous. "s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"武器や防具は、長い間所持していると簡単な鑑定がされるが、 装備の持つ魔力や本当の性能を知るためには、やはり鑑定が必要だ。強力な力を秘めたアイテムの中には、上位の鑑定を必要とするものもあるので、未判明のまま店に売ってしまうことは賢明ではないだろう。"s,
                    u8"Weapons and armor also need to be identified. If you carry them long enough, you will get a hunch as to how good they are. But to gain full knowledge of the items, you need to identify them."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                buff = lang(
                    u8"では、今足元に置いた鑑定の巻物をxキーで読み、その金塊を鑑定してみるんだ。"s,
                    u8"Now I'll give you a scroll of identify. Read it by using [x] and identify the gold bar you just found."s);
                ELONA_APPEND_RESPONSE(
                    0,
                    lang(
                        u8"結果は想像がつくが、やってみるか…"s,
                        u8"Alright, I will try."s));
                ELONA_APPEND_RESPONSE(4, lang(u8"鑑定した"s, u8"Done..."s));
            }
            if (gdata_tutorial_flag == 5)
            {
                buff = lang(
                    u8"アイテムを装備するには、cキーから装備画面を呼び出せばいい。呪われたアイテムを装備してしまうと、装備が外せなくなるだけではなく、様々な悪い効果が発生する。その弓も呪われているので、解呪の巻物で呪いをといてくれ。"s,
                    u8"To equip weapons or armor, press [c] and press [9] to select [Wear]. Note that if you wear cursed equipment, they can't be removed normally and cause some unwelcome effects. That bow is cursed. Use this scroll of uncurse to uncurse it."s);
                ELONA_APPEND_RESPONSE(0, lang(u8"わかった"s, u8"Will do."s));
                ELONA_APPEND_RESPONSE(
                    5, lang(u8"装備も解呪も終わった"s, u8"All done."s));
            }
            if (gdata_tutorial_flag == 6)
            {
                p = chara_find(3);
                if (p != 0)
                {
                    listmax = 0;
                    buff = lang(
                        u8"どうした？ まだ全てのプチを倒していないぞ。"s,
                        u8"Kill them all."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_end;
                }
                listmax = 0;
                buff = lang(u8"上出来だ。"s, u8"Well done."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata_tutorial_flag = 7;
            }
            if (gdata_tutorial_flag == 7)
            {
                listmax = 0;
                buff = lang(
                    u8"ノースティリスの地理について少し説明しよう。シエラ・テールには幾多の国が存在するが、ノースティリスはどの国の支配も受けておらず、《ネフィア》と呼ばれる迷宮群が存在する特殊な場所だ。この地では、地殻変動とともに新しい迷宮がしばしば生成される。"s,
                    u8"Let's learn a little history of North Tyris. This sacred land governed by Palmia is known for ancient ruins <<Nefia>>. Occasionally new ruins are found and lost by erratic movements of the earths crust."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"迷宮の主を倒すと貴重な物資や財宝が手に入るため、冒険者にとっては格好の収入源になるわけだ。迷宮に辿り着くと、その場所の危険度が表示される。危険度が自分のレベルより高い場所を探索することは、まず避けたほうがいいだろう。"s,
                    u8"A lord lives at the lowest layer of these ruins, protecting great treasures and therefore attracts numerous adventurers. However, avoid those ruins which exceed your current level. You may gain a lot, but you may lose your life."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                flt();
                itemcreate(
                    -1, 240, cdata[0].position.x, cdata[0].position.y, 0);
                inv[ci].param1 = 35;
                inv[ci].param2 = 25;
                flt();
                itemcreate(
                    -1, 636, cdata[0].position.x, cdata[0].position.y, 2);
                txt(lang(
                    u8"何かが足元に転がってきた。"s,
                    u8"Something is put on the ground."s));
                listmax = 0;
                buff = lang(
                    u8"迷宮に落ちている宝箱の開け方を知っておく必要があるな。足元に宝箱を置くので、xキー、またはスペースキーで開けてみるんだ。"s,
                    u8"You might find chests containing loot in ruins. There's one nearby, open it."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, lang(u8"わかった", u8"Okay."));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata_tutorial_flag = 8;
                return talk_result_t::talk_end;
            }
            if (gdata_tutorial_flag == 8)
            {
                listmax = 0;
                buff = lang(
                    u8"鍵が掛かっているだろう？宝箱の鍵は、ロックピックを所持していて、鍵開けの技術が開錠に必要な値に達していないと、解除することはできない。君の技量では、おそらくその宝箱を開けることはできないな。宝箱はダンジョンに落ちていることもあるが、生憎と重い代物なので、開けられない時は諦めるしかないだろう。気をつけろ…宝箱に押しつぶされて無様な死をさらした冒険者を、私は何度となく見てきている。"s,
                    u8"Notice the chest has a lock? Locked chests require sufficient lockpick skill and lockpicks to open. You need to practice to open that chest. Be aware, those chests are heavy and trust me, give up if you can't open them when you're in dungeons. I saw a fool running around with a chest on his back and he got killed."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"宝箱に限らず、荷物を持ちすぎると速度にペナルティが課せられるため注意が必要だな。必要のないアイテムは、家に保管しておくといい。"s,
                    u8"As you explore dungeons, your backpack may get heavier. Remember to leave stuff you don't need in your house. Overweight will slow your movement."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"最後に、家について説明しておこう。家はアイテムを保管したり、安全に魔法を学んだり、また単に装飾して楽しむために利用できる。家の権利書を購入できるようになれば、ノースティリスの好きな場所に家を建てることができるだろう。ただし、家は一つしか持てない。"s,
                    u8"Finally, I'm going to explain a bit about your house. As you already know, you can safely store items in your house. And the salary chest periodically gets filled with some gold and items. Eventually you might be able to buy a new house."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"家の中にあるハウスボードを使うことで、壁を作ったり、床の模様を変えたり、滞在者を募ったりできるぞ。後で試してみるといい。"s,
                    u8"You can do several things by using a house board in your house. Try it later."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata_tutorial_flag = 99;
            }
            if (gdata_tutorial_flag == 99)
            {
                listmax = 0;
                buff = lang(
                    u8"よくやった。これでノースティリスで生活するための、基本的な知識は身に付いたわけだ。自分の状態を把握し、慎重に行動すれば、瀕死の状態を高慢なエレアに拾われ、講釈をたれられることも、もうないだろう（ロミアスはニヤリと笑った）。"s,
                    u8"Alright, we're finished. You should already know how to survive in North Tyris by now."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"まだ目的が定まっていないのなら、南のヴェルニースを訪れるといい。ネフィアの迷宮群を巡るのも、貴重な経験になるだろう。この世界で何を見て、如何な足跡を残すか決めるのは、君自身だ。"s,
                    u8"(You've finished the tutorial!)"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata_tutorial_flag = -1;
                return talk_result_t::talk_end;
            }
            if (gdata_tutorial_flag == -1)
            {
                buff = lang(u8"まだ、何か用があるのか？"s, u8"What?"s);
                ELONA_APPEND_RESPONSE(0, lang(u8"何も"s, u8"Nothing."s));
            }
            if (gdata_tutorial_flag == 0 || gdata_tutorial_flag == -1)
            {
                ELONA_APPEND_RESPONSE(
                    2,
                    lang(
                        u8"わが家から出て行ってほしい"s,
                        u8"Get out of my house!"s));
            }
            talk_window_query();
        }
        if (chatval == 1)
        {
            listmax = 0;
            buff = lang(
                u8"賢明な判断だな。まずは最も基本的な動作から教えよう。"s,
                u8"A wise choice. I will start from the beginning."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(-1, 204, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].subname = 9;
            inv[ci].identification_state =
                identification_state_t::completely_identified;
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            gdata_tutorial_flag = 1;
            return talk_result_t::talk_unique;
        }
        if (chatval == 2)
        {
            tc = chara_find(33);
            if (tc == 0 || cdata[tc].state != 1)
            {
                tc = chara_find(34);
                hostileaction(0, tc);
                listmax = 0;
                buff = lang(
                    u8"ラーネイレ…？ どこにいったんだ？ まさか貴様！"s,
                    u8"You...you scum!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            listmax = 0;
            buff = lang(""s + cdatan(0, 0) +
                    u8"の言うとおり、私達に残されている時間は少ないわ。こうしている間にも、新王国のかの者の計画は着実に進んでいる… 出発しよう、ロミアス。"s,
                ""s + cdatan(0, 0) +
                    u8" is right. The time left for us is scarce. We need to depart, Lomias."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"ああ、わかった。パルミアまでは長い旅路だ。一時であれ休息をとれて良かったのかも知れないな。"s,
                u8"Yes. Palmia is still far away. Perhaps, It was fortunate that we could have a little rest before everything begins."s);
            tc = tc * (chara_find(34) == 0)
                + (chara_find(34) != 0) * chara_find(34);
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"また巡り会う時まで、"s + cdatan(1, 0)
                    + u8"、あなたに風の加護のあらんことを。"s,
                u8"Farewell..until we meet again. May the blessing of Lulwy be with you."s);
            tc = tc * (chara_find(33) == 0)
                + (chara_find(33) != 0) * chara_find(33);
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            chara_vanquish(chara_find(33));
            chara_vanquish(chara_find(34));
            txt(lang(
                u8"二人は荷物をまとめ洞窟を後にした。"s,
                u8"Lomias and Larnneire leave the cave."s));
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                flt();
                flttypemajor = 60000;
                itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            }
        }
        if (chatval == 3)
        {
            listmax = 0;
            buff = lang(
                u8"…本当に食べてしまったのか？"s,
                u8"...err..you really ate that thing? Oh well.."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, lang(u8"えー"s, u8"What!"s));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"食料以外のアイテムも、同様にxキーで操作することになる。例えば巻物や魔法書は「読む」のメニューから、杖は「振る」のメニューから使用できる。"s,
                u8"You can also use other items by pressing [x]. For example, if you want to read a book, press [x], hit [9] a few times to select the <Read> menu, then choose a book you want to read."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            if (jp)
            {
                listmax = 0;
                buff = lang(u8"次はzキーでの行動について説明しよう。"s, ""s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            gdata_tutorial_flag = 2;
            return talk_result_t::talk_unique;
        }
        if (chatval == 4)
        {
            listmax = 0;
            buff = lang(
                u8"（ロミアスはにやりと笑った。どうやら、この偽物の金塊は彼がいつの間にか埋めたらしい…）"s,
                u8"(Lomias grins. Looks like he buried it unnoticed.)"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"次は戦闘について教えるが、戦う前にまずアイテムを装備し、準備を整えなければならない。使い古しだが、君のために弓と矢を用意した。射撃武器のほとんどは、例えば銃なら弾丸のように、対応した矢・弾を装備する必要がある。"s,
                u8"Okay, I will now tell you how to fight. Before the combat starts, you need to equip weapons. Take my old bow and arrows and equip them."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(-1, 58, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].curse_state = curse_state_t::cursed;
            flt();
            itemcreate(-1, 61, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].curse_state = curse_state_t::none;
            flt();
            itemcreate(-1, 363, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].identification_state =
                identification_state_t::completely_identified;
            inv[ci].curse_state = curse_state_t::blessed;
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            gdata_tutorial_flag = 5;
            return talk_result_t::talk_unique;
        }
        if (chatval == 5)
        {
            listmax = 0;
            buff = lang(
                u8"…よし、いよいよ戦闘の説明だ。"s,
                u8"Good. Now listen carefully."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"相手を打撃で攻撃するには、単に相手の方向のキーを押すだけだ。射撃も、zキーから射撃を選択するだけで、一番近くの敵を自動的に攻撃する。攻撃する敵を予め指定したいときは*キーを押せばいい。"s,
                u8"By moving towards a target, you automatically attack it with your close range weapon. To use your long range weapon, you can either press [z] and choose [Shoot] or simply press [f] (Fire). You will shoot a nearby enemy. If you want to change your target, press [*]."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"では、訓練用のモンスターを召喚するぞ。可能なら、使い勝手を知るために射撃で倒してみてくれ。ただし、弓は近接して打っても威力が低いので注意が必要だ。危なくなった時のために、治療薬を足元に置いておこう…必要ないとは思うが。ポーションの飲み方はわかるな？…そう、xキーだ。"s,
                u8"Get ready. I will summon some weak monsters. Kill them with your bow if possible. Try to stay away from the enemies as bows aren't effective in close range. I've dropped a few potions in case you get hurt. You know how to use them right? Yes, use [x] key."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            txtef(9);
            txt(lang(
                u8"ロミアスは隠し持っていたプチを放った。"s,
                u8"Lomias releases tiny cute creatures."s));
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                flt();
                chara_create(-1, 3, cdata[0].position.x, cdata[0].position.y);
                cdata[rc].does_not_search_enemy() = true;
            }
            flt();
            itemcreate(-1, 68, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].identification_state =
                identification_state_t::completely_identified;
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            gdata_tutorial_flag = 6;
        }
        return talk_result_t::talk_end;
    case 79:
        if (gdata_main_quest_flag == 200)
        {
            listmax = 0;
            buff = lang(
                u8"王の死に続き、世界の崩壊の始まり…パルミアは…シエラ・テールは困難な時代にいます。このまま、イルヴァは最後を迎えてしまうのでしょうか。"s,
                u8"The tragedy of our king, and the collapse of our world, Palmia is...Sierre Terre is in difficult times."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_main_quest_flag < 90)
        {
            listmax = 0;
            buff = lang(
                u8"パルミアは歴史ある自由と文化の国。大アセリア大陸の戦乱から離れ、静かに育ってきた国です。王制政治が廃止された今でも、この平和を培った代々の王と夫であるジャビ王に、民は忠誠を尽くしてくれています。"s,
                u8"Palmia is an old and historical kingdom which respects peace and freedom. The royalism has been obsoleted long time ago, but people still carry loyalty to the old kings and my husband, King Xabi."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        else
        {
            listmax = 0;
            buff = lang(
                u8"王の悲報にパルミアは衝撃を受けています。あの方のいない王座は、なんと冷たく感じられることでしょう…"s,
                u8"The whole kingdom is devastated to hear the tragic news of our king. This throne... it feels very cold without him."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        return talk_result_t::talk_end;
    case 80:
        if (gdata_main_quest_flag >= 60)
        {
            listmax = 0;
            buff = lang(
                u8"汝の活躍を楽しみにしておるぞ。"s,
                u8"Any assistance you provide to us will be most welcome."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_main_quest_flag == 50)
        {
            listmax = 0;
            buff = lang(
                u8"今の時勢、信頼に足る者の剣を遊ばせておくのは惜しい。もしパルミアの元で働く意志があるのなら、城の図書室にいるエリステアを訪ねるがよい。十分な報酬と名誉を約束しよう。"s,
                u8"In times like these, we can't afford to let those we can trust sit idly on their swords. If you're willing to serve Palmia, then you should pay a visit to Erystia in the library. We will be sure to reward you with honor and riches commiserate with your sacrifice."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_main_quest_flag == 40)
        {
            gdata_main_quest_flag = 50;
            listmax = 0;
            buff = lang(
                u8"斥候からの知らせを預かっていると？…よかろう、その者の書簡をわしの手元へ。"s,
                u8"What's that you say? You have a message from one of our scouts? ...Very well then, let me see it."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            update_screen();
            fade_out();
            gsel(4);
            pos(0, 0);
            picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
            gsel(0);
            listmax = 0;
            buff = lang(
                u8"…なるほど、恐れていたことが現実になったというわけだな。知らせにあるよう、悪しき者がレシマスに眠る秘宝を狙うのであれば、パルミアの王の名誉にかけてそれを阻止せねばなるまい…"s +
                    cdatan(0, 0) +
                    u8"とやら、大儀であった。直ちに謝礼を用意させようではないか。"s,
                u8"I see... then what we feared has indeed come to pass. If evil has set its sights on the artifact hidden within the depths of Lesimas, then for the honor of our King we are bound to stop it... You must be tired, "s +
                    cdatan(0, 0) +
                    u8". Give me a moment to prepare appropriate compensation for your efforts today."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 2500);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
            flt();
            itemcreate(-1, 559, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(-1, 621, cdata[0].position.x, cdata[0].position.y, 0);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            return talk_result_t::talk_unique;
        }
        break;
    case 139:
        if (gdata_main_quest_flag == 20)
        {
            gdata_main_quest_flag = 30;
            listmax = 0;
            buff = lang(
                u8"…そこの御人…頼みが…頼みがある…私はパルミアの斥候…王の命令でレシマスに潜んでいた者だ…"s,
                u8"You...you there, listen to me. *cough* *cough* I-I'm a scout of Palmia...I've been investigating on Zanan's strange activities in Lesimas.... *cough* I have a favor to ask..."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"詳しく説明する体力は…私には…もう残っていない…ジャビ王にこの書簡を…届けて頂きたい…二つの大国の衝突を…シエラ・テールの…危機を…防ぐために…"s,
                u8"T-There's no time left for me to explain all....my wounds are... *cough* Listen, Sierre Terre is in danger...this letter..this letter...this is our only hope...."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"…う、うぅ…貴方を…信じる以外にもう希望はない…私の所持品は…自由にして構わない…どうか、この知らせを…パルミアに…"s,
                u8"I have no choice but to trust you.... *cough* bring the letter to Palmia.... I-I beg you...You can take everything I have on me...so... plea..s.."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
                flttypemajor = fltsetdungeon();
                itemcreate(
                    -1, 0, cdata[tc].position.x, cdata[tc].position.y, 0);
            }
            flt();
            itemcreate(
                -1,
                54,
                cdata[tc].position.x,
                cdata[tc].position.y,
                1000 + rnd(200));
            flt();
            itemcreate(-1, 55, cdata[tc].position.x, cdata[tc].position.y, 3);
            flt();
            itemcreate(-1, 239, cdata[tc].position.x, cdata[tc].position.y, 0);
            inv[ci].param2 = 0;
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャビ王への書簡を受け取った。ジャーナルが更新された。"s,
                u8"You receive a letter to the king Xabi. Your journal has been updated."s));
            txt(lang(
                cdatan(0, tc) + u8"は静かに息絶えた…"s,
                cdatan(0, tc) + u8" dies silently..."s));
            chara_vanquish(tc);
            return talk_result_t::talk_end;
        }
        break;
    case 142:
        if (gdata_main_quest_flag == 200)
        {
            if (jp)
            {
                listmax = 0;
                buff =
                    u8"私達は…失敗してしまったのですね、サイモアの陰謀を止めることに。あなたが《常闇の眼》を入手するために冒した危険も、カラムの命も、今となっては何の意味があったのでしょう。"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff =
                    u8"ゆっくりと死に行く世界の中で、私達は無力感と罪を抱えて生きています。森を忌み嫌い、あるいは迫害を見ぬふりをしてきた私達が、サイモアだけを責めることなどできません。いっそのこと、あの時森とともに…"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff =
                    u8"ごめんなさい、つまらないことを聞かせてしまって。あなたは…あなたの目には…まだ希望の光が宿っている。"s
                    + cdatan(1, 0) + cdatan(0, 0)
                    + u8"、あなたはその運命の先に何を見ているの？"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            else
            {
                listmax = 0;
                buff = u8"You've done well."s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            return talk_result_t::talk_end;
        }
        if (gdata_main_quest_flag == 120)
        {
            listmax = 0;
            buff = lang(cdatan(0, 0) +
                    u8"、遂に三つの魔石を揃えたのですね。私達の調査によれば、魔石はレシマスの秘宝の間への扉を開く鍵となるはず。しかし、レシマスの奥深くには恐ろしい魔物が巣食い、その場所が何階にあるかまでは判明していません。"s,
                u8"It looks like you've finally managed to acquire all three of the stones, "s +
                    cdatan(0, 0) +
                    u8". According to the information we've learned during the excavation, these stones are the key that will unlock the deepest reaches of Lesimas. However, be aware that terrifying monsters lurk in the abyss of Lesimas, and we have no idea how deep those caverns go."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"あなたの任務…おそらくは最後の任務は、決して易しいものではなく、失敗も許されません。レシマスの探索を進め、秘宝の間を見つけてください。そして、《常闇の眼》を地上に持ち帰り、ザナンの陰謀を阻止するのです。"s,
                u8"This will be your last mission. This will be no easy task, but failure is not an option. It's up to you to complete the excavation of Lesimas and find the room where the codex is kept. If you can't retrieve the <Origin of Vice> we will never be able to uncover the conspiracy Zanan has set into motion."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"カラムの言葉が正しければ、秘宝を守るのは今は亡きザシム王の従弟ゼーム。ゼームは名うての魔術師としても知られていました。彼が生きながらえているのも何らかの魔力によるものでしょう。心して望んでください。"s,
                u8"If what Karam told us is true, the codex will be guarded by the late king Zashim's cousin, Zeome. Zeome was known to have been a very powerful warlock. In his day, he was by far the most powerful sorcerer alive. I wouldn't dare confront him unless you are extremely well prepared."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"あなたの働きには、感謝の言葉だけでは報いきれません。この指輪は、スターシャ様からの贈り物です。あなたの冒険の成功を祈っています。"s,
                u8": Words alone are not enough to express our gratitude for all that you have done. This ring is a gift from Queen Stersha. We are praying for your success, "s
                    + cdatan(0, 0) + u8"."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            snd(44);
            txtef(2);
            txt(lang(
                u8"レシマス25階の鍵を受け取った。ジャーナルが更新された。"s,
                u8"You receive a key of Lesimas 25th level. Your journal has been updated."s));
            flt();
            itemcreate(-1, 360, cdata[0].position.x, cdata[0].position.y, 0);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            gdata_main_quest_flag = 125;
            return talk_result_t::talk_end;
        }
        if (gdata_main_quest_flag == 105)
        {
            listmax = 0;
            buff = lang(cdatan(0, 0) +
                    u8"、あなたの帰還を待っていました。カラムは無事に…いえ、その顔を見れば想像はつきます。私達の救助は遅すぎたのですね…。"s,
                u8"I've been waiting for you to return, "s + cdatan(0, 0) +
                    u8". I hope that Karam is... no, I can tell just by looking at you. Then our rescue attempt was too little too late."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            update_screen();
            fade_out();
            gsel(4);
            pos(0, 0);
            picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
            gsel(0);
            listmax = 0;
            buff = lang(
                u8"…カラムの言葉、確かに受け取りました。《常闇の眼》という古宝の伝承は、私も本で読んだことがあります。それは、イルヴァの大地の上に築かれた全ての歴史の真相を網羅していると伝えられています。もしカラムが危惧していたように、ザナンのサイモアが自らの説の誤りを葬らんとするためレシマスの秘宝を狙っているとしたら、私達はそれを阻止しなければなりません。"s,
                u8"Well take Karam's message to heart then... I remember reading about the <Origin of Vice> in one of these books. I believe it referred to the codex as an exhaustive account of the history of all things in Irva. If, as Karam suspected, Saimore is trying to acquire the codex in order cover up gaps in his story we can't allow him to succeed."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"…王の悲報はもう耳にしているでしょう。都の土は涙で濡れていようとも、今の私達に喪に服している時間はありません。カラムと、そして王の意思を継ぐためにも。"s,
                u8"I'm sure you've already heard the tragic news about the king. All of Palmia is heartbroken by the king's demise, but we can't afford to spend our time mourning right now. We have to push on, for Karam... and for the king's sake."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"あなたの次の任務は、三つの魔石の入手です。魔石には、レシマスの秘密を解く何らかの力が秘められていると伝えられています。魔石の所在は判明していますが、どこも危険な場所ばかり。まずは、各地を探索し、経験を積んでから臨んだほうがいいでしょう。"s,
                u8"Your next task is to retrieve the three magic stones. It's written in several of our historical accounts that the stones are the key to unlocking the secrets of Lesimas. We already know where the stones are located, but actually getting the stones is definitely easier said than done. First, you should scout the areas, gather info, and build your strength."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"探索に必要な情報がある時は、いつでも私に話しかけてくださいね。帰還したばかりなのに酷ですが、あなたに期待しています。"s,
                u8"Please come see me anytime you get information that would be useful to the expedition. I know you've just returned and we're asking an awful lot of you, but I don't have any other choice."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            snd(44);
            txtef(2);
            txt(lang(
                u8"レシマス17階の鍵を受け取った。ジャーナルが更新された。"s,
                u8"You receive a key of Lesimas 17th level. Your journal has been updated."s));
            gdata_main_quest_flag = 110;
            return talk_result_t::talk_end;
        }
        if (gdata_main_quest_flag >= 60)
        {
            buff = lang(u8"あら、"s + cdatan(0, 0) +
                    u8"。レシマスの調査は進んでいるかしら？ 何か必要な情報があれば、何でも聞いてください。"s,
                ""s + cdatan(0, 0) +
                    u8", how's your investigation going? Ask anything you'd like to know."s);
            ELONA_APPEND_RESPONSE(
                6, lang(u8"レシマスについて"s, u8"Tell me about Lesimas."s));
            ELONA_APPEND_RESPONSE(
                5,
                lang(u8"任務について"s, u8"Tell me about the mission again."s));
            if (gdata_main_quest_flag >= 100 && gdata_main_quest_flag <= 120)
            {
                ELONA_APPEND_RESPONSE(
                    3,
                    lang(
                        u8"古城について"s,
                        u8"Tell me about the ancient castle."s));
                ELONA_APPEND_RESPONSE(
                    2,
                    lang(
                        u8"灼熱の塔について"s,
                        u8"Tell me about the tower of infernos."s));
                ELONA_APPEND_RESPONSE(
                    1,
                    lang(
                        u8"死者の洞窟について"s,
                        u8"Tell me about the crypt of the damned."s));
            }
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            talk_window_query();
            if (chatval == 6)
            {
                listmax = 0;
                buff = lang(
                    u8"ネフィアの迷宮群の一つレシマスは、パルミアの歴史と大きな関わりがあります。エウダーナがネフィアの秘宝の一つにより繁栄を約束されたように、第三代の王ザシムと従弟ゼームもレシマスの秘宝を求め、調査隊を繰り出していました。"s,
                    u8"Lesimas is one of the numerous ruins of Nefia. It is a significant part of the history of Palmia. The Eulderna sought to bring themselves prosperity using one of the treasures of Nefia, so the third king, Zashim and his cousin Zeome organized an excavation of Lesimas."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"そしてある日、ついに調査隊の朗報を受けた王と従弟は、レシマスの最下層に赴き、秘宝の眠る部屋へと足を踏み入れたのです…しかし数刻の後、部屋から出てきたのはザシム王一人だけでした。ザシム王は側近にこう言ったと伝えられています。"s,
                    u8"Eventually the king and his cousin received word that the excavation had been completed, so they descended to the deepest reaches of Lesimas. Together they set foot into the darkened room where the codex was said to reside, yet after some number of hours, King Zashim emerged from the chamber alone. As the legend goes, King Zashim said the following words to his aides."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"「それは強き者の手の内では決して輝くことはない。弱き者の手の内では黄金のごとくまばゆいが、その輝きを他の者に見せることはできない。この秘宝は、常闇の中で永遠に眠っているべきものなのだ。直ちに部屋を封印するがよい。従弟はもはや帰っては来るまい」"s,
                    u8"\"In the hands of the mighty it was dull and lifeless, devoid of magic... yet... in the hands of the meek it shone with a brilliant golden light that defies description. But no matter how I tried, I could not show that light to anyone else. The codex was meant to remain in these depths for all of eternity. We should seal this place off. My cousin will never return from these caves.\""s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"秘宝が眠る部屋は魔術により封印され、封印の鍵となる三つの魔石は、それぞれ最も強大で邪悪な存在の元に送られたといいます。魔石の真の価値は知らさずに。"s,
                    u8"And so, they sealed the cavern with powerful magic and bound that seal to three magic stones. They gave each stone to a powerful guardian and sent them to three separate strongholds to watch over the stones. I don't believe the guardians knew the true value or purpose of the stones. "s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"以来、パルミアの代々の王家は、ザシム王の意思を引き継ぎ、洞窟にはもう何もないかのように、他の国々の目を欺いてきたのです。"s,
                    u8"Since that day, the passing generations of Palmia's royal family have preserved King Zashim's mandate and we've always deceived the other nations into believing there was nothing of value in Lesimas."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (chatval == 5)
            {
                if (gdata_main_quest_flag >= 125)
                {
                    listmax = 0;
                    buff = lang(
                        u8"レシマスの探索を進め、秘宝の間を見つけてください。あなたの任務は、《常闇の眼》を地上に持ち帰ることです。"s,
                        u8"Complete the excavation of Lesimas and find the room where the codex is kept. And retrieve the <Origin of Vice>."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    listmax = 0;
                    buff = lang(
                        u8"カラムの言葉が正しければ、秘宝を守るのは今は亡きザシム王の従弟ゼーム。ゼームは名うての魔術師としても知られていました。彼が生きながらえているのも何らかの魔力によるものでしょう。心して臨んでください。"s,
                        u8"If what Karam told us is true, the codex will be guarded by the late king Zashim's cousin, Zeome. Zeome was known to have been a very powerful warlock. In his day, he was by far the most powerful sorcerer alive. I wouldn't dare confront him unless you are extremely well prepared."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_unique;
                }
                if (gdata_main_quest_flag >= 110)
                {
                    listmax = 0;
                    buff = lang(
                        u8"あなたの任務は、三つの魔石の入手です。魔石には、レシマスの秘密を解く何らかの力が秘められていると伝えられています。魔石の所在は判明していますが、どこも危険な場所ばかり。まずは、各地を探索し、経験を積んでから臨んだほうがいいでしょう。"s,
                        u8"Your next task is to retrieve the three magic stones. It's said that the stones are the key to unlocking the secrets of Lesimas. We already know where the stones are located, but all three locations are extremely dangerous. First, you should scout the areas, gather info, and build your strength."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_unique;
                }
                listmax = 0;
                buff = lang(
                    u8"あなたの任務は、レシマスに赴き、冒険者カラムとの接触を試みることです。彼から最後に連絡があったのは、レシマスの16階。おそらくは、より深層に探索の手を広げているでしょう。彼の足取りをつかみ、私に報告してください。"s,
                    u8"Your duty will be to penetrate into Lesimas and make contact with <Karam>. In the last report we received from him, he told us he was on the 16th floor. If you can find him, perhaps we can get this excavation back on track. Godspeed, "s
                        + cdatan(0, 0)
                        + u8", find out what happened to <Karam>."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (chatval == 3)
            {
                listmax = 0;
                buff = lang(
                    u8"古城の宝物庫には、数々の財宝とともに《覇者の魔石》が眠っていると伝えられています。ヴェルニースを南に下った閑静な森の中に佇むこの城は、古の王族により建てられました。しかし王都がパルミアに移り、廃墟となった城は、長らくならず者の拠点として使われるように…"s,
                    u8"The <King's Magic Stone>, along with numerous other treasures, sleeps deep in the recesses of the vaults of the Ancient Castle, which was built by a long forgotten generation of the royal family. However, the royal family eventually relocated to Palmia and the former throne of the kingdom fell into disrepair and decay. It has been ages since anyone even set foot in the old castle..."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"一世紀前に《古城の主ワイナン》が占拠してからは、ダルフィの悪漢でさえ近づかない恐ろしい場所として知られるようになりました。危険度はレシマスの１７階相当です。"s,
                    u8"After <Lord Wynan> took charge of the castle in the first century, even the thugs of Derphy became too scared to approach the castle. The danger level in the castle is roughly equivalent to the 17th floor of Lesimas."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"噂では、《ワイナン》がまだ生きて王座に君臨しているとか…彼は生粋の戦士で、その手に持つ槍斧《ランキス》は相対するものの生命を吸い取ると怖れられています。地獄への耐性か、間合いをとる手段なくして彼と対するのは賢明とはいえませんね。"s,
                    u8"It is rumored that <Wynan> still rules the throne along with his personally trained army. Legends tell that the deadly halberd he carries, <Rankis>, can drain the life from his enemies with the greatest of ease. It would be wise to boost your resistance to nether... oh, and bear in mind that unless you can time your actions wisely he'll devour you like a dog."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (chatval == 2)
            {
                listmax = 0;
                buff = lang(
                    u8"パルミアを出て北の未開の地を越えていくと、真紅に燃え盛る灼熱の塔が見えます。この塔の守護者、《赤き義眼のクルイツゥア》と呼ばれる魔女が、《賢者の魔石》を所持しているはずです。"s,
                    u8"If you head north from Palmia, through the untamed lands, you will eventually see a tower blazing with an aura of flames. The guardian of the tower, a powerful witch named <Quruiza the Red-eyed Deceiver>, watches over the <Sage's magic stone>. "s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"《クルイツゥア》の強力な魔法だけでなく、彼女の僕であり夫である《鋼鉄竜コルゴン》の力も恐るべきものです。"s,
                    u8"Quruiza's magic is not the only thing you have to fear either, her husband, the <Steel Dragon Corgon> has pledged his strength to her defense. No doubt you'll have to face him as well."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"言うまでもないですが、この塔を探索するには、何らかの手段で火への耐性を得る必要があるでしょう。もし体力を失っていくようであれば、耐性を高めてから挑戦したほうが無難です。危険度はレシマスの１５階相当です。"s,
                    u8"I probably don't need to tell you this, but if you plan to brave the tower, you'll need some sort of powerful resistance to heat and flames. If you find you can't hack it inside, I'd suggest you find some way to protect yourself from the heat before venturing back inside. The danger level in the tower is roughly equivalent to the 15th floor of Lesimas. "s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (chatval == 1)
            {
                listmax = 0;
                buff = lang(
                    u8"《愚者の魔石》が眠っているとされる死者の洞窟は、最も危険な場所です。多くの名のある冒険者が命を落とし、不死者となりこの洞窟の中をさ迷っています。"s,
                    u8"The <Crypt of the Damned> is an ancient cave where the walking dead have amassed in droves. It is the most dangerous of the three strongholds. Countless famous adventurers have lost their lives in the crypt, doomed to wander its halls for all eternity as undead."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"魔石はこの洞窟を支配する《闇の奇形イスシズル》が身に着けているはずです。死霊術使い達に崇められ、その名は大陸中で畏怖されていますが、《イスシズル》の姿や力は、全くの謎に包まれています…"s,
                    u8"I believe that the <Dark Abomination Issizzle> rules the hallowed crypts. He is a powerful necromancer and his name is feared all across the continent. Issizzle is shrouded in mystery so I'm afraid I can't tell you much more."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                listmax = 0;
                buff = lang(
                    u8"死者の洞窟はヴェルニースとパルミアを結ぶ街道の中ほどにあり、危険度はレシマスの２５階相当です。万全に準備を整えていく必要があるでしょう。"s,
                    u8"The crypt of the damned is along the road that runs between Vernis and Palmia. The danger level of the crypt is roughly equivalent to the 25th floor of Lesimas. You will need to be well prepared before venturing into the crypts."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            return talk_result_t::talk_end;
        }
        if (gdata_main_quest_flag == 50)
        {
            listmax = 0;
            buff = lang(u8"あなたが"s + cdatan(0, 0) +
                    u8"ですね。使いの者から聞いています。私はエリステア、ネフィア迷宮群の歴史の研究に携わって来ました。今は王の命によりレシマス調査隊の副長を務めていますが、洞窟に眠る多くの謎と危険な魔物の存在のために、調査は思わしく進んでいません。あなたのような冒険者に力になってもらえると心強いです。"s,
                u8"You must be "s + cdatan(0, 0) +
                    u8". I've already heard some of the soldiers talking about you. My name is Erystia, and I came to Nefia in order to research the history behind the various labyrinths here. The King has placed me in charge of the expedition to investigate Lesimas. Unfortunately, due to numerous obstacles and an abundance of hostile monsters residing in the caverns, our investigation has made little, if any, progress. It would be very reassuring if we had the strength of adventurers like you backing us up."s);
            ELONA_APPEND_RESPONSE(
                1,
                lang(
                    u8"力になる"s,
                    u8"I will gladly pledge my strength to Palmia."s));
            ELONA_APPEND_RESPONSE(0, lang(u8"断る"s, u8"I'm not interested."s));
            chatesc = 1;
            talk_window_query();
            if (chatval == 0)
            {
                listmax = 0;
                buff = lang(
                    u8"わかりました。考えが変わったら、また声をかけてください。"s,
                    u8"Fair enough... but should you change your mind feel free to come back."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            listmax = 0;
            buff = lang(
                u8"よかった。こんなことを言っては悪いけれど、城の兵士達は機転に欠けていて、調査にはあまり役に立ってくれなかったの。"s,
                u8"Fantastic. I hate to admit it, but the castle's regular soldiers have been virtually useless so far..."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"私達の目的は、レシマスを探索し、最下層にあるといわれる《秘宝》を持ち帰ることです。《秘宝》の正体とレシマスについての研究はある程度進んでいます。一度に言っても覚えられないでしょうから、必要があればその度に聞いてください。"s,
                u8"Our objective is to penetrate to the deepest reaches of Lesimas and retrieve the <codex> hidden there. Once we know the true nature of the <codex>, we can complete our research on the ancient dungeon. You probably won't remember all this after hearing it only once, so feel free to ask me about it again."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"最初の仕事として、あなたにはある人物の探索をお願いします。男の名は《カラム》。あなたと同じように、彼もレシマス探索の協力を買って出た屈指の冒険者です。調査隊の情報源として少なからぬ貢献をしていました。しかし、彼からの音沙汰がここ数週間まったくないのです。"s,
                u8"Now, on to the first order of business. We need you to investigate the fate of one of our agents. His name is <Karam>. Like you, he is one of the foremost adventurers in the land. He agreed to assist with the expedition into Lesimas. He had been contributing information to the expedition's limited intelligence on the caverns. However... we haven't heard anything from him in some number of weeks."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"あなたの任務は、レシマスに赴き、《カラム》との接触を試みることです。彼から最後に連絡があったのは、レシマスの16階。おそらくは、より深層に探索の手を広げているでしょう。彼の足取りをつかみ、私に報告してください。"s,
                u8"Your duty will be to penetrate into Lesimas and make contact with <Karam>. In the last report we received from him, he told us he was on the 16th floor. If you can find him, perhaps we can get this excavation back on track. Godspeed, "s
                    + cdatan(0, 0) + u8", find out what happened to <Karam>."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            snd(44);
            txtef(2);
            txt(lang(
                u8"レシマス4階の鍵を受け取った。ジャーナルが更新された。"s,
                u8"You receive a key of Lesimas 4th level. Your journal has been updated."s));
            gdata_main_quest_flag = 60;
            return talk_result_t::talk_end;
        }
        break;
    case 146:
        if (gdata_main_quest_flag == 90)
        {
            gdata_main_quest_flag = 100;
            listmax = 0;
            buff = lang(
                u8"…貴公は？そうか、エリステアが私を探すために…見ての通り私は傷を負い、もう動くことすらできぬ。しかし、貴公のおかげで、今まで生きながらえたことに意味を見出せるようだ。"s,
                u8"Who's there? So... Erystia sent you to find me... as you can see I'm badly wounded. I'm pretty much screwed aren't I? But then... now that you're here maybe I won't have to die in vain after all."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"貴公にお願いする。エリステアに、私の言葉を伝えてもらいたい。信じがたいことだが、レシマスの奥深くに眠る秘宝を守護しているのは、今は亡きザシム王の従弟ゼームだ。秘宝の、いやレシマスの魔に操られているのだろうか。もはや生身の人間ではあるまい。"s,
                u8"I have something to ask of you. Relay this message to Erystia for me... Tell her that she must believe me when I say that the one guarding the codex in the depths of Lesimas is none other than former King Zashim's brother, Zeome. He's the one controlling the magic of the codex... or... no, not just the codex, but the whole of Lesimas. He's no longer human... he's something... more."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"それだけではない。ザナンのサイモアが秘宝を狙っていることは知っておろう。しかし、その理由は？"s,
                u8"But it doesn't end there... You need to know that Saimore from Zanan is also after the codex. But... why?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"ゼームが持つ秘宝の名は《常闇の眼》。世界の真実を映すといわれている。レム・イドの終焉とシエラ・テールの始まりを説き、自身の説に莫大な支持を得ているサイモアが、今更秘宝を求めるのは何故だ？"s,
                u8"The codex Zeome possesses... it's called the <Origin of Vice>. They say it describes the darkness inherent in the world. But if Saimore's widely accepted story about the end of Rehm-Ido and the beginning of the era of Sierre Terre is true, then why would he be after the relic?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"サイモアの後押しにより、エレアとの戦が始まろうとしている。異形の森がレム・イドの災厄《メシェーラ》であるというのは、果たして確かなのだろうか。そして、もしサイモアの説が偽りであるとすれば、かの者の本当の目的は？…私には悪い予感がする。"s,
                u8"aimore has been pushing for war against the Eleas. The truth is that Saimore's claim that the irreverent forest destroyed the world of the era of Rehm-Ido is a carefully constructed lie and that the <Meshella> are real. But then, if Saimore's theory was just a deception meant to incite a war, then what is he really after? I have a bad feeling about all of this..."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"私の役目はこれまでだ。この傷ではどうせ地上まで辿りつけまい。この報せを早く都に…貴公に運命の神の加護のあらんことを！"s,
                u8"My role in this saga is at an end... I'll never make it out with these injuries... Deliver my message to the capital quickly... and may the gods of fate watch over you..."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(2));
                flttypemajor = fltsetdungeon();
                itemcreate(
                    -1, 0, cdata[tc].position.x, cdata[tc].position.y, 0);
            }
            flt();
            itemcreate(
                -1,
                54,
                cdata[tc].position.x,
                cdata[tc].position.y,
                1000 + rnd(200));
            flt();
            itemcreate(-1, 55, cdata[tc].position.x, cdata[tc].position.y, 3);
            flt();
            itemcreate(-1, 239, cdata[tc].position.x, cdata[tc].position.y, 0);
            inv[ci].param2 = 0;
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            txt(lang(
                cdatan(0, tc) + u8"は自ら命を絶った…"s,
                cdatan(0, tc) + u8" kills himself..."s));
            chara_vanquish(tc);
            return talk_result_t::talk_end;
        }
        break;
    case 208:
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = lang(
            u8"見て分からんか、わしゃ忙しいんじゃ。用があるなら手短にな。"s,
            u8"Don't you see I'm busy!"s);
        talk_window_query();
        if (chatval == 1)
        {
            invctrl = 1;
            snd(26);
            crafting_menu();
            return talk_result_t::talk_unique;
        }
        return talk_result_t::talk_end;
    case 209:
        ELONA_APPEND_RESPONSE(
            2, lang(u8"小さなメダル"s, u8"I have some small medals."s));
        ELONA_APPEND_RESPONSE(
            3, lang(u8"荷車の改造"s, u8"Can you upgrade my cart?"s));
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = lang(
            u8"ほほう、客人とはこれまた珍しい。暖かい飯でも馳走してさしあげたいが、あいにくと今日の飯番はガロクでの。あやつの作る料理は自らの作品に似て、なんとも無骨で味気ない。とても客人に楽しんでもらえる代物じゃないのう。まぁ、せっかくこんな辺境の地にまで、やって来なさったんだ。何か用件があれば、話だけは聞こうじゃないか。"s,
            u8"Oh oh, what we got, talk about rare! A traveler? I would have given you a feast if it were not Garok that handles today's dinner. You know, his cooking is as loutish as his creations. Oh well, you've come all the way here, what can I do for you?"s);
        talk_window_query();
        if (chatval == 2)
        {
            listmax = 0;
            buff = lang(
                u8"おお、小さなメダルを持っておるのか？メダルの収集は、わしの生きがいなんじゃよ！これまでに生産してきた自慢の品の数々と交換せぬか？"s,
                u8"Ho ho ho! You got small medals! Let me see, let me see! Would you like to trade them for one of my proud works?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            invctrl = 28;
            invfile = cdata[tc].shop_store_id;
            shop_sell_item();
            screenupdate = -1;
            update_screen();
            cs = 0;
            return talk_result_t::talk_unique;
        }
        if (chatval == 3)
        {
            listmax = 0;
            buff = lang(
                u8"荷車の改造とな。たいして気乗りのする仕事ではないが、そうじゃの、小さなメダル"s
                    + calccargoupdatecost()
                    + u8"枚をくれるならやらんでもない。"s,
                u8"Upgrade your cart? It's not something I get excited about but if you can give me "s
                    + calccargoupdatecost()
                    + u8" small medals, I'll think about it."s);
            int stat = item_find(622, 3, 1);
            if (stat != -1)
            {
                ci = stat;
                if (inv[ci].number >= calccargoupdatecost())
                {
                    ELONA_APPEND_RESPONSE(
                        1,
                        lang(u8"メダルを渡す"s, u8"Here, take these medals."s));
                }
            }
            ELONA_APPEND_RESPONSE(0, lang(u8"断る"s, u8"I think not."s));
            chatesc = 1;
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"ふぅん。"s, u8"Huh."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            txtnew();
            txt(lang(
                u8"荷車の重量の限界が"s + cnvweight(calccargoupdate())
                    + u8"上昇した。"s,
                u8"Your cart's weight limit has increased by "s
                    + cnvweight(calccargoupdate()) + u8"."s));
            snd(58);
            inv[ci].number -= calccargoupdatecost();
            gdata_current_cart_limit += calccargoupdate();
            refresh_burden_state();
            listmax = 0;
            buff = lang(u8"ほい。"s, u8"Here you are."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        return talk_result_t::talk_end;
    case 221:
        if (gdata_pael_and_her_mom == 1000)
        {
            if (gdata_current_map == 33 && adata(29, gdata_current_map))
            {
                listmax = 0;
                buff = lang(
                    u8"おかあさん、なんだか今日はいつもより元気そう！お祭りは人がたくさん来るから嫌いだけど、おかあさんにもジュア様の加護があるといいな。"s,
                    u8"Mommy looks to be in a good condition today. I hate the festival because there are so many people out there but I hope St.Jure will watch over her!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            listmax = 0;
            buff = lang(
                u8"どうして、おかあさんはあんなに悲しそうなの？顔はかわっても、あたしのおかあさんだよ。お友達もきっとわかってくれる…わかってくれないんなら…お友達なんていらない！…あたしはお母さんとずっといっしょにいるんだもん。"s,
                u8"Why does mommy look so sad? Her face has changed but she's still my mommy. I know my friends will understand too... and if they don't then they're no friends of mine! I'll always be by her side. Always."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 1001)
        {
            listmax = 0;
            buff = lang(
                u8"消えて！二度と顔をみせないで！！ばかぁ！"s,
                u8"Go away! Never come back again! Bastard!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 1002)
        {
            listmax = 0;
            buff = lang(
                u8"おかあさん…どこにいっちゃったのぉ…"s,
                u8"Mommy... where have you gone mommy?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 0)
        {
            buff = lang(
                u8"おかあさんがひどい病気で…お医者さんはエーテル病だから手に負えないって…"s,
                u8"Mommy is really sick... but the doctor said she has the ether plague and he can't do anything..."s);
            bool stat = talk_give_potion_of_cure_corruption();
            if (!stat)
            {
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            gdata_pael_and_her_mom = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 1 || gdata_pael_and_her_mom == 3)
        {
            listmax = 0;
            buff = lang(
                u8"おかあさん、はやく良くなるといいな♪"s,
                u8"I hope mommy gets better soon!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 5 || gdata_pael_and_her_mom == 7)
        {
            listmax = 0;
            buff = lang(""s + cdatan(0, 0) +
                    u8"さん、大好き〜。おかあさん、どんどん元気になってるよ♪"s,
                u8"Thanks "s + cdatan(0, 0) +
                    u8", you're the best! Mommy's getting better and better."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 2 || gdata_pael_and_her_mom == 4)
        {
            buff = lang(u8"あ…"s + cdatan(0, 0) +
                    u8"さん。おかげで、おかあさんの身体も良くなっています。でもまだ、もとどおりに元気になるには時間がかかるみたいなの…"s,
                u8"Ah, hi "s + cdatan(0, 0) +
                    u8". Thanks to you Mommy's been getting better! But... it still looks like she needs more time before she's really healthy."s);
            bool stat = talk_give_potion_of_cure_corruption();
            if (!stat)
            {
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            ++gdata_pael_and_her_mom;
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 6)
        {
            buff = lang(
                u8"おかあさん、最近すごく調子いいの！お医者さんも、もう大丈夫だろうって。最近は、近所の子供達もお見舞いに来てくれるんだよ。はやく、おかあさんやみんなと遊びたいな〜。"s,
                u8"Mommy looks a lot better these days! The doctor said she's gonna be okay. Even the other kids have come to visit her in the past few weeks. I want mommy to be able to play with us soon..."s);

            bool stat = talk_give_potion_of_cure_corruption();
            if (!stat)
            {
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            ++gdata_pael_and_her_mom;
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 8)
        {
            buff = lang(""s + cdatan(0, 0) +
                    u8"さん…おかあさんが…！おかあさんが…急に具合が悪くなって…身体がおかしくなって…あぁ…神様…"s,
                ""s + cdatan(0, 0) +
                    u8"! It's mommy... something's wrong! Suddenly she started acting strange and... now her body is changing and... oh gods..."s);
            bool stat = talk_give_potion_of_cure_corruption();
            if (!stat)
            {
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            ++gdata_pael_and_her_mom;
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 9)
        {
            listmax = 0;
            buff = lang(
                u8"おかあさん…大丈夫？…大丈夫？…あぁぁ…"s,
                u8"Mommy! Mommy are you okay? Mommy?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 10)
        {
            listmax = 0;
            buff = lang(
                u8"おかあさんが…"s + cdatan(0, 0) + u8"さんにお話があるって…"s,
                ""s + cdatan(0, 0) + u8", mommy has something to say to you."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        break;
    case 222:
        if (gdata_pael_and_her_mom == 1002)
        {
            listmax = 0;
            buff = lang(u8"ひどいわ。"s, u8"You are cruel."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom == 10)
        {
            listmax = 0;
            buff = lang(""s + cdatan(0, 0) +
                    u8"さん…こんな姿でごめんなさい…どうか、怖がらないで…逃げないで…。私の病気は、もう手遅れだったようです。この醜い身体が元に戻ることは…もうないでしょう。"s,
                ""s + cdatan(0, 0) +
                    u8", I'm sorry you have to see me this way... please don't turn away... don't run. It seems my disease has already progressed too far... my twisted and hideous body... I can never return to normal... the disease is too advanced now."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"病気は治りませんでしたが、あなたがして下さった全ての事に感謝します。ええ、無駄ではなかったの。だって、おかげでパエルに、あんないいお友達がたくさんできたんだもの。"s,
                u8"Even though you couldn't cure me, you have my thanks for all that you've done. It was... your efforts were not in vain. You helped Pael make a lot of friends... surely that counts for something."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(-1, 639, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 20000);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 4);
            snd(51);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"これは少ないですが、私の感謝の気持ちです。受け取ってくださいな。"s,
                u8"This isn't much, I know, but it's the least I can do. Please accept these gifts."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_pael_and_her_mom = 1000;
            cdata[tc].is_silent() = true;
        }
        if (gdata_pael_and_her_mom == 1000)
        {
            if (gdata_current_map == 33 && adata(29, gdata_current_map))
            {
                buff = lang(
                    u8"ああ、もうこんな時期になったのね。パエルったら、私のことなんか気にせずお祭りを楽しんでくればいいのに。元気な頃は、よく二人でジュア様の像にお参りしていたのよ。"s,
                    u8"Oh, it's already this time of the year. Poor Pael, she should stop worrying about me and go to the festival. We used to visit the St.Jure's statue and pray together around this time."s);
                int stat = inv_find(559, 0);
                if (stat != -1)
                {
                    ELONA_APPEND_RESPONSE(
                        2,
                        lang(
                            u8"エーテル抗体を1本渡す"s,
                            u8"(Give her a potion of cure corruption.)"s));
                }
                ELONA_APPEND_RESPONSE(0, lang(u8"お元気で"s, u8"Take care."s));
                chatesc = 1;
                talk_window_query();
                if (chatval == 2)
                {
                    int stat = inv_find(559, 0);
                    --inv[stat].number;
                    txt(lang(
                        u8"エーテル抗体を1本渡した。"s,
                        u8"You hand her a potion."s));
                    snd(13);
                    modify_karma(0, 20);
                    listmax = 0;
                    buff = lang(
                        u8"ありがとうございます。あなたは本当に優しい心の持ち主ね。ジュア様のご加護があるのかしら、なんだか聖夜祭の間はお薬がよく効く気がするわ。"s,
                        u8"Oh, thank you. You have a very kind heart, you know. The potion, I feel like the medicine is working better during the festival. Maybe it's the blessing of St.Jure?"s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_end;
                }
                listmax = 0;
                buff = lang(
                    u8"いつもお見舞いに来てくれてありがとう…どうぞ、聖夜祭を楽しんで行ってください。"s,
                    u8"Thanks for coming to see me. Please enjoy yourself at the festival during your stay."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
        }
        if (gdata_pael_and_her_mom == 1000)
        {
            listmax = 0;
            buff = lang(u8"…"s + cdatan(0, 0) +
                    u8"さん、あなたに最後のお願いがあります。この短剣で、私の胸を貫いてください。うふふ、だって、この姿がばれてしまったら、せっかくできたパエルの友達が逃げてしまうじゃない。あの子が幸せになれるなら、私は…"s,
                ""s + cdatan(0, 0) +
                    u8", I have... I have one final request. Take this knife and... *weep*. If Pael's friends saw me like this, they'd run in fear and treat her with fear and suspicion. As long as she can be happy, I..."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            buff = lang(
                u8"こんなこと、あなたにだから頼めるのよ。どうか、この苦しみを終わらせてください…"s,
                u8"Please, I'm begging you. Please put me out of my misery..."s);
            int stat = inv_find(559, 0);
            if (stat != -1)
            {
                ELONA_APPEND_RESPONSE(
                    2,
                    lang(
                        u8"エーテル抗体を1本渡す"s,
                        u8"(Give her a potion of cure corruption.)"s));
            }
            ELONA_APPEND_RESPONSE(
                1, lang(u8"息の根を止める"s, u8"(End her life.)"s));
            ELONA_APPEND_RESPONSE(
                0, lang(u8"希望はまだある"s, u8"There's still hope."s));
            chatesc = 1;
            talk_window_query();
            if (chatval == 1)
            {
                listmax = 0;
                buff = lang(
                    u8"あぁ…ありがとう。ありがとう…"s,
                    u8"Th-thank you... thank..."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                event_add(20, tc);
                return talk_result_t::talk_end;
            }
            if (chatval == 2)
            {
                int stat = inv_find(559, 0);
                --inv[stat].number;
                txt(lang(
                    u8"エーテル抗体を1本渡した。"s,
                    u8"You hand her a potion."s));
                snd(13);
                modify_karma(0, 20);
                listmax = 0;
                buff = lang(
                    u8"そんなものいくら飲んでも、元には戻らないのに…そんなもの…ありがとう…"s,
                    u8"No matter how many I drink, my body won't return to normal... thank you though..."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            listmax = 0;
            buff = lang(
                u8"あ、あなたは、私にこんな姿で生き続けろというの？世の中には、希望なんて便利な言葉で片付けられない苦しみがたくさんあることを、あなたはわかっているのかしら。…ごめんなさい、きついことをいって。あなたの考えが変わるのをまっているわ。"s,
                u8"You... you would force me to keep living like this? You'll find there's much suffering and pain in this world that you can't heal with such optimistic words. I'm sorry... I'm sure you know that well, but... I'll be waiting for you to change your mind."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom > 7)
        {
            listmax = 0;
            buff = lang(
                u8"う…けほっ、けほっ。ごめん…なさい…気分が悪いの…はぁ…はぁ…"s,
                u8"*cough* *cough* I'm... sorry... I don't... feel well... *huff* *huff*"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom > 5)
        {
            listmax = 0;
            buff = lang(""s + cdatan(0, 0) +
                    u8"さん、いらっしゃい。え？嬉しそうな顔をしてる？…うふふ、この前ね、パエルが家の外に大きな雪だるまを作ってくれたのよ。「お友達と一緒に作ったの」って、あんな嬉しそうな顔は、あの子の父親が死んでしまって以来見ていないわ。あのパエルの作った雪だるまを窓から見てるとね、とても幸せな気分になるのよ。"s,
                u8"It's good to see you, "s + cdatan(0, 0) +
                    u8". Hmm? You say I look happy? Hehe, just before you arrived Pael made a snowman outside. She said she made it with her friends. I haven't seen her smile like that since her father died. When I see that snowman through the window, I feel a joy I cannot describe to you."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pael_and_her_mom > 3)
        {
            listmax = 0;
            buff = lang(
                u8"いつもありがとうございます。薬のおかげで、だいぶ痛みも引いてきました。身体が元気になったら、あの子と思う存分遊んであげたいわ…そうそう、最近では、近所の子供達が何人か見舞いに来てくれるの。パエルも、最初は恥ずかしがっていたけど、だんだんと話をするようになって。パエル、いいお友達ができるといいわね。"s,
                u8"Thanks for everything you've done for us. The medicine has mostly stopped the pain. If I can get better I promise to play with my daughter to her heart's content... thankfully the other kids in the neighborhood have been coming to visit these past few days. Pael seems quite shy, but even still she's started to talk to them little by little. I hope Pael can make a lot of friends."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = lang(
            u8"あら…こんな姿でごめんなさいね。パエルの父親は、パエルが5歳の時にプチに食べられてしまったの…そのせいで、あの子は家にこもりがち、いつも、ほかの子供が外で遊ぶのを眩しそうに眺めているわ。きっと、外の世界と自分との間に、見えない線を引いてしまっているのね。小さな胸の奥には、とても、とても優しい心をもった子なのに。ちょっとだけ甘えん坊さんだけどね、うふふ。"s,
            u8"Oh... I'm sorry you have to see me like this. Pael's father died when she was five... he was eaten by a swarm of putits. Ever since then, she just sits around the house. She's always watching the other kids play from the window, staring longingly like she'd love to join them. I can tell she's torn between watching over me and joining the outside world. She has a kind heart beating in that little chest of hers. She's a bit spoiled, but she's a good kid, he he."s);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    case 223:
        if (gdata_wife_collector == 0)
        {
            ELONA_APPEND_RESPONSE(1, lang(u8"こんな嫁でよければ"s, u8"Sure."s));
            ELONA_APPEND_RESPONSE(
                0,
                lang(u8"ふざけるな"s, u8"Don't mock me you filthy wretch."s));
            buff = lang(
                u8"俺を誰だか知らないだと？この街で一番の色男、ラファエロ様だよ。俺が狙った女は、例えパルミアの王妃だろうとイチコロさ。だがな、最近はどうも恋の駆け引きみたいなのに、飽き飽きしちまった。本音をいや、無条件で俺に仕えてくれる女が欲しいんだよ。で、お前の嫁を俺によこさないか？礼はするぜ。"s,
                u8"Don't you know who I am? I am, by far, without question, doubtlessly and unabashedly, the sexiest man in this town -- if not the whole of North Tyris. I can have any woman I desire. I could even take the princess of Palmia if I wanted. Yet, strange as it sounds, lately I've grown tired of the game. Honestly, I want a woman who will serve me unconditionally and never complain. Why don't you let me keep one of your wives? You'd have my thanks. "s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"まあ、そんな上手い話はないよな。"s,
                    u8"Pah, it's not that important anyhow."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"よしきた。じゃあ、お前さんのとびきりの嫁を連れてきてくれ！"s,
                u8"Great. Bring me a fine young girl!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_wife_collector = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_wife_collector == 1 || gdata_wife_collector == 1000)
        {
            ELONA_APPEND_RESPONSE(
                1, lang(u8"嫁を見せる"s, u8"How's this one?"s));
            ELONA_APPEND_RESPONSE(0, lang(u8"ふざけるな"s, u8"Forget it."s));
            buff = lang(
                u8"どれどれ、お前さんの嫁を吟味させてもらおうか！"s,
                u8"Which one? Who have you brought for me to inspect?"s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"はやくしてくれよ。"s, u8"Bring me your wife!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            allyctrl = 1;
            int stat = ctrl_ally();
            if (stat == -1)
            {
                listmax = 0;
                buff = lang(u8"じらすなよ。"s, u8"Huh?"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            rc = stat;
            if (cdata[rc].is_married() == 0)
            {
                listmax = 0;
                buff = lang(
                    u8"嫁だ。嫁じゃなきゃだめだ！"s,
                    u8"I want your wife, it's pointless if you aren't married!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            listmax = 0;
            buff = lang(
                u8"ほう、これがお前さんの嫁か。"s + cdatan(0, rc)
                    + u8"ちゃんというのだな？恥ずかしがらずこっちに来なさい。"s,
                u8"So... this is your wife eh? "s + cdatan(0, rc)
                    + u8" is her name? Don't be embarrassed, come along!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            tcbk = tc;
            tc = rc;
            s = chara_refstr(cdata[tc].id, 8);
            if (!strutil::contains(s(0), u8"/man/"))
            {
                dmgcon(tcbk, status_ailment_t::insane, 1000);
                f = 1;
                modify_karma(0, 2);
            }
            else
            {
                f = 0;
                modify_karma(0, -15);
            }
            listmax = 0;
            buff = lang(
                u8"いやん、おじさまったら♪"s,
                u8"Ick, you're leaving me with him!?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            tc = tcbk;
            if (f == 1)
            {
                listmax = 0;
                buff = lang(
                    u8"な、おま…ぎぎ…の嫁さ…ぎぎ…は人間じゃ…ぎぎ"s,
                    u8"She's...she's not--hiii--She's not even hu--huuuuu--human.."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            if (gdata_wife_collector == 1)
            {
                flt();
                itemcreate(
                    -1, 54, cdata[0].position.x, cdata[0].position.y, 5000);
                txt(lang(
                    u8"クエストを達成した！"s,
                    u8"You have completed the quest!"s));
                snd(51);
                snd(44);
                txtef(2);
                txt(lang(
                    u8"ジャーナルが更新された。"s,
                    u8"Your journal has been updated."s));
                gdata_wife_collector = 1000;
            }
            chara_vanquish(rc);
            snd(51);
            flt();
            itemcreate(-1, 640, cdata[0].position.x, cdata[0].position.y, 2);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            listmax = 0;
            buff = lang(
                u8"これは…すごい嫁だ…！お前さんとは女の趣味が合いそうだな。また嫁を連れてきてくれれば、いいものを渡すぜ。"s,
                u8"She's a work of art! Looks like we have the same taste in women. Hey, if you bring me another one as good as this one, I will give you something incredible. "s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        break;
    case 224:
        if (gdata_novice_knight == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"イィッック！！イィーック！ハ…これは、"s + cdatan(0, 0)
                    + u8"さん、その節はお世話になりました。"s,
                u8"Yeeeeck! Yeee-eeeck! Oh, it's you again."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_novice_knight == 0)
        {
            ELONA_APPEND_RESPONSE(
                1, lang(u8"まかせて"s, u8"I'll do it for you."s));
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            buff = lang(
                u8"イィッック！やめて！くるなぁー！イィーック！ハ…失礼しました。あなた…見たところ強そうですね。私に力を貸してくれませんか？騎士昇格のための試験で、イークの首領を討伐しなければならないんです。私には、荷が重い使命ですよ…イーク…うわあああ…ダメだ…思い出しただけでも膝が震える…お願いです。私の代わりに倒してきてください。"s,
                u8"Yeeeck! Nooo! Don't!! Get away from me!! Yeeeee-eeeck! Hump, oh....excuse me. You...you look like a skilled adventurer. Could you give me your hand? I need to slay the head of Yeek to be promoted to the rank of knight. The duty is too heavy for me....yeeee-eeck! No...! Hump...I don't want to recall anything anymore. Please do this duty for me."s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"イィッック！"s, u8"Yeeeeck!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"助かります。こんな試験、私にはできっこないんです。奴らの住処は、この村を出てすぐ西の洞窟。頼みますよ。"s,
                u8"Fantastic! This duty...it's impossible for me. Yeeks live in a dungeon west from here. I'm counting on you."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_novice_knight = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_novice_knight == 1)
        {
            listmax = 0;
            buff = lang(
                u8"イィッック！やめて！くるなぁー！イィーック！ハ…あなたでしたか…"s,
                u8"Yeeeeck! Noo...! Don't..! That's my nose..! Yeee-eeeck! Hump, oh, it's you..."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_novice_knight == 2)
        {
            listmax = 0;
            buff = lang(
                u8"おお、無事にイークの首領を討伐してくれたのですね。これで晴れて立派な騎士になれます。本当にありがとうございました。"s,
                u8"Oh, you've brought me the head! I can pass the test now. Thank you very much."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(-1, 661, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 5000);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            gdata_novice_knight = 1000;
            return talk_result_t::talk_end;
        }
        break;
    case 225:
        if (gdata_puppys_cave == 1000)
        {
            listmax = 0;
            buff = lang(u8"くぅぅぅぅん！"s, u8"Ruff-ruff!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (chara_get_free_slot_ally() != 0)
        {
            ELONA_APPEND_RESPONSE(1, lang(u8"連れて行く"s, u8"I'll take you"s));
        }
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = lang(u8"くぅうううん。"s, u8"Woof!"s);
        talk_window_query();
        if (chatval == 1)
        {
            txt(lang(
                name(tc) + u8"を保護した。無事に連れて帰らなければ。"s,
                u8"You must return the puppy safely."s));
            rc = tc;
            new_ally_joins();
            cdata[rc].is_escorted_in_sub_quest() = true;
            chara_refresh(rc);
            return talk_result_t::talk_end;
        }
        else
        {
            return talk_result_t::talk_end;
        }
        break;
    case 226:
        if (gdata_puppys_cave == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"あ、冒険者さんだ〜。こんにちわん！"s, u8"Hello there!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_puppys_cave == 0)
        {
            ELONA_APPEND_RESPONSE(
                1, lang(u8"まかせて"s, u8"I'll get your puppy."s));
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            buff = lang(
                u8"はうっ。ポピーがいなくなっちゃった…また、あの洞窟に迷い込んじゃったのかな？どうしよう、お父さんは今いそがしくて相手にしてもらえないし…あ、冒険者さん、ポピーを探してきてよ〜。ポピー？ポピーは子犬だよ。私の一番のお友達なの。"s,
                u8"Oh no, Poppy has disappeared again... He probably got lost in that cave again. Now what do I do, Papa is too busy to deal with this... Oh, Adventurer, go and find Poppy for me. Poppy? He's my puppy, and my best friend."s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"ポピー…。"s, u8"Poppy..."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"よかったぁ！ポピーは、きっといつもの洞窟で迷っちゃったの。この街を出て、すぐ東にある洞窟だよ。冒険者さん、よろしくね。"s,
                u8"Great! I'm sure he's lost in that cave he always plays in. The cave is just outside the east side of town. Thanks in advance."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_puppys_cave = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_puppys_cave == 1)
        {
            if (chara_find_ally(225) == -1)
            {
                listmax = 0;
                buff = lang(u8"ポピーまだ〜？"s, u8"Where's Poppy?"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            listmax = 0;
            buff = lang(
                u8"ポピー！！無事だったのね！冒険者さん、ありがとう。これ、あげる〜。"s,
                u8"Poppy you're safe！ Thank you adventurer, you can have this..."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(-1, 641, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 2500);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            gdata_puppys_cave = 1000;
            chara_vanquish(chara_find_ally(225));
            flt();
            chara_create(-1, 225, 31, 4);
            cdata[rc].character_role = 3;
            return talk_result_t::talk_end;
        }
        break;
    case 227:
        if (gdata_cat_house == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"いや〜。おかげさまで家は猫から解放されたんですが、宿屋のほうが快適でね。つい、こっちで寝泊りしてしまいますよ。ははは。"s,
                u8"Well...actually...I found this inn more comfortable than my house."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_cat_house == 0)
        {
            ELONA_APPEND_RESPONSE(1, lang(u8"引き受ける"s, u8"No problem."s));
            ELONA_APPEND_RESPONSE(
                0, lang(u8"面倒だ"s, u8"None of my business."s));
            buff = lang(
                u8"あなた、猫は大丈夫ですか？いえね、私は猫が大の苦手なんですが、こともあろうに、私の家に大量の猫が住み着いてしまったんですよ。そこで冒険者さん達に猫の退治を依頼しているものの、何故か誰も帰ってこない…いったい、家の中はどうなってるんでしょうか。あなた、もしよかったら見てきてくれませんか？"s,
                u8"Hey you, are you..uh...alright with cats? Well, those filthy...they creatures took over my house. I've been asking adventurers to clean up the cats from my house ever since but none returned. What's happening in my house? You...can you take a look inside my house?"s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"そうですか…残念です。"s, u8"Uh...fine..."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"おお、ありがたい。家は南の畑の近くにあります。中にどんな猫がいるのかわからないので、十分気をつけてください。"s,
                u8"Thank God. My house is south from hear. Be careful, for it is unknown what inhabits my home."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_cat_house = 1;
            cell_featset(23, 22, tile_downstairs, 11, 3);
            return talk_result_t::talk_end;
        }
        if (gdata_cat_house == 1)
        {
            listmax = 0;
            buff = lang(
                u8"どうです？猫はもういなくなりましたか？"s,
                u8"Is my home safe from the cats?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_cat_house == 2)
        {
            flt();
            nostack = 1;
            itemcreate(-1, 630, cdata[0].position.x, cdata[0].position.y, 0);
            fixmaterial = 24;
            change_item_material();
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 25500);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 4);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"なんと、猫使いなる魔物が住み着いていたのですか。いやぁ、猫退治なんて軽い依頼ではなかったですね。ははは。私の家で亡くなった冒険者さん達も、あなたのおかげで浮かばれるでしょう。どうぞ、お礼を受け取ってください。"s,
                u8"What? An evil cat tamer? My God...I have no idea why such a creature took over my home. But uh...thanks anyway."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_cat_house = 1000;
            return talk_result_t::talk_end;
        }
        break;
    case 231:
        if (gdata_defense_line == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"おお、勇者よ！酒でも飲み交わさぬか？フハハハア！"s,
                u8"Ah, the bravest of the brave. Care for a drink? Muwahaha!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (cdata[0].fame < 5000)
        {
            listmax = 0;
            buff = lang(
                u8"なんだ、ぬしは。私は弱いものには興味がないのだ。フハハハハ！"s,
                u8"Be gone. I have no interest in weak soldiers. Muwahahaha!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_defense_line == 0)
        {
            listmax = 0;
            buff = lang(u8"オパートスの名にかけて！貴殿はかの有名な"s +
                    cdatan(1, 0) +
                    u8"ではないか？貴殿の腕を見込んで頼みがあるのだ。"s,
                u8"By Opatos! You are the famous "s + cdatan(1, 0) +
                    u8", are you not? I have a favor I'd like to ask of someone like you. "s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            ELONA_APPEND_RESPONSE(
                1, lang(u8"話を聞こう"s, u8"(Hear him out.)"s));
            ELONA_APPEND_RESPONSE(
                0, lang(u8"止めておこう"s, u8"(Don't get involved.)"s));
            buff = lang(
                u8"私はジューアの解放軍の大佐、ギルバートと申す。軍といっても国軍ではないが、イェルスの犬に占拠された各地のジューア自治区を、解放してまわっておるのだ。その我が軍が、パルミア国境でイェルスの強力な防衛線の前に苦戦しておる。最新鋭の武装を持つ奴らに対し、我らは剣に頼るのみ。このままでは、全滅する恐れさえあるのだ。どうか、貴殿の力、貸してもらえぬか？"s,
                u8"I am colonel of the Juere Liberation Army, Gilbert. We're not the true national army, but even so we fully intend to free the Juere Territories from their occupation by those Yerles dogs. However, our army is having a hard time breaking through their strong front lines on the Palmia border. We only have our swords against their advanced weapons, after all. If things go on like they are, our army might be totally annihalated. So I ask you, will you lend us your power?"s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"フハハハハッ。腰抜けめ。"s,
                    u8"Mwahahaha! You damn coward!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"フハハハァッ。そうこなくてはならぬ。貴殿の力、頼りにしておる。戦の準備ができ次第、声をかけてくれ。"s,
                u8"Mwahahaha! Good, good. We'll be counting on you. Once you've prepared, come speak to me again."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_defense_line = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_defense_line == 1 || gdata_defense_line == 2)
        {
            ELONA_APPEND_RESPONSE(1, lang(u8"いい"s, u8"They are."s));
            ELONA_APPEND_RESPONSE(0, lang(u8"だめ"s, u8"Not yet."s));
            buff = lang(
                u8"準備はいいかな？"s,
                u8"Are your preparations complete, then?"s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"待っておるぞ。"s, u8"We're waiting on you."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"フハァ。貴殿にオパートスの加護のあらんことを祈っておるぞ！"s,
                u8"Hahaha! I pray Opatos' favor be with you!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_defense_line = 2;
            mdata(4) = cdata[0].position.y * 1000 + cdata[0].position.x;
            gdata_destination_map = 12;
            gdata_destination_dungeon_level = 4;
            levelexitby = 2;
            chatteleport = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_defense_line == 3)
        {
            flt();
            itemcreate(-1, 655, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 10000);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"フアハァァァァハハハ。フハー！ファハハハ、フ、フハッ、ブ、ブバァッ…ゲホッ…ゲホ…す…すまん。震えるほど興奮したぞ、ぬしの雄姿に。解放軍も、これで無事にパルミアの国境を越えることができる。どうか、この感謝の気持ちを受け取ってくれ。"s,
                u8"Muwahahahah! Muwahahahahaha! Mu-mu...wa..! *cough* *cough* My...My apologies. Your heroic figure striding the battlefield was so amazing that even I was shaken. With this, the Liberation Army can pass the borders of Palmia. Please, accept this reward as my thanks."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_defense_line = 1000;
            return talk_result_t::talk_end;
        }
        return talk_result_t::talk_end;
    case 243:
        if (gdata_kamikaze_attack == 1000)
        {
            listmax = 0;
            buff = lang(
                ""s + cdatan(0, 0)
                    + u8"さん、あなたとまた会話できるとは光栄です！"s,
                u8"I hope we can talk again sometime, "s + cdatan(0, 0)
                    + u8"!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_kamikaze_attack == 0)
        {
            buff = lang(
                u8"パルミア軍第十連隊は、カミカゼ特攻隊の猛攻により大苦戦中です！敵は弾幕の雨の中を潜り抜け、戦死を前提とした自爆攻撃を繰り返しています。このままでは、我が部隊は全滅の恐れもあります。どうか、援軍に向かってください！"s,
                u8"Right now, the 10th regiment of the Palmian army is entrenched in battle with the suicide squadron! The enemy has broken through our suppression fire and now they're assaulting us with suicide bombers. The enemy know they're going to die and they're trying to take us with them. How can we fight an enemy with no regard for his own life! At this rate it looks like we'll be totally annihilated! We need you to lend us your hand and lead the reinforcements."s);
            ELONA_APPEND_RESPONSE(1, lang(u8"引き受ける"s, u8"I accept."s));
            ELONA_APPEND_RESPONSE(
                0,
                lang(
                    u8"やめておこう"s,
                    u8"That sounds... dangerous. No thanks."s));
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"無念です！"s, u8"I'm sorry to hear that."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"助かります。準備ができ次第、声をかけてください。必ず遠隔武器を持参してください！"s,
                u8"Thank the gods. Call me when you're prepared. Be sure to bring a ranged weapon!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_kamikaze_attack = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_kamikaze_attack == 1 || gdata_kamikaze_attack == 2)
        {
            ELONA_APPEND_RESPONSE(1, lang(u8"いい"s, u8"Okay, let's roll."s));
            ELONA_APPEND_RESPONSE(0, lang(u8"だめ"s, u8"I'm not ready yet."s));
            buff = lang(
                u8"準備はよろしいですか？あなたは、パルミア軍が撤退するまでの間、どうにかカミカゼ特攻隊の猛撃に耐え、時間稼ぎをして下さい。"s,
                u8"Are you ready to go? We need you to hold off the suicide squadron's onslaught and buy time for the Palmian army to retreat."s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"早くしてください！"s, u8"Hurry up!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"伝令に現地まで案内させます。くれぐれも、奴らの接近を許さないように！パルミア軍の撤退が完了次第、連絡を入れます。"s,
                u8"I'll guide you to the battlefield then. Whatever you do, don't let them get close! I'll tell the Palmian army to begin a steady retreat."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_kamikaze_attack = 2;
            mdata(4) = cdata[0].position.y * 1000 + cdata[0].position.x;
            gdata_destination_map = 11;
            gdata_destination_dungeon_level = 25;
            levelexitby = 2;
            chatteleport = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_kamikaze_attack == 3)
        {
            flt();
            itemcreate(-1, 662, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 7500);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"お疲れ様であります。まさか、あの死地から戻って来ることができるなんて！戦友の無事も確認し、感謝の言葉もありません。どうかこの報酬を受け取ってください。"s,
                u8"Well done. I cannot believe you made it back alive! I've heard my comrades are safe. I can find no words to express my gratitude. Please take this reward."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_kamikaze_attack = 1000;
            return talk_result_t::talk_end;
        }
        return talk_result_t::talk_end;
    case 247:
        if (gdata_mias_dream == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"あ、冒険者さん！お仕事お疲れでありますぅ♪"s,
                u8"Mia's happy happy nyah!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_mias_dream == 0)
        {
            ELONA_APPEND_RESPONSE(
                1, lang(u8"捕ってくる"s, u8"I'll find one for you!"s));
            ELONA_APPEND_RESPONSE(
                0, lang(u8"さ、さようなら"s, u8"Oh...God..."s));
            buff = lang(
                u8"るんるんるん♪ねっこねっここっねこっ♪ふ〜んふ〜ん♪お〜冒険者さんだ〜。お仕事お疲れ様でありますぅ。冒険者さんは、シルバーキャット見たことありますかぁ？シルバーにゃんことお風呂できゃっきゃするのが、ミーアの夢なんですっ！う〜。ねっこねっここっねこ♪ふ〜んふ〜ん♪"s,
                u8"Nyobody knyows the touble Mia's seen, nyobody knyows Mia's Tru-bull. Nuah? Adventurer? Nyou find silver cat for me?"s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"はーい♪さよ〜なら〜♪"s,
                    u8"Nyo? Mia can wait nyou. Mia have goood mannyah!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"はわぁ。ほんとですか〜！楽しみにしてますぅ♪う〜。ねっこねっここっねこ♪は〜やくこないかな♪るんるんるん♪"s,
                u8"Nyowl! Mia trust nyou. Nyo hurting cats!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_mias_dream = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_mias_dream == 1)
        {
            if (chara_find_ally(246) == -1)
            {
                listmax = 0;
                buff = lang(
                    u8"ふ〜んふ〜ん♪ねっこねっこ〜ま〜だかな〜♪にししし！"s,
                    u8"Nyoroon nyoroon. Nyou still look for Mia's cat?"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            if (jp)
            {
                listmax = 0;
                buff =
                    u8"はわわ？それはっ！シルバーキャット！お〜♪ミーアうれしぃであります！こっちにおいで〜だっこだっこっ♪にしし！"s;
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            listmax = 0;
            buff = lang(
                u8"そうだ、お礼にこれあげますっ！モンスターハートっていって、所持しているだけで、支配の確率を高めてくれるアーティファクトなんですよ♪"s,
                u8"Nyanya! Nyou bring Mia silver cat! Come come, I nyo hurt nyou, nyo hurt nyou. Mia thank you very much. Nyou can have Mia's precious!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(-1, 663, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 5000);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 3);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            gdata_mias_dream = 1000;
            chara_relocate(chara_find_ally(246), -1);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            cdata[rc].character_role = 3;
            return talk_result_t::talk_end;
        }
        break;
    case 252:
        if (gdata_rare_books == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"私は…生きている価値があるのかな？"s,
                u8"I wonder... does my life really have any value?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_rare_books == 0 || gdata_rare_books == 1)
        {
            listmax = 0;
            buff = lang(
                u8"才能のある者の努力とない者の努力は、果たして同じなのだろうか？私の妹は、このルミエストの都で絵描きを目指していた。彼女は美しいものを愛したが、画家としての才能には恵まれてなかった。自分の限界に気付いた彼女は精神を病み、周りの者に当たり散らかした。罵られ、蔑まれ、誰からも理解されないまま、冬のある日、湖に身を投げて死んでしまった。"s,
                u8"Talent or no talent... if you're a success it doesn't really matter now does it? My sister came here to Lumiest hoping to make it as an artist. She dearly loved the beauty of all things, but she had no artistic ability. She tried so hard and she pushed her limits to succeed, but in the end she was rejected and it drained all the life out of her. The people here mocked and insulted her; nobody understood her. Then, one winter day, despondent, she jumped into the lake and drowned herself. "s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"私は知っていたよ…身体を壊すほどに、妹が絵の勉強に励んでいたこと。常人離れした情熱と、名声への憧れ。だが、妹が死んで間も無く、一人の天才がこの都にやって来て、何の努力もなしに彼女が望んでいた全てを手に入れてしまった。名声、幸福、富…"s,
                u8"I was sure... her obsession with painting had wrecked her health. Her devotion and desire for fame alienated her from ordinary people. But, not long after my sister died, a prodigal artist came here to Lumiest. With hardly any effort, all the things she wanted came to her. Fame, happiness, fortune... "s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"恵まれたもの、恵まれないもの、全ては運命の偶然に過ぎない…何がいいたいかよくわからない？そうだな、私自身、この感情をうまく説明できないんだ。ただ、私には人生の意味が分からなくなった…ただそれだけだ。"s,
                u8"To be privileged, or to be poor, it's all just a matter of fate and inescapable coincidence... Do you understand what it is I'm trying to say? That's right, it's tough for me to explain exactly how I feel. It's just that... I guess I no longer understand the meaning of life... that's all. "s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            listmax = 0;
            buff = lang(
                u8"…レイチェルという童話作家が描いた絵本を、妹は愛読していた。もうすでに遺品は処理してしまったが、一度読んでみたいものだ。今ならば、あいつの気持ちを、少しはわかってやれそうな気がするよ。"s,
                u8"I remember my sister really loved a series of children's books illustrated by a woman named Rachel. I'm sure they're really rare, or even impossible to find, but... I'd like to read them just once. I feel that perhaps you can understand how I feel... "s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            if (gdata_rare_books == 0)
            {
                snd(44);
                txtef(2);
                txt(lang(
                    u8"ジャーナルが更新された。"s,
                    u8"Your journal has been updated."s));
                gdata_rare_books = 1;
                return talk_result_t::talk_end;
            }
            p(0) = 0;
            p(1) = 0;
            p(2) = 0;
            p(3) = 0;
            p(4) = 0;
            p(5) = 0;
            for (const auto& cnt : items(0))
            {
                if (inv[cnt].number == 0)
                {
                    continue;
                }
                if (inv[cnt].id == 668)
                {
                    p(inv[cnt].param2) = 1;
                }
            }
            for (int cnt = 1; cnt < 5; ++cnt)
            {
                p += p(cnt);
            }
            if (p != 0)
            {
                if (p != 4)
                {
                    listmax = 0;
                    buff = lang(u8"私のために、絵本を"s + p +
                            u8"冊集めた…？感謝するよ。絵本は第4巻まであるみたいだ。もし全部集めて持ってきてくれれば、何か礼をしよう。"s,
                        u8"You've brought "s + p + u8" book"s + _s2(p) +
                            u8", just for my sake? You have my thanks. If I recall correctly, there are four volumes in the series. If you can find all four for me I'll find some way to thank you. "s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_end;
                }
                p(0) = 0;
                p(1) = 0;
                p(2) = 0;
                p(3) = 0;
                p(4) = 0;
                p(5) = 0;
                for (const auto& cnt : items(0))
                {
                    if (inv[cnt].number == 0)
                    {
                        continue;
                    }
                    if (inv[cnt].id == 668)
                    {
                        if (p(inv[cnt].param2) == 0)
                        {
                            --inv[cnt].number;
                            p(inv[cnt].param2) = 1;
                        }
                    }
                }
                listmax = 0;
                buff = lang(
                    u8"おお…これがレイチェルの絵本か。本を読んでみたいと思う気になったのは、久しぶりだよ。さっそく読ませてもらおう。"s,
                    u8"Oh! So these are Rachel's storybooks? I feel like I should read them soon... it's been such a long time. Give me a moment to look at them will you. These... these are! And this! And... *Renton bubbles at the mouth* "s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                if (jp)
                {
                    listmax = 0;
                    buff = u8"…"s;
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    listmax = 0;
                    buff = u8"… …"s;
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    listmax = 0;
                    buff = u8"… … …"s;
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                }
                listmax = 0;
                buff = lang(
                    u8"ビーーー！バリリ！！ビリリ！バリリリリリ！！！こんなモノ！こんなモノ！こんなモノ…ビリビリビリビリ！ふう、ふう、はあ、はあ…。"s,
                    u8"And this... *huff* *huff* "s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                txtef(5);
                txt(lang(u8"エヘカトル「うみゃ〜？」"s, u8"\"Mew?\""s));
                listmax = 0;
                buff = lang(
                    u8"…こんな絵は天才にしか描けない。努力じゃダメだ。妹には…どう頑張っても、描けなかっただろう。幸運の女神というものがいるのなら、私は彼女を恨もう。…すまない、報酬だ。しばらく一人にしておくれ。"s,
                    u8"*A crazed look wells up in Renton's eyes* These books... only a true artistic genius could've painted like this. Effort alone is simply not enough... my sister... no matter how long or hard she tried, she never could've painted such beauty. If the goddess of luck truly exists, I should devote myself to her. I'm sorry... you do deserve a reward. I'd like to be alone for a while... if you don't mind. "s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                flt();
                itemcreate(
                    -1, 666, cdata[0].position.x, cdata[0].position.y, 0);
                flt();
                itemcreate(
                    -1, 655, cdata[0].position.x, cdata[0].position.y, 0);
                flt();
                itemcreate(
                    -1, 54, cdata[0].position.x, cdata[0].position.y, 20000);
                flt();
                itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 5);
                txt(lang(
                    u8"クエストを達成した！"s,
                    u8"You have completed the quest!"s));
                snd(51);
                txt(lang(
                    u8"何かが足元に転がってきた。"s,
                    u8"Something is put on the ground."s));
                snd(44);
                txtef(2);
                txt(lang(
                    u8"ジャーナルが更新された。"s,
                    u8"Your journal has been updated."s));
                gdata_rare_books = 1000;
            }
            return talk_result_t::talk_end;
        }
        break;
    case 253:
        if (gdata_pyramid_trial != 0)
        {
            listmax = 0;
            buff = lang(
                u8"フッ。安心してください。あなたの家に侵入したりはしませんよ。"s,
                u8"Heh, don't worry, I won't break in your house."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (cdata[0].fame < 3000)
        {
            listmax = 0;
            buff = lang(
                u8"私に気安く話しかけないでもらえますか？"s,
                u8"Leave me alone, please."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_pyramid_trial == 0)
        {
            listmax = 0;
            buff = lang(u8"ああ、あなたがかの有名な"s + cdatan(1, 0) +
                    u8"ですね。いい所に来てくれました。カプールの北にある謎のピラミッドを、あなたはご存知ですか？ネフィアがまだ草の根も生えない砂漠だった頃から存在し、古代の秘宝が眠っているといわれている。しかし、入り口は奇妙な魔法に保護され、誰も手をつけることができない。いや…できなかった。"s,
                u8"Ah, you're the famous "s + cdatan(1, 0) +
                    u8", aren't you? You came at a fine time. North of Kapul lies an enigmatic pyramid; you may have heard of it. The pyramid has existed since Nefia was a barren desert where even grass wouldn't grow and it's said that ancient treasure is buried within. However, it's sealed by some bizarre enchantments and is impenetrable... well, it WAS impenetrable."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            if (cdata[0].gold >= 20000)
            {
                ELONA_APPEND_RESPONSE(
                    1, lang(u8"購入する"s, u8"Alright, I'll pay."s));
            }
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            buff = lang(
                u8"私宛にね、面白い手紙が届いたんですよ。送り主はピラミッドの主『ツェン』。そして、内容は私にピラミッドへの挑戦権を与えると。…しかし、私は危険な罠に自ら陥るほど愚かではない。あなたにこの挑戦状を譲りましょう。むろん、タダではない。金貨20000枚でいかがですか？"s,
                u8"I have received a very strange letter. The sender calls himself Tsen, lord of the Pyramid. He has sent me an invitation to enter his pyramid... However, I am not foolish enough to barge into such a trap. I'll turn this invitation over to you. Of course, I won't let you have it for nothing. 20,000 gold and it's yours."s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"フッ。お金が用意できたら、いつでも取引に応じますよ。"s,
                    u8"Heh, talk to me again when you have money."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            cdata[0].gold -= 20000;
            snd(12);
            flt();
            itemcreate(-1, 24, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].param1 = 13;
            listmax = 0;
            buff = lang(
                u8"ホホホッ。取引成立ですね。では、この招待状をあなたに渡しましょう。"s,
                u8"Deal then. You can keep this invitation."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_pyramid_trial = 1;
            return talk_result_t::talk_end;
        }
        break;
    case 259:
        if (gdata_red_blossom_in_palmia == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"あなた、生きてたのね。ヒトゴロシくん。"s,
                u8"You're still alive I see. Good luck glorious murderer."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        if (gdata_red_blossom_in_palmia == 1)
        {
            listmax = 0;
            buff = lang(
                u8"パルミアの街に、真っ赤な花が咲くのを楽しみにしているわ。"s,
                u8"Go, make the brilliant blood red roses bloom."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        if (gdata_red_blossom_in_palmia == 2)
        {
            flt();
            nostack = 1;
            itemcreate(-1, 672, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].param1 = 162;
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 6);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            gdata_red_blossom_in_palmia = 1000;
            listmax = 0;
            buff = lang(
                u8"感じるわ、大勢の人の苦しみ…悲しみ…。あなたはたくさん殺したのね。小さな子供…女性…老人…生まれて間もない赤ん坊…あたし、今日は身体が火照って眠れそうにないわ。ありがとう。報酬を受け取りなさい。"s,
                u8"I can feel it already... the suffering... the misery... the pain... You've killed many people this day, you should be proud. Little kids, girls, women, old men, the sick, the feeble, even those neither born nor conceived yet. My body's hot, excited, I can hardly breathe... I won't be able to sleep tonight. My thanks, these are for you. "s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        if (gdata_red_blossom_in_palmia == 0)
        {
            listmax = 0;
            buff = lang(
                u8"ねえ、あなたはこの街の人じゃないでしょ？匂いで分かるのよ、外の人間は。外の…世界があたしに教えてくれたのは、力のない生物はただ利用され、弄ばれ、最後には食べられてしまうっていうことだけ。同情や慈悲さえ勝ち取れない人間が、この街には大勢いる。そんな者達がどうやって生活しているか、あなたは知りたいと思うわない？"s,
                u8"Hey, you're not from around here are you? I can tell just by your smell. The world out there... it's taught me that the meek are inevitably used, abused, and then chewed up and swallowed kicking and screaming. The people here are a rank lot, you won't win them over with sympathy and compassion. Don't you ever wonder how people like that can survive? Don't you want to know? "s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            ELONA_APPEND_RESPONSE(
                1, lang(u8"もちろん"s, u8"Of course I will."s));
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            buff = lang(
                u8"あたし達は他人の血を吸って生きるのよ。憎しみや妬み、執着、悪意が、この街では力になる。外の世界では疎まれ軽蔑される弱き者達が、自分に与えられた能力をはじめて認めてもらえる、ダルフィはそんな街。ねえ、あなたもこっちの世界に来る気はない？"s,
                u8"It's so simple, we live by feeding off of others. Spite, hatred, wickedness, and unrelenting cutthroat vigor are the only strengths you can rely on in this town. The outside world looks down on our lot, so we will make the outside world recognize our might. Say, stranger, why don't you join me in my world?"s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"どっかにいきなさい、イクジナシくん。"s,
                    u8"Then find somewhere else to stand, coward."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            gdata_red_blossom_in_palmia = 1;
            listmax = 0;
            buff = lang(
                u8"そう、あなたもこちらの人間だったのね。歓迎の宴の代わりに、美味しい話をあげるわ。あたしね、たくさんの人が苦しむ姿を想像すると、とても興奮するの。パルミアの宿屋にぬいぐるみが置かれている部屋がある。そのぬいぐるみに、爆弾をしかけなさい。あのすました街を血で溢れさせてくれたら、ご褒美をあげる。"s,
                u8"Looks like you're one of us after all. I can't give you a welcome feast, but I can tell you a delicious little story. When I imagine others suffering, whimpering in pain and misery, I get goose bumps. How divine! At the inn in Palmia, there's a stuffed toy laying on the floor of the private room. Stick this bomb inside that toy for me. If you can drown those mindless ants in blood for me, I'll reward you well "s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
        }
        if (cdata[0].gold >= 12000)
        {
            ELONA_APPEND_RESPONSE(1, lang(u8"購入する"s, u8"I'll buy."s));
        }
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = lang(
            u8"ねえ、核爆弾買う？金貨12000枚よ。"s,
            u8"Here, you need a nuke. Only 12000 gold pieces."s);
        talk_window_query();
        if (chatval != 1)
        {
            listmax = 0;
            buff = lang(u8"あら、そう。"s, u8"Then go away."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        txt(lang(
            u8"何かが足元に転がってきた。"s,
            u8"Something is put on the ground."s));
        cdata[0].gold -= 12000;
        snd(12);
        flt();
        itemcreate(-1, 671, cdata[0].position.x, cdata[0].position.y, 0);
        listmax = 0;
        buff = lang(
            u8"さあ、真っ赤な花を咲かせなさい。"s,
            u8"Go, make the brilliant blood red roses bloom."s);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    case 279:
        if (gdata_ambitious_scientist >= 1000)
        {
            listmax = 0;
            buff = lang(
                u8"なんじゃ、話しかけるでにゃー。実験で忙しいのじゃ！"s,
                u8"I don't have time to talk, I'm busy conducting experiments. Out of the way!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_ambitious_scientist == 0)
        {
            ELONA_APPEND_RESPONSE(
                1, lang(u8"手伝う"s, u8"Alright, I'll see what I can do."s));
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            buff = lang(
                u8"おうおう、良いところに来た。猫の手も借りたいほど忙しいのじゃ。今わしは遺伝子操作の研究をしておってな、成功すればなんと、二体の生物を合成させて、より強力な種を造りだすことができるのじゃ！最後の段階として、5体の実験体が必要じゃが、ちょっと取ってきてはくれまいか？報酬として、今使っている試作機をくれてやってもよいぞ。"s,
                u8"Oh oh oh! You've come at *just* the right time. I'm so busy I'd take help from a cat if I had to. I'm doing research in the most remarkable field of genetic engineering. You see, I can take two living creatures and combine them to produce an even stronger creature! Is that not the most amazing thing you've ever heard? I need five test subjects for the final stage of the experiment. Won't you go get some for me? I'll reward you with the gene splicing machine I'm building."s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"とんだ愚か者じゃ！"s,
                    u8"Then get out of my way you fool!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            flt();
            nostack = 1;
            itemcreate(-1, 685, cdata[0].position.x, cdata[0].position.y, 6);
            inv[ci].param2 = 5;
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            listmax = 0;
            buff = lang(
                u8"よしよし…このモンスターボールを持っていくがいい。使い方はわかっておるな？そう、瀕死のモンスターに投げつけるだけでよい。ボールのLvより上の相手には効かないから、気をつけるのじゃ。5個のボールにモンスターを捕獲して持ってきてくれ。いいか、「ボールに入れたまま」持ってくるのじゃぞ！"s,
                u8"Good good! Take these monster balls with you. Do you know how to use them? Yes yes, throw them at a monster when it is near death. The ball won't work if the monster is too high in level, so be careful. Please bring me five captured monsters. Oh... and... *please* bring them back to me IN the balls!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_ambitious_scientist = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_ambitious_scientist >= 1 && gdata_ambitious_scientist <= 5)
        {
            f = 0;
            const auto tmp = inv_getheader(0);
            const auto invhead = tmp.first;
            const auto invrange = tmp.second;
            for (int cnt = invhead, cnt_end = invhead + invrange; cnt < cnt_end;
                 ++cnt)
            {
                if (gdata_ambitious_scientist >= 6)
                {
                    break;
                }
                if (inv[cnt].number > 0)
                {
                    if (inv[cnt].id == 685)
                    {
                        if (inv[cnt].subname != 0)
                        {
                            --inv[cnt].number;
                            ++gdata_ambitious_scientist;
                            f = 1;
                            txt(itemname(cnt, 1) + u8"を納入した。"s);
                            --cnt;
                            continue;
                        }
                    }
                }
            }
            if (f)
            {
                listmax = 0;
                buff = lang(
                    u8"おうおう、例の品を持ってきてくれたか。これで実験が進むわい。"s,
                    u8"Oh oh! What a fine batch of samples you've brought me. I can finally proceed with the final stage."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            if (f == 0)
            {
                listmax = 0;
                buff = lang(
                    u8"さあ、実験体を集めてくるのじゃ。"s,
                    u8"Let's go over this one last time... I need five samples to proceed. FIVE."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            refresh_burden_state();
        }
        if (gdata_ambitious_scientist >= 6)
        {
            listmax = 0;
            buff = lang(
                u8"成功じゃ！実験は大成功じゃ！おぬしの働きに感謝して、記念すべき遺伝子複合機第一号をくれてやろう。大事に使うのじゃぞ！"s,
                u8"Success! The experiment is a huge success! You've done a great job! To express my thanks I'll let you use my gene splicing machine. Please take good care of it."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            itemcreate(-1, 684, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 2500);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 2);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            gdata_ambitious_scientist = 1000;
        }
        return talk_result_t::talk_end;
    case 280:
        if (gdata_sewer_sweeping == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"ルミエストの街道は今日も清潔だぞ！"s,
                u8"Clean! The roads are clean in Lumiest today!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_sewer_sweeping == 0)
        {
            listmax = 0;
            buff = lang(u8"待て待て待てーい！"s, u8"Wait there! Wait!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            ELONA_APPEND_RESPONSE(1, lang(u8"いいだろう"s, u8"Alright."s));
            ELONA_APPEND_RESPONSE(
                0, lang(u8"面倒だ"s, u8"I'm not interested."s));
            buff = lang(
                u8"俺はルミエストの清掃を生涯の使命とし、この道十年のベテラン掃除屋バルザックだ。街道に落ちているどんな小さなゴミも見逃さないプロ魂を持つが、そんなプライドも傷つけられちまった。下水道にとんでもない化け物が住みついて、もう俺の手には負えないぜ。お前なら、俺の気持ちを汲み取って、退治に出向いてくれるな？"s,
                u8"I'm Balzak, a well known pro garage man who has been cleaning the roads of Lumiest for 10 years. I've never missed a single garbage that messes the beautiful town of Lumiest. But my days are over. Foul creatures now nest in the sewer and sick smells spread everywhere. Adventurer, you are my only hope. Kill them, kill them for my sake!"s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(u8"そうか…冷たい奴だな…"s, u8"Ok. You are cruel."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"その言葉、待っていたぜ！下水道は宿屋の近くにある。気をつけろ、奴らは手強いぞ！"s,
                u8"That's the word I wanted to hear! You'll find the sewer entrance near the inn. Be aware, they are pretty tough."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_sewer_sweeping = 1;
            cell_featset(18, 45, tile_downstairs, 11, 20);
            return talk_result_t::talk_end;
        }
        if (gdata_sewer_sweeping == 1)
        {
            listmax = 0;
            buff = lang(
                u8"おう、お前か。下水道の掃除は進んでいるか？"s,
                u8"Oh, it's you. What about the task I asked you?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_sewer_sweeping == 2)
        {
            flt();
            itemcreate(-1, 686, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            nostack = 1;
            itemcreate(-1, 685, cdata[0].position.x, cdata[0].position.y, 0);
            inv[ci].param2 = 30;
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 15000);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 4);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"なんだってー！あの下水道をほんとに浄化したというのか？さすがに、お前を選んだ俺の目は確かだったということか…ともかく礼をいうぞ！この報酬を受け取ってくれ。"s,
                u8"Whaaat! You've really done it? Amazing! Here, take it, you deserve this."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_sewer_sweeping = 1000;
            return talk_result_t::talk_end;
        }
        break;
    case 290:
        if (gdata_belongs_to_mages_guild == 0)
        {
            ELONA_APPEND_RESPONSE(
                2,
                lang(
                    u8"魔術士ギルドとは？"s,
                    u8"Tell me about the Mages Guild."s));
            ELONA_APPEND_RESPONSE(
                1,
                lang(
                    u8"魔術士ギルドに加入したい"s,
                    u8"I want to join the Mages Guild."s));
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            buff = lang(
                u8"止まれ…この階段の先は魔術士ギルドの管轄だ。ギルドメンバー以外の者が入ることはできない…"s,
                u8"Halt...the stairs lead to the Mages Guild office. Only the members of the guild are allowed to enter."s);
            talk_window_query();
            if (chatval == 2)
            {
                listmax = 0;
                buff = lang(
                    u8"魔術士ギルドは、各地の魔術士を管轄する組合だ。組合員には規律の厳守と一定のノルマを求める代わりに、援助を施し特定の仕事を斡旋している。魔術士ギルドのメンバーには、魔法書の予約、全店舗での魔法書の割引、魔術スキルの習得と訓練などの特典がある。ギルドに加入するには、厳しい審査を通らなければならない。"s,
                    u8"The Mages Guild is made up by experienced and confirmed experts in their field of magic. We offer a variety of services such as discounted spellbook prices, reservation of spellbooks, and training related skills. But joining the Mages Guild requires you to pass a difficult test that most common mages will fail."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (chatval == 1)
            {
                if (gdata_joining_mages_guild == 0)
                {
                    listmax = 0;
                    buff = lang(
                        u8"ギルドに加入したいというのか…我々が求めているのは有能な魔術士だ。お前がギルドのメンバーにふさわしいか試させてもらおう。"s,
                        u8"So you are interested in joining our guild and we only need elite mages. Let's see if you are worthy of becoming one of us."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    listmax = 0;
                    buff = lang(
                        u8"この世界には、特殊な古代文字で書かれた古書物が散らばっている。これらを収集し、解読した後に、私の横にある納入箱に収めたまえ。古書物の価値に応じてギルドポイントを与えよう。30ギルドポイント、これがお前に課せられた試験のノルマだ…"s,
                        u8"In north Tyris, there are several ancient books encrypted with an unique rune language. Should you want to join the guild, put them into the delivery chest after you have decrypted them and we shall reward you with guild points."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    gdata_joining_mages_guild = 1;
                    gdata_mages_guild_quota = 30;
                    snd(44);
                    txtef(2);
                    txt(lang(
                        u8"ジャーナルが更新された。"s,
                        u8"Your journal has been updated."s));
                    listmax = 0;
                    buff = lang(
                        u8"ギルドポイントを規定の値まで集めたら、また私に話しかけてくれ。"s,
                        u8"You will need to gather 30 guild points in order to enter the Mages Guild. Until then, we have no more to speak."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_unique;
                }
                if (gdata_mages_guild_quota > 0)
                {
                    listmax = 0;
                    buff = lang(
                        u8"まだノルマが残っているじゃないか…ギルドに加入するには、審査を通らなければならないぞ。"s,
                        u8"To pass the test, you need to gather 30 guild points."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_unique;
                }
                listmax = 0;
                buff = lang(
                    u8"ほう…どうやらノルマを見事に達成したようだな。"s,
                    u8"Quite impressive...you have accomplished the task."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata(128) = 10000;
                gdata_belongs_to_thieves_guild = 0;
                gdata_belongs_to_fighters_guild = 0;
                gdata_belongs_to_mages_guild = 1;
                gdata_mages_guild_quota = 0;
                gdata_thieves_guild_quota = 0;
                gdata_joining_mages_guild = 1000;
                gdata_joining_thieves_guild = 0;
                gdata_joining_fighters_guild = 0;
                gdata_fighters_guild_quota2 = 0;
                gdata_mages_guild_quota2 = 0;
                gdata_thieves_guild_quota2 = 0;
                txt(lang(
                    u8"クエストを達成した！"s,
                    u8"You have completed the quest!"s));
                snd(51);
                snd(44);
                txtef(2);
                txt(lang(
                    u8"ジャーナルが更新された。"s,
                    u8"Your journal has been updated."s));
                txtef(5);
                txt(lang(
                    u8"魔術士ギルドに加入した！"s,
                    u8"You have joined the Mages Guild!"s));
                listmax = 0;
                buff = lang(
                    u8"おめでとう…合格だ。今日からお前は魔術士ギルドの一員となった。以後はギルドの規約を守り、ノルマをしっかりこなすように。"s,
                    u8"Congratulations. You are a formal member of the Mages Guild now. You can now use this stairs to enter the office. Always conform to the guild's rule and perform your tasks."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                cell_movechara(tc, 4, 20);
                cdata[tc].initial_position.x = 4;
                cdata[tc].initial_position.y = 20;
            }
            return talk_result_t::talk_end;
        }
        cell_movechara(tc, 4, 20);
        cdata[tc].initial_position.x = 4;
        cdata[tc].initial_position.y = 20;
        if (gdata_mages_guild_quota2 == 0)
        {
            ELONA_APPEND_RESPONSE(
                1, lang(u8"ノルマを貰う"s, u8"Do you have any tasks for me?"s));
        }
        else
        {
            ELONA_APPEND_RESPONSE(
                2, lang(u8"ノルマを報告する"s, u8"About my task."s));
        }
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = lang(
            u8"ようこそ魔術士ギルドへ、"s + ranktitle(8) + u8"の"s
                + cdatan(0, 0) + u8"…どうぞ中にお入り下さい。"s,
            u8"Welcome to the Mages Guild, "s + ranktitle(8) + u8" "s
                + cdatan(0, 0) + u8"... Please come in."s);
        talk_window_query();
        if (chatval == 1)
        {
            gdata_mages_guild_quota2 = 1;
            gdata_mages_guild_quota = 75 - gdata(128) / 200;
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"良い心がけです。あなたにランク昇格のためのノルマを与えましょう。世界に散らばった古書物を解読し、納入してください。"s +
                    gdata_mages_guild_quota +
                    u8"ギルドポイントが集まったら、昇進のための審査会に報告してあげましょう。"s,
                u8"Sure, there're plenty of tasks for you. For now, collect the ancient books and decrypt them. When you gather "s +
                    gdata_mages_guild_quota +
                    u8" guild points, we will think about your promotion."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 2)
        {
            if (gdata_mages_guild_quota > 0)
            {
                listmax = 0;
                buff = lang(
                    u8"どうしました？まだノルマが残っていますよ。"s,
                    u8"You have your task to complete."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            gdata_mages_guild_quota2 = 0;
            flt(51 - gdata(128) / 200);
            flttypemajor = 54000;
            itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(
                -1,
                54,
                cdata[0].position.x,
                cdata[0].position.y,
                10000 - gdata(128) + 1000);
            flt();
            itemcreate(
                -1,
                55,
                cdata[0].position.x,
                cdata[0].position.y,
                clamp(4 - gdata(128) / 2500, 1, 4));
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            modrank(8, 500, 8);
            listmax = 0;
            buff = lang(
                u8"確かにノルマの達成を確認しました。早速審査会を開いてあなたの功績を報告しましょう。"s,
                u8"You've done very well. I will give a report of your achievement to the council."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        return talk_result_t::talk_end;
    case 294:
        if (gdata_belongs_to_thieves_guild == 0)
        {
            ELONA_APPEND_RESPONSE(
                2,
                lang(
                    u8"盗賊ギルドとは？"s,
                    u8"Tell me about the Thieves Guild."s));
            ELONA_APPEND_RESPONSE(
                1,
                lang(
                    u8"盗賊ギルドに加入したい"s,
                    u8"I want to join the Thieves Guild."s));
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            buff = lang(
                u8"止まれ…この階段の先は盗賊ギルドの管轄だ。ギルドメンバー以外の者が入ることはできない…"s,
                u8"Halt...the stairs lead to the Thieves Guild office. Only the members of the guild are allowed to enter."s);
            talk_window_query();
            if (chatval == 2)
            {
                listmax = 0;
                buff = lang(
                    u8"盗賊ギルドは、各地の盗賊を管轄する組合だ。組合員には規律の厳守と一定のノルマを求める代わりに、援助を施し特定の仕事を斡旋している。盗賊ギルドのメンバーには、盗品の高値での売却、ブラックマーケットでの割引、盗賊スキルの習得と訓練などの特典がある。ギルドに加入するには、厳しい審査を通らなければならない。"s,
                    u8"The Thieves Guild is made up by experienced and confirmed experts in their field of the shadow arts. We offer a variety of services such as buying stolen goods, discount at black markets, and training related skills. But joining the Thieves Guild requires you to pass a difficult test that most common thieves will fail."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (chatval == 1)
            {
                if (gdata_joining_thieves_guild == 0)
                {
                    listmax = 0;
                    buff = lang(
                        u8"盗賊ギルドに加入したいというのか…我々は知ってのとおり闇の世界に身を置いている。まずは、お前が信頼に足る者かどうか試させてもらおう。"s,
                        u8"So...you're interested in our guild? We hide in the shadows of the society. You must win our trust to enter the guild."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    gdata_joining_thieves_guild = 1;
                    snd(44);
                    txtef(2);
                    txt(lang(
                        u8"ジャーナルが更新された。"s,
                        u8"Your journal has been updated."s));
                    listmax = 0;
                    buff = lang(
                        u8"なに、簡単な試験だ。一定のレベルを越えた冒険者には、税金が毎月徴収されるのは知っているな？その税金を4ヶ月滞納するだけだ。無論、お前は犯罪者となり、国の犬に追われる事になるだろう。その覚悟がないならば、盗賊ギルドに入るなど諦めることだ。"s,
                        u8"It is a simple task. We require you to not pay tax for 4 months. Take it granted the guards will try to hunt you down. If you aren't ready to face it, just forget it."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_unique;
                }
                if (gdata_left_bill <= 4)
                {
                    listmax = 0;
                    buff = lang(
                        u8"どうした？試験の内容は伝えたはずだ。税金を4ヶ月以上滞納してからまた来るがいい。"s,
                        u8"I've already told you what you must do. Don't pay tax for 4 months."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_unique;
                }
                listmax = 0;
                buff = lang(
                    u8"ほう…どうやらノルマを見事に達成したようだな。"s,
                    u8"Quite impressive...you have accomplished the task."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata(128) = 10000;
                gdata_belongs_to_thieves_guild = 1;
                gdata_belongs_to_fighters_guild = 0;
                gdata_belongs_to_mages_guild = 0;
                gdata_mages_guild_quota = 0;
                gdata_thieves_guild_quota = 0;
                gdata_joining_mages_guild = 0;
                gdata_joining_thieves_guild = 1000;
                gdata_joining_fighters_guild = 0;
                gdata_fighters_guild_quota2 = 0;
                gdata_mages_guild_quota2 = 0;
                gdata_thieves_guild_quota2 = 0;
                txt(lang(
                    u8"クエストを達成した！"s,
                    u8"You have completed the quest!"s));
                snd(51);
                snd(44);
                txtef(2);
                txt(lang(
                    u8"ジャーナルが更新された。"s,
                    u8"Your journal has been updated."s));
                txtef(5);
                txt(lang(
                    u8"盗賊ギルドに加入した！"s,
                    u8"You have joined the Thieves Guild!"s));
                listmax = 0;
                buff = lang(
                    u8"おめでとう…合格だ。今日からお前は盗賊ギルドの一員となった。以後はギルドの規約を守り、ノルマをしっかりこなすように。"s,
                    u8"Congratulations. You are a formal member of the Thieves Guild now. You can now use this stairs to enter the office. Always conform to the guild's rule and perform your tasks."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                cell_movechara(tc, 17, 17);
                cdata[tc].initial_position.x = 17;
                cdata[tc].initial_position.y = 17;
            }
            return talk_result_t::talk_end;
        }
        cell_movechara(tc, 17, 17);
        cdata[tc].initial_position.x = 17;
        cdata[tc].initial_position.y = 17;
        if (gdata_thieves_guild_quota2 == 0)
        {
            ELONA_APPEND_RESPONSE(
                1, lang(u8"ノルマを貰う"s, u8"Do you have any tasks for me?"s));
        }
        else
        {
            ELONA_APPEND_RESPONSE(
                2, lang(u8"ノルマを報告する"s, u8"About my task."s));
        }
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = lang(
            u8"ようこそ盗賊ギルドへ、"s + ranktitle(8) + u8"の"s + cdatan(0, 0)
                + u8"…どうぞ中にお入り下さい。"s,
            u8"Welcome to the Thieves Guild, "s + ranktitle(8) + u8" "s
                + cdatan(0, 0) + u8"... Please come in."s);
        talk_window_query();
        if (chatval == 1)
        {
            gdata_thieves_guild_quota2 = 1;
            gdata_thieves_guild_quota = (10000 - gdata(128)) * 6 + 1000;
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"良い心がけです。あなたにランク昇格のためのノルマを与えましょう。他人の所有物を奪い取り、盗品を売り払いなさい。金貨"s +
                    gdata_thieves_guild_quota +
                    u8"枚相当の盗品を売ったら、昇進のための審査会に報告してあげましょう。"s,
                u8"Alright. The Thieves Guild wants you to put stolen goods into circulation. Steal some goods and sell them to any vendors. When the sum of your earning reaches "s +
                    gdata_thieves_guild_quota +
                    u8" gold pieces, we will think about your promotion."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 2)
        {
            if (gdata_thieves_guild_quota > 0)
            {
                listmax = 0;
                buff = lang(
                    u8"どうしました？まだノルマが残っていますよ。"s,
                    u8"You have your task to complete."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            gdata_thieves_guild_quota2 = 0;
            flt(51 - gdata(128) / 200);
            flttypemajor = 60000;
            itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(
                -1,
                54,
                cdata[0].position.x,
                cdata[0].position.y,
                10000 - gdata(128) + 1000);
            flt();
            itemcreate(
                -1,
                55,
                cdata[0].position.x,
                cdata[0].position.y,
                clamp(3 - gdata(128) / 3000, 1, 3));
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            modrank(8, 500, 8);
            listmax = 0;
            buff = lang(
                u8"確かにノルマの達成を確認しました。早速審査会を開いてあなたの功績を報告しましょう。"s,
                u8"You've done very well. I will give a report of your achievement to the council."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        return talk_result_t::talk_end;
    case 297:
        if (gdata_belongs_to_fighters_guild == 0)
        {
            ELONA_APPEND_RESPONSE(
                2,
                lang(
                    u8"戦士ギルドとは？"s,
                    u8"Tell me about the Fighters Guild."s));
            ELONA_APPEND_RESPONSE(
                1,
                lang(
                    u8"戦士ギルドに加入したい"s,
                    u8"I want to join the Fighters Guild."s));
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            buff = lang(
                u8"止まれ…この階段の先は戦士ギルドの管轄だ。ギルドメンバー以外の者が入ることはできない…"s,
                u8"Halt...the stairs lead to the Fighters Guild office. Only the members of the guild are allowed to enter."s);
            talk_window_query();
            if (chatval == 2)
            {
                listmax = 0;
                buff = lang(
                    u8"戦士ギルドは、各地の戦士を管轄する組合だ。組合員には規律の厳守と一定のノルマを求める代わりに、援助を施し特定の仕事を斡旋している。戦士ギルドのメンバーには、能力復元価格の割引、鑑定価格の割引、戦士スキルの習得と訓練などの特典がある。ギルドに加入するには、厳しい審査を通らなければならない。"s,
                    u8"The Fighters Guild is made up by experienced and confirmed experts in their field of the fighting. We offer a variety of services such as reduced prices of identification and restoring, and training related skills. But joining the Fighters Guild requires you to pass a difficult test that most common fighters will fail."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            if (chatval == 1)
            {
                if (gdata_joining_fighters_guild == 0)
                {
                    listmax = 0;
                    buff = lang(
                        u8"戦士ギルドに加入したいというのか…我々が求めているのは、どんな強敵にも怯まず、与えられた指令を確実にこなす真のハンターだ。いる。お前が信頼に足る者かどうか試させてもらおう。"s,
                        u8"To join the Fighters Guild, you must first face a test to earn our trust. We only need skilled hunters who will obey our law and remain undaunted even in a desperate battle."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    gdata_joining_fighters_guild = 1;
                    snd(44);
                    txtef(2);
                    txt(lang(
                        u8"ジャーナルが更新された。"s,
                        u8"Your journal has been updated."s));
                    while (1)
                    {
                        flt(10);
                        chara_create(56, 0, -3, 0);
                        if (the_character_db[cdata[56].id]->rarity / 1000 < 70)
                        {
                            continue;
                        }
                        if (cdata[56].relationship != -3)
                        {
                            continue;
                        }
                        if (cdata[56].quality >= 4)
                        {
                            continue;
                        }
                        break;
                    }
                    gdata_fighters_guild_quota = 15;
                    gdata_fighters_guild_target = cdata[56].id;
                    chara_vanquish(56);
                    listmax = 0;
                    buff = lang(""s + chara_refstr(gdata_fighters_guild_target, 2) + u8"を"s +
                            gdata_fighters_guild_quota +
                            u8"匹討伐するのが、お前に課せられた試験だ。ノルマを達成したら、私に報告したまえ。"s,
                        u8"The task given to you is this. Find and slay "s +
                            gdata_fighters_guild_quota + u8" "s + chara_refstr(gdata_fighters_guild_target, 2) +
                            u8". When you complete this, talk to me again"s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_unique;
                }
                if (gdata_fighters_guild_quota > 0)
                {
                    listmax = 0;
                    buff = lang(
                        u8"どうした？試験の内容は伝えたはずだ。"s
                            + chara_refstr(gdata_fighters_guild_target, 2)
                            + u8"をあと"s + gdata_fighters_guild_quota
                            + u8"匹討伐してからまた来なさい。"s,
                        u8"You still need to slay "s
                            + gdata_fighters_guild_quota + u8" more "s
                            + chara_refstr(gdata_fighters_guild_target, 2)
                            + u8"."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_unique;
                }
                listmax = 0;
                buff = lang(
                    u8"ほう…どうやらノルマを見事に達成したようだな。"s,
                    u8"Quite impressive...you have accomplished the task."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                gdata(128) = 10000;
                gdata_belongs_to_thieves_guild = 0;
                gdata_belongs_to_fighters_guild = 1;
                gdata_belongs_to_mages_guild = 0;
                gdata_mages_guild_quota = 0;
                gdata_thieves_guild_quota = 0;
                gdata_joining_mages_guild = 0;
                gdata_joining_thieves_guild = 0;
                gdata_joining_fighters_guild = 1000;
                gdata_fighters_guild_quota2 = 0;
                gdata_mages_guild_quota2 = 0;
                gdata_thieves_guild_quota2 = 0;
                txt(lang(
                    u8"クエストを達成した！"s,
                    u8"You have completed the quest!"s));
                snd(51);
                snd(44);
                txtef(2);
                txt(lang(
                    u8"ジャーナルが更新された。"s,
                    u8"Your journal has been updated."s));
                txtef(5);
                txt(lang(
                    u8"戦士ギルドに加入した！"s,
                    u8"You have joined the Fighters Guild!"s));
                listmax = 0;
                buff = lang(
                    u8"おめでとう…合格だ。今日からお前は戦士ギルドの一員となった。以後はギルドの規約を守り、ノルマをしっかりこなすように。"s,
                    u8"Congratulations. You are a formal member of the Fighters Guild now. You can now use this stairs to enter the office. Always conform to the guild's rule and perform your tasks."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                cell_movechara(tc, 29, 2);
                cdata[tc].initial_position.x = 29;
                cdata[tc].initial_position.y = 2;
            }
            return talk_result_t::talk_end;
        }
        cell_movechara(tc, 29, 2);
        cdata[tc].initial_position.x = 29;
        cdata[tc].initial_position.y = 2;
        if (gdata_fighters_guild_quota2 == 0)
        {
            ELONA_APPEND_RESPONSE(
                1, lang(u8"ノルマを貰う"s, u8"Do you have any tasks for me?"s));
        }
        else
        {
            ELONA_APPEND_RESPONSE(
                2, lang(u8"ノルマを報告する"s, u8"About my task."s));
        }
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        buff = lang(
            u8"ようこそ戦士ギルドへ、"s + ranktitle(8) + u8"の"s + cdatan(0, 0)
                + u8"…どうぞ中にお入り下さい。"s,
            u8"Welcome to the Fighters Guild, "s + ranktitle(8) + u8" "s
                + cdatan(0, 0) + u8"... Please come in."s);
        talk_window_query();
        if (chatval == 1)
        {
            while (1)
            {
                flt(cdata[0].level + 10);
                chara_create(56, 0, -3, 0);
                if (the_character_db[cdata[56].id]->rarity / 1000 < 70)
                {
                    continue;
                }
                if (cdata[56].relationship != -3)
                {
                    continue;
                }
                if (cdata[56].quality >= 4)
                {
                    continue;
                }
                break;
            }
            gdata_fighters_guild_quota = 2 + rnd(3);
            gdata_fighters_guild_target = cdata[56].id;
            chara_vanquish(56);
            gdata_fighters_guild_quota2 = 1;
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"良い心がけです。あなたにランク昇格のためのノルマを与えましょう。"s +
                    chara_refstr(gdata_fighters_guild_target, 2) + u8"をあと"s + gdata_fighters_guild_quota +
                    u8"匹討伐してからまた来なさい。昇進のための審査会に報告してあげましょう。"s,
                u8"There's a task for you. Go find and slay "s + gdata_fighters_guild_quota +
                    u8" "s + chara_refstr(gdata_fighters_guild_target, 2) +
                    u8". Then we will think about your promotion."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_unique;
        }
        if (chatval == 2)
        {
            if (gdata_fighters_guild_quota > 0)
            {
                listmax = 0;
                buff = lang(
                    u8"どうしました？まだノルマが残っていますよ。"s,
                    u8"You have your task to complete."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_unique;
            }
            gdata_fighters_guild_quota2 = 0;
            flt(51 - gdata(128) / 200, calcfixlv(3));
            flttypemajor = 10000;
            itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            flt();
            itemcreate(
                -1,
                54,
                cdata[0].position.x,
                cdata[0].position.y,
                10000 - gdata(128) + 1000);
            flt();
            itemcreate(
                -1,
                55,
                cdata[0].position.x,
                cdata[0].position.y,
                clamp(4 - gdata(128) / 2500, 1, 4));
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            modrank(8, 500, 8);
            listmax = 0;
            buff = lang(
                u8"確かにノルマの達成を確認しました。早速審査会を開いてあなたの功績を報告しましょう。"s,
                u8"You've done very well. I will give a report of your achievement to the council."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        return talk_result_t::talk_end;
    case 301:
        if (gdata_minotaur_king == 1000)
        {
            listmax = 0;
            buff = lang(
                u8"おお、おぬしか。先の依頼の件、恩に着るぞ。どうだ、わしの部下になる気はないか？"s,
                u8"Ahh it's you. I owe you for what you've done for me. What do you say? Why don't you join my unit?"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_minotaur_king == 0)
        {
            ELONA_APPEND_RESPONSE(1, lang(u8"まかせて"s, u8"Leave it to me!"s));
            ELONA_APPEND_RESPONSE(
                0, lang(i18n::_(u8"ui", u8"bye"), u8"No way."s));
            buff = lang(
                u8"困った…困ったぞ。そこのおぬし、良いところに来た。実はヨウィンがミノタウロスの軍による侵攻の危機にさらされておるのだ。ヨウィンの村長とは親しくしておって、一軍を討伐に向かわせたいのだが、今は何やら不穏な空気がパルミアを包んでいる。城から離れるわけにはいかないのだ。そこで、冒険者のおぬしに依頼したい。ミノタウロスを退治してきてはくれぬか？報酬はもちろん用意しよう。"s,
                u8"What do I do about this... You, over there... You couldn't have gotten here a moment too soon. Yowyn is in great danger of being destroyed by the minotaur legion. The mayor of Yowyn is a close friend of mine and I don't want to leave him out in the cold. I want to send a detachment to reinforce him but I can't. The current political climate in Palmia is too volatile and the troops must remain in the castle. That's why I'm asking an adventurer like you. Will you attack the minotaur's camp for me? I will reward you handsomely if you do this."s);
            talk_window_query();
            if (chatval != 1)
            {
                listmax = 0;
                buff = lang(
                    u8"やはり、おぬしには無理か…"s,
                    u8"I knew you'd refuse... and after all, why wouldn't you?"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                return talk_result_t::talk_end;
            }
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            listmax = 0;
            buff = lang(
                u8"なに、真か！では早々にミノタウロスの巣窟に向かい、首領を退治して来てもらいたい。場所は確かヨウィンの南と聞いておる。頼むぞ！"s,
                u8"What? You will? Great... Head to the Minotaur's Nest south of Yowyn and take the head of the minotaurs' king. Godspeed, "s
                    + cdatan(0, 0) + u8"."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_minotaur_king = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_minotaur_king == 1)
        {
            listmax = 0;
            buff = lang(
                u8"どうした？おぬしが早くせんと、ヨウィンが危ないのだ。頼むぞ。"s,
                u8"What's wrong? You must make haste. Yowyn is in grave danger."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        if (gdata_minotaur_king == 2)
        {
            listmax = 0;
            buff = lang(
                u8"おぬしか、待っておったぞ。報告はいい。すでに、ミノタウロスの王を倒した英雄のことは、この耳に伝わっておるわい。わしの感謝の印だ、受け取ってくれ。"s,
                u8"You've returned. I've been waiting for you. I've already heard the good word about the hero who crushed the minotaur king. Take this as a sign of my eternal gratitude."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            flt();
            nostack = 1;
            itemcreate(-1, 630, cdata[0].position.x, cdata[0].position.y, 0);
            fixmaterial = 31;
            change_item_material();
            flt();
            itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, 50000);
            flt();
            itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, 4);
            txt(lang(
                u8"クエストを達成した！"s, u8"You have completed the quest!"s));
            snd(51);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            gdata_minotaur_king = 1000;
            return talk_result_t::talk_end;
        }
        break;
    case 302:
        if (cdata[0].gold <= 10)
        {
            listmax = 0;
            buff = lang(
                u8"チッ、一文無しの乞食"s + _ka() + u8"とっとといっちまい"s
                    + _na(),
                u8"Bah, a beggar without a penny. What a waste of time! Just go away!"s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        ELONA_APPEND_RESPONSE(1, lang(u8"返り討ちにする"s, u8"Try me."s));
        ELONA_APPEND_RESPONSE(0, lang(u8"降参する"s, u8"I surrender."s));
        buff = lang(u8"おまえさん、ついてない"s + _na() + _ore(3) +
                u8"達は泣く子も黙る冷血な盗賊団、その名も"s + gdatan(1) +
                _da() + u8"命が惜しければ、おとなしく荷車の積荷と金貨"s +
                cdata[0].gold / 5 + u8"枚を渡すがいい"s + _yo(),
            u8"Halt, halt, traveler. You're a quite fortunate one. Before you is the renowned band of legendary brigands \""s +
                gdatan(1) +
                u8"\" that the mere mention of its name is enough to silence a naughty child. Yet we will spare your life for only a toll of "s +
                cdata[0].gold / 5 +
                u8" gold pieces and your cargos. Quite fortunate indeed."s);
        chatesc = 0;
        talk_window_query();
        if (chatval == 0)
        {
            snd(12);
            cdata[0].gold -= cdata[0].gold / 5;
            for (const auto& cnt : items(0))
            {
                if (inv[cnt].number > 0)
                {
                    if (the_item_db[inv[cnt].id]->is_cargo == 1)
                    {
                        txt(lang(
                            itemname(cnt) + u8"を渡した。"s,
                            u8"You hand over "s + itemname(cnt) + u8"."s));
                        inv[cnt].number = 0;
                    }
                }
            }
            refresh_burden_state();
            listmax = 0;
            buff = lang(u8"なかなか賢明な判断"s + _da(), u8"A wise choice."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            levelexitby = 4;
            chatteleport = 1;
            snd(49);
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = lang(
            u8"いい度胸"s + _da() + u8"…しかし、賢い選択とは言えない"s + _na()
                + u8"ここがおまえさんの墓場"s + _da(2),
            u8"You've got some guts. But your decision sure ain't a wise one. This will be your grave, kid."s);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    case 322:
        if (gdata_little_sister == 0)
        {
            listmax = 0;
            buff = lang(
                u8"よく聞きなさい。もしあなたがいつかリトルシスターに出会ったら、あの子達に救いの手を差し伸べてあげて。見た目こそ化け物のように映るかもしれないけど、彼女たちがまた元の可愛らしい笑顔を取り戻せるように、私は研究を続けている。だから、お願い。この道具を使ってリトルたちを私の元に運んで。あなたへのお礼は、いつか必ず。"s,
                u8"Please, hear me out. If you should happen to run into any little sisters during your travels, please help them out. They seem to be monsters at first glance, but I'm doing important research that will return these girls to their gentle smiling nature. Please I beg of you... use these balls to bring the little sisters to me. I'd be very grateful, perhaps I'd even reward you."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            gdata_little_sister = 0;
            flt();
            itemcreate(-1, 699, cdata[0].position.x, cdata[0].position.y, 0);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            snd(44);
            txtef(2);
            txt(lang(
                u8"ジャーナルが更新された。"s,
                u8"Your journal has been updated."s));
            gdata_little_sister = 1;
            return talk_result_t::talk_end;
        }
        if (gdata_little_sister > 0)
        {
            ELONA_APPEND_RESPONSE(
                1,
                lang(
                    u8"約束のお礼は？"s,
                    u8"What about the reward you promised me?"s));
            ELONA_APPEND_RESPONSE(
                2,
                lang(
                    u8"捕獲玉を補充したい"s,
                    u8"I need to replenish my supply of little balls."s));
            if (chara_find_ally(319) != -1)
            {
                ELONA_APPEND_RESPONSE(
                    3,
                    lang(
                        u8"リトルシスターを引き渡す"s,
                        u8"(Turn over the little sister.)"s));
            }
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            buff = lang(
                u8"リトルたちを、終わりのない苦痛から解放するべきだという人もいる。でも、大抵の人間はあの子達の力が欲しくて殺すのよ。そう、確かにリトルの肉は人の肉体を進化させる。それでも、私はあの子たちを救う別の道があることを信じているの。…そして覚えておいて。もしあなたがリトルの命を奪うようなことがあれば、いつかその酬いを受ける時がくるから。"s,
                u8"Many people feel we need to free these girls from their never-ending oppression, but there are also scumbags that would murder them for their own personal gain. That's right; they say eating the girls' flesh will evolve the human body. I know there must be a better way to help them... don't forget that. Remember that if you take their lives, you will eventually get what's coming to you. "s);
            talk_window_query();
            if (chatval == 1)
            {
                p = gdata_kill_count_of_little_sister;
                for (int cnt = 1,
                         cnt_end =
                             cnt + (gdata_gift_count_of_little_sister + 1);
                     cnt < cnt_end;
                     ++cnt)
                {
                    p += cnt;
                }
                if (gdata_save_count_of_little_sister >= p || 0)
                {
                    listmax = 0;
                    buff = lang(
                        u8"報酬、そうね。リトルたちが、あなたのために街で落し物を集めてきたのよ。好きなものを選んでちょうだい。あなたが貴重なものを無くした時のために、保留しておいてもいいわ。"s,
                        u8"That's right...your reward. The little sisters have been picking things up for you that people have lost in town. Please, take whatever you like. If you like, you can wait until you've lost something valuable."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    begintempinv();
                    mode = 6;
                    flt();
                    itemcreate(-1, 283, -1, -1, 0);
                    flt();
                    itemcreate(-1, 284, -1, -1, 0);
                    for (int cnt = 0; cnt < 800; ++cnt)
                    {
                        if (cnt == 672)
                        {
                            continue;
                        }
                        randomize(gdata_day + cnt);
                        f = 0;
                        if (itemmemory(0, cnt))
                        {
                            f = 1;
                        }
                        if (cnt == 662)
                        {
                            if (gdata_kamikaze_attack >= 1000)
                            {
                                f = 1;
                            }
                        }
                        if (cnt == 655)
                        {
                            if (gdata_rare_books >= 1000)
                            {
                                f = 1;
                            }
                        }
                        if (cnt == 639)
                        {
                            if (gdata_pael_and_her_mom >= 1000)
                            {
                                f = 1;
                            }
                        }
                        if (f)
                        {
                            flt(cdata[0].level * 3 / 2, calcfixlv(3));
                            int stat = itemcreate(-1, cnt, -1, -1, 0);
                            if (stat == 1)
                            {
                                if (inv[ci].quality < 4)
                                {
                                    inv[ci].number = 0;
                                }
                            }
                        }
                        randomize();
                    }
                    txt(lang(
                        u8"落し物をひとつ貰える。"s,
                        u8"You can choose 1 item."s));
                    invsubroutine = 1;
                    invctrl(0) = 22;
                    invctrl(1) = 4;
                    ctrl_inventory();
                    exittempinv();
                    mode = 0;
                    listmax = 0;
                    buff = lang(
                        u8"お目当てのものはあったかしら？"s,
                        u8"Did you find what you were looking for?"s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                }
                else
                {
                    listmax = 0;
                    buff = lang(
                        u8"あなたにまだその資格はない。リトルたちを連れてきて。報酬はそのあと考えるわ。"s,
                        u8"You haven't brought me enough sisters yet. Bring me a few more and then we'll discuss your reward."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                }
                return talk_result_t::talk_end;
            }
            if (chatval == 2)
            {
                listmax = 0;
                buff = lang(
                    u8"さあ、これを持っていきなさい。重いから注意して。"s,
                    u8"Well then, take this with you. Be careful though, it's heavy."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                flt();
                itemcreate(
                    -1, 699, cdata[0].position.x, cdata[0].position.y, 0);
                txt(lang(
                    u8"何かが足元に転がってきた。"s,
                    u8"Something is put on the ground."s));
                return talk_result_t::talk_end;
            }
            if (chatval == 3)
            {
                txt(lang(
                    u8"リトルシスターを謎の科学者に手渡した。"s,
                    u8"You turn over the little sister."s));
                ++gdata_save_count_of_little_sister;
                txtef(2);
                txt(lang(
                    u8"リトルシスター殺害"s + gdata_kill_count_of_little_sister
                        + u8"回、救出"s + gdata_save_count_of_little_sister
                        + u8"回。"s,
                    u8"You have saved little sister "s
                        + gdata_save_count_of_little_sister
                        + u8" times and killed "s
                        + gdata_kill_count_of_little_sister + u8" times."s));
                chara_vanquish(chara_find_ally(319));
                snd(51);
                listmax = 0;
                buff = lang(
                    u8"ありがとう。あなたの行いに感謝するわ。あなたへのお礼は近いうちに必ず。"s,
                    u8"Thanks, I appreciate what you've done. It won't be long before I can reward you"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
            }
            return talk_result_t::talk_end;
        }
        break;
    case 345:
        if (gdata_blue_capsule_drug >= 3)
        {
            buff = lang(
                u8"どうだい、俺に乗ってみたいかい？"s,
                u8"So, you wanted to ride me right?"s);
            ELONA_APPEND_RESPONSE(1, lang(u8"乗りたい"s, u8"Yes!"s));
            ELONA_APPEND_RESPONSE(
                0, lang(u8"別に乗りたくない"s, u8"Not really."s));
            chatesc = 1;
            talk_window_query();
            if (chatval == 1)
            {
                f = chara_get_free_slot_ally();
                if (f == 0)
                {
                    listmax = 0;
                    buff = lang(
                        u8"おっと、これ以上仲間を連れて行けないようだぜ。"s,
                        u8"Oops, it seems your party is already full."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                }
                listmax = 0;
                buff = lang(u8"そうこなくっちゃ！"s, u8"That's the spirit!"s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                rc = tc;
                new_ally_joins();
                gdata_blue_capsule_drug = 0;
                return talk_result_t::talk_end;
            }
            listmax = 0;
            buff = lang(u8"まあ、いいさ。"s, u8"If you say so."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        {
            int stat = inv_find(771, 0);
            if (stat != -1)
            {
                buff = lang(
                    u8"それはカプセル・ドラッグ！…なあ、それ譲ってくれよ。"s,
                    u8"That-that's a capsule drug! ...hey, you want to give it to me?"s);
                ELONA_APPEND_RESPONSE(1, lang(u8"譲る"s, u8"Take it."s));
                ELONA_APPEND_RESPONSE(0, lang(u8"断る"s, u8"Nope."s));
                chatesc = 1;
                talk_window_query();
                if (chatval == 1)
                {
                    int stat = inv_find(771, 0);
                    --inv[stat].number;
                    txt(lang(
                        u8"カプセルドラッグを1錠渡した。"s,
                        u8"You hand him a capsule drug."s));
                    snd(13);
                    listmax = 0;
                    buff = lang(u8"いいねえ。"s, u8"Great, you are great."s);
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    ++gdata_blue_capsule_drug;
                    return talk_result_t::talk_end;
                }
            }
        }
        listmax = 0;
        buff =
            lang(u8"気安く話しかけんな。"s, u8"Stay away from me, will ya?"s);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    case 348:
        if (gdata_current_map != 33 || adata(29, gdata_current_map) == 0)
        {
            break;
        }
        if (cdata[0].god_id == core_god::jure)
        {
            listmax = 0;
            buff = lang(
                u8"ああ、あなた既に信者さんでしょ？悪いけど、新規契約しか受け付けてないからさ。"s,
                u8"Ah, you already believe in Jure right? Sorry bro, but we are only looking for new contracts."s);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            return talk_result_t::talk_end;
        }
        ELONA_APPEND_RESPONSE(
            1,
            lang(
                u8"ジュア教に改宗する"s,
                u8"I will become a faithful servant of Jure."s));
        ELONA_APPEND_RESPONSE(0, lang(u8"興味ない"s, u8"Not interested."s));
        buff = lang(
            u8"ジュア教団では、ただ今他の神からの乗り換えキャンペーン実施中だ！聖夜祭の期間中なら、改宗によるペナルティは払わなくていいよ。さらになんと、今なら無料で数量限定のジュア様の抱き枕も付けちゃうよ！お客さん、このチャンスを見逃す手はないよ。"s,
            u8"We are running a special campaign to help you join our religion! Be a brother of Jure today and win free body pillow of Jure! During the festival, you won't have to pay penalty to convert your religion neither. So what are you waiting? Sign up now!"s);
        chatesc = 1;
        talk_window_query();
        if (chatval == 1)
        {
            ELONA_APPEND_RESPONSE(1, lang(u8"はい"s, u8"Yes."s));
            ELONA_APPEND_RESPONSE(0, lang(u8"いいえ"s, u8"No."s));
            buff = lang(
                u8"よし、本当に改宗していいね？"s,
                u8"Okie, just making sure. Do you really want to convert your religion?"s);
            chatesc = 1;
            talk_window_query();
            if (chatval == 1)
            {
                listmax = 0;
                buff = lang(
                    u8"あざーっす！やっと今日のノルマが達成できたよ。"s,
                    u8"Thanks, bro! I just filled my daily quota."s);
                tc = tc * 1 + 0;
                ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
                chatesc = 1;
                ELONA_TALK_SCENE_CUT();
                txt(lang(
                    u8"何かが足元に転がってきた。"s,
                    u8"Something is put on the ground."s));
                flt();
                itemcreate(
                    -1, 767, cdata[0].position.x, cdata[0].position.y, 0);
                cdata[0].god_id = core_god::int2godid(6);
                switch_religion();
                return talk_result_t::talk_end;
            }
        }
        listmax = 0;
        buff = lang(u8"ちっ！"s, u8"Shit!"s);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }

    listmax = 0;
    buff = lang(
        u8"…(あなたを無視している)"s, u8"("s + he(tc) + u8" ignores you...)"s);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return talk_result_t::talk_end;
}



} // namespace elona
