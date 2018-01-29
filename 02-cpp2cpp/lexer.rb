require './token.rb'


class StringScanner
  def initialize(src)
    @src = src
    @line = src.gets
    @i = 0
  end

  def get
    @line[@i]
  end

  def advance
    @i += 1
    if @i >= @line.length
      @line = gets
      @i = 0
    end
  end

  def eos?
    !@line
  end

  def rest
    @line
  end
end



class Lexer
  def initialize(input)
    @tokens = []
    scan(StringScanner.new(input))
  end

  def get
    @tokens[0]
  end

  def advance
    @tokens.shift
  end

  def expect(token_type)
    actual_token = get
    if actual_token == token_type
      advance
      actual_token
    else
      STDERR.puts @tokens[0..20]
      raise "ERROR: expected #{token_type}, but actually got #{actual_token}"
    end
  end

  private

  KEYWORDS = %w[
    if else repeat switch case return break continue goto function let
    onerror onkey button oncmd comevent
  ]

  def scan(scanner)
    loop do
      if scanner.eos?
        @tokens << Token.new(:eof, "- End Of File -")
        break
      end

      t, s = scan_one_token(scanner)
      if t
        @tokens << Token.new(t, s)
      end
    end
  end

  def scan_one_token(scanner)
    case scanner.get
    when ','
      scanner.advance
      return :comma, ','
    when '('
      scanner.advance
      return :parenthesis_left, '('
    when ')'
      scanner.advance
      return :parenthesis_right, ')'
    when '{'
      scanner.advance
      return :brace_left, '{'
    when '}'
      scanner.advance
      return :brace_right, '}'
    when '='
      scanner.advance
      return :assign, '='
    when '/'
      scanner.advance
      if scanner.get == '='
        scanner.advance
        return :assign_div, '/='
      else
        raise
      end
    when '-'
      scanner.advance
      case scanner.get
      when '-'
        scanner.advance
        return :decrement, '-'
      when '='
        scanner.advance
        return :assign_sub, '-='
      else
        raise
      end
    when '+'
      scanner.advance
      case scanner.get
      when '+'
        scanner.advance
        return :increment, '++'
      when '='
        scanner.advance
        return :assign_add, '+='
      else
        raise
      end
    when '*'
      scanner.advance
      if scanner.get == '='
        scanner.advance
        return :assign_mul, '*='
      else
        raise
      end
    when '!'
      scanner.advance
      if scanner.get == '='
        scanner.advance
        return :not_equal, '!='
      else
        raise
      end
    when /\d/
      d = ''
      while /\d/ =~ scanner.get
        d += scanner.get
        scanner.advance
      end
      if scanner.get == '.'
        scanner.advance
        d += '.'
        while /\d/ =~ scanner.get
          d += scanner.get
          scanner.advance
        end
        return :floating_literal, d
      else
        return :integer_literal, d
      end
    when ':'
      scanner.advance
      return :colon, ':'
    when ';'
      scanner.advance
      return :semicolon, ';'
    when /[ \n\t]/
      while !scanner.eos? && /[ \n\t]/ =~ scanner.get
        scanner.advance
      end
      return nil, nil
    when /\w/
      w = ''
      while /\w/ =~ scanner.get
        w += scanner.get
        scanner.advance
      end
      if KEYWORDS.include?(w)
        return ('keyword_' + w).to_sym, w
      else
        return :identifier, w
      end
    when '"'
      scanner.advance
      s = ''
      while scanner.get != '"'
        if scanner.get == '\\'
          s += '\\'
          scanner.advance
        end
        s += scanner.get
        scanner.advance
      end
      scanner.advance
      return :string_literal, s
    end

    raise scanner.rest
  end
end
