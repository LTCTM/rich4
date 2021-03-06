/*
 * Copyright (C)  2018 Iru Cai <mytbk920423@gmail.com>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "player_info.h"
#include "global.h"
#include "sound_struct.h"
#include "window_util.h"

uint8_t player_cards[60]; // 0x499120
int selected_card; // 0x48c544
const char str_use[] = "\xa8\xcf\xa5\xce%s"; // 使用%s

sound_struct snd0 = {1, NULL}; // 0x00482322
sound_struct snd1 = {3, NULL}; // 0x0048233a
sound_struct snd2; // 0x0048cae0

void fcn_4540d8(LPDIRECTSOUNDBUFFER sbuf, uint32_t a1, int a2)
{
	if (sbuf == NULL || dw_49715b == 0)
		return;

	IDirectSoundBuffer_SetCurrentPosition(sbuf, 0);
	if (IDirectSoundBuffer_Play(sbuf, 0, 0, a2) == DSERR_BUFFERLOST) {
		if (fcn.00453f6c(sbuf, a1) == 1) {
			IDirectSoundBuffer_Play(sbuf, 0, 0, a2);
		}
	}
	IDirectSoundBuffer_SetVolume(sbuf, dword [(uint8_t)b_49715b * 4 + 0x47e758]);
	snd2.f0 = a1;
	snd2.sbuf = sbuf;
}

void fcn_4542ce(sound_struct * a0, int a1)
{
	fcn_4540d8(a0->sbuf, a0->f0, a1);
}

LRESULT CALLBACK cardProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	RECT rect2;

	if (message >= 0x202) {
		if (message == WM_LBUTTONUP) {
			if (selected_card == 0)
				return 0;
			fcn.00451d4e();
			fcn_00402460(0);
			Post_0402_Message(selected_card);
			return 0;
		}
		if (message >= 0x205) {
			if (message == WM_RBUTTONUP) {
				fcn_00402460(0);
				Post_0402_Message(0);
				return 0;
			}
			if (message == 0x401) {
				selected_card = 0;
				fcn_00402460(1);
				InvalidateRect(hWnd, NULL, FALSE);
				return 0;
			}
			return DefWindowProcA(hWnd, message, wp, lp);
		} else {
			return DefWindowProcA(hWnd, message, wp, lp);
		}
	}

	if (message >= 0xf) {
		if (message == 0xf) {
			BeginPaint(hWnd, &ps);
			GetCursorPos_35d(&ps.rcPaint); /* fcn_4021f8.c */
			IDirectDrawSurface_BltFast(pddrawsf1, ps.rcPaint.left, ps.rcPaint.top, pddrawsf2, &ps.rcPaint, 0x10);
			GetCursorPos_250(&ps.rcPaint); /* fcn_4021f8.c */
			EndPaint(hWnd, &ps);
			return 0;
		}
		if (message == 0x201) {
			ebx = (uint16_t)dx;
			edx >>= 16; /* unsigned shift */
			if (ebx < 0x13 || ebx >= 0x1a3 || edx < 0x87 || edx >= 0x12f)
				return 0;

			esi = ((edx - 0x87) / 56) * 5;
			ebx = esi + (ebx - 0x13) / 80;
			eax = current_player * 15;
			if (player_cards[current_player * 15 + ebx] == 0)
				return 0;

			int t1 = (ebx % 5) * 80;
			int t2 = (ebx / 5) * 56;
			rect2.left = t1 + 0x14;
			rect2.right = t1 + 0x62;
			rect2.top = t2 + 0x88;
			rect2.bottom = t2 + 0xbe;
			fcn.00451b9e(&rect2);

			eax = player_cards[current_player * 15 + ebx];
			selected_card = eax;
			fcn_4542ce(&snd0, 0);
			return 0;
		}
		return DefWindowProcA(hWnd, message, wp, lp);
	} else {
		return DefWindowProcA(hWnd, message, wp, lp);
	}
}

void cards_ui()
{
	int t[4]; /* esp + 0x80 */
	char s[128];
	uint8_t mem[8]; /* esp + 0x90 */

	eax = current_player * 0x68;
	uint8_t dl = players[current_player].who_plays;
	if (dl == 1) {
		fcn.0041d546();
		edi = eax = read_mkf(mkf_panel, 11, NULL, NULL);
		t[0] = 0;
		t[1] = 40;
		t[2] = 440;
		t[3] = 480;
		ebp = fcn.00451e7e(t);
		do {
			esi = 1;
			fcn_00441b0a(0, edi, current_player);
			IDirectDrawSurface_Lock(pddrawsf2, NULL, &sfdesc1, 1, 0);
			overlay_fullscreen(sfdesc1.lpSurface, edi+12, 14, 130);
			IDirectDrawSurface_Unlock(pddrawsf2, NULL);
			int cardid = register_wait_callback(cardProc, 0);
			fcn_00451edb(ebp, 0, 0x8028);
			if (ebx != 0) {
				edx = cards_table[cardid - 1].name_ptr;
				sprintf(s, str_use, edx);
				fcn_00441f73(cardid, s);
				esi = eax = card_functions[cardid]();
				if (eax) {
					fcn_4542ce(&snd1, eax);
				}
			}
		} while (esi != 0);
		free (edi);
		free (ebp);
		return;
	}
	if ((dl & 6) && (players[current_player].f22 & 1)) {
		edi = esi = eax = player_cards_num(current_player);
		if (eax == 0)
			return;
		memset(mem, 0, 8);
		if (esi > 8) {
			esi = rand() % esi;
		} else {
			esi = 0;
		}
		for (ebx = 0; ebx < 8; ebx++) {
			eax = current_player * 15;
			edx = esi;
			esi++;
			al = player_cards[edx + eax];
			mem[ebx] = al;
			if (edi <= 8 || esi != edi)
				continue;
			esi ^= edi;
		}
	}
	for (ebx = 0; ebx < 8; ebx++) {
		cl = mem[ebx];
		if (cl == 0)
			return;
		eax = cl; /* zero ext */
		eax = fcn_0041e69e(eax);
		if (eax != 1)
			continue;

		eax = mem[ebx];
		ecx = cards_table[eax - 1].name_ptr;
		sprintf(s, str_use, ecx);
		eax = mem[ebx];
		fcn_00441f73(eax, s);
		eax = mem[ebx];
		card_functions[eax]();
		return;
	}
}
