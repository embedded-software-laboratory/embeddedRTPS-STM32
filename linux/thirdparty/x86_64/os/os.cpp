#include <asoa/driver/os.h>
#include <thread>
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include <functional>

class Task;

static asoa::OS::thread::thread_id_t thread_id_counter_ = 0;

const asoa::OS::thread::thread_t *asoa::OS::thread::create(func_t func, void *arg, const char *name, uint16_t stack_size)
{
    asoa::OS::thread::thread_t *asoa_wrapper = (asoa::OS::thread::thread_t *)malloc(sizeof(asoa::OS::thread::thread_t));

    std::thread *std_thread = new std::thread(func, arg);
    asoa_wrapper->ptr = (void *)std_thread;
    asoa_wrapper->id = 0;

    return asoa_wrapper;
}

void asoa::OS::log::error(asoa_error_t error, const char* file, int line)
{
    switch (error)
    {
    case ASOA_ERROR_BUFFER_OVERFLOW:
    case ASOA_ERROR_MALLOC_FAILURE:
    case ASOA_ERROR_SERIALIZE_FAILURE:
    case ASOA_ERROR_RTPS_FAILURE:
    default:
        std::cout << "[" << file << ":" << line << "] ERROR CODE: " << error << std::endl;
        std::exit(-1);
    }
}

void asoa::OS::thread::detach(const thread_t *thread)
{
    std::thread *std_thread = (std::thread *)(thread->ptr);
    std_thread->detach();
}

void asoa::OS::thread::yield()
{
    std::this_thread::yield();
}

asoa::OS::mutex::mutex_t *asoa::OS::mutex::create()
{

    asoa::OS::mutex::mutex_t *mutex = (asoa::OS::mutex::mutex_t *)malloc(sizeof(asoa::OS::mutex::mutex_t));
    std::mutex *std_mutex = new std::mutex();
    mutex->ptr = std_mutex;
    return mutex;
}

void asoa::OS::mutex::lock(asoa::OS::mutex::mutex_t *mutex)
{
    std::mutex *std_mutex = ((std::mutex *)mutex->ptr);
    std_mutex->lock();
}

void asoa::OS::mutex::unlock(asoa::OS::mutex::mutex_t *mutex)
{
    std::mutex *std_mutex = ((std::mutex *)mutex->ptr);
    std_mutex->unlock();
}

asoa::OS::time::time_t asoa::OS::time::getTime(void)
{
    struct timespec tspec;
    asoa::OS::time::time_t ts;

    clock_gettime(CLOCK_REALTIME, &tspec);

    ts.tv_sec = tspec.tv_sec;
    ts.tv_nsec = tspec.tv_nsec;

    return ts;
}

asoa::OS::time::time_t asoa::OS::time::zeroTime(void)
{
    return {0, 0};
}

bool asoa::OS::time::isTimeZero(asoa::OS::time::time_t t)
{
    return ((t.tv_sec == 0) && (t.tv_nsec == 0));
}

double asoa::OS::time::getTimeDiffNs(asoa::OS::time::time_t start, asoa::OS::time::time_t end)
{

    double difference;

    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        difference = (end.tv_sec - start.tv_sec - 1) * 1000000.0;
        difference += (1000000000.0 + end.tv_nsec - start.tv_nsec) / 1000.0;
    }
    else
    {
        difference = (end.tv_sec - start.tv_sec) * 1000000.0;
        difference += (end.tv_nsec - start.tv_nsec) / 1000.0;
    }

    return difference;
}

double asoa::OS::time::getTimeDiffNs(asoa::OS::time::time_t start, uint64_t end_tv_sec, int64_t end_tv_nsec)
{
    asoa::OS::time::time_t end;
    end.tv_nsec = end_tv_nsec;
    end.tv_sec = end_tv_sec;

    return getTimeDiffNs(start, end);
}

double asoa::OS::time::getTimeDiffNs(uint64_t end_tv_sec, int64_t end_tv_nsec, asoa::OS::time::time_t end)
{
    asoa::OS::time::time_t start;
    start.tv_nsec = end_tv_nsec;
    start.tv_sec = end_tv_sec;

    return getTimeDiffNs(start, end);
}

void asoa::OS::time::usleep(unsigned long useconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(useconds));
}