CFLAGS=-Wall -I. -g
CC=gcc

all: apmcc apmcd apmcworker connect

connect : connect.o apmcd_clnt.o apmcd_xdr.o
	$(CC) -o connect connect.o apmcd_clnt.o apmcd_xdr.o

apmcc : apmcc.o apmcd_clnt.o apmcd_xdr.o
	$(CC) -o apmcc apmcc.o apmcd_clnt.o apmcd_xdr.o -lm

apmcd : apmcd_svc.o apmcd_clnt.o apmcd_xdr.o var.o \
        add.o launch_program.o stop_program.o query_program.o connect_apmcd.o \
	send_thresholds.c get_thresholds.c
	$(CC) -o apmcd $^

apmcworker : apmcworker.o apmcd_clnt.o apmcd_xdr.o
	$(CC) -o apmcworker apmcworker.o apmcd_clnt.o apmcd_xdr.o 

apmcd_xdr.o : apmcd_xdr.c
	$(CC) -o apmcd_xdr.o -c apmcd_xdr.c

test : test.o apmcd_xdr.o apmcd_clnt.o
	$(CC) -o test $^ -lm

%.o : %.c
	$(CC) -o $@ $(CFLAGS) -c $<

depend:
	makedepend -- $(CFLAGS) -- *.c

apmcd.h apmcd_clnt.c apmcd_svc.c apmcd_xdr.c : apmcd.x
	rpcgen -N apmcd.x

clean :
	rm -f apmcd apmcworker apmcd.h apmcd_clnt.c apmcd_svc.c apmcd_xdr.c 
	rm -f apmcd_svc.o apmcd_xdr.o var.o add.o launch_program.o 
	rm -f stop_program.o query_program.o apmcworker.o apmcd_clnt.o 
	rm -f apmcd_xdr.o apmcc apmcc.o connect connect.o connect_apmcd.o
	rm -f *~


add.o : apmcd.h
apmcworker.o : apmcd.h
launch_program.o : apmcd.h
query_program.o : apmcd.h
stop_program.o : apmcd.h
apmcc.o : apmcd.h

# DO NOT DELETE

add.o: /usr/include/stdlib.h /usr/include/features.h /usr/include/sys/cdefs.h
add.o: /usr/include/gnu/stubs.h
add.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
add.o: /usr/include/string.h apmcd.h /usr/include/rpc/rpc.h
add.o: /usr/include/rpc/types.h /usr/include/sys/types.h
add.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
add.o: /usr/include/bits/typesizes.h /usr/include/time.h
add.o: /usr/include/sys/time.h /usr/include/bits/time.h
add.o: /usr/include/sys/select.h /usr/include/bits/select.h
add.o: /usr/include/bits/sigset.h /usr/include/sys/param.h
add.o: /usr/include/limits.h
add.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
add.o: /usr/include/linux/limits.h /usr/include/linux/param.h
add.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
add.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
add.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
add.o: /usr/include/stdint.h /usr/include/bits/wchar.h
add.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
add.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
add.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
add.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
add.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
add.o: /usr/include/endian.h /usr/include/bits/endian.h
add.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
add.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
add.o: /usr/include/wchar.h /usr/include/gconv.h
add.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
add.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
add.o: /usr/include/rpc/auth.h /usr/include/rpc/clnt.h /usr/include/sys/un.h
add.o: /usr/include/rpc/rpc_msg.h /usr/include/rpc/auth_unix.h
add.o: /usr/include/rpc/auth_des.h /usr/include/rpc/svc.h
add.o: /usr/include/rpc/svc_auth.h /usr/include/rpc/netdb.h
add.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
add.o: /usr/include/bits/confname.h
apmcc.o: /usr/include/signal.h /usr/include/features.h
apmcc.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
apmcc.o: /usr/include/bits/sigset.h /usr/include/bits/types.h
apmcc.o: /usr/include/bits/wordsize.h
apmcc.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
apmcc.o: /usr/include/bits/typesizes.h /usr/include/bits/signum.h
apmcc.o: /usr/include/math.h /usr/include/bits/huge_val.h
apmcc.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h apmcd.h
apmcc.o: /usr/include/rpc/rpc.h /usr/include/rpc/types.h
apmcc.o: /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
apmcc.o: /usr/include/sys/time.h /usr/include/bits/time.h
apmcc.o: /usr/include/sys/select.h /usr/include/bits/select.h
apmcc.o: /usr/include/sys/param.h /usr/include/limits.h
apmcc.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
apmcc.o: /usr/include/linux/limits.h /usr/include/linux/param.h
apmcc.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
apmcc.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
apmcc.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
apmcc.o: /usr/include/stdint.h /usr/include/bits/wchar.h
apmcc.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
apmcc.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
apmcc.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
apmcc.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
apmcc.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
apmcc.o: /usr/include/endian.h /usr/include/bits/endian.h
apmcc.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
apmcc.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
apmcc.o: /usr/include/wchar.h /usr/include/gconv.h
apmcc.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
apmcc.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
apmcc.o: /usr/include/rpc/auth.h /usr/include/rpc/clnt.h
apmcc.o: /usr/include/sys/un.h /usr/include/rpc/rpc_msg.h
apmcc.o: /usr/include/rpc/auth_unix.h /usr/include/rpc/auth_des.h
apmcc.o: /usr/include/rpc/svc.h /usr/include/rpc/svc_auth.h
apmcc.o: /usr/include/rpc/netdb.h /usr/include/unistd.h
apmcc.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
apmcd_clnt.o: /usr/include/memory.h /usr/include/features.h
apmcd_clnt.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
apmcd_clnt.o: /usr/include/string.h
apmcd_clnt.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h apmcd.h
apmcd_clnt.o: /usr/include/rpc/rpc.h /usr/include/rpc/types.h
apmcd_clnt.o: /usr/include/stdlib.h /usr/include/sys/types.h
apmcd_clnt.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
apmcd_clnt.o: /usr/include/bits/typesizes.h /usr/include/time.h
apmcd_clnt.o: /usr/include/sys/time.h /usr/include/bits/time.h
apmcd_clnt.o: /usr/include/sys/select.h /usr/include/bits/select.h
apmcd_clnt.o: /usr/include/bits/sigset.h /usr/include/sys/param.h
apmcd_clnt.o: /usr/include/limits.h
apmcd_clnt.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
apmcd_clnt.o: /usr/include/linux/limits.h /usr/include/linux/param.h
apmcd_clnt.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
apmcd_clnt.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
apmcd_clnt.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
apmcd_clnt.o: /usr/include/stdint.h /usr/include/bits/wchar.h
apmcd_clnt.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
apmcd_clnt.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
apmcd_clnt.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
apmcd_clnt.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
apmcd_clnt.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
apmcd_clnt.o: /usr/include/endian.h /usr/include/bits/endian.h
apmcd_clnt.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
apmcd_clnt.o: /usr/include/stdio.h /usr/include/libio.h
apmcd_clnt.o: /usr/include/_G_config.h /usr/include/wchar.h
apmcd_clnt.o: /usr/include/gconv.h
apmcd_clnt.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
apmcd_clnt.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
apmcd_clnt.o: /usr/include/rpc/auth.h /usr/include/rpc/clnt.h
apmcd_clnt.o: /usr/include/sys/un.h /usr/include/rpc/rpc_msg.h
apmcd_clnt.o: /usr/include/rpc/auth_unix.h /usr/include/rpc/auth_des.h
apmcd_clnt.o: /usr/include/rpc/svc.h /usr/include/rpc/svc_auth.h
apmcd_clnt.o: /usr/include/rpc/netdb.h /usr/include/unistd.h
apmcd_clnt.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
apmcd_svc.o: apmcd.h /usr/include/rpc/rpc.h /usr/include/rpc/types.h
apmcd_svc.o: /usr/include/stdlib.h /usr/include/features.h
apmcd_svc.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
apmcd_svc.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
apmcd_svc.o: /usr/include/sys/types.h /usr/include/bits/types.h
apmcd_svc.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
apmcd_svc.o: /usr/include/time.h /usr/include/sys/time.h
apmcd_svc.o: /usr/include/bits/time.h /usr/include/sys/select.h
apmcd_svc.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
apmcd_svc.o: /usr/include/sys/param.h /usr/include/limits.h
apmcd_svc.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
apmcd_svc.o: /usr/include/linux/limits.h /usr/include/linux/param.h
apmcd_svc.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
apmcd_svc.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
apmcd_svc.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
apmcd_svc.o: /usr/include/stdint.h /usr/include/bits/wchar.h
apmcd_svc.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
apmcd_svc.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
apmcd_svc.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
apmcd_svc.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
apmcd_svc.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
apmcd_svc.o: /usr/include/endian.h /usr/include/bits/endian.h
apmcd_svc.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
apmcd_svc.o: /usr/include/stdio.h /usr/include/libio.h
apmcd_svc.o: /usr/include/_G_config.h /usr/include/wchar.h
apmcd_svc.o: /usr/include/gconv.h
apmcd_svc.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
apmcd_svc.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
apmcd_svc.o: /usr/include/rpc/auth.h /usr/include/rpc/clnt.h
apmcd_svc.o: /usr/include/sys/un.h /usr/include/rpc/rpc_msg.h
apmcd_svc.o: /usr/include/rpc/auth_unix.h /usr/include/rpc/auth_des.h
apmcd_svc.o: /usr/include/rpc/svc.h /usr/include/rpc/svc_auth.h
apmcd_svc.o: /usr/include/rpc/netdb.h /usr/include/unistd.h
apmcd_svc.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
apmcd_svc.o: /usr/include/rpc/pmap_clnt.h /usr/include/string.h
apmcd_svc.o: /usr/include/memory.h
apmcd_xdr.o: apmcd.h /usr/include/rpc/rpc.h /usr/include/rpc/types.h
apmcd_xdr.o: /usr/include/stdlib.h /usr/include/features.h
apmcd_xdr.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
apmcd_xdr.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
apmcd_xdr.o: /usr/include/sys/types.h /usr/include/bits/types.h
apmcd_xdr.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
apmcd_xdr.o: /usr/include/time.h /usr/include/sys/time.h
apmcd_xdr.o: /usr/include/bits/time.h /usr/include/sys/select.h
apmcd_xdr.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
apmcd_xdr.o: /usr/include/sys/param.h /usr/include/limits.h
apmcd_xdr.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
apmcd_xdr.o: /usr/include/linux/limits.h /usr/include/linux/param.h
apmcd_xdr.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
apmcd_xdr.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
apmcd_xdr.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
apmcd_xdr.o: /usr/include/stdint.h /usr/include/bits/wchar.h
apmcd_xdr.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
apmcd_xdr.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
apmcd_xdr.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
apmcd_xdr.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
apmcd_xdr.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
apmcd_xdr.o: /usr/include/endian.h /usr/include/bits/endian.h
apmcd_xdr.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
apmcd_xdr.o: /usr/include/stdio.h /usr/include/libio.h
apmcd_xdr.o: /usr/include/_G_config.h /usr/include/wchar.h
apmcd_xdr.o: /usr/include/gconv.h
apmcd_xdr.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
apmcd_xdr.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
apmcd_xdr.o: /usr/include/rpc/auth.h /usr/include/rpc/clnt.h
apmcd_xdr.o: /usr/include/sys/un.h /usr/include/rpc/rpc_msg.h
apmcd_xdr.o: /usr/include/rpc/auth_unix.h /usr/include/rpc/auth_des.h
apmcd_xdr.o: /usr/include/rpc/svc.h /usr/include/rpc/svc_auth.h
apmcd_xdr.o: /usr/include/rpc/netdb.h /usr/include/unistd.h
apmcd_xdr.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
apmcworker.o: /usr/include/signal.h /usr/include/features.h
apmcworker.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
apmcworker.o: /usr/include/bits/sigset.h /usr/include/bits/types.h
apmcworker.o: /usr/include/bits/wordsize.h
apmcworker.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
apmcworker.o: /usr/include/bits/typesizes.h /usr/include/bits/signum.h
apmcworker.o: apmcd.h /usr/include/rpc/rpc.h /usr/include/rpc/types.h
apmcworker.o: /usr/include/stdlib.h /usr/include/sys/types.h
apmcworker.o: /usr/include/time.h /usr/include/sys/time.h
apmcworker.o: /usr/include/bits/time.h /usr/include/sys/select.h
apmcworker.o: /usr/include/bits/select.h /usr/include/sys/param.h
apmcworker.o: /usr/include/limits.h
apmcworker.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
apmcworker.o: /usr/include/linux/limits.h /usr/include/linux/param.h
apmcworker.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
apmcworker.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
apmcworker.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
apmcworker.o: /usr/include/stdint.h /usr/include/bits/wchar.h
apmcworker.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
apmcworker.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
apmcworker.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
apmcworker.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
apmcworker.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
apmcworker.o: /usr/include/endian.h /usr/include/bits/endian.h
apmcworker.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
apmcworker.o: /usr/include/stdio.h /usr/include/libio.h
apmcworker.o: /usr/include/_G_config.h /usr/include/wchar.h
apmcworker.o: /usr/include/gconv.h
apmcworker.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
apmcworker.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
apmcworker.o: /usr/include/rpc/auth.h /usr/include/rpc/clnt.h
apmcworker.o: /usr/include/sys/un.h /usr/include/rpc/rpc_msg.h
apmcworker.o: /usr/include/rpc/auth_unix.h /usr/include/rpc/auth_des.h
apmcworker.o: /usr/include/rpc/svc.h /usr/include/rpc/svc_auth.h
apmcworker.o: /usr/include/rpc/netdb.h /usr/include/unistd.h
apmcworker.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
connect_apmcd.o: apmcd.h /usr/include/rpc/rpc.h /usr/include/rpc/types.h
connect_apmcd.o: /usr/include/stdlib.h /usr/include/features.h
connect_apmcd.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
connect_apmcd.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
connect_apmcd.o: /usr/include/sys/types.h /usr/include/bits/types.h
connect_apmcd.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
connect_apmcd.o: /usr/include/time.h /usr/include/sys/time.h
connect_apmcd.o: /usr/include/bits/time.h /usr/include/sys/select.h
connect_apmcd.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
connect_apmcd.o: /usr/include/sys/param.h /usr/include/limits.h
connect_apmcd.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
connect_apmcd.o: /usr/include/linux/limits.h /usr/include/linux/param.h
connect_apmcd.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
connect_apmcd.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
connect_apmcd.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
connect_apmcd.o: /usr/include/stdint.h /usr/include/bits/wchar.h
connect_apmcd.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
connect_apmcd.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
connect_apmcd.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
connect_apmcd.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
connect_apmcd.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
connect_apmcd.o: /usr/include/endian.h /usr/include/bits/endian.h
connect_apmcd.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
connect_apmcd.o: /usr/include/stdio.h /usr/include/libio.h
connect_apmcd.o: /usr/include/_G_config.h /usr/include/wchar.h
connect_apmcd.o: /usr/include/gconv.h
connect_apmcd.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
connect_apmcd.o: /usr/include/bits/stdio_lim.h
connect_apmcd.o: /usr/include/bits/sys_errlist.h /usr/include/rpc/auth.h
connect_apmcd.o: /usr/include/rpc/clnt.h /usr/include/sys/un.h
connect_apmcd.o: /usr/include/rpc/rpc_msg.h /usr/include/rpc/auth_unix.h
connect_apmcd.o: /usr/include/rpc/auth_des.h /usr/include/rpc/svc.h
connect_apmcd.o: /usr/include/rpc/svc_auth.h /usr/include/rpc/netdb.h
connect_apmcd.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
connect_apmcd.o: /usr/include/bits/confname.h
connect.o: /usr/include/stdlib.h /usr/include/features.h
connect.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
connect.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h apmcd.h
connect.o: /usr/include/rpc/rpc.h /usr/include/rpc/types.h
connect.o: /usr/include/sys/types.h /usr/include/bits/types.h
connect.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
connect.o: /usr/include/time.h /usr/include/sys/time.h
connect.o: /usr/include/bits/time.h /usr/include/sys/select.h
connect.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
connect.o: /usr/include/sys/param.h /usr/include/limits.h
connect.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
connect.o: /usr/include/linux/limits.h /usr/include/linux/param.h
connect.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
connect.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
connect.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
connect.o: /usr/include/stdint.h /usr/include/bits/wchar.h
connect.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
connect.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
connect.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
connect.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
connect.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
connect.o: /usr/include/endian.h /usr/include/bits/endian.h
connect.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
connect.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
connect.o: /usr/include/wchar.h /usr/include/gconv.h
connect.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
connect.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
connect.o: /usr/include/rpc/auth.h /usr/include/rpc/clnt.h
connect.o: /usr/include/sys/un.h /usr/include/rpc/rpc_msg.h
connect.o: /usr/include/rpc/auth_unix.h /usr/include/rpc/auth_des.h
connect.o: /usr/include/rpc/svc.h /usr/include/rpc/svc_auth.h
connect.o: /usr/include/rpc/netdb.h /usr/include/unistd.h
connect.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
get_thresholds.o: /usr/include/stdlib.h /usr/include/features.h
get_thresholds.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
get_thresholds.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
get_thresholds.o: /usr/include/signal.h /usr/include/bits/sigset.h
get_thresholds.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
get_thresholds.o: /usr/include/bits/typesizes.h /usr/include/bits/signum.h
get_thresholds.o: apmcd.h /usr/include/rpc/rpc.h /usr/include/rpc/types.h
get_thresholds.o: /usr/include/sys/types.h /usr/include/time.h
get_thresholds.o: /usr/include/sys/time.h /usr/include/bits/time.h
get_thresholds.o: /usr/include/sys/select.h /usr/include/bits/select.h
get_thresholds.o: /usr/include/sys/param.h /usr/include/limits.h
get_thresholds.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
get_thresholds.o: /usr/include/linux/limits.h /usr/include/linux/param.h
get_thresholds.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
get_thresholds.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
get_thresholds.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
get_thresholds.o: /usr/include/stdint.h /usr/include/bits/wchar.h
get_thresholds.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
get_thresholds.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
get_thresholds.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
get_thresholds.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
get_thresholds.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
get_thresholds.o: /usr/include/endian.h /usr/include/bits/endian.h
get_thresholds.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
get_thresholds.o: /usr/include/stdio.h /usr/include/libio.h
get_thresholds.o: /usr/include/_G_config.h /usr/include/wchar.h
get_thresholds.o: /usr/include/gconv.h
get_thresholds.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
get_thresholds.o: /usr/include/bits/stdio_lim.h
get_thresholds.o: /usr/include/bits/sys_errlist.h /usr/include/rpc/auth.h
get_thresholds.o: /usr/include/rpc/clnt.h /usr/include/sys/un.h
get_thresholds.o: /usr/include/rpc/rpc_msg.h /usr/include/rpc/auth_unix.h
get_thresholds.o: /usr/include/rpc/auth_des.h /usr/include/rpc/svc.h
get_thresholds.o: /usr/include/rpc/svc_auth.h /usr/include/rpc/netdb.h
get_thresholds.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
get_thresholds.o: /usr/include/bits/confname.h
launch_program.o: /usr/include/stdlib.h /usr/include/features.h
launch_program.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
launch_program.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
launch_program.o: /usr/include/string.h /usr/include/sys/types.h
launch_program.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
launch_program.o: /usr/include/bits/typesizes.h /usr/include/time.h
launch_program.o: /usr/include/sys/wait.h /usr/include/signal.h
launch_program.o: /usr/include/bits/sigset.h /usr/include/bits/signum.h
launch_program.o: /usr/include/sys/resource.h /usr/include/bits/resource.h
launch_program.o: /usr/include/bits/time.h /usr/include/bits/waitflags.h
launch_program.o: /usr/include/bits/waitstatus.h /usr/include/errno.h
launch_program.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
launch_program.o: /usr/include/asm/errno.h /usr/include/asm-i486/errno.h
launch_program.o: /usr/include/asm-generic/errno.h
launch_program.o: /usr/include/asm-generic/errno-base.h apmcd.h
launch_program.o: /usr/include/rpc/rpc.h /usr/include/rpc/types.h
launch_program.o: /usr/include/sys/time.h /usr/include/sys/select.h
launch_program.o: /usr/include/bits/select.h /usr/include/sys/param.h
launch_program.o: /usr/include/limits.h
launch_program.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
launch_program.o: /usr/include/linux/limits.h /usr/include/linux/param.h
launch_program.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
launch_program.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
launch_program.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
launch_program.o: /usr/include/stdint.h /usr/include/bits/wchar.h
launch_program.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
launch_program.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
launch_program.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
launch_program.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
launch_program.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
launch_program.o: /usr/include/endian.h /usr/include/bits/endian.h
launch_program.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
launch_program.o: /usr/include/stdio.h /usr/include/libio.h
launch_program.o: /usr/include/_G_config.h /usr/include/wchar.h
launch_program.o: /usr/include/gconv.h
launch_program.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
launch_program.o: /usr/include/bits/stdio_lim.h
launch_program.o: /usr/include/bits/sys_errlist.h /usr/include/rpc/auth.h
launch_program.o: /usr/include/rpc/clnt.h /usr/include/sys/un.h
launch_program.o: /usr/include/rpc/rpc_msg.h /usr/include/rpc/auth_unix.h
launch_program.o: /usr/include/rpc/auth_des.h /usr/include/rpc/svc.h
launch_program.o: /usr/include/rpc/svc_auth.h /usr/include/rpc/netdb.h
launch_program.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
launch_program.o: /usr/include/bits/confname.h
query_program.o: /usr/include/stdlib.h /usr/include/features.h
query_program.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
query_program.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
query_program.o: /usr/include/string.h /usr/include/sys/types.h
query_program.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
query_program.o: /usr/include/bits/typesizes.h /usr/include/time.h
query_program.o: /usr/include/sys/wait.h /usr/include/signal.h
query_program.o: /usr/include/bits/sigset.h /usr/include/bits/signum.h
query_program.o: /usr/include/sys/resource.h /usr/include/bits/resource.h
query_program.o: /usr/include/bits/time.h /usr/include/bits/waitflags.h
query_program.o: /usr/include/bits/waitstatus.h apmcd.h
query_program.o: /usr/include/rpc/rpc.h /usr/include/rpc/types.h
query_program.o: /usr/include/sys/time.h /usr/include/sys/select.h
query_program.o: /usr/include/bits/select.h /usr/include/sys/param.h
query_program.o: /usr/include/limits.h
query_program.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
query_program.o: /usr/include/linux/limits.h /usr/include/linux/param.h
query_program.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
query_program.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
query_program.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
query_program.o: /usr/include/stdint.h /usr/include/bits/wchar.h
query_program.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
query_program.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
query_program.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
query_program.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
query_program.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
query_program.o: /usr/include/endian.h /usr/include/bits/endian.h
query_program.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
query_program.o: /usr/include/stdio.h /usr/include/libio.h
query_program.o: /usr/include/_G_config.h /usr/include/wchar.h
query_program.o: /usr/include/gconv.h
query_program.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
query_program.o: /usr/include/bits/stdio_lim.h
query_program.o: /usr/include/bits/sys_errlist.h /usr/include/rpc/auth.h
query_program.o: /usr/include/rpc/clnt.h /usr/include/sys/un.h
query_program.o: /usr/include/rpc/rpc_msg.h /usr/include/rpc/auth_unix.h
query_program.o: /usr/include/rpc/auth_des.h /usr/include/rpc/svc.h
query_program.o: /usr/include/rpc/svc_auth.h /usr/include/rpc/netdb.h
query_program.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
query_program.o: /usr/include/bits/confname.h
send_thresholds.o: /usr/include/stdlib.h /usr/include/features.h
send_thresholds.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
send_thresholds.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h apmcd.h
send_thresholds.o: /usr/include/rpc/rpc.h /usr/include/rpc/types.h
send_thresholds.o: /usr/include/sys/types.h /usr/include/bits/types.h
send_thresholds.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
send_thresholds.o: /usr/include/time.h /usr/include/sys/time.h
send_thresholds.o: /usr/include/bits/time.h /usr/include/sys/select.h
send_thresholds.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
send_thresholds.o: /usr/include/sys/param.h /usr/include/limits.h
send_thresholds.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
send_thresholds.o: /usr/include/linux/limits.h /usr/include/linux/param.h
send_thresholds.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
send_thresholds.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
send_thresholds.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
send_thresholds.o: /usr/include/stdint.h /usr/include/bits/wchar.h
send_thresholds.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
send_thresholds.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
send_thresholds.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
send_thresholds.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
send_thresholds.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
send_thresholds.o: /usr/include/endian.h /usr/include/bits/endian.h
send_thresholds.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
send_thresholds.o: /usr/include/stdio.h /usr/include/libio.h
send_thresholds.o: /usr/include/_G_config.h /usr/include/wchar.h
send_thresholds.o: /usr/include/gconv.h
send_thresholds.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
send_thresholds.o: /usr/include/bits/stdio_lim.h
send_thresholds.o: /usr/include/bits/sys_errlist.h /usr/include/rpc/auth.h
send_thresholds.o: /usr/include/rpc/clnt.h /usr/include/sys/un.h
send_thresholds.o: /usr/include/rpc/rpc_msg.h /usr/include/rpc/auth_unix.h
send_thresholds.o: /usr/include/rpc/auth_des.h /usr/include/rpc/svc.h
send_thresholds.o: /usr/include/rpc/svc_auth.h /usr/include/rpc/netdb.h
send_thresholds.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
send_thresholds.o: /usr/include/bits/confname.h
stop_program.o: /usr/include/stdlib.h /usr/include/features.h
stop_program.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
stop_program.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
stop_program.o: /usr/include/string.h /usr/include/sys/types.h
stop_program.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
stop_program.o: /usr/include/bits/typesizes.h /usr/include/time.h
stop_program.o: /usr/include/sys/wait.h /usr/include/signal.h
stop_program.o: /usr/include/bits/sigset.h /usr/include/bits/signum.h
stop_program.o: /usr/include/sys/resource.h /usr/include/bits/resource.h
stop_program.o: /usr/include/bits/time.h /usr/include/bits/waitflags.h
stop_program.o: /usr/include/bits/waitstatus.h /usr/include/errno.h
stop_program.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
stop_program.o: /usr/include/asm/errno.h /usr/include/asm-i486/errno.h
stop_program.o: /usr/include/asm-generic/errno.h
stop_program.o: /usr/include/asm-generic/errno-base.h apmcd.h
stop_program.o: /usr/include/rpc/rpc.h /usr/include/rpc/types.h
stop_program.o: /usr/include/sys/time.h /usr/include/sys/select.h
stop_program.o: /usr/include/bits/select.h /usr/include/sys/param.h
stop_program.o: /usr/include/limits.h
stop_program.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
stop_program.o: /usr/include/linux/limits.h /usr/include/linux/param.h
stop_program.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
stop_program.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
stop_program.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
stop_program.o: /usr/include/stdint.h /usr/include/bits/wchar.h
stop_program.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
stop_program.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
stop_program.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
stop_program.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
stop_program.o: /usr/include/asm-i486/sockios.h /usr/include/bits/in.h
stop_program.o: /usr/include/endian.h /usr/include/bits/endian.h
stop_program.o: /usr/include/bits/byteswap.h /usr/include/rpc/xdr.h
stop_program.o: /usr/include/stdio.h /usr/include/libio.h
stop_program.o: /usr/include/_G_config.h /usr/include/wchar.h
stop_program.o: /usr/include/gconv.h
stop_program.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
stop_program.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
stop_program.o: /usr/include/rpc/auth.h /usr/include/rpc/clnt.h
stop_program.o: /usr/include/sys/un.h /usr/include/rpc/rpc_msg.h
stop_program.o: /usr/include/rpc/auth_unix.h /usr/include/rpc/auth_des.h
stop_program.o: /usr/include/rpc/svc.h /usr/include/rpc/svc_auth.h
stop_program.o: /usr/include/rpc/netdb.h /usr/include/unistd.h
stop_program.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
test.o: /usr/include/stdlib.h /usr/include/features.h
test.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
test.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
test.o: /usr/include/string.h /usr/include/math.h
test.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
test.o: /usr/include/bits/mathcalls.h endcode.h /usr/include/unistd.h
test.o: /usr/include/bits/posix_opt.h /usr/include/bits/types.h
test.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
test.o: /usr/include/bits/confname.h /usr/include/stdio.h
test.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
test.o: /usr/include/bits/wchar.h /usr/include/gconv.h
test.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h
test.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
test.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/bits/time.h
test.o: /usr/include/sys/select.h /usr/include/bits/select.h
test.o: /usr/include/bits/sigset.h /usr/include/signal.h
test.o: /usr/include/bits/signum.h apmcd.h /usr/include/rpc/rpc.h
test.o: /usr/include/rpc/types.h /usr/include/sys/types.h
test.o: /usr/include/sys/param.h /usr/include/limits.h
test.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
test.o: /usr/include/linux/limits.h /usr/include/linux/param.h
test.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
test.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
test.o: /usr/include/asm-i486/autoconf.h /usr/include/netinet/in.h
test.o: /usr/include/stdint.h /usr/include/sys/socket.h
test.o: /usr/include/sys/uio.h /usr/include/bits/uio.h
test.o: /usr/include/bits/socket.h /usr/include/bits/sockaddr.h
test.o: /usr/include/asm/socket.h /usr/include/asm-i486/socket.h
test.o: /usr/include/asm/sockios.h /usr/include/asm-i486/sockios.h
test.o: /usr/include/bits/in.h /usr/include/endian.h
test.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
test.o: /usr/include/rpc/xdr.h /usr/include/rpc/auth.h
test.o: /usr/include/rpc/clnt.h /usr/include/sys/un.h
test.o: /usr/include/rpc/rpc_msg.h /usr/include/rpc/auth_unix.h
test.o: /usr/include/rpc/auth_des.h /usr/include/rpc/svc.h
test.o: /usr/include/rpc/svc_auth.h /usr/include/rpc/netdb.h
var.o: /usr/include/sys/socket.h /usr/include/features.h
var.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
var.o: /usr/include/sys/uio.h /usr/include/sys/types.h
var.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
var.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stddef.h
var.o: /usr/include/bits/typesizes.h /usr/include/time.h
var.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
var.o: /usr/include/limits.h
var.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/limits.h
var.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
var.o: /usr/include/asm-i486/socket.h /usr/include/asm/sockios.h
var.o: /usr/include/asm-i486/sockios.h /usr/include/netinet/in.h
var.o: /usr/include/stdint.h /usr/include/bits/wchar.h /usr/include/bits/in.h
var.o: /usr/include/endian.h /usr/include/bits/endian.h
var.o: /usr/include/bits/byteswap.h /usr/include/arpa/inet.h
var.o: /usr/lib/gcc/i486-linux-gnu/4.0.3/include/stdarg.h apmcd.h
var.o: /usr/include/rpc/rpc.h /usr/include/rpc/types.h /usr/include/stdlib.h
var.o: /usr/include/sys/time.h /usr/include/bits/time.h
var.o: /usr/include/sys/select.h /usr/include/bits/select.h
var.o: /usr/include/bits/sigset.h /usr/include/sys/param.h
var.o: /usr/include/linux/limits.h /usr/include/linux/param.h
var.o: /usr/include/asm/param.h /usr/include/asm-i486/param.h
var.o: /usr/include/linux/config.h /usr/include/linux/autoconf.h
var.o: /usr/include/asm-i486/autoconf.h /usr/include/rpc/xdr.h
var.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
var.o: /usr/include/wchar.h /usr/include/gconv.h
var.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
var.o: /usr/include/rpc/auth.h /usr/include/rpc/clnt.h /usr/include/sys/un.h
var.o: /usr/include/rpc/rpc_msg.h /usr/include/rpc/auth_unix.h
var.o: /usr/include/rpc/auth_des.h /usr/include/rpc/svc.h
var.o: /usr/include/rpc/svc_auth.h /usr/include/rpc/netdb.h
var.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
var.o: /usr/include/bits/confname.h
