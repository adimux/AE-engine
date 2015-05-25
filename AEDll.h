#ifndef AE_DLL_HEADER
#define AE_DLL_HEADER

/*#ifde
	#ifdef WIN32
		#define AE_DLL_COMPILE
	#endif

	#ifdef AE_DLL_COMPILE
		#define AE_2D_ENGINE_EXPORTS

		#ifdef AE_2D_ENGINE_EXPORTS
			#define AE_EXPORT __declspec(dllexport)
		#else
			#define AE_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define AE_EXPORT
#endif*/

/*#ifdef WIN32
		#ifdef COMPILE_MODE_WITH_DLL
			#define AE_EXPORT __declspec(dllexport)
		#else
			#define AE_EXPORT __declspec(dllimport)
		#endif
#else
	#define AE_EXPORT
#endif*/
//#define AE_EXPORT w

#endif
