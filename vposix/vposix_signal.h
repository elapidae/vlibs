/****************************************************************************************
**
**  VLIBS codebase, NIIAS
**
**  Authors:
**  Alexandre Gromtsev aka elapidae     elapidae@yandex.ru
**  Nadezhda Churikova aka claorisel    claorisel@gmail.com
**  Ekaterina Boltenkova aka kataretta  kitkat52@yandex.ru
**  Ivan Deylid aka sid1057             ivanov.dale@gmail.com>
**
**  GNU Lesser General Public License Usage
**  This file may be used under the terms of the GNU Lesser General Public License
**  version 3 as published by the Free Software Foundation and appearing in the file
**  LICENSE.LGPL3 included in the packaging of this file. Please review the following
**  information to ensure the GNU Lesser General Public License version 3 requirements
**  will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************************/


#ifndef VPOSIX_SIGNAL_H
#define VPOSIX_SIGNAL_H

//=======================================================================================
//  http://www.opennet.ru/man.shtml?topic=signal&category=2
//  http://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=alarm&category=2
//  http://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=sigaction&category=2
//=======================================================================================


//=======================================================================================
namespace vposix
{

    class Signal
    {
        static constexpr bool do_trace() { return false; }

    public:
        using CallBack = void(*)(int);

        static int sig_interactive();           // SIGINT
        static int sig_termination_request();   // SIGTERM
        static int sig_killed();                // SIGKILL -- его нельзя переопределить.
        static int sig_alarm();                 // SIGALRM


        static CallBack _signal( int sig, CallBack cb );
        static void register_std_stops( CallBack cb ); // Ctl+C & kill <pid>

        static unsigned int _alarm( unsigned int seconds );

        static unsigned int re_alarm( unsigned int seconds, CallBack cb );

    };

} // namespace vposix
//=======================================================================================


//=======================================================================================
//#define	SIGINT		2	/* Interactive attention signal.  */
//#define	SIGILL		4	/* Illegal instruction.  */
//#define	SIGABRT		6	/* Abnormal termination.  */
//#define	SIGFPE		8	/* Erroneous arithmetic operation.  */
//#define	SIGSEGV		11	/* Invalid access to storage.  */
//#define	SIGTERM		15	/* Termination request.  */

///* Historical signals specified by POSIX. */
//#define	SIGHUP		1	/* Hangup.  */
//#define	SIGQUIT		3	/* Quit.  */
//#define	SIGTRAP		5	/* Trace/breakpoint trap.  */
//#define	SIGKILL		9	/* Killed.  */
//#define SIGBUS		10	/* Bus error.  */
//#define	SIGSYS		12	/* Bad system call.  */
//#define	SIGPIPE		13	/* Broken pipe.  */
//#define	SIGALRM		14	/* Alarm clock.  */

///* New(er) POSIX signals (1003.1-2008, 1003.1-2013).  */
//#define	SIGURG		16	/* Urgent data is available at a socket.  */
//#define	SIGSTOP		17	/* Stop, unblockable.  */
//#define	SIGTSTP		18	/* Keyboard stop.  */
//#define	SIGCONT		19	/* Continue.  */
//#define	SIGCHLD		20	/* Child terminated or stopped.  */
//#define	SIGTTIN		21	/* Background read from control terminal.  */
//#define	SIGTTOU		22	/* Background write to control terminal.  */
//#define	SIGPOLL		23	/* Pollable event occurred (System V).  */
//#define	SIGXCPU		24	/* CPU time limit exceeded.  */
//#define	SIGXFSZ		25	/* File size limit exceeded.  */
//#define	SIGVTALRM	26	/* Virtual timer expired.  */
//#define	SIGPROF		27	/* Profiling timer expired.  */
//#define	SIGUSR1		30	/* User-defined signal 1.  */
//#define	SIGUSR2		31	/* User-defined signal 2.  */

///* Nonstandard signals found in all modern POSIX systems
//   (including both BSD and Linux).  */
//#define	SIGWINCH	28	/* Window size change (4.3 BSD, Sun).  */

///* Archaic names for compatibility.  */
//#define	SIGIO		SIGPOLL	/* I/O now possible (4.2 BSD).  */
//#define	SIGIOT		SIGABRT	/* IOT instruction, abort() on a PDP-11.  */
//#define	SIGCLD		SIGCHLD	/* Old System V name */
//=======================================================================================


//=======================================================================================
/*  Это примерный список удобрений, из signal.h.
 *  Приведен просто для интереса, вдруг что заинтересует.
 *
 *
extern int kill (__pid_t __pid, int __sig) __THROW;
extern int killpg (__pid_t __pgrp, int __sig) __THROW;
extern int raise (int __sig) __THROW;
extern __sighandler_t ssignal (int __sig, __sighandler_t __handler);
extern int gsignal (int __sig) __THROW;
extern void psignal (int __sig, const char *__s);
extern void psiginfo (const siginfo_t *__pinfo, const char *__s);
extern int sigpause (int __sig) __asm__ ("__xpg_sigpause");
extern int __sigpause (int __sig_or_mask, int __is_sig);
extern int sigblock (int __mask) __THROW __attribute_deprecated__;
extern int sigsetmask (int __mask) __THROW __attribute_deprecated__;
extern int siggetmask (void) __THROW __attribute_deprecated__;
extern int sigemptyset (sigset_t *__set) __THROW __nonnull ((1));
extern int sigfillset (sigset_t *__set) __THROW __nonnull ((1));
extern int sigaddset (sigset_t *__set, int __signo) __THROW __nonnull ((1));
extern int sigdelset (sigset_t *__set, int __signo) __THROW __nonnull ((1));
extern int sigismember (const sigset_t *__set, int __signo)
     __THROW __nonnull ((1));
extern int sigisemptyset (const sigset_t *__set) __THROW __nonnull ((1));
extern int sigandset (sigset_t *__set, const sigset_t *__left,
              const sigset_t *__right) __THROW __nonnull ((1, 2, 3));
extern int sigorset (sigset_t *__set, const sigset_t *__left,
             const sigset_t *__right) __THROW __nonnull ((1, 2, 3));
extern int sigprocmask (int __how, const sigset_t *__restrict __set,
            sigset_t *__restrict __oset) __THROW;
extern int sigsuspend (const sigset_t *__set) __nonnull ((1));
extern int sigaction (int __sig, const struct sigaction *__restrict __act,
              struct sigaction *__restrict __oact) __THROW;
extern int sigpending (sigset_t *__set) __THROW __nonnull ((1));
extern int sigwait (const sigset_t *__restrict __set, int *__restrict __sig)
     __nonnull ((1, 2));
extern int sigwaitinfo (const sigset_t *__restrict __set,
            siginfo_t *__restrict __info) __nonnull ((1));
extern int sigtimedwait (const sigset_t *__restrict __set,
             siginfo_t *__restrict __info,
             const struct timespec *__restrict __timeout)
     __nonnull ((1));
extern int sigqueue (__pid_t __pid, int __sig, const union sigval __val);
extern const char *const _sys_siglist[_NSIG];
extern const char *const sys_siglist[_NSIG];
extern int sigreturn (struct sigcontext *__scp) __THROW;
extern int siginterrupt (int __sig, int __interrupt) __THROW;
extern int sigaltstack (const stack_t *__restrict __ss,
            stack_t *__restrict __oss) __THROW;
extern int sighold (int __sig) __THROW;
extern int sigrelse (int __sig) __THROW;
extern int sigignore (int __sig) __THROW;
extern __sighandler_t sigset (int __sig, __sighandler_t __disp) __THROW;
extern int __libc_current_sigrtmin (void) __THROW;
extern int __libc_current_sigrtmax (void) __THROW;
*/
//=======================================================================================


#endif // VPOSIX_SIGNAL_H

