require 'set'


class Type
  def return_type
    nil
  end

  def parameter_type_at(n)
    nil
  end

  def valid?(as_return_type: false)
    false
  end
end


class BasicType < Type
  attr_reader :name

  def initialize(name)
    @name = name
  end

  def ==(other)
    BasicType === other && name == other.name
  end

  def to_s
    name.to_s
  end

  def to_ctype(var_name = nil, is_parameter = false)
    if name == :string
      ret = is_parameter ? 'const std::string&' : 'std::string'
    else
      ret = to_s
    end
    if var_name
      ret + ' ' + var_name.to_s
    else
      ret
    end
  end

  def valid?(as_return_type: false)
    name != :unknown && (as_return_type || name != :void)
  end

  UNKNOWN = BasicType.new(:unknown)
  INT = BasicType.new(:int)
  STRING = BasicType.new(:string)
  VOID = BasicType.new(:void)
end


class RefType < Type
  attr_reader :base_type

  def initialize(base_type)
    @base_type = base_type
  end

  def ==(other)
    RefType === other && base_type == other.base_type
  end

  def to_s
    "ref<#{base_type}>"
  end

  def to_ctype(var_name = nil, is_parameter = false)
    if is_parameter
      ret = base_type.to_ctype + '&'
    else
      ret = base_type.to_ctype
    end
    if var_name
      ret + ' ' + var_name.to_s
    else
      ret
    end
  end

  def valid?(as_return_type: false)
    @base_type.valid?
  end

  INT = RefType.new(BasicType::INT)
  STRING = RefType.new(BasicType::STRING)
end


class ArrayType < Type
  attr_reader :base_type, :dimension

  def initialize(base_type, dimension)
    @base_type = base_type
    @dimension = dimension
  end

  def ==(other)
    ArrayType === other && base_type == other.base_type && dimension == other.dimension
  end

  def to_s
    "elona_vector#{dimension}<#{base_type}>"
  end

  def to_ctype(var_name = nil, is_parameter = false)
    ret = "elona_vector#{dimension}<#{base_type.to_ctype}>"
    if is_parameter
      ret = 'const ' + ret + '&'
    end
    if var_name
      ret + ' ' + var_name.to_s
    else
      ret
    end
  end

  def return_type
    base_type
  end

  def parameter_type_at(n)
    BasicType::INT
  end

  def valid?(as_return_type: false)
    @base_type.valid?
  end
end


class Union < Type
  attr_reader :types

  def initialize(*types)
    @types = types.to_set
  end

  def include?(type)
    @types.include?(type)
  end

  def ==(other)
    Union === other && types == other.types
  end

  def to_s
    types.to_a.join(' | ')
  end
end



class FunctionType < Type
  attr_reader :return_type, :parameter_types

  def initialize(return_type, parameter_types)
    @return_type = return_type
    @parameter_types = parameter_types
  end

  def ==(other)
    FunctionType === other && return_type == other.return_type && parameter_types == other.parameter_types
  end

  def to_s
    "(#{parameter_types.join(', ')}) -> #{return_type}"
  end

  def to_ctype(var_name)
    ret = "#{return_type.to_ctype} #{var_name}("
    parameter_types.each_with_index do |param, i|
      ret += param.to_ctype(nil, true)
      opt = parameter_types[i..-1].all?{|p| p == BasicType::INT}
      if opt
        ret += ' = 0'
      end
      if i != parameter_types.length - 1
        ret += ', '
      end
    end
    ret + ')'
  end

  def parameter_type_at(n)
    parameter_types[n]
  end

  def valid?(as_return_type: false)
    return_type.valid?(as_return_type: true) && parameter_types.all?(&:valid?)
  end
end



class OperatorFunctionType < FunctionType
  attr_reader :type

  def initialize(type, return_type, parameter_types)
    super(return_type, parameter_types)
    @type = type
  end

  def ==(other)
    OperatorFunctionType === other && return_type == other.return_type && parameter_types == other.parameter_types
  end

  # [return, arg1, arg2, ...]
  def get_concrete_signature(argument_types)
    case type
    when :comparison
      if argument_types[0] == BasicType::INT
        [BasicType::INT, argument_types[0], argument_types[0]]
      elsif argument_types[1] == BasicType::INT
        [BasicType::INT, argument_types[1], argument_types[1]]
      elsif argument_types[0] == BasicType::STRING
        [BasicType::INT, argument_types[0], argument_types[0]]
      elsif argument_types[1] == BasicType::STRING
        [BasicType::INT, argument_types[1], argument_types[1]]
      else
        [BasicType::INT, argument_types[0], argument_types[1]]
      end
    when :add_or_concat
      if argument_types[0] == BasicType::STRING
        [BasicType::STRING, BasicType::STRING, argument_types[1]]
      elsif argument_types[0] == BasicType::INT
        [BasicType::INT, BasicType::INT, argument_types[1]]
      else
        [GENERIC, argument_types[0], argument_types[1]]
      end
    end
  end
end


def promote(t, u)
  if t == u
    t
  elsif GenericType === t
    u
  elsif GenericType === u
    t
  elsif RefType === t && t.base_type == u
    u
  elsif RefType === u && u.base_type == t
    t
  else
    nil
  end
end



# (0) A + A
# (1) A + a
# (2) a + A
# (3) a + a
def make_array(t, u)
  if ArrayType === t
    if ArrayType === u
      # (0)
      if promoted = promote(t.base_type, u.base_type)
        ArrayType.new(promoted, t.dimension)
      else
        nil
      end
    else
      # (1)
      if promoted = promote(t.base_type, u)
        ArrayType.new(promoted, t.dimension)
      else
        nil
      end
    end
  else
    if ArrayType === u
      # (2)
      if promoted = promote(t, u.base_type)
        ArrayType.new(promoted, u.dimension)
      else
        nil
      end
    else
      # (3)
      nil
    end
  end
end


def make_func(t, u)
  if FunctionType === t && FunctionType === u && t.parameter_types == u.parameter_types
    if promoted = promote(t.return_type, u.return_type)
      FunctionType.new(promoted, t.parameter_types)
    else
      nil
    end
  else
    nil
  end
end

# (0) U + U
# (1) U + B
# (2) B + U
# (3) B + B
def make_union(t, u)
  if Union === t
    if Union === u
      # (0)
      Union.new(*(t.types + u.types).uniq)
    else
      # (1)
      if t.include?(u)
        t
      else
        Union.new(*t.types, u)
      end
    end
  else
    if Union === u
      # (2)
      if u.include?(t)
        u
      else
        Union.new(t, *u.types)
      end
    else
      # (3)
      Union.new(t, u)
    end
  end
end


class GenericType < Type
  def initialize
  end

  def ==(other)
    false
  end

  def to_s
    "T"
  end
end

GENERIC = GenericType.new
