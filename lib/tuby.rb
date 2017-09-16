require 'set'

require 'tuby/instruction_sequence'
require 'tuby/insn'
require 'tuby/lexer'
require 'tuby/node'
require 'tuby/parser'
require 'tuby/tuby'

module Tuby
  def self.compile(content)
    Parser.compile(content)
  end
end
