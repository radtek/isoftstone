svn export d:\svn_repos d:\export_svn
svn_sync d:\export_svn d:\other_dev_svn
svncommit.bat
svn commit -m "svnsync"