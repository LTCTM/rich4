#include <windows.h>
#include <stdint.h>

HFONT gFont; // 0x4762d0
int gFontHeight; // 0x4762d4
uint32_t gfa[4]; // 0x4762d8, 0x4762dc, 0x4762e0, 0x4762e4
const char tfname[] = "\xb2\xd3\xa9\xfa\xc5\xe9"; // 0x4660a0, typeface name, BIG5:细明体

static inline uint32_t swapbytes3(uint32_t x)
{
  return (((x & 0xff) << 16) | (x & 0xff00) | ((x & 0xff0000) >> 16));
}

/* 0x0044f9d8 */
HFONT create_some_font(int a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4)
{
  gfa[2] = swapbytes3(a1);
  gfa[3] = swapbytes3(a2);
  gfa[0] = a3;
  gfa[1] = a4;
  int weight = (a3==2)?400:700;
  if (gFont != 0) {
    DeleteObject(gFont);
  }
  gFontHeight = a0;
  gFont = CreateFontA(-a0, 0, 0, 0, weight, 0, 0, 0, 0x88 /* charset */, 0, 0, 0, 0, tfname);
  return gFont;
}

void drawStringY(HDC hdc, int nXStart, int nYStart, LPCSTR str)
{
	int h = gFontHeight + gfa[1];
	if (((uint8_t)gfa[0] & 6) != 0)
		h++;

	while (*str) {
		if ((str[0] & 0x80) != 0) {
			TextOutA(hdc, nXStart, nYStart, str, 2);
			str += 2;
		} else {
			TextOutA(hdc, nXStart, nYStart, str, 1);
			str += 1;
		}
		nYStart += h;
	}
}

void draw_some_text(a1, const char *str, a3, a4, int a5)
{
	DDSURFACEDESC desc; /* esp */
	RECT fmt_dim1; /* esp + 0x6c */
	RECT fmt_dim2; /* esp + 0x7c */
	HDC hDC; /* esp + 0x8c */

	fmt_dim1 = *(RECT*)0x44f6ec;
	fmt_dim2 = *(RECT*)0x44f6fc;

	if (str == NULL || str[0] == 0)
		return;
	if (str[0] == '#') {
		int t = (str[1] - '0') * 1000 + (str[2] - '0') * 100 +
			(str[3] - '0') * 10 + (str[4] - '0');
		fcn.0045441a(t);
		str += 5;
	}
	IDirectDrawSurface_GetDC(pddrawsf3, &hDC);
	SelectObject(hDC, &gFont);
	SetBkMode(hDC, 1);
	SetTextCharacterExtra(hDC, gfa[1]-1);
	DrawTextA(hDC, str, strlen(str), &fmt_dim2, 0x400);
	int t1 = fmt_dim2.right + 10;
	int t2 = fmt_dim2.bottom + 10;
	fmt_dim2.right = t1;
	fmt_dim2.bottom = t2;
	if (a5 == 3) {
		fmt_dim2.right = t2;
		fmt_dim2.bottom = t1;
	} else if (a5 == 4 || a5 == 7) {
		eax = fmt_dim2.right / 2;
		edx = 256 - eax;
		fmt_dim2.left = edx;
		eax += 256;
		fmt_dim2.right = eax;
	}
	dh = b_4762d8;
	if (dh != 1) {
		SetTextColor(hDC, dw_4762e4);
		eax = 1;
		fmt_dim1.left = 1;
		fmt_dim1.top = 1;
		if (a5 >= 4) {
			if (a5 == 4 || a5 == 7) {
				DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, 1);
			} else {
				DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, 0);
			}
		} else if (a5 != 3) {
			DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, 0);
		} else {
			drawStringY(hDC, eax, eax, ebx);
		}
		goto L44fe09;
	}
	if (dh == 4)
		goto L44fe09;
	SetTextColor(hDC, dw_4762e4);
	if (a5 == 3) {
		drawStringY(hDC, 1, 0, ebx);
		drawStringY(hDC, 1, 2, ebx);
		drawStringY(hDC, 0, 1, ebx);
		drawStringY(hDC, 2, 1, ebx);
		goto L44fe09;
	}
	if (a5 == 4 || a5 == 7) {
		esi = 1;
	} else {
		esi = 0;
	}

	fmt_dim1.left = 1;
	fmt_dim1.top = 0;
	DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, esi);

	fmt_dim1.left = 1;
	fmt_dim1.top = 2;
	DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, esi);

	fmt_dim1.left = 0;
	fmt_dim1.top = 1;
	DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, esi);

	fmt_dim1.left = 2;
	fmt_dim1.top = 1;
	DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, esi);

L44fe09:

	SetTextColor(hDC, dw_4762e0);
	if ( ((uint8_t)gfa[0] & 4) != 0 ) {
		edi = 1;
		fmt_dim1.left = 1;
		fmt_dim1.top = 1;
	} else {
		ecx = 0;
		fmt_dim1.left = 0;
		fmt_dim1.top = 0;
	}
	if (a5 >= 4) {
		if (a5 == 4 || a5 == 7) {
			DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, 1);
		} else {
			DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, 0);
		}
	} else if (a5 == 3) {
		drawStringY(hDC, fmt_dim1.left, fmt_dim1.top, ebx);
	} else {
		DrawTextA(hDC, ebx, strlen(ebx), &fmt_dim1, 0);
	}

	IDirectDrawSurface_ReleaseDC(pddrawsf3, hDC);

	desc.dwSize = 0x6c;
	IDirectDrawSurface_Lock(pddrawsf3, NULL, &desc, 1, 0);

	fcn.0044f70c(desc.lpSurface, &fmt_dim2, &fmt_dim1);
	esi = fmt_dim1.right - fmt_dim1.left + 1;
	ebx = fmt_dim1.bottom - fmt_dim1.top + 1;
	dw_4762f0 = desc.lpSurface;
	eax = a5-1;
	switch (eax) {
		case 0:
			a3 -= esi;
			break;
		case 1:
		case 2:
		case 3:
			a3 -= esi / 2;
			/* fall through */
		case 4:
			eax = ebx / 2;
			a4 -= eax;
			break;
		case 5:
			a3 -= esi;
			eax = ebx / 2;
			a4 -= eax;
			break;
		case 6:
			eax = esi / 2;
			a3 = eax;
			a4 = ebx;
			break;
		default:
			break;
	}

	if ( ((uint8_t)gfa[0] & 8) != 0) {
		if (!a1) {
			fcn.004564e6(sfdesc1.lpSurface, 0x4762e8, a3, a4, fmt_dim1.left, fmt_dim1.top, esi, ebx);
		} else {
			fcn.00456356(a1, 0x4762e8, a3, a4, fmt_dim1.left, fmt_dim1.top, esi, ebx);
		}
	} else {
		if (!a1) {
			fcn.00456495(sfdesc1.lpSurface, 0x4762e8, a3, a4, fmt_dim1.left, fmt_dim1.top, esi, ebx);
		} else {
			fcn.00456328(a1, 0x4762e8, a3, a4, fmt_dim1.left, fmt_dim1.top, esi, ebx);
		}
	}
	fcn.004561be(0x4762e8, fmt_dim1.left, fmt_dim1.top, esi, ebx, 0);
	IDirectDrawSurface_Unlock(NULL);
}
