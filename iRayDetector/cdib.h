// cdib.h ��CDib�������ݺͺ������н�������

#ifndef _INSIDE_VISUAL_CPP_CDIB
#define _INSIDE_VISUAL_CPP_CDIB

class CDib : public CObject
{
public:
	enum Alloc {noAlloc, crtAlloc, heapAlloc};	// ö�����ͣ���ʾ�ڴ�����״��
	DECLARE_SERIAL(CDib)
public:
	LPVOID m_lpvColorTable;						// ��ɫ��ָ��
	HBITMAP m_hBitmap;							// BITMAP�ṹָ��
	LPBYTE m_lpImage;							// DIBλͼ���ݿ��ַ
	LPBITMAPINFOHEADER m_lpBMIH;				// DIB��Ϣͷָ��
	HGLOBAL m_hGlobal;							// ȫ�ֵľ���������ڴ�ӳ���ļ���	                   
	Alloc m_nBmihAlloc;							// ��ʾ��Ϣͷ�ڴ�����״��
	Alloc m_nImageAlloc;						// ��ʾλͼ���ݷ����״��
	DWORD m_dwSizeImage;						// DIBλͼ�е��ֽ�������Ϣͷ�͵�ɫ�����ݳ��⣩
	int m_nColorTableEntries;					// ��ɫ�������
	
	HANDLE m_hFile;								// �ļ����
	HANDLE m_hMap;								// �ڴ�ӳ���ļ����
	LPVOID m_lpvFile;							// �ļ����
	HPALETTE m_hPalette;						// ��ɫ����
public:
	// ��ȡ������ʵ����ɫֵ
	RGBQUAD GetPixel(int x, int y);				

	// ��ȡ������ͼ�����ݿ��е�λ��
	LONG GetPixelOffset(int  x, int y);			
	
	// ��ȡDIBλͼ���ݿ�Ĵ洢�ߴ�
	CSize GetDibSaveDim();	
	
	// �ж�DIB�Ƿ�Ϊ��
	BOOL IsEmpty();	
	
	// �����ɫ��ı�����
	WORD PaletteSize();	
	
	// ���캯��
	CDib();	
	// �������캯��
	CDib(CDib &Backup);
	// ����ָ����λͼ�ߴ������λ��������CDibʵ��
	CDib(CSize size, int nBitCount);
	// ��������
	~CDib();									

	// ��ȡDIBλͼ�����ݵ��ֽ���
	int GetSizeImage() {return m_dwSizeImage;}	
	// ��ȡ��Ϣͷ�͵�ɫ��ĳߴ�
	int GetSizeHeader()							
		{return sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;}
	// ��ȡ�����ر�ʾ��DIB�Ŀ�Ⱥ͸߶�
	CSize GetDimensions();						

	// �Զ�ģʽ���ڴ�ӳ���ļ�����������CDib������й���]
	BOOL AttachMapFile(const char* strPathname, BOOL bShare = FALSE);
	
	//����һ���µ��ڴ�ӳ���ļ������������ݵĸ���
	BOOL CopyToMapFile(const char* strPathname);

	// ���ڴ��е�DIB�����е�CDib�������
	BOOL AttachMemory(LPVOID lpvMem, BOOL bMustDelete = FALSE, HGLOBAL hGlobal = NULL);

	// ��CDib������ָ���ĳߴ��������ʾ�������ߴ�ӡ����
	BOOL Draw(CDC* pDC, CPoint origin, CSize size);// until we implemnt CreateDibSection

	// ����һ��DIB�̣�ͼ���ڴ潫������ʼ��
	HBITMAP CreateSection(CDC* pDC = NULL);		

	// ��CDib������߼���ɫ��ѡ���豸�����ģ�Ȼ��ʵ�ָõ�ɫ��
	UINT UsePalette(CDC* pDC, BOOL bBackground = FALSE);

	// �����ɫ����ڵĻ�����ȡ��ɫ�壬������һ��Windows��ɫ��
	BOOL MakePalette();

	// ���16bpp��24bpp��32bppDIB���ٱ���ɫ�壬��ú�������ΪCDib���󴴽�һ���߼���ɫ�壬
	// ������CreatehalftonePalette�������صĵ�ɫ����ƥ�䡣���������256ɫ��ɫ����ʾ����
	// ���У�������û�е���SetSystemPalette����ô���㽫�������κε�ɫ�壬ֻ��20�б�׼��
	// Windows��ɫ������DIB��
 	BOOL SetSystemPalette(CDC* pDC);

	// ��DIB��������Ϊѹ���Ļ��߲�ѹ����DIB��
	BOOL Compress(CDC* pDC, BOOL bCompress = TRUE); 

	// ���Ժ��DIB�д���DDBλͼ��ʵ��DIB��DDB��ת��
	HBITMAP CreateBitmap(CDC* pDC);

	// ��DDB�д���DIB��ʵ��DDB��DIB��ת��
	BOOL ConvertFromDDB(HBITMAP hBitmap, HPALETTE hPal);

	// ���ļ��ж�ȡ���ݣ�������ļ�ͷ����Ϣͷ����ɫ���λͼ����
	BOOL Read(CFile* pFile);

	// ��BMP�ļ��ж�ȡ��Ϣͷ������CreateDIBSection������λͼ�����ڴ棬Ȼ��λͼ�Ӹ��ļ�����ղŷ�����ڴ�
	BOOL ReadSection(CFile* pFile, CDC* pDC = NULL);

	// ��DIB��CDib����д���ļ�
	BOOL Write(CFile* pFile);

	// ���л�����
	void Serialize(CArchive& ar);

	// ���DIB���ͷ��Ѿ�������ڴ棬���ҹر�ӳ���ļ�
	void Empty();

	// �����ɫ��ĳߴ�
	void ComputePaletteSize(int nBitCount);
private:
	// �Ͽ�ӳ���ļ��Ĺ���
	void DetachMapFile();
	
	// �����ɫ���λͼ�ߴ�
	void ComputeMetrics();
};
#endif // _INSIDE_VISUAL_CPP_CDIB
