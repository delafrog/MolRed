#ifndef _INIT_H
#define _INIT_H

#include <memory.h>
#include <stdlib.h>
//____________���� ������ ����InitObject() �ClearObject() � �������

inline void InitObject(int		& x){x	= 0;}
inline void InitObject(long		& x){x	= 0;}
inline void InitObject(bool		& x){x	= 0;}
inline void InitObject(char		& x){x	= 0;}
inline void InitObject(float	& x){x	= 0.0;}
inline void InitObject(double	& x){x	= 0.0;}
inline void InitObject(int		* x){x	= (int*)	malloc(sizeof(int));}
inline void InitObject(long		* x){x	= (long*)	malloc(sizeof(long));}
inline void InitObject(bool		* x){x	= (bool*)	malloc(sizeof(bool));}
inline void InitObject(char		* x){x	= (char*)	malloc(sizeof(char));}
inline void InitObject(float	* x){x	= (float*)	malloc(sizeof(float));}
inline void InitObject(double	* x){x	= (double*)	malloc(sizeof(double));}

inline void CopyObject(int		& x,const int		& y){x	= y;}
inline void CopyObject(long		& x,const long	& y){x	= y;}
inline void CopyObject(bool		& x,const bool	& y){x	= y;}
inline void CopyObject(char		& x,const char	& y){x	= y;}
inline void CopyObject(float	& x,const float	& y){x	= y;}
inline void CopyObject(double	& x,const double	& y){x	= y;}


inline void ClearObject(int		& x){}
inline void ClearObject(long	& x){}
inline void ClearObject(bool	& x){}
inline void ClearObject(char	& x){}
inline void ClearObject(float	& x){}
inline void ClearObject(double	& x){}


//______________________________________________________________________________________
#endif

