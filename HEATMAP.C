/**
 * @brief Show heatmap data
 * @author Thomas Cherryhomes
 * @email thom dot cherryhomes at gmail dot com
 * @license GPL v. 3, see LICENSE for details.
 */

#include <stdio.h>
#include <stdlib.h>

struct Heatmap
{
	unsigned char data[16384];
	char name[80];
	char ts[80];
	char desc[80];
} hm;

read_data()
{
	FILE *fp = fopen("h.dat","rb");

	if (!fp)
	{
		gr_text(0,0,"Could not open h.dat.");
		return 0;
	}

	fread(&hm,16624,1,fp);
	fclose(fp);
	
	return 1;
}

display_data()
{
	short o=0;
	short x=0, y=0;
	short xo=0, yo=0;

	for (y=0; y<128; y++)
	{
		for (x=0; x<128; x++)
		{
			gr_pset(xo,yo,hm.data[o++]);
			xo++;
		}

		xo = 0;
		yo ++;
	}

	gr_text(0,22,hm.name);
	gr_text(0,23,hm.ts);
	gr_text(0,24,hm.desc);

	gr_text(0,0,"");
}

legend()
{
	int i=0;
	char *t[8];

	t[0] = "< 20*C";
	t[1] = "  25*C";
	t[2] = "  30*C";
	t[3] = "  35*C";
	t[4] = "  40*C";
	t[5] = "  45*C";
	t[6] = "  50*C";
	t[7] = "> 55*C";

	for (i=0;i<8;i++)
	{
		gr_bar(256,i*8+16,264,i*8+16+8,i);
		gr_text(34,i+2,t[i]);
	}
}

main()
{
	int oldmode = gr_mode(-1);

	gr_mode(0x04);

	if (!read_data())
		return 1;

	legend();
	display_data();

	getchar();

	gr_mode(oldmode);

	return 0;
}
