#include "marlin/EventSelector.h"

#include <iostream>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"


using namespace lcio ;
using namespace marlin ;


MarlinEventSelector aMarlinEventSelector ;


MarlinEventSelector::MarlinEventSelector() : Processor("EventSelector") {
  
  // modify processor description
  _description = "EventSelector returns true if given event was specified in EventList" ;
  
  IntVec evtsExample ;
  // evtsExample.push_back( 42 );
  // evtsExample.push_back( 1024 );
  
  
  registerProcessorParameter( "EventList" , 
			      "event list - pairs of Eventnumber RunNumber"  ,
			      _evtList ,
			      evtsExample ) ;
  _nEvt = -1;
  _nRun = -1;  
}


void MarlinEventSelector::init() {
  
  // usually a good idea to
  printParameters() ;
  
  _nRun = 0 ;
  _nEvt = 0 ;
  

  unsigned nEvts = _evtList.size() ;

  for( unsigned i=0 ; i < nEvts ; i+=2 ) {
    
    _evtSet.insert( std::make_pair( _evtList[i] , _evtList[ i+1 ] ) ) ;
  }
}

void MarlinEventSelector::processRunHeader( LCRunHeader* ) {
  
  _nRun++ ;
} 


void MarlinEventSelector::modifyEvent( LCEvent *evt ) {
  processEvent( evt );
}

void MarlinEventSelector::processEvent( LCEvent * evt ) {

  // if no events specifiec - always return true
  if( _evtList.size() == 0 ) {
    setReturnValue( true ) ;
    return ;
  }

  SET::iterator it = _evtSet.find( std::make_pair( evt->getEventNumber() , evt->getRunNumber() ) ) ;

  bool isInList = it != _evtSet.end() ; 
    

  //-- note: this will not be printed if compiled w/o MARLINDEBUG=1 !

  streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		       << "   in run:  " << evt->getRunNumber() 
		       << " - in event list : " << isInList 
		       << std::endl ;

  setReturnValue( isInList ) ;


  _nEvt ++ ;
}



void MarlinEventSelector::check( LCEvent *  ) { 
  // nothing to check here - could be used to fill checkplots in reconstruction processor
}


void MarlinEventSelector::end(){ 
  
//   std::cout << "MarlinEventSelector::end()  " << name() 
// 	    << " processed " << _nEvt << " events in " << _nRun << " runs "
// 	    << std::endl ;

}

