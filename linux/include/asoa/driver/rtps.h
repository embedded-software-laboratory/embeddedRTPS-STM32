#ifndef RTPS_H
#define RTPS_H

/** @addtogroup drivers
  * @{
  */

/** @defgroup rtps RTPS drivers */
/** @addtogroup rtps
  * @brief Driver layer for interaction with the operating system.
  * @{
  */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef void (*rtps_subscriber_cb_t)(const uint8_t* msg, const uint32_t len, void* arg);

/*!
* \struct rtps_driver_t
* \brief Contains the rtps_driver from FastRTPS.
*/
typedef struct rtps_driver_t{
    void* ptr_;
} rtps_driver_t;

/*!
* \struct rtps_publisher_t
* \brief Contains the publisher from FastRTPS.
*/
typedef struct rtps_publisher_t{
    void* ptr_;
} rtps_publisher_t;

/*!
* \struct rtps_subscriber_t
* \brief Contains the rtps_subscriber from FastRTPS.
*/
typedef struct rtps_subscriber_t{
    void* ptr_;
} rtps_subscriber_t;

/*!
* \brief Creates a new rtps_publisher_t with the topic and data_type.
* \param[topic] Pointer to the topic.
* \param[data_type_name] Pointer to the data_type.
*/
struct rtps_driver_t* rtps_init();
 
/*!
* \brief Creates a new rtps_publisher_t with the topic and data_type.
* \param[topic] Pointer to the topic.
* \param[data_type_name] Pointer to the data_type.
* \return rtps_publisher_t* Pointer to the new publisher.
*/
struct rtps_publisher_t* rtps_create_publisher(const char* topic,const char* data_type_name);

/*!
* \brief Creates a new rtps_subscriber_t for the topic, data_type and callback.
* \param[topic] Pointer to the topic.
* \param[data_type_name] Pointer to the data_type.
* \param[data] Pointer to instance as only static function can be used as a direct callback.
* \param[cb] Static callback function.
* \return rtps_subscriber_t* Pointer to the new subscriber.
*/
extern struct rtps_subscriber_t* rtps_create_subscriber(const char* topic, const char* data_type_name, void* data, rtps_subscriber_cb_t cb);

/*!
* \brief Publishes a message using the publisher.
* \param[publisher] Pointer to the publisher.
* \param[msg_len] Length of the message.
* \param[msg] Pointer to the data.
*/
extern void rtps_publish(struct rtps_publisher_t* publisher, uint8_t* msg, uint32_t msg_len);

/*!
* \brief Destroys a subscriber.
* \param[subscriber] Subscriber to destroy.
* \note unimplemented function
*/
extern bool rtps_destroy_subscriber(struct rtps_publisher_t subscriber);

/*!
* \brief Destroys a publisher.
* \param[subscriber] Publisher to destroy.
* \note unimplemented function
*/
extern bool rtps_destroy_publisher(struct rtps_publisher_t subscriber);

/*!
* \brief Returns if the publisher is still alive.
* \param[subscriber] Publisher to check.
* \return bool Returns true if publisher is still alive.
* \note unimplemented function
*/
extern bool rtps_get_publisher_stat(struct rtps_publisher_t* publisher); 

/*!
* \note unimplemented function
*/
extern bool rtps_finalize_init();

#ifdef __cplusplus
}
#endif

#endif


//@}
//@}
//@}
