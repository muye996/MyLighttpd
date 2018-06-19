/******************************
 * File Name    : Master.h
 * Created Time : 2018/6/10
******************************/

#ifndef _SERVER_H_
#define _SERVER_H_

#include "Worker.h"

#include <string>

#include "event2/event.h"
#include "event2/util.h"

class Master
{
public:
	Master();
	~Master();
public:
	bool StartMaster();
	// SIGINT 回调函数
	static void MasterExitSignal(evutil_socket_t signo,
								short event,void* arg);
	// SIGCHLD 回调函数
	static void MasterChldSignal(evutil_socket_t signo,
								short event,void* arg);
public:
	Worker _worker;

	struct event_base *_m_base;
	struct event	  *_m_exit_event;
	struct event	  *_m_chld_event;

	int				  _nums_of_child;
};

#endif
