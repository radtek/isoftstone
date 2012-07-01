  if (WScript.Arguments.length == 0) {
      WScript.Echo("请输入参数！");
      WScript.quit();
  }
   else {
      var path = WScript.Arguments(0);
      var fso = new ActiveXObject("Scripting.FileSystemObject");
      var rootFolder = fso.getFolder(path);
      var folderList = new Array();
     folderList.push(rootFolder);
 
     var folder, fc;
     while (folderList.length > 0) {
         folder = folderList.pop();
         fc = new Enumerator(folder.SubFolders);
         while (!fc.atEnd()) {
             if (fc.item().name == ".svn") {
                 fso.deleteFolder(fc.item().path, true);
             }
             else {
                 folderList.push(fc.item());
             }
             fc.moveNext();
         }
     }
     WScript.Echo("完成！");
 }