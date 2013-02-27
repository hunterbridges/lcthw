set -e

./devpkg -S
./devpkg -F http://www.trieuvan.com/apache/apr/apr-1.4.6.tar.gz
./devpkg -B http://www.trieuvan.com/apache/apr/apr-1.4.6.tar.gz
./devpkg -I http://www.trieuvan.com/apache/apr/apr-1.4.6.tar.gz
./devpkg -L
