#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>
#include <boost/interprocess/ipc/message_queue.hpp>
#define _POSIX_C_SOURCE 199309L

#include <time.h>
#include "helper.h"
#define BILLION 1000000000L

using namespace std;
using namespace boost::interprocess;
int main()
{
    cout << "Hello World!" << endl;
    int pid = fork();
    if (pid == 0) {

        //while (1) {
            sleep(2);
            size_t recvd_size;
            unsigned int priority;
            struct timespec start, end;
            uint64_t diff;
            message_queue mq (open_only, "mq");
            clock_gettime(CLOCK_MONOTONIC, &start);
            for (int i=0;i<20;i++) {
                int buffer;

                mq.receive((void*) &buffer, sizeof(int), recvd_size, priority);

                std::cout << buffer << " " << recvd_size << " " << priority;
                cout << "child is running" << endl;
            }
            clock_gettime(CLOCK_MONOTONIC, &end);
            diff = time_elapsed_misec(start, end);
            double time_in_ns_sec = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
            std::cout << "Time taken to send ns sec \n" << time_in_ns_sec << endl;
        //}
        exit(0);
        //return 0;
    } else {
        try {
            message_queue mq (create_only, "mq", 20, sizeof(int));
            for (int i=0; i<20;i++) {
                mq.send(&i, sizeof(int), 0);
            }
        } catch (interprocess_exception& e) {
            std::cout << e.what() << std::endl;
        }
        int cpid = wait(nullptr);
        cout << cpid << endl;
    }
    return 0;
}
