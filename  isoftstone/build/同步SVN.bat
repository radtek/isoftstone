cd /d d:
rmdir export_dev /s /q
mkdir export_dev

svn export d:\vis_dev\backup d:\export_dev\backup
svn export d:\vis_dev\include d:\export_dev\include
svn export d:\vis_dev\src d:\export_dev\src
svn export d:\vis_dev\proj d:\export_dev\proj
svn export d:\vis_dev\config d:\export_dev\config
svn export d:\vis_dev\images d:\export_dev\images
svn export d:\vis_dev\bin d:\export_dev\bin
svn export d:\vis_dev\lib d:\export_dev\lib
svn export d:\vis_dev\build d:\export_dev\build
svn export d:\vis_dev\doc d:\export_dev\doc

svn_sync D:\export_dev\ D:\lcsh\vis

./svncommit.bat
del svncommit.bat


@pause