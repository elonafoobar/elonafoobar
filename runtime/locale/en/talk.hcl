locale {
    talk {
        will_not_listen = "${name(_1)} won't listen."
        is_sleeping = "${name(_1)} is sleeping."
        is_busy = "${name(_1)} is in the middle of something."

        window {
            impress ="Impress"
            attract ="Attract"
            fame = " Fame: "
            shop_rank = " Shop Rank:"
        }

        trainer {
            leave = "Come see me again when you need more training."
            cost {
                training = "Training ${_1} will cost you ${_2} platinum pieces."
                learning = "Learning ${_1} will cost you ${_2} platinum pieces."
            }
            finish {
                training = "Well done. You've got more room to develop than anyone else I've ever drilled. Keep training."
                learning = "I've taught you all that I know of the skill. Now develop it by yourself."
            }
        }

        shop {
            invest {
                ask = "Oh, do you want to invest in my shop? It will cost you ${_1} golds. I hope you got the money."
                choices {
                    invest = "Invest"
                    reject = "Reject"
                }
                thanks = "Thanks!"
            }
        }

        # TODO: organize
        visitor {
            wanted_to_say_hi = "I just wanted to say hi."

            adventurer {
                new_year {
                    dialog_1 = "Happy new year!"
                    dialog_2 = "I've brought you a gift today, here."
                    throws = "${name(_1)} throws you ${itemname(_1, 1)}."
                }
                hate {
                    dialog = "You scum! You won't get away from me now!"
                    text = "\"Eat this!\""
                    throws = "${name(_1)} throws molotov."
                }
                like {
                    dialog = "Here, take this!"
                    receive = "You receive ${itemname(_1, 1)}."
                    wonder_if = "Wonder if we can reach 100 friends? ♪"
                }
                trainer {
                    learn {
                        dialog = "I can teach you the art of ${_1} for a friendly price of ${_2} platinum pieces. Do you want me to train you?"
                        accept = "Teach me the skill."
                        after = "Fantastic! You've learned the skill in no time. I'm glad I could help."
                    }
                    train {
                        dialog = "I can train your ${_1} skill for a friendly price of ${_2} platinum pieces. Do you want me to train you?"
                        accept = "Train me."
                        after = "Marvelous! The training is now complete. I think you've improved some potential."
                    }
                    pass = "I think I'll pass."
                    ask_again = "I see. I'll ask you again at some time in the future."
                }
                friendship {
                    dialog = "As a pledge of friendship, here's something for you!"
                    no_empty_spot = "Your home has no empty spot..."
                    receive = "You receive ${itemname(_1, 1)}."
                }
                souvenir {
                    dialog = "I just stopped by to see you. Oh, I happen to have a gift for you too."
                    inventory_is_full = "Your inventory is full..."
                    receive = "You receive ${itemname(_1, 1)}."
                }
                materials {
                    dialog = "I found these during my journey. Thought you could find them useful."
                    receive = "${name(_1)} gives you a bag full of materials."
                }
                favorite_skill {
                    dialog = "${_1} is one of my favorite skills."
                }
                favorite_stat {
                    dialog = "I'm proud of my good ${_1}."
                }
                conversation {
                    dialog = "Hey ${basename(_1)}, how's your journey? I was bored to death so I decided to make a visit to you!"
                    hold = "You hold an amusing conversation with ${name(_1)}!"
                }
                drink {
                    dialog = "Let's have a drink and deepen our friendship!"
                    cheers = "\"Cheers!\""
                }
            }
            trainer {
                no_more_this_month = "No more training in this month."
                dialog {
                    member = "As a member of ${_1} you have to forge your talent to live up to our reputation. For only ${_2} platinum coins, I'll improve the potential of your talent."
                    nonmember = "Training! Training! At the end, only thing that saves your life is training! For only ${_1} platinum coins, I'll improve the potential of your talent."
                }

                choices {
                    not_today = "Not today."
                    improve = "I want to improve ${_1}."
                }
                regret = "You'll regret this!"
                potential_expands = "${name(_1)}${his_owned(_1)} potential of ${_2} greatly expands."
                after = "Good. You show a lot of potential."
            }
            beggar {
                no_money = "I got no money to buy food. Will you spare me some coins?"
                spare = "You spare ${_1} gold pieces"
                after = "Thanks! I'll never forget this."
                cheap = "You're so cheap!"
            }
            punk {
                choices {
                    yes = "Yes."
                    no = "No."
                    come_on = "Come on!"
                }
                are_you_ready = "So, are you ready?"
                no_turning_back = "Okay, no turning back now!"
                hump = "Hump!"
            }
            mysterious_producer {
                want_to_be_star = "You want to be a star?"
                no_turning_back = "Okay, no turning back now!"
            }
            merchant {
                choices {
                    buy = "I want to buy something."
                    sell = "I want to sell something."
                    not_now = "Not now."
                }
                dialog = "This is your lucky day. I wouldn't normally show my discounted goods to commoners but since I feel so good today..."
                regret = "I hope you won't regret it later."
            }
        }
    }
}
