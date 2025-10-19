#pragma once

#include <string>
#include <vector>
#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
	class CallFuncWrapper
	{
	public:
		CallFuncWrapper(u32 addr);
		
		void SetAddress(u32 addr);
		u32 WithParamArray(int p_count, u32 params[]);
		
		u32 operator () ();
		u32 operator () (u32 p1);
		u32 operator () (u32 p1, u32 p2);
		u32 operator () (u32 p1, u32 p2, u32 p3);
		u32 operator () (u32 p1, u32 p2, u32 p3, u32 p4);
		u32 operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5);
		u32 operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6);
		u32 operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7);
		u32 operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8);
		u32 operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9);
		u32 operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, u32 p10);
		u32 operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, u32 p10, u32 p11);
		
	private:
		volatile u32(*f0)();
		volatile u32(*f1)(u32 p1);
		volatile u32(*f2)(u32 p1, u32 p2);
		volatile u32(*f3)(u32 p1, u32 p2, u32 p3);
		volatile u32(*f4)(u32 p1, u32 p2, u32 p3, u32 p4);
		volatile u32(*f5)(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5);
		volatile u32(*f6)(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6);
		volatile u32(*f7)(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7);
		volatile u32(*f8)(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8);
		volatile u32(*f9)(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9);
		volatile u32(*f10)(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, u32 p10);
		volatile u32(*f11)(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, u32 p10, u32 p11);
	};
}

