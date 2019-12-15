#include "SimpleTimer.h"

SimpleTimer::SimpleTimer(std::string _msg, bool _visible): visible(_visible), stopped(false)  {
	start(_msg);
}

SimpleTimer::~SimpleTimer() {
	if(stopped != true) 
		stop();
}

void SimpleTimer::start(std::string _msg) {
	msg = _msg;
	begin = std::chrono::steady_clock::now();
	stopped = false;
}

int64_t SimpleTimer::stop() {
	end = std::chrono::steady_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	if (visible) {
		std::cout << msg << " duration: " << time 
				  << " microsecond " 	  << std::endl << std::endl;
	}
	stopped = true;
	return time;
}