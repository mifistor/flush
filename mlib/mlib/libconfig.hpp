/**************************************************************************
*                                                                         *
*   MLib - library of some useful things for internal usage               *
*                                                                         *
*   Copyright (C) 2009-2010, Dmitry Konishchev                            *
*   http://konishchevdmitry.blogspot.com/                                 *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 3 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
**************************************************************************/


#ifndef HEADER_MLIB_LIBCONFIG
#define HEADER_MLIB_LIBCONFIG

#include <mlib/main.hpp>

#ifndef MLIB_ENABLE_LIBS_FORWARDS
	#include <libconfig.h++>
#endif

namespace m {


namespace libconfig {

	using namespace ::libconfig;

	// Т. к. libconfig писался без учета x86-64 систем -->
		const Setting::Type Size_type = ::libconfig::Setting::TypeInt64;
		const Setting::Type Speed_type = ::libconfig::Setting::TypeInt64;
		const Setting::Type Time_type = ::libconfig::Setting::TypeInt64;
		const Setting::Type Version_type = ::libconfig::Setting::TypeInt64;

		typedef long long	Size;
		typedef long long	Speed;
		typedef long long	Time;
		typedef long long	Version;
	// Т. к. libconfig писался без учета x86-64 систем <--

}


std::string		EE(const ::libconfig::FileIOException& error);
std::string		EE(const ::libconfig::ParseException& error);


namespace aliases
{
	using m::EE;
}

}


#endif

