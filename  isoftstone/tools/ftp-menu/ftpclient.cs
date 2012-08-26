using System;
using System.Collections.Generic;
using System.Net;
using System.IO;

namespace MyContextMenu
{
    ///<summary>
    /// FTP�ͻ��˲�����
    ///</summary>
    public class FtpClient
    {
        #region ���캯��
        ///<summary>
        /// ����FTP����
        ///<para>
        /// Ĭ�ϲ�ʹ��SSL,ʹ�ö����ƴ��䷽ʽ,ʹ�ñ���ģʽ
        ///</para>
        ///</summary>
        ///<param name="host">��������</param>
        ///<param name="userId">�û���</param>
        ///<param name="password">����</param>
        public FtpClient(string host, string userId, string password)
            : this(host, userId, password, 21, null, false, false, true)
        {
        }

        ///<summary>
        /// ����FTP����
        ///</summary>
        ///<param name="host">��������</param>
        ///<param name="userId">�û���</param>
        ///<param name="password">����</param>
        ///<param name="port">�˿�</param>
        ///<param name="enableSsl">����Ssl</param>
        ///<param name="proxy">����</param>
        ///<param name="useBinary">���������</param>
        ///<param name="usePassive">������ģʽ</param>
        public FtpClient(string host, string userId, string password, int port, IWebProxy proxy, bool enableSsl, bool useBinary, bool usePassive)
        {
            this.userId = userId;
            this.password = password;
            if (host.ToLower().StartsWith("ftp://"))
            {
                this.host = host;
            }
            else
            {
                this.host = "ftp://" + host;
            }
            this.port = port;
            this.proxy = proxy;
            this.enableSsl = enableSsl;
            this.useBinary = useBinary;
            this.usePassive = usePassive;
        }
        #endregion

        #region ����
        private string host = string.Empty;
        ///<summary>
        /// ����
        ///</summary>
        public string Host
        {
            get
            {
                return this.host ?? string.Empty;
            }
        }
        #endregion

        #region ��¼�û���
        private string userId = string.Empty;
        ///<summary>
        /// ��¼�û���
        ///</summary>
        public string UserId
        {
            get
            {
                return this.userId;
            }
        }
        #endregion

        #region ����
        private string password = string.Empty;
        ///<summary>
        /// ����
        ///</summary>
        public string Password
        {
            get
            {
                return this.password;
            }
        }
        #endregion

        #region ����
        IWebProxy proxy = null;
        ///<summary>
        /// ����
        ///</summary>
        public IWebProxy Proxy
        {
            get
            {
                return this.proxy;
            }
            set
            {
                this.proxy = value;
            }
        }
        #endregion

        #region �˿�
        private int port = 21;
        ///<summary>
        /// �˿�
        ///</summary>
        public int Port
        {
            get
            {
                return port;
            }
            set
            {
                this.port = value;
            }
        }
        #endregion

        #region �����Ƿ�����Ssl
        private bool enableSsl = false;
        ///<summary>
        /// EnableSsl 
        ///</summary>
        public bool EnableSsl
        {
            get
            {
                return enableSsl;
            }
        }
        #endregion

        #region ʹ�ñ���ģʽ
        private bool usePassive = true;
        ///<summary>
        /// ����ģʽ
        ///</summary>
        public bool UsePassive
        {
            get
            {
                return usePassive;
            }
            set
            {
                this.usePassive = value;
            }
        }
        #endregion

        #region �����Ʒ�ʽ
        private bool useBinary = true;
        ///<summary>
        /// �����Ʒ�ʽ
        ///</summary>
        public bool UseBinary
        {
            get
            {
                return useBinary;
            }
            set
            {
                this.useBinary = value;
            }
        }
        #endregion

        #region Զ��·��
        private string remotePath = "/";
        ///<summary>
        /// Զ��·��
        ///<para>
        ///     ����FTP�������ϵĵ�ǰ·��(������ / �� /a/../ ����ʽ)
        ///</para>
        ///</summary>
        public string RemotePath
        {
            get
            {
                return remotePath;
            }
            set
            {
                string result = "/";
                if (!string.IsNullOrEmpty(value) && value != "/")
                {
                    result = "/" + value.TrimStart('/').TrimEnd('/') + "/";
                }
                this.remotePath = result;
            }
        }
        #endregion

        #region ����һ��FTP����
        ///<summary>
        /// ����һ��FTP����
        ///</summary>
        ///<param name="url">�����ַ</param>
        ///<param name="method">���󷽷�</param>
        ///<returns>FTP����</returns>
        private FtpWebRequest CreateRequest(string url, string method)
        {
            //��������
            FtpWebRequest request = (FtpWebRequest)WebRequest.Create(url);
            request.Credentials = new NetworkCredential(this.userId, this.password);
            request.Proxy = this.proxy;
            request.KeepAlive = false;//����ִ�����֮��ر�����
            request.UseBinary = useBinary;
            request.UsePassive = usePassive;
            request.EnableSsl = enableSsl;
            request.Method = method;
            return request;
        }
        #endregion

        #region �ϴ�һ���ļ���Զ��·����
        ///<summary>
        /// ���ļ��ϴ���FTP��������RemotePath��
        ///</summary>
        ///<param name="localFile">�����ļ���Ϣ</param>
        ///<param name="remoteFileName">Ҫ���浽FTP�ļ��������ϵ�����</param>
        public bool Upload(FileInfo localFile, string remoteFileName)
        {
            bool result = false;
            if (localFile.Exists)
            {
                string url = Host.TrimEnd('/') + RemotePath + remoteFileName;
                FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.UploadFile);

                //�ϴ�����
                using (Stream rs = request.GetRequestStream())
                using (FileStream fs = localFile.OpenRead())
                {
                    byte[] buffer = new byte[4096];//4K
                    int count = fs.Read(buffer, 0, buffer.Length);
                    while (count > 0)
                    {
                        rs.Write(buffer, 0, count);
                        count = fs.Read(buffer, 0, buffer.Length);
                    }
                    fs.Close();
                    result = true;
                }
                return result;
            }
            throw new Exception(string.Format("�����ļ�������,�ļ�·��:{0}", localFile.FullName));
        }
        #endregion

        #region ��FTP�������������ļ�
        ///<summary>
        /// �ӵ�ǰĿ¼�������ļ�
        ///<para>
        /// ��������ļ�����,��ӱ����ļ�������λ�ÿ�ʼ����.
        ///</para>
        ///</summary>
        ///<param name="serverName">�������ϵ��ļ�����</param>
        ///<param name="localName">�����ļ�����</param>
        ///<returns>����һ��ֵ,ָʾ�Ƿ����سɹ�</returns>
        public bool Download(string serverName, string localName)
        {
            bool result = false;
            using (FileStream fs = new FileStream(localName, FileMode.OpenOrCreate)) //������򿪱����ļ�
            {
                //��������
                string url = Host.TrimEnd('/') + RemotePath + serverName;
                FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.DownloadFile);
                request.ContentOffset = fs.Length;
                using (FtpWebResponse response = (FtpWebResponse)request.GetResponse())
                {
                    fs.Position = fs.Length;
                    byte[] buffer = new byte[4096];//4K
                    int count = response.GetResponseStream().Read(buffer, 0, buffer.Length);
                    while (count > 0)
                    {
                        fs.Write(buffer, 0, count);
                        count = response.GetResponseStream().Read(buffer, 0, buffer.Length);
                    }
                    response.GetResponseStream().Close();
                }
                result = true;
            }
            return result;
        }
        #endregion

        #region ������FTP�������ϵ��ļ�
        ///<summary>
        /// �ļ�����
        ///</summary>
        ///<param name="oldFileName">ԭ�ļ���</param>
        ///<param name="newFileName">���ļ���</param>
        ///<returns>����һ��ֵ,ָʾ�����Ƿ�ɹ�</returns>
        public bool Rename(string oldFileName, string newFileName)
        {
            bool result = false;
            //��������
            string url = Host.TrimEnd('/') + RemotePath + oldFileName;
            FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.Rename);
            request.RenameTo = newFileName;
            using (FtpWebResponse response = (FtpWebResponse)request.GetResponse())
            {
                result = true;
            }
            return result;
        }
        #endregion

        #region �ӵ�ǰĿ¼�»�ȡ�ļ��б�
        ///<summary>
        /// ��ȡ��ǰĿ¼���ļ��б�
        ///</summary>
        ///<returns></returns>
        public List<string> GetFileList()
        {
            List<string> result = new List<string>();
            //��������
            string url = Host.TrimEnd('/') + RemotePath;
            FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.ListDirectory);
            using (FtpWebResponse response = (FtpWebResponse)request.GetResponse())
            {
                StreamReader reader = new StreamReader(response.GetResponseStream(), System.Text.Encoding.Default);//�����ļ���
                string line = reader.ReadLine();
                while (line != null)
                {
                    result.Add(line);
                    line = reader.ReadLine();
                }
            }
            return result;
        }
        #endregion

        #region ��FTP�������ϻ�ȡ�ļ����ļ����б�
        ///<summary>
        /// ��ȡ��ϸ�б�
        ///</summary>
        ///<returns></returns>
        public List<string> GetFileDetails()
        {
            List<string> result = new List<string>();
            //��������
            string url = Host.TrimEnd('/') + RemotePath;
            FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.ListDirectoryDetails);
            using (FtpWebResponse response = (FtpWebResponse)request.GetResponse())
            {
                StreamReader reader = new StreamReader(response.GetResponseStream(), System.Text.Encoding.Default);//�����ļ���
                string line = reader.ReadLine();
                while (line != null)
                {
                    result.Add(line);
                    line = reader.ReadLine();
                }
            }
            return result;
        }
        #endregion

        #region ��FTP��������ɾ���ļ�
        ///<summary>
        /// ɾ��FTP�������ϵ��ļ�
        ///</summary>
        ///<param name="fileName">�ļ�����</param>
        ///<returns>����һ��ֵ,ָʾ�Ƿ�ɾ���ɹ�</returns>
        public bool DeleteFile(string fileName)
        {
            bool result = false;
            //��������
            string url = Host.TrimEnd('/') + RemotePath + fileName;
            FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.DeleteFile);
            using (FtpWebResponse response = (FtpWebResponse)request.GetResponse())
            {
                result = true;
            }

            return result;
        }
        #endregion

        #region ��FTP�������ϴ���Ŀ¼
        ///<summary>
        /// �ڵ�ǰĿ¼�´����ļ���
        ///</summary>
        ///<param name="dirName">�ļ�������</param>
        ///<returns>����һ��ֵ,ָʾ�Ƿ񴴽��ɹ�</returns>
        public bool MakeDirectory(string dirName)
        {
            bool result = false;
            //��������
            string url = Host.TrimEnd('/') + RemotePath + dirName;
            FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.MakeDirectory);
            using (FtpWebResponse response = (FtpWebResponse)request.GetResponse())
            {
                result = true;
            }
            return result;
        }
        #endregion

        #region ��FTP��������ɾ��Ŀ¼
        ///<summary>
        /// ɾ���ļ���
        ///</summary>
        ///<param name="dirName">�ļ�������</param>
        ///<returns>����һ��ֵ,ָʾ�Ƿ�ɾ���ɹ�</returns>
        public bool DeleteDirectory(string dirName)
        {
            bool result = false;
            //��������
            string url = Host.TrimEnd('/') + RemotePath + dirName;
            FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.RemoveDirectory);
            using (FtpWebResponse response = (FtpWebResponse)request.GetResponse())
            {
                result = true;
            }
            return result;
        }
        #endregion

        #region ��FTP�������ϻ�ȡ�ļ���С
        ///<summary>
        /// ��ȡ�ļ���С
        ///</summary>
        ///<param name="fileName"></param>
        ///<returns></returns>
        public long GetFileSize(string fileName)
        {
            long result = 0;
            //��������
            string url = Host.TrimEnd('/') + RemotePath + fileName;
            FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.GetFileSize);
            using (FtpWebResponse response = (FtpWebResponse)request.GetResponse())
            {
                result = response.ContentLength;
            }

            return result;
        }
        #endregion

        #region ��FTP�������ϵ��ļ�׷������
        ///<summary>
        /// ��FTP�������ϵ��ļ�׷������
        ///</summary>
        ///<param name="localFile">�����ļ�</param>
        ///<param name="remoteFileName">FTP�������ϵ��ļ�</param>
        ///<returns>����һ��ֵ,ָʾ�Ƿ�׷�ӳɹ�</returns>
        public bool Append(FileInfo localFile, string remoteFileName)
        {
            if (localFile.Exists)
            {
                using (FileStream fs = new FileStream(localFile.FullName, FileMode.Open))
                {
                    return Append(fs, remoteFileName);
                }
            }
            throw new Exception(string.Format("�����ļ�������,�ļ�·��:{0}", localFile.FullName));
        }

        ///<summary>
        /// ��FTP�������ϵ��ļ�׷������
        ///</summary>
        ///<param name="stream">������(��ͨ������ƫ����ʵ�ִ��ض�λ�ÿ�ʼ�ϴ�)</param>
        ///<param name="remoteFileName">FTP�������ϵ��ļ�</param>
        ///<returns>����һ��ֵ,ָʾ�Ƿ�׷�ӳɹ�</returns>
        public bool Append(Stream stream, string remoteFileName)
        {
            bool result = false;
            if (stream != null && stream.CanRead)
            {
                //��������
                string url = Host.TrimEnd('/') + RemotePath + remoteFileName;
                FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.AppendFile);
                using (Stream rs = request.GetRequestStream())
                {
                    //�ϴ�����
                    byte[] buffer = new byte[4096];//4K
                    int count = stream.Read(buffer, 0, buffer.Length);
                    while (count > 0)
                    {
                        rs.Write(buffer, 0, count);
                        count = stream.Read(buffer, 0, buffer.Length);
                    }
                    result = true;
                }
            }
            return result;
        }
        #endregion

        #region ��ȡFTP�������ϵĵ�ǰ·��
        ///<summary>
        /// ��ȡFTP�������ϵĵ�ǰ·��
        ///</summary>
        public string CurrentDirectory
        {
            get
            {
                string result = string.Empty;
                string url = Host.TrimEnd('/') + RemotePath;
                FtpWebRequest request = CreateRequest(url, WebRequestMethods.Ftp.PrintWorkingDirectory);
                using (FtpWebResponse response = (FtpWebResponse)request.GetResponse())
                {
                    string temp = response.StatusDescription;
                    int start = temp.IndexOf('"') + 1;
                    int end = temp.LastIndexOf('"');
                    if (end >= start)
                    {
                        result = temp.Substring(start, end - start);
                    }
                }
                return result;

            }
        }
        #endregion

        #region ��鵱ǰ·�����Ƿ����ĳ���ļ�
        ///<summary>
        /// ����ļ��Ƿ����
        ///</summary>
        ///<param name="fileName">Ҫ�����ļ���</param>
        ///<returns>����һ��ֵ,ָʾҪ�����ļ��Ƿ����</returns>
        public bool CheckFileExist(string fileName)
        {
            bool result = false;
            if (fileName != null && fileName.Trim().Length > 0)
            {
                fileName = fileName.Trim();
                List<string> files = GetFileList();
                if (files != null && files.Count > 0)
                {
                    foreach (string file in files)
                    {
                        if (file.ToLower() == fileName.ToLower())
                        {
                            result = true;
                            break;
                        }
                    }
                }
            }
            return result;
        }
        #endregion

    }
}
