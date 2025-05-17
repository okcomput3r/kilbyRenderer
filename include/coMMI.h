/* MMMI -->  Multiple Media Interface */
#ifndef COMMI_H
#define COMMI_H

    #include <iostream>
    #include <Windows.h>

    /* Debug Flag For mostly memory allocation logging and other logging operation*/
    #if defined(_DEBUG)
        # define CO_DEBUG _DEBUG
    #endif

    // define custom data types
    #if !defined(int8_c) || \
        !defined(uint8_c) || \
        !defined(int16_c) || \
        !defined(uint16_c) || \
        !defined(int32_c) || \
        !defined(uint32_c) || \
        !defined(int64_c) || \
        !defined(uint64_c) || \
        !defined(COMMI_SIZE_MAX)

        #include <stdint.h>
        
        #ifndef int8_c
            #ifdef INT8_MAX
                #define int8_c int8_t
            #else
                #define int8_c char 
            #endif     
        #endif

        #ifndef uint8_c
            #ifdef UINT8_MAX
                #define uint8_c uint8_t
            #else
                #define uint8_c unsigned char 
            #endif     
        #endif
        
        #ifndef int16_c
            #ifdef INT16_MAX
                #define int16_c int16_t
            #else
                #define int16_c short 
            #endif     
        #endif
        
        #ifndef uint16_c
            #ifdef UINT16_MAX
                #define uint16_c uint16_t
            #else
                #define uint16_c unsigned short 
            #endif     
        #endif

        #ifndef int32_c
            #ifdef INT32_MAX
                #define int32_c int32_t
            #else
                #define int32_c long 
            #endif     
        #endif
        
        #ifndef uint32_c
            #ifdef UINT32_MAX
                #define uint32_c uint32_t 
            #else
                #define uint32_c unsigned long 
            #endif     
        #endif

        #ifndef int64_c
            #ifdef INT64_MAX
                #define int64_c int64_t
            #else
                #define int64_c long long 
            #endif     
        #endif

        #ifndef uint64_c
            #ifdef UINT64_MAX
                #define uint64_c uint64_t
            #else
                #define uint64_c unsigned long long 
            #endif     
        #endif

        #ifndef COMMI_SIZE_MAX
            #define COMMI_SIZE_MAX SIZE_MAX
        #endif

    #endif /* stdint.h */

    #if !defined(size_c) || \
        !defined(nullptr_c)

        #include <stddef.h>

        #ifndef size_c
            #define size_c size_t
        #endif

        #ifndef nullptr_c
            #define nullptr_c nullptr_t
        #endif

    #endif /* stddef.h */

    #if !defined(coBool) || \
        !defined(CO_TRUE) || \
        !defined(CO_FALSE)

        #include <stdbool.h>

        #ifndef coBool
            #define coBool bool
        #endif

        #ifndef CO_TRUE
            #define CO_TRUE 1
        #endif

        #ifndef CO_FALSE
            #define CO_FALSE 0
        #endif

    #endif  /* stdbool.h */

    #if !defined(co_malloc) || \
        !defined(co_free) || \
        !defined(co_realloc)

        #include <stdlib.h>
        
        #if !defined(CO_DEBUG)
            #define co_malloc malloc
            #define co_free free
            #define co_realloc realloc
        #else 
            // define custom malloc function with debugging logs
            void* co_malloc(size_c nbytes);
            void co_free(void* memblock);
            void* realloc(void* memblock, size_c nbytes);
        #endif

            

    #endif

    #if !defined(CO_WIN32) && !defined(CO_LINUX)
        #if defined(WIN32) || defined(_WIN32)
            #define CO_WIN32 
        #endif
        #if defined(__linux__)
            #define  CO_LINUX
        #endif
    #endif

    /* MESSAGE TYPES */
    #define COMMI_SUCCESS 0
    #define COMMI_FAILED_NULL_WINDOW_SYSTEM 1
    #define COMMI_FAILED_MALLOC 2
    /* MESSAGE TYPES</> */

    /* ENV VARIABLES */
    typedef uint16_c coMMIResult;
    typedef uint8_c  coWindowSystem; // a window system is the type of OS is currently executing the script. Its called that way because other OS like linux can have different window systems like x11

    #define CO_WINDOW_NULL 0
    #define CO_WINDOW_WIN32 1
    #define CO_WINDOW_X11 2
    /* ENV VARIABLES </> */


    /* STRUCTS */
    struct coMMITimeW32{
        double iniTime;
        double fixed_time;

    };
    typedef struct coMMITime coMMITime;
    
    struct coMMIWindowContext{
        // pointer to a manually allocated part of memory away from user interaction
        // inner is a system independent context of the COMMI window, inside it reides the system dependent context, aswell as the current system
        void* inner; 

        // the result of the lastest non-successfull function call 
        coMMIResult result;
    };
    typedef struct coMMIWindowContext coMMIWindowContext;

    struct coMMIinner{
        coWindowSystem system;
        // system dependent context of the window, it will contain different data types depending on the context 
        void* context;
    };
    typedef struct coMMIinner coMMIinner;


    struct coMMIContextW32{
        coMMITimeW32 time;

        // WIN32 context

    };

    struct coMMIWindowInfo{

    };

    struct coMMIWindow{

    };
    
    double coMMI_get_current_time_W32();
    void coMMI_get_init_time_W32(coMMITimeW32* time);

    coWindowSystem coMMI_find_window_system();

    static void coMMI_create_context(coMMIWindowContext* context, coWindowSystem system);
    coMMIResult coMMI_create_context_W32(coMMIContextW32* w32_contex);

    static void coMMI_destroy_context(coMMIWindowContext* context);


    coMMIResult coMMI_create_inner(coMMIinner* inner, coWindowSystem system);
    void coMMI_destroy_inner(coMMIinner* inner);
    
    

#endif /* COMMI_H */

#ifdef COMMI_IMPLEMENTATION


    // implements custom malloc function in case the debug flag is set 
    #ifdef CO_DEBUG
        void* co_malloc(size_c nbytes)
        {
            std::cout << "ALLOCATING Nº BYTES: " << nbytes << std::endl;
            return malloc(nbytes);
        }

        void* realloc(void* memblock, size_c nbytes)
        {
            std::cout << "RE_ALLOCATING Nº BYTES: " << nbytes << std::endl;
            return realloc(memblock, nbytes);
        }

        void co_free(void* memblock)
        {
            std::cout << "FREEING Nº BYTES: " << sizeof(memblock) << std::endl;
            free(memblock);
        }

        
    #endif

    void coMMI_get_init_time_W32(coMMITimeW32* time)
    {
        time->iniTime = time->fixed_time = coMMI_get_current_time_W32();
    }

    double coMMI_get_current_time_W32()
    {
        FILETIME file_time;
        GetSystemTimeAsFileTime(&file_time);

        LONGLONG ll_now = (LONGLONG)(file_time.dwLowDateTime) + (LONGLONG)(file_time.dwHighDateTime << 32LL);

        return (double)(ll_now) / (double)(1.0e7);
    }

    coWindowSystem coMMI_find_window_system()
    {
        #ifdef CO_WIN32
            return CO_WINDOW_WIN32;
        #endif
        #ifdef CO_LINUX
            return CO_WINDOW_NULL;
        #endif
    }

    static void coMMI_create_context(coMMIWindowContext* context, coWindowSystem system)
    {
        // allocate memory for inner's context and system
        context->inner = co_malloc(sizeof(coMMIinner));
        
        
        // create inner's system dependent context 
        context->result = coMMI_create_inner(static_cast<coMMIinner*>(context->inner), system);

        /* TODO CO_BOOL coMMI_fatal_error(coMMIResult reult) --> to check if the error is fatal and need to free memory or continue*/
        if(context->result == 1)
        {
            co_free(context->inner);
            std::cout << "UNABLE TO ALLOCATE CONTEXT" << std::endl;

        }
    }

    static void coMMI_destroy_context(coMMIWindowContext* context)
    {
        if(context->inner){
            coMMI_destroy_inner(static_cast<coMMIinner*>(context->inner));
            co_free(context->inner);
        }

    }

    coMMIResult coMMI_create_inner(coMMIinner* inner, coWindowSystem system)
    {
        if(system == 0)
        {
            system = coMMI_find_window_system();
        }
        switch (system)
        {
            // unsuported/unrecognized window system
            default: return COMMI_FAILED_NULL_WINDOW_SYSTEM; break;
            case CO_WINDOW_WIN32:
            {
                inner->context = co_malloc(sizeof(coMMIContextW32));
                if(!inner->context)
                    return COMMI_FAILED_MALLOC;

                // Create Context
                /* TODO CO_BOOL coMMI_fatal_error(coMMIResult reult) --> to check if the error is fatal and need to free memory or continue*/
                coMMIResult result = coMMI_create_context_W32(static_cast<coMMIContextW32*>(inner->context));
                if(result == 1)
                {
                    co_free(inner->context);
                }
                return result;
                break;
            } 
            /* TODO CO_WINDOW_LINUX case for x11*/
            case CO_WINDOW_X11:
            {
                return 1;
                break;
            }
        } /* end switch*/
    }
    
    void coMMI_destroy_inner(coMMIinner* inner)
    {
        if(inner->context)
        {
            co_free(inner->context);
        }
    }

    coMMIResult coMMI_create_context_W32(coMMIContextW32* w32_contex)
    {
        coMMI_get_init_time_W32(&w32_contex->time);


        coMMIResult result = COMMI_SUCCESS;
        return result;
    }

#endif /* COMMI_IMPLEMENTATION */ 