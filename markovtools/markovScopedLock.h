/*
 *      Author: Arvind de Menezes Pereira
 */
#ifndef SCOPEDLOCK_H_
#define SCOPEDLOCK_H_

#ifndef _WINDOWS_ // Only applicable in OS-X and Linux

#include <cstdlib>
#include <pthread.h>

namespace MarkovTools {

/** \section ScopedMutexGuard provides a means of
 * locking resources in a consistent way which minimizes
 * deadlocks from taking place by automatically removing these deadlocks when
 * this ScopedMutexGuard goes out of scope.
 *
 * Usage:
 * pthread_mutex_t mutex;
 * pthread_mutex_init( &mutex, NULL );
 * foo( ) {
 *	  ScopedMutexGuard( mutex );
 *	  ++counter; // or whatever needs to be atomic.
 *	  // The mutex will be automatically released when going out of scope.
 * }
 *
 * or:
 * class Counter {
 *  Counter() {
 *   pthread_mutex_t mutex;
 *   pthread_mutex_init( &mutex, NULL );
 *   count = 0;
 *   }
 *
 *   int increment() {
 *   	ScopedMutexGuard( mutex );
 *		return ++count;
 *   }
 *
 * };
 */
class MarkovScopedMutexGuard {
	pthread_mutex_t *mutexLock;

public:
	MarkovScopedMutexGuard( pthread_mutex_t& lock ) : mutexLock(&lock) {
		pthread_mutex_lock( mutexLock );
	}

	~MarkovScopedMutexGuard() {
		pthread_mutex_unlock( mutexLock );
	}
};

}


#endif

#endif /* SCOPEDLOCK_H_ */
