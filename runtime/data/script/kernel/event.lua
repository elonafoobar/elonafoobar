local EventTree = require "event_tree"

hooks = {}
instanced_hooks = {}

reg = {}
instanced_reg = {}

Event = {}

function table.find(tbl, func, ...)
    for k, v in pairs(tbl) do
        if func(v, k, ...) then
            return v, k
        end
    end
    return nil
end

local function is_registered(event_id, cb, instance)
   if instance then
      if instanced_reg[event_id] == nil then
         instanced_reg[event_id] = {}
      end
      if instanced_reg[event_id][instance] == nil then
         instanced_reg[event_id][instance] = {cb = true}
         return false
      end
      if instanced_reg[event_id][instance][cb] then
         return true
      end
      instanced_reg[event_id][instance][cb] = true
      return false
   else
      if reg[event_id] == nil then
         reg[event_id] = {}
         return false
      end
      if reg[event_id][cb] then
         return true
      end
      reg[event_id][cb] = true
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
   print("reg instance " .. tostring(instance))
   if is_registered(event_id, cb, instance) then
      error("An identical callback was registered twice for an event: " .. event_id)
      return
   end

   local events = get_events(event_id, instance)
   events:insert(priority, cb)
end

function Event.register(event_id, cb, opts)
   if opts == nil then
      opts = {}
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
         register(event_id, cb, priority, instance)
      end
   end
end

local function run_event(priority, callbacks, args)
   for _, cb in ipairs(callbacks) do
      local result = cb(args)

      if result == nil or args.stop then
         return false
      end
   end

   return true
end

function Event.trigger(event_id, args, opts)
   local instances = opts.instances
   if type(instances) ~= "table" then
      instances = {instances}
   end

   for _, instance in ipairs(instances) do
      local events = get_events(event_id, instance)
      events:traverse(run_event, args)
   end

   events = get_events(event_id)
   events:traverse(run_event, args)

   return args
end
