/*
 * FuzzyLogger.h
 *
 *  Created on: Oct 11, 2012
 *      Author: igloo
 *
 *      Singleton class used for logging purpose.
 */

#ifndef FUZZYLOGGER_H_
#define FUZZYLOGGER_H_

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <iomanip>


using namespace log4cplus;

class FuzzyLogger {

private:

	FuzzyLogger();

	static FuzzyLogger* singleton_logger;	//Unique instance of my object

	Logger internalLogger;							//Logger that come from log4cplus


public:

	static FuzzyLogger*  getSingletonLogger();
	Logger& getLogger() ;
	static Logger& getActualLogger();
};



#endif /* FUZZYLOGGER_H_ */
