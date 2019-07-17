#ifndef TIME_HPP
#define TIME_HPP

class Time
{
public:

	static const unsigned int secondToMilis(const unsigned int seconds) { return seconds * 1000; }
	static const unsigned int minutesToMilis(const unsigned int minutes) { return minutes * 60 * 1000; }
	static const unsigned int hoursToMilis(const unsigned int hours) { return hours * 60 * 60 * 1000; }

	static const unsigned int milisToHours(const unsigned int milis) { return milis / (60 * 60 * 1000); }
	static const unsigned int milisToMinutes(const unsigned int milis) { return milis / (60 * 1000); }
	static const unsigned int milisToSeconds(const unsigned int milis) { return milis / 1000; }
	
};

#endif