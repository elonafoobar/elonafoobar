require './ctype.rb'
require './builtins.rb'



class TypeTable
  def initialize
    @table = BUILTINS.clone

    @table[:randomname] = FunctionType.new(BasicType::STRING, [BasicType::INT])
  end

  def dump_ctype(out)
    @table[:randomname] = FunctionType.new(BasicType::STRING, [BasicType::INT])

    out.puts 'inline int cnt;'
    out.puts 'inline int strsize;'
    out.puts 'inline int stat;'
    out.puts 'inline std::string refstr;'
    @table.each do |k, v|
      if v.valid? && !SPECIAL_FUNCTIONS.include?(k) && !BUILTINS.include?(k) && !k.to_s.start_with?('prm_')
        if FunctionType === v
          out.puts v.to_ctype(k) + ';'
        else
          out.puts 'inline ' + v.to_ctype(k) + ';'
        end
      else
        out.puts "// #{k} :: #{v}"
      end
    end
  end

  def dump(out)
    @table.each do |k, v|
      out.puts "#{k} :: #{v}"
    end
  end

  def [](name)
    @table[name]
  end

  def get(t, u)
  end

  def register(name, type, info = nil)
    return if SPECIAL_FUNCTIONS.include?(name)

    # hook
    hooked_names = %i[xfix_at_m184]
    if hooked_names.include?(name) &&
        type && type != BasicType::UNKNOWN &&
        @table[name] != type
      STDERR.puts "TypeTable#register: #{name}(#{@table[name]} => #{type})"
      STDERR.puts '      where: ' + caller(1, 1).to_s.match(/.*:in `(.*)'"\]/)[1]
      if info
        STDERR.puts '    details: ' + info.to_s
      end
    end

    @table[name] = merge(@table[name], type)
  end

  def merge(t, u)
    return u unless Type === t
    return t unless Type === u
    return u if t == BasicType::UNKNOWN
    return t if u == BasicType::UNKNOWN
    promote(t, u) || make_array(t, u) || make_func(t, u) || make_union(t, u)
  end

  private

  SPECIAL_FUNCTIONS = %i[
    DIM1 DIM2 DIM3 DIM4
    SDIM1 SDIM2 SDIM3 SDIM4
    dup
    main

    eqhelm eqweapon1 eqshield eqrange eqammo eqweapon2 eqarmor eqglove eqboots
    eqcloack eqgirdle eqring1 eqring2 eqamulet1 eqamulet2

    roomexist roomx roomy roomwidth roomheight roomexit roomexitmax
    roomentrancex roomentrancey

    sdatadup_at_m161

    key_identify key_pageup key_pagedown key_cancel key_help key_msglog
    key_enter key_save key_north key_northeast key_east key_southeast key_south
    key_southwest key_west key_northwest key_skill key_close key_cast key_drink
    key_read key_zap key_fire key_search key_target key_dig key_wait
    key_inventory key_drop key_get key_wipe key_charainfo key_eat key_wear
    key_godown key_goup key_interact key_rest key_use key_bash key_open key_dip
    key_pray key_offer key_journal key_material key_quick key_get2 key_trait
    key_look key_give key_prev key_next key_quickinv key_throw key_esc key_alt
    key_mode key_ammo key_mode2

    rqop cdref_at_tcg r_at_m133

    label_1547 label_1550 label_1553 label_1557 label_2743 label_2737

    cs_list label_1567
  ].to_set
end
