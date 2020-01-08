#ifndef OS_H
#define OS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>


namespace asoa{

namespace OS {

	/** @defgroup drivers Drivers */
	/** @addtogroup drivers
	  * @brief RTPS Driver and OS Driver.
	  * @{
	  */


	/** @defgroup os OS drivers */
	/** @addtogroup os
	  * @brief Driver for interaction with the operating system.
	  * The interaction with the operating system depends on the
	  * platform ASOA is running on.
	  * @{
	  */

	namespace thread {

		typedef uint32_t thread_id_t;

		
		/*!
		* \struct thread_t
		* \brief Contains a ASOA thread.
		* Contains the thread_id and a pointer to the std::thread.
		*/
		typedef struct thread_t{
			void* ptr;
			thread_id_t id;
		} thread_t;

		// Unfortunately can't use std::function with FreeRTOS C interface
		typedef void (*func_t)( void * );

		#define ASOA_DEFAULT_THREAD_STACK_SIZE 0

		/*!
		* \brief Creates a new thread.
		* Uses std::thread to create a new thread.
		* \param[func] Function to execute in the new thread.
		* \param[arg] Arguments for the function in the new thread.
		* \param[name] Name of the new thread.
		* \param[stack_size] Size of the stack for the new thread (not used on x86).
		* \return thread* Returns the newly created thread.
		*/
		const thread_t* create(func_t func, void* arg = nullptr, const char* name = nullptr, uint16_t stack_size = ASOA_DEFAULT_THREAD_STACK_SIZE);

		/*!
		* \note Not used and not implemented on x86.
		*/
		void schedule(const thread_t* thread);

		/*!
		* \brief Detaches the thread from the current thread.
		* \param[thread] The thread to detach.
		*/
		void detach(const thread_t* thread);

		/*!
		* \brief The currently active thread yields its time.
		*/
		void yield();

		/*!
		* \brief Returns the current thread.
		* \return thread_t* Returns the current thread.
		*/
		const thread_t* current();

		/*!
		* \brief Returns the current thread id.
		* \return thread_id_t Returns the current threadid.
		*/
		const thread_id_t getThreadID(thread_t* thread);

	}

	namespace mutex {
		
		/*!
		* \struct mutex_t
		* \brief Contains the ASOA mutex.
		* \note On x86 this is the std::mutex implementation.
		*/
		typedef struct mutex_t{
		  void* ptr;
		} mutex_t;
		
		
		/*!
		* \brief Creates a new ASOA mutex.
		* \return mutex_t* Pointer to the new mutex.
		*/
		mutex_t* create();

		/*!
		* \brief Locks a ASOA mutex.
		* \param[mutex_t*] Pointer to the mutex.
		*/
		void lock(mutex_t* mutex);

		/*!
		* \brief Unlocks a ASOA mutex.
		* \param[mutex_t*] Pointer to the mutex.
		*/
		void unlock(mutex_t* mutex);

	}

	namespace log {

		/** \brief ASOA errors. */
		typedef enum{
			ASOA_ERROR_BUFFER_OVERFLOW,
			ASOA_ERROR_MALLOC_FAILURE,
			ASOA_ERROR_SERIALIZE_FAILURE,
			ASOA_ERROR_RTPS_FAILURE,
			ASOA_UNIMPLEMENTED_FUNCTION
		} asoa_error_t ;

		/*!
		* \brief Stops the exection of the programm and prints the line and file where the error occured. 
		* The requirement creates a unique accessHandle for each task that access it.
		* \param[error] Type of error that occured.
		* \param[file] File where the error occured.
		* \param[line] Line in which the error occured.
		*/
		void error(asoa_error_t error, const char* file, int line);
	}

	#define ASOA_ASSERT(cond, reason) if(!(cond)){ asoa::OS::log::error(reason, __FILE__, __LINE__); }

	namespace time {

		
		/*!
		* \struct time_t
		* \brief Contains the ASOA timestamps.
		* The timestamp consists of a second value and a signed nanoseconds
		* value.
		*/
		typedef struct {
			unsigned long tv_sec;
			long tv_nsec;
		} time_t;

		/*!
		* \brief Returns the current time.
		* \return time_t Returns a timestamp struct with the current time.
		*/
		time_t getTime(void);

		/*!
		* \brief Returns the zero timestamp.
		* \return time_t Returns a timestamp struct with all values set to zero.
		*/
		time_t zeroTime(void);

		/*!
		* \brief Checks wether time is zeroTime.
		* \param[t] The timestamp to check.
		* \return bool Returns wether time is zeroTime.
		*/
		bool isTimeZero(time_t t);

		/*!
		* \brief Computes time difference between two timestamps.
		* \param[start] The start timestamp.
		* \param[end] The end timestamp.
		* \return double Returns the time difference in nanoseconds.
		*/
		double getTimeDiffNs(time_t start, time_t end);

		/*!
		* \brief Computes time difference between two timestamps.
		* \param[end_tv_sec] The end seconds (first timestamp component).
		* \param[end_tv_nsec] The end nanoseconds (second timestamp component).
		* \param[start] The start timestamp.
		* \return double Returns the time difference in nanoseconds.
		*/
		double getTimeDiffNs(time_t start, uint64_t end_tv_sec, int64_t end_tv_nsec);

		/*!
		* \brief Computes time difference between two timestamps.
		* \param[end_tv_sec] The start seconds (first timestamp component).
		* \param[end_tv_nsec] The start nanoseconds (second timestamp component).
		* \param[end] The end timestamp.
		* \return double Returns the time difference in nanoseconds.
		*/
		double getTimeDiffNs(uint64_t end_tv_sec, int64_t end_tv_nsec, time_t end);

		/*!
		* \brief Sleeps for the number of mikroseconds.
		* \param[useconds] The time to sleep.
		*/
		void usleep(unsigned long useconds);
	}

}

};

#endif // OS_H

//@}
//@}

