/*
 * Copyright 2006-2008 The FLWOR Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "imap_function.h"
#include <sstream>
#include <zorba/zorba.h>
#include "imap_module.h"
#include <map>

namespace zorba { namespace emailmodule {


ImapFunction::ImapFunction(const ImapModule* aModule)
        : theModule(aModule)
{
}
ImapFunction::~ImapFunction()
{
}

String
ImapFunction::getURI() const
{
  return theModule->getURI();
}

void
ImapFunction::throwError(
    const std::string aErrorMessage,
    const XQUERY_ERROR& aErrorType)
{
  throw zorba::ExternalFunctionData::createZorbaException(aErrorType,
      aErrorMessage.c_str(), __FILE__, __LINE__);
}

void 
ImapFunction::throwImapError(const std::string aErrorMessage) {
  throwError(aErrorMessage, XPTY0004); 
}  


void 
ImapFunction::getHostUserPassword(const StatelessExternalFunction::Arguments_t& aArgs,
                          int aPos,
                          std::string& aHost,
                          std::string& aUserName,
                          std::string& aPassword) {
  Item lNode;
  aArgs[aPos]->next(lNode);
  Iterator_t lChildren = lNode.getChildren();
  lChildren->open();
  Item lChild;
  lChildren->next(lChild);
  aHost = lChild.getStringValue().c_str();
  lChildren->next(lChild);
  aUserName = lChild.getStringValue().c_str();
  lChildren->next(lChild);
  aPassword = lChild.getStringValue().c_str();
  
}

String
ImapFunction::getOneStringArg(
    const StatelessExternalFunction::Arguments_t& aArgs,
    int aPos)
{
  Item lItem;
  if (!aArgs[aPos]->next(lItem)) {
    std::stringstream lErrorMessage;
    lErrorMessage << "An empty-sequence is not allowed as "
                  << aPos << ". parameter.";
    throwError(lErrorMessage.str(), XPTY0004);
  }
  zorba::String lTmpString = lItem.getStringValue();
  if (aArgs[aPos]->next(lItem)) {
    std::stringstream lErrorMessage;
    lErrorMessage << "A sequence of more then one item is not allowed as "
                  << aPos << ". parameter.";
    throwError(lErrorMessage.str(), XPTY0004);
  }
  return lTmpString;
}

std::string
ImapFunction::getMessageNumbers(
    const StatelessExternalFunction::Arguments_t& aArgs,
    int aPos)
{
  Item lItem;
  std::stringstream lMessageNumbers;
  aArgs[aPos]->next(lItem);
  lMessageNumbers << lItem.getStringValue().c_str();
  while(aArgs[aPos]->next(lItem)) {
    lMessageNumbers << "," << lItem.getStringValue().c_str();
  }
  return lMessageNumbers.str(); 
}


unsigned long 
ImapFunction::getOneMessageNumber(
    const StatelessExternalFunction::Arguments_t& aArgs,
    int aPos)
{
  Item lItem;
  aArgs[aPos]->next(lItem);
  return lItem.getLongValue();
}


bool
ImapFunction::getOneBoolArg(
    const StatelessExternalFunction::Arguments_t& aArgs,
    int aPos)
{
  Item lItem;
  if (!aArgs[aPos]->next(lItem)) {
    std::stringstream lErrorMessage;
    lErrorMessage << "An empty-sequence is not allowed as "
                  << aPos << ". parameter.";
    throwError(lErrorMessage.str(), XPTY0004);
  }
  bool lTmpBool = lItem.getBooleanValue();
  if (aArgs[aPos]->next(lItem)) {
    std::stringstream lErrorMessage;
    lErrorMessage << "A sequence of more then one item is not allowed as "
                  << aPos << ". parameter.";
    throwError(lErrorMessage.str(), XPTY0004);
  }
  return lTmpBool;
}


std::string
ImapFunction::getDateTime(const std::string& aCClientDateTime) {
  std::stringstream lResult;    
  std::stringstream lDateTimeStream(aCClientDateTime);
  std::string lBuffer;
  std::vector<std::string> lTokens;
  while (lDateTimeStream >> lBuffer) { 
    lTokens.push_back(lBuffer);
  }
  // YYYY-MM-DDThh:mm:ss, first push YYYY
  lResult << lTokens[3] << "-";
  // then push MM
  // build up map for Months
  std::map<std::string, std::string> lMonths;
  lMonths.insert(std::pair<std::string, std::string> ("Jan", "01"));
  lMonths.insert(std::pair<std::string, std::string> ("Feb", "02"));
  lMonths.insert(std::pair<std::string, std::string> ("Mar", "03"));
  lMonths.insert(std::pair<std::string, std::string> ("Apr", "04"));
  lMonths.insert(std::pair<std::string, std::string> ("May", "05"));
  lMonths.insert(std::pair<std::string, std::string> ("Jun", "06"));
  lMonths.insert(std::pair<std::string, std::string> ("Jul", "07"));
  lMonths.insert(std::pair<std::string, std::string> ("Aug", "08"));
  lMonths.insert(std::pair<std::string, std::string> ("Sep", "09"));
  lMonths.insert(std::pair<std::string, std::string> ("Okt", "10"));
  lMonths.insert(std::pair<std::string, std::string> ("Nov", "11"));
  lMonths.insert(std::pair<std::string, std::string> ("Dez", "12"));
    
  lResult << lMonths.find(lTokens[2])->second << "-";
  // then push DD
  lResult << lTokens[1] << "T";
  // now hh:mm:ss
  lResult << lTokens[4].substr(0,2) << ":" << lTokens[4].substr(3,2) << ":" << lTokens[4].substr(6,2);

  return lResult.str();
  


}  


void
ImapFunction::createInnerNodeWithText(const ImapModule* aModule, Item aParent, const std::string& aNamespace, const std::string& aPrefix, const std::string& aName, const std::string& aType, const std::string& aContent) {
   std::vector<std::pair<String, String> > null_binding; 
  Item lName = aModule->getItemFactory()->createQName(aNamespace, aPrefix, aName);
  Item lType = aModule->getItemFactory()->createQName(aNamespace,  aType);
  Item lItem = aModule->getItemFactory()->createElementNode(aParent, lName, lType, false, false, null_binding);
  aModule->getItemFactory()->createTextNode(lItem, String(aContent));
}  

void 
ImapFunction::createEmailAddressNode(const ImapModule* aModule, Item aParent, const std::string& aName, const char* aPersonal, const char* aMailbox, const char* aHost) {
  Item lType = aModule->getItemFactory()->createQName("http://www.zorba-xquery.com/modules/email/email", "emailAddress");
  Item lName = aModule->getItemFactory()->createQName("http://www.zorba-xquery.com/modules/email/email", "email",  aName);

  std::vector<std::pair<String, String> >  ns_binding; 
   ns_binding.push_back(std::pair<String, String>("email", "http://www.zorba-xquery.com/modules/email/email"));
 
  Item lItem = aModule->getItemFactory()->createElementNode(aParent, lName, lType, false, false, ns_binding);
  if (aPersonal) {
    createInnerNodeWithText(aModule, lItem, "http://www.zorba-xquery.com/modules/email/email", "email", "name", "string", aPersonal);
  }
  if ((aMailbox) && (aHost)) {
    createInnerNodeWithText(aModule, lItem, "http://www.zorba-xquery.com/modules/email/email", "email", "email", "string", std::string(aMailbox) + "@" + std::string(aHost));  
  }
}



void 
ImapFunction::createRecipentNode(const ImapModule* aModule, Item aParent, const std::string& aName, const char* aPersonal, const char* aMailbox, const char* aHost) {                    
  Item lType = aModule->getItemFactory()->createQName("http://www.zorba-xquery.com/modules/email/email", "recipientType");                                                                    
  Item lName = aModule->getItemFactory()->createQName("http://www.zorba-xquery.com/modules/email/email", "email",  "recipient");                           
  
  std::vector<std::pair<String, String> >  ns_binding;                                        
    ns_binding.push_back(std::pair<String, String>("email", "http://www.zorba-xquery.com/modules/email/email"));
 
  Item lItem = aModule->getItemFactory()->createElementNode(aParent, lName, lType, false, false, ns_binding); 
  createEmailAddressNode(aModule, lItem, aName, aPersonal, aMailbox, aHost);
  
}
  




} /* namespace emailmodule */ } /* namespace zorba */
