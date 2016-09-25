#include "Viewer.h"
#include "Status.h"
#include "Application.h"

ViewerPtr Viewer::getTask( ) {
	ApplicationPtr app = Application::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( app->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}


Viewer::~Viewer( ) {
}

void Viewer::update( ) {
	drawStatus( );
}

void Viewer::drawStatus( ) {
	StatusPtr status = Status::getTask( );
	status->draw( );
}