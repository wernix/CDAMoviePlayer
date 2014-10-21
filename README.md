CDAMoviePlayer
==============
<info><b>CDA Movie Player</b> is simple and small application to watching your fauvorite movies in MPlayer. At now you can run app, search and play movie <b>WITHOUT BROWSER</b>!</info>

<p><b>Requirements:</b><br>
mplayer, libcurl-dev(libcurl4-gnutls-dev), libboost-regex-dev, Qt5 with qmake</p>

<p><b>How to compile/install:</b><br>
1. Add QTDIR  to your system variables<br>
example QTDIR=/home/user/Qt5.3.2/5.3<br>
<code>$ export QTDIR=<path_to_qt></code><br>
2. Install requirements packages<br>
<code>$ sudo apt-get install mplayer libcurl4-gnutls-dev libboost-regex1.49-dev</code><br>
3. Run ./install in CDAMoviePlayer dir<br>
<code>$ ./install</code><br>
4. If make has done without errors you can run CDAMoviePlayer from bin dir<br>
<code>$ cd bin && ./CDAMoviePlayer</code><br>
5. Now you can start watching movies from cda:)</p>
