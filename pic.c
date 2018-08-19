/*
 * pic.c
 * 
 * Copyright 2018  <cryptodad>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "pic.h"


#define BYTE unsigned char


/*
 * 	ref: driver-btm-l3.c
 *
 *	mutex are used, but this is not a threaded program, so can be removed
 *
 */
 
static BYTE	Pic_command_1	[ 1 ] 						= { PIC_COMMAND_1 };
static BYTE	Pic_command_2	[ 1 ] 						= { PIC_COMMAND_2 };
static BYTE 	Pic_set_voltage	[ 1 ] 						= { SET_VOLTAGE };
static BYTE 	Pic_get_voltage	[ 1 ] 						= { GET_VOLTAGE };
static BYTE 	Pic_read_pic_software_version 	[ 1 ]		= { READ_PIC_SOFTWARE_VERSION };
//static BYTE 	Pic_reset		[ 1 ] 						= { RESET_PIC };
static BYTE 	Pic_jump_from_loader_to_app		[ 1 ] 		= { JUMP_FROM_LOADER_TO_APP };

pthread_mutex_t	iic_mutex 								= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t 	i2c_mutex 								= PTHREAD_MUTEX_INITIALIZER;


extern void 	safe_exit 						( int );


extern int fd_i2c;


void 
pic_send_command ( void )
{    
	pthread_mutex_lock ( &i2c_mutex );
    //printf ( "%s write1 returns %d\n", 
	//	__FUNCTION__, 
		write ( fd_i2c, Pic_command_1, 1 );// );
    
    //usleep ( 100000 );
    
    //printf ( "%s write2 returns %d\n", 
		//__FUNCTION__, 
		write ( fd_i2c, Pic_command_2, 1 );// );
    
    //usleep ( 100000 );
    pthread_mutex_unlock ( &i2c_mutex );
}




void 
send_pic_command( void )
{
    BYTE	cmd [ 2 ];
    
    cmd [ 0 ] = PIC_COMMAND_1;
    cmd [ 1 ] = PIC_COMMAND_2;
    
    write ( fd_i2c, &cmd [ 0 ], 1 );
    
    usleep ( 200 );
    
    write ( fd_i2c, &cmd [ 1 ], 1 );

    usleep ( 200 );
}


void 
pic_reset ( void )
{
    //pic_send_command ();

    //pthread_mutex_lock(&i2c_mutex);
    
    //write ( fd_i2c, Pic_reset, 1 );
    
    //pthread_mutex_unlock(&i2c_mutex);
    
    //usleep ( 600 * 1000 );
    
    BYTE	cmd [ 2 ];
    
    cmd [ 0 ] = RESET_PIC;

    send_pic_command ();
    
    write ( fd_i2c, &cmd [ 0 ], 1 );
    
    usleep ( 100000 );
}


void 
pic_read_pic_software_version ( void )
{
	BYTE	version;
	
	
    pic_send_command ();
    
    pthread_mutex_lock ( &i2c_mutex );
    //printf ( "%s write returns %d\n", 
		//__FUNCTION__, 
		write ( fd_i2c, Pic_read_pic_software_version, 1 );// );
    
    //usleep ( 100000 );
    
    //printf ( "%s read returns %d\n", 
		//__FUNCTION__, 
		read  ( fd_i2c, &version, 1 );// );
		
    pthread_mutex_unlock ( &i2c_mutex );
    
	if ( version != 0x03 ) {
		
		printf ( "\nWrong PIC version %d\n", version );
		
		safe_exit ( 1 );
	}
	
	//usleep ( 100000 );
}


void 
pic_read_voltage( BYTE	*voltage ) 
{
	pic_send_command ();
    
    pthread_mutex_lock ( &i2c_mutex );
    
    write ( fd_i2c, Pic_get_voltage, 1 );
    
    read  ( fd_i2c, voltage, 1 );
    
    pthread_mutex_unlock ( &i2c_mutex );
    
    usleep ( 500000 );
}


void 
pic_set_voltage( BYTE *voltage )
{
    pic_send_command ();
    
    pthread_mutex_lock ( &i2c_mutex );
    
    write ( fd_i2c, Pic_set_voltage, 1 );
    
    write ( fd_i2c, voltage, 1 );
    
    pthread_mutex_unlock ( &i2c_mutex );
    
    usleep ( 500000 );
}


void 
pic_jump_from_loader_to_app( void )
{
    pic_send_command ();
    
    pthread_mutex_lock ( &i2c_mutex );
    
    write ( fd_i2c, Pic_jump_from_loader_to_app, 1 );
    
    pthread_mutex_unlock ( &i2c_mutex );
    
    usleep ( 500000 );
}
