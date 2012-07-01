using System;
using System.Text;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using System.Drawing;


namespace ShellLib
{    

    #region Struct
    
    public struct HMenu
    {
        public HMenu(IntPtr x)
        {
            handle = x;
        }
        public IntPtr handle;
    }

    [StructLayout(LayoutKind.Sequential)]
	public struct RECT
	{
		public int left;
		public int top;
		public int right;
		public int bottom;
	}

    [StructLayout(LayoutKind.Sequential)]
    public struct DRAWITEMSTRUCT
    {
        public uint CtlType;
        public uint CtlID;
        public int itemID;
        public uint itemAction;
        public int itemState;
        public IntPtr hwndItem;
        public IntPtr hDC;
        public RECT rcItem;
        public IntPtr itemData;
    }

    [ComVisible(false), StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class LPCSHCOLUMNINIT
    {
        public uint dwFlags;
        public uint dwReserved;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
        public string wszFolder;
    }

    [ComVisible(false), StructLayout(LayoutKind.Sequential)]
    public struct SHCOLUMNID
    {
        public Guid fmtid;
        public uint pid;
    }

    [ComVisible(false), StructLayout(LayoutKind.Sequential)]
    public class LPCSHCOLUMNID
    {
        public Guid fmtid;
        public uint pid;
    }

    [ComVisible(false), StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode, Pack = 1)]
    public struct SHCOLUMNINFO
    {
        public SHCOLUMNID scid;
        public ushort vt;
        public LVCFMT fmt;
        public uint cChars;
        public SHCOLSTATE csFlags;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 80)]
        public string wszTitle;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string wszDescription;
    }

    [ComVisible(false), StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public class LPCSHCOLUMNDATA
    {
        public uint dwFlags;
        public uint dwFileAttributes;
        public uint dwReserved;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string pwszExt;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
        public string wszFile;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct MENUITEMINFO
    {
        public int cbSize;
        public uint fMask;
        public uint fType;
        public uint fState;
        public int wID;
        public IntPtr	/*HMENU*/	  hSubMenu;
        public IntPtr	/*HBITMAP*/   hbmpChecked;
        public IntPtr	/*HBITMAP*/	  hbmpUnchecked;
        public IntPtr	/*ULONG_PTR*/ dwItemData;
        public String dwTypeData;
        public uint cch;
        public IntPtr /*HBITMAP*/ hbmpItem;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct FORMATETC
    {
        public CLIPFORMAT cfFormat;
        public uint ptd;
        public DVASPECT dwAspect;
        public int lindex;
        public TYMED tymed;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct STGMEDIUM
    {
        public uint tymed;
        public uint hGlobal;
        public uint pUnkForRelease;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct INVOKECOMMANDINFO
    {
        public int cbSize;
        public uint fMask;
        public uint wnd;
        public int verb;
        [MarshalAs(UnmanagedType.LPStr)]
        public string parameters;
        [MarshalAs(UnmanagedType.LPStr)]
        public string directory;
        public int Show;
        public uint HotKey;
        public uint hIcon;
    }

    #endregion

    #region Enum

    [Flags]

    [ComVisible(false)]
    public enum LVCFMT
    {
        LEFT = 0x0000,
        RIGHT = 0x0001,
        CENTER = 0x0002,
        JUSTIFYMASK = 0x0003,
        IMAGE = 0x0800,
        BITMAP_ON_RIGHT = 0x1000,
        COL_HAS_IMAGES = 0x8000
    }

    [Flags]
    public enum CMIC : uint
    {
        HOTKEY = 0x00000020,
        ICON = 0x00000010,
        FLAG_NO_UI = 0x00000400,
        UNICODE = 0x00004000,
        NO_CONSOLE = 0x00008000,
        ASYNCOK = 0x00100000,
        NOZONECHECKS = 0x00800000,
        SHIFT_DOWN = 0x10000000,
        CONTROL_DOWN = 0x40000000,
        FLAG_LOG_USAGE = 0x04000000,
        PTINVOKE = 0x20000000
    }

    [Flags, ComVisible(false)]
    public enum SHCOLSTATE
    {
        TYPE_STR = 0x1,
        TYPE_INT = 0x2,
        TYPE_DATE = 0x3,
        TYPEMASK = 0xf,
        ONBYDEFAULT = 0x10,
        SLOW = 0x20,
        EXTENDED = 0x40,
        SECONDARYUI = 0x80,
        HIDDEN = 0x100,
        PREFER_VARCMP = 0x200
    }

    [Flags]
    public enum MFMENU : uint
    {
        MF_UNCHECKED = 0,
        MF_STRING = 0,
        MF_ENABLED = 0,
        MF_BYCOMMAND = 0,
        MF_GRAYED = 1,
        MF_DISABLED = 0x00000002,
        MF_CHECKED = 0x00000008,
        MF_POPUP = 0x00000010,
        MF_HILITE = 0x00000080,
        MF_BYPOSITION = 0x00000400,
        MF_SEPARATOR = 0x00000800,
    }

    [Flags]
    public enum MIIM : uint
    {
        STATE = 0x00000001,
        ID = 0x00000002,
        SUBMENU = 0x00000004,
        CHECKMARKS = 0x00000008,
        TYPE = 0x00000010,
        DATA = 0x00000020,
        STRING = 0x00000040,
        BITMAP = 0x00000080,
        FTYPE = 0x00000100
    }

    [Flags]
    public enum MF : uint
    {
        INSERT = 0x00000000,
        CHANGE = 0x00000080,
        APPEND = 0x00000100,
        DELETE = 0x00000200,
        REMOVE = 0x00001000,
        BYCOMMAND = 0x00000000,
        BYPOSITION = 0x00000400,
        SEPARATOR = 0x00000800,
        ENABLED = 0x00000000,
        GRAYED = 0x00000001,
        DISABLED = 0x00000002,
        UNCHECKED = 0x00000000,
        CHECKED = 0x00000008,
        USECHECKBITMAPS = 0x00000200,
        STRING = 0x00000000,
        BITMAP = 0x00000004,
        OWNERDRAW = 0x00000100,
        POPUP = 0x00000010,
        MENUBARBREAK = 0x00000020,
        MENUBREAK = 0x00000040,
        UNHILITE = 0x00000000,
        HILITE = 0x00000080,
        DEFAULT = 0x00001000,
        SYSMENU = 0x00002000,
        HELP = 0x00004000,
        RIGHTJUSTIFY = 0x00004000,
        MOUSESELECT = 0x00008000
    }

    [Flags]
    public enum MFS : uint
    {
        GRAYED = 0x00000003,
        DISABLED = MFS.GRAYED,
        CHECKED = MF.CHECKED,
        HILITE = MF.HILITE,
        ENABLED = MF.ENABLED,
        UNCHECKED = MF.UNCHECKED,
        UNHILITE = MF.UNHILITE,
        DEFAULT = MF.DEFAULT,
        MASK = 0x0000108B,
        HOTTRACKDRAWN = 0x10000000,
        CACHEDBMP = 0x20000000,
        BOTTOMGAPDROP = 0x40000000,
        TOPGAPDROP = 0x80000000,
        GAPDROP = 0xC0000000
    }

    public enum CLIPFORMAT : uint
    {
        CF_TEXT = 1,
        CF_BITMAP = 2,
        CF_METAFILEPICT = 3,
        CF_SYLK = 4,
        CF_DIF = 5,
        CF_TIFF = 6,
        CF_OEMTEXT = 7,
        CF_DIB = 8,
        CF_PALETTE = 9,
        CF_PENDATA = 10,
        CF_RIFF = 11,
        CF_WAVE = 12,
        CF_UNICODETEXT = 13,
        CF_ENHMETAFILE = 14,
        CF_HDROP = 15,
        CF_LOCALE = 16,
        CF_MAX = 17,

        CF_OWNERDISPLAY = 0x0080,
        CF_DSPTEXT = 0x0081,
        CF_DSPBITMAP = 0x0082,
        CF_DSPMETAFILEPICT = 0x0083,
        CF_DSPENHMETAFILE = 0x008E,

        CF_PRIVATEFIRST = 0x0200,
        CF_PRIVATELAST = 0x02FF,

        CF_GDIOBJFIRST = 0x0300,
        CF_GDIOBJLAST = 0x03FF
    }

    [Flags]
    public enum DVASPECT : uint
    {
        DVASPECT_CONTENT = 1,
        DVASPECT_THUMBNAIL = 2,
        DVASPECT_ICON = 4,
        DVASPECT_DOCPRINT = 8
    }

    public enum TYMED : uint
    {
        TYMED_HGLOBAL = 1,
        TYMED_FILE = 2,
        TYMED_ISTREAM = 4,
        TYMED_ISTORAGE = 8,
        TYMED_GDI = 16,
        TYMED_MFPICT = 32,
        TYMED_ENHMF = 64,
        TYMED_NULL = 0
    }

    [Flags]
    public enum CMF : uint
    {
        CMF_NORMAL = 0x00000000,
        CMF_DEFAULTONLY = 0x00000001,
        CMF_VERBSONLY = 0x00000002,
        CMF_EXPLORE = 0x00000004,
        CMF_NOVERBS = 0x00000008,
        CMF_CANRENAME = 0x00000010,
        CMF_NODEFAULT = 0x00000020,
        CMF_INCLUDESTATIC = 0x00000040,
        CMF_RESERVED = 0xffff0000
    }

    [Flags]
    public enum GCS : uint
    {
        VERBA = 0x00000000,
        HELPTEXTA = 0x00000001,
        VALIDATEA = 0x00000002,
        VERBW = 0x00000004,
        HELPTEXTW = 0x00000005,
        VALIDATEW = 0x00000006,
        UNICODE = 0x00000004,
        VERB = GCS.VERBA,
        HELPTEXT = GCS.HELPTEXTA,
        VALIDATE = GCS.VALIDATEA
    }

    [Flags]
    public enum ExtractIconOptions
    {
        OpenIcon = 0x0001,
        ForShell = 0x0002,
        Async = 0x0020,
        DefaultIcon = 0x0040,
        ForShortcut = 0x0080
    }

    [Flags]
    public enum ExtractIconFlags
    {
        None = 0x0000,
        SimulateDoc = 0x0001,	// simulate this document icon for this	}
        PerInstance = 0x0002,	// icons from this class are per instance (each file has its own)}
        PerClass = 0x0004,	// icons from this class per class (shared for all files of this type)
        NotFilename = 0x0008,	// location is not a filename, must call ::ExtractIcon
        DontCache = 0x0010	// this icon should not be cached
    }

    #endregion

    #region IDataObject

    [ComImport(), InterfaceType(ComInterfaceType.InterfaceIsIUnknown), GuidAttribute("0000010e-0000-0000-C000-000000000046")]
    public interface IDataObject
    {
        [PreserveSig()]
        int GetData(ref FORMATETC a, ref STGMEDIUM b);
        [PreserveSig()]
        void GetDataHere(int a, ref STGMEDIUM b);
        [PreserveSig()]
        int QueryGetData(int a);
        [PreserveSig()]
        int GetCanonicalFormatEtc(int a, ref int b);
        [PreserveSig()]
        int SetData(int a, int b, int c);
        [PreserveSig()]
        int EnumFormatEtc(uint a, ref Object b);
        [PreserveSig()]
        int DAdvise(int a, uint b, Object c, ref uint d);
        [PreserveSig()]
        int DUnadvise(uint a);
        [PreserveSig()]
        int EnumDAdvise(ref Object a);
    }

    #endregion

    #region IPersistFile

    [ComImport(), ComVisible(true), InterfaceType(ComInterfaceType.InterfaceIsIUnknown), GuidAttribute("0000010b-0000-0000-C000-000000000046")]
    public interface IPersistFile
    {
        [PreserveSig]
        uint GetClassID(out Guid pClassID);

        [PreserveSig]
        uint IsDirty();

        [PreserveSig]
        uint Load([In, MarshalAs(UnmanagedType.LPWStr)] string pszFileName, [In] uint dwMode);

        [PreserveSig]
        uint Save([In, MarshalAs(UnmanagedType.LPWStr)] string pszFileName, [In] bool fRemember);

        [PreserveSig]
        uint SaveCompleted([In, MarshalAs(UnmanagedType.LPWStr)] string pszFileName);

        [PreserveSig]
        uint GetCurFile([MarshalAs(UnmanagedType.LPWStr)] out string ppszFileName);
    }

    #endregion

    #region IShellExtInit

    [ComImport(), InterfaceType(ComInterfaceType.InterfaceIsIUnknown), GuidAttribute("000214e8-0000-0000-c000-000000000046")]
    public interface IShellExtInit
    {
        [PreserveSig()]
        int Initialize(IntPtr pidlFolder, IntPtr lpdobj, uint /*HKEY*/ hKeyProgID);
    }

    #endregion

    #region IContextMenu

    [ComImport(), InterfaceType(ComInterfaceType.InterfaceIsIUnknown), GuidAttribute("000214e4-0000-0000-c000-000000000046")]
    public interface IContextMenu
    {
        [PreserveSig()]
        int QueryContextMenu(HMenu hmenu, uint iMenu, uint idCmdFirst, uint idCmdLast, CMF uFlags);
        [PreserveSig()]
        void InvokeCommand(IntPtr pici);
        [PreserveSig()]
        void GetCommandString(uint idcmd, GCS uflags, uint reserved, IntPtr commandstring, int cchMax);
    }
    
    #endregion

    #region IContextMenu2

    [ComImport, Guid("000214f4-0000-0000-c000-000000000046")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IContextMenu2
    {
        [PreserveSig()]
        int QueryContextMenu(
            IntPtr hmenu,
            uint iMenu,
            uint idCmdFirst,
            uint idCmdLast,
            CMF uFlags);

        [PreserveSig()]
        int InvokeCommand(IntPtr pici);

        [PreserveSig()]
        int GetCommandString(
            uint idcmd,
            GCS uflags,
            uint reserved,
            [MarshalAs(UnmanagedType.LPWStr)]
            StringBuilder commandstring,
            int cch);

        [PreserveSig]
        int HandleMenuMsg(
            uint uMsg,
            IntPtr wParam,
            IntPtr lParam);
    } 

    #endregion

    #region IContextMenu3

    [ComImport, Guid("bcfce0a0-ec17-11d0-8d10-00a0c90f2719")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IContextMenu3
    {
        [PreserveSig()]
        int QueryContextMenu(
            HMenu hmenu,
            uint iMenu,
            uint idCmdFirst,
            uint idCmdLast,
            CMF uFlags);

        [PreserveSig()]
        int InvokeCommand(IntPtr pici);

        [PreserveSig()]
        int GetCommandString(
            uint idcmd,
            GCS uflags,
            uint reserved,
            [MarshalAs(UnmanagedType.LPWStr)]
            StringBuilder commandstring,
            int cch);

        [PreserveSig]
        int HandleMenuMsg(
            uint uMsg,
            IntPtr wParam,
            IntPtr lParam);

        [PreserveSig]
        int HandleMenuMsg2(
            uint uMsg,
            IntPtr wParam,
            IntPtr lParam,
            IntPtr plResult);
    } 

    #endregion

    #region IExtractIcon

    [ComVisible(true), ComImport, Guid("000214eb-0000-0000-c000-000000000046"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IExtractIcon
    {
        [PreserveSig]
        int GetIconLocation([In] ExtractIconOptions uFlags, 
            [In] IntPtr szIconFile, 
            [In] uint cchMax,
            [Out] out int piIndex, 
            [Out] out ExtractIconFlags pwFlags);

        [PreserveSig]
        int Extract([In, MarshalAs(UnmanagedType.LPWStr)] string pszFile, 
            uint nIconIndex, 
            [Out, MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef=typeof(IconMarshaler))] out Icon phiconLarge, 
            [Out, MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef=typeof(IconMarshaler))] out Icon phiconSmall, 
            [In] uint nIconSize);
    } 

    #endregion

    #region IQueryInfo

    [ComImport(), ComVisible(true), InterfaceType(ComInterfaceType.InterfaceIsIUnknown), GuidAttribute("00021500-0000-0000-c000-000000000046")]
    public interface IQueryInfo
    {
        [PreserveSig]
        uint GetInfoTip(uint dwFlags, out IntPtr pszInfoTip);

        [PreserveSig]
        uint GetInfoFlags(out uint dwFlags);
    } 

    #endregion

    #region Helpers

    public class Helpers
    {
        public const uint WM_DRAWITEM = 0x002b;
        public const uint WM_MEASUREITEM = 0x002c;

        [DllImport("shell32")]
        internal static extern uint DragQueryFile(uint hDrop, uint iFile, StringBuilder buffer, int cch);

        [DllImport("user32")]
        internal static extern HMenu CreatePopupMenu();

        [DllImport("user32")]
        internal static extern bool InsertMenuItem(HMenu hmenu, uint uposition, uint uflags, ref MENUITEMINFO mii);

        [DllImport("user32")]
        internal static extern bool AppendMenu(HMenu hmenu, MFMENU uflags, IntPtr uIDNewItemOrSubmenu, string text);

        [DllImport("user32")]
        internal static extern bool InsertMenu(HMenu hmenu, int position, MFMENU uflags, IntPtr uIDNewItemOrSubmenu, string text);

        [DllImport("user32")]
        internal static extern int SetMenuItemBitmaps(HMenu hmenu, int nPosition, MFMENU uflags, IntPtr hBitmapUnchecked, IntPtr hBitmapChecked);
    }
    
    #endregion

}
