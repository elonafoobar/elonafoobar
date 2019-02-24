LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := elona

SDL_PATH := ../../android/external

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/SDL2/include \
$(LOCAL_PATH)/$(SDL_PATH)/SDL2_mixer \
$(LOCAL_PATH)/$(SDL_PATH)/SDL2_image \
$(LOCAL_PATH)/$(SDL_PATH)/SDL2_ttf \
$(LOCAL_PATH)/$(SDL_PATH)/boost/include \
$(LOCAL_PATH)/$(SDL_PATH)/lua/src

LOCAL_CPP_FEATURES := exceptions rtti

# Add your application source files here...
LOCAL_SRC_FILES := \
ability.cpp \
access_character_info.cpp \
access_item_db.cpp \
activity.cpp \
adventurer.cpp \
ai.cpp \
animation.cpp \
area.cpp \
audio.cpp \
autopick.cpp \
blending.cpp \
browser.cpp \
buff.cpp \
building.cpp \
calc.cpp \
card.cpp \
casino.cpp \
casino_card.cpp \
cell_draw.cpp \
character.cpp \
character_making.cpp \
character_status.cpp \
class.cpp \
command.cpp \
crafting.cpp \
ctrl_file.cpp \
ctrl_inventory.cpp \
debug.cpp \
dmgheal.cpp \
draw.cpp \
element.cpp \
elonacore.cpp \
enchantment.cpp \
equipment.cpp \
event.cpp \
filesystem.cpp \
fish.cpp \
food.cpp \
fov.cpp \
gdata.cpp \
get_card_info.cpp \
get_random_npc_id.cpp \
globals.cpp \
god.cpp \
i18n.cpp \
init.cpp \
initialize_map.cpp \
initialize_map_types.cpp \
input.cpp \
input_prompt.cpp \
item.cpp \
item_load_desc.cpp \
item_material.cpp \
itemgen.cpp \
loading_screen.cpp \
log.cpp \
magic.cpp \
main.cpp \
main_menu.cpp \
map.cpp \
map_cell.cpp \
map_chara_filter.cpp \
map_special_events.cpp \
map_trainer_skills.cpp \
mapgen.cpp \
mef.cpp \
menu.cpp \
menu_quick_menu.cpp \
message.cpp \
message_log.cpp \
network.cpp \
proc_event.cpp \
quest.cpp \
race.cpp \
random.cpp \
random_event.cpp \
save.cpp \
save_update.cpp \
set_item_info.cpp \
shop.cpp \
spec.cpp \
status_ailment.cpp \
std.cpp \
talk.cpp \
talk_house_visitor.cpp \
talk_npc.cpp \
talk_unique.cpp \
tcg.cpp \
testing.cpp \
text.cpp \
trait.cpp \
turn_sequence.cpp \
turn_sequence_pc_actions.cpp \
ui.cpp \
ui_menus.cpp \
variables.cpp \
wish.cpp \
 \
data/init.cpp \
data/types.cpp \
data/util.cpp \
 \
lua_env/api_manager.cpp \
lua_env/data_manager.cpp \
lua_env/event_manager.cpp \
lua_env/export_manager.cpp \
lua_env/handle_manager.cpp \
lua_env/i18n_function_manager.cpp \
lua_env/interface.cpp \
lua_env/lua_console.cpp \
lua_env/lua_env.cpp \
lua_env/mod_manager.cpp \
lua_env/mod_manifest.cpp \
 \
lua_env/enums/enums.cpp \
 \
lua_env/lua_api/lua_api.cpp \
 \
lua_env/lua_class/lua_class.cpp \
lua_env/lua_class/lua_class_ability.cpp \
lua_env/lua_class/lua_class_character.cpp \
lua_env/lua_class/lua_class_item.cpp \
lua_env/lua_class/lua_class_position.cpp \
 \
config/config.cpp \
config/config_def.cpp \
config/set_option.cpp \
config/create_config_screen.cpp \
 \
dialog/dialog.cpp \
dialog/dialog_data.cpp \
dialog/dialog_decoder.cpp \
 \
keybind/input_context.cpp \
keybind/key_names.cpp \
keybind/keybind.cpp \
keybind/keybind_actions.cpp \
keybind/keybind_deserializer.cpp \
keybind/keybind_manager.cpp \
keybind/keybind_serializer.cpp \
 \
pic_loader/pic_loader.cpp \
 \
profile/profile_manager.cpp \
 \
../version.cpp


LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer SDL2_image SDL2_ttf boost_filesystem boost_system lua util snail

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

LOCAL_CFLAGS += -Wextra -Wall -ffast-math $(LTO)

LOCAL_LDFLAGS += $(LOCAL_CFLAGS) $(LTO) -fPIC

include $(BUILD_SHARED_LIBRARY)
