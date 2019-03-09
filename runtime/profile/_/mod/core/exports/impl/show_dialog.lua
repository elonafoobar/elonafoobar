local Chara = Elona.require("Chara")
local I18N = Elona.require("I18N")
local Input = Elona.require("Input")
local Internal = Elona.require("Internal")
local table = Elona.require("table")

local function dialog_error(talk, msg, err)
   if err then
      error("Dialog error in " .. talk.id .. ": " .. msg)
   else
      error("Dialog error in " .. talk.id .. ": " .. msg .. ":\n    " .. err)
   end
end

local function resolve_key(key, talk)
   local get = talk.dialog.root .. "." .. key
   if I18N.get_optional(get) == nil then
      get = key
   end
   return get
end

--- Convert a response localization key to the full localization key.
--- It can be one of the following.
---  * __MORE__                - "(More)"
---  * __BYE__                 - "Bye bye."
---  * key.fragment            - core.locale.dialog.root.key.fragment
---  * core.locale.dialog.key  - core.locale.dialog.key
local function resolve_response(response, talk)
   if response == nil then
      response = "__MORE__"
   end
   if response == "__BYE__" then
      return "core.locale.ui.bye"
   elseif response == "__MORE__" then
      return "core.locale.ui.more"
   end
   return resolve_key(response, talk)
end

--- Opens a single talk window choice.
-- @tparam table talk Dialog control data.
-- @tparam string text String to display (not locale key)
-- @tparam table choices List of choices in format {"response_id", "core.locale.key"}
-- @tparam[opt] num default_choice index of default choice if window is canceled
-- @treturn string Response ID of the choice selected.
local function query(talk, text, choices, default_choice)
   local image = talk.speaker.portrait
   if image == "" then
      image = talk.speaker.image
   end
   local show_impress = true
   if talk.speaker.quality == "Special" and not Chara.is_ally(talk.speaker) then
      show_impress = false
   end

   if #choices == 1 then
      default_choice = 0
   end

   local the_choices = {}
   for i, choice in ipairs(choices) do
      the_choices[i] = I18N.get(resolve_response(choice[2], talk))
      if default_choice == nil and choice[1] == "__END__" then
         default_choice = i - 1
      end
   end

   local result
   if show_impress then
      result = Input.prompt_dialog(text, image, Internal.speaker_name(talk.speaker), default_choice, the_choices, talk.speaker.impression, talk.speaker.interest)
   else
      result = Input.prompt_dialog(text, image, Internal.speaker_name(talk.speaker), default_choice, the_choices)
   end

   return choices[result + 1][1]
end

--- Initializes the dialog control data.
-- @tparam LuaCharacter speaker Character who is speaking.
-- @tparam core.dialog dialog Dialog data.
-- @tparam string id Dialog data ID.
local function make_talk(speaker, dialog, id)
   return {
      id = id,
      speaker = speaker,
      dialog = dialog,
      say = function(self, key, response)
         if response == nil then
            response = "__MORE__"
         end
         local resolved = resolve_key(key, self)
         query(self, I18N.get(resolved), {{"dummy", resolve_response(response, self)}})
      end
   }
end

local function step_dialog(dialog, node_data, talk, state)
   if node_data.choice == "__END__" then
      return nil
   end
   if node_data.choice == "__IGNORED__" then
      return nil
   end
   if node_data.choice == nil then
      return nil
   end

   local node = dialog.nodes[node_data.choice]
   if node == nil then
      dialog_error(talk, "No node with ID " .. node_data.choice .. " found")
   end

   local next_node = nil

   if type(node) == "function" then
      -- Run function. It is expected to return either a string or
      -- table containing the next node to jump to.
      local ok, result = pcall(node, talk, state, {})
      if ok then
         if type(result) == "string" then
            next_node = {choice = result, opts = {}}
         elseif type(result) == "table" then
            next_node = result
         end
      else
         dialog_error(talk, "Error running dialog inline function", result)
      end
   elseif type(node) == "table" then
      -- Parse table structure for dialog data.
      -- text: array of text entries, displayed in order.
      --     text[1][1]: locale fragment or key, or function.
      --     text[1].args: function returning table of arguments to localization
      --     text[1].speaker: core.chara ID of speaker to display, if they are in this map
      --     text[1].choice: locale key of default choice. Defaults to "more" or "bye".
      -- choices: array of choices, displayed at last text entry. If nil, end the dialog at the last one.
      --     choices[1][1]: Node ID to jump to
      --     choices[1][2]: locale key of choice. Defaults to "more" or "bye".
      -- on_finish: Function run when this node is exited.
      local texts = node.text

      for i, text in ipairs(texts) do
         if texts[i+1] == nil then
            if type(text) ~= "table" then
               dialog_error(talk, "Last text entry must be table (got: " .. type(text) .. ")")
            end
         end

         if type(text) == "table" then
            -- Obtain arguments to I18N.get().
            local args = {}
            if text.args then
               local ok
               ok, args = pcall(text.args, talk, state)
               if not ok then
                  dialog_error(talk, "Error getting I18N arguments", args)
               end
            end

            -- Get localization key of default response ("more", "bye").
            local choice_key = text.choice
            if choice_key == nil then
               if texts[i+1] == nil then
                  choice_key = "__BYE__"
               else
                  choice_key = "__MORE__"
               end
            end

            -- Change speaking character.
            if text.speaker ~= nil then
               local found = Chara.find(text.speaker)
               if found ~= nil then
                  talk.speaker = found
               end
            end

            -- Build choices. Default to ending the dialog.
            local choices = node.choices
            if choices == nil then
               choices = {{"__END__", choice_key}}
            end

            -- Set the default choice to select if window is
            -- cancelled. If nil, prevent cancellation.
            local default_choice = nil
            if text.default_choice ~= nil then
               for j, choice in ipairs(choices) do
                  if choice[1] == text.default_choice then
                     default_choice = j - 1
                  end
               end
            end

            -- Resolve localized text.
            local key = talk.dialog.root .. "." .. text[1]
            local tex = I18N.get_optional(key, table.unpack(args))
            if tex == nil then
               tex = I18N.get(text[1], table.unpack(args))
            end

            -- Prompt for choice if on the last text entry, otherwise
            -- show single choice.
            if texts[i+1] == nil then
               local choice = query(talk, tex, choices, default_choice)
               next_node = {choice = choice, opts = {}}
            else
               query(talk, tex, {{"dummy", choice_key}})
            end
         elseif type(text) == "function" then
            -- Call an arbitrary function. The result is ignored.
            local ok, err = pcall(text, talk, state, {})
            if not ok then
               dialog_error(talk, "Error running text function", err)
            end
         end
      end

      -- Run on_finish callback.
      if node.on_finish then
         local ok, result = pcall(node.on_finish, talk, state, {})
         if not ok then
            dialog_error(talk, "Error running on_finish function", result)
         end
      end
   else
      dialog_error(talk, "Invalid node, must be string or table (got: " .. type(node) .. ")")
   end

   return next_node
end

local function show_dialog(chara, id)
   local dialog = data.raw["core.dialog"][id]
   if dialog == nil then
      error("No such dialog " .. id)
   end
   local talk = make_talk(chara, dialog, id)
   local state = {}
   local next_node = {choice = "__start", opts = {}}

   while next_node ~= nil do
      next_node = step_dialog(dialog, next_node, talk, state)
   end
end

return show_dialog
