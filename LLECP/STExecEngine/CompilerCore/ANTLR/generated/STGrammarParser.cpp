
// Generated from /home/LLECP/LLECP/STExecEngine/CompilerCore/ANTLR/STGrammar.g4 by ANTLR 4.13.2


#include "STGrammarListener.h"
#include "STGrammarVisitor.h"

#include "STGrammarParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct STGrammarParserStaticData final {
  STGrammarParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  STGrammarParserStaticData(const STGrammarParserStaticData&) = delete;
  STGrammarParserStaticData(STGrammarParserStaticData&&) = delete;
  STGrammarParserStaticData& operator=(const STGrammarParserStaticData&) = delete;
  STGrammarParserStaticData& operator=(STGrammarParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag stgrammarParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<STGrammarParserStaticData> stgrammarParserStaticData = nullptr;

void stgrammarParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (stgrammarParserStaticData != nullptr) {
    return;
  }
#else
  assert(stgrammarParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<STGrammarParserStaticData>(
    std::vector<std::string>{
      "one_para_set_func_name", "two_para_set_func_name", "read_func_name", 
      "program", "statement", "assignment", "expression", "if_statement", 
      "condition", "global_var_decl", "one_para_function", "two_para_function", 
      "read_set_function", "argumentList", "loop_statement", "till_statement", 
      "block_statement"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'#'", "'['", "']'", "", "", "", "", "','", "';'", 
      "", "", "", "'INT'", "'LREAL'", "'BOOL'", "'IF'", "'THEN'", "'ELSE'", 
      "'ELSIF'", "'END_IF'", "'TO'", "'DO'", "'END_FOR'", "':='", "'BY'", 
      "'LOOP'", "'END_LOOP'", "'TILL'", "'BLOCK'", "'END_BLOCK'", "'*'", 
      "'/'", "'+'", "'-'", "'AND'", "'OR'", "'NOT'", "'='", "'@'", "'>'", 
      "'<'", "'AXIS_ENABLE'", "'AXIS_DISABLE'", "'AXIS_STOP'", "'AXIS_MOVE_ABS'", 
      "'AXIS_MOVE_REL'", "'AXIS_MOVE_VEL'", "'AXIS_POS'", "'AXIS_VEL'", 
      "'AXIS_ACC'", "'AXIS_JERK'", "'AXIS_DEC'", "'AXIS_RESET'", "'AXIS_STAUTS_STATE'", 
      "'AXIS_STAUTS_ENABLE'", "'AXIS_STAUTS_MOVE'", "'DRIVE_SET_DO'", "'DRIVE_SET_AO'", 
      "'DRIVE_STAUTS_DI'", "'DRIVE_STAUTS_AI'", "'BUFFER_ENABLE'", "'BUFFER_DISABLE'", 
      "'WAIT'", "'NULL_CMD'", "'START_ANALOGFOCUSING'", "'STOP_ANALOGFOCUSING'", 
      "'START_PEG'", "'STOP_PEG'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "WS", "NEWLINE", "COMMENT", "LINE_COMMENT", 
      "COMMA", "SEMI", "BOOL", "INT", "LREAL", "INT_TYPE", "LREAL_TYPE", 
      "BOOL_TYPE", "IF", "THEN", "ELSE", "ELSE_IF", "END_IF", "TO", "DO", 
      "END_FOR", "ASSIGN", "BY", "LOOP", "END_LOOP", "TILL", "BLOCK", "END_BLOCK", 
      "MULT", "DIV", "PLUS", "MINUS", "AND", "OR", "NOT", "EQ", "NEQ", "GT", 
      "LT", "AXIS_ENABLE", "AXIS_DISABLE", "AXIS_STOP", "AXIS_MOVE_ABS", 
      "AXIS_MOVE_REL", "AXIS_MOVE_VEL", "AXIS_POS", "AXIS_VEL", "AXIS_ACC", 
      "AXIS_JERK", "AXIS_DEC", "AXIS_RESET", "AXIS_STAUTS_STATE", "AXIS_STAUTS_ENABLE", 
      "AXIS_STAUTS_MOVE", "DRIVE_SET_DO", "DRIVE_SET_AO", "DRIVE_STAUTS_DI", 
      "DRIVE_STAUTS_AI", "BUFFER_ENABLE", "BUFFER_DISABLE", "WAIT", "NULL_CMD", 
      "START_ANALOGFOCUSING", "STOP_ANALOGFOCUSING", "START_PEG", "STOP_PEG", 
      "ID"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,71,226,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,1,0,1,1,1,1,1,2,1,2,1,3,4,3,42,8,3,11,3,12,
  	3,43,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,57,8,4,1,4,1,4,4,
  	4,61,8,4,11,4,12,4,62,1,4,3,4,66,8,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,86,8,6,1,6,1,6,1,6,1,6,1,
  	6,1,6,5,6,94,8,6,10,6,12,6,97,9,6,1,7,1,7,1,7,1,7,4,7,103,8,7,11,7,12,
  	7,104,1,7,4,7,108,8,7,11,7,12,7,109,1,7,1,7,1,7,1,7,4,7,116,8,7,11,7,
  	12,7,117,1,7,4,7,121,8,7,11,7,12,7,122,5,7,125,8,7,10,7,12,7,128,9,7,
  	1,7,1,7,4,7,132,8,7,11,7,12,7,133,1,7,3,7,137,8,7,1,7,1,7,1,8,1,8,1,8,
  	1,8,1,8,3,8,146,8,8,1,9,1,9,1,9,1,9,3,9,152,8,9,1,9,1,9,1,9,1,9,3,9,158,
  	8,9,1,9,1,9,1,9,1,9,3,9,164,8,9,3,9,166,8,9,1,10,1,10,1,10,1,10,1,10,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,
  	1,13,5,13,188,8,13,10,13,12,13,191,9,13,1,14,1,14,1,14,1,14,4,14,197,
  	8,14,11,14,12,14,198,1,14,4,14,202,8,14,11,14,12,14,203,1,14,1,14,1,15,
  	1,15,1,15,1,15,1,15,1,16,1,16,4,16,215,8,16,11,16,12,16,216,1,16,4,16,
  	220,8,16,11,16,12,16,221,1,16,1,16,1,16,0,1,12,17,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,32,0,6,4,0,44,49,55,55,63,65,67,70,2,0,50,54,
  	59,60,2,0,56,58,61,62,1,0,33,36,1,0,37,38,2,0,37,38,40,43,247,0,34,1,
  	0,0,0,2,36,1,0,0,0,4,38,1,0,0,0,6,41,1,0,0,0,8,56,1,0,0,0,10,67,1,0,0,
  	0,12,85,1,0,0,0,14,98,1,0,0,0,16,145,1,0,0,0,18,165,1,0,0,0,20,167,1,
  	0,0,0,22,172,1,0,0,0,24,179,1,0,0,0,26,184,1,0,0,0,28,192,1,0,0,0,30,
  	207,1,0,0,0,32,212,1,0,0,0,34,35,7,0,0,0,35,1,1,0,0,0,36,37,7,1,0,0,37,
  	3,1,0,0,0,38,39,7,2,0,0,39,5,1,0,0,0,40,42,3,8,4,0,41,40,1,0,0,0,42,43,
  	1,0,0,0,43,41,1,0,0,0,43,44,1,0,0,0,44,45,1,0,0,0,45,46,5,0,0,1,46,7,
  	1,0,0,0,47,57,3,10,5,0,48,57,3,14,7,0,49,57,3,18,9,0,50,57,3,20,10,0,
  	51,57,3,22,11,0,52,57,3,24,12,0,53,57,3,28,14,0,54,57,3,32,16,0,55,57,
  	3,30,15,0,56,47,1,0,0,0,56,48,1,0,0,0,56,49,1,0,0,0,56,50,1,0,0,0,56,
  	51,1,0,0,0,56,52,1,0,0,0,56,53,1,0,0,0,56,54,1,0,0,0,56,55,1,0,0,0,57,
  	58,1,0,0,0,58,65,5,11,0,0,59,61,5,7,0,0,60,59,1,0,0,0,61,62,1,0,0,0,62,
  	60,1,0,0,0,62,63,1,0,0,0,63,66,1,0,0,0,64,66,5,0,0,1,65,60,1,0,0,0,65,
  	64,1,0,0,0,66,9,1,0,0,0,67,68,5,71,0,0,68,69,5,26,0,0,69,70,3,12,6,0,
  	70,11,1,0,0,0,71,72,6,6,-1,0,72,73,5,39,0,0,73,86,3,12,6,9,74,86,5,71,
  	0,0,75,86,5,13,0,0,76,86,5,12,0,0,77,86,5,14,0,0,78,79,5,1,0,0,79,80,
  	3,12,6,0,80,81,5,2,0,0,81,86,1,0,0,0,82,86,3,20,10,0,83,86,3,22,11,0,
  	84,86,3,24,12,0,85,71,1,0,0,0,85,74,1,0,0,0,85,75,1,0,0,0,85,76,1,0,0,
  	0,85,77,1,0,0,0,85,78,1,0,0,0,85,82,1,0,0,0,85,83,1,0,0,0,85,84,1,0,0,
  	0,86,95,1,0,0,0,87,88,10,11,0,0,88,89,7,3,0,0,89,94,3,12,6,12,90,91,10,
  	10,0,0,91,92,7,4,0,0,92,94,3,12,6,11,93,87,1,0,0,0,93,90,1,0,0,0,94,97,
  	1,0,0,0,95,93,1,0,0,0,95,96,1,0,0,0,96,13,1,0,0,0,97,95,1,0,0,0,98,99,
  	5,18,0,0,99,100,3,16,8,0,100,102,5,19,0,0,101,103,5,7,0,0,102,101,1,0,
  	0,0,103,104,1,0,0,0,104,102,1,0,0,0,104,105,1,0,0,0,105,107,1,0,0,0,106,
  	108,3,8,4,0,107,106,1,0,0,0,108,109,1,0,0,0,109,107,1,0,0,0,109,110,1,
  	0,0,0,110,126,1,0,0,0,111,112,5,21,0,0,112,113,3,16,8,0,113,115,5,19,
  	0,0,114,116,5,7,0,0,115,114,1,0,0,0,116,117,1,0,0,0,117,115,1,0,0,0,117,
  	118,1,0,0,0,118,120,1,0,0,0,119,121,3,8,4,0,120,119,1,0,0,0,121,122,1,
  	0,0,0,122,120,1,0,0,0,122,123,1,0,0,0,123,125,1,0,0,0,124,111,1,0,0,0,
  	125,128,1,0,0,0,126,124,1,0,0,0,126,127,1,0,0,0,127,136,1,0,0,0,128,126,
  	1,0,0,0,129,131,5,20,0,0,130,132,5,7,0,0,131,130,1,0,0,0,132,133,1,0,
  	0,0,133,131,1,0,0,0,133,134,1,0,0,0,134,135,1,0,0,0,135,137,3,8,4,0,136,
  	129,1,0,0,0,136,137,1,0,0,0,137,138,1,0,0,0,138,139,5,22,0,0,139,15,1,
  	0,0,0,140,141,3,12,6,0,141,142,7,5,0,0,142,143,3,12,6,0,143,146,1,0,0,
  	0,144,146,5,12,0,0,145,140,1,0,0,0,145,144,1,0,0,0,146,17,1,0,0,0,147,
  	148,5,15,0,0,148,151,5,71,0,0,149,150,5,26,0,0,150,152,5,13,0,0,151,149,
  	1,0,0,0,151,152,1,0,0,0,152,166,1,0,0,0,153,154,5,17,0,0,154,157,5,71,
  	0,0,155,156,5,26,0,0,156,158,5,12,0,0,157,155,1,0,0,0,157,158,1,0,0,0,
  	158,166,1,0,0,0,159,160,5,16,0,0,160,163,5,71,0,0,161,162,5,26,0,0,162,
  	164,5,14,0,0,163,161,1,0,0,0,163,164,1,0,0,0,164,166,1,0,0,0,165,147,
  	1,0,0,0,165,153,1,0,0,0,165,159,1,0,0,0,166,19,1,0,0,0,167,168,3,0,0,
  	0,168,169,5,1,0,0,169,170,3,12,6,0,170,171,5,2,0,0,171,21,1,0,0,0,172,
  	173,3,2,1,0,173,174,5,1,0,0,174,175,3,12,6,0,175,176,5,3,0,0,176,177,
  	3,12,6,0,177,178,5,2,0,0,178,23,1,0,0,0,179,180,3,4,2,0,180,181,5,4,0,
  	0,181,182,3,12,6,0,182,183,5,5,0,0,183,25,1,0,0,0,184,189,3,12,6,0,185,
  	186,5,3,0,0,186,188,3,12,6,0,187,185,1,0,0,0,188,191,1,0,0,0,189,187,
  	1,0,0,0,189,190,1,0,0,0,190,27,1,0,0,0,191,189,1,0,0,0,192,193,5,28,0,
  	0,193,194,5,13,0,0,194,196,5,19,0,0,195,197,5,7,0,0,196,195,1,0,0,0,197,
  	198,1,0,0,0,198,196,1,0,0,0,198,199,1,0,0,0,199,201,1,0,0,0,200,202,3,
  	8,4,0,201,200,1,0,0,0,202,203,1,0,0,0,203,201,1,0,0,0,203,204,1,0,0,0,
  	204,205,1,0,0,0,205,206,5,29,0,0,206,29,1,0,0,0,207,208,5,30,0,0,208,
  	209,5,1,0,0,209,210,3,16,8,0,210,211,5,2,0,0,211,31,1,0,0,0,212,214,5,
  	31,0,0,213,215,5,7,0,0,214,213,1,0,0,0,215,216,1,0,0,0,216,214,1,0,0,
  	0,216,217,1,0,0,0,217,219,1,0,0,0,218,220,3,8,4,0,219,218,1,0,0,0,220,
  	221,1,0,0,0,221,219,1,0,0,0,221,222,1,0,0,0,222,223,1,0,0,0,223,224,5,
  	32,0,0,224,33,1,0,0,0,24,43,56,62,65,85,93,95,104,109,117,122,126,133,
  	136,145,151,157,163,165,189,198,203,216,221
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  stgrammarParserStaticData = std::move(staticData);
}

}

STGrammarParser::STGrammarParser(TokenStream *input) : STGrammarParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

STGrammarParser::STGrammarParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  STGrammarParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *stgrammarParserStaticData->atn, stgrammarParserStaticData->decisionToDFA, stgrammarParserStaticData->sharedContextCache, options);
}

STGrammarParser::~STGrammarParser() {
  delete _interpreter;
}

const atn::ATN& STGrammarParser::getATN() const {
  return *stgrammarParserStaticData->atn;
}

std::string STGrammarParser::getGrammarFileName() const {
  return "STGrammar.g4";
}

const std::vector<std::string>& STGrammarParser::getRuleNames() const {
  return stgrammarParserStaticData->ruleNames;
}

const dfa::Vocabulary& STGrammarParser::getVocabulary() const {
  return stgrammarParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView STGrammarParser::getSerializedATN() const {
  return stgrammarParserStaticData->serializedATN;
}


//----------------- One_para_set_func_nameContext ------------------------------------------------------------------

STGrammarParser::One_para_set_func_nameContext::One_para_set_func_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::AXIS_ENABLE() {
  return getToken(STGrammarParser::AXIS_ENABLE, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::AXIS_DISABLE() {
  return getToken(STGrammarParser::AXIS_DISABLE, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::AXIS_STOP() {
  return getToken(STGrammarParser::AXIS_STOP, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::AXIS_MOVE_ABS() {
  return getToken(STGrammarParser::AXIS_MOVE_ABS, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::AXIS_MOVE_REL() {
  return getToken(STGrammarParser::AXIS_MOVE_REL, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::AXIS_MOVE_VEL() {
  return getToken(STGrammarParser::AXIS_MOVE_VEL, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::AXIS_RESET() {
  return getToken(STGrammarParser::AXIS_RESET, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::WAIT() {
  return getToken(STGrammarParser::WAIT, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::BUFFER_ENABLE() {
  return getToken(STGrammarParser::BUFFER_ENABLE, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::BUFFER_DISABLE() {
  return getToken(STGrammarParser::BUFFER_DISABLE, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::START_ANALOGFOCUSING() {
  return getToken(STGrammarParser::START_ANALOGFOCUSING, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::STOP_ANALOGFOCUSING() {
  return getToken(STGrammarParser::STOP_ANALOGFOCUSING, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::START_PEG() {
  return getToken(STGrammarParser::START_PEG, 0);
}

tree::TerminalNode* STGrammarParser::One_para_set_func_nameContext::STOP_PEG() {
  return getToken(STGrammarParser::STOP_PEG, 0);
}


size_t STGrammarParser::One_para_set_func_nameContext::getRuleIndex() const {
  return STGrammarParser::RuleOne_para_set_func_name;
}

void STGrammarParser::One_para_set_func_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOne_para_set_func_name(this);
}

void STGrammarParser::One_para_set_func_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOne_para_set_func_name(this);
}


std::any STGrammarParser::One_para_set_func_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitOne_para_set_func_name(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::One_para_set_func_nameContext* STGrammarParser::one_para_set_func_name() {
  One_para_set_func_nameContext *_localctx = _tracker.createInstance<One_para_set_func_nameContext>(_ctx, getState());
  enterRule(_localctx, 0, STGrammarParser::RuleOne_para_set_func_name);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    _la = _input->LA(1);
    if (!(((((_la - 44) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 44)) & 129501247) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Two_para_set_func_nameContext ------------------------------------------------------------------

STGrammarParser::Two_para_set_func_nameContext::Two_para_set_func_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::Two_para_set_func_nameContext::AXIS_POS() {
  return getToken(STGrammarParser::AXIS_POS, 0);
}

tree::TerminalNode* STGrammarParser::Two_para_set_func_nameContext::AXIS_VEL() {
  return getToken(STGrammarParser::AXIS_VEL, 0);
}

tree::TerminalNode* STGrammarParser::Two_para_set_func_nameContext::AXIS_ACC() {
  return getToken(STGrammarParser::AXIS_ACC, 0);
}

tree::TerminalNode* STGrammarParser::Two_para_set_func_nameContext::AXIS_JERK() {
  return getToken(STGrammarParser::AXIS_JERK, 0);
}

tree::TerminalNode* STGrammarParser::Two_para_set_func_nameContext::AXIS_DEC() {
  return getToken(STGrammarParser::AXIS_DEC, 0);
}

tree::TerminalNode* STGrammarParser::Two_para_set_func_nameContext::DRIVE_SET_DO() {
  return getToken(STGrammarParser::DRIVE_SET_DO, 0);
}

tree::TerminalNode* STGrammarParser::Two_para_set_func_nameContext::DRIVE_SET_AO() {
  return getToken(STGrammarParser::DRIVE_SET_AO, 0);
}


size_t STGrammarParser::Two_para_set_func_nameContext::getRuleIndex() const {
  return STGrammarParser::RuleTwo_para_set_func_name;
}

void STGrammarParser::Two_para_set_func_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTwo_para_set_func_name(this);
}

void STGrammarParser::Two_para_set_func_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTwo_para_set_func_name(this);
}


std::any STGrammarParser::Two_para_set_func_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitTwo_para_set_func_name(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::Two_para_set_func_nameContext* STGrammarParser::two_para_set_func_name() {
  Two_para_set_func_nameContext *_localctx = _tracker.createInstance<Two_para_set_func_nameContext>(_ctx, getState());
  enterRule(_localctx, 2, STGrammarParser::RuleTwo_para_set_func_name);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1764285154022391808) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Read_func_nameContext ------------------------------------------------------------------

STGrammarParser::Read_func_nameContext::Read_func_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::Read_func_nameContext::AXIS_STAUTS_STATE() {
  return getToken(STGrammarParser::AXIS_STAUTS_STATE, 0);
}

tree::TerminalNode* STGrammarParser::Read_func_nameContext::AXIS_STAUTS_ENABLE() {
  return getToken(STGrammarParser::AXIS_STAUTS_ENABLE, 0);
}

tree::TerminalNode* STGrammarParser::Read_func_nameContext::AXIS_STAUTS_MOVE() {
  return getToken(STGrammarParser::AXIS_STAUTS_MOVE, 0);
}

tree::TerminalNode* STGrammarParser::Read_func_nameContext::DRIVE_STAUTS_DI() {
  return getToken(STGrammarParser::DRIVE_STAUTS_DI, 0);
}

tree::TerminalNode* STGrammarParser::Read_func_nameContext::DRIVE_STAUTS_AI() {
  return getToken(STGrammarParser::DRIVE_STAUTS_AI, 0);
}


size_t STGrammarParser::Read_func_nameContext::getRuleIndex() const {
  return STGrammarParser::RuleRead_func_name;
}

void STGrammarParser::Read_func_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRead_func_name(this);
}

void STGrammarParser::Read_func_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRead_func_name(this);
}


std::any STGrammarParser::Read_func_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitRead_func_name(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::Read_func_nameContext* STGrammarParser::read_func_name() {
  Read_func_nameContext *_localctx = _tracker.createInstance<Read_func_nameContext>(_ctx, getState());
  enterRule(_localctx, 4, STGrammarParser::RuleRead_func_name);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7421932185906577408) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgramContext ------------------------------------------------------------------

STGrammarParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::ProgramContext::EOF() {
  return getToken(STGrammarParser::EOF, 0);
}

std::vector<STGrammarParser::StatementContext *> STGrammarParser::ProgramContext::statement() {
  return getRuleContexts<STGrammarParser::StatementContext>();
}

STGrammarParser::StatementContext* STGrammarParser::ProgramContext::statement(size_t i) {
  return getRuleContext<STGrammarParser::StatementContext>(i);
}


size_t STGrammarParser::ProgramContext::getRuleIndex() const {
  return STGrammarParser::RuleProgram;
}

void STGrammarParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void STGrammarParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any STGrammarParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::ProgramContext* STGrammarParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 6, STGrammarParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(41); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(40);
      statement();
      setState(43); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 15) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 15)) & 141863387725406223) != 0));
    setState(45);
    match(STGrammarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

STGrammarParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::StatementContext::SEMI() {
  return getToken(STGrammarParser::SEMI, 0);
}

STGrammarParser::AssignmentContext* STGrammarParser::StatementContext::assignment() {
  return getRuleContext<STGrammarParser::AssignmentContext>(0);
}

STGrammarParser::If_statementContext* STGrammarParser::StatementContext::if_statement() {
  return getRuleContext<STGrammarParser::If_statementContext>(0);
}

STGrammarParser::Global_var_declContext* STGrammarParser::StatementContext::global_var_decl() {
  return getRuleContext<STGrammarParser::Global_var_declContext>(0);
}

STGrammarParser::One_para_functionContext* STGrammarParser::StatementContext::one_para_function() {
  return getRuleContext<STGrammarParser::One_para_functionContext>(0);
}

STGrammarParser::Two_para_functionContext* STGrammarParser::StatementContext::two_para_function() {
  return getRuleContext<STGrammarParser::Two_para_functionContext>(0);
}

STGrammarParser::Read_set_functionContext* STGrammarParser::StatementContext::read_set_function() {
  return getRuleContext<STGrammarParser::Read_set_functionContext>(0);
}

STGrammarParser::Loop_statementContext* STGrammarParser::StatementContext::loop_statement() {
  return getRuleContext<STGrammarParser::Loop_statementContext>(0);
}

STGrammarParser::Block_statementContext* STGrammarParser::StatementContext::block_statement() {
  return getRuleContext<STGrammarParser::Block_statementContext>(0);
}

STGrammarParser::Till_statementContext* STGrammarParser::StatementContext::till_statement() {
  return getRuleContext<STGrammarParser::Till_statementContext>(0);
}

tree::TerminalNode* STGrammarParser::StatementContext::EOF() {
  return getToken(STGrammarParser::EOF, 0);
}

std::vector<tree::TerminalNode *> STGrammarParser::StatementContext::NEWLINE() {
  return getTokens(STGrammarParser::NEWLINE);
}

tree::TerminalNode* STGrammarParser::StatementContext::NEWLINE(size_t i) {
  return getToken(STGrammarParser::NEWLINE, i);
}


size_t STGrammarParser::StatementContext::getRuleIndex() const {
  return STGrammarParser::RuleStatement;
}

void STGrammarParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void STGrammarParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any STGrammarParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::StatementContext* STGrammarParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 8, STGrammarParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case STGrammarParser::ID: {
        setState(47);
        assignment();
        break;
      }

      case STGrammarParser::IF: {
        setState(48);
        if_statement();
        break;
      }

      case STGrammarParser::INT_TYPE:
      case STGrammarParser::LREAL_TYPE:
      case STGrammarParser::BOOL_TYPE: {
        setState(49);
        global_var_decl();
        break;
      }

      case STGrammarParser::AXIS_ENABLE:
      case STGrammarParser::AXIS_DISABLE:
      case STGrammarParser::AXIS_STOP:
      case STGrammarParser::AXIS_MOVE_ABS:
      case STGrammarParser::AXIS_MOVE_REL:
      case STGrammarParser::AXIS_MOVE_VEL:
      case STGrammarParser::AXIS_RESET:
      case STGrammarParser::BUFFER_ENABLE:
      case STGrammarParser::BUFFER_DISABLE:
      case STGrammarParser::WAIT:
      case STGrammarParser::START_ANALOGFOCUSING:
      case STGrammarParser::STOP_ANALOGFOCUSING:
      case STGrammarParser::START_PEG:
      case STGrammarParser::STOP_PEG: {
        setState(50);
        one_para_function();
        break;
      }

      case STGrammarParser::AXIS_POS:
      case STGrammarParser::AXIS_VEL:
      case STGrammarParser::AXIS_ACC:
      case STGrammarParser::AXIS_JERK:
      case STGrammarParser::AXIS_DEC:
      case STGrammarParser::DRIVE_SET_DO:
      case STGrammarParser::DRIVE_SET_AO: {
        setState(51);
        two_para_function();
        break;
      }

      case STGrammarParser::AXIS_STAUTS_STATE:
      case STGrammarParser::AXIS_STAUTS_ENABLE:
      case STGrammarParser::AXIS_STAUTS_MOVE:
      case STGrammarParser::DRIVE_STAUTS_DI:
      case STGrammarParser::DRIVE_STAUTS_AI: {
        setState(52);
        read_set_function();
        break;
      }

      case STGrammarParser::LOOP: {
        setState(53);
        loop_statement();
        break;
      }

      case STGrammarParser::BLOCK: {
        setState(54);
        block_statement();
        break;
      }

      case STGrammarParser::TILL: {
        setState(55);
        till_statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(58);
    match(STGrammarParser::SEMI);
    setState(65);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case STGrammarParser::NEWLINE: {
        setState(60); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(59);
          match(STGrammarParser::NEWLINE);
          setState(62); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == STGrammarParser::NEWLINE);
        break;
      }

      case STGrammarParser::EOF: {
        setState(64);
        match(STGrammarParser::EOF);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

STGrammarParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::AssignmentContext::ID() {
  return getToken(STGrammarParser::ID, 0);
}

tree::TerminalNode* STGrammarParser::AssignmentContext::ASSIGN() {
  return getToken(STGrammarParser::ASSIGN, 0);
}

STGrammarParser::ExpressionContext* STGrammarParser::AssignmentContext::expression() {
  return getRuleContext<STGrammarParser::ExpressionContext>(0);
}


size_t STGrammarParser::AssignmentContext::getRuleIndex() const {
  return STGrammarParser::RuleAssignment;
}

void STGrammarParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void STGrammarParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


std::any STGrammarParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::AssignmentContext* STGrammarParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 10, STGrammarParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(67);
    match(STGrammarParser::ID);
    setState(68);
    match(STGrammarParser::ASSIGN);
    setState(69);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

STGrammarParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t STGrammarParser::ExpressionContext::getRuleIndex() const {
  return STGrammarParser::RuleExpression;
}

void STGrammarParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Set1PFuncExprContext ------------------------------------------------------------------

STGrammarParser::One_para_functionContext* STGrammarParser::Set1PFuncExprContext::one_para_function() {
  return getRuleContext<STGrammarParser::One_para_functionContext>(0);
}

STGrammarParser::Set1PFuncExprContext::Set1PFuncExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::Set1PFuncExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSet1PFuncExpr(this);
}
void STGrammarParser::Set1PFuncExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSet1PFuncExpr(this);
}

std::any STGrammarParser::Set1PFuncExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitSet1PFuncExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoolConstContext ------------------------------------------------------------------

tree::TerminalNode* STGrammarParser::BoolConstContext::BOOL() {
  return getToken(STGrammarParser::BOOL, 0);
}

STGrammarParser::BoolConstContext::BoolConstContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::BoolConstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolConst(this);
}
void STGrammarParser::BoolConstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolConst(this);
}

std::any STGrammarParser::BoolConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitBoolConst(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarContext ------------------------------------------------------------------

tree::TerminalNode* STGrammarParser::VarContext::ID() {
  return getToken(STGrammarParser::ID, 0);
}

STGrammarParser::VarContext::VarContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::VarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar(this);
}
void STGrammarParser::VarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar(this);
}

std::any STGrammarParser::VarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitVar(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstContext ------------------------------------------------------------------

tree::TerminalNode* STGrammarParser::ConstContext::INT() {
  return getToken(STGrammarParser::INT, 0);
}

STGrammarParser::ConstContext::ConstContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::ConstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConst(this);
}
void STGrammarParser::ConstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConst(this);
}

std::any STGrammarParser::ConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitConst(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Set2PFuncExprContext ------------------------------------------------------------------

STGrammarParser::Two_para_functionContext* STGrammarParser::Set2PFuncExprContext::two_para_function() {
  return getRuleContext<STGrammarParser::Two_para_functionContext>(0);
}

STGrammarParser::Set2PFuncExprContext::Set2PFuncExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::Set2PFuncExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSet2PFuncExpr(this);
}
void STGrammarParser::Set2PFuncExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSet2PFuncExpr(this);
}

std::any STGrammarParser::Set2PFuncExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitSet2PFuncExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalOpContext ------------------------------------------------------------------

std::vector<STGrammarParser::ExpressionContext *> STGrammarParser::LogicalOpContext::expression() {
  return getRuleContexts<STGrammarParser::ExpressionContext>();
}

STGrammarParser::ExpressionContext* STGrammarParser::LogicalOpContext::expression(size_t i) {
  return getRuleContext<STGrammarParser::ExpressionContext>(i);
}

tree::TerminalNode* STGrammarParser::LogicalOpContext::AND() {
  return getToken(STGrammarParser::AND, 0);
}

tree::TerminalNode* STGrammarParser::LogicalOpContext::OR() {
  return getToken(STGrammarParser::OR, 0);
}

STGrammarParser::LogicalOpContext::LogicalOpContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::LogicalOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOp(this);
}
void STGrammarParser::LogicalOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOp(this);
}

std::any STGrammarParser::LogicalOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitLogicalOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReadFuncExprContext ------------------------------------------------------------------

STGrammarParser::Read_set_functionContext* STGrammarParser::ReadFuncExprContext::read_set_function() {
  return getRuleContext<STGrammarParser::Read_set_functionContext>(0);
}

STGrammarParser::ReadFuncExprContext::ReadFuncExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::ReadFuncExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReadFuncExpr(this);
}
void STGrammarParser::ReadFuncExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReadFuncExpr(this);
}

std::any STGrammarParser::ReadFuncExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitReadFuncExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotOpContext ------------------------------------------------------------------

tree::TerminalNode* STGrammarParser::NotOpContext::NOT() {
  return getToken(STGrammarParser::NOT, 0);
}

STGrammarParser::ExpressionContext* STGrammarParser::NotOpContext::expression() {
  return getRuleContext<STGrammarParser::ExpressionContext>(0);
}

STGrammarParser::NotOpContext::NotOpContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::NotOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotOp(this);
}
void STGrammarParser::NotOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotOp(this);
}

std::any STGrammarParser::NotOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitNotOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

STGrammarParser::ExpressionContext* STGrammarParser::ParenExprContext::expression() {
  return getRuleContext<STGrammarParser::ExpressionContext>(0);
}

STGrammarParser::ParenExprContext::ParenExprContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::ParenExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenExpr(this);
}
void STGrammarParser::ParenExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenExpr(this);
}

std::any STGrammarParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LREALContext ------------------------------------------------------------------

tree::TerminalNode* STGrammarParser::LREALContext::LREAL() {
  return getToken(STGrammarParser::LREAL, 0);
}

STGrammarParser::LREALContext::LREALContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::LREALContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLREAL(this);
}
void STGrammarParser::LREALContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLREAL(this);
}

std::any STGrammarParser::LREALContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitLREAL(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryOpContext ------------------------------------------------------------------

std::vector<STGrammarParser::ExpressionContext *> STGrammarParser::BinaryOpContext::expression() {
  return getRuleContexts<STGrammarParser::ExpressionContext>();
}

STGrammarParser::ExpressionContext* STGrammarParser::BinaryOpContext::expression(size_t i) {
  return getRuleContext<STGrammarParser::ExpressionContext>(i);
}

tree::TerminalNode* STGrammarParser::BinaryOpContext::PLUS() {
  return getToken(STGrammarParser::PLUS, 0);
}

tree::TerminalNode* STGrammarParser::BinaryOpContext::MINUS() {
  return getToken(STGrammarParser::MINUS, 0);
}

tree::TerminalNode* STGrammarParser::BinaryOpContext::MULT() {
  return getToken(STGrammarParser::MULT, 0);
}

tree::TerminalNode* STGrammarParser::BinaryOpContext::DIV() {
  return getToken(STGrammarParser::DIV, 0);
}

STGrammarParser::BinaryOpContext::BinaryOpContext(ExpressionContext *ctx) { copyFrom(ctx); }

void STGrammarParser::BinaryOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBinaryOp(this);
}
void STGrammarParser::BinaryOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBinaryOp(this);
}

std::any STGrammarParser::BinaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitBinaryOp(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::ExpressionContext* STGrammarParser::expression() {
   return expression(0);
}

STGrammarParser::ExpressionContext* STGrammarParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  STGrammarParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  STGrammarParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, STGrammarParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(85);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case STGrammarParser::NOT: {
        _localctx = _tracker.createInstance<NotOpContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(72);
        match(STGrammarParser::NOT);
        setState(73);
        expression(9);
        break;
      }

      case STGrammarParser::ID: {
        _localctx = _tracker.createInstance<VarContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(74);
        match(STGrammarParser::ID);
        break;
      }

      case STGrammarParser::INT: {
        _localctx = _tracker.createInstance<ConstContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(75);
        match(STGrammarParser::INT);
        break;
      }

      case STGrammarParser::BOOL: {
        _localctx = _tracker.createInstance<BoolConstContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(76);
        match(STGrammarParser::BOOL);
        break;
      }

      case STGrammarParser::LREAL: {
        _localctx = _tracker.createInstance<LREALContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(77);
        match(STGrammarParser::LREAL);
        break;
      }

      case STGrammarParser::T__0: {
        _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(78);
        match(STGrammarParser::T__0);
        setState(79);
        expression(0);
        setState(80);
        match(STGrammarParser::T__1);
        break;
      }

      case STGrammarParser::AXIS_ENABLE:
      case STGrammarParser::AXIS_DISABLE:
      case STGrammarParser::AXIS_STOP:
      case STGrammarParser::AXIS_MOVE_ABS:
      case STGrammarParser::AXIS_MOVE_REL:
      case STGrammarParser::AXIS_MOVE_VEL:
      case STGrammarParser::AXIS_RESET:
      case STGrammarParser::BUFFER_ENABLE:
      case STGrammarParser::BUFFER_DISABLE:
      case STGrammarParser::WAIT:
      case STGrammarParser::START_ANALOGFOCUSING:
      case STGrammarParser::STOP_ANALOGFOCUSING:
      case STGrammarParser::START_PEG:
      case STGrammarParser::STOP_PEG: {
        _localctx = _tracker.createInstance<Set1PFuncExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(82);
        one_para_function();
        break;
      }

      case STGrammarParser::AXIS_POS:
      case STGrammarParser::AXIS_VEL:
      case STGrammarParser::AXIS_ACC:
      case STGrammarParser::AXIS_JERK:
      case STGrammarParser::AXIS_DEC:
      case STGrammarParser::DRIVE_SET_DO:
      case STGrammarParser::DRIVE_SET_AO: {
        _localctx = _tracker.createInstance<Set2PFuncExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(83);
        two_para_function();
        break;
      }

      case STGrammarParser::AXIS_STAUTS_STATE:
      case STGrammarParser::AXIS_STAUTS_ENABLE:
      case STGrammarParser::AXIS_STAUTS_MOVE:
      case STGrammarParser::DRIVE_STAUTS_DI:
      case STGrammarParser::DRIVE_STAUTS_AI: {
        _localctx = _tracker.createInstance<ReadFuncExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(84);
        read_set_function();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(95);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(93);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryOpContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(87);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(88);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 128849018880) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(89);
          expression(12);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<LogicalOpContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(90);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(91);
          _la = _input->LA(1);
          if (!(_la == STGrammarParser::AND

          || _la == STGrammarParser::OR)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(92);
          expression(11);
          break;
        }

        default:
          break;
        } 
      }
      setState(97);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- If_statementContext ------------------------------------------------------------------

STGrammarParser::If_statementContext::If_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::If_statementContext::IF() {
  return getToken(STGrammarParser::IF, 0);
}

std::vector<STGrammarParser::ConditionContext *> STGrammarParser::If_statementContext::condition() {
  return getRuleContexts<STGrammarParser::ConditionContext>();
}

STGrammarParser::ConditionContext* STGrammarParser::If_statementContext::condition(size_t i) {
  return getRuleContext<STGrammarParser::ConditionContext>(i);
}

std::vector<tree::TerminalNode *> STGrammarParser::If_statementContext::THEN() {
  return getTokens(STGrammarParser::THEN);
}

tree::TerminalNode* STGrammarParser::If_statementContext::THEN(size_t i) {
  return getToken(STGrammarParser::THEN, i);
}

tree::TerminalNode* STGrammarParser::If_statementContext::END_IF() {
  return getToken(STGrammarParser::END_IF, 0);
}

std::vector<tree::TerminalNode *> STGrammarParser::If_statementContext::NEWLINE() {
  return getTokens(STGrammarParser::NEWLINE);
}

tree::TerminalNode* STGrammarParser::If_statementContext::NEWLINE(size_t i) {
  return getToken(STGrammarParser::NEWLINE, i);
}

std::vector<STGrammarParser::StatementContext *> STGrammarParser::If_statementContext::statement() {
  return getRuleContexts<STGrammarParser::StatementContext>();
}

STGrammarParser::StatementContext* STGrammarParser::If_statementContext::statement(size_t i) {
  return getRuleContext<STGrammarParser::StatementContext>(i);
}

tree::TerminalNode* STGrammarParser::If_statementContext::ELSE() {
  return getToken(STGrammarParser::ELSE, 0);
}

std::vector<tree::TerminalNode *> STGrammarParser::If_statementContext::ELSE_IF() {
  return getTokens(STGrammarParser::ELSE_IF);
}

tree::TerminalNode* STGrammarParser::If_statementContext::ELSE_IF(size_t i) {
  return getToken(STGrammarParser::ELSE_IF, i);
}


size_t STGrammarParser::If_statementContext::getRuleIndex() const {
  return STGrammarParser::RuleIf_statement;
}

void STGrammarParser::If_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIf_statement(this);
}

void STGrammarParser::If_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIf_statement(this);
}


std::any STGrammarParser::If_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitIf_statement(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::If_statementContext* STGrammarParser::if_statement() {
  If_statementContext *_localctx = _tracker.createInstance<If_statementContext>(_ctx, getState());
  enterRule(_localctx, 14, STGrammarParser::RuleIf_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(98);
    match(STGrammarParser::IF);
    setState(99);
    condition();
    setState(100);
    match(STGrammarParser::THEN);
    setState(102); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(101);
      match(STGrammarParser::NEWLINE);
      setState(104); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == STGrammarParser::NEWLINE);
    setState(107); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(106);
      statement();
      setState(109); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 15) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 15)) & 141863387725406223) != 0));

    setState(126);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == STGrammarParser::ELSE_IF) {
      setState(111);
      match(STGrammarParser::ELSE_IF);
      setState(112);
      condition();
      setState(113);
      match(STGrammarParser::THEN);
      setState(115); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(114);
        match(STGrammarParser::NEWLINE);
        setState(117); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == STGrammarParser::NEWLINE);
      setState(120); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(119);
        statement();
        setState(122); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (((((_la - 15) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 15)) & 141863387725406223) != 0));
      setState(128);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(136);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == STGrammarParser::ELSE) {
      setState(129);
      match(STGrammarParser::ELSE);
      setState(131); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(130);
        match(STGrammarParser::NEWLINE);
        setState(133); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == STGrammarParser::NEWLINE);
      setState(135);
      statement();
    }
    setState(138);
    match(STGrammarParser::END_IF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

STGrammarParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<STGrammarParser::ExpressionContext *> STGrammarParser::ConditionContext::expression() {
  return getRuleContexts<STGrammarParser::ExpressionContext>();
}

STGrammarParser::ExpressionContext* STGrammarParser::ConditionContext::expression(size_t i) {
  return getRuleContext<STGrammarParser::ExpressionContext>(i);
}

tree::TerminalNode* STGrammarParser::ConditionContext::EQ() {
  return getToken(STGrammarParser::EQ, 0);
}

tree::TerminalNode* STGrammarParser::ConditionContext::NEQ() {
  return getToken(STGrammarParser::NEQ, 0);
}

tree::TerminalNode* STGrammarParser::ConditionContext::GT() {
  return getToken(STGrammarParser::GT, 0);
}

tree::TerminalNode* STGrammarParser::ConditionContext::LT() {
  return getToken(STGrammarParser::LT, 0);
}

tree::TerminalNode* STGrammarParser::ConditionContext::AND() {
  return getToken(STGrammarParser::AND, 0);
}

tree::TerminalNode* STGrammarParser::ConditionContext::OR() {
  return getToken(STGrammarParser::OR, 0);
}

tree::TerminalNode* STGrammarParser::ConditionContext::BOOL() {
  return getToken(STGrammarParser::BOOL, 0);
}


size_t STGrammarParser::ConditionContext::getRuleIndex() const {
  return STGrammarParser::RuleCondition;
}

void STGrammarParser::ConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondition(this);
}

void STGrammarParser::ConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondition(this);
}


std::any STGrammarParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::ConditionContext* STGrammarParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 16, STGrammarParser::RuleCondition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(145);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(140);
      expression(0);
      setState(141);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 16904991277056) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(142);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(144);
      match(STGrammarParser::BOOL);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Global_var_declContext ------------------------------------------------------------------

STGrammarParser::Global_var_declContext::Global_var_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::Global_var_declContext::INT_TYPE() {
  return getToken(STGrammarParser::INT_TYPE, 0);
}

tree::TerminalNode* STGrammarParser::Global_var_declContext::ID() {
  return getToken(STGrammarParser::ID, 0);
}

tree::TerminalNode* STGrammarParser::Global_var_declContext::ASSIGN() {
  return getToken(STGrammarParser::ASSIGN, 0);
}

tree::TerminalNode* STGrammarParser::Global_var_declContext::INT() {
  return getToken(STGrammarParser::INT, 0);
}

tree::TerminalNode* STGrammarParser::Global_var_declContext::BOOL_TYPE() {
  return getToken(STGrammarParser::BOOL_TYPE, 0);
}

tree::TerminalNode* STGrammarParser::Global_var_declContext::BOOL() {
  return getToken(STGrammarParser::BOOL, 0);
}

tree::TerminalNode* STGrammarParser::Global_var_declContext::LREAL_TYPE() {
  return getToken(STGrammarParser::LREAL_TYPE, 0);
}

tree::TerminalNode* STGrammarParser::Global_var_declContext::LREAL() {
  return getToken(STGrammarParser::LREAL, 0);
}


size_t STGrammarParser::Global_var_declContext::getRuleIndex() const {
  return STGrammarParser::RuleGlobal_var_decl;
}

void STGrammarParser::Global_var_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobal_var_decl(this);
}

void STGrammarParser::Global_var_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobal_var_decl(this);
}


std::any STGrammarParser::Global_var_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitGlobal_var_decl(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::Global_var_declContext* STGrammarParser::global_var_decl() {
  Global_var_declContext *_localctx = _tracker.createInstance<Global_var_declContext>(_ctx, getState());
  enterRule(_localctx, 18, STGrammarParser::RuleGlobal_var_decl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(165);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case STGrammarParser::INT_TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(147);
        match(STGrammarParser::INT_TYPE);
        setState(148);
        match(STGrammarParser::ID);
        setState(151);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == STGrammarParser::ASSIGN) {
          setState(149);
          match(STGrammarParser::ASSIGN);
          setState(150);
          match(STGrammarParser::INT);
        }
        break;
      }

      case STGrammarParser::BOOL_TYPE: {
        enterOuterAlt(_localctx, 2);
        setState(153);
        match(STGrammarParser::BOOL_TYPE);
        setState(154);
        match(STGrammarParser::ID);
        setState(157);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == STGrammarParser::ASSIGN) {
          setState(155);
          match(STGrammarParser::ASSIGN);
          setState(156);
          match(STGrammarParser::BOOL);
        }
        break;
      }

      case STGrammarParser::LREAL_TYPE: {
        enterOuterAlt(_localctx, 3);
        setState(159);
        match(STGrammarParser::LREAL_TYPE);
        setState(160);
        match(STGrammarParser::ID);
        setState(163);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == STGrammarParser::ASSIGN) {
          setState(161);
          match(STGrammarParser::ASSIGN);
          setState(162);
          match(STGrammarParser::LREAL);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- One_para_functionContext ------------------------------------------------------------------

STGrammarParser::One_para_functionContext::One_para_functionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

STGrammarParser::One_para_set_func_nameContext* STGrammarParser::One_para_functionContext::one_para_set_func_name() {
  return getRuleContext<STGrammarParser::One_para_set_func_nameContext>(0);
}

STGrammarParser::ExpressionContext* STGrammarParser::One_para_functionContext::expression() {
  return getRuleContext<STGrammarParser::ExpressionContext>(0);
}


size_t STGrammarParser::One_para_functionContext::getRuleIndex() const {
  return STGrammarParser::RuleOne_para_function;
}

void STGrammarParser::One_para_functionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOne_para_function(this);
}

void STGrammarParser::One_para_functionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOne_para_function(this);
}


std::any STGrammarParser::One_para_functionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitOne_para_function(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::One_para_functionContext* STGrammarParser::one_para_function() {
  One_para_functionContext *_localctx = _tracker.createInstance<One_para_functionContext>(_ctx, getState());
  enterRule(_localctx, 20, STGrammarParser::RuleOne_para_function);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(167);
    one_para_set_func_name();
    setState(168);
    match(STGrammarParser::T__0);
    setState(169);
    expression(0);
    setState(170);
    match(STGrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Two_para_functionContext ------------------------------------------------------------------

STGrammarParser::Two_para_functionContext::Two_para_functionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

STGrammarParser::Two_para_set_func_nameContext* STGrammarParser::Two_para_functionContext::two_para_set_func_name() {
  return getRuleContext<STGrammarParser::Two_para_set_func_nameContext>(0);
}

std::vector<STGrammarParser::ExpressionContext *> STGrammarParser::Two_para_functionContext::expression() {
  return getRuleContexts<STGrammarParser::ExpressionContext>();
}

STGrammarParser::ExpressionContext* STGrammarParser::Two_para_functionContext::expression(size_t i) {
  return getRuleContext<STGrammarParser::ExpressionContext>(i);
}


size_t STGrammarParser::Two_para_functionContext::getRuleIndex() const {
  return STGrammarParser::RuleTwo_para_function;
}

void STGrammarParser::Two_para_functionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTwo_para_function(this);
}

void STGrammarParser::Two_para_functionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTwo_para_function(this);
}


std::any STGrammarParser::Two_para_functionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitTwo_para_function(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::Two_para_functionContext* STGrammarParser::two_para_function() {
  Two_para_functionContext *_localctx = _tracker.createInstance<Two_para_functionContext>(_ctx, getState());
  enterRule(_localctx, 22, STGrammarParser::RuleTwo_para_function);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    two_para_set_func_name();
    setState(173);
    match(STGrammarParser::T__0);
    setState(174);
    expression(0);
    setState(175);
    match(STGrammarParser::T__2);
    setState(176);
    expression(0);
    setState(177);
    match(STGrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Read_set_functionContext ------------------------------------------------------------------

STGrammarParser::Read_set_functionContext::Read_set_functionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

STGrammarParser::Read_func_nameContext* STGrammarParser::Read_set_functionContext::read_func_name() {
  return getRuleContext<STGrammarParser::Read_func_nameContext>(0);
}

STGrammarParser::ExpressionContext* STGrammarParser::Read_set_functionContext::expression() {
  return getRuleContext<STGrammarParser::ExpressionContext>(0);
}


size_t STGrammarParser::Read_set_functionContext::getRuleIndex() const {
  return STGrammarParser::RuleRead_set_function;
}

void STGrammarParser::Read_set_functionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRead_set_function(this);
}

void STGrammarParser::Read_set_functionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRead_set_function(this);
}


std::any STGrammarParser::Read_set_functionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitRead_set_function(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::Read_set_functionContext* STGrammarParser::read_set_function() {
  Read_set_functionContext *_localctx = _tracker.createInstance<Read_set_functionContext>(_ctx, getState());
  enterRule(_localctx, 24, STGrammarParser::RuleRead_set_function);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(179);
    read_func_name();
    setState(180);
    match(STGrammarParser::T__3);
    setState(181);
    expression(0);
    setState(182);
    match(STGrammarParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

STGrammarParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<STGrammarParser::ExpressionContext *> STGrammarParser::ArgumentListContext::expression() {
  return getRuleContexts<STGrammarParser::ExpressionContext>();
}

STGrammarParser::ExpressionContext* STGrammarParser::ArgumentListContext::expression(size_t i) {
  return getRuleContext<STGrammarParser::ExpressionContext>(i);
}


size_t STGrammarParser::ArgumentListContext::getRuleIndex() const {
  return STGrammarParser::RuleArgumentList;
}

void STGrammarParser::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void STGrammarParser::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}


std::any STGrammarParser::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::ArgumentListContext* STGrammarParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 26, STGrammarParser::RuleArgumentList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    expression(0);
    setState(189);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == STGrammarParser::T__2) {
      setState(185);
      match(STGrammarParser::T__2);
      setState(186);
      expression(0);
      setState(191);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Loop_statementContext ------------------------------------------------------------------

STGrammarParser::Loop_statementContext::Loop_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::Loop_statementContext::LOOP() {
  return getToken(STGrammarParser::LOOP, 0);
}

tree::TerminalNode* STGrammarParser::Loop_statementContext::INT() {
  return getToken(STGrammarParser::INT, 0);
}

tree::TerminalNode* STGrammarParser::Loop_statementContext::THEN() {
  return getToken(STGrammarParser::THEN, 0);
}

tree::TerminalNode* STGrammarParser::Loop_statementContext::END_LOOP() {
  return getToken(STGrammarParser::END_LOOP, 0);
}

std::vector<tree::TerminalNode *> STGrammarParser::Loop_statementContext::NEWLINE() {
  return getTokens(STGrammarParser::NEWLINE);
}

tree::TerminalNode* STGrammarParser::Loop_statementContext::NEWLINE(size_t i) {
  return getToken(STGrammarParser::NEWLINE, i);
}

std::vector<STGrammarParser::StatementContext *> STGrammarParser::Loop_statementContext::statement() {
  return getRuleContexts<STGrammarParser::StatementContext>();
}

STGrammarParser::StatementContext* STGrammarParser::Loop_statementContext::statement(size_t i) {
  return getRuleContext<STGrammarParser::StatementContext>(i);
}


size_t STGrammarParser::Loop_statementContext::getRuleIndex() const {
  return STGrammarParser::RuleLoop_statement;
}

void STGrammarParser::Loop_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoop_statement(this);
}

void STGrammarParser::Loop_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoop_statement(this);
}


std::any STGrammarParser::Loop_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitLoop_statement(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::Loop_statementContext* STGrammarParser::loop_statement() {
  Loop_statementContext *_localctx = _tracker.createInstance<Loop_statementContext>(_ctx, getState());
  enterRule(_localctx, 28, STGrammarParser::RuleLoop_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    match(STGrammarParser::LOOP);
    setState(193);
    match(STGrammarParser::INT);
    setState(194);
    match(STGrammarParser::THEN);
    setState(196); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(195);
      match(STGrammarParser::NEWLINE);
      setState(198); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == STGrammarParser::NEWLINE);
    setState(201); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(200);
      statement();
      setState(203); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 15) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 15)) & 141863387725406223) != 0));
    setState(205);
    match(STGrammarParser::END_LOOP);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Till_statementContext ------------------------------------------------------------------

STGrammarParser::Till_statementContext::Till_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::Till_statementContext::TILL() {
  return getToken(STGrammarParser::TILL, 0);
}

STGrammarParser::ConditionContext* STGrammarParser::Till_statementContext::condition() {
  return getRuleContext<STGrammarParser::ConditionContext>(0);
}


size_t STGrammarParser::Till_statementContext::getRuleIndex() const {
  return STGrammarParser::RuleTill_statement;
}

void STGrammarParser::Till_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTill_statement(this);
}

void STGrammarParser::Till_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTill_statement(this);
}


std::any STGrammarParser::Till_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitTill_statement(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::Till_statementContext* STGrammarParser::till_statement() {
  Till_statementContext *_localctx = _tracker.createInstance<Till_statementContext>(_ctx, getState());
  enterRule(_localctx, 30, STGrammarParser::RuleTill_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    match(STGrammarParser::TILL);
    setState(208);
    match(STGrammarParser::T__0);
    setState(209);
    condition();
    setState(210);
    match(STGrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Block_statementContext ------------------------------------------------------------------

STGrammarParser::Block_statementContext::Block_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* STGrammarParser::Block_statementContext::BLOCK() {
  return getToken(STGrammarParser::BLOCK, 0);
}

tree::TerminalNode* STGrammarParser::Block_statementContext::END_BLOCK() {
  return getToken(STGrammarParser::END_BLOCK, 0);
}

std::vector<tree::TerminalNode *> STGrammarParser::Block_statementContext::NEWLINE() {
  return getTokens(STGrammarParser::NEWLINE);
}

tree::TerminalNode* STGrammarParser::Block_statementContext::NEWLINE(size_t i) {
  return getToken(STGrammarParser::NEWLINE, i);
}

std::vector<STGrammarParser::StatementContext *> STGrammarParser::Block_statementContext::statement() {
  return getRuleContexts<STGrammarParser::StatementContext>();
}

STGrammarParser::StatementContext* STGrammarParser::Block_statementContext::statement(size_t i) {
  return getRuleContext<STGrammarParser::StatementContext>(i);
}


size_t STGrammarParser::Block_statementContext::getRuleIndex() const {
  return STGrammarParser::RuleBlock_statement;
}

void STGrammarParser::Block_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock_statement(this);
}

void STGrammarParser::Block_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<STGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock_statement(this);
}


std::any STGrammarParser::Block_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<STGrammarVisitor*>(visitor))
    return parserVisitor->visitBlock_statement(this);
  else
    return visitor->visitChildren(this);
}

STGrammarParser::Block_statementContext* STGrammarParser::block_statement() {
  Block_statementContext *_localctx = _tracker.createInstance<Block_statementContext>(_ctx, getState());
  enterRule(_localctx, 32, STGrammarParser::RuleBlock_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    match(STGrammarParser::BLOCK);
    setState(214); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(213);
      match(STGrammarParser::NEWLINE);
      setState(216); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == STGrammarParser::NEWLINE);
    setState(219); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(218);
      statement();
      setState(221); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 15) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 15)) & 141863387725406223) != 0));
    setState(223);
    match(STGrammarParser::END_BLOCK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool STGrammarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 6: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool STGrammarParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 11);
    case 1: return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

void STGrammarParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  stgrammarParserInitialize();
#else
  ::antlr4::internal::call_once(stgrammarParserOnceFlag, stgrammarParserInitialize);
#endif
}
