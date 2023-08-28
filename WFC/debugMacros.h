#ifndef DEBUGMACROS_H 
#define DEBUGMACROS_H 

namespace wfc {

#define DEBUG true

#if DEBUG

// timing
#define TIMER_PROPAGATE false
#define TIMER_RUN true

// indexing functions
#define INDEX_SAFEGUARD false

// logging
#define FULL_TILE_LOG true
#define FULL_TILE_T_LOG false

#else
// sets everything to false
#define TIMER_PROPAGATE false
#define TIMER_RUN false
#define INDEX_SAFEGUARD false
#define FULL_TILE_LOG false
#define FULL_TILE_T_LOG false

#endif


}; // namespace wfc

#endif