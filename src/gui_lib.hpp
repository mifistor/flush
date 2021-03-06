/**************************************************************************
*                                                                         *
*   Flush - GTK-based BitTorrent client                                   *
*   http://sourceforge.net/projects/flush                                 *
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


#ifndef HEADER_GUI_LIB
#define HEADER_GUI_LIB

	#include <glibmm/ustring.h>
#if !MLIB_ENABLE_LIBS_FORWARDS
	#include <gtkmm/widget.h>
	#include <gtkmm/window.h>
#endif

	#include <mlib/gtk/misc.hxx>

	#include "common.hpp"


/// Форматирует заголовок окна стандартным заранее определенным образом.
Glib::ustring				format_window_title(const Glib::ustring& title);

/// Возвращает окно, наиболее подходящее в качестве родительского окна для
/// диалога, отображение которого инициируется виджетом widget.
Gtk::Window&				get_dialog_proper_parent_window(Gtk::Widget& widget);

/// Аналог m::gtk::ok_cancel_dialog, но только не принимает параметр с
/// родительским окном, т. к. всегда использует в качестве него главное
/// окно приложения.
m::gtk::Dialog_response		ok_cancel_dialog(const std::string& title, const std::string& message);

#endif
