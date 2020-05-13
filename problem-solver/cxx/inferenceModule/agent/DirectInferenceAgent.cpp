/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/
#include <map>

#include <sc-kpm/sc-agents-common/keynodes/CoreKeynodes.hpp>
#include <sc-kpm/sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/AgentUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/LogicRuleUtils.hpp>
#include <manager/DirectInferenceManager.hpp>

#include "DirectInferenceAgent.hpp"
#include "keynodes/InferenceKeynodes.hpp"

using namespace std;
using namespace utils;
using namespace scAgentsCommon;

namespace inference
{

//DirectInferenceAgent::DirectInferenceAgent(const char * name, sc_uint8 accessLvl) : ScAgent(name, accessLvl)
//{
//  this->inferenceManager = new DirectInferenceManager();
//}

SC_AGENT_IMPLEMENTATION(DirectInferenceAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr targetTemplate = IteratorUtils::getFirstByOutRelation(ms_context.get(), questionNode, CoreKeynodes::rrel_1);
  ScAddr ruleSet = IteratorUtils::getFirstByOutRelation(ms_context.get(), questionNode, CoreKeynodes::rrel_2);
  ScAddr argumentSet = IteratorUtils::getFirstByOutRelation(ms_context.get(), questionNode, CoreKeynodes::rrel_3);

  if (!targetTemplate.IsValid() || !ruleSet.IsValid() || !argumentSet.IsValid())
  {
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }


  AgentUtils::finishAgentWork((ScMemoryContext *) ms_context.get(), questionNode, targetTemplate);
  return SC_RESULT_OK;
}
}