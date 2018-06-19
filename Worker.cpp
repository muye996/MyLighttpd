/*******************************
 * File    Name  :  Worker.cpp
 * Created Time  :  2018/6/10
*******************************/

#include "Worker.h"
#include "Master.h"

#include <stdlib.h>
#include <iostream>

Worker::Worker()
{
	_master        = NULL;
	_w_base       = NULL;
	_w_exit_event = NULL;
}

Worker::~Worker()
{
	if (_w_exit_event)
		event_free(_w_exit_event);
	if (_w_base)
		event_base_free(_w_base);
	
	std::cout << "Worker closed" << "\n";
}

void Worker::Run()
{
	_w_base = event_base_new();
	_w_exit_event = evsignal_new(_w_base,2,
								Worker::WorkerExitSignal,_w_base);
	evsignal_add(_w_exit_event,NULL);
					
	event_base_dispatch(_w_base);
	
	return;
}

void Worker::WorkerExitSignal(evutil_socket_t signo,short event,
							void* arg)
{
		event_base_loopexit((struct event_base*)arg,NULL);
}
