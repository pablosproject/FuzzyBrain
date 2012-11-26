/*
 * FuzzyLogger.cpp
 *
 *  Created on: Oct 11, 2012
 *      Author: igloo
 */

#include "FuzzyLogger.h"

using namespace log4cplus;

FuzzyLogger* FuzzyLogger::singleton_logger = NULL;

FuzzyLogger::FuzzyLogger(){

	this->internalLogger = Logger::getInstance(LOG4CPLUS_STRING_TO_TSTRING("Log"));
	PropertyConfigurator::doConfigure(LOG4CPLUS_STRING_TO_TSTRING("/Users/igloo/Documents/workspace/FuzzyTrainer/logger_configuration.config"));


}

 FuzzyLogger* FuzzyLogger::getSingletonLogger() {

	  if (!singleton_logger){

		  	 singleton_logger = new FuzzyLogger();
		}

	  return singleton_logger;

}

Logger& FuzzyLogger::getLogger()  {

  	return this->internalLogger;
}

Logger& FuzzyLogger::getActualLogger()  {

	return getSingletonLogger()->getLogger();
}
