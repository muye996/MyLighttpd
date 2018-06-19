/***************************
 * File Name    : Master.cpp
 * Created Time : 2018/6/10
***************************/

#include "Master.h"
#include "Worker.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>

Master::Master()
{
	_m_base = NULL;
	_m_exit_event = NULL;
	_m_chld_event = NULL;

	_nums_of_child = 4;  // 4个进程
}

Master::~Master()
{
	if (_m_base)
	{
		event_free(_m_exit_event);
		event_free(_m_chld_event);
		event_base_free(_m_base);
	}
	std::cout << "Master closed" << "\n";
} 

bool Master::StartMaster()
{
	std::cout << "Master started" << "\n";
	_worker._master = this;
	// 创建一定数量的worker
	while(_nums_of_child > 0)
	{
		switch(fork())
		{
			case -1:
			{
				return false;
			}
			case 0:
			{
				_worker.Run();
				return true;
			}
			default:
			{
				--_nums_of_child;
				break;
			}
		}
	}
	_m_base = event_base_new();
	_m_exit_event = evsignal_new(_m_base,SIGINT,
								Master::MasterExitSignal,_m_base);
	_m_chld_event = evsignal_new(_m_base,SIGCHLD,
								Master::MasterChldSignal,this);
	evsignal_add(_m_exit_event,NULL);
	evsignal_add(_m_chld_event,NULL);
	// 开始事件循环
	event_base_dispatch(_m_base);
	return true;
}   

void Master::MasterExitSignal(evutil_socket_t signo,short evrnt,
							void* arg)
{
	// 通知所有子进程，暂时不需要，因为不是守护进程
	// 所有子进程跟终端相连，都会收到SIGINT
	// kill(0,SIGINT);
	// 结束事件循环
	event_base_loopexit((struct event_base*)arg,NULL);
}

// 预防僵尸进程
void Master::MasterChldSignal(evutil_socket_t signo,short event,
							void* arg)
{
	Master* master = (Master*)arg;
	pid_t pid;
	int   stat;
	while((pid = waitpid(-1,&stat,WNOHANG)) > 0)
	{
		++(master->_nums_of_child);
		std::cout << "Child" << pid << "terminated" << "\n";
	}
}




