/* IPG's prebuilt libcarmaker4sl.a (licclient.o) references __security_cookie,
** an MSVC /GS stack-protector global that plain MinGW-w64 does not provide.
** Without this stub the final link fails with "undefined reference to
** `__security_cookie'". The value is never read by MinGW-compiled code (no
** /GS checks are emitted), so any nonzero placeholder is sufficient -- this
** exists purely to satisfy the linker.
*/
#include <stdint.h>
uintptr_t __security_cookie = 0xBB40E64EU;
