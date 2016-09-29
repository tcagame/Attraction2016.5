#pragma once
#include "Task.h"
#include "Network.h"
#include "smart_ptr.h"
#include <string>

PTR( Processor );

class Processor : public Task {
public:
	static ProcessorPtr getTask( );
	static std::string getTag( ){ return "PROCESSOR"; }
public:
	Processor( );
	virtual ~Processor( );
public:
	void update( );
	void setInputDevice( );
private:
	CLIENTDATA _data;
};

