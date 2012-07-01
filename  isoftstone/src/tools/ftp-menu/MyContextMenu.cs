using System;
using System.Reflection;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;

using ShellLib;
using System.Drawing;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using Microsoft.Win32;

namespace MyContextMenu
{
    [Guid("18f8154b-5cdd-4733-94b8-c978f36623b3"), ComVisible(true)]
    public class MyContextMenu : IShellExtInit, IContextMenu, IPersistFile, IExtractIcon, IQueryInfo
    {
        private const string GUID = "{18f8154b-5cdd-4733-94b8-c978f36623b3}";
        private const string KEYNAME = "Ftp管理";
        const int S_OK = 0;
        const int S_FALSE = 1;
        private const uint E_NOTIMPL = 0x80004001;
        private const uint QITIPF_DEFAULT = 0;
        protected string szFileName;
        protected long lngFileSize;

        protected ShellLib.IDataObject m_dataObject = null;
        uint m_hDrop = 0;

        #region IContextMenu 接口实现

        int IContextMenu.QueryContextMenu(HMenu hMenu, uint iMenu, uint idCmdFirst, uint idCmdLast, CMF uFlags)
        {
            int id = 0;
            if ((uFlags & (CMF.CMF_VERBSONLY | CMF.CMF_DEFAULTONLY | CMF.CMF_NOVERBS)) == 0 ||
                (uFlags & CMF.CMF_EXPLORE) != 0)
            {
                //创建子菜单
                HMenu submenu = ShellLib.Helpers.CreatePopupMenu();
                Helpers.AppendMenu(submenu, MFMENU.MF_STRING, new IntPtr(idCmdFirst + id++), "上传");
                Helpers.AppendMenu(submenu, MFMENU.MF_STRING, new IntPtr(idCmdFirst + id++), "下载");
                Helpers.AppendMenu(submenu, MFMENU.MF_STRING, new IntPtr(idCmdFirst + id++), "查看远程文件");

                //将子菜单插入到上下文菜单中
                Helpers.InsertMenu(hMenu, 1, MFMENU.MF_BYPOSITION | MFMENU.MF_POPUP, submenu.handle, "FTP管理");

                //为菜单增加图标
                Bitmap bpCopy = Resource1.copy;
                Helpers.SetMenuItemBitmaps(submenu, 0, MFMENU.MF_BYPOSITION, bpCopy.GetHbitmap(), bpCopy.GetHbitmap());
                Helpers.SetMenuItemBitmaps(submenu, 1, MFMENU.MF_BYPOSITION, bpCopy.GetHbitmap(), bpCopy.GetHbitmap());
                Bitmap bpHome = Resource1.home;
                Helpers.SetMenuItemBitmaps(submenu, 2, MFMENU.MF_BYPOSITION, bpHome.GetHbitmap(), bpHome.GetHbitmap());
            }
            return id;
        }

        void IContextMenu.GetCommandString(uint idcmd, GCS uflags, uint reserved, IntPtr commandstring, int cchMax)
        {
            string tip = "";

            switch (uflags)
            {
                case GCS.VERB:
                    break;
                case GCS.HELPTEXTW:
                    switch (idcmd)
                    {
                        case 0:
                            tip = "上传";
                            break;
                        case 1:
                            tip = "下载";
                            break;
                        case 2:
                            tip = "查看";
                            break;
                        default:
                            break;
                    }
                    if (!string.IsNullOrEmpty(tip))
                    {
                        byte[] data = new byte[cchMax * 2];
                        Encoding.Unicode.GetBytes(tip, 0, tip.Length, data, 0);
                        Marshal.Copy(data, 0, commandstring, data.Length);
                    }
                    break;
            }
        }

        void IContextMenu.InvokeCommand(IntPtr pici)
        {
            INVOKECOMMANDINFO ici = (INVOKECOMMANDINFO)Marshal.PtrToStructure(pici, typeof(ShellLib.INVOKECOMMANDINFO));
            StringBuilder sb = new StringBuilder(1024);
            StringBuilder sbAll = new StringBuilder();
            uint nselected;

            switch (ici.verb)
            {
                case 0:
                    //上传
                    nselected = Helpers.DragQueryFile(m_hDrop, 0xffffffff, null, 0);
                    for (uint i = 0; i < nselected; i++)
                    {
                        ShellLib.Helpers.DragQueryFile(m_hDrop, i, sb, sb.Capacity + 1);
                        string filePath = sb.ToString();
                        IniWrapper ini = new IniWrapper("c:/log.ini");
                        ini.WriteValue("LOG","FILE",filePath);
                        UploadFile(filePath);
                    }
                    break;
                case 1:
                    //下载
                    nselected = Helpers.DragQueryFile(m_hDrop, 0xffffffff, null, 0);
                    for (uint i = 0; i < nselected; i++)
                    {
                        ShellLib.Helpers.DragQueryFile(m_hDrop, i, sb, sb.Capacity + 1);
                        string filePath = sb.ToString();
                        DownloadFile(filePath,false);
                    }
                    break;
                case 2:
                    {
                        //查看
                        IniWrapper ini = new IniWrapper("c:\\ftp.ini");
                        string tool = ini.ReadValue("FTP", "TOOL");
                        FileInfo info = new FileInfo(tool);
                        if (info.Exists == false)
                        {
                            tool = "notepad";
                        }

                        nselected = Helpers.DragQueryFile(m_hDrop, 0xffffffff, null, 0);
                        string args = "";
                        for (uint i = 0; i < nselected; i++)
                        {
                            ShellLib.Helpers.DragQueryFile(m_hDrop, i, sb, sb.Capacity + 1);
                            string filePath = sb.ToString();
                            DownloadFile(filePath, true);
                            args += filePath;
                            args += ".bak ";
                        }

                        Process proc = new Process();
                        proc.StartInfo.FileName = tool;
                        proc.StartInfo.Arguments = args;
                        proc.Start();
                    }

                    break;
                default:
                    break;
            }
        }

        #endregion

        #region IPersistFile 接口实现

        public uint GetClassID(out Guid pClassID)
        {
            pClassID = new Guid("18f8154b-5cdd-4733-94b8-c978f36623b3");

            return E_NOTIMPL;
        }

        public uint Load(string pszFileName, uint dwMode)
        {
            szFileName = pszFileName;

            return S_OK;
        }


        public uint IsDirty()
        {
            return E_NOTIMPL;

        }

        public uint Save(string pszFileName, bool fRemember)
        {
            return E_NOTIMPL;
        }

        public uint SaveCompleted(string pszFileName)
        {
            return E_NOTIMPL;
        }

        public uint GetCurFile(out string ppszFileName)
        {
            ppszFileName = null;

            return E_NOTIMPL;
        }

        #endregion

        #region IExtractIcon 接口实现

        int IExtractIcon.GetIconLocation(ExtractIconOptions uFlags, IntPtr szIconFile, uint cchMax, out int piIndex, out ExtractIconFlags pwFlags)
        {
            piIndex = -1;

            try
            {
                FileInfo f = new FileInfo(szFileName);
                lngFileSize = f.Length;
                pwFlags = ExtractIconFlags.DontCache | ExtractIconFlags.NotFilename;

                return S_OK;
            }
            catch { }

            pwFlags = ExtractIconFlags.None;
            return S_FALSE;
        }

        int IExtractIcon.Extract(string pszFile, uint nIconIndex, out Icon phiconLarge, out Icon phiconSmall, uint nIconSize)
        {
            phiconLarge = null;
            phiconSmall = null;

            try
            {
                if (lngFileSize > 16 * 1024)
                {
                    phiconLarge = Resource1._2;
                    phiconSmall = new Icon(Resource1._2, new Size(16, 16));
                }
                else if (lngFileSize > 0)
                {
                    phiconLarge = Resource1._1;
                    phiconSmall = new Icon(Resource1._1, new Size(16, 16));
                }
                else
                {
                    phiconLarge = Resource1._0;
                    phiconSmall = new Icon(Resource1._0, new Size(16, 16));
                }

                return S_OK;
            }
            catch { }

            return S_FALSE;
        }

        #endregion

        #region IQueryInfo 接口实现

        public uint GetInfoFlags(out uint dwFlags)
        {
            dwFlags = QITIPF_DEFAULT;

            return S_OK;
        }

        public uint GetInfoTip(uint dwFlags, out IntPtr pszInfoTip)
        {
            StreamReader sr = new StreamReader(szFileName, Encoding.GetEncoding("gb2312"));
            string text = sr.ReadToEnd();
            sr.Close();

            if (text.Length > 256)
            {
                text = text.Substring(0, 256) + "...";
            }

            string tip = "------------- 内容预览 -------------\r\n\r\n" + text;


            pszInfoTip = Marshal.StringToCoTaskMemUni(tip);

            return S_OK;
        } 

        #endregion

        #region IShellExtInit

        int IShellExtInit.Initialize(IntPtr pidlFolder, IntPtr lpdobj, uint hKeyProgID)
        {
            try
            {
                m_dataObject = null;
                if (lpdobj != (IntPtr)0)
                {
                    m_dataObject = (ShellLib.IDataObject)Marshal.GetObjectForIUnknown(lpdobj);
                    FORMATETC fmt = new FORMATETC();
                    fmt.cfFormat = CLIPFORMAT.CF_HDROP;
                    fmt.ptd = 0;
                    fmt.dwAspect = DVASPECT.DVASPECT_CONTENT;
                    fmt.lindex = -1;
                    fmt.tymed = TYMED.TYMED_HGLOBAL;
                    STGMEDIUM medium = new STGMEDIUM();
                    m_dataObject.GetData(ref fmt, ref medium);
                    m_hDrop = medium.hGlobal;
                }
            }
            catch (Exception)
            {
            }
            return S_OK;
        }

        #endregion

        #region Registration

        [System.Runtime.InteropServices.ComRegisterFunctionAttribute()]
        static void RegisterServer(String str1)
        {
            try
            {
                //注册 DLL
                RegistryKey root;
                RegistryKey rk;
                root = Registry.LocalMachine;
                rk = root.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved", true);
                rk.SetValue(GUID, KEYNAME);
                rk.Close();
                root.Close();

                //注册文件
                RegTXT();
               // RegFtpExtFile();
            }
            catch{
            }
        }

        [System.Runtime.InteropServices.ComUnregisterFunctionAttribute()]
        static void UnregisterServer(String str1)
        {
            try
            {
                //注销动态库
                RegistryKey root;
                RegistryKey rk;
                root = Registry.LocalMachine;
                rk = root.OpenSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved", true);
                rk.DeleteValue(GUID);
                rk.Close();
                root.Close();

                //注销文件
                UnRegTXT();
                //UnRegFtpExtFile();
            }
            catch
            {
            }
        }

        private static void RegAll()
        {
            RegistryKey rk, rk2;
            rk = Registry.ClassesRoot.OpenSubKey(@"*\shellex\ContextMenuHandlers", true);
            rk2 = rk.OpenSubKey(KEYNAME);
            if (rk2 == null)
                rk2 = rk.CreateSubKey(KEYNAME);
            rk2.SetValue("", GUID);
            rk2.Close();
            rk.Close();

            rk = Registry.ClassesRoot.OpenSubKey(@"Folder\shellex\ContextMenuHandlers", true);
            rk2 = rk.OpenSubKey(GUID);
            if (rk2 == null)
                rk2 = rk.CreateSubKey(GUID);
            rk2.SetValue("", "FTP管理");
            rk2.Close(); 
        }

        private static void UnRegAll()
        {
            RegistryKey rk;
            rk = Registry.ClassesRoot.OpenSubKey(@"*\shellex\ContextMenuHandlers", true);
            rk.DeleteSubKey(KEYNAME, false);
            rk.Close();
            rk = Registry.ClassesRoot.OpenSubKey(@"Folder\shellex\ContextMenuHandlers", true);
            rk.DeleteSubKey(GUID, false);
            rk.Close();
        }

        private static void RegTXT()
        {
            RegistryKey root;
            RegistryKey rk;

            root = Registry.ClassesRoot;
            rk = root.OpenSubKey(".xml");
            string txtclass = (string)rk.GetValue("");
            if (string.IsNullOrEmpty(txtclass))
            {
                txtclass = "xml";
                rk.SetValue("", txtclass);

            }
            rk.Close();

            rk = root.CreateSubKey(txtclass + "\\shellex\\ContextMenuHandlers\\" + KEYNAME);
            rk.SetValue("", GUID);
            rk.Close();

            rk = root.CreateSubKey(txtclass + "\\shellex\\IconHandler");
            rk.SetValue("", GUID);
            rk.Close();

            rk = root.CreateSubKey(txtclass + "\\shellex\\{00021500-0000-0000-C000-000000000046}");
            rk.SetValue("", GUID);
            rk.Close();
        }

        private static void UnRegTXT()
        {
            RegistryKey root;
            RegistryKey rk;

            root = Registry.ClassesRoot;
            rk = root.OpenSubKey(".xml");
            rk.Close();
            string txtclass = (string)rk.GetValue("");
            if (!string.IsNullOrEmpty(txtclass))
            {
                root.DeleteSubKey(txtclass + "\\shellex\\ContextMenuHandlers\\" + KEYNAME);
                root.DeleteSubKey(txtclass + "\\shellex\\IconHandler");
                root.DeleteSubKey(txtclass + "\\shellex\\{00021500-0000-0000-C000-000000000046}");
            }
        }


        private static void RegFileExt(string keyName, string subkey, string value, string guid)
        {
            RegistryKey root;
            RegistryKey rk;

            root = Registry.ClassesRoot;
            rk = root.OpenSubKey(subkey);
            string txtclass = (string)rk.GetValue("");
            if (string.IsNullOrEmpty(txtclass))
            {
                txtclass = value;
                rk.SetValue("", txtclass);

            }
            rk.Close();

            rk = root.CreateSubKey(txtclass + "\\shellex\\ContextMenuHandlers\\" + keyName);
            rk.SetValue("", guid);
            rk.Close();

            rk = root.CreateSubKey(txtclass + "\\shellex\\IconHandler");
            rk.SetValue("", guid);
            rk.Close();

            rk = root.CreateSubKey(txtclass + "\\shellex\\{00021500-0000-0000-C000-000000000046}");
            rk.SetValue("", guid);
            rk.Close();
        }

        private static void RegFtpExtFile()
        {
            RegFileExt(KEYNAME, "*.h", "H", GUID);
             RegFileExt(KEYNAME, "*.cpp", "CPP", GUID);
//             RegFileExt(KEYNAME, "*.pro", "PRO", GUID);
//             RegFileExt(KEYNAME, "*.ui", "UI", GUID);
//             RegFileExt(KEYNAME, "*.qrc", "QRC", GUID);
        }

        private static void UnRegExtFile(string keyName, string subkey)
        {
            RegistryKey root;
            RegistryKey rk;

            root = Registry.ClassesRoot;
            rk = root.OpenSubKey(subkey);
            rk.Close();
            string txtclass = (string)rk.GetValue("");
            if (!string.IsNullOrEmpty(txtclass))
            {
                root.DeleteSubKey(txtclass + "\\shellex\\ContextMenuHandlers\\" + keyName);
                root.DeleteSubKey(txtclass + "\\shellex\\IconHandler");
                root.DeleteSubKey(txtclass + "\\shellex\\{00021500-0000-0000-C000-000000000046}");
            }
        }

        private static void UnRegFtpExtFile()
        {
            UnRegExtFile(KEYNAME, "*.h");
             UnRegExtFile(KEYNAME, "*.cpp");
//             UnRegExtFile(KEYNAME, "*.pro");
//             UnRegExtFile(KEYNAME, "*.ui" );
//             UnRegExtFile(KEYNAME, "*.qrc");
        }


        private static void UploadFile(string fileName)
        {
            IniWrapper ini = new IniWrapper("c:\\ftp.ini");
            string host = ini.ReadValue("FTP", "HOST");
            string user = ini.ReadValue("FTP", "USER");
            string pass = ini.ReadValue("FTP", "PASS");
            string localpath = ini.ReadValue("FTP", "LOCALPATH");
            string remotepath = ini.ReadValue("FTP", "REMOTEPATH");
            FtpClient client = new FtpClient(host, user, pass);
            FileInfo info = new FileInfo(fileName);
            string relativePath = info.DirectoryName.Replace("\\", "/") + "/" + info.Name;
            relativePath = relativePath.Replace(localpath, "");
            string remoteFilePath = remotepath + relativePath;
            client.Upload(info, remoteFilePath);
        }

        private static void DownloadFile(string fileName,bool bRename)
        {
            IniWrapper ini = new IniWrapper("c:\\ftp.ini");
            string host = ini.ReadValue("FTP", "HOST");
            string user = ini.ReadValue("FTP", "USER");
            string pass = ini.ReadValue("FTP", "PASS");
            string localpath = ini.ReadValue("FTP", "LOCALPATH");
            string remotepath = ini.ReadValue("FTP", "REMOTEPATH");
            FtpClient client = new FtpClient(host, user, pass);
            FileInfo info = new FileInfo(fileName);
            string relativePath = info.DirectoryName.Replace("\\", "/") + "/" + info.Name;
            relativePath = relativePath.Replace(localpath, "");
            string remoteFilePath = remotepath + relativePath;
            string localName = fileName;
            if (bRename)
            {
                localName += ".bak";
            }
            client.Download(remoteFilePath, localName);
        }

        #endregion

    }
}
