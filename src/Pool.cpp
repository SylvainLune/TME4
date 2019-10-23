/*
 * Pool.cpp
 *
 *  Created on: 23 oct. 2019
 *      Author: 3105491
 */

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>
#include "Pool.h"

namespace pr {

Pool::Pool(int qsize) : queue(qsize) {
	// threads = nullptr;
}

void poolWorker(Queue<Job> *q) {
	while (true) {
		Job *j = q->pop();
		if (j == nullptr) {
			return;
		}
		j->run();
		delete j;
	}
}

void Pool::start(int nbthread) { //  : threads(nbthread)
	// Affectation des fonctions aux threads
	threads.reserve(nbthread);
	for (int iThread = 0; iThread < nbthread; iThread++) {
		threads.emplace_back(poolWorker, &queue);
	}

}



void Pool::stop() {
	queue.setBlocking(false);
	for (auto &t : threads) {
		t.join();
	}
	threads.clear();
}

void Pool::submit(Job *job) {
	queue.push(job);
}

void Pool::threadWork() {

}

Pool::~Pool() {
	stop();
}

}

