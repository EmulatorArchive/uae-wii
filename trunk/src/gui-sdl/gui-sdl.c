 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Interface to the Tcl/Tk GUI
  *
  * Copyright 1996 Bernd Schmidt
  */

#include "sysconfig.h"
#include "sysdeps.h"
#include "savestate.h"
#include "custom.h"

#include "options.h"
#include "gui.h"
#include "uae.h"
#include "menu.h"

static void default_config(void);

static const char *main_menu_messages[] = {
		/*00*/		"Insert floppy",
		/*01*/		"^|df0|df1|df2|df3",
		/*02*/		"States",
		/*03*/		"^|Load|Save|Delete",
		/*04*/		"#1-------------------------------------",
		/*05*/		"Reset UAE",
		/*06*/		"Amiga model",
		/*07*/		"Options",
		/*08*/		"Advanced options",
		/*09*/		"Help",
		/*10*/		"Quit",
		NULL
};

static const char *amiga_model_messages[] = {
		/*00*/		"Amiga model",
		/*01*/		"^|A1000|A500|A600|A1200|Custom",
		/*02*/		"Emulation accuracy",
		/*03*/		"^|Fast|Accurate",
		NULL
};

static const char *memory_messages[] = {
		/*00*/		"Chip mem",
		/*01*/		"^|512K|1M|2M|4M|8M",
		/*02*/		"Slow mem",
		/*03*/		"^|512K|1M|1.8M",
		/*04*/		"Fast mem",
		/*05*/		"^|None|1M|2M|4M|8M",
		NULL
};

static const char *cpu_messages[] = {
		/*00*/		"Model",
		/*01*/		"^|68000|68010|68020|68030|68040",
		/*02*/		"Accuracy",
		/*03*/		"^|Normal|Compatible|Cycle exact",
		/*04*/		"Speed",
		/*05*/		"^|Approx 1-1|Maximum",
		/*06*/		"Chipset",
		/*07*/		"^|OCS|ECS Agnus|Full ECS|AGA",
		/*08*/		"TV mode (emulation)",
		/*09*/		"^|NTSC|PAL",
		NULL
};

static const char *other_messages[] = {
		NULL	
};

/* All this is taken directly from PSPUAE */
static void A500_config(void)
{
	default_config();

	changed_prefs.collision_level = 2; //Playfields
	changed_prefs.cpu_level = 0; //68000
	changed_prefs.cpu_compatible = 1; //ON
	changed_prefs.m68k_speed = -1; // max speed
	changed_prefs.fastmem_size = 0; //OFF
	changed_prefs.chipmem_size = 512 * 1024; //512
	changed_prefs.bogomem_size = 512 * 1024; //512
	changed_prefs.chipset_mask = 0; //OCS
	changed_prefs.floppy_speed = 100;  //Normal
	changed_prefs.immediate_blits = 1; //ON
}

static void A600_config(void)
{
	default_config();

	changed_prefs.collision_level = 2; //Playfields
	changed_prefs.cpu_level = 1; //68010
	changed_prefs.cpu_compatible = 1; //ON
	changed_prefs.m68k_speed = -1; // max speed
	changed_prefs.fastmem_size = 0; //OFF
	changed_prefs.chipmem_size = 1024 * 1024; //1024
	changed_prefs.bogomem_size = 0; //OFF
	changed_prefs.chipset_mask = 2; //ECS Denise
	changed_prefs.immediate_blits = 1; //ON
}

static void A1000_config(void)
{
	default_config();

	changed_prefs.collision_level = 2; //Playfields
	changed_prefs.cpu_level = 0; //68000
	changed_prefs.cpu_compatible = 1; //ON
	changed_prefs.m68k_speed = -1; // max speed
	changed_prefs.fastmem_size = 0; //OFF
	changed_prefs.chipmem_size = 512 * 1024; //512
	changed_prefs.bogomem_size = 0; //OFF
	changed_prefs.chipset_mask = 0; //OCS
	changed_prefs.immediate_blits = 1; //ON
}

static void A1200_config(void)
{
	default_config();

	changed_prefs.cpu_level = 2; //68020
	changed_prefs.cpu_compatible = 1; //ON
	changed_prefs.m68k_speed = -1; // max speed
	changed_prefs.fastmem_size = 0; //OFF
	changed_prefs.chipmem_size = 1024 * 2048; //2048
	changed_prefs.bogomem_size = 0;
	changed_prefs.chipset_mask = 3; //ECS
	changed_prefs.immediate_blits = 1; //ON
}

static void default_config(void)
{
	changed_prefs.gfx_framerate=5;
	changed_prefs.produce_sound=2; //normal
	changed_prefs.sound_stereo = 0;	//Stereo
	changed_prefs.sound_interpol = 0; //None FOL (Added Interpol to Sound Menu)

	changed_prefs.collision_level = 2; //Playfields
	changed_prefs.cpu_level = 0; //M68k
	changed_prefs.cpu_idle = 0; // OFF FOL
	changed_prefs.cpu_compatible = 0; //OFF
	changed_prefs.m68k_speed = -1; // max speed
	changed_prefs.fastmem_size = 0; //OFF
	changed_prefs.chipmem_size = 512 * 1024; //512kb
	changed_prefs.bogomem_size = 512 * 1024; //512kb
	changed_prefs.chipset_mask = CSMASK_ECS_AGNUS; //ECS Super AGNUS
	changed_prefs.leds_on_screen = 1; //Floppy, Power, FPS, etc etc.

	changed_prefs.floppy_speed = 100; //Floppy Speed Normal
	changed_prefs.immediate_blits = 0; //OFF
	changed_prefs.blitter_cycle_exact = 0; //OFF
	changed_prefs.gfx_correct_aspect = 0; //OFF FOL (This doesnt work any more) FOL
	changed_prefs.dfxtype[0] = 0; //Drive Type Double Density, can be set to High Density 1.7Megs
	changed_prefs.dfxtype[1] = 0; //Drive Type Double Density, can be set to High Density 1.7Megs
	changed_prefs.tod_hack = 1; //ON, Syncronise Clocks FOL
	changed_prefs.gfx_xcenter = 1; //Simple   Horizontal Center FOL
	changed_prefs.gfx_ycenter = 1;  //Simple   Vertical Center FOL
	changed_prefs.gfx_width_fs = 480;  //FOL
	changed_prefs.gfx_height_fs = 272;  //FOL
	changed_prefs.gfx_afullscreen = 1; //ON    Amiga FullScreen
	changed_prefs.sound_stereo_separation = 0;

	changed_prefs.chipset_refreshrate = 50; //Chipset Refresh Rate
}

static int prefs_has_changed;

static void insert_floppy(int which)
{
	const char *name = menu_select_file(prefs_get_attr("floppy_path"));

	if (name != NULL)
		strcpy (changed_prefs.df[which], name);
}

static void memory_options(void)
{
	int submenus[3], opt;
	memset(submenus, 0, sizeof(submenus));

	switch(currprefs.chipmem_size)
	{
	case 1 * 1024 * 1024:
		submenus[0] = 1; break;
	case 2 * 1024 * 1024:
		submenus[0] = 2; break;
	case 4 * 1024 * 1024:
		submenus[0] = 3; break;
	case 8 * 1024 * 1024:
		submenus[0] = 4; break;
	case 512 * 1024:
	default:
		submenus[0] = 0; break;
	}
	switch(currprefs.fastmem_size)
	{
	case 1 * 1024 * 1024:
		submenus[2] = 1; break;
	case 2 * 1024 * 1024:
		submenus[2] = 2; break;
	case 4 * 1024 * 1024:
		submenus[2] = 3; break;
	case 8 * 1024 * 1024:
		submenus[2] = 4; break;
	case 0:
	default:
		submenus[2] = 0; break;
	}
	
	opt = menu_select_title("Memory options menu",
			memory_messages, submenus);
	if (opt < 0)
		return;
	prefs_has_changed = 1;
}

static void cpu_options(void)
{
	int submenus[5], opt;
	memset(submenus, 0, sizeof(submenus));

	submenus[0] = currprefs.cpu_level;
	submenus[1] = currprefs.cpu_cycle_exact;
	submenus[2] = currprefs.m68k_speed;
//	submenus[3] = currprefs.chipset_mask; // FIXME!
	submenus[4] = currprefs.chipset_refreshrate == 50;

	opt = menu_select_title("CPU options menu",
			cpu_messages, submenus);
	if (opt < 0)
		return;

	changed_prefs.cpu_level = submenus[0];
	changed_prefs.cpu_cycle_exact = submenus[1];
	changed_prefs.m68k_speed = submenus[2];
	/* FIXME! Chipset mask */
	changed_prefs.chipset_refreshrate = submenus[4] == 1 ? 60 : 50;
	prefs_has_changed = 1;
}

static void general_options(void)
{
}

static void amiga_model_options(void)
{
	int submenus[2];
	int opt;

	memset(submenus, 0, sizeof(submenus));
	opt = menu_select_title("Amiga model menu",
			amiga_model_messages, submenus);
	if (opt < 0)
		return;
	switch(submenus[0])
	{
	case 0:	A1000_config(); break;
	case 1:	A500_config(); break;
	case 2:	A600_config(); break;
	case 3:	A1200_config(); break;
	default: /* custom */
		break;
	}
	/* Cycle-exact or not? */
	changed_prefs.cpu_cycle_exact = submenus[1] == 0 ? 0 : 1;
}

static void save_load_state(int which)
{
	const char *dir = prefs_get_attr("savestate_path");
	const char *floppy0 = prefs_get_attr("floppy0");
	char db[256];
	char fb[81];

	/* Name (for saves) */
	if (floppy0 && strrchr(floppy0, '/'))
		strncpy(fb, strrchr(floppy0, '/') + 1, 80);
	else
		strcpy(fb, "unknown");

	switch(which)
	{
	case 2:
	case 0: /* Load state */
	{
		const char *name = menu_select_file(dir);

		if (!name)
			return;
		snprintf(db, 255, "%s/%s", dir, name);

		if (which == 0)
			restore_state(db);
		else
			unlink(db);
	} break;
	case 1: /* Save state */
		snprintf(db, 255, "%s/%s.sav", dir, fb);
		save_state(db, floppy0);
		break;
	default:
		break;
	}
}

static void exit_fn(void)
{
	sleep(3);
}



void gui_init (int argc, char **argv)
{
	printf("Init gui\n");
	atexit(exit_fn);
}

int gui_open (void)
{
    return -1;
}

void gui_notify_state (int state)
{
}

int gui_update (void)
{
	printf("Al-mibb: Gui is updejted!\n");
    return 0;
}

void gui_exit (void)
{
}

void gui_fps (int fps, int idle)
{
    gui_data.fps  = fps;
    gui_data.idle = idle;
}

void gui_led (int led, int on)
{
}

void gui_hd_led (int led)
{
    static int resetcounter;

    int old = gui_data.hd;

    if (led == 0) {
	resetcounter--;
	if (resetcounter > 0)
	    return;
    }

    gui_data.hd = led;
    resetcounter = 6;
    if (old != gui_data.hd)
	gui_led (5, gui_data.hd);
}

void gui_cd_led (int led)
{
    static int resetcounter;

    int old = gui_data.cd;
    if (led == 0) {
	resetcounter--;
	if (resetcounter > 0)
	    return;
    }

    gui_data.cd = led;
    resetcounter = 6;
    if (old != gui_data.cd)
	gui_led (6, gui_data.cd);
}

void gui_filename (int num, const char *name)
{
}

void gui_handle_events (void)
{
}

void gui_display(int shortcut)
{
	int submenus[3];
	int opt;

	memset(submenus, 0, sizeof(submenus));
	printf("gui_display: %d\n", shortcut);
	prefs_has_changed = 0;

	opt = menu_select_title("Main menu", main_menu_messages, submenus);
	switch(opt)
	{
	case 0:
		/* Insert floppy */
		insert_floppy(submenus[0]);
		break;
	case 2:
		/* States */
		save_load_state(submenus[1]);
		break;
	case 5:
		uae_reset(1);
		break;
	case 6:
		amiga_model_options();
		break;
	case 7:
		general_options();
		break;
	case 8:
		//other_options();
		break;
	case 10:
		uae_quit();
		break;
	default:
		break;
	}
}

void gui_message (const char *format,...)
{
       char msg[2048];
       va_list parms;

       printf("Al-mibb: Gui message!\n");

       va_start (parms,format);
       vsprintf ( msg, format, parms);
       va_end (parms);
//       msgYesNo(msg, 0, 24, 24);

       write_log (msg);
}