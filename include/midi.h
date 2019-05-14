/*
 *  Copyright (C) 2002-2013  The DOSBox Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#ifndef DOSBOX_MIDI_H
#define DOSBOX_MIDI_H

#ifndef DOSBOX_PROGRAMS_H
#include "programs.h"
#endif

class MidiHandler {
public:
	MidiHandler();
	virtual bool Open(const char * /*conf*/) { return true; };
	virtual void Close(void) {};
	virtual void PlayMsg(Bit8u * /*msg*/) {};
	virtual void PlaySysex(Bit8u * /*sysex*/,Bitu /*len*/) {};
	virtual const char * GetName(void) { return "none"; };
	virtual void ListAll(Program * base) {};
	virtual ~MidiHandler() { };
	MidiHandler * next;
};


#define SYSEX_SIZE 8192
struct DB_Midi {
	Bitu status;
	Bitu cmd_len;
	Bitu cmd_pos;
	Bit8u cmd_buf[8];
	Bit8u rt_buf[8];
	struct midi_state_sysex_t {
		Bit8u buf[SYSEX_SIZE];
		Bitu used;
		Bitu delay;
		Bit32u start;

		midi_state_sysex_t() : used(0), delay(0), start(0) { }
	} sysex;
	bool available;
	MidiHandler * handler;

	DB_Midi() : status(0x00), cmd_len(0), cmd_pos(0), available(false), handler(NULL) { }
};

extern DB_Midi midi;

#endif