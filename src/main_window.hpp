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


#ifndef HEADER_MAIN_WINDOW
	#define HEADER_MAIN_WINDOW

	#include <queue>

	#include <gtkmm/window.h>

	#include <mlib/gtk/main.hpp>
	#include <mlib/gtk/toolbar.hpp>
	#include <mlib/gtk/window.hpp>

	#include "client_settings.hpp"
	#include "common.hpp"



	class Main_window: public m::gtk::Window
	{
		private:
			struct Gui;


		public:
			Main_window(const Main_window_settings& settings);
			~Main_window();


		private:
			Gui* gui;


		public:
			/// Добавляет сообщение демона в виджет, занимащийся отображанием
			/// этих сообщений.
			void		add_daemon_message(const Daemon_message& message) const;

			/// Выполняет все необходимые действия по подготовке главного окна
			/// приложения к завершению работы.
			void		close(void);

			/// Производит все необходимые в зависимости от настроек действия
			/// по открытию торрента.
			void		open_torrent(const std::string& torrent_uri, const std::string& torrent_encoding = MLIB_UTF_CHARSET_NAME);

			/// Cохраняет текущие настройки клиента.
			void		save_settings(void);

			/// Инициирует обновление GUI.
			void		update_gui(bool force = true);

		private:
			/// Изменяет стиль панели инструментов.
			void		change_toolbar_style(m::gtk::toolbar::Style style);

			/// Скрывает окно.
			void		hide(void);

			/// Определяет, отображается ли окно в элементах оконного
			/// менеджера (в панели задач и меню, вызываемом по Alt+Tab).
			bool		is_visible_in_wm(void);

		#if HAVE_APP_INDICATOR
			/// Вызывается при изменении статуса соединения с AppIndicator'ом.
			static void	on_appindicator_connection_changed(gpointer appindicator, gboolean connected, gpointer user_data);
		#endif

			/// При выборе пункта меню "Изменить максимальную скорость скачивания/отдачи".
			void		on_change_rate_limit_callback(Traffic_type traffic_type);

			/// Обработчик сигнала на закрытие окна.
			bool		on_close_callback(GdkEventAny* event);

			/// Обработчик сигнала на создание торрент файла.
			void		on_create_callback(void);

			/// Обработчик сигнала на обновление GUI.
			bool		on_gui_update_timeout(void);

			/// Прерывает выполнение текущего "временного действия".
			/// @param complete - если false, то действие отменяется, если true
			/// - выполняется досрочно.
			void		on_interrupt_temporary_action_cb(bool complete);

			/// Обработчик сигнала на открытие торрент файла.
			void		on_open_callback(void);

			/// Обработчик сигнала на открытие magnet-ссылки.
			void		on_open_magnet_callback(void);

			/// При выборе пункта меню "Приостановить все торренты".
			void		on_pause_torrents_callback(Torrents_group group);

			/// При выборе пункта меню "Возобновить все торренты".
			void		on_resume_torrents_callback(Torrents_group group);

			/// Обработчик сигнала на автоматическое сохранение настроек.
			bool		on_save_settings_timeout(void);

			/// Обработчик сигнала на отображение About диалога.
			void		on_show_about_dialog_callback(void);

			/// Обработчик сигнала на открытие окна настроек.
			void		on_show_settings_window_callback(void);

			/// Обработчик сигнала на отображение статистики.
			void		on_show_statistics_callback(void);

			/// Обработчик сигнала на переключение флажка меню "Отображать
			/// панель инструментов".
			void		on_show_toolbar_toggled_callback(void);

			/// Обработчик сигнала на временное возобновление/приостановку
			/// торрентов.
			void		on_temporary_process_torrents_cb(const std::pair<Temporary_action,Torrents_group>& data);

			/// Обработчик сигнала на изменение списка действий, которые можно
			/// выполнить над торрентом(ами), выделенным(ми) в данный момент.
			void		on_torrent_process_actions_changed_callback(Torrent_process_actions actions);

			/// Обработчик нажатия левой кнопки мыши по значку в трее.
			void		on_tray_activated(void);

			/// Обработчик нажатия правой кнопки мыши по значку в трее.
			void		on_tray_popup_menu(int button, int activate_time);

			/// Обработчик сигнала на изменение состояния окна.
			bool		on_window_state_changed_callback(const GdkEventWindowState* state);

			/// Задает интервал обновления GUI.
			void		set_gui_update_interval(int interval);

			/// Отображает окно.
			void		show(void);

			/// Отображает окно и все дочерние виджеты.
			void		show_all(void);

			/// Отображает или скрывает иконку из трея.
			void		show_tray_icon(bool show);

			/// Включает/отключает отображение окна в элементах оконного
			/// менеджера (в панели задач и меню, вызываемом по Alt+Tab).
			void		set_visible_in_wm(bool visible = true);
	};

#endif

