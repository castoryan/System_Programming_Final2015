/********************************************************************************
 * File Name:	Storagemgr.h
 * Author: 	Qinrui Yan
 * Organizaion: KU_Leuven-GroupT
 * Date: 	2015-06-01
 * E-mail: 	castoryan1991@gmail.com
 * Description: header file of Storage manager in charge of SQL connection
 *******************************************************************************/
#ifndef _SENSOR_DB_H_
#define _SENSOR_DB_H_
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "db_config.h"

#ifndef TABLE_NAME
#endif



typedef uint16_t sensor_id_t;
typedef double sensor_value_t;    
typedef time_t sensor_ts_t;         // UTC timestamp as returned by time()

/*
 * Make a connection to MySQL database
 * Create a table named 'yourname' if the table does not exist
 * If the table existed, clear up the existing data if clear_up_flag is set to 1
 * return the connection for success, NULL if an error occurs
 */

MYSQL *init_connection(char clear_up_flag);

/*
 * Disconnect MySQL database
 */
void disconnect(MYSQL *conn);

/*
 * Write an INSERT query to insert a single sensor measurement
 * return zero for success, and non-zero if an error occurs
 */

int insert_sensor(MYSQL *conn, sensor_id_t id, sensor_value_t value, sensor_ts_t ts);

/*
 * Write an INSERT query to insert all sensor measurements existed in the file pointed by sensor_data
 * return zero for success, and non-zero if an error occurs
 */

int insert_sensor_from_file(MYSQL *conn, FILE *sensor_data);

/*
 * Write a SELECT query to return all sensor measurements existed in the table
 * return MYSQL_RES with all the results
 */

MYSQL_RES *find_sensor_all(MYSQL *conn);

/*
 * Write a SELECT query to return all sensor measurements containing 'value_t'
 * return MYSQL_RES with all the results
 */

MYSQL_RES *find_sensor_by_value(MYSQL *conn, sensor_value_t value_t);

/*
 * Write a SELECT query to return all sensor measurement that its value exceeds 'value_t'
 * return MYSQL_RES with all the results
 */
MYSQL_RES *find_sensor_exceed_value(MYSQL *conn, sensor_value_t value_t);

/*
 * Write a SELECT query to return all sensor measurement containing timestamp 'ts_t'
 * return MYSQL_RES with all the results
 */
MYSQL_RES *find_sensor_by_timestamp(MYSQL *conn, sensor_ts_t ts_t);

/*
 * Write a SELECT query to return all sensor measurement recorded later than timestamp 'ts_t'
 * return MYSQL_RES with all the results
 */
MYSQL_RES *find_sensor_later_timestamp(MYSQL *conn, sensor_ts_t ts_t);

/*
 * Return the number of records contained in the result
 */
int get_result_size(MYSQL_RES *result);

/*
 * Print all the records contained in the result
 */
void print_result(MYSQL_RES *result);

#endif /* _SENSOR_DB_H_ */

