/*-------------------------------------------------------
Copyright (C) 2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: README.txt
Purpose: Showing how to run faster matrix multiplication with SIMD
Language: C/C++ with Microsoft (R) C/C++ Optimizing Compiler 2015
Platform:
	-Compiler Version: 19.00.24210 for x64
	-OS: Windows 7
Project: CS529_chiyenteng_1
Author:
	-Name: Chi-Yen Teng
	-Login: chiyen.teng
	-ID: 60000416
Creation date: 09/18/16
--------------------------------------------------------*/


In Matrix2D.c, I defined "USE_SIMD" for using SIMD to make matrix multiplication 
twice faster than using normal iterative algorithm.

In case this method doesn't work with some other compilers or hardware, you can 
comment the line "#define USE_SIMD" to do matrix multiplication by using normal 
iterative algorithm.