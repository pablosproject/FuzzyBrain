/*
 *
 *  Created on: Sep 20, 2012
 *      Author: igloo
 */

#include "XMLFPParser.h"

	//Constant definition
	static const char* APPLICATION_TAG = "Application";
	static const char* LINGUISTIC_VARIABLE_TAG = "FuzzyFunction";
	static const char* LINGUISTIC_VARIABLES_TAG = "FuzzyFunctions";
	static const char* LINGUISTIC_VARIABLE_ID_TAG = "FuzzyFunctionId";
	static const char* LINGUISTIC_VARIABLE_LOW_BOUND_TAG = "LowValue";
	static const char* LINGUISTIC_VARIABLE_UP_BOUND_TAG = "HighValue";
	static const char* LINGUISTIC_VARIABLE_VALUE_TAG = "Value";
	static const char* LINGUISTIC_VARIABLE_SETS_TAG = "FuzzyValues";
	static const char* LINGUISTIC_VARIABLE_SET_TAG = "FuzzyValue";
	static const char* LINGUISTIC_VARIABLE_SET_ID_TAG = "FuzzyValueId";
	static const char* LINGUISTIC_VARIABLE_SET_DEFINITION_TAG = "FuzzyValueMagnitude";
	static const char* LINGUISTIC_VARIABLE_SET_POINT_A_TAG = "Avalue";
	static const char* LINGUISTIC_VARIABLE_SET_POINT_B_TAG = "Bvalue";
	static const char* LINGUISTIC_VARIABLE_SET_POINT_C_TAG = "Cvalue";
	static const char* LINGUISTIC_VARIABLE_SET_POINT_D_TAG = "Dvalue";
	static const char* RULES_TAG = "FuzzyRules";
	static const char* RULE_TAG = "FuzzyRuleLine";
	static const char* RULE_CONSEQUENT_TAG = "Consequent";
	static const char* RULE_TOKENS_TAG = "TokenCollection";
	static const char* RULE_TOKEN_TAG = "Token";
	static const char* FUZZY_OBJECT_TAG = "FuzzyObject";
	static const char* KNOWLEDGE_CHIP_TAG = "KnowledgeChip";
	static const char* FUZZY_OBJECT_BEHAVIOUR_TAG = "FuzzyBehaviour";
	static const char* RULE_VALUE_TAG = "LitteralValue";


XMLFPParser::XMLFPParser() {}

XMLFPParser::~XMLFPParser() {}



bool XMLFPParser::Parse(const string& filePath, FuzzyEngine* engine){

	xml_document doc;

	const char *file;
	file = filePath.c_str();

	xml_parse_result result = doc.load_file(file);
	if (!result){
		LERROR << "Error in parsing the xml file. File inexistent or invalid: " << file;
		return false;
	}

	xml_node application = doc.child(APPLICATION_TAG);
	xml_node fuzzy_object = application.child(FUZZY_OBJECT_TAG); 		// search in the root there's some fuzzy set
	xml_node knowledge_chip = application.child(KNOWLEDGE_CHIP_TAG);	// search for knowledge chip

	MamdaniFuzzyObject *root= new MamdaniFuzzyObject();

	xml_node test =application.child(KNOWLEDGE_CHIP_TAG).next_sibling().next_sibling().child(FUZZY_OBJECT_TAG);

	//If there's a fuzzy object I process the object existent and stop
	if(!fuzzy_object){
		/*Parse of the linguistic variables*/
		string consequent = consequentNameChip(application);
		uniformTokenName(consequent);
		if (!loopLinguisticVariables(application, root, consequent)){
			LERROR << "Error in parse linguistic variables: " << consequent;
			return false;
		}

		//Cerco tutti i knowledge chip e li inserisco come variabili.
		loopKnowledgeChip(application,root, engine);

		if (!loopRules(application.child(RULES_TAG),root)){
			LERROR << "Error in parse rules: " << consequent;
			return false;
		}
		engine->addRootFuzzyObject(root);

		return true;
	}
	else{
		//Parse only the fuzzy object and stop it
		return parseFuzzyObject(fuzzy_object, root);
	}

}

bool XMLFPParser::parseFuzzyObject(const xml_node& object_root,
		MamdaniFuzzyObject* object) {

	/*PARSE OF LINGUISTIC VARIABLES IN THE OBJECT*/
	string outputName = consequentNameObject(object_root);
	uniformTokenName(outputName);

	xml_node variables = object_root.child(LINGUISTIC_VARIABLES_TAG);

	if(!loopLinguisticVariables(variables, object, outputName)){
		LERROR << "Error parsing the variables, object: " << outputName;
	}

	/*PARSE OF THE RULES */
	//Search the behaviour node
	xml_node rules = object_root.child(FUZZY_OBJECT_BEHAVIOUR_TAG).child(RULES_TAG);

	if(!loopRules(rules, object)){
		LERROR << "Error parsing the rules, object: " << outputName;
		return false;
	}

	return true;
}

bool XMLFPParser::loopLinguisticVariables(const xml_node& node,
	MamdaniFuzzyObject* object, const string& outputName) {

	for (xml_node lang_var_root = node.child(LINGUISTIC_VARIABLE_TAG) ; lang_var_root ; lang_var_root = lang_var_root.next_sibling(LINGUISTIC_VARIABLE_TAG)){
			if(!parseLinguisticVariable(lang_var_root, object, outputName)){
				LERROR << "Error parsing the object " +  outputName;
				return false;
			}
		}

	return true;
}

bool XMLFPParser::parseLinguisticVariable(const xml_node& node,
		MamdaniFuzzyObject* object, const string& outputName) {

	string variable_name = node.child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value();
	if (variable_name == outputName) // it's the output variable
		return processOutputVariable(node, object);
	else
		return processInputVariable(node, object);
}

bool XMLFPParser::processInputVariable(const xml_node& var_root,
		MamdaniFuzzyObject* object) {

	InputLinguisticVariable *variable = new InputLinguisticVariable(var_root.child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value(),
																	parsing::extractFloat(var_root.child(LINGUISTIC_VARIABLE_LOW_BOUND_TAG).child(LINGUISTIC_VARIABLE_VALUE_TAG).first_child().value()),
																	parsing::extractFloat(var_root.child(LINGUISTIC_VARIABLE_UP_BOUND_TAG).child(LINGUISTIC_VARIABLE_VALUE_TAG).first_child().value()));
	if(!loopFuzzySets(var_root.child(LINGUISTIC_VARIABLE_SETS_TAG),variable)){
		LERROR << "Error in parsing the fuzzy set for the variable : " << std::string(var_root.child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value());
		return false;
	}

	return object->addInputVar(variable);
}

bool XMLFPParser::processOutputVariable(const xml_node& var_root,
		MamdaniFuzzyObject* object) {

	MamdaniOutputVariable *variable = new MamdaniOutputVariable(var_root.child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value(),
																	parsing::extractFloat(var_root.child(LINGUISTIC_VARIABLE_LOW_BOUND_TAG).child(LINGUISTIC_VARIABLE_VALUE_TAG).first_child().value()),
																	parsing::extractFloat(var_root.child(LINGUISTIC_VARIABLE_UP_BOUND_TAG).child(LINGUISTIC_VARIABLE_VALUE_TAG).first_child().value()));

	if(!loopFuzzySets(var_root.child(LINGUISTIC_VARIABLE_SETS_TAG),variable)){
		LERROR << "Error in parsing the fuzzy set for the variable : " << std::string(var_root.child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value());
		return false;
	}

	return object->setOutputVar(variable);

}

bool XMLFPParser::parseFuzzySet (const xml_node& node, LinguisticVariable* variable){

	xml_node magnitude = node.child(LINGUISTIC_VARIABLE_SET_DEFINITION_TAG);

	float A = parsing::extractFloat(magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_A_TAG).first_child().value());
	float B = parsing::extractFloat(magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_B_TAG).first_child().value());
	float C = parsing::extractFloat(magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_C_TAG).first_child().value());
	float D =parsing::extractFloat(magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_D_TAG).first_child().value());

	LDEBUG << "Fuzzy Set:"<< node.child(LINGUISTIC_VARIABLE_SET_ID_TAG).first_child().value();
	LDEBUG << " A "<< magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_A_TAG).first_child().value();
	LDEBUG << " B "<< magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_B_TAG).first_child().value();
	LDEBUG << " C "<< magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_C_TAG).first_child().value();
	LDEBUG << " D "<< magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_D_TAG).first_child().value();

	correctPoint(A,variable);
	correctPoint(B,variable);
	correctPoint(C,variable);
	correctPoint(D,variable);

	if (A == B && B == C && C == D)
		return variable->addSet(new SingletonFuzzySet(node.child(LINGUISTIC_VARIABLE_SET_ID_TAG).first_child().value(), A));
	else if (B == C)
		return variable->addSet(new TriangularFuzzySet(node.child(LINGUISTIC_VARIABLE_SET_ID_TAG).first_child().value(), A, B, D));
	else if (A == B && C == D)
		return variable->addSet(new RectangularFuzzySet(node.child(LINGUISTIC_VARIABLE_SET_ID_TAG).first_child().value(), A, D));
	else
		return variable->addSet(new TrapezoidalFuzzySet(node.child(LINGUISTIC_VARIABLE_SET_ID_TAG).first_child().value(), A, B, C, D));
}

bool XMLFPParser::parseRule (const xml_node& rule, MamdaniFuzzyObject* object){

	string rule_string = rule.child(RULE_CONSEQUENT_TAG).child(RULE_VALUE_TAG).first_child().value();
	uniformRuleSintax(rule_string);
	MamdaniRule* toAdd = new MamdaniRule(rule_string);
	return object->addRule(toAdd);
}

bool XMLFPParser::loopFuzzySets(const xml_node& sets_root,
		LinguisticVariable* variable) {

	//cerco tutti i set della variabile linguistica
	for (xml_node fuzzy_set = sets_root.child(LINGUISTIC_VARIABLE_SET_TAG); fuzzy_set;	fuzzy_set = fuzzy_set.next_sibling(LINGUISTIC_VARIABLE_SET_TAG)) {
		if (!parseFuzzySet(fuzzy_set, variable)) {
			LERROR << " Error during the parsing of the variable " << variable->getName();
			return false;
		}
	}
	return true;

}

bool XMLFPParser::loopRules(const xml_node& rules_root,
		MamdaniFuzzyObject* object) {

	for (xml_node rule = rules_root.child(RULE_TAG); rule; rule = rule.next_sibling(RULE_TAG)){
		if(!parseRule(rule, object)){
			LERROR << "Error during parse rule for object: " << object->getName();
			return false;
		}
	}
	return true;
}

const char_t* XMLFPParser::consequentNameChip (const xml_node& rules_root){
	return rules_root.child(RULES_TAG).child(RULE_TAG).child(
			RULE_CONSEQUENT_TAG).child(
			RULE_TOKENS_TAG).child(RULE_TOKEN_TAG).child(
			LINGUISTIC_VARIABLE_TAG).first_child().value();
}

const char_t* XMLFPParser::consequentNameObject(
		const xml_node& object_root) {

	xml_node consequent= object_root.child(FUZZY_OBJECT_BEHAVIOUR_TAG).child(
			RULES_TAG).child(RULE_TAG).child(RULE_CONSEQUENT_TAG);

	xml_node token_collection = consequent.child(RULE_TOKENS_TAG);	//There's time where there isn't token collection

	if(token_collection)
		return token_collection.child(RULE_TOKEN_TAG).child(LINGUISTIC_VARIABLE_TAG).first_child().value();
	else
		return consequent.child(RULE_TOKEN_TAG).child(LINGUISTIC_VARIABLE_TAG).first_child().value();
}

void XMLFPParser::uniformTokenName(std::string& tokenName) {

	size_t find = tokenName.find_first_of("_");
	if(find != string::npos)
		tokenName.erase(0, find+1); //erase all the inappropriate char
}

void XMLFPParser::correctPoint(float& X, const LinguisticVariable* variable) {
	if (X < variable->getMinRange())
		X = variable->getMinRange();
	if (X > variable->getMaxRange())
		X = variable->getMaxRange();
}

void XMLFPParser::uniformRuleSintax(string& rule) {
		char chars[] = "()";

	   for (unsigned int i = 0; i < strlen(chars); ++i)
	   {
	      rule.erase (std::remove(rule.begin(), rule.end(), chars[i]), rule.end());
	   }
}

bool XMLFPParser::loopKnowledgeChip(const xml_node& applicationRoot,
		MamdaniFuzzyObject* object, FuzzyEngine* engine) {

	//Loop on all the knowledge chips
	for(xml_node chips = applicationRoot.child(KNOWLEDGE_CHIP_TAG); chips; chips = chips.next_sibling(KNOWLEDGE_CHIP_TAG)){
		LDEBUG << "Chip Name: " << chips.first_child().first_child().value();

		//process every single knowledge chip
		if(MamdaniFuzzyObject* result = processKnowledgeChip(chips,engine)){
			InputLinguisticVariable *temp = new InputLinguisticVariable(*(result->getOutputVar()));
			if(!object->addInputVar(temp) || !object->setInput(temp->getName(),result)){
				LERROR << "Error in adding the input nested variable for chip named: " << chips.first_child().first_child().value();
				return false;
			}
			else
				engine->addFuzzyObject(result);
		}
		else{
			LERROR << "Error in processing the chip named: " << chips.first_child().first_child().value();
			return false;
		}
	}
	return true;
}

MamdaniFuzzyObject* XMLFPParser::processKnowledgeChip(
		const xml_node& chipRoot, FuzzyEngine* engine) {

	MamdaniFuzzyObject *object_chip = new MamdaniFuzzyObject();

	//Output variable name for the chip
	string consequent = consequentNameChip(chipRoot);
	uniformTokenName(consequent);

	//Search for linguistic variables of the fuzzy set
	if(!loopLinguisticVariables(chipRoot,object_chip,consequent)){
		LERROR << "Error in processing knowledge chip's" << consequent << " linguistic variables.";
		return NULL;
	}

	//Search for fuzzy object nested
	if(chipRoot.child(FUZZY_OBJECT_TAG)){
		//Process every object and extract the input var fot the knowledge chip
		for(xml_node obj = chipRoot.child(FUZZY_OBJECT_TAG) ; obj; obj = obj.next_sibling(FUZZY_OBJECT_TAG)){
			MamdaniFuzzyObject *temp = new MamdaniFuzzyObject();	//temp obj storage
			if (parseFuzzyObject(obj,temp)){
				engine->addFuzzyObject(temp);

				const LinguisticVariable *out = temp->getOutputVar();
				InputLinguisticVariable * input = new InputLinguisticVariable(*out);

				if (!object_chip->addInputVar(input) || !object_chip->setInput(out->getName(), temp)){ // add the input variable and refer it to other objects
					LERROR << "Error in creating nested input var knowledge chip: " << consequent;
					return NULL;
				}
			}
			else{
				LERROR << "Error during the parsing of the nested fuzzy object of the knowledge chip: " << consequent;
				return NULL;
			}
		}
	}

	//Search for rules for the external knowledge chip
	if(!loopRules(chipRoot.child(RULES_TAG),object_chip)){
		LERROR << "Error in processing knowledge chip's" << consequent  << "rules.";
		return NULL;
	}

	return object_chip;
}

