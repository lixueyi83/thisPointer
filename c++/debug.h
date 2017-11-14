/*************************************************************************
	> File Name: debug.h
	> Author: 
	> Mail: 
	> Created Time: Mon 18 Sep 2017 11:55:00 AM PDT
 ************************************************************************/

#ifndef _DEBUG_H
#define _DEBUG_H


/***************************************************************************************************************************************************************************************
*       Debug in compile time
*/
#ifndef TEST_DEF
//#warning "TEST_DEF is not defined"
#endif 

//#pragma message "this is pragma message produced in compile time."

#ifdef ERROR_MSG_DEF
#error "if this message is printed out, then the compile process will ended."
#endif 

/***************************************************************************************************************************************************************************************
*       Debug in compile time
*/
#ifndef NULL
#define NULL 	((void *)0)
#endif

#define ATTR_UNUSED		__attribute__ ((unused)) /*This attribute suppresses the warining -Wunused-but-set-variable*/
#define COMMON_EXTERN	extern

/************************* Standard I/O Macros *************************/
#define TRACE			puts				/*'\n' will be automatically added in the end of the string.*/
#define DEBUG			printf			/* equals: #define DEBUG printf */
/*Both Dec and Hex Format */
#ifdef DETAIL_DEBUG_INFO
#define debug_var(exp)			{printf("Debug: "); printf(#exp" = %d(0x%X),  Line:%d, Func:%s, File:%s\n", (int)exp, (int)exp, __LINE__, __func__, __FILE__);}
#define debug_2_var(exp1,exp2)		{printf("Debug: "); printf(#exp1" = %d(0x%X), "#exp2" = %d(0x%X),  Line:%d, Func:%s, File:%s\n", (int)exp1, (int)exp1, (int)exp2, (int)exp2, __LINE__, __func__, __FILE__);}
#define debug_3_var(exp1,exp2,exp3)	(printf("Debug: "), printf(#exp1" = %d(0x%X), "#exp2" = %d(0x%X), "#exp3" = %d(0x%X),  Line:%d, Func:%s, File:%s\n", (int)exp1, (int)exp1, (int)exp2, (int)exp2, (int)exp3, (int)exp3, __LINE__, __func__, __FILE__))
#else
#define debug_var(exp)			{printf(#exp" = %d(0x%X)\n", (int)exp, (int)exp);}
#define debug_2_var(exp1,exp2)		{printf(#exp1" = %d(0x%X), "#exp2" = %d(0x%X)\n", (int)exp1, (int)exp1, (int)exp2, (int)exp2);}
#define debug_3_var(exp1,exp2,exp3)	(printf(#exp1" = %d(0x%X), "#exp2" = %d(0x%X), "#exp3" = %d(0x%X)\n", (int)exp1, (int)exp1, (int)exp2, (int)exp2, (int)exp3, (int)exp3))	
#endif
//#define debug_str(exp) 			{printf("Debug: "); printf(#exp" = %s, Line:%d, Func:%s, File:%s\n", exp, __LINE__, __func__, __FILE__);}
#define debug_str(exp) 				{printf("Debug: "); printf(#exp" = %s\n", (char *)exp);}
#define debug_char(exp) 				{printf("Debug: "); printf(#exp" = %c\n", (char)exp);}
/************************* debugging info*************************/
#define debug_info()	                                                    \
do{								                                            \
	printf("-------- Function:%s  File:%s --------\n",__func__, __FILE__);	\
}while(0)

#define main_parameter_parse(argc, argv)	\
do{											\
	static int i = 0;			            \
	DEBUG("NumberOfParameters: %d\n", argc);\
	TRACE("TheInputString: ");				\
	for(i=0; argv[i] != '\0'; i++)		\
	{									\
		DEBUG("%s\n", argv[i]);			\
	}									\
}while(0)


/***************************************************************************************************************************************************************************************
*       time in runtime
*/
#define CURRENT_TIME()          \
{                               \
	time_t now;                 \
	time(&now);                 \
	DEBUG("%s", ctime(&now));   \
	return EXIT_SUCCESS;        \
}

#define sec()                   \
{                               \
    struct timeval tv;          \
	gettimeofday(&tv, NULL);    \
	return (tv.tv_sec % 60);    \
}

#define msec()                  \
{                               \
    struct timeval tv;          \
	gettimeofday(&tv, NULL);    \
	return (tv.tv_usec/1000);   \
}

#define usec()                  \
{                               \
    struct timeval tv;          \
	gettimeofday(&tv, NULL);    \
	return (tv.tv_usec);        \
}

#define busy_wait()             \
{                               \
    unsinged int tnow;          \
    unsigned int elapsed;       \
    static int start_time = msec(); \
    do                          \
    {                           \
        tnow = msec();          \
        elapsed = (unsigned int)(tnow - start_time);    \
    } while (elapsed < 2000);                           \
    start_time += 2000;         \
}


#define RUNTIME_MEAS(func,arg)				\
{											\
    struct timespec ss;						\
    struct timespec ee;						\
    clock_gettime(CLOCK_MONOTONIC, &ss);	\
    func(arg);								\
    clock_gettime(CLOCK_MONOTONIC, &ee);	\
    double timediff = (ee.tv_sec-ss.tv_sec)+(ee.tv_nsec-ss.tv_nsec)/1000000000.0;	\
    printf("\t *** Runtime of %s:  %.12f\n", #func, timediff);					\
}

#define MEA_PRE()	\
{                   \
    struct timespec ss;						\
    struct timespec ee;						\
    clock_gettime(CLOCK_MONOTONIC, &ss);	

#define MEA_POST()	\
    clock_gettime(CLOCK_MONOTONIC, &ee);	\
    double timediff = (ee.tv_sec-ss.tv_sec)+(ee.tv_nsec-ss.tv_nsec)/1000000000.0;	\
    printf("\t *** Runtime:  %.12f\n", timediff);   \
}
		
#define MEAS_FUNC(func_call)	\
	MEA_PRE();		\
	func_call;		\
	MEA_POST();
	
    
#define PRINT_TIMESTAMP()	\
    std::time_t timestamp_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());	\
    std::cout << "\t *** timestamp: " << std::ctime(&timestamp_);

/* Use this in looping code, e.g. a read frame loop*/
#define PRINT_FPS()						\
{										\
	static int fps = 0;					\
    static struct timespec ss;			\
    struct timespec ee;					\
    fps++;								\
    clock_gettime(CLOCK_MONOTONIC, &ee);\
    double timediff = (ee.tv_sec-ss.tv_sec)+(ee.tv_nsec-ss.tv_nsec)/1000000000.0;	\
    if(timediff > 1)						\
    {										\
    	printf("\t *** FPS = %d\n", fps);	\
    	fps = 0;							\
    	ss.tv_sec = ee.tv_sec;				\
    	ss.tv_nsec = ee.tv_nsec;			\
    }										\
}


#endif
