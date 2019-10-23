#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) ;
	void start (int nbthread);
	void submit (Job * job) ;
	void stop() ;
	~Pool() ;

	//void poolWorker(Queue<Job> *q);

	// Gestion du travail des threads
	void threadWork();
};

}
