#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

atomic_flag spinlock = ATOMIC_FLAG_INIT;

void *threadfunc(void *arg) { 
	_Atomic unsigned **x = (_Atomic unsigned **) arg; 
	
	for (int i = 0; i != 10000000; i++) { 

		spin_lock(&spinlock); 
		for (int j = 0; j < 10; j++) {
			atomic_fetch_add(x[j], 1); 
		} 
		spin_unlock(&spinlock);
	} 
}

void spin_lock(atomic_flag* l) { 
	while (atomic_flag_test_and_set(l)) { } 
} 

void spin_unlock(atomic_flag* l) { 
	atomic_flag_clear(l);           // “*l = 0;” 
}


int main() { 
	pthread_t th[4];
	_Atomic unsigned n[10]; 
	_Atomic unsigned *pn[10];

	for (int i = 0; i < 10; i++) { 
		n[i] = ATOMIC_VAR_INIT(0); 
		pn[i] = &(n[i]); 
	}
	
	for (int i = 0; i < 4; i++) { 
		pthread_create(&th[i], NULL, threadfunc, (void *) pn); 
	} 
	
	for (int i = 0; i != 4; i++) { 
		pthread_join(th[i], NULL); 
	}
	
	for (int i = 0; i < 10; i++) { 
		printf("%u\n", n[i]); 
	}
}
