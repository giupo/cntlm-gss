# cntlm-gss

This is [Cntlm](http://cntlm.sourceforge.net/) **with Kerberos patch applied**, and **syslog** logging removed.

 - Works on a Ubuntu 12.04 box, at least for me.
 - Works on a RedHat EL 7.9, at least for @giupo.

Dependency: 
  - [Kerberos](https://web.mit.edu/kerberos/).
  - [zf_log](https://github.com/wonder-mice/zf_log)

#  How to compile

**FIRST OF ALL** : clonw this repo with:

`git clone --recursive https://github.com/giupo/cntlm-gss`

(we have a dependency on zf_log)

After cloning, do the usual `cmake` dance (assuming you are in the project root):

  ```
  mkdir build && cd build
  cmake ..
  make
  ```

The compiled `cntlm` executable is under `build/src`: to run it, try `src/cntlm --help` or `src/cntlm -v`
and fix whatever it complains.

# Kerberos support

If you need kerberos support, modify the previous `cmake ..` command with `cmake .. -DWITH_KERBEROS` and compile with `make` as usual.

# configuration file

I have only the following lines in my ctnlm.conf file:

  ```
  Username	
  Domain		
  Password	
  Proxy		proxy.server.domain.com:3128
  NoProxy		localhost, 127.0.0.*, 10.*, 192.168.*
  Listen		3128
  ```

The username, domain and password are all erased for good.

I could start it with `src/cntlm -a gss -c /path/to/cntlm.conf` .
