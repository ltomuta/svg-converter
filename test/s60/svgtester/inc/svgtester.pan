/*
 ============================================================================
 Name		: svgtester.pan
 Author	  : 
 Copyright   : Your copyright notice
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __SVGTESTER_PAN__
#define __SVGTESTER_PAN__

/** svgtester application panic codes */
enum TsvgtesterPanics
	{
	EsvgtesterUi = 1
	// add further panics here
	};

inline void Panic(TsvgtesterPanics aReason)
	{
	_LIT(applicationName, "svgtester");
	User::Panic(applicationName, aReason);
	}

#endif // __SVGTESTER_PAN__
