//=======================================================================================
//=======================================================================================
// PROGRAMA 		: Filtros Digitales (FIR)
// FUNCIÓN 			: Práctica Proyecto de Grado
// REALIZADO POR	: Holguer A. Becerra D. - Jefferson M. García P. - Juan D. Prieto A.
// ORGANIZACIÓN		: Universidad pontificia Bolivariana
// FECHA 			: Agosto 2015
//=======================================================================================
//=======================================================================================

//=======================================================================================
// LIBRERIAS
//=======================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "./include/hwlib.h"
#include "./include/socal/socal.h"
#include "./include/socal/hps.h"
#include "./include/socal/alt_gpio.h"

#include "hps_0.h"
#include "filtroFIR.h"

//=======================================================================================
// PARÁMETROS
//=======================================================================================
#define REG_BASE 0xC0000000
#define REG_SPAN 0x04000000

//=======================================================================================
// VARIABLES GLOBALES
//=======================================================================================
int i=0,j=0;
int fd;
void *virtual_base;
volatile unsigned long *h2p_start_timer_addr=NULL;
volatile unsigned long *p2h_div_time_addr=NULL;
volatile unsigned long *p2h_get_tick_addr=NULL;


volatile unsigned long *val1_addr=NULL;
volatile unsigned long *val2_addr=NULL;
volatile unsigned long *select_addr=NULL;
volatile unsigned long *wr_addr=NULL;
volatile unsigned long *result_addr=NULL;


//=======================================================================================
// RUTINA: INICIO DEL SISTEMA
//=======================================================================================
void init_system()
{
	if(( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ))) == -1 )
	{
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return;
	}

	virtual_base = mmap( NULL, REG_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, REG_BASE );
	if( virtual_base == MAP_FAILED )
	{
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return;
	}

	h2p_start_timer_addr 	= virtual_base + (( unsigned long )( REG_BASE + TIMER_START_BASE ) & ( unsigned long)( REG_SPAN-1 ));
	p2h_div_time_addr 		= virtual_base + (( unsigned long )( REG_BASE + TIMER_DIV_BASE ) & ( unsigned long)( REG_SPAN-1 ));
	p2h_get_tick_addr 		= virtual_base + (( unsigned long )( REG_BASE + GETTICK_BASE ) & ( unsigned long)( REG_SPAN-1 ));


	///acc para el filtro HW
	val1_addr 		= virtual_base + (( unsigned long )( REG_BASE + VAL1_BASE ) & ( unsigned long)( REG_SPAN-1 ));
	val2_addr 		= virtual_base + (( unsigned long )( REG_BASE + VAL2_BASE ) & ( unsigned long)( REG_SPAN-1 ));
	select_addr 	= virtual_base + (( unsigned long )( REG_BASE + SELECTOR_BASE ) & ( unsigned long)( REG_SPAN-1 ));
	wr_addr 		= virtual_base + (( unsigned long )( REG_BASE + WR_BASE ) & ( unsigned long)( REG_SPAN-1 ));
	result_addr 	= virtual_base + (( unsigned long )( REG_BASE + RESULT_SPAN ) & ( unsigned long)( REG_SPAN-1 ));

	alt_write_word( p2h_div_time_addr, 24 );
	alt_write_word( h2p_start_timer_addr, 0 );

}
//=======================================================================================
// EJECUCIÓN FILTRO FIR
//=======================================================================================
int main(int argc, char *argv[])
{
	if (argc > 1)
	{
	}
	else
	{
		printf("The command had no other arguments.\n");
		return 0;
	}

	//<><><><><><><><><><><><><><><><><>//
	// 		SYSTEM INITIALIZING			//
	//<><><><><><><><><><><><><><><><><>//
	init_system();

	//<><><><><><><><><><><><><><><><><>//
	// 		  SIGNALS DECLARATION		//
	//<><><><><><><><><><><><><><><><><>//
	FIR_filter filtro,filtro2,filtro3;
	SIGNAL signal1;
	SIGNAL signal1_output;
	SIGNAL signal2_output;
	SIGNAL signal3_output;

	sscanf (argv[1],"%d",&filtro.F1);
	sscanf (argv[2],"%d",&filtro.F2);
	sscanf (argv[3],"%d",&filtro.order);
	sscanf (argv[4],"%d",&filtro.FS);
	sscanf (argv[5],"%d",&filtro.window_type);
	sscanf (argv[6],"%d",&filtro.filter_type);
	sscanf (argv[7],"%d",&filtro.sw_hw);

//	filtro.F1=12071;
//	filtro.F2=12171;
//	filtro.order=200;
//	filtro.FS=44100;
//	filtro.window_type=BLACKMAN_HARRIS;
//	filtro.filter_type=BS_FILTER;

	//<><><><><><><><><><><><><><><><><>//
	// FILTER COEFFICIENTS CALCULATION	//
	//<><><><><><><><><><><><><><><><><>//
	calc_FIR_coefs(&filtro);
//	calc_FIR_coefs(&filtro2);
//	calc_FIR_coefs(&filtro3);

	//<><><><><><><><><><><><><><><><><>//
	// 			 LOAD FILE 				//
	//<><><><><><><><><><><><><><><><><>//
	load_signal(&signal1,argv[8]);

	//<><><><><><><><><><><><><><><><><>//
	// 		 SIGNAL REPLICATION 		//
	//<><><><><><><><><><><><><><><><><>//
	signal1_output.lenght=signal1.lenght;
//	signal2_output.lenght=signal1.lenght;
//	signal3_output.lenght=signal1.lenght;
	signal1_output.signal=(int*) malloc (sizeof(int)*signal1.lenght);
//	signal2_output.signal=(int*) malloc (sizeof(int)*signal1.lenght);
//	signal3_output.signal=(int*) malloc (sizeof(int)*signal1.lenght);

	//<><><><><><><><><><><><><><><><><>//
	// 			START TIMER				//
	//<><><><><><><><><><><><><><><><><>//
	alt_write_word(h2p_start_timer_addr, 1 );  //0:ligh, 1:unlight

	//<><><><><><><><><><><><><><><><><>//
	// APPLY FILTER & NORMALIZE SIGNAL	//
	//<><><><><><><><><><><><><><><><><>//
	normalize_signal( &signal1, 128);
	apply_FIR_whole_signal(&filtro, &signal1, &signal1_output);
	normalize_signal( &signal1_output, 128);
//	apply_FIR_whole_signal(&filtro2, &signal1_output, &signal2_output);
//	normalize_signal( &signal2_output, 128);
//	apply_FIR_whole_signal(&filtro3, &signal2_output, &signal3_output);
//	normalize_signal( &signal3_output, 128);

	//<><><><><><><><><><><><><><><><><>//
	// 		   GET TICK <TIMER>			//
	//<><><><><><><><><><><><><><><><><>//
	int time_cont;
	time_cont = alt_read_word(p2h_get_tick_addr);
	printf("valor del timer: %d\n",time_cont);

	//<><><><><><><><><><><><><><><><><>//
	// 		   TIMER SHUTDOWN			//
	//<><><><><><><><><><><><><><><><><>//
	alt_write_word(h2p_start_timer_addr, 0 );

	save_signal( &signal1_output, argv[9]);
//	save_signal( &signal2_output, "filtrito2.bin");
//	save_signal( &signal3_output, "filtrito3.bin");

	printf("Finalizando Ejecucion.\n");
	return 0;
}
