/*
 * Parser.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: igloo
 */

#include "XLFPParser.h"

using namespace pugi;

XMLFPParser::XMLFPParser() {}

bool XMLFPParser::Parse(const std::string& filePath) {

	const char *file;
	file = filePath.c_str();

	xml_parse_result result = document.load_file(file);

	xml_node application = document.child(APPLICATION_TAG);
	xml_node rules_root = application.child(RULES_TAG);

	//Cerco per le variabili linguistiche nei figli della root
	for (xml_node lang_var_root = application.child(LINGUISTIC_VARIABLE_TAG) ; lang_var_root ; lang_var_root = lang_var_root.next_sibling(LINGUISTIC_VARIABLE_TAG)){

		parseLinguisticVariable(&lang_var_root);
	}

	for (xml_node rule_root = rules_root.child(RULE_TAG) ; rule_root ; rule_root = rule_root.next_sibling(RULE_TAG)){

		parseRule(&rule_root);
	}

	//TODO:cerca per knowledge chip


}


void XMLFPParser::parseLinguisticVariable (const xml_node* node){

	//TODO: inserisci salvataggio dell'id della variabile linguistica

	std::cout << "Variabile linguistica: " << node->child(LINGUISTIC_VARIABLE_ID_TAG).first_child().value() << "\n";

	//TODO: gestisci il min e max della variabile linguistica
	xml_node fuzzy_sets = node->child(LINGUISTIC_VARIABLE_SETS_TAG);

	//Ciclo su tutte le definizioni di insiemi nella variabile linguistica
	for (xml_node fuzzy_set = fuzzy_sets.child(LINGUISTIC_VARIABLE_SET_TAG) ; fuzzy_set ; fuzzy_set = fuzzy_set.next_sibling(LINGUISTIC_VARIABLE_SET_TAG)){

		std::cout << "Fuzzy set :" << fuzzy_set.first_child().first_child().value() << "\n";
		//TODO: Gestione del nome del fuzzy set
		parseFuzzySet(&(fuzzy_set.child(LINGUISTIC_VARIABLE_SET_DEFINITION_TAG)));

	}

}

void XMLFPParser::parseFuzzySet (const xml_node* node){

	xml_node A = node->child(LINGUISTIC_VARIABLE_SET_POINT_A_TAG);
	xml_node B = node->child(LINGUISTIC_VARIABLE_SET_POINT_B_TAG);
	xml_node C = node->child(LINGUISTIC_VARIABLE_SET_POINT_C_TAG);
	xml_node D = node->child(LINGUISTIC_VARIABLE_SET_POINT_D_TAG);
	//TODO:Salva e rappresenta i valori della funzione di appartenenza

	std::cout <<"A:"<<A.first_child().value() << "B:"<<B.first_child().value() << "C:"<<C.first_child().value() << "D:"<<D.first_child().value()<<"\n";
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

XMLFPParser::~XMLFPParser() {}




