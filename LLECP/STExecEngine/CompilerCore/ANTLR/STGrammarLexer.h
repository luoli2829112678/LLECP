
// Generated from STGrammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  STGrammarLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, WS = 6, NEWLINE = 7, 
    COMMENT = 8, LINE_COMMENT = 9, COMMA = 10, SEMI = 11, BOOL = 12, INT = 13, 
    LREAL = 14, INT_TYPE = 15, LREAL_TYPE = 16, BOOL_TYPE = 17, IF = 18, 
    THEN = 19, ELSE = 20, ELSE_IF = 21, END_IF = 22, TO = 23, DO = 24, END_FOR = 25, 
    ASSIGN = 26, BY = 27, LOOP = 28, END_LOOP = 29, TILL = 30, BLOCK = 31, 
    END_BLOCK = 32, MULT = 33, DIV = 34, PLUS = 35, MINUS = 36, AND = 37, 
    OR = 38, NOT = 39, EQ = 40, NEQ = 41, GT = 42, LT = 43, AXIS_ENABLE = 44, 
    AXIS_DISABLE = 45, AXIS_STOP = 46, AXIS_MOVE_ABS = 47, AXIS_MOVE_REL = 48, 
    AXIS_MOVE_VEL = 49, AXIS_POS = 50, AXIS_VEL = 51, AXIS_ACC = 52, AXIS_JERK = 53, 
    AXIS_DEC = 54, AXIS_RESET = 55, AXIS_STAUTS_STATE = 56, AXIS_STAUTS_ENABLE = 57, 
    AXIS_STAUTS_MOVE = 58, DRIVE_SET_DO = 59, DRIVE_SET_AO = 60, DRIVE_STAUTS_DI = 61, 
    DRIVE_STAUTS_AI = 62, BUFFER_ENABLE = 63, BUFFER_DISABLE = 64, WAIT = 65, 
    NULL_CMD = 66, START_ANALOGFOCUSING = 67, STOP_ANALOGFOCUSING = 68, 
    START_PEG = 69, STOP_PEG = 70, ID = 71
  };

  explicit STGrammarLexer(antlr4::CharStream *input);

  ~STGrammarLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

