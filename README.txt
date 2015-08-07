Program:
————————
url-engine.c

Language:
—————————
C

System:
———————
Linux and-sw-web1 2.6.18-348.3.1.el5 #1 SMP Tue Mar 5 13:19:32 EST 2013 x86_64 x86_64 x86_64 GNU/Linux

Compiler (gcc) info:
————————————————————
Using built-in specs.
Target: x86_64-redhat-linux
Configured with: ../configure --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --enable-shared --enable-threads=posix --enable-checking=release --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-libgcj-multifile --enable-languages=c,c++,objc,obj-c++,java,fortran,ada --enable-java-awt=gtk --disable-dssi --disable-plugin --with-java-home=/usr/lib/jvm/java-1.4.2-gcj-1.4.2.0/jre --with-cpu=generic --host=x86_64-redhat-linux
Thread model: posix
gcc version 4.1.2 20080704 (Red Hat 4.1.2-54)

Following format of XML file is assumed:
————————————————————————————————————————
<?xml version="1.0" encoding="UTF-8"?>
<patterns>
    <algo>posix</algo>
    <set1>   *.aaa.com   *.bb.cc/*   dup.com   </set1>
    <set2>  *.yahoo.com   *.google.com   dup.com  </set2>
</patterns>


How to compile:
———————————————
“cc url-engine.c -lxml2 -lz -lm -I/usr/include/libxml2 -o url-engine”

How to run:
———————————

USAGE: 
——————
url-engine <xml_file> <url_pattern_file> [posix]
Specify "posix" if you want to use POSIX regex library. It is optional.

1) ./url-engine configuration.xml example-url.txt
2) ./url-engine configuration.xml example-url.txt posix (To use POSIX regex library)

Unit Test:
——————————

Following content of exmaple-url.txt is used to test various cases:
————————————————————————————————————————————————————————————————————-
www.aaa.com
aa.bb.cc/ddx/eee
www.abc.com
xx.bb.cc/ddd
www.yahoo.com
dup.com

Sample output of the url-engine program with above inputs:
—————————————————————————————————————————————————————————
CMD: 
————
./url-engine configuration.xml example-url.txt

OUTPUT:
———————
url: www.aaa.com, pattern: *.aaa.com, set: 1
url: aa.bb.cc/ddx/eee, pattern: *.bb.cc/*, set: 1
url: xx.bb.cc/ddd, pattern: *.bb.cc/*, set: 1
url: www.yahoo.com, pattern: *.yahoo.com, set: 2
url: dup.com, pattern: dup.com, set: 1
url: dup.com, pattern: dup.com, set: 2


To use POSIX regex library, use the following CMD,

CMD:
————
./url-engine configuration.xml example-url.txt posix

OUTPUT:
———————
url: www.aaa.com, pattern: *.aaa.com, set: 1
url: aa.bb.cc/ddx/eee, pattern: *.bb.cc/*, set: 1
url: xx.bb.cc/ddd, pattern: *.bb.cc/*, set: 1
url: www.yahoo.com, pattern: *.yahoo.com, set: 2
url: dup.com, pattern: dup.com, set: 1
url: dup.com, pattern: dup.com, set: 2

