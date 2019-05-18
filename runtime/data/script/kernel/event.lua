local EventTree = require "event_tree"

local hooks = {}
local instanced_hooks = {}

local reg = {}
local instanced_reg = {}

local event_types = {}
local loaded = false

Event = {}

function table.find(tbl, func, ...)
    for k, v in pairs(tbl) do
        if func(v, k, ...) then
            return v, k
        end
    end
    return nil
end

local function check_event(event_id)
   if event_types[event_id] == nil then
      error("Unknown event type \"" .. event_id .. "\"")
   end
end

function remove_unknown_events(event_table)
   for k, _ in pairs(event_table) do
      event_types[k] = true
   end

   for k, _ in pairs(hooks) do
      check_event(k)
   end

   for k, _ in pairs(instanced_hooks) do
      check_event(k)
   end

   loaded = true
end

local function get_instance(instance)
   if instance == nil then
      return nil
   end
   if type(instance) == "table" and instance.__handle then
      return instance.__uuid
   end
   return instance
end

local function is_registered(event_id, cb, instance)
   if instance then
      if instanced_reg[event_id] == nil then
         instanced_reg[event_id] = {}
      end
      if instanced_reg[event_id][instance] == nil then
         instanced_reg[event_id][instance] = {}
         return false
      end
      if instanced_reg[event_id][instance][cb] then
         return true
      end
      return false
   else
      if reg[event_id] == nil then
         reg[event_id] = {}
         return false
      end
      if reg[event_id][cb] then
         return true
      end
      return false
   end
end

local function get_events(event_id, instance)
   if instance == nil then
      if hooks[event_id] == nil then
         hooks[event_id] = EventTree.new()
      end
      return hooks[event_id]
   else
      if instanced_hooks[event_id] == nil then
         instanced_hooks[event_id] = {}
      end
      if instanced_hooks[event_id][instance] == nil then
         instanced_hooks[event_id][instance] = EventTree.new()
      end
      return instanced_hooks[event_id][instance]
   end
end

local function register(event_id, cb, priority, instance)
   if is_registered(event_id, cb, instance) then
      error("An identical callback was registered twice for an event: " .. event_id)
      return
   end

   if instance then
      instanced_reg[event_id][instance][cb] = true
   else
      reg[event_id][cb] = true
   end

   local events = get_events(event_id, instance)
   events:insert(priority, cb)
end

function Event.register(event_id, cb, opts)
   if opts == nil then
      opts = {}
   end
   if cb == nil then
      error("No callback passed to Event.register (" .. event_id .. ")")
      return
   end

   if loaded then
      check_event(event_id)
   end

   local instances = opts.instances
   if type(instances) ~= "table" or instances.__handle then
      instances = {instances}
   end

   local priority = opts.priority or 1000

   if #instances == 0 then
      register(event_id, cb, priority)
   else
      for _, instance in ipairs(instances) do
         local instance = get_instance(instance)
         register(event_id, cb, priority, instance)
      end
   end
end

function Event.unregister(event_id, cb, opts)
   if opts == nil then
      opts = {}
   end
   if loaded then
      check_event(event_id)
   end

   local instance = get_instance(opts.instance)

   if not is_registered(event_id, cb, instance) then
      return
   end

   if instance and instanced_reg[event_id][instance] then
      local events = get_events(event_id, instance)
      events:remove_value(cb)
      instanced_reg[event_id][instance][cb] = nil
   elseif reg[event_id][cb] then
      local events = get_events(event_id)
      events:remove_value(cb)
      reg[event_id][cb] = nil
   end
end

local function run_event(priority, callbacks, args)
   for _, cb in ipairs(callbacks) do
      local result = cb(args)

      if args.stop then
         return false
      end
   end

   return true
end

function Event.trigger(event_id, args, opts)
   if args == nil then
      args = {}
   end
   if type(args) ~= "table" then
      error("Event.register must be passed a table of event arguments as a second argument (got: " .. type(args) .. ").")
   end
   if opts == nil then
      opts = {}
   end
   if loaded then
      check_event(event_id)
   end

   local instances = opts.instances
   if type(instances) ~= "table" then
      instances = {instances}
   end

   for _, instance in ipairs(instances) do
      local instance = get_instance(instance)
      local events = get_events(event_id, instance)
      events:traverse(run_event, args)
   end

   events = get_events(event_id)
   events:traverse(run_event, args)

   return args
end
