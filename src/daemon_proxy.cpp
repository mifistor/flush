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


#include <algorithm>
#include <deque>
#include <functional>
#include <string>
#include <vector>

#include <mlib/gtk/main.hpp>
#include <mlib/libtorrent.hpp>

#include "common.hpp"
#include "daemon.hpp"
#include "daemon_proxy.hpp"
#include "daemon_types.hpp"
#include "gui_lib.hpp"



Daemon_proxy::Daemon_proxy(const std::string& daemon_config_path)
:
	daemon(new Daemon(daemon_config_path))
{
	// Обработчик сигнала на приход сообщения от демона (libtorrent)
	this->signals_holder.push(this->daemon->messages_signal.connect(
		sigc::mem_fun(this->daemon_message_signal, &M_TYPEOF(this->daemon_message_signal)::emit)));

	// Обработчик сигнала на приход notify-сообщения от демона
	this->signals_holder.push(this->daemon->notify_message_signal.connect(
		sigc::mem_fun(this->notify_message_signal, &M_TYPEOF(this->notify_message_signal)::emit)));
}



Daemon_proxy::~Daemon_proxy(void)
{
	delete this->daemon;
}



void Daemon_proxy::add_torrent(const std::string& torrent_uri, const New_torrent_settings& torrent_settings)
{
	this->daemon->add_torrent(torrent_uri, torrent_settings);
}



Speed Daemon_proxy::get_rate_limit(Traffic_type traffic_type) const
{
	return this->daemon->get_rate_limit(traffic_type);
}



Session_status Daemon_proxy::get_session_status(void) const
{
	return this->daemon->get_session_status();
}



Daemon_settings Daemon_proxy::get_settings(void) const
{
	return this->daemon->get_settings();
}



Torrent_details Daemon_proxy::get_torrent_details(const Torrent_id& torrent_id) const
{
	return this->daemon->get_torrent_details(torrent_id);
}



std::string Daemon_proxy::get_torrent_download_path(const Torrent_id& torrent_id) const
{
	return this->daemon->get_torrent_download_path(torrent_id);
}



Revision Daemon_proxy::get_torrent_files_info(const Torrent_id& torrent_id, std::vector<Torrent_file> *files, std::vector<Torrent_file_status>* statuses, Revision revision) const
{
	Revision new_revision = this->daemon->get_torrent_files_info(torrent_id, files, statuses, revision);

	// Проверяем полученные данные
	if(new_revision != revision)
	{
		for(size_t i = 0; i < files->size(); i++)
		{
			std::string& path = (*files)[i].path;

			// m::Exception
			path = m::lt::get_torrent_file_path(path);
		}
	}

	return new_revision;
}



void Daemon_proxy::get_torrent_peers_info(const Torrent_id& torrent_id, std::vector<Torrent_peer_info>& peers_info) const
{
	this->daemon->get_torrent_peers_info(torrent_id, peers_info);
}



bool Daemon_proxy::get_torrent_new_download_settings(const Torrent_id& torrent_id, Revision* revision, Download_settings* download_settings) const
{
	return this->daemon->get_torrent_new_download_settings(torrent_id, revision, download_settings);
}



bool Daemon_proxy::get_torrent_new_trackers(const Torrent_id& torrent_id, Revision* revision, std::vector<std::string>* trackers) const
{
	return this->daemon->get_torrent_new_trackers(torrent_id, revision, trackers);
}



void Daemon_proxy::get_torrents(std::vector<Torrent_info>& torrents_info)
{
	this->daemon->get_torrents_info(torrents_info);
}



void Daemon_proxy::interrupt_temporary_action(bool complete)
{
	this->daemon->interrupt_temporary_action(complete);
}



void Daemon_proxy::process_torrents(const std::vector<Torrent_id>& torrents_ids, Torrent_process_action action)
{
	this->daemon->process_torrents(torrents_ids, action);
}



void Daemon_proxy::process_torrents_temporary(Temporary_action action, Torrents_group group, Time time)
{
	this->daemon->process_torrents_temporary(action, group, time);
}



void Daemon_proxy::reset_statistics(void)
{
	this->daemon->reset_statistics();
}



void Daemon_proxy::set_copy_when_finished(const Torrent_id& torrent_id, bool copy, const std::string& to)
{
	this->daemon->set_copy_when_finished(torrent_id, copy, to);
}



void Daemon_proxy::set_files_download_status(const Torrent_id& torrent_id, const std::vector<int>& files_ids, bool download)
{
	this->daemon->set_files_download_status(torrent_id, files_ids, download);
}



#if 0
void Daemon_proxy::set_files_new_paths(const Torrent_id& torrent_id, const std::vector<Torrent_file>& files_new_paths)
{
	this->daemon->set_files_new_paths(torrent_id, files_new_paths);
}
#endif



void Daemon_proxy::set_files_priority(const Torrent_id& torrent_id, const std::vector<int>& files_ids, const Torrent_file_settings::Priority priority)
{
	this->daemon->set_files_priority(torrent_id, files_ids, priority);
}



void Daemon_proxy::set_rate_limit(Traffic_type traffic_type, Speed speed)
{
	this->daemon->set_rate_limit(traffic_type, speed);
}



void Daemon_proxy::set_settings(const Daemon_settings& settings)
{
	this->daemon->set_settings(settings);
}



void Daemon_proxy::set_sequential_download(const Torrent_id& torrent_id, bool value)
{
	this->daemon->set_sequential_download(torrent_id, value);
}



void Daemon_proxy::set_torrent_trackers(const Torrent_id& torrent_id, const std::vector<std::string>& trackers)
{
	this->daemon->set_torrent_trackers(torrent_id, trackers);
}



void Daemon_proxy::start(void)
{
	this->daemon->start();
}



void Daemon_proxy::start_torrents(const Torrents_group group)
{
	this->daemon->start_torrents(group);
}



void Daemon_proxy::stop(void)
{
	this->daemon->stop();
}



void Daemon_proxy::stop_torrents(const Torrents_group group)
{
	this->daemon->stop_torrents(group);
}

