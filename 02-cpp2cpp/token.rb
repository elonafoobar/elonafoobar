class Token
  attr_reader :type, :str

  def initialize(type, str)
    @type = type
    @str = str
  end

  def ==(type)
    self.type == type
  end

  def to_s
    "Token(#{type}, #{str})"
  end

  alias inspect to_s
end
