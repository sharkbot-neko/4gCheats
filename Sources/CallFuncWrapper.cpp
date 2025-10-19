#include "CallFuncWrapper.hpp"

namespace CTRPluginFramework
{
	CallFuncWrapper::CallFuncWrapper(u32 addr)
	{
		Process::Write32((u32)&f0, addr);
		Process::Write32((u32)&f1, addr);
		Process::Write32((u32)&f2, addr);
		Process::Write32((u32)&f3, addr);
		Process::Write32((u32)&f4, addr);
		Process::Write32((u32)&f5, addr);
		Process::Write32((u32)&f6, addr);
		Process::Write32((u32)&f7, addr);
		Process::Write32((u32)&f8, addr);
		Process::Write32((u32)&f9, addr);
		Process::Write32((u32)&f10, addr);
		Process::Write32((u32)&f11, addr);
	}
	
	void CallFuncWrapper::SetAddress(u32 addr)
	{
		Process::Write32((u32)&f0, addr);
		Process::Write32((u32)&f1, addr);
		Process::Write32((u32)&f2, addr);
		Process::Write32((u32)&f3, addr);
		Process::Write32((u32)&f4, addr);
		Process::Write32((u32)&f5, addr);
		Process::Write32((u32)&f6, addr);
		Process::Write32((u32)&f7, addr);
		Process::Write32((u32)&f8, addr);
		Process::Write32((u32)&f9, addr);
		Process::Write32((u32)&f10, addr);
		Process::Write32((u32)&f11, addr);
	}
	
	u32 CallFuncWrapper::WithParamArray(int p_count, u32 params[])
	{
		u32 res;
		
		switch (p_count)
		{
		case 0:
			res = f0();
			break;
		case 1:
			res = f1(params[0]);
			break;
		case 2:
			res = f2(params[0], params[1]);
			break;
		case 3:
			res = f3(params[0], params[1], params[2]);
			break;
		case 4:
			res = f4(params[0], params[1], params[2], params[3]);
			break;
		case 5:
			res = f5(params[0], params[1], params[2], params[3], params[4]);
			break;
		case 6:
			res = f6(params[0], params[1], params[2], params[3], params[4], params[5]);
			break;
		case 7:
			res = f7(params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
			break;
		case 8:
			res = f8(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7]);
			break;
		case 9:
			res = f9(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8]);
			break;
		case 10:
			res = f10(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9]);
			break;
		case 11:
			res = f11(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10]);
			break;
		}
		
		return res;
	}
	
	u32 CallFuncWrapper::operator () ()
	{
		return f0();
	}
	
	u32 CallFuncWrapper::operator () (u32 p1)
	{
		return f1(p1);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2)
	{
		return f2(p1, p2);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2, u32 p3)
	{
		return f3(p1, p2, p3);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2, u32 p3, u32 p4)
	{
		return f4(p1, p2, p3, p4);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5)
	{
		return f5(p1, p2, p3, p4, p5);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6)
	{
		return f6(p1, p2, p3, p4, p5, p6);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7)
	{
		return f7(p1, p2, p3, p4, p5, p6, p7);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8)
	{
		return f8(p1, p2, p3, p4, p5, p6, p7, p8);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9)
	{
		return f9(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, u32 p10)
	{
		return f10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
	}
	
	u32 CallFuncWrapper::operator () (u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7, u32 p8, u32 p9, u32 p10, u32 p11)
	{
		return f11(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
	}
	
	
	
	
	
	
	
}




