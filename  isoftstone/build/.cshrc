#================================================================
#                                                               =
#  for d5000 system 
#  2009-10-12
#================================================================

umask 0002

alias ora 'setenv DATABASE oracle'
alias syb 'setenv DATABASE sybase'
setenv EXTSHM ON
setenv DATABASE oracle
setenv DB_TYPE dm
setenv OBJECT_DIR linux 
setenv APP_SYS_TYPE _APP_SYS_EMS
setenv NLS_DATE_FORMAT 'YYYY-MM-DD HH24:MI:SS'
#setenv QTDIR /home/d5000/qt453
setenv QTDIR /home/d5000/guodiao/wenkong/qt473
setenv QMAKESPEC $QTDIR/mkspecs/linux-g++
setenv QMAKE_CONFIG_PATH $QTDIR/lib
setenv D5000_HOME /home/d5000/guodiao
setenv D5000_HOME $D5000_HOME
setenv VIEW $D5000_HOME
setenv SRC_HOME $D5000_HOME/src
setenv OPEN2000E_HOME $D5000_HOME
setenv OPENWINHOME /usr/openwin
setenv PIHOME $HOME/piapi
setenv VISUAL_TYPE _QT_VISUAL
setenv NAS_DBSECS_HOME  $D5000_HOME/data
setenv NAS_SRC_HOME  $VIEW/src/advanced
#setenv GIS_TYPE    _QT_GIS

#wenkong

setenv VISDIR $HOME/vis
setenv VISDATAPATH /home/d5000/guodiao/data/graph_client
setenv QWTDIR $VISDIR/src/include/wams/vmi/qwt6.0.0

#end wenkong

limit coredumpsize 800000

setenv MANPATH /usr/openwin/share/man:/usr/man:/usr/vacpp/man:/usr/vac/man:$QTDIR/doc/man:/usr/share/man:/usr/X11R6/man
setenv LIBPATH /usr/shlib:/usr/ccs/lib:/usr/lib/cmplrs/cc:/usr/lib:/usr/local/lib:/var/shlib:/usr/local/perl/lib:/usr/openwin/lib:/usr/dt/lib:$QTDIR/lib:$QTDIR/qwt/lib:/users/sybase/lib:$D5000_HOME/lib/graph:$D5000_HOME/lib:$D5000_HOME/lib/lf:$PIHOME/lib:$VISDIR/lib

setenv LD_LIBRARY_PATH $VISDIR/lib:/lib:/usr/lib:$QTDIR/lib:$QTDIR/qwt/lib:/home/kingbase/dci:/home/kingbase/KingbaseES/bin:$D5000_HOME/src/lib:$D5000_HOME/lib/gis 

#=========================== path ================================
set path=($QTDIR/bin /bin /usr/bin /usr/dt/bin  /usr/ucb /usr/ccs/bin /etc /usr/sbin /sbin /usr/local/bin) 
set path=(/usr/local/valgrind/bin /usr/bin/X11 $OPENWINHOME/bin $QTDIR/bin $path)
set path=($D5000_HOME/bin/mmiexec/jdk/bin $path)
set path=($D5000_HOME/bin/mmiexec/scripts/linux  $path)
#set path=(/usr/java14/bin $path)
set path=(/opt/jdk1.5.0_19/jre/bin $path)
set path=(/users/sybase $path)
set path=(. $D5000_HOME/bin $D5000_HOME/lib $D5000_HOME/debug $HOME/ss40/bin $path)
set path=($D5000_HOME/../mozilla $QTDIR/bin $path)
set path=($D5000_HOME/bin /usr/vacpp/bin /usr/vac/bin $path)
set path=($D5000_HOME/qtcreator-1.0.0/bin $path)
set path=($D5000_HOME/data/dts/sbin  $path)
set path=($VISDIR/lib $path)
set path=($VISDIR/bin $path)
set HOST = `hostname`
set prompt = "// ${HOST}:$cwd % "

set cls = /usr/netscape/suitespot/docs/class

#========================== aliases  list  ========================
alias   cp      'cp -p'
alias   rcp     'rcp -p'
alias   ss      'showservice'
alias   dtterm 'dtterm -ls -sl 20000'
alias	bye	logout
alias	run	source
alias   cd      'cd \!* ;set prompt = "// ${HOST}:$cwd % "'
alias   grep    'grep -n'
alias	sys 	'cd $D5000_HOME/sys'
alias	conf 	'cd $D5000_HOME/conf'
alias	src 	'cd $D5000_HOME/src'
alias   bin 	'cd $D5000_HOME/bin'
alias   lib 	'cd $D5000_HOME/lib'
alias   sbin 	'cd $SRC_HOME/bin'
alias   slib 	'cd $SRC_HOME/lib'
alias	data 	'cd $D5000_HOME/data'
alias	plf 	'cd $D5000_HOME/src/platform'
alias	midserv 'cd $D5000_HOME/src/platform/service/midserv'
alias   sbus    'cd $D5000_HOME/src/platform/servicebus'
alias	rtdbms 	'cd $D5000_HOME/src/platform/rtdbms'
alias	hidb 	'cd $D5000_HOME/src/platform/rtdbms_hi'
alias   fml 	'cd $D5000_HOME/src/platform/service/formula_define'
alias   qt      'cd $QTDIR'
alias	sam 	'cd $D5000_HOME/src/platform/sys_admin/sysadmin'
alias   dbsrc   'cd $D5000_HOME/src/platform/data_srv'
alias   comsrv  'cd $D5000_HOME/src/platform/comsrv'
alias   disp    'setenv DISPLAY `who am i | cut -f2 -d"(" | cut -f1 -d")"`:0.0'
alias   findcc   'find . -name "*.cc" | xargs grep -n '
alias   findh    'find . -name "*.h" |xargs grep -n '
alias   findcpp   'find . -name "*.cpp" | xargs grep -n '
alias   rmmoc   'find . -name "*moc*" | xargs rm -r '
alias   rmvss   'find . -name "*.scc" | xargs rm '
alias   rmdsp   'find . -name "*.dsp" | xargs rm '
alias   rmdsw   'find . -name "*.dsw" | xargs rm ' 
alias   rmbak   'find . -name "*.bak*" | xargs rm -r '
alias   rmryuan   'find . -name "*ryuan*" | xargs rm -r '

alias	h	'history'
alias	scada	'cd $D5000_HOME/src/scada'
alias   graph   'cd $D5000_HOME/src/platform/graph'
alias   gdisp   'cd $D5000_HOME/src/platform/graph/DLL_SCADACallback'

alias ddts 'cd $D5000_HOME/src/dts'
alias dapp 'cd $D5000_HOME/src/dts/app'
alias dlib 'cd $D5000_HOME/src/dts/lib'

setenv TERM vt100

setenv MAIL /usr/spool/mail/$USER
setenv LD_LIBRARY_PATH ".:$D5000_HOME/lib:$D5000_HOME/lib/graph:$LD_LIBRARY_PATH"
set 	history=600
set	editmode = emacs
setenv _RLD_ARGS "-ignore_version libcurses.so"

alias	fes	'cd $D5000_HOME/src/fes'
alias	feslog	'cd $D5000_HOME/var/log/fes'
alias	fesconf	'cd $D5000_HOME/conf/fes'

#============================  sybase   ========================
setenv SYBASE /users/sybase

setenv LANG zh_CN
#setenv TMPL_REPOS_DIR "cxx_repository"

setenv DOC_LANG zh_CN
setenv NLSPATH /usr/lib/nls/msg/%L/%N:/usr/lib/nls/msg/%L/%N.cat

################################
# RTE settings
# ################################
setenv  dualNetFlag 0
setenv  Domain 2
setenv  PTHRTE $HOME/adm/rte/map/
setenv  OSADB $HOME/adm/osadb
setenv  RTELOGPATH $HOME/log/rte
setenv  RTECONFPATH $HOME/conf/msgbus/conf
setenv CASEDIR $HOME/adm/osadb/save
setenv RTEVERSION Ver1.0
setenv  OSABINPATH $HOME/bin


# model merge
setenv AREA fj
setenv CF_CONFIG /home/d5000/cimdata/CF
setenv  ORACLE_DIC_USER maintenance
setenv INTERBUS_ROOT  /data/users/interbus/InterESB2.0/bin
setenv CCAPI_FILEPATH  /home/d5000/cimdata
setenv TAR_FILEPATH  $CCAPI_FILEPATH/tarfiles
setenv MODEL_FILES  /home/d5000/cimdata
setenv CCAPI_E  $CCAPI_FILEPATH/version/online/efiles
setenv SVG_FILES  $CCAPI_FILEPATH/workspace/svgfiles

setenv  CF_CONFIG1 /home/d5000/cimdata/CF/test
setenv  MOD_USER inf_share
setenv  CIMDOMAIN_EXT cimNC
setenv  OUTDEF /home/d5000/bin
setenv  ENODE ems1
setenv  MAINTENANCE_SID o2001
setenv 	SVN_EDITOR vim

setenv WHDB /home/d5000/guodiao/conf/whdb/
