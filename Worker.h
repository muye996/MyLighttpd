/******************************
 * File    Name   : Worker.h
 * Created Time   : 2018/6/10
******************************/

#ifndef _WORKER_H_
#define _WORKER_H_

#include <string>
#include <map>

#include "event2/event.h"
#include "event2/util.h"

class Master;

class Worker
{
public:
	Worker();
	~Worker();
	void Run();
	static void WorkerExitSignal(evutil_socket_t signo,
								short event,void *arg);
public:
	Master* 		   _master;
	struct event_base* _w_base;
	struct event* 	   _w_exit_event;
										
	std::string		   _s_inbuf;
	std::string		   _s_intmp;
	std::string 	   _s_outbuf;
};

#endif //WORKER_H_
