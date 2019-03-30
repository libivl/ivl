/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_SYSTEM_TIMER_HPP
#define IVL_SYSTEM_TIMER_HPP

//-----------------------------------------------------------------------------

#ifdef _WIN32  // Windows implementation

#ifndef IVL_MINMAX_MACROS
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif

#include <windows.h>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

class timer
{
	LARGE_INTEGER time_start;
	LARGE_INTEGER time_stop;
	LONGLONG time_lap;
	double total;

protected:
	inline void start() {
		QueryPerformanceCounter(&time_start);
	};

	inline void stop() {
		QueryPerformanceCounter(&time_stop);
	};

	inline void mark() {
		time_lap = time_stop.QuadPart  - time_start.QuadPart ;
	};

	// duration in milliseconds
	inline double duration()
	{
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		double d = (double)(time_stop.QuadPart - time_start.QuadPart) * 1000 /
		           (double)freq.QuadPart;
		return d;
	}

	inline double comp_time() { return (double) time_lap;}

//-----------------------------------------------------------------------------

public:

	timer() : total(0) { }

	inline void tic() { start(); }

	inline double tac()
	{
		stop();
		double d = duration();
		total += d;
		return d;
	}

	double toc()
	{
		tac();
		double t = total;
		total = 0;
		return t;
	}

	inline double toctic() { double t = toc(); tic(); return t; }
};

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#else  // *NIX implementation

//-----------------------------------------------------------------------------

#include <sys/time.h>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

class timer
{
	struct timeval time_start;
	struct timeval time_stop;
	double total;

public:

	timer() : total(0) { }

	void tic() { gettimeofday(&time_start, 0); }

	double tac()
	{
		struct timeval res;
		gettimeofday(&time_stop, 0);
		timersub(&time_stop, &time_start, &res);
		double duration = 1000.0 * res.tv_sec + 0.001 * res.tv_usec;
		total += duration;
		return duration;
	}

	double toc()
	{
		tac();
		double t = total;
		total = 0;
		return t;
	}

	double toctic(void) { double t = toc(); tic(); return t; }
};

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // implementation

//-----------------------------------------------------------------------------

#endif // IVL_SYSTEM_TIMER_HPP
