// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#ifdef NOCONST
// 悪い例：RAMを1KBも消費してしまう（2KBしかないのに！）
unsigned char map_data[1024] = { 0x01, 0x02, };
#else
// 良い例：データはROM(32KB)に置かれ、RAMを全く消費しない
const unsigned char map_data[1024] = { 0x01, 0x02, };
#endif

int main(void) {
	map_data[1];
}

