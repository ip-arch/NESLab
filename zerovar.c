// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
int foo(int x) {
register int i;
	for(i=0;i<10;i++)
		x+=i;
	return x;
}
