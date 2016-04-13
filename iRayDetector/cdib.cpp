// cdib.cpp

//======================================================================
//2011-09-01 ע�͵���
			//#include "GlobalApi.h"
			//����BOOL CDib::ConvertFromDDB(HBITMAP hBitmap, HPALETTE hPal)
//======================================================================

#include "stdafx.h"
#include "math.h"
#include "process.h"

#include "cdib.h"
//#include "GlobalApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// �������л�����
IMPLEMENT_SERIAL(CDib, CObject, 0);


/*************************************************************************
 *
 * \�������ƣ�
 *   CDib()
 *
 * \�������:
 * ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ���캯��
 *
 ************************************************************************
 */
CDib::CDib()
{
	m_hFile      = NULL;
	m_hBitmap    = NULL;
	m_hPalette   = NULL;
	m_nBmihAlloc = m_nImageAlloc = noAlloc;
	Empty();
}

/*************************************************************************
 *
 * \�������ƣ�
 *   CDib()
 *
 * \�������:
 *   CDib Backup
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   �������캯��
 *
 ************************************************************************
 */
CDib::CDib(CDib &Backup)
{
	m_dwSizeImage= Backup.m_dwSizeImage;
	m_hFile      = Backup.m_hFile;
	m_hBitmap    = Backup.m_hBitmap;
	m_hGlobal	 = Backup.m_hGlobal;
	m_hMap		 = Backup.m_hMap;
	m_hPalette   = Backup.m_hPalette;
	m_lpBMIH	 = Backup.m_lpBMIH;
	m_lpvColorTable=Backup.m_lpvColorTable;
	m_lpvFile	 = Backup.m_lpvFile;
	m_nColorTableEntries=Backup.m_nColorTableEntries;
	m_nBmihAlloc = Backup.m_nBmihAlloc;
	m_nImageAlloc= Backup.m_nImageAlloc;
	Empty();
}

/*************************************************************************
 *
 * \�������ƣ�
 *   CDib()
 *
 * \�������:
 * CSize	size			- λͼ�ߴ�
 * int		nBitCount		- ����λ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ���캯��
 *   ���ݸ�����λͼ�ߴ������λ������CDib���󣬲�����Ϣͷ�͵�ɫ������ڴ�
 *   ����û�и�λͼ���ݷ����ڴ�
 *
 ************************************************************************
 */
CDib::CDib(CSize size, int nBitCount)
{
	m_hFile      = NULL;
	m_hBitmap    = NULL;
	m_hPalette   = NULL;
	m_nBmihAlloc = m_nImageAlloc = noAlloc;
	Empty();

	// ��������λ�������ɫ��ߴ�
	ComputePaletteSize(nBitCount);

	// ����DIB��Ϣͷ�͵�ɫ����ڴ�
	m_lpBMIH = (LPBITMAPINFOHEADER) new 
		char[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries];

	// ������Ϣͷ�ڴ����״̬
	m_nBmihAlloc = crtAlloc;

	// ������Ϣͷ�е���Ϣ
	m_lpBMIH->biSize	= sizeof(BITMAPINFOHEADER);
	m_lpBMIH->biWidth	= size.cx;
	m_lpBMIH->biHeight	= size.cy;
	m_lpBMIH->biPlanes	= 1;
	m_lpBMIH->biBitCount	= nBitCount;
	m_lpBMIH->biCompression = BI_RGB;
	m_lpBMIH->biSizeImage	= 0;
	m_lpBMIH->biXPelsPerMeter = 0;
	m_lpBMIH->biYPelsPerMeter = 0;
	m_lpBMIH->biClrUsed	= m_nColorTableEntries;
	m_lpBMIH->biClrImportant= m_nColorTableEntries;

	// ����ͼ�������ڴ�Ĵ�С�������ô�DIB�ĵ�ɫ���ָ��
	ComputeMetrics();

	// ����DIB�ĵ�ɫ���ʼ��Ϊ0
	memset(m_lpvColorTable, 0, sizeof(RGBQUAD) * m_nColorTableEntries);

	// ��ʱ������ͼ�������ڴ�
	m_lpImage = NULL; 
}


/*************************************************************************
 *
 * \�������ƣ�
 *   ~CDib()
 *
 * \�������:
 * ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   �������������ͷ����з����DIB�ڴ�
 *
 ************************************************************************
 */
CDib::~CDib()
{
	Empty();
}


/*************************************************************************
 *
 * \�������ƣ�
 *   GetDimensions()
 *
 * \�������:
 *   ��
 *
 * \����ֵ:
 *   CSize				- DIB�Ŀ�Ⱥ͸߶�
 *
 * \˵��:
 *   ���������ر�ʾ��DIB�Ŀ�Ⱥ͸߶�
 *
 ************************************************************************
 */
CSize CDib::GetDimensions()
{	
	if(m_lpBMIH == NULL) return CSize(0, 0);
	return CSize((int) m_lpBMIH->biWidth, (int) m_lpBMIH->biHeight);
}


/*************************************************************************
 *
 * \�������ƣ�
 *   AttachMapFile()
 *
 * \�������:
 *   const	char* strPathname		- ӳ���ļ���·����
 *   BOOL	bShare				- ����ļ��Թ�����ʽ�򿪣�����ΪTRUE
 *						- Ĭ��ֵΪFALSE
 *
 * \����ֵ:
 *   BOOL					- ����ɹ�����ΪTRUE 
 *
 * \˵��:
 *   �Զ�ģʽ���ڴ�ӳ���ļ�����������CDib������й�������Ϊ���ļ�ʹ��֮ǰ��û�ж����ڴ棬
 *   �������������ء����������������DIB��ʱ�򣬿��ܻ���һЩ�ӳ٣���Ϊ�ļ��Ƿ�ҳ�ġ�
 *   DetachMapFile���������ͷ����е��ѷ�����ڴ棬���ر���ǰ�������κ��ڴ�ӳ���ļ���
 *   ���ڴ��е�DIB�����е�CDib������������ڴ�����ǳ������Դ�������ǿ����Ǽ�����
 *   ����OLE���ݶ����ڴ档�ڴ�����Ѿ���CRT��ջ��new����������ˣ����߿����Ѿ���
 *   Windows��ջ��GlobalAlloc�����ˡ�
 *   �������ͬ���ļ����Σ���Windows����һ���ļ����Դ� 
 *
 ************************************************************************
 */
BOOL CDib::AttachMapFile(const char* strPathname, BOOL bShare) // for reading
{
	// ��ȡ�ļ�����������ô�ģʽΪ����
	HANDLE hFile = ::CreateFile(strPathname, GENERIC_WRITE | GENERIC_READ,
		bShare ? FILE_SHARE_READ : 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ASSERT(hFile != INVALID_HANDLE_VALUE);

	// ��ȡ�ļ��ĳߴ�
	DWORD dwFileSize = ::GetFileSize(hFile, NULL);

	// �����ļ�ӳ����󣬲������ļ�ӳ���ģʽΪ��д
	HANDLE hMap = ::CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
	DWORD dwErr = ::GetLastError();
	if(hMap == NULL) {
		AfxMessageBox("Empty bitmap file");
		return FALSE;
	}

	// ӳ�������ļ���ע��FILE_MAP_WRITEΪ��дģʽ
	LPVOID lpvFile = ::MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0); // map whole file
	ASSERT(lpvFile != NULL);

	// ȷ��Ϊbmp��ʽ�ļ�
	if(((LPBITMAPFILEHEADER) lpvFile)->bfType != 0x4d42) {
		AfxMessageBox("Invalid bitmap file");
		DetachMapFile();
		return FALSE;
	}

	// ���ڴ��е�DIB�����е�CDib�������
	AttachMemory((LPBYTE) lpvFile + sizeof(BITMAPFILEHEADER));

	// ����Щ���õľ������Ϊ�����ݳ�Ա
	m_lpvFile = lpvFile;
	m_hFile   = hFile;
	m_hMap    = hMap;

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   CopyToMapFile()
 *
 * \�������:
 *   const	char* strPathname		- ӳ���ļ���·����
 *
 * \����ֵ:
 *   BOOL					- ����ɹ�����ΪTRUE 
 *
 * \˵��:
 *   �ú������Դ���һ���µ��ڴ�ӳ���ļ����������е�CDib���ݸ��Ƶ����ļ����ڴ�
 *   �ͷ���ǰ�������ڴ档���ر����е������ڴ�ӳ���ļ���ʵ���ϣ�ֱ�����ļ�
 *   �رյ�ʱ�򣬲Ž��������д�����̣����ǣ���CDib�����ظ�ʹ�û��ƻ�
 *   ʱ��Ҳ�ᷢ��д���̲���
 *
 ************************************************************************
 */
BOOL CDib::CopyToMapFile(const char* strPathname)
{
	BITMAPFILEHEADER bmfh;

	// �����ļ�ͷ��Ϣ
	bmfh.bfType	= 0x4d42;  
	bmfh.bfSize	= m_dwSizeImage + sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableEntries + sizeof(BITMAPFILEHEADER);
	bmfh.bfReserved1= bmfh.bfReserved2 = 0;
	bmfh.bfOffBits	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableEntries;	
	
	// �����������ݵ��ļ�
	HANDLE hFile	= ::CreateFile(strPathname, GENERIC_WRITE | GENERIC_READ, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	ASSERT(hFile != INVALID_HANDLE_VALUE);

	// �����ļ��Ĵ�С�ߴ�
	int nSize	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
				sizeof(RGBQUAD) * m_nColorTableEntries +  m_dwSizeImage;

	// �����ڴ�ӳ���ļ�����
	HANDLE hMap = ::CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, nSize, NULL);
	DWORD dwErr = ::GetLastError();
	ASSERT(hMap != NULL);

	// ӳ�������ļ�
	LPVOID lpvFile = ::MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0); 
	ASSERT(lpvFile != NULL);

	// ��ʱ�ļ�ָ��
	LPBYTE lpbCurrent = (LPBYTE) lpvFile;

	// �����ļ�ͷ��Ϣ���ڴ�ӳ���ļ���
	memcpy(lpbCurrent, &bmfh, sizeof(BITMAPFILEHEADER)); 

	// ������Ϣͷ���ļ��еĵ�ַ����������Ϣͷ��Ϣ
	lpbCurrent += sizeof(BITMAPFILEHEADER);
	LPBITMAPINFOHEADER lpBMIH = (LPBITMAPINFOHEADER) lpbCurrent;
	memcpy(lpbCurrent, m_lpBMIH,
		sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries); 

	// �����ɫ�����ļ��еĵ�ַ����������ɫ��
	lpbCurrent += sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;
	memcpy(lpbCurrent, m_lpImage, m_dwSizeImage); 

	// ��ʱ���ͼ�����ݳߴ����
	DWORD dwSizeImage = m_dwSizeImage;

	// �ͷ�һ�����������ڴ�
	Empty();

	// ����ͼ�����ݳߴ粢�����ڴ����״̬
	m_dwSizeImage = dwSizeImage;
	m_nBmihAlloc  = m_nImageAlloc = noAlloc;

	// ��Ϣͷָ������ָ���ļ��е�λ��
	m_lpBMIH = lpBMIH;

	// ͼ������ָ������ָ���ļ��е����ݵ�ַ
	m_lpImage = lpbCurrent;

	// �����ļ����
	m_hFile = hFile;

	// ����ӳ�������
	m_hMap = hMap;

	// ����ӳ���ļ�ָ��
	m_lpvFile = lpvFile;

	// ���¼���õ���ɫ��ߴ�
	ComputePaletteSize(m_lpBMIH->biBitCount);

	// ���¼���ͼ�����ݿ��С�������õ�ɫ��ָ��
	ComputeMetrics();

	// �����ɫ����ڵĻ�����ȡ������һ��Windows��ɫ��
	MakePalette();

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   AttachMemory()
 *
 * \�������:
 *   LPVOID	lpvMem			- Ҫ�������ڴ��ַ
 *   BOOL	bMustDelete		- ���CDib�ฺ��ɾ������ڴ棬���ΪTRUE
 *					- Ĭ��ֵΪFALSE
 *   HGLOBAL	hGlobal			- ����ڴ���ͨ��Win32 GlobalAlloc�õ��ģ�
 *					- ��CDib������뱣��þ�����������Ժ�
 *					- �����ͷž�����������bMustDelete����ΪTRUE
 *
 * \����ֵ:
 *   BOOL					- ����ɹ�����ΪTRUE 
 *
 * \˵��:
 *   ���ڴ��е�DIB�����е�CDib������������ڴ�����ǳ������Դ�������ǿ����Ǽ�����
 *   ����OLE���ݶ����ڴ档�ڴ�����Ѿ���CRT��ջ��new����������ˣ����߿����Ѿ���
 *   Windows��ջ��GlobalAlloc�����ˡ�
 *
 ************************************************************************
 */
BOOL CDib::AttachMemory(LPVOID lpvMem, BOOL bMustDelete, HGLOBAL hGlobal)
{
	// �����ͷ��Ѿ�������ڴ�
	Empty();

	m_hGlobal = hGlobal;
	
	// bMustDeleteΪTRUE��ʾ��CDib�������ڴ棬����ɾ��
	// �����������Ϣͷ����״̬ΪnoAlloc
	if(bMustDelete == FALSE) {
		m_nBmihAlloc = noAlloc;
	}
	else {
		m_nBmihAlloc = ((hGlobal == NULL) ? crtAlloc : heapAlloc);
	}
	try {
		// ������Ϣͷָ��
		m_lpBMIH = (LPBITMAPINFOHEADER) lpvMem;

		// ���¼���õ�ͼ�����ݿ�Ĵ�С�������õ�ɫ���ָ��
		ComputeMetrics();

		// �����ɫ��ĳߴ�
		ComputePaletteSize(m_lpBMIH->biBitCount);

		// ����ͼ������ָ��
		m_lpImage = (LPBYTE) m_lpvColorTable + sizeof(RGBQUAD) * m_nColorTableEntries;

		// �����ɫ����ڵĻ�����ȡ����������һ��Windows��ɫ�壬
		// ������ɫ��ľ����������ݳ�Ա��
		MakePalette();
	}

	// ������
	catch(CException* pe) {
		AfxMessageBox("AttachMemory error");
		pe->Delete();
		return FALSE;
	}

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   UsePalette()
 *
 * \�������:
 *   CDC*	pDC			- Ҫʵ�ֵ�ɫ����豸������ָ��
 *   BOOL	bBackground		- ������ΪFALSE��Ĭ��ֵ��������Ӧ��
 *					- ��������ǰ̨���У���Windows���Ѹõ�
 *					- ɫ����Ϊǰ̨��ɫ����ʵ�֣���ϵͳ��ɫ
 *					- ���и��ƾ����ܶ����ɫ����������Ϊ
 *					- TURE����Windows���Ѹõ�ɫ����Ϊ��̨
 *					- ��ɫ����ʵ�֣���������ϵͳ��ɫ��ӳ��
 *					- �߼���ɫ�壩
 *
 * \����ֵ:
 *   UINT				- ����ɹ����򷵻�ӳ�䵽ϵͳ��ɫ�����
 *					- ����ɫ��ı����������򷵻�GDI_ERROR 
 *
 * \˵��:
 *   �ú�����CDib������߼���ɫ��ѡ���豸�����ģ�Ȼ��ʵ�ָõ�ɫ�塣Draw��Ա��
 *   ���ڻ���DIB֮ǰ����UsePalette��
 *
 ************************************************************************
 */
UINT CDib::UsePalette(CDC* pDC, BOOL bBackground /* = FALSE */)
{
	// �ж��Ƿ���ڵ�ɫ��
	if(m_hPalette == NULL) return 0;

	// �õ��豸�����ľ��
	HDC hdc = pDC->GetSafeHdc();

	// ѡ���ɫ�嵽�豸������
	::SelectPalette(hdc, m_hPalette, bBackground);

	// ʵ�ָõ�ɫ��
	return ::RealizePalette(hdc);
}


/*************************************************************************
 *
 * \�������ƣ�
 *   Draw()
 *
 * \�������:
 *   CDC*	pDC			- ָ��Ҫ����DIBͼ����豸������ָ��
 *   CPoint	origin			- ��ʾDIB���߼�����
 *   CSize	size			- ��ʾ���εĿ�Ⱥ͸߶�
 *
 * \����ֵ:
 *   BOOL				- ����ɹ�����ΪTRUE��
 *
 * \˵��:
 *   ͨ������Win32 SDK��StretchDIBits������CDib�����������ʾ�������ߴ�ӡ������
 *   Ϊ���ʺ�ָ���ľ��Σ�λͼ���Խ��б�Ҫ������
 *
 ************************************************************************
 */
BOOL CDib::Draw(CDC* pDC, CPoint origin, CSize size)
{
	// �����ϢͷΪ�գ���ʾ��δ�����ݣ�����FALSE
	if(m_lpBMIH == NULL) return FALSE;

	// �����ɫ�岻Ϊ�գ��򽫵�ɫ��ѡ���豸������
	if(m_hPalette != NULL) {
		::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	// ������ʾģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);

	// ���豸��originλ���ϻ�����СΪsize��ͼ��
	::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y,size.cx,size.cy,
		0, 0, m_lpBMIH->biWidth, m_lpBMIH->biHeight,
		m_lpImage, (LPBITMAPINFO) m_lpBMIH, DIB_RGB_COLORS, SRCCOPY);

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   CreateSection()
 *
 * \�������:
 *   CDC*	pDC			- �豸������ָ��
 *
 * \����ֵ:
 *   HBITMAP				- ��GDIλͼ�ľ����������ɹ�����ΪNULL��
 *					- �þ��Ҳ����Ϊ�������ݳ�Ա�洢��
 *
 * \˵��:
 *   ͨ������Win32 SDK��CreateDIBSection��������һ��DIB�Ρ�ͼ���ڴ潫������ʼ��
 *
 ************************************************************************
 */
HBITMAP CDib::CreateSection(CDC* pDC /* = NULL */)
{
	// �����ϢͷΪ�գ������κδ���
	if(m_lpBMIH == NULL) return NULL;

	// ���ͼ�����ݲ����ڣ������κδ���
	if(m_lpImage != NULL) return NULL; 

	// ����һ��DIB��
	m_hBitmap = ::CreateDIBSection(pDC->GetSafeHdc(), (LPBITMAPINFO) m_lpBMIH,
		DIB_RGB_COLORS,	(LPVOID*) &m_lpImage, NULL, 0);	
	ASSERT(m_lpImage != NULL);

	// ����HBIMAP���
	return m_hBitmap;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   MakePalette()
 *
 * \�������:
 *   ��
 *
 * \����ֵ:
 *   BOOL				- ����ɹ�����ΪTRUE
 *
 * \˵��:
 *   �����ɫ����ڵĻ����ú�������ȡ����������һ��Windows��ɫ�塣
 *   HPALETTE�洢��һ�����ݳ�Ա�С�
 *
 ************************************************************************
 */
BOOL CDib::MakePalette()
{
	// ��������ڵ�ɫ�壬�򷵻�FALSE
	if(m_nColorTableEntries == 0) return FALSE;

	if(m_hPalette != NULL) ::DeleteObject(m_hPalette);
	TRACE("CDib::MakePalette -- m_nColorTableEntries = %d\n", m_nColorTableEntries);
	
	// ���߼���ɫ������ڴ�
	LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) +
		m_nColorTableEntries * sizeof(PALETTEENTRY)];

	// �����߼���ɫ�����Ϣ
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = m_nColorTableEntries;

	// ����DIB�е���ɫ���߼���ɫ��
	LPRGBQUAD pDibQuad = (LPRGBQUAD) m_lpvColorTable;
	for(int i = 0; i < m_nColorTableEntries; i++) {
		pLogPal->palPalEntry[i].peRed = pDibQuad->rgbRed;
		pLogPal->palPalEntry[i].peGreen = pDibQuad->rgbGreen;
		pLogPal->palPalEntry[i].peBlue = pDibQuad->rgbBlue;
		pLogPal->palPalEntry[i].peFlags = 0;
		pDibQuad++;
	}

	// �����߼���ɫ��
	m_hPalette = ::CreatePalette(pLogPal);

	// ɾ����ʱ����������TRUE
	delete pLogPal;
	return TRUE;
}	


/*************************************************************************
 *
 * \�������ƣ�
 *   SetSystemPalette()
 *
 * \�������:
 *   CDC*	pDC			- �豸������ָ��
 *
 * \����ֵ:
 *   BOOL				- ����ɹ�����ΪTRUE��
 *
 * \˵��:
 *   ���16bpp��24bpp��32bppDIB���߱���ɫ�壬��ú�������ΪCDib���󴴽�һ���߼���ɫ�壬
 *   ������CreatehalftonePalette�������صĵ�ɫ����ƥ�䡣���������256ɫ��ɫ����ʾ����
 *   ���У�������û�е���SetSystemPalette����ô���㽫�������κε�ɫ�壬ֻ��20�б�׼��
 *   Windows��ɫ������DIB��
 *
 ************************************************************************
 */
BOOL CDib::SetSystemPalette(CDC* pDC)
{
	// ���DIB���߱���ɫ�壬����Ҫ����ϵͳ�ĵ�ɫ��
	if(m_nColorTableEntries != 0) return FALSE;
	
	// Ϊ�豸�����Ĵ����м��ɫ�壬��������CPalette��������
	m_hPalette = ::CreateHalftonePalette(pDC->GetSafeHdc());

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   CreateBitmap()
 *
 * \�������:
 *   CDC*	pDC			- �豸������ָ��
 *
 * \����ֵ:
 *   HBITMAP				- ��GDIλͼ�ľ����������ɹ�����ΪNULL
 *					- �þ��������Ϊ�������ݳ�Ա�洢��
 *
 * \˵��:
 *   �����е�DIB�д���DDBλͼ����Ҫ�����������CreateSection
 *   Ū���ˣ����ߵ�����������DIB��������
 *
 ************************************************************************
 */
HBITMAP CDib::CreateBitmap(CDC* pDC)
{
	// ���������ͼ�����ݣ��򷵻�NULL
	if (m_dwSizeImage == 0) return NULL;

	// ��ָ����DIB������DDB������DIB��Ϣ��ʼ��λͼ��ͼ��λ
	HBITMAP hBitmap = ::CreateDIBitmap(pDC->GetSafeHdc(), m_lpBMIH,
		CBM_INIT, m_lpImage, (LPBITMAPINFO) m_lpBMIH, DIB_RGB_COLORS);
	ASSERT(hBitmap != NULL);

	// ����DDBλͼ���
	return hBitmap;
}

/*************************************************************************
 *
 * \�������ƣ�
 *   Compress()
 *
 * \�������:
 *   CDC*	pDC			- �豸������ָ��
 *   BOOL	bCompress		- TRUE��Ӧ��ѹ����DIB��FALSE��Ӧ�ڲ�ѹ����DIB
 *
 * \����ֵ:
 *   BOOL				- ����ɹ����򷵻�TRUE
 *
 * \˵��:
 *   �ú�����DIB��������Ϊѹ�����߲�ѹ����DIB�����ڲ�����ת�����е�DIBΪDDBλͼ
 *   Ȼ������һ���µ�ѹ�����߲�ѹ����DIB��ѹ����Ϊ4bpp��8bpp��DIB��֧�֡�����
 *   ѹ��DIB��
 *
 ************************************************************************
 */
BOOL CDib::Compress(CDC* pDC, BOOL bCompress /* = TRUE */)
{
	// �ж��Ƿ�Ϊ4bpp����8bppλͼ�����򣬲�����ѹ��������FALSE
	if((m_lpBMIH->biBitCount != 4) && (m_lpBMIH->biBitCount != 8)) return FALSE;
	
	// ���ΪDIB�Σ�Ҳ����֧��ѹ��������FALSE
	if(m_hBitmap) return FALSE; 

	TRACE("Compress: original palette size = %d\n", m_nColorTableEntries); 
	
	// ����豸�����ľ��
	HDC hdc = pDC->GetSafeHdc();

	// ����DIB�ĵ�ɫ��ѡ���豸�����ģ���������ǰ�ĵ�ɫ����
	HPALETTE hOldPalette = ::SelectPalette(hdc, m_hPalette, FALSE);

	HBITMAP hBitmap;  

	// ����һ��DDBλͼ��������ɹ����򷵻�FALSE
	if((hBitmap = CreateBitmap(pDC)) == NULL) return FALSE;

	// ������Ϣͷ���ϵ�ɫ��Ĵ�С�ߴ磬�������Ƿ����ڴ�
	int nSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;
	LPBITMAPINFOHEADER lpBMIH = (LPBITMAPINFOHEADER) new char[nSize];

	// ����Ϣͷ�͵�ɫ�忽�����ڴ���
	memcpy(lpBMIH, m_lpBMIH, nSize);  // new header

	// �����Ҫ����ѹ����������Ӧ����Ϣ��������ѹ����ʽ��DIB
	if(bCompress) {
		switch (lpBMIH->biBitCount) {
		case 4:
			lpBMIH->biCompression = BI_RLE4;
			break;
		case 8:
			lpBMIH->biCompression = BI_RLE8;
			break;
		default:
			ASSERT(FALSE);
		}

		// ����λͼ����ָ��ΪNULL������GetDIBits���õ�ѹ����ʽ��DIB�ĳߴ�
		// ������ܴ���DIB���������Ӧ�Ĵ�����
		if(!::GetDIBits(pDC->GetSafeHdc(), hBitmap, 0, (UINT) lpBMIH->biHeight,
					NULL, (LPBITMAPINFO) lpBMIH, DIB_RGB_COLORS)) {
			AfxMessageBox("Unable to compress this DIB");			

			// ɾ����ʱ���������ͷ��ѷ����ڴ�
	 		::DeleteObject(hBitmap);
			delete [] lpBMIH;

			// ���½���ǰ�ĵ�ɫ��ѡ�룬������FALSE
			::SelectPalette(hdc, hOldPalette, FALSE);
			return FALSE; 
		}

		// ���λͼ����Ϊ�գ��������Ӧ�Ĵ�����
		if (lpBMIH->biSizeImage == 0) {
			AfxMessageBox("Driver can't do compression");

			// ɾ����ʱ���������ͷ��ѷ����ڴ�
	 		::DeleteObject(hBitmap);
			delete [] lpBMIH;

			// ���½���ǰ�ĵ�ɫ��ѡ�룬������FALSE
			::SelectPalette(hdc, hOldPalette, FALSE);
			return FALSE; 
		}

		// ��λͼ���ݳߴ縳ֵ����ĳ�Ա����
		else {
			m_dwSizeImage = lpBMIH->biSizeImage;
		}
	}

	// ����ǽ�ѹ����������Ӧ�Ĵ���
	else {

		// ����ѹ����ʽΪ��ѹ��
		lpBMIH->biCompression = BI_RGB; 

		// ����λͼ�Ŀ�Ⱥ͸߶ȼ���λͼ�����ڴ�Ĵ�С		
		DWORD dwBytes = ((DWORD) lpBMIH->biWidth * lpBMIH->biBitCount) / 32;
		if(((DWORD) lpBMIH->biWidth * lpBMIH->biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;
		
		// ���õ�λͼ���ݵĴ�С�ߴ籣������ĳ�Ա������
		m_dwSizeImage = dwBytes * lpBMIH->biHeight; 

		// ��λͼ�����ڴ�Ĵ�С��ֵ����ʱ����Ϣͷ�е���Ӧ�ı���
		lpBMIH->biSizeImage = m_dwSizeImage;
	} 

	// �ٴε���GetDIBits������DIB����

	// ������ʱ���λͼ����
	LPBYTE lpImage = (LPBYTE) new char[m_dwSizeImage];

	// �ٴε���GetDIBits������DIB���ݣ�ע���ʱλͼ����ָ�벻Ϊ��
	VERIFY(::GetDIBits(pDC->GetSafeHdc(), hBitmap, 0, (UINT) lpBMIH->biHeight,
    		lpImage, (LPBITMAPINFO) lpBMIH, DIB_RGB_COLORS));
	TRACE("dib successfully created - height = %d\n", lpBMIH->biHeight);
	
	// ѹ��ת����ϣ�������Ӧ����������

	// ɾ����ʱ��DDBλͼ
	::DeleteObject(hBitmap);

	// �ͷ�ԭ����DIB������ڴ�
	Empty();

	// ��������ͼ����Ϣͷ��ͼ�������ڴ����״̬
	m_nBmihAlloc = m_nImageAlloc = crtAlloc;

	// ���¶�λ��Ϣͷ��ͼ������ָ��
	m_lpBMIH = lpBMIH;
	m_lpImage = lpImage;

	// ����ͼ�����ݳߴ磬������DIB�е�ɫ���ָ��
	ComputeMetrics();

	// ����DIB�е�ɫ��ĳߴ�
	ComputePaletteSize(m_lpBMIH->biBitCount);

	// ���DIB�е�ɫ����ڵĻ�����ȡ������һ��Windows��ɫ��
	MakePalette();

	// �ָ���ǰ�ĵ�ɫ��
	::SelectPalette(hdc, hOldPalette, FALSE);
	TRACE("Compress: new palette size = %d\n", m_nColorTableEntries); 

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   Read()
 *
 * \�������:
 *   CFile*	pFile			- ָ��CFile�����ָ��
 *
 * \����ֵ:
 *   BOOL				- ����ɹ����򷵻�TRUE
 *
 * \˵��:
 *   �ú���DIB��һ���ļ�����CDib���󡣸��ļ�����ɹ��򿪡�������ļ���BMP�ļ�
 *   ��ȡ�������ļ�ͷ��ʼ��������ļ���һ���ĵ�����ȡ������ӵ�ǰ�ļ�ָ�봦��ʼ 
 *
 ************************************************************************
 */
BOOL CDib::Read(CFile* pFile)
{
	// �ͷ��Ѿ�������ڴ�
	Empty();

	// ��ʱ�����Ϣ�ı���
	int nCount, nSize;
	BITMAPFILEHEADER bmfh;

	// ���ж�����
	try 
	{
		// ��ȡ�ļ�ͷ
		nCount = pFile->Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		if(nCount != sizeof(BITMAPFILEHEADER)) {
			throw new CException;
		}

		// ����ļ����Ͳ�λ"BM"���򷵻ز�������Ӧ������
		if(bmfh.bfType != 0x4d42) {
			throw new CException;
		}

		// ������Ϣͷ���ϵ�ɫ��Ĵ�С����������Ӧ���ڴ�
		nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		m_lpBMIH = (LPBITMAPINFOHEADER) new char[nSize];
		m_nBmihAlloc = m_nImageAlloc = crtAlloc;

		// ��ȡ��Ϣͷ�͵�ɫ��
		nCount = pFile->Read(m_lpBMIH, nSize); 

		// ����ͼ�����ݴ�С�����õ�ɫ��ָ��
		ComputeMetrics();

		// �����ɫ��ı�����
		ComputePaletteSize(m_lpBMIH->biBitCount);

		// ���DIB�д��ڵ�ɫ�壬�򴴽�һ��Windows��ɫ��
		MakePalette();

		// ����ͼ�������ڴ棬�����ļ��ж�ȡͼ������
		m_lpImage = (LPBYTE) new char[m_dwSizeImage];
		nCount = pFile->Read(m_lpImage, m_dwSizeImage); 
	}

	// ������
	catch(CException* pe) 
	{
		AfxMessageBox("Read error");
		pe->Delete();
		return FALSE;
	}

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   ReadSection()
 *
 * \�������:
 *   CFile*	pFile			- ָ��CFile�����ָ�룻��Ӧ�Ĵ���
 *					- �ļ��а���DIB
 *   CDC*	pDC			- �豸������ָ��
 *
 * \����ֵ:
 *   BOOL				- ����ɹ����򷵻�TRUE
 *
 * \˵��:
 *   �ú�����BMP�ļ��ж�ȡ��Ϣͷ������CreateDIBSection������ͼ���ڴ棬Ȼ��
 *   ͼ��Ӹ��ļ�����ղŷ�����ڴ档�������Ӵ��̶�ȡһ��DIB��Ȼ��ͨ������
 *   GDI�����༭���Ļ�������ʹ�øú������������Write��CopyToMapFile��DIBд
 *   �ص�����
 *
 ************************************************************************
 */
BOOL CDib::ReadSection(CFile* pFile, CDC* pDC /* = NULL */)
{
	
	// �ͷ��Ѿ�������ڴ�
	Empty();

	// ��ʱ����
	int nCount, nSize;
	BITMAPFILEHEADER bmfh;

	// ���ļ��ж�ȡ����
	try {
		// ��ȡ�ļ�ͷ
		nCount = pFile->Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		if(nCount != sizeof(BITMAPFILEHEADER)) {
			throw new CException;
		}

		// ����ļ����Ͳ�λ"BM"���򷵻ز�������Ӧ������
		if(bmfh.bfType != 0x4d42) {
			throw new CException;
		}

		// ������Ϣͷ���ϵ�ɫ��Ĵ�С����������Ӧ���ڴ�
		nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
		m_lpBMIH = (LPBITMAPINFOHEADER) new char[nSize];
		m_nBmihAlloc = crtAlloc;
		m_nImageAlloc = noAlloc;

		// ��ȡ��Ϣͷ�͵�ɫ��
		nCount = pFile->Read(m_lpBMIH, nSize); 

		// ���ͼ��Ϊѹ����ʽ���򲻽��к�������
		if(m_lpBMIH->biCompression != BI_RGB) {
			throw new CException;
		}

		// ����ͼ�����ݴ�С�����õ�ɫ��ָ��
		ComputeMetrics();

		// �����ɫ��ı�����
		ComputePaletteSize(m_lpBMIH->biBitCount);

		// ���DIB�д��ڵ�ɫ�壬�򴴽�һ��Windows��ɫ��
		MakePalette();

		// ��CDib������߼���ɫ��ѡ���豸������		
		UsePalette(pDC);

		// ����һ��DIB�Σ�������ͼ���ڴ�
		m_hBitmap = ::CreateDIBSection(pDC->GetSafeHdc(), (LPBITMAPINFO) m_lpBMIH,
			DIB_RGB_COLORS,	(LPVOID*) &m_lpImage, NULL, 0);
		ASSERT(m_lpImage != NULL);

		// ���ļ��ж�ȡͼ������
		nCount = pFile->Read(m_lpImage, m_dwSizeImage); 
	}

	// ������
	catch(CException* pe) {
		AfxMessageBox("ReadSection error");
		pe->Delete();
		return FALSE;
	}
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   Write()
 *
 * \�������:
 *   CFile*	pFile			- ָ��CFile�����ָ��
 *
 * \����ֵ:
 *   BOOL				- ����ɹ����򷵻�TRUE
 *
 * \˵��:
 *   �ú�����DIB��CDib����д���ļ��С����ļ�����ɹ��򿪻��ߴ���
 *
 ************************************************************************
 */
BOOL CDib::Write(CFile* pFile)
{
	BITMAPFILEHEADER bmfh;

	// �����ļ�ͷ���ļ�����Ϊ"BM"
	bmfh.bfType = 0x4d42;  

	// ������Ϣͷ�͵�ɫ��Ĵ�С�ߴ�
	int nSizeHdr = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;

	// �����ļ�ͷ��Ϣ
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + nSizeHdr + m_dwSizeImage;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableEntries;	
	
	// ����д����
	try {
		pFile->Write((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		pFile->Write((LPVOID) m_lpBMIH,  nSizeHdr);
		pFile->Write((LPVOID) m_lpImage, m_dwSizeImage);
	}

	// ������
	catch(CException* pe) {
		pe->Delete();
		AfxMessageBox("write error");
		return FALSE;
	}

	// ����
	return TRUE;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   Serialize()
 *
 * \�������:
 *   CArchive&	ar			- ָ��Ӧ�ó���鵵����
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   �ú������д��л����̣���CDib���ݽ��ж������д��
 *
 ************************************************************************
 */
void CDib::Serialize(CArchive& ar)
{
	DWORD dwPos;

	// ��ô˹鵵�ļ���CFile����ָ��
	dwPos = ar.GetFile()->GetPosition();
	TRACE("CDib::Serialize -- pos = %d\n", dwPos);

	// �ӹ鵵�ļ��������г��δд������
	ar.Flush();

	// ���»�ô˹鵵�ļ���CFile����ָ��
	dwPos = ar.GetFile()->GetPosition();
	TRACE("CDib::Serialize -- pos = %d\n", dwPos);

	// ȷ���鵵�ļ��Ƿ񱻴洢��������д洢	
	if(ar.IsStoring()) {
		Write(ar.GetFile());
	}

	// ������м���
	else {
		Read(ar.GetFile());
	}
}


/*************************************************************************
 *
 * \�������ƣ�
 *   ComputePaletteSize()
 *
 * \�������:
 *   int	nBitCount		- ָ��CFile�����ָ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   �ú�������λͼ����λ�������ɫ��ĳߴ�
 *
 ************************************************************************
 */
void CDib::ComputePaletteSize(int nBitCount)
{
	// ���biClrUsedΪ�㣬���õ�����ɫ��Ϊ2��biBitCount�η�
	if((m_lpBMIH == NULL) || (m_lpBMIH->biClrUsed == 0)) {
		switch(nBitCount) {
			case 1:
				m_nColorTableEntries = 2;
				break;
			case 4:
				m_nColorTableEntries = 16;
				break;
			case 8:
				m_nColorTableEntries = 256;
				break;
			case 16:
			case 24:
			case 32:
				m_nColorTableEntries = 0;
				break;
			default:
				ASSERT(FALSE);
		}
	}

	// �����ɫ��ı����������õ�����ɫ��Ŀ
	else {
		m_nColorTableEntries = m_lpBMIH->biClrUsed;
	}

	ASSERT((m_nColorTableEntries >= 0) && (m_nColorTableEntries <= 256)); 
}


/*************************************************************************
 *
 * \�������ƣ�
 *   ComputeMetrics()
 *
 * \�������:
 *   ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   �ú�������ͼ��λͼ�ĳߴ磬����DIB�еĵ�ɫ���ָ����и�ֵ
 *
 ************************************************************************
 */
void CDib::ComputeMetrics()
{
	// ����ṹ�ĳ��Ȳ��ԣ�����д�����
	if(m_lpBMIH->biSize != sizeof(BITMAPINFOHEADER)) {
		TRACE("Not a valid Windows bitmap -- probably an OS/2 bitmap\n");
		throw new CException;
	}

	// ����ͼ�������ڴ��С��CDib��������ݳ�Ա��
	m_dwSizeImage = m_lpBMIH->biSizeImage;

	// ���ͼ�������ڴ��СΪ0�������¼���
	if(m_dwSizeImage == 0) {
		DWORD dwBytes = ((DWORD) m_lpBMIH->biWidth * m_lpBMIH->biBitCount) / 32;
		if(((DWORD) m_lpBMIH->biWidth * m_lpBMIH->biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;
		m_dwSizeImage = dwBytes * m_lpBMIH->biHeight;	
	}

	// ����DIB�еĵ�ɫ��ָ��
	m_lpvColorTable = (LPBYTE) m_lpBMIH + sizeof(BITMAPINFOHEADER);
}


/*************************************************************************
 *
 * \�������ƣ�
 *   Empty()
 *
 * \�������:
 *   ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   �ú������DIB���ͷ��ѷ�����ڴ棬���ұ�Ҫ��ʱ��ر�ӳ���ļ�
 *
 ************************************************************************
 */
void CDib::Empty()
{
	// �ر��ڴ�ӳ���ļ�������
	DetachMapFile();

	// �����ڴ�����״̬��������Ӧ�ĺ����ͷ���Ϣͷ
	if(m_nBmihAlloc == crtAlloc) {
		delete [] m_lpBMIH;
	}
	else if(m_nBmihAlloc == heapAlloc) {
		::GlobalUnlock(m_hGlobal);
		::GlobalFree(m_hGlobal);
	}

	// �ͷ�ͼ�������ڴ�
	if(m_nImageAlloc == crtAlloc) delete [] m_lpImage;

	// �ͷŵ�ɫ����
	if(m_hPalette != NULL) ::DeleteObject(m_hPalette);

	// ���������BITMAP��������ͷ�
	if(m_hBitmap != NULL) ::DeleteObject(m_hBitmap);

	// ���������ڴ����״̬
	m_nBmihAlloc = m_nImageAlloc = noAlloc;

	// �ͷ��ڴ�󣬻���Ҫ��ָ������ΪNULL������Ӧ����������Ϊ0
	m_hGlobal = NULL;
	m_lpBMIH = NULL;
	m_lpImage = NULL;
	m_lpvColorTable = NULL;
	m_nColorTableEntries = 0;
	m_dwSizeImage = 0;
	m_lpvFile = NULL;
	m_hMap = NULL;
	m_hFile = NULL;
	m_hBitmap = NULL;
	m_hPalette = NULL;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   DetachMapFile()
 *
 * \�������:
 *   ��
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ���������ͷ����е��ѷ�����ڴ棬���ر���ǰ�������κ��ڴ�ӳ���ļ���
 *
 ************************************************************************
 */
void CDib::DetachMapFile()
{
	// ���û�н����ڴ�ӳ�䣬�򲻽��д���
	if(m_hFile == NULL) return;

	// �ر��ڴ�ӳ��
	::UnmapViewOfFile(m_lpvFile);

	// �ر��ڴ�ӳ�������ļ�
	::CloseHandle(m_hMap);
	::CloseHandle(m_hFile);
	m_hFile = NULL;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   PaletteSize()
 *
 * \�������:
 *   ��
 *
 * \����ֵ:
 *   DWORD				- ���ص�ɫ��ĳߴ�
 *
 * \˵��:
 *   �ú����������ɫ������ĳߴ�
 *
 ************************************************************************
 */
WORD CDib::PaletteSize()
{
	// ��ʱ����
	WORD	       NumColors;
	LPBITMAPINFOHEADER lpbi=m_lpBMIH;

	// ���biClrUsedΪ�㣬��ͼ������λ��С��8��������ɫ���õ��ı�����
	NumColors = 	((lpbi)->biClrUsed == 0 && (lpbi)->biBitCount <= 8 \
                                    ? (int)(1 << (int)(lpbi)->biBitCount)          \
                                    : (int)(lpbi)->biClrUsed);

	// ������ɫ��ʾ���ֽ��������ɫ��ĳߴ�
	if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
		return NumColors * sizeof(RGBTRIPLE);
	else 
		return NumColors * sizeof(RGBQUAD);

}


/*************************************************************************
 *
 * \�������ƣ�
 *   IsEmpty()
 *
 * \�������:
 *   ��
 *
 * \����ֵ:
 *   BOOL				- �����Ϣͷ��ͼ������Ϊ�գ��򷵻�TRUE
 *
 * \˵��:
 *   �ж���Ϣͷ��ͼ�������Ƿ�Ϊ��
 *
 ************************************************************************
 */
BOOL CDib::IsEmpty()
{

	if(	m_lpBMIH == NULL&&m_lpImage == NULL)
		return TRUE;
	else
		return FALSE;

}


/*************************************************************************
 *
 * \�������ƣ�
 *   GetDibSaveDim()
 *
 * \�������:
 *   ��
 *
 * \����ֵ:
 *   CSize			- DIBʵ�ʴ洢�ĸ߶ȺͿ��
 *
 * \˵��:
 *   �ú������������õ�dib��ʵ�ʴ洢��ȣ�DWORD���룩
 *
 ************************************************************************
 */

CSize CDib::GetDibSaveDim()
{
	CSize sizeSaveDim;
	sizeSaveDim.cx	= ( m_lpBMIH->biWidth * m_lpBMIH->biBitCount + 31)/32 * 4;
	sizeSaveDim.cy	= m_lpBMIH->biHeight; 
	return sizeSaveDim;

}


/*************************************************************************
 *
 * \�������ƣ�
 *   GetPixelOffset()
 *
 * \�������:
 *   int	x		- ������X�������
 *   int	y		- ������Y�������
 *
 * \����ֵ:
 *   int			- ����������ͼ�����ݿ��е���ʵ��ַ
 *
 * \˵��:
 *   �ú����õ�����Ϊ(x,y)�����ص����ʵ��ַ������DIB�ṹ�ж�ͼ���������е�
 *   ��ʽΪ���µ��ϣ������ҵģ�������Ҫ����ת����
 *
 ************************************************************************
 */
LONG CDib::GetPixelOffset(int  x, int y)
{
	CSize sizeSaveDim;
	sizeSaveDim = GetDibSaveDim();

	LONG lOffset = (LONG) (sizeSaveDim.cy - y - 1) * sizeSaveDim.cx +
		x  / (8 / m_lpBMIH->biBitCount);
	return lOffset;
}


/*************************************************************************
 *
 * \�������ƣ�
 *   GetPixel()
 *
 * \�������:
 *   int	x		- ������X�������
 *   int	y		- ������Y�������
 *
 * \����ֵ:
 *   RGBQUAD			- ����DIB�ڸõ���ʵ����ɫ
 *
 * \˵��:
 *   �ú����õ�DIBͼ���ڸõ����ǵ���ɫ��
 *
 ************************************************************************
 */
RGBQUAD CDib::GetPixel(int x, int y)
{
	// ��ɫ�ṹ
	RGBQUAD cColor;
	
	// ����ÿ���ر������õ��˵������ֵ
	switch (m_lpBMIH->biBitCount)
	{
		case 1 :
			if (1<<(7-x%8) & *(LPBYTE)(m_lpImage+GetPixelOffset(x, y)))
			{			
				cColor.rgbBlue  = 255;
				cColor.rgbGreen = 255;
				cColor.rgbRed   = 255;
				cColor.rgbReserved =0;
			}
			else
			{			
				cColor.rgbBlue  = 0;
				cColor.rgbGreen = 0;
				cColor.rgbRed   = 0;	
				cColor.rgbReserved =0;
			}
			break;
		case 4 :	
			{
				int nIndex = (*(LPBYTE)(m_lpImage+GetPixelOffset(x, y)) & 
							   (x%2 ? 0x0f : 0xf0)) >> (x%2 ? 0 : 4);
				LPRGBQUAD pDibQuad = (LPRGBQUAD) (m_lpvColorTable) + nIndex;
				cColor.rgbBlue  = pDibQuad->rgbBlue;
				cColor.rgbGreen = pDibQuad->rgbGreen;
				cColor.rgbRed   = pDibQuad->rgbRed;
				cColor.rgbReserved =0;
			}
					break;
		case 8 :	
			{
				int nIndex = *(BYTE*)(m_lpImage+GetPixelOffset(x, y));
				LPRGBQUAD pDibQuad = (LPRGBQUAD) (m_lpvColorTable) + nIndex;
				cColor.rgbBlue  = pDibQuad->rgbBlue;
				cColor.rgbGreen = pDibQuad->rgbGreen;
				cColor.rgbRed   = pDibQuad->rgbRed;
				cColor.rgbReserved =0;
			}
					break;
		default:
				int nIndex = *(BYTE*)(m_lpImage+GetPixelOffset(x, y));					
				cColor.rgbRed   = m_lpImage[nIndex];
				cColor.rgbGreen = m_lpImage[nIndex + 1];
				cColor.rgbBlue  = m_lpImage[nIndex + 2];
				cColor.rgbReserved =0;	
				break;
	}

	// ������ɫ�ṹ
	return cColor;
}
