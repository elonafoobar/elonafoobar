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

  def skip_line_breaks
    while get == :line_break
      advance
    end
  end

  def advance
    @tokens.shift
  end

  def expect(token_type)
    if token_type != :line_break
      skip_line_breaks
    end

    actual_token = get
    if actual_token == token_type
      advance
      actual_token
    else
      raise "ERROR: expected #{token_type}, but actually got #{actual_token}"
    end
  end

  private

  KEYWORDS = %w[if else repeat onerror onkey button oncmd comevent]

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
    when '|'
      scanner.advance
      return :or, '|'
    when '^'
      scanner.advance
      return :xor, '^'
    when '\\'
      scanner.advance
      return :modulo, '%'
    when '>'
      scanner.advance
      case scanner.get
      when '>'
        scanner.advance
        return :shift_r, '>>'
      when '='
        scanner.advance
        return :greater_than_equal, '>='
      else
        return :greater_than, '>'
      end
    when '='
      scanner.advance
      if scanner.get == '='
        scanner.advance
        return :equal, '=='
      else
        return :assign, '='
      end
    when '<' 
      scanner.advance
      case scanner.get
      when '<'
        scanner.advance
        return :shift_l, '<<'
      when '='
        scanner.advance
        return :less_than_equal, '<='
      else
        return :less_than, '<'
      end
    when '/'
      scanner.advance
      if scanner.get == '='
        scanner.advance
        return :assign_div, '/='
      else
        return :division, '/'
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
        return :minus, '-'
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
        return :plus, '+'
      end
    when '*'
      scanner.advance
      if scanner.get == '='
        scanner.advance
        return :assign_mul, '*='
      else
        return :multiplication, '*'
      end
    when '&'
      scanner.advance
      return :and, '&'
    when '!'
      scanner.advance
      if scanner.get == '='
        scanner.advance
        return :not_equal, '!='
      else
        raise
      end
    when '#'
      scanner.advance
      w = ''
      while /\w/ =~ scanner.get
        w += scanner.get
        scanner.advance
      end
      case w
      when 'uselib'
        return :macro_uselib, '#uselib'
      when 'func'
        return :macro_func, '#func'
      when 'cfunc'
        return :macro_cfunc, '#cfunc'
      when 'deffunc'
        return :macro_deffunc, '#deffunc'
      when 'defcfunc'
        return :macro_defcfunc, '#defcfunc'
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
      return :line_break, ':'
    when "\n"
      scanner.advance
      return :line_break, 'line break'
    when /[ \t]/
      while /[ \t]/ =~ scanner.get
        scanner.advance
      end
      return nil, nil
    when /\w/, '@'
      w = ''
      while /\w/ =~ scanner.get || scanner.get == '@'
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
