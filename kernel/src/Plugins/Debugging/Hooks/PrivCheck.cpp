// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <Plugins/Debugging/Debugger.hpp>
#include <Utils/Kdlsym.hpp>
#include <Mira.hpp>

extern "C"
{
	#include <sys/lock.h>
	#include <sys/uio.h>
	#include <sys/proc.h>
	#include <sys/ioccom.h>
	#include <sys/fcntl.h>

	#include <vm/vm.h>
	#include <vm/pmap.h>

	#include <machine/psl.h>
	#include <machine/pmap.h>
	#include <machine/segments.h>
	#include <machine/trap.h>
};

using namespace Mira::Plugins;

int Debugger::OnPrivCheck(struct thread* p_Td, int p_Priv)
{
	auto priv_check_cred = (int(*)(void*, int))kdlsym(priv_check_cred);

    if(p_Priv == 0x2AB) {
    	//WriteLog(LL_Info, "priv_check: 0x2AB is needed, return 0.");
        return 0;
    }

    return priv_check_cred((void*)(p_Td->td_ucred), p_Priv);
}
