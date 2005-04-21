#ifndef IRecoParticleFactory_h
#define IRecoParticleFactory_h 1

#include "lcio.h"
#include "EVENT/MCParticle.h"
#include "EVENT/ReconstructedParticle.h"


namespace marlin{


  /** Interface for a factory class that creates a ReconstructedParticle
   *  from an MCParticle 
   */ 
  
  class IRecoParticleFactory {
  
  public:
    
    /** Virtual d'tor.*/
    virtual ~IRecoParticleFactory() {} 

    /** The actual factory method that creates a new ReconstructedParticle
     *  for the given MCParticle. NULL if no ReconstructedParticle should be created
     *  due to detector acceptance.
     */ 
    virtual lcio::ReconstructedParticle* createReconstructedParticle( const lcio::MCParticle* mcp ) = 0 ;
    
  } ;
  

} // end namespace 
#endif



