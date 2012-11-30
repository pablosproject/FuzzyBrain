/*
 * Parser.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: igloo
 */

#include "XMLFPParser.h"

	//Constant definition
	static const char* APPLICATION_TAG = "Application";
	static const char* LINGUISTIC_VARIABLE_TAG = "FuzzyFunction";
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
	static const char* RULE_ANTECEDENT_TAG = "Antecedent";
	static const char* RULE_CONSEQUENT_TAG = "Consequent";
	static const char* RULE_TOKENS_TAG = "TokenCollection";
	static const char* RULE_TOKEN_TAG = "Token";
	static const char* RULE_OPERATOR_TAG = "Connector";
	static const char* FUZZY_OBJECT_TAG = "FuzzyObject";
	static const char* KNOWLEDGE_CHIP_TAG = "KnowledgeChip";
	static const char* FUZZY_OBJECT_BEHAVIOUR_TAG = "FuzzyBehaviour";

log4cplus::Logger XMLFPParser::logger = logging::getLogger("XMLFPParser");

XMLFPParser::XMLFPParser() {}

XMLFPParser::~XMLFPParser() {}

const pugi::char_t* XMLFPParser::consequentNameChip(
		const xml_node& rules_root) {
	return rules_root.child(RULES_TAG).child(RULE_TAG).child(
			RULE_CONSEQUENT_TAG).child(
			RULE_TOKENS_TAG).child(RULE_TOKEN_TAG).child(
			LINGUISTIC_VARIABLE_TAG).first_child().value();
}

const pugi::char_t* XMLFPParser::consequentNameObject(
		const xml_node& rules_root) {
	return rules_root.child(FUZZY_OBJECT_BEHAVIOUR_TAG).child(
			RULES_TAG).child(RULE_TAG).child(RULE_CONSEQUENT_TAG).child(
			RULE_TOKENS_TAG).child(RULE_TOKEN_TAG).child(
			LINGUISTIC_VARIABLE_TAG).first_child().value();
}

bool XMLFPParser::Parse(const std::string& filePath) {

	xml_document doc;

	const char *file;
	file = filePath.c_str();

	xml_parse_result result = doc.load_file(file);

	xml_node application = doc.child(APPLICATION_TAG);
	xml_node rules_root = application.child(RULES_TAG);
	xml_node fuzzy_object = application.child(FUZZY_OBJECT_TAG); 		// search in the root there's some fuzzy set
	xml_node knowledge_chip = application.child(KNOWLEDGE_CHIP_TAG);	// search for knowledge chip
	std::string consequent_name = consequentNameChip(rules_root);

	MamdaniFuzzyObject *root=new MamdaniFuzzyObject();

	xml_node test =application.child(KNOWLEDGE_CHIP_TAG).next_sibling().next_sibling().child(FUZZY_OBJECT_TAG);

	parseFuzzyObject(test, root);
	//If there's a fuzzy object I process this and stop
	if(!fuzzy_object){

	}
	else{

	}
	//Create a Fuzzy Object, that is the root


	//search for linguistic variable for the root object.
	for (xml_node lang_var_root = application.child(LINGUISTIC_VARIABLE_TAG) ; lang_var_root ; lang_var_root = lang_var_root.next_sibling(LINGUISTIC_VARIABLE_TAG)){

		parseLinguisticVariable(lang_var_root, root);
	}

	for (xml_node rule_root = rules_root.child(RULE_TAG) ; rule_root ; rule_root = rule_root.next_sibling(RULE_TAG)){

		parseRule(&rule_root);
	}

	//TODO:cerca per knowledge chip
	uniformTokenName(consequent_name);
	std::cout<< "Ci sono fuzzy object: "<< consequent_name;


}

bool XMLFPParser::parseLinguisticVariable(const xml_node& node,
		MamdaniFuzzyObject* object, const string& outputName) {

	//DEBUG
	std::cout << "Variabile linguistica: "
			<< node.child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value()
			<< "\n";	//TODO:elimina quando finito
	printf("Min value: %f \n",
			atof(
					node.child(LINGUISTIC_VARIABLE_LOW_BOUND_TAG).child(
							LINGUISTIC_VARIABLE_VALUE_TAG).first_child().value()));	//TODO:elimina
	//
	std::string variable_name =
			node.child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value();

	if (variable_name == outputName) // it's the output variable
		MamdaniOutputVariable* variable =
				new InputLinguisticVariable(
						node.child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value(),
						atof(
								node.child(LINGUISTIC_VARIABLE_LOW_BOUND_TAG).child(
										LINGUISTIC_VARIABLE_VALUE_TAG).first_child().value()),
						atof(
								node.child(LINGUISTIC_VARIABLE_UP_BOUND_TAG).child(
										LINGUISTIC_VARIABLE_VALUE_TAG).first_child().value()));
	xml_node fuzzy_sets = node.child(LINGUISTIC_VARIABLE_SETS_TAG);

	//cerco tutti i set della variabile linguistica
	for (xml_node fuzzy_set = fuzzy_sets.child(LINGUISTIC_VARIABLE_SET_TAG);
			fuzzy_set;
			fuzzy_set = fuzzy_set.next_sibling(LINGUISTIC_VARIABLE_SET_TAG)) {
		if (!parseFuzzySet(fuzzy_set, variable)) {
			LOG4CPLUS_ERROR(this->logger,
					"Error during the parsing of the variable: " + std::string(node.child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value()));
			return false;
		}
	}

	//Cerco tutti i knowledge chip della variabile linguistica

}

bool XMLFPParser::parseFuzzySet (const xml_node& node, LinguisticVariable* variable){

	xml_node magnitude = node.child(LINGUISTIC_VARIABLE_SET_DEFINITION_TAG);

	float A = atof(magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_A_TAG).first_child().value());
	float B = atof(magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_B_TAG).first_child().value());
	float C = atof(magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_C_TAG).first_child().value());
	float D = atof(magnitude.child(LINGUISTIC_VARIABLE_SET_POINT_D_TAG).first_child().value());

	std::cout<< "Fuzzy Set:"<< node.child(LINGUISTIC_VARIABLE_SET_ID_TAG).first_child().value()<<" .A"<< A << "B "<< B << "C "<< C <<" D "<< D <<" \n";
	correctPoint(A,variable);
	correctPoint(B,variable);
	correctPoint(C,variable);
	correctPoint(D,variable);

	if (B == C)
		return variable->addSet(new TriangularFuzzySet(node.child(LINGUISTIC_VARIABLE_SET_ID_TAG).first_child().value(), A, B, D));
	else if (A == B && C == D)
		return variable->addSet(new RectangularFuzzySet(node.child(LINGUISTIC_VARIABLE_SET_ID_TAG).first_child().value(), A, D));
	else
		return variable->addSet(new TrapezoidalFuzzySet(node.child(LINGUISTIC_VARIABLE_SET_ID_TAG).first_child().value(), A, B, C, D));
}

void XMLFPParser::parseRule (const xml_node* node){

	std::cout << "Rule :" << node->first_child().first_child().value() <<"\n";

	//ho in mano gli antecedenti antecedente
	xml_node antecedents = node->child(RULE_ANTECEDENT_TAG);
	xml_node token_collection = antecedents.child(RULE_TOKENS_TAG);

	for (xml_node token = token_collection.child(RULE_TOKEN_TAG) ; token ; token = token.next_sibling(RULE_TOKEN_TAG)){

		parseToken(&token);
	}

}

void XMLFPParser::parseToken(const xml_node* token){

	//TODO:Gestisci e salve il singolo token con l'operazione

	xml_node variable = token->child(LINGUISTIC_VARIABLE_TAG);
	xml_node set = token->child(LINGUISTIC_VARIABLE_SET_TAG);
	xml_node operation = token->child(RULE_OPERATOR_TAG);
	const char* connettore;

	if(strcmp(operation.first_child().value(), "No connector"))
		connettore = "\n";
	else
		connettore = operation.first_child().value();

	std::cout << "Token : " << variable.first_child().value() << " is " << set.first_child().value() << connettore;
}

bool XMLFPParser::parseFuzzyObject(const xml_node& object_root,
		MamdaniFuzzyObject* object) {


	//search for linguistic variable for the root object.
	for (xml_node lang_var_root = object_root.child(LINGUISTIC_VARIABLE_TAG) ; lang_var_root ; lang_var_root = lang_var_root.next_sibling(LINGUISTIC_VARIABLE_TAG)){
		parseLinguisticVariable(lang_var_root, object_root);
	}
}



void XMLFPParser::correctPoint(float& X, const LinguisticVariable* variable) {
	if (X < variable->getMinRange())
		X = variable->getMinRange();
	if (X > variable->getMaxRange())
		X = variable->getMaxRange();
}

void XMLFPParser::uniformTokenName(std::string& tokenName) {

	size_t find = tokenName.find_first_of("_");
	if(find != string::npos)
		tokenName.erase(0, find+1); //erase all the inappropriate char
}

