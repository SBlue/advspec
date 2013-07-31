/*
 *  vfuncs.cpp
 *  WebSpec project
 *  
 *  Copyright (c) 2013 Matthew McNamara
 *  BSD 2-Clause License
 *  http://opensource.org/licenses/BSD-2-Clause
 *
 */

#include "vfuncs.h"

void CBaseCombatCharacter_UpdateGlowEffect(CBaseCombatCharacter *pThisPtr) {
	//Magic from SourceMod
	void **this_ptr = *(void ***)&pThisPtr;
	void **vtable = *(void ***)pThisPtr;
	void *func = vtable[Index_CBaseCombatCharacter_UpdateGlowEffect];

	union {
		void (WSEmptyClass::*mfpnew)();
#if !defined(_LINUX) && !defined(_OSX)
		void *addr;
	} u;
	u.addr = func;
#else
		struct {
			void *addr;
			intptr_t adjustor;
		} s;
	} u;
	u.s.addr = func;
	u.s.adjustor = 0;
#endif

	(void) (reinterpret_cast<WSEmptyClass*>(this_ptr)->*u.mfpnew)();
}

DWORD *HookVFunc(DWORD *vtable, int index, DWORD *newFunction)
{
	DWORD dwOldProt, *oldFunc;
	VirtualProtect(&vtable[index], 4, PAGE_EXECUTE_READWRITE, &dwOldProt);
	oldFunc=(DWORD*)vtable[index];
	vtable[index]=(DWORD)newFunction;
	VirtualProtect(&vtable[index], 4, dwOldProt, &dwOldProt);
	return oldFunc;
}