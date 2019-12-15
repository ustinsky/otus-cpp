#include <chrono>
#include <string>
#include <iostream>

class SimpleTimer {
public:
	SimpleTimer(std::string _msg, bool _visible = true);
	~SimpleTimer();

	void start(std::string _msg);
	int64_t stop();

private:
	std::chrono::steady_clock::time_point begin, end;
	std::string msg;
	bool visible;
	bool stopped;
	
};